#pragma once

#include <memory>
#include <optional>
#include <concepts>
#include "listas_utils.hpp"

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
        NóListaEncadeada<T>* _tail() const;
        void clone(ListaEncadeada<T>* dest) const;

    public:
        ListaEncadeada();
        ~ListaEncadeada();

        /// @brief Adiciona um elemento no início da lista.
        /// @param element 
        /// @return Uma referência do elemento recém adicionado.
        T& pushfront(T element);

        /// @brief Adiciona um elemento no final da lista.
        /// @param element 
        /// @return Uma referência do elemento recém adicionado.
        T& pushback(T element);

        /// @brief Adiciona o `element` logo após o `offset`ésimo elemento. 
        /// @param element 
        /// @param offset 
        /// @return Uma referência do elemento recém adicionado.
        /// @throw `std::out_of_range` se `offset` >= tamanho da lista.
        T& insert(T element, size_t offset);

        /// @brief Adiciona o `element` logo antes do primeiro elemento que
        /// for maior que ele.
        /// @param element 
        /// @return Uma referência do elemento recém adicionado.
        T& insertsorted(T element) requires std::totally_ordered<T>;

        /// @brief Obtém o último item da lista.
        /// @return Uma referência para o último item da lista.
        /// @throw `std::out_of_range` se a lista estiver vazia.
        T& tail() const;

        /// @brief Obtém o primeiro item da lista.
        /// @return Uma referência para o primeiro item da lista.
        /// @throw `std::out_of_range` se a lista estiver vazia.
        T& head();

        /// @brief Obtém um ponteiro para o item na posição `index`.
        /// @param index 
        /// @return Um ponteiro (que pode ser nulo) do elemento na posição `index`.
        T* get(size_t index);

        /// @brief Obtém o índice (posição) da primeira ocorrência de `element` dentro da lista.
        /// @param element 
        /// @return Um `size_t` representando a posição da primeira ocorrência do `element` na lista.
        /// Caso `element` não esteja na lista, é retornado `-1`.
        size_t getpos(const T& element) const;

        /// @brief Remove o primeiro elemento da lista.
        /// @return O elemento removido, se a lista não estiver vazia. Caso contrário, um `nullopt` é retornado.
        std::optional<T> popfront();
        
        /// @brief Remove o último elemento da lista.
        /// @return O elemento removido, se a lista não estiver vazia. Caso contrário, um `nullopt` é retornado.
        std::optional<T> poplast();

        /// @brief Remove o elemento na posição `index` da lista.
        /// @return O elemento removido. Se a posição for inválida, um `nullopt` é retornado.
        std::optional<T> remove(size_t index);

        /// @brief Obtém o tamanho da lista.
        /// @return Um `size_t` contendo a quantidade de items na lista.
        size_t size() const;

        /// @brief Verifica se a lista está vazia.
        /// @return `true` se e somente se houver ao menos 1 elemento na lista. `false` caso contrário.
        bool isempty() const;

        /// @brief Verifica se a lista está ordenada.
        /// @return `true` se e somente se todos os elementos estiverem em ordem crescente. `false` caso contrário.
        bool issorted() const requires std::totally_ordered<T>;

        /// @brief Imprime todos os elementos da lista em formato JSON.
        void print() const;

        /// @brief Imprime o último elemento na saída padrão.
        void printlast() const;

        /// @brief Cria uma nova lista com cópias de todos os elementos desta instância.
        /// @return Um novo ponteiro único de lista encadeada do mesmo tipo que a atual.
        std::unique_ptr<ListaEncadeada<T>> deepcopy() const;      

        /// @brief O mesmo que `deep_copy`, mas retornando o elemento na stack ao invés
        /// de alocá-lo na heap.
        /// @return Uma instância de lista encadeada do mesmo tipo da atual alocado na stack.
        ListaEncadeada<T> stackdeepcopy() const;

        /// @brief Copia todos os elementos de `source` ao final da lista atual.
        /// @param source 
        void concat(const ListaEncadeada<T>& source);

        /// @brief Mescla uma segunda lista com a atual em uma nova instância de lista
        /// encadeada de `T`.
        /// @param branch 
        void merge(const ListaEncadeada<T>& branch) const;
};

}