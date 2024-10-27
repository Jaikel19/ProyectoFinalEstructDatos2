#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>

class Artista {
public:
    std::string cedula;
    std::string apellido;
    std::string nombre;
    std::string telefono;
    std::string email;
    std::string provincia;
    std::string canton;
    std::string barrio;

    Artista() = default;
    Artista(std::string cedula, std::string apellido, std::string nombre, std::string telefono, 
            std::string email, std::string provincia, std::string canton, std::string barrio);

    void display() const;
};

#endif
