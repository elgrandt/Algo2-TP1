//
// Created by dylan on 30 mar 2018.
//
#include "Programa.h"

Programa::Programa() {

}

bool Programa::esRutinaExistente(Id idRutina) const {
    for (int i = 0; i < _rutinas.size(); i++) {
        if (_rutinas[i].id == idRutina) {
            return true;
        }
    }
    return false;
}

int Programa::longitud(Id idRutina) const {
    for (int i = 0; i < _rutinas.size(); i++) {
        if (_rutinas[i].id == idRutina) {
            return _rutinas[i].instrucciones.size();
        }
    }
}

Instruccion Programa::instruccion(Id idRutina, int i) const {
    for (int x = 0; x < _rutinas.size(); x++) {
        if (_rutinas[x].id == idRutina) {
            return _rutinas[x].instrucciones[i];
        }
    }
}

void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion) {
    if (esRutinaExistente(idRutina)) {
        for (int i = 0; i < _rutinas.size(); i++) {
            if (_rutinas[i].id == idRutina) {
                _rutinas[i].instrucciones.push_back(instruccion);
            }
        }
    } else {
        Rutina rutina;
        rutina.id = idRutina;
        rutina.instrucciones.push_back(instruccion);
        _rutinas.push_back(rutina);
    }
}