/**
 * @file main.cpp
 * @brief Proyecto Final - Sistema de gestion para servidor de MAINKRA.
 * @author David Barrios
 * @date 20 de mayo de 2026
 */

#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

/**
 * @brief Enumeración de colores para facilitar el diseño en la consola.
 */
enum Colors {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5,
    BROWN = 6, LGREY = 7, DGREY = 8, LBLUE = 9, LGREEN = 10,
    LCYAN = 11, LRED = 12, LMAGENTA = 13, YELLOW = 14, WHITE = 15
};

/**
 * @brief Cambia el color del texto y del fondo en la consola de Windows.
 * * @param background Color de fondo deseado.
 * @param text Color del texto deseado.
 */
void aplicar_color(int background, int text) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // variable en camelCase
    int newColor = text + (background * 16);                // variable en camelCase
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
 * * @param ms Cantidad de milisegundos a esperar.
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
 * * @return 0 si el programa finaliza correctamente.
 */
int main() {
    int opcionElegida = 0;     // variable en camelCase
    bool sistemaActivo = true; // variable en camelCase
    
    // Simulacion de carga inicial interactiva
    limpiar_pantalla();
    aplicar_color(BLACK, YELLOW);
    cout << "Iniciando sistema";
    for(int i = 0; i < 3; i++) {
        esperar_tiempo(500); // Espera medio segundo por cada punto
        cout << ".";
    }
    cout << "\n¡Bienvenido, Administrador!" << endl;
    esperar_tiempo(1000);

    // Bucle principal (Loop del Menu)
    while (sistemaActivo) {
        mostrar_menu();
        cin >> opcionElegida;

        // Limpia el error de lectura por si el usuario mete una letra en lugar de numero
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcionElegida = 0;
        }

        switch (opcionElegida) {
            case 1:
                cout << "\n[Modulo de Clanes en construccion...]" << endl;
                esperar_tiempo(1500);
                break;
            case 2:
                cout << "\n[Modulo de Jugadores en construccion...]" << endl;
                esperar_tiempo(1500);
                break;
            case 3:
                cout << "\n[Modulo de Actualizacion en construccion...]" << endl;
                esperar_tiempo(1500);
                break;
            case 4:
                cout << "\n[Modulo de Eliminacion en construccion...]" << endl;
                esperar_tiempo(1500);
                break;
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
    
    // Regresar el color a la normalidad al salir a la terminal de Windows
    aplicar_color(BLACK, WHITE);
    return 0;
}