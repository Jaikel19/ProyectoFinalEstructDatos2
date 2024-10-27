#ifndef NODOAVL_H
#define NODOAVL_H

#include "Artista.h"

class NodoAVL {
public:
    Artista data;
    int height;
    NodoAVL* left;
    NodoAVL* right;

    NodoAVL(Artista artista);
};

#endif
