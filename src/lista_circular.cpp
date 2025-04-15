#include "lista_circular.hpp"

namespace Listas
{

// NóListaCircular
template<typename T>
T& NóListaCircular<T>::element()
{
    return this->element_;
}

template<typename T>
T NóListaCircular<T>::takeelement()
{
    auto element = std::move(this->element_);
    this->element_ = T{};
    return element;
}

template<typename T>
bool NóListaCircular<T>::hasnext() const
{
    return this->next_ != nullptr;
}

template<typename T>
bool NóListaCircular<T>::hasprevious() const
{
    return this->previous_ != nullptr;
}

template<typename T>
NóListaCircular<T>* NóListaCircular<T>::getnext()
{
    return this->next_;
}

template<typename T>
NóListaCircular<T>* NóListaCircular<T>::getprevious()
{
    return this->previous_;
}

template<typename T>
void NóListaCircular<T>::setprevious(NóListaCircular<T>* node)
{
    this->previous_ = node;
}

template<typename T>
void NóListaCircular<T>::setnext(NóListaCircular<T>* node)
{
    this->next_ = node;
}

// ListaCircular

template<typename T>
T& ListaCircular<T>::pushfront(T element)
{
}

template<typename T>
T& ListaCircular<T>::pushback(T element)
{
}

template<typename T>
T& ListaCircular<T>::insert(size_t index, T element)
{
}

template<typename T>
T& ListaCircular<T>::addsorted(T element) requires std::totally_ordered<T>
{
}

template<typename T>
std::optional<T> ListaCircular<T>::popfront()
{
}

template<typename T>
std::optional<T> ListaCircular<T>::poplast()
{
}

template<typename T>
std::optional<T> ListaCircular<T>::remove(size_t index)
{
}

template<typename T>
size_t ListaCircular<T>::find(T& element) requires std::equality_comparable<T>
{
}

template<typename T>
bool ListaCircular<T>::isempty() const
{
    return !!this->head_;
}

template<typename T>
size_t ListaCircular<T>::size() const
{
    return this->size_;
}

}
