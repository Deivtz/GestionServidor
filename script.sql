-- Universidad Mariano Gálvez
-- Facultad de Ingeniería en Sistemas
-- Curso: Programación 1
-- Autor: David Barrios
-- Fecha: 19 de mayo de 2026
-- Descripción: Script inicial de base de datos para el control de un servidor de videojuegos (Proyecto Final)

CREATE DATABASE IF NOT EXISTS control_servidor_db;
USE control_servidor_db;

-- ========================================================
-- Entidad Padre: clanes (Grupos organizados en el servidor)
-- ========================================================
CREATE TABLE clanes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(50) NOT NULL,
    descripcion VARCHAR(150)
);

-- ========================================================
-- Entidad Hija: jugadores (Usuarios registrados)
-- Cumple con la regla obligatoria de FK: tabla_id (clan_id)
-- ========================================================
CREATE TABLE jugadores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nickname VARCHAR(50) NOT NULL,
    nivel INT DEFAULT 1,
    clan_id INT,
    FOREIGN KEY (clan_id) REFERENCES clanes(id)
);

-- Registros iniciales base para pruebas de conexión posteriores
INSERT INTO clanes (nombre, descripcion) VALUES ('Gremio Alfa', 'Clan principal de pruebas'), ('Beta Force', 'Segundo clan de soporte');
INSERT INTO jugadores (nickname, nivel, clan_id) VALUES ('Deivtz', 99, 1), ('PlayerOne', 10, 2);