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
size_t ListaSequencial<T>::available_space() const
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
void ListaSequencial<T>::print_reverse() const
{
    std::cout << "[";

    // using a for-loop with descending `i` would trigger infinite loop as comparison for size_t >= 0 is not valid
    // 'cause compiler expects `size_t` to be unsigned. This triggers undefined behavior, since when getting > 0 by for-loop `i--`
    // it is sent to unsigned long max value.
    size_t i = this->size_ - 1;
    while(true)
    {
        std::cout << this->list_[i];
        if (i > 0) std::cout << ", ";

        if (i == 0) break;
        i--;
    }

    std::cout << "]";
}

template <typename T>
ListaSequencial<T> ListaSequencial<T>::from_array_on_stack(const T* array, size_t size)
{
    ListaSequencial<T> list = ListaSequencial(size);
    for (size_t i = 0; i < size; i++)
    {
        list.append(array[i]);
    }

    return list;
}

template<typename T>
ListaSequencial<T> ListaSequencial<T>::from_array_on_stack(std::initializer_list<T> array)
{
    ListaSequencial<T> list = ListaSequencial(array.size());
    for (auto& element : array)
    {
        list.append(element);
    }

    return list;
}

template<typename T>
std::unique_ptr<ListaSequencial<T>> ListaSequencial<T>::from_array(std::initializer_list<T> array)
{
    auto list = std::make_unique<ListaSequencial<T>>(array.size());
    for (auto& element : array)
    {
        list->append(element);
    }

    return list;
}

template<typename T>
std::unique_ptr<ListaSequencial<T>> ListaSequencial<T>::from_array(const T* array, size_t size)
{
    auto list = std::make_unique<ListaSequencial<T>>(size);
    for (size_t i = 0; i < size; i++)
    {
        list->append(array[i]);
    }

    return list;
}

template<typename T>
ListaSequencial<T> ListaSequencial<T>::clone_on_stack() const {
    ListaSequencial<T> list = ListaSequencial(this->capacity_);

    for (size_t i = 0; i < this->size_; i++)
    {
        list.append(this->list_[i]);
    }

    return list;
}

template<typename T>
std::unique_ptr<ListaSequencial<T>> ListaSequencial<T>::clone() const {
    auto list = std::make_unique<ListaSequencial<T>>(this->capacity_);

    for (size_t i = 0; i < this->size_; i++)
    {
        list->append(this->list_[i]);
    }

    return list;
}

template<typename T>
void ListaSequencial<T>::concat(ListaSequencial<T>& list)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        T element = T{};
        std::swap(*list.get(i), element);
        this->append(element);
    }
}

template<typename T>
void ListaSequencial<T>::clear()
{
    this->size_ = 0;
    this->capacity_ = DEFAULT_CAPACITY;
    this->list_.reset(new T[this->capacity_]);
}

// ===========================
// UNIMPLEMENTED
// ===========================

template<typename T>
bool ListaSequencial<T>::is_sorted() const
{
    for (size_t i = 0; i < this->size_ -1; i++)
    {
        if (this->list_[i] > this->list_[(i+1)]) return false;
    }

    return true;
}

template<typename T>
bool ListaSequencial<T>::equals(const ListaSequencial<T>& list) const
requires std::equality_comparable<T>
{
    if (this->size() != list.size()) return false;

    for (size_t i = 0; i < this->size(); i++)
    {
        if (this->list_[i] != list.list_[i]) return false;
    }

    return true;
}

template<typename T>
bool ListaSequencial<T>::operator==(const ListaSequencial<T>& list) const
requires std::equality_comparable<T>
{
    return this->equals(list);
}

template<typename T>
bool ListaSequencial<T>::operator!=(const ListaSequencial<T>& list) const
requires std::equality_comparable<T>
{
    return !this->equals(list);
}

template<typename T>
bool ListaSequencial<T>::equals(const ListaSequencial<T>* list) const
requires std::equality_comparable<T>
{
    if (this->size() != list->size()) return false;

    for (size_t i = 0; i < this->size(); i++)
    {
        if (this->list_[i] != list->list_[i]) return false;
    }

    return true;
}

template<typename T>
bool ListaSequencial<T>::equals(const std::unique_ptr<ListaSequencial<T>>& list) const
requires std::equality_comparable<T>
{
    return this->equals(*list);
}

template<typename T>
bool ListaSequencial<T>::equals(const std::shared_ptr<ListaSequencial<T>>& list) const
requires std::equality_comparable<T>
{
    return true;
    // return this->equals(*list);
}

template class ListaSequencial<int>;

}