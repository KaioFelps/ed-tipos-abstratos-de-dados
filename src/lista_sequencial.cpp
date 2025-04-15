#include "lista_sequencial.hpp"
#include <iostream>
#include <concepts>
#include <exception>

namespace Listas
{

template<typename T>
ListaSequencial<T>::ListaSequencial(size_t _capacity)
{
    this->list_ = std::make_unique<T[]>(_capacity);
    this->capacity_ = _capacity;
}

template<typename T>
ListaSequencial<T>::ListaSequencial()
{
    this->list_ = std::make_unique<T[]>(DEFAULT_CAPACITY);
    this->capacity_ = DEFAULT_CAPACITY;
}

template<typename T>
T& ListaSequencial<T>::append(T item)
{
    this->mayberesize();
    this->list_[this->size_++] = item;
    return this->list_[this->size_-1];
}

template<typename T>
size_t ListaSequencial<T>::size() const { return this->size_; }

template<typename T>
size_t ListaSequencial<T>::capacity() const { return this->capacity_; }

template<typename T>
bool ListaSequencial<T>::isempty() const { return this->size_ == 0; }

template<typename T>
bool ListaSequencial<T>::isfull() const { return this->size_ == this->capacity_; }

template<typename T>
void ListaSequencial<T>::mayberesize()
{
    if (this->size_ == this->capacity_) {
        this->resize();
    }
}

template<typename T>
void ListaSequencial<T>::resize() {
    auto new_capacity = this->capacity_ + INCREASE_CAPACITY_BY;
    auto new_data = new T[new_capacity];

    for (size_t i = 0; i < this->capacity_; i++)
        new_data[i] = this->list_.get()[i];
    
    this->capacity_ = new_capacity;
    this->list_.reset(new_data);
}

template<typename T>
T* ListaSequencial<T>::get(size_t index)
{
    if (index < 0 || index >= this->size_) return nullptr;

    return &this->list_[index];
}

template<typename T>
T& ListaSequencial<T>::insert(size_t index, T item) noexcept(false)
{
    if (index < 0 || index >= this->capacity_)
    {
        throw std::invalid_argument("Tentou acessar um índice fora dos limites da lista.");
    }
    
    this->mayberesize();

    for (size_t i = this->size_; i > index && i > 0; i--)
    {
        this->list_[i] = this->list_[i-1];
    }

    this->list_[index] = item;
    this->size_++;


    return this->list_[index];
}

template<typename T>
T& ListaSequencial<T>::addsorted(T item)
requires std::totally_ordered<T>
{
    size_t idx = 0;
    while (idx < this->size_ && this->list_[idx] < item) idx++;

    this->insert(idx, item);
    return this->list_[idx];
}


template<typename T>
size_t ListaSequencial<T>::find(T _item)
requires std::equality_comparable<T>
{
    for (size_t i = 0; i < this->size_; i++)
    {
        auto& item = this->list_[i];
        if (item == _item) return i;
    }

    return not_found_pos;
}

template<typename T>
std::optional<T> ListaSequencial<T>::pop()
{
    if (this->isempty())
    {
        return std::nullopt;
    }

    auto removed_item = this->list_[this->size_ -1];
    this->list_[this->size_-1] = T{};
    this->size_--;

    return removed_item;
}

template<typename T>
std::optional<T> ListaSequencial<T>::remove(size_t index)
{
    if (index < 0 || this->size_ <= index)
    {
        return std::nullopt;
    }

    auto removed_item = this->list_[index];

    for (size_t i = index; i < this->size_ -1; i++)
    {
        this->list_.get()[i] = this->list_.get()[i+1];
    }

    this->size_--;

    return removed_item;
}

template<typename T>
void ListaSequencial<T>::print() const
{
    std::cout << "[ ";
    for (size_t i = 0; i < this->size_; i++)
    {
        if (i != this->size_ -1)
        {
            std::cout << this->list_[i] << ", ";
        } else {
            std::cout << this->list_[i];
        }
    }
    std::cout << " ]\n";
}

template class ListaSequencial<int>;

}