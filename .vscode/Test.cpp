#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "/home/robert1/proyectos/.vscode/Matriz.h"

TEST_CASE("Multiplicación correcta de matrices", "[matriz]") {
    Matriz A(2, 2);
    Matriz B(2, 2);

    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);

    B.set(0, 0, 5); B.set(0, 1, 6);
    B.set(1, 0, 7); B.set(1, 1, 8);

    Matriz C = A * B;

    REQUIRE(C.getFilas() == 2);
    REQUIRE(C.getColumnas() == 2);
    REQUIRE(C.get(0,0) == Approx(19.0).epsilon(0.0001));
    REQUIRE(C.get(0,1) == Approx(22.0).epsilon(0.0001));
    REQUIRE(C.get(1,0) == Approx(43.0).epsilon(0.0001));
    REQUIRE(C.get(1,1) == Approx(50.0).epsilon(0.0001));
}

TEST_CASE("Lanzar excepción si dimensiones son negativas", "[matriz]") {
    REQUIRE_THROWS_AS(Matriz(-1, 2), std::invalid_argument);
    REQUIRE_THROWS_AS(Matriz(2, 0), std::invalid_argument);
}

TEST_CASE("Error al multiplicar dimensiones incompatibles", "[matriz]") {
    Matriz A(2, 3);
    Matriz B(2, 2);
    REQUIRE_THROWS_AS(A * B, std::invalid_argument);
}