# TAD - Tipos Abstratos de Dados
- Lista Sequencial
    - Arrays dinâmicos, isto é, que se realocam sozinho assim que sua capacidade é esgotada.
        - Implica que deve ser alocado na Heap.
    - Permite acesso aleatório por meio de índices.
    - Operações simples (adicionar, remover, alterar).
    - Bom para inserção/remoção ao final da lista.
    - Ruim para inserções/remoções no início ou meio da lista (piora ao tender ao início).
        - Nesse caso, acontece o "bubble".
- Lista Encadeada (linked list)
    - Trata cada item como um "node" (um nó, um elemento filho).
        - Cada node possui outro node como o próximo, a não ser que seja o último.
    - Acesso sequencial.
        - Não permite acesso aleatório verdadeiro.
    - **Ótimo** para inserções e remoções em qualquer parte da lista, devido ao modo como funciona.
    - No CPP, é a `std::forward_list`.
- Lista Duplamente Encadeada
    - Uma extensão da Lista Encadeada, mas seus nós agora também possuem um ponteiro para o node anterior
        (a não ser que seja o primeiro da lista.)
    - Permite maior navegabilidade, já que pode-se navegar de trás pra frente também.
    - No CPP, é a `std::List`.
- Lista Circular
    - É como a lista ligada, porém o último nó aponta para o primeiro.
    - É necessário atenção para evitar problemas como buscas infinitas.
- Lista Circular Duplamente Encadeada
    - É como a lista duplamente ligada, porém o úlitmo node aponta para o primeiro.
    - Mesmas desvantagens da Lista Circular.
- Fila
- Pilha

As listas podem ter otimizações como:
-   manter um atributo `size` (sempre atualizado) para evitar iterações frequentes para determinar o tamanho
    da lista dinâmicamente;
-   manter um atributo `tail` contendo o último node da lista, ao invés de determiná-lo dinâmicamente (por
    meio de iterações);
-   listas duplamente encadeadas podem utilizar o atributo `size` para procurar elementos em iterações começando
    do final da lista rumo ao início, caso o índice buscado esteja mais próximo do final da lista.

## Implementações
- `Listas::ListaSequencial`: uma implementação de uma lista sequencial simples:
    - [x] `list_get_available` => `Listas::ListaSequencial::space_available;
    - [x] `list_clear` => `Listas::clear`;
    - [x] `list_remove_last` => `Listas::ListaSequencial::pop`;
    - [ ] `list_print_reverse` => `Listas::ListaSequencial::print_reverse`;
    - [x] `list_add` => `Listas::ListaSequencial::append`;
    - [ ] `list_is_sorted` => `Listas::ListaSequencial::is_sorted`;
    - [ ] `list_reverse` => `Listas::ListaSequencial::reverse`;
    - [ ] `list_equal` => `Listas::ListaSequencial::equals`;
    - [x] `list_from_vector` => `Listas::ListaSequencial::from_array`;
    - [x] `list_copy` => `Listas::ListaSequencial::clone`;
    - [ ] `list_concat` => `Listas::ListaSequencial::concat`;
- `Listas::ListaEncadeada`: uma implementação de uma lista duplamente encadeada (sem otimizações).

## Rodando

Para rodar, será necessário ter instalado [vcpkg]() e também ter disponível o comando `make`.
Rode `vcpkg install` para baixar as dependências necessárias.

### Buildando
```shell
$ make build
```

### Rodar os testes
```shell
$ make test
```

> [!NOTE]
> Talvez seja necessário modificar os diretórios de "include" e "libs" no Makefile
> para que seja possível encontrar os cabeçalhos das dependências e "linká-las" corretamente.
