# Lista Duplamente Encadeada em C

## Conceito

Uma **Lista Duplamente Encadeada** é uma estrutura de dados linear e dinâmica onde cada elemento (nó) contém dados e dois ponteiros: um para o próximo elemento e outro para o elemento anterior na sequência. Esta estrutura permite navegação bidirecional e operações de inserção/remoção mais eficientes em qualquer posição da lista.

### Características Principais

- **Navegação Bidirecional**: Possibilita percorrer a lista em ambas as direções
- **Tamanho Dinâmico**: Cresce e diminui conforme necessário durante a execução
- **Dois Ponteiros por Nó**: Cada célula mantém referências para o próximo e anterior
- **Alocação Dinâmica**: Usa `malloc()` e `free()` para gerenciar memória

### Vantagens

- **Flexibilidade de Navegação**: Permite percorrer a lista em qualquer direção
- **Eficiência de Remoção**: Não precisa percorrer para encontrar o elemento anterior
- **Inserção Eficiente**: Operações O(1) quando se tem o ponteiro do nó
- **Uso Eficiente de Memória**: Aloca apenas o necessário
- **Operações Simétricas**: Inserção/remoção no início e fim com complexidade similar

### Desvantagens

- **Overhead de Memória**: Cada nó precisa armazenar dois ponteiros adicionais
- **Complexidade de Implementação**: Mais complexa que lista simples devido às ligações duplas
- **Fragmentação de Memória**: Nós podem estar espalhados pela memória
- **Manutenção de Integridade**: Requer cuidado para manter ligações corretas

## Estrutura de Dados

### Definição do Elemento (Jogador)
```c
typedef struct {
    int numCamisa;
    char nome[50];
} Jogador;
```

### Definição da Célula (Nó)
```c
typedef struct celula {
    struct celula* ante;
    Jogador elemento;
    struct celula* prox;
} Celula;
```

- `ante`: Ponteiro para o nó anterior (NULL se for o primeiro)
- `elemento`: Dados armazenados no nó
- `prox`: Ponteiro para o próximo nó (NULL se for o último)

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

#### `int contarElementos(Celula **lista)`
Percorre a lista e retorna o número total de elementos armazenados.

#### `void exibirCabecalho(Celula **lista)`
Exibe o cabeçalho do sistema com informações sobre o status atual da lista:
- Status: VAZIA ou COM DADOS
- Contador de jogadores

### Funções de Manipulação da Lista

#### `void inicializarLista(Celula **lista)`
**Descrição**: Inicializa uma lista duplamente encadeada vazia.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Funcionamento**: Define o ponteiro da lista como NULL, indicando lista vazia.

**Complexidade**: O(1)

---

#### `int listaVazia(Celula **lista)`
**Descrição**: Verifica se a lista está vazia.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Retorno**: 
- `1` se a lista estiver vazia
- `0` se a lista contiver elementos

**Funcionamento**: Verifica se o ponteiro da lista é NULL.

**Complexidade**: O(1)

---

#### `Celula * criarCelula()`
**Descrição**: Aloca dinamicamente memória para um novo nó.

**Retorno**: 
- Ponteiro para a nova célula alocada
- NULL se não conseguir alocar memória

**Funcionamento**: Usa `malloc()` para alocar memória do tamanho de uma Celula.

**Complexidade**: O(1)

---

#### `int inserirNoFim(Celula **lista, Jogador novo)`
**Descrição**: Insere um novo elemento no final da lista duplamente encadeada.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `novo`: Estrutura Jogador a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro de alocação de memória

**Funcionamento**: 
1. Cria uma nova célula e verifica alocação
2. Inicializa os campos da nova célula
3. Se a lista estiver vazia, faz o ponteiro principal apontar para ela
4. Caso contrário, percorre até o último nó
5. Faz as ligações duplas: último->prox = nova e nova->ante = último

**Complexidade**: O(n) para encontrar o final da lista

---

#### `int inserirNoInicio(Celula **lista, Jogador novo)`
**Descrição**: Insere um novo elemento no início da lista duplamente encadeada.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `novo`: Estrutura Jogador a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro de alocação de memória

**Funcionamento**: 
1. Cria uma nova célula
2. Se a lista estiver vazia, reutiliza inserirNoFim()
3. Caso contrário, configura os ponteiros:
   - nova->prox = primeiro elemento atual
   - primeira célula atual->ante = nova
   - nova->ante = NULL
4. Atualiza o ponteiro principal para a nova célula

**Complexidade**: O(1)

---

#### `Jogador removerNoInicio(Celula **lista)`
**Descrição**: Remove o primeiro elemento da lista duplamente encadeada.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Retorno**: 
- Estrutura Jogador removida
- Jogador com numCamisa = -1 se a lista estiver vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Guarda o endereço da célula a ser removida
3. Faz uma cópia do elemento da célula removida
4. Atualiza o ponteiro principal para o segundo elemento
5. Se ainda há elementos, define o campo ante do novo primeiro como NULL
6. Libera a memória da célula removida

**Complexidade**: O(1)

---

#### `Jogador removerNoFim(Celula **lista)`
**Descrição**: Remove o último elemento da lista duplamente encadeada.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Retorno**: 
- Estrutura Jogador removida
- Jogador com numCamisa = -1 se a lista estiver vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Percorre até encontrar a última célula
3. Se há apenas um elemento, reutiliza removerNoInicio()
4. Caso contrário, ajusta o ponteiro prox da célula anterior para NULL
5. Libera a memória da última célula

**Complexidade**: O(n) para encontrar o final da lista

---

#### `Celula * pesquisar(Celula **lista, Jogador pesquisado)`
**Descrição**: Busca um elemento na lista pelo nome do jogador.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `pesquisado`: Estrutura Jogador com o nome a ser buscado

**Retorno**: 
- Ponteiro para a célula que contém o elemento
- NULL se não encontrar ou lista vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Percorre a lista comparando nomes com strcmp()
3. Retorna o ponteiro da célula se encontrar
4. Retorna NULL se percorrer toda a lista sem encontrar

**Complexidade**: O(n) no pior caso

---

#### `Jogador removerElemento(Celula **lista, Jogador elemento)`
**Descrição**: Remove um elemento específico da lista baseado no nome.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `elemento`: Estrutura Jogador com o nome a ser removido

**Retorno**: 
- Estrutura Jogador removida
- Jogador com numCamisa = -1 se não encontrou

**Funcionamento**: 
1. Usa a função pesquisar para localizar o elemento
2. Se for o primeiro elemento, usa removerNoInicio()
3. Se for o último elemento, usa removerNoFim()
4. Caso contrário, ajusta as ligações duplas:
   - anterior->prox = próximo
   - próximo->ante = anterior
5. Libera a memória do elemento removido

**Complexidade**: O(n) para encontrar o elemento

---

#### `Jogador criarElemento(int numCamisa, char nome[])`
**Descrição**: Função auxiliar para criar uma estrutura Jogador.

**Parâmetros**:
- `numCamisa`: Número da camisa do jogador
- `nome`: Nome do jogador

**Retorno**: Estrutura Jogador preenchida

**Funcionamento**: Cria e preenche uma estrutura Jogador com os dados fornecidos.

**Complexidade**: O(1)

---

#### `int compararElemento(Jogador j1, Jogador j2)`
**Descrição**: Compara dois jogadores pelos nomes.

**Parâmetros**:
- `j1`, `j2`: Estruturas Jogador a serem comparadas

**Retorno**: 
- 0 se os nomes são iguais
- Valor negativo se j1 < j2 (alfabeticamente)
- Valor positivo se j1 > j2 (alfabeticamente)

**Funcionamento**: Usa `strcmp()` para comparar os nomes dos jogadores.

**Complexidade**: O(m) onde m é o tamanho da string

## Funções de Interface

### `void exibirMenu(Celula **lista, int *opcao)`
Exibe o menu principal com opções para manipular a lista duplamente encadeada.

### `void menuExibirElementos(Celula **lista)`
Interface para exibir todos os elementos da lista em formato tabular.

### `void menuInserirInicio(Celula **lista)`
Interface para inserir um novo jogador no início da lista.

### `void menuInserirFim(Celula **lista)`
Interface para inserir um novo jogador no final da lista.

### `void menuRemoverInicio(Celula **lista)`
Interface para remover o primeiro jogador da lista.

### `void menuRemoverFim(Celula **lista)`
Interface para remover o último jogador da lista.

### `void menuPesquisarElemento(Celula **lista)`
Interface para pesquisar um jogador pelo nome.

### `void menuRemoverElemento(Celula **lista)`
Interface para remover um jogador específico pelo nome.

## Complexidade das Operações

| Operação | Complexidade | Observações |
|----------|--------------|-------------|
| Inserir no início | O(1) | Operação constante |
| Inserir no fim | O(n) | Precisa percorrer até o final |
| Remover do início | O(1) | Operação constante |
| Remover do fim | O(n) | Precisa percorrer até o final |
| Buscar elemento | O(n) | Busca sequencial |
| Remover elemento específico | O(n) | Inclui tempo de busca |

## Vantagens da Lista Duplamente Encadeada

1. **Navegação Bidirecional**: Permite percorrer em ambas as direções
2. **Remoção Eficiente**: Não precisa buscar o elemento anterior
3. **Flexibilidade**: Facilita implementação de operações simétricas
4. **Integridade**: Ligações duplas aumentam a robustez da estrutura

## Como Usar

1. **Compilar**: `gcc -o programa main.c`
2. **Executar**: `./programa`
3. **Navegar**: Use o menu interativo para testar as funcionalidades

O programa oferece uma interface completa para gerenciamento de jogadores usando lista duplamente encadeada, com operações de inserção, remoção, busca e visualização. 