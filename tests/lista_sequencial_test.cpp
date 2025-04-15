#include <catch2/catch_all.hpp>
#include "lista_sequencial.hpp"
#include <iostream>

TEST_CASE("It should possible to append items to the list", "[ListaSequencial::append]")
{
    auto lista = Listas::ListaSequencial<int>(5);
    
    REQUIRE(lista.capacity() == 5);
    lista.append(12);
    lista.append(2);
    lista.append(5);
    lista.append(7);
    lista.append(8);

    REQUIRE(lista.size() == 5);
    REQUIRE(1==1);
}

TEST_CASE("It should possible to insert items to the list in any valid position", "[ListaSequencial::insert]")
{
    auto lista = Listas::ListaSequencial<int>(5);
    
    lista.append(12);
    lista.append(2);
    lista.append(5);
    lista.append(7);
    lista.append(8);

    lista.insert(2, 100);

    REQUIRE(lista.size() == 6);
}

TEST_CASE("It should possible to remove items from the list", "[ListaSequencial::pop, ListaSequencial::remove]")
{
    auto lista = Listas::ListaSequencial<int>(5);
    
    lista.append(12);
    lista.append(2);
    lista.append(5);
    lista.append(7);
    lista.append(8);

    auto ultimo_item = lista.pop();
    REQUIRE(ultimo_item.has_value());
    REQUIRE(ultimo_item.value() == 8);
    REQUIRE(lista.size() == 4);

    auto item_removido = lista.remove(1);
    REQUIRE(item_removido.has_value());
    REQUIRE(item_removido.value() == 2);
    REQUIRE(lista.size() == 3);
}


TEST_CASE("It should possible to insert items to the list sorted in ascending order", "[ListaSequencial::addsorted]")
{
    auto lista = Listas::ListaSequencial<int>(5);
    
    lista.append(12);
    lista.append(2);
    lista.append(5);
    lista.append(7);
    lista.append(8);

    lista.addsorted(99);
    lista.addsorted(101);

    REQUIRE(lista.find(101) == 6);
    REQUIRE(lista.find(99) == 5);
    REQUIRE(lista.size() == 7);
}

TEST_CASE("It should print list as a JSON array", "[ListaSequencial::print]")
{
    auto lista = Listas::ListaSequencial<int>();

    lista.addsorted(10);
    lista.addsorted(20);
    lista.addsorted(1);
    lista.addsorted(0);
    lista.addsorted(49);
    lista.addsorted(-255);
    lista.addsorted(294);
    lista.addsorted(128);

    std::stringstream buffer;
    auto cout_buffer = std::cout.rdbuf(buffer.rdbuf());

    lista.print();
    REQUIRE(buffer.str() == "[-255, 0, 1, 10, 20, 49, 128, 294]");

    std::cout.rdbuf(cout_buffer);
}
