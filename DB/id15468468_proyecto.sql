-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 20-12-2020 a las 02:42:54
-- Versión del servidor: 10.3.16-MariaDB
-- Versión de PHP: 7.3.23

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `id15468468_proyecto`
--
CREATE DATABASE IF NOT EXISTS `id15468468_proyecto` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `id15468468_proyecto`;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Checar`
--

CREATE TABLE `Checar` (
  `IdChecar` int(11) NOT NULL,
  `Tomar` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Volcado de datos para la tabla `Checar`
--

INSERT INTO `Checar` (`IdChecar`, `Tomar`) VALUES
(1, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `medidas`
--

CREATE TABLE `medidas` (
  `id_medida` int(11) NOT NULL,
  `fecha_medida` timestamp NOT NULL DEFAULT current_timestamp(),
  `temp` double(10,2) DEFAULT NULL,
  `humedad` int(2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `medidas`
--

INSERT INTO `medidas` (`id_medida`, `fecha_medida`, `temp`, `humedad`) VALUES
(119, '2020-12-16 16:08:41', 19.40, 45),
(120, '2020-12-16 16:10:41', 19.50, 45),
(121, '2020-12-16 16:10:49', 19.60, 44),
(122, '2020-12-16 16:11:29', 19.70, 44),
(123, '2020-12-16 16:11:37', 19.70, 43),
(124, '2020-12-16 16:11:46', 19.70, 43),
(125, '2020-12-16 16:11:54', 19.70, 43),
(126, '2020-12-16 16:15:19', 19.80, 43),
(127, '2020-12-16 16:15:27', 24.10, 95),
(128, '2020-12-16 16:15:35', 23.40, 95),
(129, '2020-12-16 16:15:49', 23.10, 95),
(130, '2020-12-16 16:15:58', 22.60, 95),
(131, '2020-12-16 16:16:12', 22.30, 95),
(132, '2020-12-16 16:16:58', 21.90, 93),
(133, '2020-12-16 16:18:47', 20.90, 70),
(134, '2020-12-16 16:19:14', 20.50, 44),
(135, '2020-12-19 18:25:23', 20.90, 58);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `Checar`
--
ALTER TABLE `Checar`
  ADD PRIMARY KEY (`IdChecar`);

--
-- Indices de la tabla `medidas`
--
ALTER TABLE `medidas`
  ADD PRIMARY KEY (`id_medida`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `medidas`
--
ALTER TABLE `medidas`
  MODIFY `id_medida` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=136;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
