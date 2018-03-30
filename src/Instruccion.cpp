//
// Created by dylan on 30 mar 2018.
//

#include "Instruccion.h"

Instruccion::Instruccion(Operacion operacion) {
    // Pre: operacion = ADD, SUB o MUL
    _operacion = operacion;
}

Instruccion::Instruccion(Operacion operacion, Id nombre) {
    // Pre: operacion = READ, WRITE, JUMP o JUMPZ
    _operacion = operacion;
    _nombre = nombre;
}

Instruccion::Instruccion(Operacion operacion, int valor) {
    // Pre: operacion = PUSH
    _operacion = operacion;
    _valor = valor;
}

Operacion Instruccion::operacion() const {
    return _operacion;
}

int Instruccion::valor() const {
    return _valor;
}

Id Instruccion::nombre() const {
    return _nombre;
}