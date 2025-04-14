#pragma once

#include <memory>
#include <optional>
#include <concepts>

namespace Listas
{

template<typename T>
requires std::equality_comparable<T>
class NóListaEncadeada
{
    private:
        T element_;
        NóListaEncadeada<T>* previous_;
        NóListaEncadeada<T>* next_;

    public:
        NóListaEncadeada(T element);
        ~NóListaEncadeada();

        T& element();
        T takeelement();
        bool ishead();
        bool hasnext();

        NóListaEncadeada<T>* getnext();
        NóListaEncadeada<T>* getprevious();

        void setnext(NóListaEncadeada<T>* element);
        void setprevious(NóListaEncadeada<T>* element);
};

template<typename T>
requires std::equality_comparable<T>
class ListaEncadeada
{
    private:
        NóListaEncadeada<T>* head_;
        NóListaEncadeada<T>* _tail();

    public:
        ListaEncadeada();
        ~ListaEncadeada();

        T& pushfront(T element);
        T& pushback(T element);
        T& insert(T element, size_t offset);

        T& tail();
        T& head();
        T* get(size_t index);
        size_t getpos(const T& element) const;

        std::optional<T> popfront();
        std::optional<T> poplast();
        std::optional<T> remove();

        size_t size() const;
        bool isempty() const;

        void print() const;
};

}