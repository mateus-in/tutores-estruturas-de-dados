# Deque Dinâmico

## Descrição
Implementação de um **Deque Dinâmico** (Double-ended Queue) em C, utilizando lista duplamente encadeada com alocação dinâmica de memória. Esta estrutura permite inserção e remoção eficiente em ambas as extremidades (início e fim).

## Características da Implementação

### Estruturas de Dados
```c
typedef struct {
  int numero;
  char descricao[80];
} Tarefa;

typedef struct NoDeque {
  Tarefa dados;
  struct NoDeque *anterior;
  struct NoDeque *proximo;
} NoDeque;
```

### Declaração no main()
```c
NoDeque *inicio, *fim;
inicializarDeque(&inicio, &fim);
```

### Funções Principais
- `void inicializarDeque(NoDeque **inicio, NoDeque **fim)` - Inicializa o deque como vazio
- `int dequeVazio(NoDeque **inicio)` - Verifica se o deque está vazio
- `int inserirInicio(NoDeque **inicio, NoDeque **fim, Tarefa elemento)` - Insere no início
- `int inserirFim(NoDeque **inicio, NoDeque **fim, Tarefa elemento)` - Insere no fim
- `Tarefa removerInicio(NoDeque **inicio, NoDeque **fim)` - Remove do início
- `Tarefa removerFim(NoDeque **inicio, NoDeque **fim)` - Remove do fim
- `Tarefa consultarInicio(NoDeque **inicio)` - Consulta o primeiro elemento
- `Tarefa consultarFim(NoDeque **fim)` - Consulta o último elemento
- `void liberarDeque(NoDeque **inicio, NoDeque **fim)` - Libera toda a memória

## Vantagens da Implementação Dinâmica

### ✅ Pontos Positivos
- **Flexibilidade total**: Inserção/remoção eficiente em ambas as extremidades
- **Tamanho dinâmico**: Cresce e diminui conforme necessário
- **Navegação bidirecional**: Permite percorrer em ambas as direções
- **Operações O(1)**: Todas as operações básicas em tempo constante

### ⚠️ Pontos de Atenção
- **Overhead de ponteiros**: Cada nó requer dois ponteiros (anterior e próximo)
- **Complexidade de implementação**: Mais complexo que estruturas simples
- **Gerenciamento de memória**: Necessário controlar alocação/liberação

## Complexidade das Operações

| Operação | Complexidade | Descrição |
|----------|--------------|-----------|
| Inserir Início | O(1) | Inserção no início do deque |
| Inserir Fim | O(1) | Inserção no fim do deque |
| Remover Início | O(1) | Remoção do início do deque |
| Remover Fim | O(1) | Remoção do fim do deque |
| Consultar Extremos | O(1) | Acesso aos elementos das extremidades |
| Busca | O(n) | Busca por elemento específico |
| Espaço | O(n) | Proporcional ao número de elementos |

## Funcionalidades do Menu

1. **Exibir deque** - Mostra todas as tarefas do início ao fim
2. **Inserir no início** - Adiciona nova tarefa no início do deque
3. **Inserir no fim** - Adiciona nova tarefa no fim do deque
4. **Remover do início** - Remove e retorna a primeira tarefa
5. **Remover do fim** - Remove e retorna a última tarefa
6. **Consultar início** - Visualiza a primeira tarefa sem remover
7. **Consultar fim** - Visualiza a última tarefa sem remover
8. **Navegar pelo deque** - Navegação bidirecional interativa
9. **Limpar deque** - Remove todas as tarefas do deque

## Aplicações Práticas

### Sistemas de Processamento
- **Fila de prioridade dupla**: Processamento por ambas as extremidades
- **Buffer circular**: Implementação eficiente de buffers
- **Undo/Redo avançado**: Navegação bidirecional no histórico

### Algoritmos
- **Busca bidirecional**: Algoritmos que exploram ambas as direções
- **Sliding window**: Janela deslizante para análise de dados
- **Palindrome checking**: Verificação de palíndromos

### Estruturas de Dados Avançadas
- **Implementação de outras estruturas**: Base para filas de prioridade
- **Cache LRU**: Least Recently Used com acesso rápido
- **Simulações**: Modelagem de sistemas com entrada/saída dupla

## Exemplo de Uso

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    NoDeque *inicio, *fim;
    Tarefa tarefa1 = {1, "Primeira tarefa"};
    Tarefa tarefa2 = {2, "Segunda tarefa"};
    
    // Inicializar deque
    inicializarDeque(&inicio, &fim);
    
    // Inserir tarefas
    inserirInicio(&inicio, &fim, tarefa1);
    inserirFim(&inicio, &fim, tarefa2);
    
    // Processar tarefas
    while (!dequeVazio(&inicio)) {
        Tarefa atual = removerInicio(&inicio, &fim);
        printf("Processando: %s\n", atual.descricao);
    }
    
    // Liberar memória
    liberarDeque(&inicio, &fim);
    
    return 0;
}
```

## Comparação com Outras Estruturas

| Aspecto | Fila Simples | Pilha | Deque |
|---------|--------------|-------|-------|
| **Inserção** | Apenas no fim | Apenas no topo | Início e fim |
| **Remoção** | Apenas do início | Apenas do topo | Início e fim |
| **Flexibilidade** | Limitada (FIFO) | Limitada (LIFO) | Máxima |
| **Complexidade** | Simples | Simples | Moderada |
| **Uso de memória** | Menor overhead | Menor overhead | Maior overhead |
| **Aplicações** | Processamento sequencial | Recursão, parsing | Algoritmos avançados |

## Detalhes Técnicos

### Gerenciamento de Memória
- Cada nó é alocado individualmente com `malloc()`
- Liberação automática com `free()` durante remoção
- Função `liberarDeque()` garante limpeza completa
- Manutenção de ponteiros `anterior` e `proximo`

### Tratamento de Erros
- Verificação de falha na alocação de memória
- Retorno de valores especiais para operações inválidas
- Validação de deque vazio antes das operações
- Manutenção consistente dos ponteiros de extremidade

### Interface do Usuário
- Menu interativo com navegação intuitiva
- Exibição formatada com bordas ASCII
- Feedback visual para todas as operações
- Navegação bidirecional única entre as estruturas

## Funcionamento Visual

```
Estado Inicial: inicio = NULL, fim = NULL

Após inserirInicio(A):
[A] <-> NULL
↑
inicio/fim

Após inserirFim(B):
[A] <-> [B] <-> NULL
↑       ↑
inicio  fim

Após inserirInicio(C):
[C] <-> [A] <-> [B] <-> NULL
↑               ↑
inicio          fim

Navegação bidirecional:
[C] ←→ [A] ←→ [B]
```

## Funcionalidade Especial: Navegação Bidirecional

O deque dinâmico oferece uma funcionalidade única de navegação interativa:

- **Próximo (→)**: Move para o próximo elemento
- **Anterior (←)**: Move para o elemento anterior
- **Ir para o início**: Salta diretamente para o primeiro elemento
- **Ir para o fim**: Salta diretamente para o último elemento

Esta funcionalidade demonstra a capacidade bidirecional da estrutura, permitindo explorar os dados em ambas as direções de forma intuitiva.

## Compilação e Execução

```bash
# Compilar
gcc -o programa main.c

# Executar
./programa
```

## Estrutura do Código

- **Estruturas de dados**: Definição de Tarefa e NoDeque
- **Funções principais**: Operações básicas do deque
- **Interface**: Funções de menu e interação
- **Navegação**: Sistema único de navegação bidirecional
- **Utilitários**: Funções auxiliares para formatação

Esta implementação demonstra os conceitos fundamentais de deques dinâmicos, oferecendo uma base sólida para compreensão de estruturas de dados bidirecionais e suas aplicações avançadas. 