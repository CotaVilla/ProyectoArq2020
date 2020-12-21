#include "SoftwareSerial.h"
//Wifi id and password
String ssid ="Christian3";
String password="Bosco130392";

String server = "proyectoarq20.000webhostapp.com"; // www.example.com
String uri = "/actuar.php";// our example is /esppost.php

String data = "ruido=1";
SoftwareSerial esp(6, 7);// RX, TX
unsigned long lastTimeMillis = 0;
//Pin numero 2 que va conectado el puerto 2
int MIC = 5;
int VALOR;
int acumulador;
int llave;

void setup() {
  pinMode(MIC, INPUT);
  
  Serial.println("Setup.");
  esp.begin(9600);
  Serial.begin(9600);
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
//AQUI ESTA EL LOOP
void loop () {
  //Capturamos el valor que nos da el micro y lo guardamos
  VALOR = digitalRead(MIC);
  //imprimimos el valor del micro que nos da para comprobar que sirve
  Serial.println(VALOR);
  //Si el valor que nos da es negativo o bajo (si es igual a 0)
  if(VALOR==LOW)
  {
    //entonces
    Serial.println("---------------Enviar----------------- ");
    Serial.println("Informacion a enviar: " + data);
    //enviamos datos por medio de este metodo
    httppost();
  }
  delay(100);
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
      if( esp.find("OK"))
        Serial.println("Package sent.");
        Serial.println("Connection terminated.");
    }
  }
}
