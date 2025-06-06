# Lista Encadeada em C

## Conceito

Uma **Lista Encadeada** é uma estrutura de dados linear e dinâmica onde os elementos não são armazenados em posições contíguas de memória. Cada elemento (nó) contém dados e um ponteiro para o próximo elemento da sequência. Esta estrutura permite inserção e remoção eficientes em qualquer posição, com tamanho limitado apenas pela memória disponível.

### Características Principais

- **Tamanho Dinâmico**: Cresce e diminui conforme necessário durante a execução
- **Alocação Dinâmica**: Usa `malloc()` e `free()` para gerenciar memória
- **Acesso Sequencial**: Para acessar um elemento, deve percorrer desde o início
- **Ponteiros**: Cada nó aponta para o próximo elemento da lista

### Vantagens

- **Flexibilidade de Tamanho**: Não tem limite pré-definido de elementos
- **Eficiência de Inserção/Remoção**: Operações O(1) quando se tem o ponteiro do nó
- **Uso Eficiente de Memória**: Aloca apenas o necessário
- **Inserção em Qualquer Posição**: Facilita reorganização dos dados

### Desvantagens

- **Overhead de Memória**: Cada nó precisa armazenar um ponteiro adicional
- **Acesso Sequencial**: Não permite acesso direto por índice como arrays
- **Fragmentação de Memória**: Nós podem estar espalhados pela memória
- **Complexidade**: Mais complexa de implementar que arrays

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
**Descrição**: Inicializa uma lista encadeada vazia.

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

#### `int inserirInicio(Celula **lista, Jogador elemento)`
**Descrição**: Insere um novo elemento no início da lista.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `elemento`: Estrutura Jogador a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro de alocação de memória

**Funcionamento**: 
1. Cria uma nova célula
2. Define o conteúdo da célula
3. Faz a nova célula apontar para o antigo primeiro elemento
4. Atualiza o ponteiro da lista para a nova célula

**Complexidade**: O(1)

---

#### `int inserirFim(Celula **lista, Jogador elemento)`
**Descrição**: Insere um novo elemento no final da lista.

**Parâmetros**:
- `lista`: Ponteiro duplo para o primeiro nó da lista
- `elemento`: Estrutura Jogador a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve erro de alocação de memória

**Funcionamento**: 
1. Cria uma nova célula
2. Se a lista estiver vazia, insere como primeiro elemento
3. Caso contrário, percorre até o último nó
4. Faz o último nó apontar para a nova célula

**Complexidade**: O(n) para encontrar o final da lista

---

#### `Jogador removerInicio(Celula **lista)`
**Descrição**: Remove o primeiro elemento da lista.

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
**Descrição**: Remove o último elemento da lista.

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
3. Retorna ponteiro para a primeira ocorrência encontrada

**Complexidade**: O(n) no pior caso (elemento no final ou não encontrado)

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
**Descrição**: Compara dois jogadores pelos nomes.

**Parâmetros**:
- `j1`, `j2`: Estruturas Jogador a serem comparadas

**Retorno**: 
- 0 se os nomes são iguais
- Valor diferente de 0 se são diferentes

**Funcionamento**: Usa `strcmp()` para comparar os nomes dos jogadores.

**Complexidade**: O(m) onde m é o tamanho da string

## Funções de Interface

### `void exibirMenu(Celula **lista, int *opcao)`
Exibe o menu principal com opções específicas para lista encadeada e captura a escolha do usuário.

### `void menuExibirElementos(Celula **lista)`
Percorre e exibe todos os elementos da lista em formato de tabela, incluindo contador.

### `void menuInserirInicio(Celula **lista)`
Interface para inserção de elemento no início da lista.

### `void menuInserirFim(Celula **lista)`
Interface para inserção de elemento no final da lista.

### `void menuRemoverInicio(Celula **lista)`
Interface para remoção do primeiro elemento, com confirmação do elemento removido.

### `void menuRemoverFim(Celula **lista)`
Interface para remoção do último elemento, com confirmação do elemento removido.

### `void menuPesquisarElemento(Celula **lista)`
Interface para busca de elemento por nome, exibindo resultado formatado.

### `void menuRemoverElemento(Celula **lista)`
Interface para remoção de elemento específico por nome.

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Gerenciamento de Memória

Esta implementação utiliza alocação dinâmica de memória:

- **Alocação**: `malloc()` para criar novos nós
- **Liberação**: `free()` para remover nós da memória
- **Cuidados**: Sempre verificar se a alocação foi bem-sucedida
- **Vazamentos**: Garantir que toda memória alocada seja eventualmente liberada

## Considerações de Implementação

1. **Ponteiros Duplos**: Usados para permitir modificação do primeiro elemento
2. **Verificação de Memória**: Todas as alocações são verificadas antes do uso
3. **Casos Especiais**: Tratamento específico para lista vazia e elemento único
4. **Interface Consistente**: Retornos padronizados para indicar sucesso/erro
5. **Robustez**: Validações em todas as operações críticas
