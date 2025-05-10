#include <cassert>
#include "lista_encadeada.hpp"
#include <iostream>

namespace Listas
{

template<typename T>
requires std::equality_comparable<T>
NóListaEncadeada<T>::NóListaEncadeada(T element)
{
    this->element_ = element;
    this->previous_ = nullptr;
    this->next_ = nullptr;
}

template<typename T>
requires std::equality_comparable<T>
NóListaEncadeada<T>::~NóListaEncadeada()
{

}

template<typename T>
requires std::equality_comparable<T>
T& NóListaEncadeada<T>::element()
{
    return this->element_;
}

template<typename T>
requires std::equality_comparable<T>
bool NóListaEncadeada<T>::ishead()
{
    return this->previous_ == nullptr;
}

template<typename T>
requires std::equality_comparable<T>
bool NóListaEncadeada<T>::hasnext()
{
    return this->next_ != nullptr;
}

template<typename T>
requires std::equality_comparable<T>
void NóListaEncadeada<T>::setnext(NóListaEncadeada<T>* element)
{
    this->next_ = element;
}

template<typename T>
requires std::equality_comparable<T>
void NóListaEncadeada<T>::setprevious(NóListaEncadeada<T>* element)
{
    this->previous_ = element;
}

template<typename T>
requires std::equality_comparable<T>
T NóListaEncadeada<T>::takeelement()
{
    T element = std::move(this->element_);
    this->element_ = T{};
    return element;
}

template<typename T>
requires std::equality_comparable<T>
NóListaEncadeada<T>* NóListaEncadeada<T>::getnext()
{
    return this->next_;
}


template<typename T>
requires std::equality_comparable<T>
NóListaEncadeada<T>* NóListaEncadeada<T>::getprevious()
{
    return this->previous_;
}

// ListaEncadeada ===========================================
        
template<typename T>
requires std::equality_comparable<T>
ListaEncadeada<T>::ListaEncadeada()
{
    this->head_ = nullptr;
}
template<typename T>
requires std::equality_comparable<T>
NóListaEncadeada<T>* ListaEncadeada<T>::_tail() const
{

    NóListaEncadeada<T>* node = this->head_;

    while (node->hasnext())
    {
        node = node->getnext();
    }

    return node;
}

template<typename T>
requires std::equality_comparable<T>
ListaEncadeada<T>::~ListaEncadeada()
{
    if (this->isempty()) return;
    
    auto* element = this->head_;
    while (element)
    {
        auto* next = element->getnext();
        delete element;
        element = next;
    }
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::pushfront(T _element)
{
    auto* new_element = new NóListaEncadeada(_element);

    if (this->isempty())
    {
        this->head_ = new_element;
        return new_element->element();
    }

    this->head_->setprevious(new_element);
    new_element->setnext(this->head_);
    this->head_ = new_element;

    return new_element->element();
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::pushback(T _element)
{
    auto* element = new NóListaEncadeada(_element);

    if (this->isempty())
    {
        this->head_ = element;
        return this->head_->element();
    }

    element->setprevious(this->_tail());
    auto* tail = this->_tail();

    assert(tail != nullptr && "since instance of ListaEncadeada is not empty, _tail method should not return a nullptr.");

    tail->setnext(element);
    return element->element();
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::insert(T element, size_t offset)
{
    if (offset < 0 || offset >= this->size())
    {
        throw std::out_of_range("offset should be smaller than the size of the list.");
    }

    size_t skipped = 0;
    NóListaEncadeada<T>* node = this->head_;

    while (skipped < offset && node != nullptr)
    {
        node = node->getnext();
        skipped++;
    }

    assert(node != nullptr && "node should not be null, since the size of the ListaEncadeada instance covers its position.");
    auto* new_element = new NóListaEncadeada(element);

    node->setprevious(new_element);
    new_element->setnext(node);

    return new_element->element();
}

template<typename T>
requires std::equality_comparable<T>
size_t ListaEncadeada<T>::getpos(const T& element) const
{
    NóListaEncadeada<T>* node = this->head_;
    auto counter = 0;

    while(node)
    {
        if (node->element() == element) return counter;
        node = node->getnext();    
        counter++;
    }

    return not_found_pos;
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::tail() const
{
    if (this->isempty()) throw std::out_of_range("tried to get tail from empty list.");
    return this->_tail()->element();
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::head()
{
    if (this->isempty()) throw std::out_of_range("tried to get head from empty list.");
    return this->head_->element();
}

template<typename T>
requires std::equality_comparable<T>
T* ListaEncadeada<T>::get(size_t index)
{
    if (index < 0 || index >= this->size()) return nullptr;
    if (index == 0) return &this->head_->element();

    size_t position = 1;
    NóListaEncadeada<T>* node = this->head_->getnext();
    
    while (node && position < index)
    {
        node = node->getnext();
        position++;
    }

    assert(position == index && "since `index` is inside of list bounds, nodes should have next nodes until the index is reached.");

    return &node->element();
}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::popfront()
{
    if (this->isempty()) {
        return std::nullopt;
    }

    auto* old_head = this->head_;

    this->head_ = old_head->getnext();
    this->head_->setprevious(nullptr);

    auto element = old_head->takeelement();
    delete old_head;
    return element;
}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::poplast()
{
    if (this->isempty()) {
        return std::nullopt;    
    }
    
    NóListaEncadeada<T>* tail = this->_tail();

    tail->getprevious()->setnext(nullptr);

    auto removed_element = tail->takeelement();

    delete tail;
    return removed_element;
}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::remove(size_t index)
{
    if (index < 0 || index >= this->size()) return std::nullopt;

    size_t position = 0;
    NóListaEncadeada<T>* node = this->head_;

    while(node && position < index)
    {
        node = node->getnext();
        position++;
    }

    assert(position == index && "since `index` is inside of list bounds, nodes should have next nodes until the index is reached.");

    // o node anterior à este, que está sendo removido, deve ter seu próximo node
    // como sendo o próximo node do node sendo removido, seja ele nulo ou um nó existente.
    node->getprevious()->setnext(node->getnext());

    // se houver um próximo node, este próximo node deve ter como seu node anterior o node anterior do nó que está sendo removido;
    // sem isso, o node subsequente apontaria o nó sendo removido como sendo seu antecessor.
    if (node->hasnext()) node->getnext()->setprevious(node->getprevious());

    auto removed_element = node->takeelement();
    delete node;

    return removed_element;
}

template<typename T>
requires std::equality_comparable<T>
size_t ListaEncadeada<T>::size() const
{
    auto count = 0;
    auto* node = this->head_;
    while (node)
    {
        node = node->getnext();
        count++;
    }

    return count;
}

template<typename T>
requires std::equality_comparable<T>
bool ListaEncadeada<T>::isempty() const
{
    return this->head_ == nullptr;
}

template<typename T>
requires std::equality_comparable<T>
void ListaEncadeada<T>::print() const
{
    if (this->isempty())
    {
        std::cout << "[]";
        return;
    }

    std::cout << "[";
    NóListaEncadeada<T>* node = this->head_;
    while (node)
    {
        std::cout << node->element();
        if (node->hasnext()) std::cout << ", ";

        node = node->getnext();
    }

    std::cout << "]";
}

template<typename T>
requires std::equality_comparable<T>
void ListaEncadeada<T>::printlast() const
{
    if (this->isempty())
    {
        std::cout << "null";
        return;
    }

    std::cout << this->tail();
}

template class ListaEncadeada<int>;
template class NóListaEncadeada<int>;
}
