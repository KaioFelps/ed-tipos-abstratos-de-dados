#include "include/lista_sequencial.hpp"
#include <iostream>

int main()
{
    auto lista = new ListaSequencial<int>(5);
    std::cout << "Tamanho da lista: " << lista->size() << "; Capacidade: " << lista->capacity() << "\n";
    
    lista->append(12);
    lista->append(2);
    lista->append(5);
    lista->append(7);
    lista->append(8);
    
    std::cout << "Tamanho da lista: " << lista->size() << "; Capacidade: " << lista->capacity() << "\n";

    lista->append(10);

    std::cout << "Noo tamanho da lista: " << lista->size() << "; Capacidade: " << lista->capacity() << "\n";

    lista->print();
    lista->insert(2, 100);
    lista->print();

    auto ultimo_item = lista->pop();
    std::cout << "Item removido: ";
    if (ultimo_item.has_value()) { std::cout << ultimo_item.value(); } else { std::cout << "null"; }
    std::cout << "\n";

    lista->print();

    auto item_removido = lista->remove(1);
    std::cout << "Item removido do índex 1: ";
    if (item_removido.has_value()) { std::cout << item_removido.value(); } else { std::cout << "null"; }
    std::cout << "\n";

    lista->print();

    lista->addsorted(99);
    lista->addsorted(101);
    lista->print();

    auto indice_de_101 = lista->find(101);
    std::cout << "Índice do item 101: " << indice_de_101 << "\n";


    auto item_no_indice_6 = lista->get(6);
    std::cout << "Item no índice 6: " << *item_no_indice_6 << "\n";


    delete lista;
    return 0;
}