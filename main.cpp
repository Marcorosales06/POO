// main.cpp
#include "biblioteca.h"
#include <limits> 

void mostrarMenu() {
    cout << "--- Menú de Libros (CRUD) ---\n";
    cout << "1. Agregar Libro\n";
    cout << "2. Listar Todos los Libros\n";
    cout << "3. Actualizar Libro por ID\n";
    cout << "4. Eliminar Libro por ID\n";
    cout << "--- Menú de Préstamos (Relaciones) ---\n";
    cout << "5. Prestar Libro\n";
    cout << "6. Devolver Libro\n";
    cout << "0. Salir y Guardar Todo\n";
    cout << "Ingrese su opción: ";
}

int main() {
    BibliotecaDB db;
    db.inicializar();

    int opcion;
    while (true) {
        mostrarMenu();

        if (!(cin >> opcion)) {
            cout << "\n*** Error: Entrada inválida. Por favor ingrese un número. ***\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        switch (opcion) {
            case 1:
                db.agregarLibro();
                break;
            case 2:
                db.listarLibros();
                break;
            case 3:
                db.actualizarLibro();
                break;
            case 4:
                db.eliminarLibro();
                break;
            case 5:
                db.prestarLibro();
                break;
            case 6:
                db.devolverLibro();
                break;
            case 0:
                cout << "\nGuardando todos los cambios antes de salir...\n";
                db.guardarLibros();
                cout << "¡Datos guardados! Saliendo del sistema.\n";
                return 0;
            default:
                cout << "\n*** Opción no válida. Intente de nuevo. ***\n";
        }
    }
}