# Lista Encadeada Ordenada em C

## Conceito

Uma **Lista Encadeada Ordenada** é uma variação da lista encadeada onde os elementos são mantidos em ordem crescente automaticamente. Cada inserção é feita na posição correta para manter a ordenação, eliminando a necessidade de ordenação posterior. Esta estrutura combina a flexibilidade de tamanho dinâmico com a vantagem de sempre manter os dados organizados.

### Características Principais

- **Ordenação Automática**: Elementos sempre mantidos em ordem crescente
- **Tamanho Dinâmico**: Cresce e diminui conforme necessário durante a execução
- **Inserção Posicionada**: Novo elemento é inserido na posição correta automaticamente
- **Acesso Sequencial Ordenado**: Percurso sempre resulta em sequência ordenada

### Vantagens

- **Dados Sempre Ordenados**: Não requer ordenação posterior
- **Busca Mais Eficiente**: Pode parar a busca quando encontra elemento maior
- **Flexibilidade de Tamanho**: Não tem limite pré-definido de elementos
- **Inserção Inteligente**: Posicionamento automático mantém ordem

### Desvantagens

- **Inserção Mais Lenta**: Precisa encontrar posição correta O(n)
- **Overhead de Comparação**: Cada inserção requer comparações
- **Complexidade**: Mais complexa que lista encadeada simples
- **Não Permite Inserção Arbitrária**: Posição é determinada pela ordenação

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
    Jogador info;
    struct celula *prox;
} Celula;
```

- `info`: Dados armazenados no nó
- `prox`: Ponteiro para o próximo nó (NULL se for o último)

**Critério de Ordenação**: Os elementos são ordenados alfabeticamente pelo campo `nome`.

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
- Status: VAZIA ou ORDENADA
- Contador de jogadores

### Funções de Manipulação da Lista

#### `void inicializarLista(Celula **lista)`
**Descrição**: Inicializa uma lista encadeada ordenada vazia.

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

#### `int inserir(Celula **lista, Jogador elemento)`
**Descrição**: Insere um elemento na posição correta para manter a ordenação.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `elemento`: Estrutura Jogador a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro de alocação de memória

**Funcionamento**: 
1. Cria uma nova célula
2. Percorre a lista até encontrar a posição correta (comparando nomes)
3. Insere o elemento mantendo a ordenação alfabética
4. Ajusta os ponteiros para incluir o novo elemento

**Complexidade**: O(n) para encontrar a posição correta

**Ordenação**: Os elementos são inseridos em ordem alfabética crescente pelo nome.

---

#### `Jogador removerInicio(Celula **lista)`
**Descrição**: Remove o primeiro elemento da lista (menor alfabeticamente).

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Retorno**: 
- Estrutura Jogador removida
- Jogador com numCamisa = -1 se a lista estiver vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Salva os dados do primeiro elemento
3. Atualiza o ponteiro da lista para o segundo elemento
4. Libera a memória do primeiro elemento
5. Retorna os dados salvos

**Complexidade**: O(1)

---

#### `Jogador removerFim(Celula **lista)`
**Descrição**: Remove o último elemento da lista (maior alfabeticamente).

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista

**Retorno**: 
- Estrutura Jogador removida
- Jogador com numCamisa = -1 se a lista estiver vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Se há apenas um elemento, remove do início
3. Percorre até o penúltimo elemento
4. Salva os dados do último elemento
5. Faz o penúltimo apontar para NULL
6. Libera a memória do último elemento

**Complexidade**: O(n) para encontrar o final da lista

---

#### `Celula * pesquisar(Celula **lista, Jogador pesquisado)`
**Descrição**: Busca um elemento na lista pelo nome do jogador.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `pesquisado`: Estrutura Jogador com o nome a ser encontrado

**Retorno**: 
- Ponteiro para a célula encontrada
- NULL se não encontrou ou lista vazia

**Funcionamento**: 
1. Verifica se a lista não está vazia
2. Percorre a lista comparando nomes
3. Pode otimizar parando quando encontra nome maior (lista ordenada)
4. Retorna ponteiro para a primeira ocorrência encontrada

**Complexidade**: O(n) no pior caso, mas pode terminar antes devido à ordenação

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
2. Se é o primeiro elemento, usa removerInicio()
3. Caso contrário, encontra o elemento anterior
4. Ajusta os ponteiros para "pular" o elemento removido
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
**Descrição**: Compara dois jogadores pelos nomes para ordenação.

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
Exibe o menu principal com opções específicas para lista encadeada ordenada.

### `void menuExibirElementos(Celula **lista)`
Percorre e exibe todos os elementos da lista em formato de tabela. Os elementos aparecem em ordem alfabética.

### `void menuInserir(Celula **lista)`
Interface para inserção de elemento na posição ordenada correta automaticamente.

### `void menuRemoverInicio(Celula **lista)`
Interface para remoção do primeiro elemento (menor nome alfabeticamente).

### `void menuRemoverFim(Celula **lista)`
Interface para remoção do último elemento (maior nome alfabeticamente).

### `void menuPesquisarElemento(Celula **lista)`
Interface para busca de elemento por nome, aproveitando a ordenação para otimizar.

### `void menuRemoverElemento(Celula **lista)`
Interface para remoção de elemento específico por nome.

## Algoritmo de Inserção Ordenada

A função `inserir()` implementa o seguinte algoritmo:

1. **Criação do Nó**: Aloca memória para novo elemento
2. **Busca da Posição**: Percorre lista até encontrar primeiro elemento maior
3. **Inserção**: 
   - Se deve ser o primeiro: atualiza ponteiro da lista
   - Caso contrário: ajusta ponteiros do anterior e atual
4. **Manutenção da Ordem**: Garante que a sequência continue ordenada

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Comparação com Lista Encadeada Simples

| Aspecto | Lista Simples | Lista Ordenada |
|---------|---------------|----------------|
| Inserção | O(1) no início | O(n) posição ordenada |
| Busca | O(n) linear | O(n) mas pode parar antes |
| Ordenação | Requer algoritmo extra | Sempre ordenada |
| Flexibilidade | Total controle posição | Posição determinada pela ordem |
| Uso de Memória | Igual | Igual |

## Vantagens da Ordenação Automática

1. **Sem Necessidade de Ordenação**: Dados sempre prontos para uso
2. **Busca Otimizada**: Pode parar quando encontra elemento maior
3. **Apresentação**: Sempre exibe dados em ordem lógica
4. **Algoritmos**: Facilita implementação de operações como merge

## Considerações de Implementação

1. **Critério de Ordenação**: Implementado através da comparação de nomes
2. **Estabilidade**: Mantém ordem relativa de elementos iguais
3. **Performance**: Trade-off entre inserção mais lenta e dados sempre ordenados
4. **Robustez**: Todas as operações mantêm a invariante de ordenação
5. **Reutilização**: Código base similar à lista encadeada simples
