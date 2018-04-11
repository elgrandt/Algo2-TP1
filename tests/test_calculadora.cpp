#include "gtest/gtest.h"


#include "../src/Calculadora.h"

TEST(test_calculadora, Asignacion_variable){
    Programa p;
    Calculadora c(p);
    EXPECT_EQ(c.valorVariable("x"),0);
    c.asignarVariable("x",7);
    EXPECT_EQ(c.valorVariable("x"),7);
    c.asignarVariable("y", 38);
    EXPECT_EQ(c.valorVariable("y"),38);
}
TEST(test_Calculadora, Ejecutar_WRITE){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,10));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    p.agregarInstruccion("A",Instruccion(WRITE,"y"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),10);
    EXPECT_EQ(c.valorVariable("y"),0);
}
//Testeamos que WRITE escribe el valor de arriba de la variable indicada, y ademas que borra el ultimo valor de la pila.

TEST(test_Calculadora, Ejecutar_PUSH){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,200));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),200);
}

TEST(test_Calculadora, Ejecutar_ADD){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,1));
    p.agregarInstruccion("A",Instruccion(PUSH,2));
    p.agregarInstruccion("A",Instruccion(ADD));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),3);
}

TEST(test_Calculadora, Ejecutar_SUB){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,100));
    p.agregarInstruccion("A",Instruccion(PUSH,15));
    p.agregarInstruccion("A",Instruccion(SUB));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),85);
}

TEST(test_Calculadora, Ejecutar_MUL){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,7));
    p.agregarInstruccion("A",Instruccion(PUSH,11));
    p.agregarInstruccion("A",Instruccion(MUL));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),77);
}

TEST(test_Calculadora, Ejecutar_READ){
    Programa p;
    p.agregarInstruccion("A",Instruccion(READ,"x"));
    p.agregarInstruccion("A",Instruccion(READ,"y"));
    p.agregarInstruccion("A",Instruccion(ADD));
    p.agregarInstruccion("A",Instruccion(WRITE,"z"));
    Calculadora c(p);
    c.asignarVariable("x",30);
    c.asignarVariable("y",40);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("z"),70);
}




TEST(test_Calculadora, EjecutarConVariablesPrevias){
    Programa p;
    p.agregarInstruccion("A",Instruccion(READ,"x"));
    p.agregarInstruccion("A",Instruccion(PUSH,2));
    p.agregarInstruccion("A",Instruccion(MUL));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    Calculadora c(p);
    c.asignarVariable("x",100);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),200);
}

TEST(test_Calculadora, JUMP){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,10));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    p.agregarInstruccion("A",Instruccion(JUMP,"B"));
    p.agregarInstruccion("B",Instruccion(READ,"x"));
    p.agregarInstruccion("B",Instruccion(PUSH,5));
    p.agregarInstruccion("B",Instruccion(MUL));
    p.agregarInstruccion("B",Instruccion(WRITE,"y"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("y"),50);
    EXPECT_EQ(c.valorVariable("x"),10);
}

TEST(test_Calculadora, JUMPZ_SALTA){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,2));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    p.agregarInstruccion("A",Instruccion(JUMPZ,"B"));
    p.agregarInstruccion("B",Instruccion(READ,"x"));
    p.agregarInstruccion("B",Instruccion(PUSH,3));
    p.agregarInstruccion("B",Instruccion(MUL));
    p.agregarInstruccion("B",Instruccion(WRITE,"y"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("y"),6);
    EXPECT_EQ(c.valorVariable("x"),2);
}

TEST(test_Calculadora, JUMPZ_NO_SALTA){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,10));
    p.agregarInstruccion("A",Instruccion(JUMPZ,"B"));
    p.agregarInstruccion("B",Instruccion(PUSH,5));
    p.agregarInstruccion("B",Instruccion(MUL));
    p.agregarInstruccion("B",Instruccion(WRITE,"y"));
    Calculadora c(p);
    c.asignarVariable("y",33);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("y"),33);
}

TEST(test_Calculadora, JUMPZ_SACA_EL_TOPE){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,10));
    p.agregarInstruccion("A",Instruccion(PUSH,11));
    p.agregarInstruccion("A",Instruccion(JUMPZ,"B"));
    p.agregarInstruccion("A",Instruccion(WRITE,"y"));
    Calculadora c(p);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("y"),10);
}

TEST(test_Calculadora, Ejecucion_Instruccion_Vacia){
    Programa p;
    p.agregarInstruccion("A",Instruccion(PUSH,1));
    p.agregarInstruccion("A",Instruccion(WRITE, "x"));
    Calculadora c(p);
    c.asignarVariable("x",2);
    c.ejecutar("B");
    EXPECT_EQ(c.valorVariable("x"),2);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"),1);
}

TEST(test_Calculadora, GENERAL){
    Programa p;
    p.agregarInstruccion("A",Instruccion(READ,"a"));
    p.agregarInstruccion("A",Instruccion(PUSH,2));
    p.agregarInstruccion("A",Instruccion(ADD));
    p.agregarInstruccion("A",Instruccion(WRITE,"x"));
    p.agregarInstruccion("A",Instruccion(PUSH,6));
    p.agregarInstruccion("A",Instruccion(JUMP, "B"));
    p.agregarInstruccion("B",Instruccion(READ,"b"));
    p.agregarInstruccion("B",Instruccion(MUL));
    p.agregarInstruccion("B",Instruccion(WRITE, "y"));
    p.agregarInstruccion("B",Instruccion(JUMPZ, "C"));
    p.agregarInstruccion("C",Instruccion(READ,"c"));
    p.agregarInstruccion("C",Instruccion(JUMPZ,"D"));
    p.agregarInstruccion("C",Instruccion(PUSH,400));
    p.agregarInstruccion("C",Instruccion(READ, "c"));
    p.agregarInstruccion("C",Instruccion(SUB));
    p.agregarInstruccion("C",Instruccion(WRITE, "z"));
    p.agregarInstruccion("D",Instruccion(WRITE, "x"));
    p.agregarInstruccion("D",Instruccion(WRITE, "y"));
    p.agregarInstruccion("D",Instruccion(WRITE, "z"));

    Calculadora c(p);
    c.asignarVariable("a",1);
    c.asignarVariable("b",654);
    c.asignarVariable("c",34);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("x"), 3);
    EXPECT_EQ(c.valorVariable("y"), 3924);
    EXPECT_EQ(c.valorVariable("z"), 366);
}

TEST(test_Calculadora, FIBONACCI){
    Programa p;
    p.agregarInstruccion("A",Instruccion(READ,"x0"));
    p.agregarInstruccion("A",Instruccion(READ,"x1"));
    p.agregarInstruccion("A",Instruccion(ADD));
    p.agregarInstruccion("A",Instruccion(READ,"x1"));
    p.agregarInstruccion("A",Instruccion(WRITE,"x0"));
    p.agregarInstruccion("A",Instruccion(WRITE, "x1"));
    p.agregarInstruccion("A",Instruccion(READ,"n"));
    p.agregarInstruccion("A",Instruccion(PUSH, 1));
    p.agregarInstruccion("A",Instruccion(SUB));
    p.agregarInstruccion("A",Instruccion(WRITE, "n"));
    p.agregarInstruccion("A",Instruccion(READ,"n"));
    p.agregarInstruccion("A",Instruccion(READ,"x1"));
    p.agregarInstruccion("A",Instruccion(WRITE,"result"));
    p.agregarInstruccion("A",Instruccion(JUMPZ, "FIN"));
    p.agregarInstruccion("A",Instruccion(JUMP, "A"));

    Calculadora c(p);
    c.asignarVariable("x0",0);
    c.asignarVariable("x1",1);
    c.asignarVariable("n",22);
    c.ejecutar("A");
    EXPECT_EQ(c.valorVariable("result"), 28657);
}
/*Recursion de Fibonacci creada con la calculadora y testeada en el 22-esimo termino de la sucesion. Se puede cambiar por cualquiera
no demasiado grande por un tema de eficiencia.
 */