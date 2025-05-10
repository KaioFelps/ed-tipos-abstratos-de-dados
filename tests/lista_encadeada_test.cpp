#include <catch2/catch_all.hpp> 
#include "lista_encadeada.hpp"
#include <iostream>

TEST_CASE("It should find the correct position of a node by its value", "[ListaEncadeada::getpos]")
{
    auto lista = Listas::ListaEncadeada<int>();
    
    lista.pushback(20);
    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);

    REQUIRE(lista.getpos(20) == 0);
    REQUIRE(lista.getpos(30) == 1);
    REQUIRE(lista.getpos(2) == 2);
    REQUIRE(lista.getpos(493) == 3);
    REQUIRE(lista.getpos(770) == 4);

    REQUIRE(lista.getpos(999) == Listas::not_found_pos);
}

TEST_CASE("It should tell the correct size of the list", "[ListaEncadeada::size]")
{
    auto lista = Listas::ListaEncadeada<int>();

    INFO("`list` should have size 0");
    REQUIRE(lista.size() == 0);

    lista.pushback(20);
    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);

    INFO("`list` should have size 5");
    REQUIRE(lista.size() == 5);

    lista.poplast();
    INFO("`list` should have size 4");
    REQUIRE(lista.size() == 4);
}

TEST_CASE("It should allow to remove elements from the list",
          "[ListaEncadeada::remove, ListaEncadeada::popfront, ListaEncadeada::poplast]")
{
    auto lista = Listas::ListaEncadeada<int>();

    lista.pushback(20);
    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);
    
    REQUIRE(lista.size() == 5);

    INFO("Removing by index");
    auto removed_el = lista.remove(lista.getpos(2));
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 2);
    REQUIRE(lista.getpos(2) == Listas::not_found_pos);

    INFO("Removing first");
    removed_el = lista.popfront();
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 20);
    REQUIRE(lista.getpos(20) == (size_t) Listas::not_found_pos);

    INFO("Removing last");
    removed_el = lista.poplast();
    REQUIRE(removed_el.has_value());
    REQUIRE(removed_el.value() == 770);
    REQUIRE(lista.getpos(770) == Listas::not_found_pos);

    REQUIRE(lista.size() == 2);
}

TEST_CASE("It should be possible to get an element by its index", "[ListaEncadeada::get]")
{
    auto lista = Listas::ListaEncadeada<int>();

    lista.pushback(20);
    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);

    SECTION("Get an element by its index")
    {
        REQUIRE(lista.get(3) != nullptr);
        REQUIRE(*lista.get(3) == 493);
    }

    SECTION("Get an element by an invalid index")
    {
        REQUIRE(lista.get(100) == nullptr);
        REQUIRE(lista.get(Listas::not_found_pos) == nullptr);
    }
}

TEST_CASE("It should find head and tail from an list", "[ListaEncadeada::head, ListaEncadeada::tail]")
{
    auto lista = Listas::ListaEncadeada<int>();

    REQUIRE_THROWS_AS(lista.head(), std::out_of_range);
    REQUIRE_THROWS_AS(lista.tail(), std::out_of_range);

    lista.pushback(20);

    REQUIRE(lista.head() == 20);
    REQUIRE(lista.head() == lista.tail());

    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);

    REQUIRE(lista.head() == 20);
    REQUIRE(lista.tail() == 770);
}

TEST_CASE("It should be able to print the content of a list as an JSON array", "[ListaEncadeada::print]")
{
    auto lista = Listas::ListaEncadeada<int>();

    lista.pushback(20);
    lista.pushback(30);
    lista.pushback(2);
    lista.pushback(493);
    lista.pushback(770);

    // muda o buffer no qual o `std::cout` escreve pra um string stream falso
    // para que possamos obter o que será impresso no `std::cout` pelo método `print`
    std::stringstream buffer;
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());

    lista.print();

    // mudamos o buffer do `std::cout` de volta para o que era antes, isto é, o padrão
    std::cout.rdbuf(old_cout);

    REQUIRE(buffer.str() == "[20, 30, 2, 493, 770]");
}

TEST_CASE("It should print last item on output", "[ListaEncadeada::printlast]")
{
    SECTION("Non-empty list")
    {
        auto lista = Listas::ListaEncadeada<int>();

        lista.pushback(20);
        lista.pushback(30);
        lista.pushback(2);
        lista.pushback(400);
        
        std::stringstream fake_buffer;
        auto cout_buffer = std::cout.rdbuf(fake_buffer.rdbuf());

        lista.printlast();

        std::cout.rdbuf(cout_buffer);

        REQUIRE("400" == fake_buffer.str());
    }

    SECTION("Empty list")
    {
        auto lista = Listas::ListaEncadeada<int>();

        std::stringstream fake_buffer;
        auto cout_buffer = std::cout.rdbuf(fake_buffer.rdbuf());

        lista.printlast();

        std::cout.rdbuf(cout_buffer);

        REQUIRE("null" == fake_buffer.str());
    }
}

TEST_CASE("It should tell whether a list is not sorted", "[ListaEncadeada::issorted]")
{
    using namespace Listas;
    auto sorted_list = ListaEncadeada<int>();
    sorted_list.pushback(1);
    sorted_list.pushback(3);
    sorted_list.pushback(2);

    REQUIRE(!sorted_list.issorted());
}

TEST_CASE("It should tell whether a list is sorted", "[ListaEncadeada::issorted]")
{
    using namespace Listas;
    auto sorted_list = ListaEncadeada<int>();
    sorted_list.pushback(1);
    sorted_list.pushback(2);
    sorted_list.pushback(3);

    REQUIRE(sorted_list.issorted());
}

TEST_CASE("It should tell that a list is sorted if it has not enough elements for not to be sorted", "[ListaEncadeada::issorted]")
{
    using namespace Listas;
    auto sorted_list = ListaEncadeada<int>();

    REQUIRE(sorted_list.issorted());

    sorted_list.pushback(3);
    REQUIRE(sorted_list.issorted());
}

TEST_CASE("It should be able to insert element sorted by descending order", "[ListaEncadeada::insertsorted]")
{
    auto list = Listas::ListaEncadeada<int>();
    list.insertsorted(5);
    list.insertsorted(3);
    list.insertsorted(424);
    list.insertsorted(-400);
    list.insertsorted(0);
    
    REQUIRE(*list.get(0) == -400);
    REQUIRE(*list.get(1) == 0);
    REQUIRE(*list.get(2) == 3);
    REQUIRE(*list.get(3) == 5);
    REQUIRE(*list.get(4) == 424);
}

TEST_CASE("It should be able to make a deep copy of itself on the heap", "[ListaEncadeada::deepcopy]")
{
    auto list = Listas::ListaEncadeada<int>();
    list.insertsorted(5);
    list.insertsorted(3);
    list.insertsorted(424);
    list.insertsorted(-400);
    list.insertsorted(0);

    auto copy = list.deepcopy();

    REQUIRE(*list.get(0) == *copy->get(0));
    REQUIRE(*list.get(1) == *copy->get(1));
    REQUIRE(*list.get(2) == *copy->get(2));
    REQUIRE(*list.get(3) == *copy->get(3));
    REQUIRE(*list.get(4) == *copy->get(4));
}

TEST_CASE("It should be able to make a deep copy of itself on the stack", "[ListaEncadeada:stackdeepcopy]")
{
    auto list = Listas::ListaEncadeada<int>();
    list.insertsorted(5);
    list.insertsorted(3);
    list.insertsorted(424);
    list.insertsorted(-400);
    list.insertsorted(0);

    auto copy = list.stackdeepcopy();

    REQUIRE(*list.get(0) == *copy.get(0));
    REQUIRE(*list.get(1) == *copy.get(1));
    REQUIRE(*list.get(2) == *copy.get(2));
    REQUIRE(*list.get(3) == *copy.get(3));
    REQUIRE(*list.get(4) == *copy.get(4));
}

TEST_CASE("It should be able to concatenate a list into another", "[ListaEncadeada::concat]")
{
    using namespace Listas;

    auto list_a = ListaEncadeada<int>();
    list_a.insertsorted(5);
    list_a.insertsorted(3);
    list_a.insertsorted(424);
    list_a.insertsorted(-400);
    list_a.insertsorted(0);

    auto list_b = ListaEncadeada<int>();
    list_b.pushback(10);
    list_b.pushback(45);

    size_t list_b_size_before_concat = list_b.size();

    list_b.concat(list_a);

    REQUIRE(10 == *list_b.get(0));
    REQUIRE(45 == *list_b.get(1));

    for (size_t i = list_b_size_before_concat; i < list_b.size(); i++)
    {
        REQUIRE(*list_a.get(i - list_b_size_before_concat) == *list_b.get(i));
    }
}

TEST_CASE("It should be able to merge two lists into a new one stored in the heap", "[ListaEncadeada::merge]")
{
    using namespace Listas;

    auto list_a = ListaEncadeada<int>();
    list_a.insertsorted(5);
    list_a.insertsorted(3);
    list_a.insertsorted(424);
    list_a.insertsorted(-400);
    list_a.insertsorted(0);

    auto list_b = ListaEncadeada<int>();
    list_b.pushback(10);
    list_b.pushback(45);

    auto merge_on_heap = list_a.merge(list_b);

    REQUIRE(list_a.size() + list_b.size() == merge_on_heap->size());

    for (size_t i = 0; i < merge_on_heap->size(); i++)
    {
        if (i < list_a.size())
        {
            REQUIRE(*list_a.get(i) == *merge_on_heap->get(i));
            continue;
        }

        REQUIRE(*list_b.get(i - list_a.size()) == *merge_on_heap->get(i));
    }
}

TEST_CASE("It should be able to merge two lists into a new one stored in the stack", "[ListaEncadeada::stackmerge]")
{
    using namespace Listas;

    auto list_a = ListaEncadeada<int>();
    list_a.insertsorted(5);
    list_a.insertsorted(3);
    list_a.insertsorted(424);
    list_a.insertsorted(-400);
    list_a.insertsorted(0);

    auto list_b = ListaEncadeada<int>();
    list_b.pushback(10);
    list_b.pushback(45);

    auto merge_on_stack = list_a.stackmerge(list_b);

    REQUIRE(list_a.size() + list_b.size() == merge_on_stack.size());

    merge_on_stack.print();
    for (size_t i = 0; i < merge_on_stack.size(); i++)
    {
        if (i < list_a.size())
        {
            REQUIRE(*list_a.get(i) == *merge_on_stack.get(i));
            continue;
        }

        REQUIRE(*list_b.get(i - list_a.size()) == *merge_on_stack.get(i));
    }
}
