/**
 * @file main.cpp
 * @brief Proyecto Final - Sistema de gestion para servidor de videojuegos.
 * @author David Barrios
 * @date 27 de mayo de 2026
 *
 * @details Este modulo contiene el menu principal interactivo y la integracion
 * del framework EloquentORM para la persistencia de datos en MySQL.
 */

#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>
#include "MySQLConexion.h"
#include "MySQLModel.h"
#include "EloquentORM.h"

using namespace std;

/**
 * @brief Enumeracion de codigos de color ANSI para la consola.
 */
enum Colors {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5,
    BROWN = 6, LGREY = 7, DGREY = 8, LBLUE = 9, LGREEN = 10,
    LCYAN = 11, LRED = 12, LMAGENTA = 13, YELLOW = 14, WHITE = 15
};

/**
 * @brief Modifica los atributos de color del texto y fondo en la consola.
 * * @param background Color de fondo.
 * @param text Color del texto.
 */
void aplicar_color(int background, int text) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int newColor = text + (background * 16);
    SetConsoleTextAttribute(consoleHandle, newColor);
}

/**
 * @brief Limpia la pantalla utilizando secuencias de escape.
 */
void limpiar_pantalla() { 
    cout << "\033[2J\033[H"; 
}

/**
 * @brief Introduce una pausa en la ejecucion del hilo actual.
 * * @param ms Tiempo de espera en milisegundos.
 */
void esperar_tiempo(int ms) { 
    for(clock_t t = clock(); (clock() - t) * 1000 / CLOCKS_PER_SEC < ms;); 
}

/**
 * @brief Despliega la interfaz del menu principal del sistema.
 */
void mostrar_menu() {
    limpiar_pantalla();
    aplicar_color(BLACK, LCYAN);
    cout << "=========================================" << endl;
    cout << "      PANEL DE CONTROL DEL SERVIDOR      " << endl;
    cout << "=========================================" << endl;
    
    aplicar_color(BLACK, WHITE);
    cout << "\n1. Registrar Clan (Create)" << endl;
    cout << "2. Registrar Jugador (Create)" << endl;
    cout << "3. Actualizar Nivel de Jugador (Update)" << endl;
    cout << "4. Eliminar Jugador (Delete)" << endl;
    cout << "5. Ver Lista de Jugadores (Read)" << endl;
    cout << "6. Salir del Sistema" << endl;
    cout << "\nSelecciona una opcion: ";
}

/**
 * @brief Punto de entrada de la aplicacion.
 * * Gestiona el ciclo de vida de la UI de consola, instanciando la conexion
 * a la base de datos y controlando las peticiones CRUD.
 * * @return int Codigo de estado final (0 = Exito).
 */
int main() {
    int opcionElegida = 0;
    bool sistemaActivo = true;
    
    limpiar_pantalla();
    aplicar_color(BLACK, YELLOW);
    cout << "Iniciando sistema";
    for(int i = 0; i < 3; i++) {
        esperar_tiempo(500);
        cout << ".";
    }
    cout << "\n¡Bienvenido, Administrador!" << endl;
    esperar_tiempo(1000);

    // Inicializacion de la conexion a la capa de persistencia de datos
    MySQLConexion conexion("root", "Tm05121204SND", "control_servidor_db");

    if (conexion.open()) {
        aplicar_color(BLACK, LGREEN); 
        cout << "\n[+] Conexion a la base de datos del server exitosa!\n";
    } else {
        aplicar_color(BLACK, LRED);   
        cout << "\n[-] Fallo al conectar a la base de datos. Revisa tus credenciales.\n";
    }
    esperar_tiempo(3000);

    // Ciclo de control principal
    while (sistemaActivo) {
        mostrar_menu();
        cin >> opcionElegida;

        // Limpieza del stream de entrada para evitar loops por caracteres invalidos
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcionElegida = 0;
        }

        switch (opcionElegida) {
            case 1: { // Modulo: Create (Clanes)
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- REGISTRAR NUEVO CLAN ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string nombreClan, descClan;
                
                cout << "\nIngresa el nombre del clan (o '0' para cancelar): ";
                getline(cin >> ws, nombreClan); 
                
                if (nombreClan == "0") {
                    aplicar_color(BLACK, YELLOW);
                    cout << "\n[!] Operacion cancelada. Regresando al menu..." << endl;
                    Sleep(1000);
                    break; 
                }

                if (nombreClan.empty()) {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Error: El nombre no puede ser nulo." << endl;
                    cout << "\nPresiona Enter para volver al menu...";
                    system("pause>nul");
                    break;
                }
                
                cout << "Ingresa una breve descripcion: ";
                getline(cin, descClan);
                
                EloquentORM clan(conexion, "clanes", {"nombre", "descripcion"});
                clan.set("nombre", nombreClan);
                clan.set("descripcion", descClan);
                
                if(clan.save()) {
                    aplicar_color(BLACK, LGREEN);
                    cout << "\n[+] Clan '" << nombreClan << "' guardado exitosamente." << endl;
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Excepcion al ejecutar la transaccion." << endl;
                }
                
                aplicar_color(BLACK, DGREY);
                cout << "\nPresiona cualquier tecla para continuar...";
                system("pause>nul"); 
                break;
            }
            case 2: { // Modulo: Create (Jugadores)
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- REGISTRAR NUEVO JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string nicknameJugador, nivelJugador, idClan;
                
                cout << "\nIngresa el nickname del jugador (o '0' para cancelar): ";
                getline(cin >> ws, nicknameJugador); 
                
                if (nicknameJugador == "0") {
                    aplicar_color(BLACK, YELLOW);
                    cout << "\n[!] Operacion cancelada." << endl;
                    Sleep(1000);
                    break; 
                }

                if (nicknameJugador.empty()) {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Error: El nickname es un campo obligatorio." << endl;
                    cout << "\nPresiona Enter para volver al menu...";
                    system("pause>nul");
                    break;
                }
                
                cout << "Ingresa el nivel del jugador (ej. 1, 50, 99): ";
                getline(cin, nivelJugador);
                
                cout << "Ingresa el ID del clan al que pertenece (ej. 1, 2, 3): ";
                getline(cin, idClan);
                
                EloquentORM jugador(conexion, "jugadores", {"nickname", "nivel", "clan_id"});
                jugador.set("nickname", nicknameJugador);
                jugador.set("nivel", nivelJugador);
                jugador.set("clan_id", idClan);
                
                if(jugador.save()) {
                    aplicar_color(BLACK, LGREEN);
                    cout << "\n[+] Jugador '" << nicknameJugador << "' registrado." << endl;
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] Error de integridad referencial. (Verifique clan_id)." << endl;
                }
                
                aplicar_color(BLACK, DGREY);
                cout << "\nPresiona cualquier tecla para continuar...";
                system("pause>nul");
                break;
            }
            case 3: { // Modulo: Update (Jugadores)
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- ACTUALIZAR NIVEL DE JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string entradaId;
                int idJugador;
                string nuevoNivel;
                
                cout << "\nIngresa el ID del jugador a actualizar (o '0' para cancelar): ";
                cin >> entradaId;
                
                if (entradaId == "0") {
                    aplicar_color(BLACK, YELLOW);
                    cout << "\n[!] Operacion cancelada." << endl;
                    Sleep(1000);
                    break; 
                }
                
                idJugador = stoi(entradaId); 
                
                cout << "Ingresa el nuevo nivel: ";
                getline(cin >> ws, nuevoNivel);
                
                EloquentORM jugador(conexion, "jugadores", {"id", "nickname", "nivel", "clan_id"});
                
                if(jugador.find(idJugador)) {
                    jugador.set("nivel", nuevoNivel); 
                    if(jugador.save()) {
                        aplicar_color(BLACK, LGREEN);
                        cout << "\n[+] Nivel actualizado a " << nuevoNivel << "." << endl;
                    } else {
                        aplicar_color(BLACK, LRED);
                        cout << "\n[-] Error durante la actualizacion." << endl;
                    }
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] El registro con ID " << idJugador << " no existe." << endl;
                }
                
                aplicar_color(BLACK, DGREY);
                cout << "\nPresiona cualquier tecla para continuar...";
                system("pause>nul");
                break;
            }
            case 4: { // Modulo: Delete (Jugadores)
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- ELIMINAR JUGADOR ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                string entradaId;
                int idJugador;
                
                cout << "\nIngresa el ID del jugador a eliminar (o '0' para cancelar): ";
                cin >> entradaId;
                
                if (entradaId == "0") {
                    aplicar_color(BLACK, YELLOW);
                    cout << "\n[!] Operacion cancelada." << endl;
                    Sleep(1000);
                    break; 
                }
                
                idJugador = stoi(entradaId);
                
                EloquentORM jugador(conexion, "jugadores", {"id", "nickname", "nivel", "clan_id"});
                
                if(jugador.find(idJugador)) {
                    if(jugador.remove()) {
                        aplicar_color(BLACK, LGREEN);
                        cout << "\n[+] Registro eliminado del sistema." << endl;
                    } else {
                        aplicar_color(BLACK, LRED);
                        cout << "\n[-] Fallo en la ejecucion del comando DELETE." << endl;
                    }
                } else {
                    aplicar_color(BLACK, LRED);
                    cout << "\n[-] El registro con ID " << idJugador << " no existe." << endl;
                }
                
                aplicar_color(BLACK, DGREY);
                cout << "\nPresiona cualquier tecla para continuar...";
                system("pause>nul");
                break;
            }
            case 5: { // Modulo: Read All (Jugadores)
                limpiar_pantalla();
                aplicar_color(BLACK, LCYAN);
                cout << "--- LISTADO GENERAL DE JUGADORES ---" << endl;
                aplicar_color(BLACK, WHITE);
                
                EloquentORM jugador(conexion, "jugadores", {"id", "nickname", "nivel", "clan_id"});
                vector<map<string, string>> listaJugadores = jugador.getAll(); 
                
                if (listaJugadores.empty()) {
                    aplicar_color(BLACK, YELLOW);
                    cout << "\n[!] No existen registros en la entidad 'jugadores'." << endl;
                } else {
                    aplicar_color(BLACK, LGREEN);
                    cout << "\nID\tNIVEL\tID_CLAN\t\tNICKNAME" << endl;
                    cout << "---------------------------------------------------" << endl;
                    aplicar_color(BLACK, WHITE);
                    
                    // Iteracion sobre el conjunto de resultados retornados por el ORM
                    for (auto &fila : listaJugadores) {
                        cout << fila["id"] << "\t" 
                             << fila["nivel"] << "\t" 
                             << fila["clan_id"] << "\t\t" 
                             << fila["nickname"] << endl;
                    }
                }
                
                aplicar_color(BLACK, DGREY);
                cout << "\nPresiona cualquier tecla para volver al menu...";
                system("pause>nul");
                break;
            }
            case 6: // Modulo: Salida Segura
                aplicar_color(BLACK, GREEN);
                cout << "\nFinalizando sesion... ¡Hasta luego!" << endl;
                sistemaActivo = false;
                Sleep(1000); 
                break;
            default: // Validacion de entrada fuera de rango
                aplicar_color(BLACK, RED);
                cout << "\nError: Opcion no contemplada en el menu." << endl;
                Sleep(1500);
                break;
        }
    }
    
    aplicar_color(BLACK, WHITE);
    return 0;
}