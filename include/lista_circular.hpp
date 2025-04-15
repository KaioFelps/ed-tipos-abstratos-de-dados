#include "listas_utils.hpp"
#include <optional>

namespace Listas
{

template<typename T>
class NóListaCircular
{
    private:
        T element_;
        NóListaCircular<T>* previous_;
        NóListaCircular<T>* next_;
    
    public:
        T& element();
        T takeelement();

        bool hasnext() const;
        bool hasprevious() const;

        NóListaCircular<T>* getnext();
        NóListaCircular<T>* getprevious();

        void setprevious(NóListaCircular<T>* node);
        void setnext(NóListaCircular<T>* node);
};

template<typename T>
class ListaCircular
{
    private:
        NóListaCircular<T>* head_;
        NóListaCircular<T>* tail_;
        size_t size_;

    public:
        ListaCircular();
        ~ListaCircular();

        /// @brief Insere `element` no início da lista.
        /// @param element 
        /// @return Uma referência para `element`.
        T& pushfront(T element);
        /// @brief Insere `element` no final da lista.
        /// @param element 
        /// @return Uma referência para `element`.
        T& pushback(T element);
        /// @brief Insere `element` na `index`ésima posição na lista.
        /// Se `index` for maior que o tamanho da lista, a volta para o início.
        /// Se `index` for menor que 0, o cursor volta para o final da lista.
        /// @param index 
        /// @param element 
        /// @return Uma referência para o `element`.
        T& insert(size_t index, T element);
        /// @brief Insere `element` ordenado em ordem crescente, parando no primeiro elemento
        /// que for maior que ele.
        /// @param element 
        /// @return Uma referência para o `element`.
        T& addsorted(T element);

        /// @brief Remove o primeiro elemento da lista.
        /// @return O elemento removido. Se a lista estiver vazia, `nullopt`.
        std::optional<T> popfront();
        /// @brief Remove o último elemento da lista e o retorna.
        /// @return O elemento removido. Se a lista estiver vazia, `nullopt`.
        std::optional<T> poplast();
        /// @brief Remove o elemento na `index`ésima posição da lista.
        /// @param index 
        /// @return O elemento removido. `nullopt` se a posição for inválida.
        std::optional<T> remove(size_t index);

        /// @brief Verifica se a lista está vazia.
        /// @return `true` se e somente se não houver nenhum elemento na lista. `false` caso contrário.
        bool isempty() const;
        /// @brief Obtém o tamanho da lista.
        /// @return Um `size_t` representando o tamanho da lista.
        size_t size() const;
};

}
