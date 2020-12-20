#include "DHT.h"
#include "SoftwareSerial.h"

#define DHTPIN 8 // Declaramos el pin que se va a conectar al sensor DHT11
#define DHTTYPE DHT11 //Declaramos el sensor que vamos a utilizar

String ssid ="IZZI-71E4";
String password="8871B1C271E4";
String server = "proyectoarq20.000webhostapp.com"; // www.example.com
String uri = "/temperatura.php";// our example is /esppost.php
String uriGet = "/tomar.php";// our example is /esppost.php

int ubicacion = 0;
String tomar = ""; //to store HTTP request

String data;

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial esp(6, 7);// RX, TX

unsigned long lastTimeMillis = 0;

void setup() {
  Serial.println("Setup.");
  
  esp.begin(9600);
  Serial.begin(9600);

  dht.begin();
  
  reset();
  
  Serial.print("Conecting to "+ssid+".");
  connectWifi();
}

//reset the esp module
void reset() {
  //Reseting module
  esp.println("AT+RST");
  if(esp.find("OK")) 
    Serial.println("Module Reset.");
    
  //Checking the ESP8266 response
  esp.println("AT");
  if(esp.find("OK"))
    Serial.println("AT OK.");
  else
    Serial.println("Error on ESP8266!!!");
  
  //ESP8266 in STA mode.
  esp.println("AT+CWMODE=1");
  if(esp.find("OK"))
    Serial.println("ESP8266 on STATION mode.");

  esp.println("AT+CIPMUX=0");
  if(esp.find("OK"))
    Serial.println("Multiple connections disabled.");
}

//connect to your wifi network
void connectWifi() {
  //Conectamos al wifi
  
  esp.println("AT+CWJAP=\""+ssid+"\",\""+password + "\"");
  delay(1000);
  
  if(esp.find("OK")) {
    Serial.println("\nConected!");
    }
  else {
    Serial.print(".");
    connectWifi();
    }
}
void loop () {
  Serial.println("---------------Tomar-----------------");
  httpGet();
  
  if(tomar == "1"){
    Serial.println("---------------Enviar----------------- ");
    getData();
    Serial.println("Informacion a enviar: " + data);
    httppost();
    }
  delay(5000);
}

void getData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  data = "temp=" + String(temp) + "&hum=" + hum;// data sent must be under this form //name1=value1&name2=value2.
}

void httppost () {
  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
  if(esp.find("OK")) {
    Serial.println("TCP connection ready");
    } 
  delay(500);

  String postRequest =
    "POST " + uri + " HTTP/1.0\r\n" +
    "Host: " + server + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "\r\n" + data;

  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
  esp.print(sendCmd);
  esp.println(postRequest.length());
  delay(500);

  if(esp.find(">")){
    Serial.println("Sending..."); 
    esp.print(postRequest);
    
    if( esp.find("SEND OK")) { 
      Serial.println("Packet sent.");
        
      //Close the connection
      esp.println("AT+CIPCLOSE");
      
      if( esp.find("CLOSED"))
        Serial.println("Package sent.");
        Serial.println("Connection terminated.");
    }
  }
}

void httpGet() {
  tomar = "0";
  //connecting to server
  Serial.println("Connecting to server...");
  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");
  if(esp.find("OK")) {
    Serial.println("Server connection successful!");
    
    //Armamos el encabezado de la peticion http
    String peticionHTTP = "GET /tomar.php HTTP/1.1\r\n";
    peticionHTTP = peticionHTTP + "Host: " + server+ "\r\n\r\n";
    peticionHTTP = peticionHTTP + "Host: localhost\r\n\r\n";
    
    //Sending the length of the HTTP request
    esp.print("AT+CIPSEND=");
    esp.println(peticionHTTP.length());
    
    //waiting for ">" for sending HTTP request
    if(esp.find(">")) {
      
      //we can send the HTTP request when > is displayed
      Serial.println("Sending HTTP request.");
      esp.println(peticionHTTP);
      
      if(esp.find("SEND OK")) {
        Serial.println("HTTP request sent.");
        Serial.println();
        Serial.println("On stand by...");
        boolean fin_respuesta=false;
        long tiempo_inicio=millis();
        String cadena="";
        
        while(fin_respuesta==false) {
          while(esp.available()>0) {
            char c=esp.read();
            //Serial.write(c);
            cadena.concat(c); //store the request string on "cadena"
            if (cadena.length() > 50) {
              if(cadena.indexOf("Valor = ")>0){
                ubicacion = cadena.indexOf("Valor = ");
                tomar = cadena.substring(ubicacion+8,ubicacion+9);
                }
              cadena = "";
            }
            
            
          }
          if(cadena.indexOf("CLOSED")>0) {
            Serial.println();
            Serial.println("String OK, connection terminated");
            fin_respuesta=true;
          }
        }
      } else {
        Serial.println("Error on HTTP request.");
      }
    }
  } else {
    Serial.println("Unable to find the server.");
  }
  Serial.println("Valor tomado:" + tomar);
}
