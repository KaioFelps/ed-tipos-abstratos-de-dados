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
    this->size_ = 0;
}

template<typename T>
ListaSequencial<T>::ListaSequencial()
{
    this->list_ = std::make_unique<T[]>(DEFAULT_CAPACITY);
    this->capacity_ = DEFAULT_CAPACITY;
    this->size_ = 0;
}

template<typename T>
T& ListaSequencial<T>::append(T item)
{
    this->mayberesize();
    auto index = this->size_++;

    this->list_[index] = item;
    return this->list_[index];
}

template<typename T>
size_t ListaSequencial<T>::size() const { return this->size_; }

template<typename T>
size_t ListaSequencial<T>::capacity() const { return this->capacity_; }

template<typename T>
size_t ListaSequencial<T>::space_available() const
{
    return this->capacity_ - this->size_;
}

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
        new_data[i] = this->list_[i];
    
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
    this->mayberesize();

    if (index < 0 || index >= this->size_)
    {
        std::string error_message = "Tentou acessar um índice fora dos limites da lista (índice é "
            + std::to_string(index)
            + ", tamanho da lista é "
            + std::to_string(this->size_)
            + ").";

        throw std::invalid_argument(error_message); 
    }

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
    if (this->isempty()) return this->append(item);

    size_t idx = 0;
    while (idx < this->size_ && this->list_[idx] < item) idx++;

    if (idx == this->size_) return this->append(item);

    return this->insert(idx, item);
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
        this->list_[i] = this->list_[i+1];
    }

    this->size_--;

    return removed_item;
}

template<typename T>
void ListaSequencial<T>::print() const
{
    std::cout << "[";

    for (size_t i = 0; i < this->size_; i++)
    {
        std::cout << this->list_[i];
        if (i != this->size_ -1) std::cout << ", ";
    }

    std::cout << "]";
}

template<typename T>
ListaSequencial<T> ListaSequencial<T>::from_array_on_stack(T* array, size_t size)
{
    ListaSequencial<T> list = ListaSequencial(size);
    for (int i = 0; i < size; i++)
    {
        list.append(array[i]);
    }

    return list;
}

template<typename T>
ListaSequencial<T>* ListaSequencial<T>::from_array(T* array, size_t size)
{
    ListaSequencial<T>* list = new ListaSequencial(size);
    for (int i = 0; i < size; i++)
    {
        list->append(array[i]);
    }

    return list;
}

template<typename T>
ListaSequencial<T> ListaSequencial<T>::clone_on_stack() const {
    ListaSequencial<T> list = ListaSequencial(this->capacity_);

    for (int i = 0; i < this->size_; i++)
    {
        list.append(this->list_[i]);
    }

    return list;
}

template<typename T>
ListaSequencial<T>* ListaSequencial<T>::clone() const {
    ListaSequencial<T>* list = new ListaSequencial(this->capacity_);

    for (int i = 0; i < this->size_; i++)
    {
        list->append(this->list_[i]);
    }

    return list;
}

template class ListaSequencial<int>;

}