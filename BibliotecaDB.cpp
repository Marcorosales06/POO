#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits> 
#include <algorithm> 

using namespace std;
struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano;
    bool disponible; 
};

struct Estudiante {
    int id;
    string nombre;
    string carnet;
};
 
class BibliotecaDB {
public:
    vector<Libro> libros;   
    vector<Estudiante> estudiantes;
    void guardarLibros() const {
        ofstream archivo("libros.txt");
        if (archivo.is_open()) {
            for (const auto& lib : libros) {
                archivo << lib.id << "," << lib.titulo << "," << lib.isbn << "," << lib.ano << "," << (lib.disponible ? 1 : 0) << endl;
            }
            archivo.close();
        } else {
            cerr << "Error: No se pudo abrir 'libros.txt' para escribir." << endl;
        }
    }

    void cargarLibros() {
        ifstream archivo("libros.txt");
        libros.clear(); 
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                stringstream ss(linea);
                string segmento;
                Libro l;
                int disp_int;

                getline(ss, segmento, ',');
                l.id = stoi(segmento);
                getline(ss, l.titulo, ',');
                getline(ss, l.isbn, ',');
                getline(ss, segmento, ',');
                l.ano = stoi(segmento);
                getline(ss, segmento, ',');
                disp_int = stoi(segmento);
                l.disponible = (disp_int == 1);

                libros.push_back(l);
            }
            archivo.close();
            cout << "Libros cargados con éxito (" << libros.size() << " registros)." << endl;
        } else {
            cout << "Advertencia: Archivo 'libros.txt' no encontrado. Se inicia con lista vacía." << endl;
        }
    }
    
    Libro* buscarLibroPorId(int id) {
        for (auto& l : libros) {
            if (l.id == id) {
                return &l;
            }
        }
        return nullptr;
    }

    void agregarLibro() {
        Libro l;
        cout << "\n--- Agregar Libro ---\n";
        cout << "ID: ";
        while (!(cin >> l.id) || buscarLibroPorId(l.id) != nullptr) {
            if (buscarLibroPorId(l.id) != nullptr) {
                cout << "Error: ID duplicado. Ingrese otro ID: ";
            } else {
                cout << "Error: Entrada inválida. Ingrese un número para el ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cin.ignore(); 

        cout << "Título: ";
        getline(cin, l.titulo);

        cout << "ISBN: ";
        getline(cin, l.isbn);

        cout << "Año: ";
        while (!(cin >> l.ano)) {
            cout << "Error: Entrada inválida. Ingrese un número para el Año: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        l.disponible = true;
        libros.push_back(l);
        guardarLibros();
        cout << "\n¡Libro agregado y guardado con éxito!\n";
    }


    void listarLibros() const {
        cout << "\n--- Lista de Libros (" << libros.size() << " en total) ---\n";
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
            return;
        }
        for (const auto& l : libros) {
            cout << "ID: " << l.id
                 << " | Título: " << l.titulo
                 << " | ISBN: " << l.isbn
                 << " | Año: " << l.ano
                 << " | Estado: " << (l.disponible ? "Disponible" : "PRESTADO")
                 << endl;
        }
    }

 
    void actualizarLibro() {
        int id_buscar;
        cout << "\n--- Actualizar Libro ---\n";
        cout << "Ingrese el ID del libro a actualizar: ";
        if (!(cin >> id_buscar)) {
             cout << "Error: Entrada inválida. Debe ser un número." << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return;
        }
        cin.ignore();

        Libro* l = buscarLibroPorId(id_buscar);

        if (l) {
            cout << "Libro encontrado: " << l->titulo << ". Nuevo Título (actual: " << l->titulo << "): ";
            string nuevo_titulo;
            getline(cin, nuevo_titulo);
            if (!nuevo_titulo.empty()) {
                l->titulo = nuevo_titulo;
            }
            
            cout << "Nuevo ISBN (actual: " << l->isbn << "): ";
            string nuevo_isbn;
            getline(cin, nuevo_isbn);
            if (!nuevo_isbn.empty()) {
                l->isbn = nuevo_isbn;
            }
            
            guardarLibros();
            cout << "\n¡Libro actualizado y guardado con éxito!\n";
        } else {
            cout << "Error: Libro con ID " << id_buscar << " no encontrado.\n";
        }
    }

    void eliminarLibro() {
        int id_eliminar;
        cout << "\n--- Eliminar Libro ---\n";
        cout << "Ingrese el ID del libro a eliminar: ";
        if (!(cin >> id_eliminar)) {
             cout << "Error: Entrada inválida. Debe ser un número." << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return;
        }
        
        auto it = remove_if(libros.begin(), libros.end(), 
            [id_eliminar](const Libro& l) {
                return l.id == id_eliminar;
            });

        if (it != libros.end()) {
            libros.erase(it, libros.end());
            guardarLibros();
            cout << "\n¡Libro con ID " << id_eliminar << " eliminado y guardado con éxito!\n";
        } else {
            cout << "Error: Libro con ID " << id_eliminar << " no encontrado.\n";
        }
    }

    void prestarLibro() {
        int id_libro, id_estudiante;
        cout << "\n--- Prestar Libro ---\n";
        
        cout << "ID del Libro a prestar: ";
        if (!(cin >> id_libro)) {
             cout << "Error: Entrada inválida. Debe ser un número." << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return;
        }

        Libro* libro_ptr = buscarLibroPorId(id_libro);

        if (!libro_ptr) {
            cout << "Error: Libro con ID " << id_libro << " no encontrado.\n";
            return;
        }

        if (!libro_ptr->disponible) {
            cout << "Error: El libro \"" << libro_ptr->titulo << "\" ya está prestado.\n";
            return;
        }
        
        cout << "ID del Estudiante: ";
        if (!(cin >> id_estudiante)) {
             cout << "Error: Entrada inválida. Debe ser un número." << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return;
        }
        
        libro_ptr->disponible = false;
        guardarLibros(); 
        cout << "\n¡Préstamo exitoso! El libro \"" << libro_ptr->titulo << "\" ahora está PRESTADO por el estudiante " << id_estudiante << ".\n";
    }

    void devolverLibro() {
        int id_libro;
        cout << "\n--- Devolver Libro ---\n";
        
        cout << "ID del Libro a devolver: ";
        if (!(cin >> id_libro)) {
             cout << "Error: Entrada inválida. Debe ser un número." << endl;
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             return;
        }

        Libro* libro_ptr = buscarLibroPorId(id_libro);

        if (!libro_ptr) {
            cout << "Error: Libro con ID " << id_libro << " no encontrado.\n";
            return;
        }
        
        if (libro_ptr->disponible) {
            cout << "Error: El libro \"" << libro_ptr->titulo << "\" ya estaba disponible (no estaba prestado).\n";
            return;
        }
        
        libro_ptr->disponible = true;
        guardarLibros(); 
        cout << "\n¡Devolución exitosa! El libro \"" << libro_ptr->titulo << "\" ahora está DISPONIBLE.\n";
    }

    void inicializar() {
        cargarLibros();
    }
};


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