#include <catch2/catch_all.hpp> 
#include "lista_encadeada.hpp"

TEST_CASE("It should find the correct position of a node by its value", "[ListaEncadeada::getpos]") {
    auto* lista = new Listas::ListaEncadeada<int>();

    lista->pushback(20);
    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);


    REQUIRE(lista->getpos(20) == 0);
    REQUIRE(lista->getpos(30) == 1);
    REQUIRE(lista->getpos(2) == 2);
    REQUIRE(lista->getpos(493) == 3);
    REQUIRE(lista->getpos(770) == 4);
}