# Lista Estática em C

## Conceito

Uma **Lista Estática** é uma estrutura de dados linear que armazena elementos em posições contíguas de memória, utilizando um array de tamanho fixo. Diferentemente das listas dinâmicas, o tamanho máximo da lista é definido em tempo de compilação e não pode ser alterado durante a execução do programa.

### Características Principais

- **Tamanho Fixo**: O número máximo de elementos é definido por uma constante
- **Acesso Sequencial**: Os elementos são acessados através de índices
- **Inserção Ordenada**: Novos elementos podem ser inseridos em qualquer posição válida
- **Memória Contígua**: Todos os elementos ficam armazenados em posições consecutivas

### Vantagens

- **Simplicidade**: Fácil implementação e compreensão
- **Eficiência de Acesso**: Acesso direto aos elementos por índice
- **Controle de Memória**: Não há necessidade de alocação dinâmica
- **Cache Friendly**: Elementos contíguos melhoram a performance do cache

### Desvantagens

- **Tamanho Limitado**: Não pode exceder o tamanho pré-definido
- **Desperdício de Memória**: Pode reservar mais espaço do que necessário
- **Inserção/Remoção Custosa**: Operações no meio da lista requerem deslocamento de elementos

## Estrutura de Dados

### Definição do Elemento (Aluno)
```c
typedef struct {
    int matricula;
    char nome[50];
} Aluno;
```

### Definição da Lista Estática
```c
typedef struct {
    Aluno elementos[MAX_ELEMENTOS];
    int ultimo;
} ListaEstatica;
```

- `elementos[]`: Array que armazena os dados
- `ultimo`: Índice do último elemento válido (-1 quando vazia)

## Funções Implementadas

### Funções Auxiliares

#### `void limparBuffer()`
Remove caracteres residuais do buffer de entrada, evitando problemas na leitura de dados.

#### `void removerQuebraLinha(char *str)`
Remove o caractere de quebra de linha ('\n') de uma string, normalmente após usar `fgets()`.

#### `void limparTela()`
Limpa a tela do terminal de forma compatível com Windows e sistemas Unix.

#### `void pausar()`
Pausa a execução e aguarda o usuário pressionar ENTER para continuar.

#### `void exibirCabecalho(ListaEstatica *lista)`
Exibe o cabeçalho do sistema com informações sobre o status atual da lista:
- Status: VAZIA, PARCIAL ou CHEIA
- Contador de elementos (atual/máximo)

### Funções de Manipulação da Lista

#### `void inicializarLista(ListaEstatica *lista)`
**Descrição**: Inicializa uma lista estática, preparando-a para uso.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista

**Funcionamento**: Define o campo `ultimo` como -1, indicando que a lista está vazia.

**Complexidade**: O(1)

---

#### `int listaVazia(ListaEstatica *lista)`
**Descrição**: Verifica se a lista está vazia.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista

**Retorno**: 
- `1` se a lista estiver vazia
- `0` se a lista contiver elementos

**Funcionamento**: Verifica se `ultimo == -1`.

**Complexidade**: O(1)

---

#### `int listaCheia(ListaEstatica *lista)`
**Descrição**: Verifica se a lista atingiu sua capacidade máxima.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista

**Retorno**: 
- `1` se a lista estiver cheia
- `0` se ainda houver espaço

**Funcionamento**: Verifica se `ultimo == (MAX_ELEMENTOS - 1)`.

**Complexidade**: O(1)

---

#### `int inserirFim(ListaEstatica *lista, Aluno elemento)`
**Descrição**: Insere um novo elemento no final da lista.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista
- `elemento`: Estrutura Aluno a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se a lista estiver cheia

**Funcionamento**: 
1. Verifica se a lista está cheia
2. Insere o elemento na posição `ultimo + 1`
3. Incrementa o valor de `ultimo`

**Complexidade**: O(1)

---

#### `int inserirPosicao(ListaEstatica *lista, int posicao, Aluno elemento)`
**Descrição**: Insere um elemento em uma posição específica da lista.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista
- `posicao`: Índice onde o elemento será inserido (0 a ultimo+1)
- `elemento`: Estrutura Aluno a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro (lista cheia ou posição inválida)

**Funcionamento**: 
1. Verifica se a lista está cheia
2. Valida se a posição está no intervalo [0, ultimo+1]
3. Desloca todos os elementos da posição até o final uma posição à direita
4. Insere o novo elemento na posição especificada
5. Incrementa o valor de `ultimo`

**Complexidade**: O(n) no pior caso (inserção no início)

---

#### `int removerPosicao(ListaEstatica *lista, int posicao)`
**Descrição**: Remove um elemento de uma posição específica da lista.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista
- `posicao`: Índice do elemento a ser removido (0 a ultimo)

**Retorno**: 
- `1` se a remoção foi bem-sucedida
- `0` se houve erro (lista vazia ou posição inválida)

**Funcionamento**: 
1. Verifica se a lista está vazia
2. Valida se a posição está no intervalo [0, ultimo]
3. Desloca todos os elementos após a posição uma posição à esquerda
4. Decrementa o valor de `ultimo`

**Complexidade**: O(n) no pior caso (remoção no início)

---

#### `int modificarElemento(ListaEstatica *lista, int posicao, Aluno elemento)`
**Descrição**: Modifica um elemento existente em uma posição específica.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista
- `posicao`: Índice do elemento a ser modificado (0 a ultimo)
- `elemento`: Nova estrutura Aluno para substituir a existente

**Retorno**: 
- `1` se a modificação foi bem-sucedida
- `0` se houve erro (lista vazia ou posição inválida)

**Funcionamento**: 
1. Verifica se a lista está vazia
2. Valida se a posição está no intervalo [0, ultimo]
3. Substitui o elemento na posição especificada

**Complexidade**: O(1)

---

#### `int pesquisarElemento(ListaEstatica *lista, int matricula)`
**Descrição**: Busca um elemento na lista pela matrícula.

**Parâmetros**:
- `lista`: Ponteiro para a estrutura da lista
- `matricula`: Matrícula do aluno a ser encontrado

**Retorno**: 
- Índice do elemento encontrado (0 a ultimo)
- `-1` se o elemento não foi encontrado ou lista vazia

**Funcionamento**: 
1. Verifica se a lista está vazia
2. Percorre sequencialmente a lista comparando matrículas
3. Retorna o índice do primeiro elemento encontrado

**Complexidade**: O(n) no pior caso (elemento no final ou não encontrado)

## Funções de Interface

### `void exibirMenu(ListaEstatica *lista, int *opcao)`
Exibe o menu principal com opções disponíveis e captura a escolha do usuário.

### `void menuExibirElementos(ListaEstatica *lista)`
Exibe todos os elementos da lista em formato de tabela, incluindo contador de elementos.

### `void menuInserirPosicao(ListaEstatica *lista)`
Interface para inserção de elemento em posição específica com validações.

### `void menuInserirFim(ListaEstatica *lista)`
Interface para inserção de elemento no final da lista.

### `void menuRemoverPosicao(ListaEstatica *lista)`
Interface para remoção de elemento, exibindo lista atual antes da operação.

### `void menuModificarElemento(ListaEstatica *lista)`
Interface para modificação de elemento existente, com exibição da lista atual.

### `void menuPesquisarElemento(ListaEstatica *lista)`
Interface para busca de elemento por matrícula, exibindo resultado formatado.

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Considerações de Implementação

1. **Validação de Entrada**: Todas as operações incluem verificações de estado da lista
2. **Interface Amigável**: Menus formatados com bordas ASCII para melhor visualização
3. **Tratamento de Strings**: Remoção automática de quebras de linha em nomes
4. **Feedback Visual**: Mensagens claras de sucesso e erro para cada operação
5. **Portabilidade**: Código compatível com diferentes sistemas operacionais
