#include "Artista.h"
#include <iostream>

Artista::Artista(std::string cedula, std::string apellido, std::string nombre,
    std::string telefono, std::string email, std::string provincia,
    std::string canton, std::string barrio)
    : cedula(cedula), apellido(apellido), nombre(nombre), telefono(telefono),
    email(email), provincia(provincia), canton(canton), barrio(barrio) {}

void Artista::display() const {
    std::cout << "Cedula: " << cedula << ", Nombre: " << nombre << " " << apellido
        << ", Telefono: " << telefono << ", Email: " << email
        << ", Provincia: " << provincia << ", Canton: " << canton
        << ", Barrio: " << barrio << std::endl;
}
