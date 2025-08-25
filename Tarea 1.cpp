#include <iostream>
#include <string>
#include <vector>

class Libro {
public:
    std::string titulo;
    std::string autor;
    int yearPublicacion;
    bool estaDisponible;

  
    Libro(std::string t, std::string a, int y)
        : titulo(std::move(t)), autor(std::move(a)), yearPublicacion(y), estaDisponible(true) {}

   
    Libro() : titulo(""), autor(""), yearPublicacion(0), estaDisponible(true) {}

    void mostrarDetalles() const {
        std::cout << "_____________________" << std::endl;
        std::cout << "Titulo: " << titulo << std::endl;
        std::cout << "Autor: " << autor << std::endl;
        std::cout << "Year: " << yearPublicacion << std::endl;
    }

    void mostrarDetallesCompletos() const {
        mostrarDetalles();
        std::cout << "Disponible para prestamo: "
                  << (estaDisponible ? "Si" : "No") << std::endl;
    }
};

class Biblioteca {
public:
    std::vector<Libro> libros;

    void agregarLibro(const Libro& nuevoLibro) {
        libros.push_back(nuevoLibro);
    }

    void mostrarInventario() const {
        std::cout << "Inventario de libros:\n";
        for (const auto& libro : libros) {
            libro.mostrarDetallesCompletos();
        }
    }

    Libro* buscarLibro(const std::string& tituloPrestamo) {
        for (auto& libro : libros) {
            if (libro.titulo == tituloPrestamo) {
                return &libro;
            }
        }
        return nullptr;
    }

    void prestarLibro(const std::string& tituloPrestamo) {
        Libro* libro = buscarLibro(tituloPrestamo);
        if (libro) {
            if (libro->estaDisponible) {
                libro->estaDisponible = false;
                std::cout << "Libro '" << libro->titulo << "' prestado.\n";
            } else {
                std::cout << "El libro ya está prestado.\n";
            }
        } else {
            std::cout << "Libro no encontrado.\n";
        }
    }

    void devolverLibro(const std::string& tituloDevolucion) {
        Libro* libro = buscarLibro(tituloDevolucion);
        if (libro) {
            if (!libro->estaDisponible) {
                libro->estaDisponible = true;
                std::cout << "Libro '" << libro->titulo << "' devuelto.\n";
            } else {
                std::cout << "El libro no estaba prestado.\n";
            }
        } else {
            std::cout << "Libro no encontrado.\n";
        }
    }
};

int main() {
    Biblioteca miBiblioteca;

  
    Libro libro1{"El viejo y el mar", "Ernest Hemingway", 1967};
    Libro libro2{"Dune", "Frank Herbert", 1965};
    Libro libro3{"El hobbit", "J.R.R. Tolkien", 1937};
    Libro libro4{"Pride and Prejudice", "Jane Austen", 1813};
    Libro libro5{"The summer I turned pretty", "Jenny Han", 2009};
    Libro libro6{"Gone Girl", "Gillian Flynn", 2012};

    miBiblioteca.agregarLibro(libro1);
    miBiblioteca.agregarLibro(libro2);
    miBiblioteca.agregarLibro(libro3);
    miBiblioteca.agregarLibro(libro4);
    miBiblioteca.agregarLibro(libro5);
    miBiblioteca.agregarLibro(libro6);

    std::cout << "Inventario inicial:\n";
    miBiblioteca.mostrarInventario();

    std::cout << "\nPréstamo de 'Dune':\n";
    miBiblioteca.prestarLibro("Dune");

    std::cout << "\nInventario actualizado:\n";
    miBiblioteca.mostrarInventario();

    std::cout << "\nDevolviendo 'Dune':\n";
    miBiblioteca.devolverLibro("Dune");

    std::cout << "\nInventario final:\n";
    miBiblioteca.mostrarInventario();

    return 0;
}

