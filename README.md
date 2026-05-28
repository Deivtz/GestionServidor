# 🎮 Panel de Control de Servidor de videojuegos - Proyecto Final

Bienvenido al repositorio del sistema de gestión para un servidor de videojuegos. Este proyecto fue desarrollado como entrega final para el curso de **Programación 1** de la Universidad Mariano Gálvez de Guatemala.

## 🚀 Descripción
Es un sistema CRUD interactivo desarrollado en **C++ puro** e integrado con una base de datos relacional en **MySQL**. El proyecto hace uso de una abstracción de base de datos (`EloquentORM`) para manejar la persistencia de datos directamente desde la consola, aplicando conceptos de llaves primarias y foráneas.

## 🛠️ Tecnologías Utilizadas
* **Lenguaje principal:** C++17
* **Base de Datos:** MySQL Server 8.0
* **Herramienta de DB:** HeidiSQL
* **Compilador:** MinGW (g++)
* **Entorno:** Visual Studio Code

## ✨ Funcionalidades Principales (CRUD)
El sistema gestiona una relación de 1 a muchos (1:N) entre las entidades, permitiendo:
* **Create:** Registro de nuevos clanes y vinculación de nuevos jugadores.
* **Read:** Visualización tabular y en tiempo real de todos los usuarios registrados en el servidor.
* **Update:** Actualización del nivel de los jugadores existentes.
* **Delete:** Eliminación segura de registros mediante validación de ID.

## 📂 Estructura de la Base de Datos
El proyecto opera sobre la base de datos `control_servidor_db` con las siguientes tablas:
1. `clanes` (Tabla Padre)
2. `jugadores` (Tabla Hija - vinculada mediante `clan_id`)

---
*Desarrollado por David Barrios - Mariano Gálvez, Flores, Petén, 2026.*
