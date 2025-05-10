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

TEST_CASE("It should be able to instantiate a sequential list from an C array", "[ListaSequencial::from_array, ListaSequencial::from_array_on_stack]")
{
    using Listas::ListaSequencial;
    int array[] = { 10, 20, 1, 0, 49, -255, 294, 129 };

    auto stack_list = ListaSequencial<int>::from_array_on_stack(array, 8);
    auto stack_list_directly_instantiated = Listas::ListaSequencial<int>::from_array_on_stack({ 10, 20, 1, 0, 49, -255, 294, 129 });

    auto heap_list = Listas::ListaSequencial<int>::from_array(array, 8);
    auto heap_list_directly_instantiated = Listas::ListaSequencial<int>::from_array({ 10, 20, 1, 0, 49, -255, 294, 129 });

    for (size_t i = 0; i < 8; i++)
    {
        REQUIRE(array[i] == *stack_list.get(i));
        REQUIRE(array[i] == *stack_list_directly_instantiated.get(i));

        REQUIRE(array[i] == *heap_list->get(i));
        REQUIRE(array[i] == *heap_list_directly_instantiated->get(i));
    }
}

TEST_CASE("It should be able to clone a sequential list", "[ListaSequencial::clone, ListaSequencial::clone_on_stack]")
{
    auto original = Listas::ListaSequencial<int>::from_array({ 10, 20, 1, 0, 49, -255, 294, 129 });

    auto clone = original->clone();
    auto clone_on_stack = original->clone_on_stack();

    for (size_t i = 0; i < original->size(); i++)
    {
        REQUIRE(*original->get(i) == *clone->get(i));
        REQUIRE(*original->get(i) == *clone_on_stack.get(i));
    }
}

TEST_CASE("It should reset a list if required to", "[ListaSequencial::clear]")
{
    auto original = Listas::ListaSequencial<int>::from_array({ 10, 20, 1, 0, 49, -255, 294, 129 });

    REQUIRE(original->size() == 8);
    REQUIRE(original->capacity() == 8);

    original->clear();

    REQUIRE(original->size() == 0);
    REQUIRE(original->get(0) == nullptr);
    REQUIRE(original->capacity() == DEFAULT_CAPACITY);
    REQUIRE(!original->pop().has_value());
}