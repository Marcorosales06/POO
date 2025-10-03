#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <iostream>
#include <vector>
#include <string>
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

    BibliotecaDB() {}

    void guardarLibros() const;
    void cargarLibros();
    void inicializar();
    Libro* buscarLibroPorId(int id);
    void agregarLibro();
    void listarLibros() const;
    void actualizarLibro();
    void eliminarLibro();
    void prestarLibro();
    void devolverLibro();

private:
    int obtenerIdValido(const string& mensaje, bool verificarDuplicado = false);
};

#endif 