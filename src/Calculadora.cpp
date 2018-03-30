//
// Created by dylan on 30 mar 2018.
//
#include "Calculadora.h"

Calculadora::Calculadora(Programa programa) {
    _programa = programa;
}

void Calculadora::asignarVariable(Id idVariable, int valor) {
    for (int i = 0; i < _variables.size(); ++i) {
        if (_variables[i].nombre == idVariable) {
            _variables[i].valor = valor;
            return;
        }
    }
    Variable v;
    v.nombre = idVariable;
    v.valor = valor;
    _variables.push_back(v);
}

int Calculadora::valorVariable(Id idVariable) const {
    for (int i = 0; i < _variables.size(); ++i) {
        if (_variables[i].nombre == idVariable) {
            return _variables[i].valor;
        }
    }
    return 0;
}

void Calculadora::Pila::push(int e) {
    _pila.push_back(e);
}

int Calculadora::Pila::pop() {
    if (_pila.size() > 0) {
        int e = _pila[_pila.size() - 1];
        _pila.pop_back();
        return e;
    } else {
        return 0;
    }
}

void Calculadora::ejecutar(Id idRutina) {
    Pila pila;
    Id rutina_actual = idRutina;
    int i = 0;
    while(_programa.esRutinaExistente(rutina_actual) && i < _programa.longitud(rutina_actual)) {
        Instruccion instr = _programa.instruccion(idRutina, i);
        switch (instr.operacion()) {
            case PUSH:
                pila.push(instr.valor());
                break;
            case ADD:
                pila.push(pila.pop() + pila.pop());
                break;
            case SUB:
                int first = pila.pop();
                int second = pila.pop();
                pila.push(second - first); // El primer valor de la pila es el substraendo
                break;
            case MUL:
                pila.push(pila.pop() * pila.pop());
                break;
            case WRITE:
                asignarVariable(instr.nombre(), pila.pop());
                break;
            case READ:
                pila.push(valorVariable(instr.nombre()));
                break;
            case JUMP:
                rutina_actual = instr.nombre();
                i = 0;
                break;
            case JUMPZ:
                if (pila.pop() == 0) {
                    rutina_actual = instr.nombre();
                    i = 0;
                }
                break;
            default:
                break;
        }
        i++;
    }
}