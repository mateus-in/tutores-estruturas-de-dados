# Pilha Dinâmica

## Descrição
Implementação de uma **Pilha Dinâmica** (Dynamic Stack) em C, utilizando lista encadeada simples com alocação dinâmica de memória. Esta estrutura segue o princípio **LIFO** (Last In, First Out) - o último elemento inserido é o primeiro a ser removido.

## Características da Implementação

### Estruturas de Dados
```c
typedef struct {
    int isbn;
    char titulo[100];
    char autor[50];
    int paginas;
} Livro;

typedef struct no {
    Livro info;
    struct no *proximo;
} No;
```

### Declaração no main()
```c
No *pilha;
inicializarPilha(&pilha);
```

### Funções Principais
- `void inicializarPilha(No **pilha)` - Inicializa a pilha como vazia
- `int pilhaVazia(No **pilha)` - Verifica se a pilha está vazia
- `int push(No **pilha, Livro elemento)` - Empilha elemento no topo
- `Livro pop(No **pilha)` - Desempilha elemento do topo
- `Livro top(No **pilha)` - Consulta o elemento do topo sem remover
- `void liberarPilha(No **pilha)` - Libera toda a memória alocada

## Vantagens da Implementação Dinâmica

### ✅ Pontos Positivos
- **Tamanho flexível**: Cresce e diminui conforme necessário
- **Uso eficiente de memória**: Aloca apenas o necessário
- **Sem limite pré-definido**: Limitado apenas pela memória disponível
- **Operações O(1)**: Push, pop e top em tempo constante

### ⚠️ Pontos de Atenção
- **Overhead de ponteiros**: Cada nó requer espaço adicional para ponteiros
- **Fragmentação de memória**: Nós podem estar espalhados na memória
- **Gerenciamento manual**: Necessário controlar alocação/liberação

## Complexidade das Operações

| Operação | Complexidade | Descrição |
|----------|--------------|-----------|
| Push | O(1) | Inserção no topo da pilha |
| Pop | O(1) | Remoção do topo da pilha |
| Top | O(1) | Acesso ao elemento do topo |
| Busca | O(n) | Busca por elemento específico |
| Espaço | O(n) | Proporcional ao número de elementos |

## Funcionalidades do Menu

1. **Exibir pilha** - Mostra todos os livros empilhados (topo → base)
2. **Empilhar (Push)** - Adiciona novo livro no topo da pilha
3. **Desempilhar (Pop)** - Remove e retorna o livro do topo
4. **Consultar topo** - Visualiza o livro do topo sem remover
5. **Verificar se está vazia** - Verifica o status da pilha
6. **Consultar tamanho** - Exibe estatísticas detalhadas
7. **Liberar pilha** - Remove todos os livros da pilha

## Aplicações Práticas

### Sistemas de Controle
- **Undo/Redo**: Histórico de operações em editores
- **Navegação**: Histórico de páginas em navegadores
- **Chamadas de função**: Stack de execução em programas

### Processamento de Dados
- **Parsing**: Análise de expressões matemáticas
- **Compiladores**: Análise sintática e semântica
- **Algoritmos**: Busca em profundidade (DFS)

### Estruturas Auxiliares
- **Validação**: Verificação de parênteses balanceados
- **Conversão**: Notação infixa para pós-fixa
- **Recursão**: Simulação de chamadas recursivas

## Exemplo de Uso

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    No *pilha;
    Livro livro1 = {123, "Estruturas de Dados", "Cormen", 1200};
    Livro livro2 = {456, "Algoritmos", "Sedgewick", 800};
    
    // Inicializar pilha
    inicializarPilha(&pilha);
    
    // Empilhar livros
    push(&pilha, livro1);
    push(&pilha, livro2);
    
    // Processar livros (LIFO)
    while (!pilhaVazia(&pilha)) {
        Livro atual = pop(&pilha);
        printf("Processando: %s\n", atual.titulo);
    }
    
    // Liberar memória
    liberarPilha(&pilha);
    
    return 0;
}
```

## Comparação: Pilha Estática vs Dinâmica

| Aspecto | Pilha Estática | Pilha Dinâmica |
|---------|----------------|----------------|
| **Tamanho** | Fixo (definido em tempo de compilação) | Flexível (cresce/diminui dinamicamente) |
| **Memória** | Alocada no stack | Alocada no heap |
| **Performance** | Acesso mais rápido | Overhead de alocação |
| **Flexibilidade** | Limitada pelo tamanho máximo | Limitada apenas pela memória disponível |
| **Complexidade** | Implementação mais simples | Gerenciamento de ponteiros |
| **Uso de memória** | Pode desperdiçar espaço | Usa apenas o necessário |

## Detalhes Técnicos

### Gerenciamento de Memória
- Cada nó é alocado individualmente com `malloc()`
- Liberação automática com `free()` durante pop
- Função `liberarPilha()` garante limpeza completa

### Tratamento de Erros
- Verificação de falha na alocação de memória
- Retorno de valores especiais para operações inválidas
- Validação de pilha vazia antes das operações

### Interface do Usuário
- Menu interativo com navegação intuitiva
- Exibição formatada com bordas ASCII
- Feedback visual para todas as operações
- Estatísticas detalhadas da pilha

## Funcionamento Visual

```
Estado Inicial: pilha = NULL

Após push(A):
[A] -> NULL
↑
topo

Após push(B):
[B] -> [A] -> NULL
↑
topo

Após push(C):
[C] -> [B] -> [A] -> NULL
↑
topo

Após pop():
[B] -> [A] -> NULL
↑
topo
```

## Compilação e Execução

```bash
# Compilar
gcc -o programa main.c

# Executar
./programa
```

## Estrutura do Código

- **Estruturas de dados**: Definição de Livro e No
- **Funções principais**: Operações básicas da pilha
- **Interface**: Funções de menu e interação
- **Utilitários**: Funções auxiliares para formatação

Esta implementação demonstra os conceitos fundamentais de pilhas dinâmicas, oferecendo uma base sólida para compreensão e extensão da estrutura de dados. 