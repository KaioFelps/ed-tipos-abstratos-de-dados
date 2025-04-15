#include <catch2/catch_all.hpp> 
#include "lista_encadeada.hpp"
#include <iostream>

TEST_CASE("It should find the correct position of a node by its value", "[ListaEncadeada::getpos]")
{
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

    REQUIRE(lista->getpos(999) == Listas::not_found_pos);
}

TEST_CASE("It should tell the correct size of the list", "[ListaEncadeada::size]")
{
    auto* lista = new Listas::ListaEncadeada<int>();

    INFO("`list` should have size 0");
    REQUIRE(lista->size() == 0);

    lista->pushback(20);
    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);

    INFO("`list` should have size 5");
    REQUIRE(lista->size() == 5);

    lista->poplast();
    INFO("`list` should have size 4");
    REQUIRE(lista->size() == 4);
}

TEST_CASE("It should allow to remove elements from the list",
          "[ListaEncadeada::remove, ListaEncadeada::popfront, ListaEncadeada::poplast]")
{
    auto* lista = new Listas::ListaEncadeada<int>();

    lista->pushback(20);
    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);
    
    REQUIRE(lista->size() == 5);

    INFO("Removing by index");
    auto removed_el = lista->remove(lista->getpos(2));
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 2);
    REQUIRE(lista->getpos(2) == Listas::not_found_pos);

    INFO("Removing first");
    removed_el = lista->popfront();
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 20);
    REQUIRE(lista->getpos(20) == (size_t) Listas::not_found_pos);

    INFO("Removing last");
    removed_el = lista->poplast();
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 770);
    REQUIRE(lista->getpos(770) == Listas::not_found_pos);

    REQUIRE(lista->size() == 2);
}

TEST_CASE("It should be possible to get an element by its index", "[ListaEncadeada::get]")
{
    auto* lista = new Listas::ListaEncadeada<int>();

    lista->pushback(20);
    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);

    SECTION("Get an element by its index")
    {
        REQUIRE(lista->get(3) != nullptr);
        REQUIRE(*lista->get(3) == 493);
    }

    SECTION("Get an element by an invalid index")
    {
        REQUIRE(lista->get(100) == nullptr);
        REQUIRE(lista->get(Listas::not_found_pos) == nullptr);
    }
}

TEST_CASE("It should find head and tail from an list", "[ListaEncadeada::head, ListaEncadeada::tail]")
{
    auto* lista = new Listas::ListaEncadeada<int>();

    REQUIRE_THROWS_AS(lista->head(), std::out_of_range);
    REQUIRE_THROWS_AS(lista->tail(), std::out_of_range);

    lista->pushback(20);

    REQUIRE(lista->head() == 20);
    REQUIRE(lista->head() == lista->tail());

    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);

    REQUIRE(lista->head() == 20);
    REQUIRE(lista->tail() == 770);
}

TEST_CASE("It should be able to print the content of a list as an JSON array", "[ListaEncadeada::print]")
{
    auto* lista = new Listas::ListaEncadeada<int>();

    lista->pushback(20);
    lista->pushback(30);
    lista->pushback(2);
    lista->pushback(493);
    lista->pushback(770);

    // muda o buffer no qual o `std::cout` escreve pra um string stream falso
    // para que possamos obter o que será impresso no `std::cout` pelo método `print`
    std::stringstream buffer;
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());

    lista->print();

    // mudamos o buffer do `std::cout` de volta para o que era antes, isto é, o padrão
    std::cout.rdbuf(old_cout);

    REQUIRE(buffer.str() == "[20, 30, 2, 493, 770]");
}
