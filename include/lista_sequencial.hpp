#pragma once

#include <optional>
#include <memory>
#include "listas_utils.hpp"

#define DEFAULT_CAPACITY 100
#define INCREASE_CAPACITY_BY 50

namespace Listas
{

template<typename T>
class ListaSequencial
{
    private:
        size_t size_;
        size_t capacity_;
        std::unique_ptr<T[]> list_;
        void resize();
        void mayberesize();

    public:
        ListaSequencial();
        ListaSequencial(size_t capacity);

        T* get(size_t index);
        
        T& append(T item);
        T& insert(size_t index, T item) noexcept(false);
        T& addsorted(T item) requires std::totally_ordered<T>;
        
        size_t find(T item) requires std::equality_comparable<T>;

        std::optional<T> pop();
        std::optional<T> remove(size_t index);
        
        size_t capacity() const;
        size_t size() const;

        bool isempty() const;
        bool isfull() const;

        void print() const;
};

}