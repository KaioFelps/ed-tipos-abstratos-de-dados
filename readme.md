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
        - Cada node possui um node como o anterior, a não ser que seja o primeiro da lista.
    - Acesso sequencial.
        - Não permite acesso aleatório.
    - **Ótimo** para inserções e remoções em qualquer parte da lista.
        - Pelo jeito como funciona.
    - No CPP, é a `std::forward_list`.
- Lista Duplamente Encadeada
    - No CPP, é a `std::List`.
- Lista Circular
- Fila
- Pilha

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
