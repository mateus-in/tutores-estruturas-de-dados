# Pilha Dinâmica em C

## 📚 Conceito Teórico

Uma **Pilha Dinâmica (Stack)** é uma estrutura de dados linear que segue o princípio **LIFO (Last In, First Out)**, implementada através de uma lista encadeada. Ao contrário da pilha estática, a pilha dinâmica cresce e diminui conforme necessário, limitada apenas pela memória disponível do sistema.

Cada elemento da pilha é um **nó** que contém os dados e um ponteiro para o nó anterior (ou próximo), formando uma cadeia encadeada onde apenas o **topo** é acessível diretamente.

### 🔍 Características Principais

- **LIFO (Last In, First Out)**: Último a entrar, primeiro a sair
- **Tamanho Flexível**: Cresce e diminui dinamicamente durante execução
- **Alocação Dinâmica**: Usa `malloc()` e `free()` para gerenciar memória
- **Acesso Restrito**: Apenas o elemento do topo pode ser acessado diretamente
- **Ponteiros**: Cada nó aponta para o elemento anterior da pilha

### ⚡ Vantagens

- **Flexibilidade de Tamanho**: Não há limite pré-definido de elementos
- **Uso Eficiente de Memória**: Aloca apenas o necessário
- **Crescimento Dinâmico**: Adapta-se às necessidades do programa
- **Operações Eficientes**: Push e Pop em O(1)
- **Sem Desperdício**: Não reserva memória desnecessária

### ⚠️ Desvantagens

- **Overhead de Memória**: Cada nó precisa armazenar um ponteiro adicional
- **Fragmentação**: Nós podem estar espalhados pela memória
- **Complexidade**: Mais complexa de implementar que versão estática
- **Gerenciamento de Memória**: Risco de memory leaks se mal implementada
- **Performance**: Ligeiramente mais lenta devido à alocação dinâmica

### 🆚 Comparação: Estática vs Dinâmica

| Aspecto | Pilha Estática | Pilha Dinâmica |
|---------|----------------|----------------|
| **Tamanho** | Fixo (definido em compilação) | Flexível (limitado pela RAM) |
| **Memória** | Array contíguo | Nós espalhados (fragmentação) |
| **Alocação** | Automática (stack) | Manual (heap) |
| **Overflow** | Possível quando cheia | Raramente (apenas sem RAM) |
| **Performance** | Mais rápida | Ligeiramente mais lenta |
| **Complexidade** | Simples | Moderada |
| **Cache** | Cache-friendly | Cache menos eficiente |
| **Implementação** | Direta | Requer gerenciamento de ponteiros |

### 🌍 Aplicações Práticas

#### Sistemas com Requisitos Variáveis
- **Parsers de Linguagens**: Tamanho da pilha varia com complexidade
- **Navegadores Web**: Histórico de páginas de tamanho indefinido
- **Jogos**: Sistema de undo/redo com muitas operações
- **Editores de Texto**: Pilha de operações para desfazer

#### Algoritmos Avançados
- **Backtracking Complexo**: Problemas com espaço de busca variável
- **Avaliação de Expressões**: Expressões de tamanho indeterminado
- **Simulação de Recursão**: Quando recursão pode ser muito profunda
- **Máquinas de Estado**: Estados com pilhas de contexto

## 🏗️ Estrutura de Dados

### Definição do Elemento (Livro)
```c
typedef struct {
    int isbn;
    char titulo[100];
    char autor[50];
    int paginas;
} Livro;
```

### Definição do Nó da Pilha
```c
typedef struct no {
    Livro info;
    struct no *proximo;
} No;
```

### Definição da Pilha Dinâmica
```c
typedef struct {
    No *topo;
    int tamanho;
} PilhaDinamica;
```

**Campos da Estrutura:**
- `topo`: Ponteiro para o nó no topo da pilha (NULL quando vazia)
- `tamanho`: Contador de elementos para eficiência (opcional)

## 🔧 Funções Implementadas

### Funções Auxiliares

#### `void limparBuffer()`
**Descrição**: Remove caracteres residuais do buffer de entrada.
**Uso**: Evita problemas na leitura sequencial de dados.

#### `void removerQuebraLinha(char *str)`
**Descrição**: Remove o caractere '\n' de strings lidas com `fgets()`.
**Parâmetros**: `str` - string a ser processada

#### `void limparTela()`
**Descrição**: Limpa a tela do terminal de forma multiplataforma.
**Compatibilidade**: Windows (`cls`) e Unix/Linux (`clear`)

#### `void pausar()`
**Descrição**: Pausa a execução aguardando input do usuário.
**Uso**: Permite visualizar resultados antes de continuar

#### `void exibirCabecalho(PilhaDinamica *pilha)`
**Descrição**: Exibe interface visual com status da pilha.
**Informações**: Status (VAZIA/COM DADOS) e contador de elementos

### Funções de Manipulação da Pilha

#### `void inicializarPilha(PilhaDinamica *pilha)`
**Descrição**: Inicializa uma pilha dinâmica vazia.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Funcionamento**: Define `topo = NULL` e `tamanho = 0`.

**Complexidade**: O(1)

**Exemplo**:
```c
PilhaDinamica pilha;
inicializarPilha(&pilha);
// pilha.topo = NULL, pilha.tamanho = 0
```

---

#### `int pilhaVazia(PilhaDinamica *pilha)`
**Descrição**: Verifica se a pilha está vazia.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- `1` se a pilha estiver vazia (topo == NULL)
- `0` se contém elementos

**Funcionamento**: Verifica se o ponteiro `topo` é NULL.

**Complexidade**: O(1)

**Exemplo**:
```c
if (pilhaVazia(&pilha)) {
    printf("Pilha vazia!\n");
}
```

---

#### `No* criarNo(Livro elemento)`
**Descrição**: Cria um novo nó dinamicamente.

**Parâmetros**:
- `elemento`: Livro a ser armazenado no nó

**Retorno**: 
- Ponteiro para o novo nó criado
- NULL se falha na alocação de memória

**Funcionamento**: 
1. Aloca memória com `malloc()`
2. Inicializa os campos do nó
3. Define o ponteiro `proximo` como NULL

**Complexidade**: O(1)

**Exemplo**:
```c
Livro livro = {12345, "1984", "George Orwell", 328};
No *novo = criarNo(livro);
if (novo == NULL) {
    printf("Erro de alocação!\n");
}
```

---

#### `int push(PilhaDinamica *pilha, Livro elemento)`
**Descrição**: Empilha (insere) um elemento no topo da pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha
- `elemento`: Livro a ser empilhado

**Retorno**: 
- `1` se a operação foi bem-sucedida
- `0` se falha na alocação de memória

**Funcionamento**: 
1. Cria um novo nó
2. O novo nó aponta para o antigo topo
3. Atualiza o topo para o novo nó
4. Incrementa o contador de tamanho

**Complexidade**: O(1)

**Exemplo**:
```c
Livro livro = {54321, "Dom Casmurro", "Machado de Assis", 256};
if (push(&pilha, livro)) {
    printf("Livro empilhado com sucesso!\n");
}
```

---

#### `Livro pop(PilhaDinamica *pilha)`
**Descrição**: Desempilha (remove) o elemento do topo da pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Livro removido do topo
- Livro com ISBN -1 se pilha vazia (underflow)

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Salva os dados do topo
3. Atualiza o topo para o próximo nó
4. Libera a memória do nó removido
5. Decrementa o contador e retorna os dados

**Complexidade**: O(1)

**Exemplo**:
```c
Livro removido = pop(&pilha);
if (removido.isbn != -1) {
    printf("Livro removido: %s\n", removido.titulo);
}
```

---

#### `Livro top(PilhaDinamica *pilha)`
**Descrição**: Consulta o elemento do topo sem removê-lo.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Livro do topo da pilha
- Livro com ISBN -1 se pilha vazia

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Retorna uma cópia dos dados do topo
3. Não modifica a estrutura da pilha

**Complexidade**: O(1)

**Exemplo**:
```c
Livro topo = top(&pilha);
if (topo.isbn != -1) {
    printf("Topo da pilha: %s\n", topo.titulo);
}
```

---

#### `int tamanho(PilhaDinamica *pilha)`
**Descrição**: Retorna o número de elementos na pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Quantidade de elementos
- 0 se a pilha estiver vazia

**Funcionamento**: Retorna o campo `tamanho` mantido pela estrutura.

**Complexidade**: O(1) - com contador | O(n) - sem contador

**Exemplo**:
```c
int total = tamanho(&pilha);
printf("A pilha contém %d livros\n", total);
```

---

#### `void exibirPilha(PilhaDinamica *pilha)`
**Descrição**: Exibe todos os elementos da pilha do topo para a base.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Percorre a lista encadeada do topo até a base
3. Exibe cada elemento com formatação visual
4. Mostra a direção do encadeamento

**Complexidade**: O(n) onde n é o número de elementos

**Exemplo de Saída**:
```
PILHA DINÂMICA (Topo → Base):
┌─────────────────────────────────────────────┐
│ Topo → [1984] - George Orwell (328 pág.)   │
│    ↓   [Dom Casmurro] - Machado (256 pág.) │
│    ↓   [O Cortiço] - Aluísio (304 pág.)    │
└─────────────────────────────────────────────┘
```

---

#### `void liberarPilha(PilhaDinamica *pilha)`
**Descrição**: Libera toda a memória alocada pela pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Funcionamento**: 
1. Percorre todos os nós da pilha
2. Libera a memória de cada nó usando `free()`
3. Reinicializa a pilha como vazia

**Complexidade**: O(n) onde n é o número de elementos

**Uso Obrigatório**: Deve ser chamada antes do programa terminar para evitar memory leaks.

**Exemplo**:
```c
liberarPilha(&pilha);
printf("Pilha liberada da memória\n");
```

## 📊 Análise de Complexidade

| Operação | Complexidade | Justificativa |
|----------|--------------|---------------|
| Inicializar | O(1) | Define ponteiros como NULL |
| Verificar Vazia | O(1) | Comparação simples de ponteiro |
| Criar Nó | O(1) | Alocação dinâmica de memória |
| Push (Empilhar) | O(1) | Inserção sempre no início |
| Pop (Desempilhar) | O(1) | Remoção sempre do início |
| Top (Consultar Topo) | O(1) | Acesso direto ao primeiro nó |
| Tamanho | O(1)* | *Se mantido contador |
| Exibir Pilha | O(n) | Percorre todos os nós |
| Liberar Pilha | O(n) | Libera todos os nós |

## 🔬 Estados da Pilha

### Estado Inicial (Vazia)
```
pilha.topo = NULL
pilha.tamanho = 0
Memória: (nenhuma alocação)
```

### Após push("1984")
```
pilha.topo → [1984] → NULL
pilha.tamanho = 1
Memória: 1 nó alocado
```

### Após push("Dom Casmurro")
```
pilha.topo → [Dom Casmurro] → [1984] → NULL
pilha.tamanho = 2
Memória: 2 nós alocados
```

### Após pop()
```
pilha.topo → [1984] → NULL
pilha.tamanho = 1
Memória: 1 nó alocado (Dom Casmurro foi liberado)
Retorna: Dom Casmurro
```

## 🚨 Tratamento de Erros

### Memory Allocation Failure
- **Causa**: Sistema sem memória disponível
- **Prevenção**: Verificar retorno de `malloc()`
- **Tratamento**: Retornar código de erro e mensagem

### Stack Underflow  
- **Causa**: Tentar desempilhar de pilha vazia
- **Prevenção**: Verificar `pilhaVazia()` antes do `pop()`
- **Tratamento**: Retornar elemento inválido (ISBN -1)

### Memory Leaks
- **Causa**: Não liberar nós removidos
- **Prevenção**: Sempre usar `free()` após remoção
- **Tratamento**: Implementar `liberarPilha()` ao finalizar

## 🔄 Gerenciamento de Memória

### Alocação Responsável
```c
No *novo = malloc(sizeof(No));
if (novo == NULL) {
    printf("Erro: Memória insuficiente!\n");
    return 0; // Falha
}
```

### Liberação Correta
```c
No *removido = pilha->topo;
pilha->topo = pilha->topo->proximo;
free(removido); // ESSENCIAL para evitar memory leak
```

### Cleanup Completo
```c
void liberarPilha(PilhaDinamica *pilha) {
    while (!pilhaVazia(pilha)) {
        pop(pilha); // Pop já faz o free() interno
    }
}
```

## 🎯 Menu Interativo

O sistema oferece interface amigável com as seguintes opções:

1. **Exibir Pilha**: Mostra todos os livros do topo à base
2. **Empilhar (Push)**: Adiciona novo livro ao topo
3. **Desempilhar (Pop)**: Remove livro do topo
4. **Consultar Topo**: Visualiza livro do topo sem remover
5. **Verificar se Vazia**: Mostra status da pilha
6. **Consultar Tamanho**: Estatísticas detalhadas
7. **Liberar Pilha**: Remove todos os elementos
8. **Sair**: Encerra o programa (com cleanup automático)

## 📚 Conceitos Relacionados

### Pilha Dinâmica vs Lista Encadeada
- **Pilha**: Acesso restrito ao topo, operações específicas (LIFO)
- **Lista**: Acesso a qualquer posição, operações genéricas

### Gerenciamento de Memória
- **Stack**: Memória automática, rápida, limitada
- **Heap**: Memória dinâmica, flexível, requer gerenciamento

### Padrões de Projeto
- **RAII**: Resource Acquisition Is Initialization
- **Exception Safety**: Garantir limpeza mesmo com erros
- **Memory Pool**: Otimização para alocações frequentes

## 🔗 Próximos Passos

Após dominar a Pilha Dinâmica, explore:
1. **Fila Estática**: Princípio FIFO com array circular
2. **Fila Dinâmica**: FIFO com lista encadeada
3. **Deque**: Double-ended queue para inserção/remoção em ambas extremidades
4. **Otimizações Avançadas**: Pool de memória, smart pointers 