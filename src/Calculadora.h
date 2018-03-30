//
// Created by dylan on 30 mar 2018.
//

#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H

#include <iostream>
#include <vector>
#include "Programa.h"
#include "Instruccion.h"
using namespace std;

class Calculadora {
public:
    // Construye una calculadora que tiene cargado el programa indicado.
    Calculadora(Programa programa);

    // Establece el valor de la variable indicada en la memoria de la calculadora.
    void asignarVariable(Id idVariable, int valor);

    // Ejecuta el programa hasta alcanzar alguna de las condiciones de finalización.
    // La ejecución comienza en la primera instrucción de la rutina especificada por el parámetro idRutina.
    // Observar que si idRutina no es una rutina existente en el programa, la ejecución finaliza de manera inmediata.
    void ejecutar(Id idRutina);

    // Devuelve que tiene la variable indicada en la memoria de la calculadora.
    // Si nunca se le dio valor a dicha variable, se asume que su valor por defecto es 0
    int valorVariable(Id idVariable) const;
private:
    struct Variable {
        Id nombre;
        int valor;
    };

    class Pila {
    public:
        void push(int e);
        int pop();
    private:
        vector<int> _pila;
    };

    vector<Variable> _variables;
    Programa _programa;
};

#endif //SOLUCION_CALCULADORA_H
