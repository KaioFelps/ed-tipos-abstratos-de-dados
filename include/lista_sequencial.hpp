#pragma once

#include <optional>
#include <memory>

#define DEFAULT_CAPACITY 100
#define INCREASE_CAPACITY_BY 50

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

        T* get(int index);
        
        T& append(T item);
        T& insert(int index, T item) noexcept(false);
        T& addsorted(T item) requires std::totally_ordered<T>;
        
        int find(T item) requires std::equality_comparable<T>;

        std::optional<T> pop();
        std::optional<T> remove(int index);
        
        size_t capacity() const;
        size_t size() const;

        bool isempty() const;
        bool isfull() const;

        void print() const;
};