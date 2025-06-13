# Pilha Estática em C

## 📚 Conceito Teórico

Uma **Pilha (Stack)** é uma estrutura de dados linear que segue o princípio **LIFO (Last In, First Out)** - o último elemento inserido é o primeiro a ser removido. Imagine uma pilha de pratos: você sempre adiciona e remove pratos do topo da pilha.

A **Pilha Estática** implementa este conceito utilizando um array de tamanho fixo, onde o "topo" da pilha é controlado por um índice que aponta para o último elemento inserido.

### 🔍 Características Principais

- **LIFO (Last In, First Out)**: Último a entrar, primeiro a sair
- **Tamanho Fixo**: Capacidade máxima definida em tempo de compilação
- **Acesso Restrito**: Apenas o elemento do topo pode ser acessado diretamente
- **Operações Fundamentais**: Push (empilhar) e Pop (desempilhar)
- **Memória Contígua**: Elementos armazenados em posições consecutivas

### ⚡ Vantagens

- **Simplicidade**: Implementação direta e fácil compreensão
- **Eficiência**: Operações de inserção e remoção em O(1)
- **Controle de Memória**: Não há necessidade de alocação dinâmica
- **Previsibilidade**: Comportamento determinístico e sem surpresas
- **Cache Friendly**: Elementos contíguos melhoram performance

### ⚠️ Desvantagens

- **Tamanho Limitado**: Não pode exceder a capacidade pré-definida
- **Overflow**: Erro ao tentar empilhar em pilha cheia
- **Underflow**: Erro ao tentar desempilhar de pilha vazia
- **Desperdício de Memória**: Pode reservar mais espaço que necessário
- **Acesso Limitado**: Apenas o topo é acessível

### 🌍 Aplicações Práticas

#### Sistemas de Computação
- **Chamadas de Função**: Stack de execução de funções
- **Recursão**: Controle de chamadas recursivas
- **Compiladores**: Análise sintática e semântica
- **Máquinas Virtuais**: Pilha de operandos (JVM, CLR)

#### Algoritmos
- **Avaliação de Expressões**: Conversão infix para postfix
- **Balanceamento de Parênteses**: Verificação de delimitadores
- **Backtracking**: Labirintos, N-rainhas, Sudoku
- **Algoritmos de Parsing**: Análise de linguagens

#### Estruturas de Dados
- **Implementação de Recursão Iterativa**: Simulação de pilha de chamadas
- **Desfazer/Refazer (Undo/Redo)**: Editores de texto, navegadores
- **Navegação**: Histórico de páginas web, pastas
- **Inversão de Dados**: Strings, arrays, listas

## 🏗️ Estrutura de Dados

### Definição do Elemento (Produto)
```c
typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;
```

### Definição da Pilha Estática
```c
typedef struct {
    Produto elementos[MAX_ELEMENTOS];
    int topo;
} PilhaEstatica;
```

**Campos da Estrutura:**
- `elementos[]`: Array que armazena os dados da pilha
- `topo`: Índice do elemento no topo da pilha (-1 quando vazia)

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

#### `void exibirCabecalho(PilhaEstatica *pilha)`
**Descrição**: Exibe interface visual com status da pilha.
**Informações**: Status (VAZIA/PARCIAL/CHEIA) e contador de elementos

### Funções de Manipulação da Pilha

#### `void inicializarPilha(PilhaEstatica *pilha)`
**Descrição**: Inicializa uma pilha estática vazia.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Funcionamento**: Define `topo = -1`, indicando pilha vazia.

**Complexidade**: O(1)

**Exemplo**:
```c
PilhaEstatica pilha;
inicializarPilha(&pilha);
// pilha.topo = -1 (vazia)
```

---

#### `int pilhaVazia(PilhaEstatica *pilha)`
**Descrição**: Verifica se a pilha está vazia.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- `1` se a pilha estiver vazia (topo == -1)
- `0` se contém elementos

**Funcionamento**: Compara o campo `topo` com -1.

**Complexidade**: O(1)

**Exemplo**:
```c
if (pilhaVazia(&pilha)) {
    printf("Pilha vazia!\n");
}
```

---

#### `int pilhaCheia(PilhaEstatica *pilha)`
**Descrição**: Verifica se a pilha atingiu capacidade máxima.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- `1` se a pilha estiver cheia (topo == MAX_ELEMENTOS - 1)
- `0` se ainda há espaço disponível

**Funcionamento**: Compara o campo `topo` com (MAX_ELEMENTOS - 1).

**Complexidade**: O(1)

**Exemplo**:
```c
if (pilhaCheia(&pilha)) {
    printf("Pilha cheia! Overflow!\n");
}
```

---

#### `int push(PilhaEstatica *pilha, Produto elemento)`
**Descrição**: Empilha (insere) um elemento no topo da pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha
- `elemento`: Produto a ser empilhado

**Retorno**: 
- `1` se a operação foi bem-sucedida
- `0` se a pilha estiver cheia (overflow)

**Funcionamento**: 
1. Verifica se a pilha não está cheia
2. Incrementa o índice `topo`
3. Insere o elemento na posição `topo`

**Complexidade**: O(1)

**Exemplo**:
```c
Produto p = {1, "Notebook", 2500.00};
if (push(&pilha, p)) {
    printf("Produto empilhado com sucesso!\n");
}
```

---

#### `Produto pop(PilhaEstatica *pilha)`
**Descrição**: Desempilha (remove) o elemento do topo da pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Produto removido do topo
- Produto com código -1 se pilha vazia (underflow)

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Salva o elemento do topo
3. Decrementa o índice `topo`
4. Retorna o elemento salvo

**Complexidade**: O(1)

**Exemplo**:
```c
Produto removido = pop(&pilha);
if (removido.codigo != -1) {
    printf("Produto removido: %s\n", removido.nome);
}
```

---

#### `Produto top(PilhaEstatica *pilha)`
**Descrição**: Consulta o elemento do topo sem removê-lo.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Produto do topo da pilha
- Produto com código -1 se pilha vazia

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Retorna o elemento na posição `topo`
3. Não modifica a estrutura da pilha

**Complexidade**: O(1)

**Exemplo**:
```c
Produto topo = top(&pilha);
if (topo.codigo != -1) {
    printf("Topo da pilha: %s\n", topo.nome);
}
```

---

#### `int tamanho(PilhaEstatica *pilha)`
**Descrição**: Retorna o número de elementos na pilha.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Retorno**: 
- Quantidade de elementos (topo + 1)
- 0 se a pilha estiver vazia

**Funcionamento**: Calcula `topo + 1` para obter o total de elementos.

**Complexidade**: O(1)

**Exemplo**:
```c
int total = tamanho(&pilha);
printf("A pilha contém %d elementos\n", total);
```

---

#### `void exibirPilha(PilhaEstatica *pilha)`
**Descrição**: Exibe todos os elementos da pilha do topo para a base.

**Parâmetros**:
- `pilha`: Ponteiro para a estrutura da pilha

**Funcionamento**: 
1. Verifica se a pilha não está vazia
2. Percorre do topo (índice maior) até a base (índice 0)
3. Exibe cada elemento com formatação visual

**Complexidade**: O(n) onde n é o número de elementos

**Exemplo de Saída**:
```
PILHA (Topo → Base):
[2] Produto: Mouse - R$ 45.00
[1] Produto: Teclado - R$ 120.00
[0] Produto: Monitor - R$ 800.00
```

## 📊 Análise de Complexidade

| Operação | Complexidade | Justificativa |
|----------|--------------|---------------|
| Inicializar | O(1) | Apenas define topo = -1 |
| Verificar Vazia | O(1) | Comparação simples |
| Verificar Cheia | O(1) | Comparação simples |
| Push (Empilhar) | O(1) | Acesso direto por índice |
| Pop (Desempilhar) | O(1) | Acesso direto por índice |
| Top (Consultar Topo) | O(1) | Acesso direto por índice |
| Tamanho | O(1) | Cálculo aritmético simples |
| Exibir Pilha | O(n) | Percorre todos os elementos |

## 🔬 Estados da Pilha

### Estado Inicial (Vazia)
```
topo = -1
elementos = [?, ?, ?, ...]
Status: VAZIA
```

### Após push("Monitor")
```
topo = 0
elementos = [Monitor, ?, ?, ...]
Status: PARCIAL
```

### Após push("Teclado")
```
topo = 1
elementos = [Monitor, Teclado, ?, ...]
Status: PARCIAL
```

### Pilha Cheia (MAX_ELEMENTOS = 3)
```
topo = 2
elementos = [Monitor, Teclado, Mouse]
Status: CHEIA
```

### Após pop()
```
topo = 1
elementos = [Monitor, Teclado, Mouse] // Mouse permanece fisicamente
Status: PARCIAL
// Retorna: Mouse
```

## 🚨 Tratamento de Erros

### Stack Overflow
- **Causa**: Tentar empilhar em pilha cheia
- **Prevenção**: Verificar `pilhaCheia()` antes do `push()`
- **Tratamento**: Retornar código de erro e exibir mensagem

### Stack Underflow  
- **Causa**: Tentar desempilhar de pilha vazia
- **Prevenção**: Verificar `pilhaVazia()` antes do `pop()`
- **Tratamento**: Retornar elemento inválido (código -1)

## 🎯 Menu Interativo

O sistema oferece interface amigável com as seguintes opções:

1. **Exibir Pilha**: Mostra todos os elementos do topo à base
2. **Empilhar (Push)**: Adiciona novo produto ao topo
3. **Desempilhar (Pop)**: Remove produto do topo
4. **Consultar Topo**: Visualiza elemento do topo sem remover
5. **Verificar Status**: Mostra se pilha está vazia, cheia ou parcial
6. **Sair**: Encerra o programa

## 📚 Conceitos Relacionados

### Pilha vs Fila
- **Pilha**: LIFO - útil para desfazer operações, recursão
- **Fila**: FIFO - útil para processamento sequencial, scheduling

### Pilha vs Lista
- **Pilha**: Acesso restrito ao topo, operações específicas
- **Lista**: Acesso a qualquer posição, operações genéricas

### Estática vs Dinâmica
- **Estática**: Array fixo, eficiente, limitada em tamanho
- **Dinâmica**: Ponteiros, flexível, overhead de memória

## 🔗 Próximos Passos

Após dominar a Pilha Estática, explore:
1. **Pilha Dinâmica**: Implementação com ponteiros
2. **Fila Estática**: Princípio FIFO com array
3. **Aplicações Avançadas**: Calculadora postfix, parsing de expressões
4. **Otimizações**: Pilha com template, pilha thread-safe 