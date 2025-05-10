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

        static std::unique_ptr<ListaSequencial<T>> from_array(const T* array, size_t size);
        static std::unique_ptr<ListaSequencial<T>> from_array(std::initializer_list<T> array);

        static ListaSequencial<T> from_array_on_stack(const T* array, size_t size);
        static ListaSequencial<T> from_array_on_stack(std::initializer_list<T> array);

        std::unique_ptr<ListaSequencial<T>> clone() const;
        ListaSequencial<T> clone_on_stack() const;

        T* get(size_t index);
        
        T& append(T item);
        T& insert(size_t index, T item) noexcept(false);
        T& addsorted(T item) requires std::totally_ordered<T>;
        /// @brief Consumes every element from another instance of `ListaSequencial<T>`
        /// on moving it to this current instance, leaving an empty instance
        /// of `T` for each element previously existing in it.
        /// @param list 
        void concat(ListaSequencial<T>& list);
        
        size_t find(T item) requires std::equality_comparable<T>;

        std::optional<T> pop();
        std::optional<T> remove(size_t index);
        
        size_t capacity() const;
        size_t size() const;
        size_t available_space() const;

        bool isempty() const;
        bool isfull() const;
        bool is_sorted() const;
        bool equals(const ListaSequencial<T>& list) const;

        void reverse();
        void clear();

        void print_reverse() const;
        void print() const;
};

}