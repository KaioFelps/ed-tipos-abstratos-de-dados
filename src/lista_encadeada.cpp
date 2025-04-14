#include <cassert>
#include "lista_encadeada.hpp"

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
NóListaEncadeada<T>* ListaEncadeada<T>::_tail()
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
    if (offset >= this->size())
    {
        throw std::range_error("offset should be smaller than the size of the list.");
    }

    int skipped = 0;
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

    return -1;
}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::tail()
{

}

template<typename T>
requires std::equality_comparable<T>
T& ListaEncadeada<T>::head()
{

}

template<typename T>
requires std::equality_comparable<T>
T* ListaEncadeada<T>::get(size_t index)
{

}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::popfront()
{
    if (this->isempty()) {
        return std::nullopt;
    }

    auto* removed_el = this->head_;
    this->head_ = removed_el->getnext();

    auto element = std::make_optional(removed_el->takeelement());
    delete removed_el;

    return element;
}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::poplast()
{
    if (this->isempty()) {
        
    }
    
}

template<typename T>
requires std::equality_comparable<T>
std::optional<T> ListaEncadeada<T>::remove()
{

}

template<typename T>
requires std::equality_comparable<T>
size_t ListaEncadeada<T>::size() const
{
    
}

template<typename T>
requires std::equality_comparable<T>
bool ListaEncadeada<T>::isempty() const
{
    return this->head_ == nullptr;
}

template class ListaEncadeada<int>;
template class NóListaEncadeada<int>;
}
