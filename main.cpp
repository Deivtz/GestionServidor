/**
 * @file main.cpp
 * @brief Proyecto Final - Sistema de gestion para servidor de MAINKRA.
 * @author David Barrios
 * @date 26 de mayo de 2026
 */

#include <iostream>
#include <windows.h>
#include <time.h>
#include "MySQLConexion.h"
#include "MySQLModel.h"
#include "EloquentORM.h"

using namespace std;

/**
 * @brief Enumeracion de colores para facilitar el diseno en la consola.
 */
enum Colors {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5,
    BROWN = 6, LGREY = 7, DGREY = 8, LBLUE = 9, LGREEN = 10,
    LCYAN = 11, LRED = 12, LMAGENTA = 13, YELLOW = 14, WHITE = 15
};

/**
 * @brief Cambia el color del texto y del fondo en la consola de Windows.
 * @param background Color de fondo deseado.
 * @param text Color del texto deseado.
 */
void aplicar_color(int background, int text) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int newColor = text + (background * 16);
    SetConsoleTextAttribute(consoleHandle, newColor);
}

/**
 * @brief Limpia la pantalla de la consola usando secuencias de escape ANSI.
 */
void limpiar_pantalla() { 
    cout << "\033[2J\033[H"; 
}

/**
 * @brief Pausa la ejecucion del programa por una cantidad especifica de milisegundos.
 * @param ms Cantidad de milisegundos a esperar.
 */
void esperar_tiempo(int ms) { 
    for(clock_t t = clock(); (clock() - t) * 1000 / CLOCKS_PER_SEC < ms;); 
}

/**
 * @brief Dibuja el menu principal del sistema en la consola.
 */
void mostrar_menu() {
    limpiar_pantalla();
    aplicar_color(BLACK, LCYAN);
    cout << "=========================================" << endl;
    cout << "      PANEL DE CONTROL DEL SERVIDOR      " << endl;
    cout << "=========================================" << endl;
    
    aplicar_color(BLACK, WHITE);
    cout << "\n1. Gestionar Clanes (Create / Read)" << endl;
    cout << "2. Gestionar Jugadores (Create / Read)" << endl;
    cout << "3. Actualizar Datos (Update)" << endl;
    cout << "4. Eliminar Registros (Delete)" << endl;
    cout << "5. Salir del Sistema" << endl;
    cout << "\nSelecciona una opcion: ";
}

/**
 * @brief Funcion principal que arranca el sistema y maneja el bucle del menu.
 * @return 0 si el programa finaliza correctamente.
 */
int main() {
    int opcionElegida = 0;
    bool sistemaActivo = true;
    
    // Animacion de carga inicial para la interfaz
    limpiar_pantalla();
    aplicar_color(BLACK, YELLOW);
    cout << "Iniciando sistema";
    for(int i = 0; i < 3; i++) {
        esperar_tiempo(500);
        cout << ".";
    }
    cout << "\n¡Bienvenido, Administrador!" << endl;
    esperar_tiempo(1000);

    // Inicializacion y validacion de la conexion a la base de datos
    MySQLConexion conexion("root", "Tm05121204SND", "control_servidor_db");

    if (conexion.open()) {
        aplicar_color(BLACK, LGREEN); 
        cout << "\n[+] Conexion a la base de datos del server exitosa!\n";
    } else {
        aplicar_color(BLACK, LRED);   
        cout << "\n[-] Fallo al conectar a la base de datos. Revisa tus credenciales.\n";
    }
    esperar_tiempo(3000); // Pausa para visualizar el estado de la conexion

    // Bucle principal del sistema
    while (sistemaActivo) {
        mostrar_menu();
        cin >> opcionElegida;

        // Manejo de excepciones para entradas de tipo no entero (limpieza de buffer)
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcionElegida = 0;
        }

        switch (opcionElegida) {
            case 1: {
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- REGISTRAR NUEVO CLAN ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string nombreClan, descClan;
                
                cout << "Ingresa el nombre del clan: ";
                // Extraccion de flujo con ws para permitir lectura de cadenas con espacios
                getline(cin >> ws, nombreClan); 
                
                cout << "Ingresa una breve descripcion: ";
                getline(cin, descClan);
                
                // Instanciar el modelo ORM para la tabla clanes e insertar los datos
                EloquentORM clan(conexion, "clanes", {"nombre", "descripcion"});
                clan.set("nombre", nombreClan);
                clan.set("descripcion", descClan);
                
                if(clan.save()) {
                    aplicar_color(BLACK, LGREEN);
                    cout << "\n[+] Clan '" << nombreClan << "' creado y guardado exitosamente!" << endl;
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Hubo un error al guardar el clan en la base de datos." << endl;
                }
                
                esperar_tiempo(2500); 
                break;
            }
            case 2: { 
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- REGISTRAR NUEVO JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string nicknameJugador, nivelJugador, idClan;
                
                cout << "Ingresa el nickname del jugador: ";
                getline(cin >> ws, nicknameJugador); 
                
                cout << "Ingresa el nivel del jugador (ej. 1, 50, 99): ";
                getline(cin, nivelJugador);
                
                cout << "Ingresa el ID del clan al que pertenece (ej. 1, 2, 3): ";
                getline(cin, idClan);
                
                // Instanciar el modelo ORM para guardar un nuevo jugador ligado a un clan
                EloquentORM jugador(conexion, "jugadores", {"nickname", "nivel", "clan_id"});
                jugador.set("nickname", nicknameJugador);
                jugador.set("nivel", nivelJugador);
                jugador.set("clan_id", idClan);
                
                if(jugador.save()) {
                    aplicar_color(BLACK, LGREEN);
                    cout << "\n[+] Jugador '" << nicknameJugador << "' registrado exitosamente!" << endl;
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Error al registrar jugador. (Verificar llave foranea de clan_id)." << endl;
                }
                
                esperar_tiempo(2500);
                break;
            }
            case 3: { 
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- ACTUALIZAR NIVEL DE JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                int idJugador;
                string nuevoNivel;
                
                cout << "Ingresa el ID del jugador a actualizar (ej. 1, 2, 3): ";
                cin >> idJugador;
                
                cout << "Ingresa el nuevo nivel: ";
                getline(cin >> ws, nuevoNivel);
                
                // Busqueda del registro por PK y actualizacion de sus atributos
                EloquentORM jugador(conexion, "jugadores", {"id", "nickname", "nivel", "clan_id"});
                
                if(jugador.find(idJugador)) {
                    jugador.set("nivel", nuevoNivel); 
                    if(jugador.save()) {
                        aplicar_color(BLACK, LGREEN);
                        cout << "\n[+] Nivel actualizado exitosamente a " << nuevoNivel << "!" << endl;
                    } else {
                        aplicar_color(BLACK, LRED);
                        cout << "\n[-] Error al ejecutar la actualizacion en la base de datos." << endl;
                    }
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] No se encontro ningun jugador con el ID " << idJugador << "." << endl;
                }
                
                esperar_tiempo(3000);
                break;
            }
            case 4: {
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- ELIMINAR JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                int idJugador;
                cout << "Ingresa el ID del jugador a eliminar del sistema: ";
                cin >> idJugador;
                
                EloquentORM jugador(conexion, "jugadores", {"id", "nickname", "nivel", "clan_id"});
                
                // Validacion de existencia previo a la operacion de eliminacion (DELETE)
                if(jugador.find(idJugador)) {
                    if(jugador.remove()) {
                        aplicar_color(BLACK, LGREEN);
                        cout << "\n[+] Jugador eliminado exitosamente del servidor." << endl;
                    } else {
                        aplicar_color(BLACK, LRED);
                        cout << "\n[-] Error al intentar eliminar el registro." << endl;
                    }
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] No se encontro ningun jugador con el ID " << idJugador << "." << endl;
                }
                
                esperar_tiempo(3000);
                break;
            }
            case 5:
                aplicar_color(BLACK, GREEN);
                cout << "\nCerrando sesion... ¡Hasta luego!" << endl;
                sistemaActivo = false;
                esperar_tiempo(1000);
                break;
            default:
                aplicar_color(BLACK, RED);
                cout << "\nError: Opcion no valida. Intenta de nuevo." << endl;
                esperar_tiempo(1500);
                break;
        }
    }
    
    // Restauracion de los atributos de color de la consola al finalizar la ejecucion
    aplicar_color(BLACK, WHITE);
    return 0;
}