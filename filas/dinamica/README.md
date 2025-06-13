# Fila Dinâmica

## Descrição
Implementação de uma **Fila Dinâmica** (Dynamic Queue) em C, utilizando lista encadeada simples com alocação dinâmica de memória. Esta estrutura segue o princípio **FIFO** (First In, First Out) - o primeiro elemento inserido é o primeiro a ser removido.

## Características da Implementação

### Estruturas de Dados
```c
typedef struct {
  int prioridade;
  char tarefa[100];
} Ticket;

typedef struct NoFila {
  Ticket dados;
  struct NoFila *proximo;
} NoFila;
```

### Declaração no main()
```c
NoFila *fila;
inicializarFila(&fila);
```

### Funções Principais
- `void inicializarFila(NoFila **fila)` - Inicializa a fila como vazia
- `int filaVazia(NoFila **fila)` - Verifica se a fila está vazia
- `int enqueue(NoFila **fila, Ticket elemento)` - Insere elemento no fim da fila
- `Ticket dequeue(NoFila **fila)` - Remove elemento do início da fila
- `Ticket consultarProximo(NoFila **fila)` - Consulta o próximo elemento sem remover
- `void liberarFila(NoFila **fila)` - Libera toda a memória alocada

## Vantagens da Implementação Dinâmica

### ✅ Pontos Positivos
- **Tamanho flexível**: Cresce e diminui conforme necessário
- **Uso eficiente de memória**: Aloca apenas o necessário
- **Sem limite pré-definido**: Limitado apenas pela memória disponível
- **Inserção/remoção O(1)**: Operações em tempo constante

### ⚠️ Pontos de Atenção
- **Overhead de ponteiros**: Cada nó requer espaço adicional para ponteiros
- **Fragmentação de memória**: Nós podem estar espalhados na memória
- **Gerenciamento manual**: Necessário controlar alocação/liberação

## Complexidade das Operações

| Operação | Complexidade | Descrição |
|----------|--------------|-----------|
| Enqueue | O(1) | Inserção no fim da fila |
| Dequeue | O(1) | Remoção do início da fila |
| Consultar | O(1) | Acesso ao primeiro elemento |
| Busca | O(n) | Busca por elemento específico |
| Espaço | O(n) | Proporcional ao número de elementos |

## Funcionalidades do Menu

1. **Exibir fila** - Mostra todos os tickets na fila com posições
2. **Enqueue (inserir)** - Adiciona novo ticket no fim da fila
3. **Dequeue (remover)** - Remove e retorna o primeiro ticket
4. **Consultar próximo** - Visualiza o próximo ticket sem remover
5. **Limpar fila** - Remove todos os tickets da fila
6. **Estatísticas** - Exibe informações detalhadas sobre a fila

## Aplicações Práticas

### Sistemas de Atendimento
- **Call centers**: Gerenciamento de chamadas em espera
- **Suporte técnico**: Fila de tickets por ordem de chegada
- **Atendimento médico**: Fila de pacientes por chegada

### Processamento de Dados
- **Sistemas operacionais**: Fila de processos para execução
- **Impressão**: Fila de documentos para impressora
- **Redes**: Buffer de pacotes de dados

### Simulações
- **Filas de banco**: Modelagem de atendimento bancário
- **Tráfego**: Simulação de semáforos e congestionamentos
- **Produção**: Linha de montagem e processamento

## Exemplo de Uso

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    NoFila *fila;
    Ticket ticket1 = {1, "Resolver bug crítico"};
    Ticket ticket2 = {2, "Implementar nova feature"};
    
    // Inicializar fila
    inicializarFila(&fila);
    
    // Inserir tickets
    enqueue(&fila, ticket1);
    enqueue(&fila, ticket2);
    
    // Processar tickets
    while (!filaVazia(&fila)) {
        Ticket atual = dequeue(&fila);
        printf("Processando: %s\n", atual.tarefa);
    }
    
    // Liberar memória
    liberarFila(&fila);
    
    return 0;
}
```

## Comparação: Fila Estática vs Dinâmica

| Aspecto | Fila Estática | Fila Dinâmica |
|---------|---------------|---------------|
| **Tamanho** | Fixo (definido em tempo de compilação) | Flexível (cresce/diminui dinamicamente) |
| **Memória** | Alocada no stack | Alocada no heap |
| **Performance** | Acesso mais rápido | Overhead de alocação |
| **Flexibilidade** | Limitada pelo tamanho máximo | Limitada apenas pela memória disponível |
| **Complexidade** | Implementação mais simples | Gerenciamento de ponteiros |
| **Uso de memória** | Pode desperdiçar espaço | Usa apenas o necessário |

## Detalhes Técnicos

### Gerenciamento de Memória
- Cada nó é alocado individualmente com `malloc()`
- Liberação automática com `free()` durante remoção
- Função `liberarFila()` garante limpeza completa

### Tratamento de Erros
- Verificação de falha na alocação de memória
- Retorno de valores especiais para operações inválidas
- Validação de fila vazia antes das operações

### Interface do Usuário
- Menu interativo com navegação intuitiva
- Exibição formatada com bordas ASCII
- Feedback visual para todas as operações
- Estatísticas detalhadas da fila

## Compilação e Execução

```bash
# Compilar
gcc -o programa main.c

# Executar
./programa
```

## Estrutura do Código

- **Estruturas de dados**: Definição de Ticket e NoFila
- **Funções principais**: Operações básicas da fila
- **Interface**: Funções de menu e interação
- **Utilitários**: Funções auxiliares para formatação

Esta implementação demonstra os conceitos fundamentais de filas dinâmicas, oferecendo uma base sólida para compreensão e extensão da estrutura de dados. 