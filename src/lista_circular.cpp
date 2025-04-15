#include "lista_circular.hpp"

namespace Listas
{

// NóListaCircular
template<typename T>
T& NóListaCircular<T>::element()
{
}
template<typename T>
T NóListaCircular<T>::takeelement()
{
}

template<typename T>
bool NóListaCircular<T>::hasnext() const
{
}

template<typename T>
bool NóListaCircular<T>::hasprevious() const
{
}

template<typename T>
NóListaCircular<T>* NóListaCircular<T>::getnext()
{
}

template<typename T>
NóListaCircular<T>* NóListaCircular<T>::getprevious()
{
}

template<typename T>
void NóListaCircular<T>::setprevious(NóListaCircular<T>* node)
{
}

template<typename T>
void NóListaCircular<T>::setnext(NóListaCircular<T>* node)
{
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
}

template<typename T>
size_t ListaCircular<T>::size() const
{
}

}
