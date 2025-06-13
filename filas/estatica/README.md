# Fila Estática em C

## Conceito

Uma **Fila Estática** é uma estrutura de dados linear que segue o princípio FIFO (First In, First Out - Primeiro a Entrar, Primeiro a Sair). Os elementos são inseridos em uma extremidade (final da fila) e removidos da outra extremidade (início da fila), simulando uma fila do mundo real. A implementação estática utiliza um array de tamanho fixo com ponteiros para controlar o início e fim da fila.

### Características Principais

- **FIFO (First In, First Out)**: O primeiro elemento inserido é o primeiro a ser removido
- **Tamanho Fixo**: O número máximo de elementos é definido em tempo de compilação
- **Fila Circular**: Utiliza aritmética modular para reutilizar posições do array
- **Dois Ponteiros**: `inicio` (para remoção) e `fim` (para inserção)
- **Controle de Tamanho**: Campo adicional para rastrear número de elementos

### Vantagens

- **Simplicidade**: Implementação direta com array
- **Eficiência**: Operações de inserção e remoção são O(1)
- **Controle de Memória**: Não há alocação dinâmica
- **Previsibilidade**: Comportamento determinístico de memória
- **Baixo Overhead**: Não requer ponteiros extras por elemento

### Desvantagens

- **Tamanho Limitado**: Não pode exceder o tamanho pré-definido
- **Desperdício de Memória**: Pode reservar mais espaço do que necessário
- **Rigidez**: Tamanho não pode ser alterado durante execução

## Estrutura de Dados

### Definição do Elemento (Processo)
```c
typedef struct {
    int id;
    char descricao[50];
} Processo;
```

### Definição da Fila Estática
```c
typedef struct {
    Processo elementos[MAX_ELEMENTOS];
    int inicio;
    int fim;
    int tamanho;
} FilaEstatica;
```

- `elementos[]`: Array que armazena os dados
- `inicio`: Índice do primeiro elemento (próximo a ser removido)
- `fim`: Índice do último elemento inserido
- `tamanho`: Número atual de elementos na fila

## Funcionamento da Fila Circular

A implementação utiliza **fila circular** para otimizar o uso do array:

```
Estado Inicial: [_, _, _, _, _]  inicio=0, fim=-1, tamanho=0

Após inserir A: [A, _, _, _, _]  inicio=0, fim=0, tamanho=1
Após inserir B: [A, B, _, _, _]  inicio=0, fim=1, tamanho=2
Após inserir C: [A, B, C, _, _]  inicio=0, fim=2, tamanho=3

Após remover A: [_, B, C, _, _]  inicio=1, fim=2, tamanho=2
Após inserir D: [_, B, C, D, _]  inicio=1, fim=3, tamanho=3
Após inserir E: [_, B, C, D, E]  inicio=1, fim=4, tamanho=4

Após remover B: [_, _, C, D, E]  inicio=2, fim=4, tamanho=3
Após inserir F: [F, _, C, D, E]  inicio=2, fim=0, tamanho=4 (circular!)
```

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

#### `void exibirCabecalho(FilaEstatica *fila)`
Exibe o cabeçalho do sistema com informações sobre o status atual da fila:
- Status: VAZIA, PARCIAL ou CHEIA
- Contador de processos (atual/máximo)

### Funções de Manipulação da Fila

#### `void inicializarFila(FilaEstatica *fila)`
**Descrição**: Inicializa uma fila estática vazia.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Funcionamento**: 
- Define `inicio = 0`
- Define `fim = -1` 
- Define `tamanho = 0`

**Complexidade**: O(1)

---

#### `int filaVazia(FilaEstatica *fila)`
**Descrição**: Verifica se a fila está vazia.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- `1` se a fila estiver vazia
- `0` se a fila contiver elementos

**Funcionamento**: Verifica se `tamanho == 0`.

**Complexidade**: O(1)

---

#### `int filaCheia(FilaEstatica *fila)`
**Descrição**: Verifica se a fila atingiu sua capacidade máxima.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- `1` se a fila estiver cheia
- `0` se ainda houver espaço

**Funcionamento**: Verifica se `tamanho == MAX_ELEMENTOS`.

**Complexidade**: O(1)

---

#### `int enqueue(FilaEstatica *fila, Processo elemento)`
**Descrição**: Insere um novo elemento no final da fila (operação de enfileiramento).

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila
- `elemento`: Estrutura Processo a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se a fila estiver cheia

**Funcionamento**: 
1. Verifica se a fila está cheia
2. Calcula nova posição do fim usando aritmética modular: `(fim + 1) % MAX_ELEMENTOS`
3. Insere o elemento na nova posição do fim
4. Incrementa o tamanho

**Complexidade**: O(1)

**Exemplo**:
```c
Processo p = {101, "Processo de Sistema"};
if (enqueue(&fila, p)) {
    printf("Processo inserido com sucesso!\n");
}
```

---

#### `Processo dequeue(FilaEstatica *fila)`
**Descrição**: Remove o primeiro elemento da fila (operação de desenfileiramento).

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- Estrutura Processo removida
- Processo com id = -1 se a fila estiver vazia

**Funcionamento**: 
1. Verifica se a fila está vazia
2. Salva o elemento do início da fila
3. Atualiza o início usando aritmética modular: `(inicio + 1) % MAX_ELEMENTOS`
4. Decrementa o tamanho
5. Retorna o elemento removido

**Complexidade**: O(1)

**Exemplo**:
```c
Processo removido = dequeue(&fila);
if (removido.id != -1) {
    printf("Removido: %d - %s\n", removido.id, removido.descricao);
}
```

---

#### `Processo consultarProximo(FilaEstatica *fila)`
**Descrição**: Consulta o próximo elemento a ser removido sem removê-lo da fila.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- Estrutura Processo do início da fila
- Processo com id = -1 se a fila estiver vazia

**Funcionamento**: 
1. Verifica se a fila está vazia
2. Retorna o elemento na posição `inicio` sem modificar a fila

**Complexidade**: O(1)

**Exemplo**:
```c
Processo proximo = consultarProximo(&fila);
if (proximo.id != -1) {
    printf("Próximo: %d - %s\n", proximo.id, proximo.descricao);
}
```

## Funções de Interface

### `void exibirMenu(FilaEstatica *fila, int *opcao)`
Exibe o menu principal com opções específicas para fila e captura a escolha do usuário.

### `void menuExibirFila(FilaEstatica *fila)`
Exibe todos os elementos da fila em ordem FIFO, mostrando:
- Posição na fila (1 = próximo a ser atendido)
- ID e descrição do processo
- Total de processos na fila
- Próximo processo a ser atendido

### `void menuEnqueue(FilaEstatica *fila)`
Interface para inserção de novo processo no final da fila, com validação de fila cheia.

### `void menuDequeue(FilaEstatica *fila)`
Interface para remoção do primeiro processo da fila, mostrando:
- Processo que será removido
- Processo removido
- Próximo processo da fila (se houver)

### `void menuConsultarProximo(FilaEstatica *fila)`
Interface para consultar o próximo processo sem removê-lo, exibindo detalhes formatados.

### `void menuLimparFila(FilaEstatica *fila)`
Interface para limpar toda a fila com confirmação do usuário, incluindo aviso sobre a operação destrutiva.

## Aplicações Práticas

### Sistemas Operacionais
- **Escalonamento de Processos**: Fila de processos prontos para execução
- **Gerenciamento de Impressão**: Fila de documentos para impressora
- **Buffer de Entrada/Saída**: Fila de dados aguardando processamento

### Simulações
- **Atendimento em Bancos**: Fila de clientes
- **Controle de Tráfego**: Fila de veículos em semáforo
- **Sistemas de Chamadas**: Fila de chamadas telefônicas

### Algoritmos
- **Busca em Largura (BFS)**: Fila de vértices a serem visitados
- **Algoritmos de Grafos**: Processamento de nós em ordem específica

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Análise de Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| **Inicializar** | O(1) | O(1) |
| **Enqueue** | O(1) | O(1) |
| **Dequeue** | O(1) | O(1) |
| **Consultar** | O(1) | O(1) |
| **Verificar Vazia/Cheia** | O(1) | O(1) |
| **Exibir Fila** | O(n) | O(1) |

## Vantagens da Implementação Circular

1. **Reutilização de Espaço**: Posições liberadas podem ser reutilizadas
2. **Eficiência**: Não há necessidade de deslocar elementos
3. **Simplicidade**: Operações O(1) para inserção e remoção
4. **Otimização de Memória**: Aproveita todo o espaço do array

## Considerações de Implementação

1. **Aritmética Modular**: Uso de `%` para implementar comportamento circular
2. **Campo Tamanho**: Essencial para distinguir fila vazia de fila cheia
3. **Validações**: Verificações em todas as operações críticas
4. **Estado Consistente**: Manutenção de invariantes da estrutura
5. **Interface Robusta**: Tratamento de casos excepcionais

## Comparação: Fila vs Lista

| Aspecto | Fila | Lista |
|---------|------|-------|
| **Acesso** | Apenas início e fim | Qualquer posição |
| **Inserção** | Apenas no fim | Qualquer posição |
| **Remoção** | Apenas do início | Qualquer posição |
| **Uso Típico** | Escalonamento, buffering | Armazenamento geral |
| **Complexidade** | O(1) para operações básicas | O(n) para busca/inserção |

---

**Desenvolvido como material didático para ensino de Estruturas de Dados em C** 