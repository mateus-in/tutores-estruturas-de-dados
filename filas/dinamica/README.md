# Fila Dinâmica (Encadeada) em C

## Conceito

Uma **Fila Dinâmica** é uma estrutura de dados linear que segue o princípio FIFO (First In, First Out), implementada utilizando lista encadeada. Diferentemente da fila estática, não possui limite pré-definido de elementos, crescendo e diminuindo conforme necessário através de alocação dinâmica de memória.

### Características Principais

- **FIFO (First In, First Out)**: O primeiro elemento inserido é o primeiro a ser removido
- **Tamanho Dinâmico**: Cresce e diminui conforme a demanda
- **Lista Encadeada**: Cada elemento aponta para o próximo
- **Dois Ponteiros**: `inicio` (para remoção) e `fim` (para inserção)
- **Gestão de Memória**: Aloca e libera memória automaticamente

### Vantagens

- **Flexibilidade**: Tamanho limitado apenas pela memória disponível
- **Eficiência de Memória**: Utiliza apenas o espaço necessário
- **Operações O(1)**: Inserção e remoção são constantes
- **Escalabilidade**: Adapta-se à demanda real do sistema
- **Sem Desperdício**: Não reserva espaço desnecessário

### Desvantagens

- **Overhead de Ponteiros**: Cada nó requer espaço adicional para ponteiros
- **Fragmentação**: Memória pode ficar fragmentada
- **Complexidade**: Implementação mais complexa que versão estática
- **Acesso Sequencial**: Não permite acesso aleatório aos elementos
- **Gerenciamento de Memória**: Risco de vazamentos se mal implementada

## Estrutura de Dados

### Definição do Elemento (Ticket)
```c
typedef struct {
    int prioridade;
    char tarefa[100];
} Ticket;
```

### Definição do Nó da Fila
```c
typedef struct NoFila {
    Ticket dados;
    struct NoFila *proximo;
} NoFila;
```

### Definição da Fila Dinâmica
```c
typedef struct {
    NoFila *inicio;
    NoFila *fim;
    int tamanho;
} FilaDinamica;
```

- `inicio`: Ponteiro para o primeiro elemento (próximo a ser removido)
- `fim`: Ponteiro para o último elemento (último inserido)
- `tamanho`: Contador de elementos na fila

## Funcionamento Visual

```
Estado Inicial: inicio = NULL, fim = NULL, tamanho = 0

Após inserir A:
[A] -> NULL
↑      
inicio/fim

Após inserir B:
[A] -> [B] -> NULL
↑      ↑
inicio fim

Após inserir C:
[A] -> [B] -> [C] -> NULL
↑             ↑
inicio        fim

Após remover A:
[B] -> [C] -> NULL
↑      ↑
inicio fim

Após remover B:
[C] -> NULL
↑
inicio/fim
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

#### `void exibirCabecalho(FilaDinamica *fila)`
Exibe o cabeçalho do sistema com informações sobre o status atual da fila:
- Status: VAZIA ou ATIVA
- Contador de tickets atual

### Funções de Manipulação da Fila

#### `void inicializarFila(FilaDinamica *fila)`
**Descrição**: Inicializa uma fila dinâmica vazia.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Funcionamento**: 
- Define `inicio = NULL`
- Define `fim = NULL` 
- Define `tamanho = 0`

**Complexidade**: O(1)

---

#### `int filaVazia(FilaDinamica *fila)`
**Descrição**: Verifica se a fila está vazia.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- `1` se a fila estiver vazia (`inicio == NULL`)
- `0` se a fila contiver elementos

**Complexidade**: O(1)

---

#### `int enqueue(FilaDinamica *fila, Ticket elemento)`
**Descrição**: Insere um novo elemento no final da fila (operação de enfileiramento).

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila
- `elemento`: Estrutura Ticket a ser inserida

**Retorno**: 
- `1` se a inserção foi bem-sucedida
- `0` se houve falha na alocação de memória

**Funcionamento**: 
1. Aloca memória para novo nó usando `malloc()`
2. Verifica se alocação foi bem-sucedida
3. Define dados e `proximo = NULL` no novo nó
4. Se fila vazia: `inicio` e `fim` apontam para novo nó
5. Se fila não vazia: liga último elemento ao novo e atualiza `fim`
6. Incrementa tamanho

**Complexidade**: O(1)

**Exemplo**:
```c
Ticket t = {5, "Processar relatório"};
if (enqueue(&fila, t)) {
    printf("Ticket inserido com sucesso!\n");
} else {
    printf("Erro: Memória insuficiente!\n");
}
```

---

#### `Ticket dequeue(FilaDinamica *fila)`
**Descrição**: Remove o primeiro elemento da fila (operação de desenfileiramento).

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- Estrutura Ticket removida
- Ticket com prioridade = -1 se a fila estiver vazia

**Funcionamento**: 
1. Verifica se fila está vazia
2. Salva ponteiro do nó a ser removido
3. Salva dados do elemento a ser removido
4. Atualiza `inicio` para próximo elemento
5. Se fila ficou vazia: atualiza `fim = NULL`
6. Libera memória do nó removido com `free()`
7. Decrementa tamanho
8. Retorna dados removidos

**Complexidade**: O(1)

**Exemplo**:
```c
Ticket removido = dequeue(&fila);
if (removido.prioridade != -1) {
    printf("Removido: %d - %s\n", removido.prioridade, removido.tarefa);
} else {
    printf("Fila vazia!\n");
}
```

---

#### `Ticket consultarProximo(FilaDinamica *fila)`
**Descrição**: Consulta o próximo elemento a ser removido sem removê-lo da fila.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Retorno**: 
- Estrutura Ticket do início da fila
- Ticket com prioridade = -1 se a fila estiver vazia

**Funcionamento**: 
1. Verifica se fila está vazia
2. Retorna dados do elemento em `inicio` sem modificar a fila

**Complexidade**: O(1)

---

#### `void liberarFila(FilaDinamica *fila)`
**Descrição**: Remove todos os elementos da fila, liberando toda a memória alocada.

**Parâmetros**:
- `fila`: Ponteiro para a estrutura da fila

**Funcionamento**: 
1. Chama `dequeue()` repetidamente até fila ficar vazia
2. Cada chamada libera a memória de um nó

**Complexidade**: O(n), onde n é o número de elementos

**Exemplo**:
```c
liberarFila(&fila);
printf("Todos os elementos foram removidos e memória liberada.\n");
```

## Funções de Interface

### `void exibirMenu(FilaDinamica *fila, int *opcao)`
Exibe o menu principal com 7 opções e captura a escolha do usuário.

### `void menuExibirFila(FilaDinamica *fila)`
Exibe todos os elementos da fila em ordem FIFO, mostrando:
- Posição na fila (1 = próximo a ser atendido)
- Prioridade e descrição da tarefa
- Total de tickets na fila
- Próximo ticket a ser atendido

### `void menuEnqueue(FilaDinamica *fila)`
Interface para inserção de novo ticket no final da fila, incluindo:
- Validação de entrada
- Tratamento de falha de alocação
- Feedback ao usuário

### `void menuDequeue(FilaDinamica *fila)`
Interface para remoção do primeiro ticket da fila, mostrando:
- Ticket que será removido
- Confirmação da remoção
- Próximo ticket da fila (se houver)

### `void menuConsultarProximo(FilaDinamica *fila)`
Interface para consultar o próximo ticket sem removê-lo, exibindo detalhes formatados.

### `void menuLimparFila(FilaDinamica *fila)`
Interface para limpar toda a fila com:
- Confirmação do usuário
- Aviso sobre operação destrutiva
- Liberação completa de memória

### `void menuEstatisticas(FilaDinamica *fila)`
Exibe estatísticas detalhadas da fila:
- Total de tickets
- Prioridade média, máxima e mínima
- Uso de memória estimado
- Detalhes técnicos da implementação

## Aplicações Práticas

### Sistemas de Help Desk
- **Gestão de Tickets**: Fila de solicitações de suporte
- **Priorização**: Tickets com diferentes níveis de urgência
- **Escalonamento**: Ordem de atendimento automática

### Sistemas Operacionais
- **Processos**: Fila de processos aguardando execução
- **Impressão**: Fila de documentos para impressora
- **I/O Buffering**: Buffer de entrada/saída de dados

### Aplicações Web
- **Processamento**: Fila de tarefas em background
- **Notificações**: Fila de mensagens a serem enviadas
- **Cache**: Fila de elementos para limpeza de cache

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Análise de Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| **Inicializar** | O(1) | O(1) |
| **Enqueue** | O(1) | O(1) por elemento |
| **Dequeue** | O(1) | O(1) |
| **Consultar** | O(1) | O(1) |
| **Verificar Vazia** | O(1) | O(1) |
| **Liberar Fila** | O(n) | O(1) |
| **Exibir Fila** | O(n) | O(1) |

## Gestão de Memória

### Alocação
- Cada `enqueue` aloca memória para um novo nó
- Verificação de falha na alocação (`malloc` retorna `NULL`)
- Estrutura cresce dinamicamente conforme necessário

### Liberação
- Cada `dequeue` libera memória do nó removido
- Função `liberarFila()` remove todos os elementos
- Importante chamar antes de encerrar programa

### Boas Práticas
```c
// Sempre verificar retorno do enqueue
if (!enqueue(&fila, ticket)) {
    printf("Erro: Memória insuficiente!\n");
}

// Liberar memória antes de sair
liberarFila(&fila);
```

## Vantagens da Implementação Dinâmica

1. **Escalabilidade**: Cresce conforme necessário
2. **Eficiência**: Usa apenas memória necessária
3. **Flexibilidade**: Sem limite pré-definido
4. **Operações O(1)**: Inserção e remoção eficientes

## Comparação: Fila Estática vs Dinâmica

| Aspecto | Fila Estática | Fila Dinâmica |
|---------|---------------|---------------|
| **Tamanho** | Fixo | Ilimitado* |
| **Memória** | Pré-alocada | Sob demanda |
| **Overhead** | Baixo | Ponteiros extras |
| **Implementação** | Simples | Mais complexa |
| **Falhas** | Overflow | Out of memory |
| **Performance** | Previsível | Dependente do sistema |

*Limitado pela memória disponível do sistema

## Considerações de Implementação

1. **Ponteiros Duplos**: `inicio` e `fim` para operações O(1)
2. **Verificação de NULL**: Sempre verificar ponteiros antes de usar
3. **Atualização Consistente**: Manter `tamanho` sempre correto
4. **Liberação de Memória**: Essencial para evitar vazamentos
5. **Tratamento de Erros**: Verificar falhas de alocação

---

**Desenvolvido como material didático para ensino de Estruturas de Dados em C** 