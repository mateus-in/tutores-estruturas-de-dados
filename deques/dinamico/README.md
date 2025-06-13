# Deque Dinâmico em C

## Conceito

Um **Deque Dinâmico** (Double-ended Queue) é uma estrutura de dados linear que permite inserção e remoção eficiente em ambas as extremidades, implementada através de lista duplamente encadeada. Oferece máxima flexibilidade combinando características de pilhas e filas, sem limitações de tamanho pré-definido.

### Características Principais

- **Dupla Extremidade**: Inserção e remoção no início e no fim
- **Lista Duplamente Encadeada**: Cada nó possui ponteiros anterior e próximo
- **Tamanho Dinâmico**: Cresce e diminui conforme necessário
- **Navegação Bidirecional**: Permite percorrer em ambas as direções
- **Operações O(1)**: Todas as operações nas extremidades são constantes

### Vantagens

- **Flexibilidade Total**: Sem limitações de tamanho
- **Eficiência de Memória**: Usa apenas o espaço necessário
- **Navegação Bidirecional**: Percorre em qualquer direção
- **Operações Simétricas**: Início e fim têm mesma eficiência
- **Versatilidade**: Funciona como pilha, fila ou deque

### Desvantagens

- **Overhead de Ponteiros**: Dois ponteiros por nó
- **Fragmentação de Memória**: Nós espalhados na memória
- **Complexidade**: Implementação mais complexa
- **Gerenciamento de Memória**: Risco de vazamentos se mal implementada

## Estrutura de Dados

### Definição do Elemento (Tarefa)
```c
typedef struct {
    int numero;
    char descricao[80];
} Tarefa;
```

### Definição do Nó do Deque
```c
typedef struct NoDeque {
    Tarefa dados;
    struct NoDeque *anterior;
    struct NoDeque *proximo;
} NoDeque;
```

### Definição do Deque Dinâmico
```c
typedef struct {
    NoDeque *inicio;
    NoDeque *fim;
    int tamanho;
} DequeDinamico;
```

- `inicio`: Ponteiro para o primeiro nó
- `fim`: Ponteiro para o último nó
- `tamanho`: Contador de elementos no deque

## Funcionamento Visual

```
Estado Inicial: inicio = NULL, fim = NULL, tamanho = 0

Inserir A no fim:
[A] ⟷ NULL
↑
inicio/fim

Inserir B no início:
[B] ⟷ [A] ⟷ NULL
↑      ↑
inicio fim

Inserir C no fim:
[B] ⟷ [A] ⟷ [C] ⟷ NULL
↑             ↑
inicio        fim

Navegação bidirecional:
← [B] ⟷ [A] ⟷ [C] →
```

## Funções Implementadas

### Funções Auxiliares

#### `void limparBuffer()`
Remove caracteres residuais do buffer de entrada.

#### `void removerQuebraLinha(char *str)`
Remove o caractere de quebra de linha de uma string.

#### `void limparTela()`
Limpa a tela do terminal de forma multiplataforma.

#### `void pausar()`
Pausa a execução aguardando ENTER do usuário.

#### `void exibirCabecalho(DequeDinamico *deque)`
Exibe cabeçalho com status do deque (VAZIO/ATIVO) e contador de tarefas.

### Funções de Manipulação do Deque

#### `void inicializarDeque(DequeDinamico *deque)`
**Descrição**: Inicializa um deque dinâmico vazio.

**Parâmetros**:
- `deque`: Ponteiro para a estrutura do deque

**Funcionamento**: 
- Define `inicio = NULL`
- Define `fim = NULL` 
- Define `tamanho = 0`

**Complexidade**: O(1)

---

#### `int dequeVazio(DequeDinamico *deque)`
**Descrição**: Verifica se o deque está vazio.

**Retorno**: 
- `1` se vazio (`inicio == NULL`)
- `0` se contém elementos

**Complexidade**: O(1)

---

#### `int inserirInicio(DequeDinamico *deque, Tarefa elemento)`
**Descrição**: Insere elemento no início do deque.

**Parâmetros**:
- `deque`: Ponteiro para a estrutura do deque
- `elemento`: Tarefa a ser inserida

**Retorno**: 
- `1` se inserção bem-sucedida
- `0` se falha na alocação de memória

**Funcionamento**: 
1. Aloca memória para novo nó
2. Verifica se alocação foi bem-sucedida
3. Define dados e `anterior = NULL`
4. Se deque vazio: `inicio` e `fim` apontam para novo nó
5. Se não vazio: liga novo nó ao início atual e atualiza ponteiros
6. Incrementa tamanho

**Complexidade**: O(1)

**Exemplo**:
```c
Tarefa t = {101, "Implementar função"};
if (inserirInicio(&deque, t)) {
    printf("Tarefa inserida no início!\n");
} else {
    printf("Erro: Memória insuficiente!\n");
}
```

---

#### `int inserirFim(DequeDinamico *deque, Tarefa elemento)`
**Descrição**: Insere elemento no fim do deque.

**Funcionamento**: 
1. Aloca memória para novo nó
2. Define dados e `proximo = NULL`
3. Se deque vazio: `inicio` e `fim` apontam para novo nó
4. Se não vazio: liga novo nó ao fim atual e atualiza ponteiros
5. Incrementa tamanho

**Complexidade**: O(1)

---

#### `Tarefa removerInicio(DequeDinamico *deque)`
**Descrição**: Remove elemento do início do deque.

**Retorno**: 
- Tarefa removida
- Tarefa com número -1 se deque vazio

**Funcionamento**: 
1. Verifica se deque está vazio
2. Salva dados do nó a ser removido
3. Se único elemento: `inicio` e `fim` = NULL
4. Se múltiplos: atualiza `inicio` e ajusta ponteiro `anterior`
5. Libera memória do nó removido
6. Decrementa tamanho
7. Retorna dados removidos

**Complexidade**: O(1)

---

#### `Tarefa removerFim(DequeDinamico *deque)`
**Descrição**: Remove elemento do fim do deque.

**Funcionamento**: Similar ao `removerInicio`, mas opera no fim da lista.

**Complexidade**: O(1)

---

#### `Tarefa consultarInicio(DequeDinamico *deque)`
**Descrição**: Consulta primeiro elemento sem removê-lo.

**Retorno**: Tarefa do início ou número -1 se vazio

**Complexidade**: O(1)

---

#### `Tarefa consultarFim(DequeDinamico *deque)`
**Descrição**: Consulta último elemento sem removê-lo.

**Retorno**: Tarefa do fim ou número -1 se vazio

**Complexidade**: O(1)

---

#### `void liberarDeque(DequeDinamico *deque)`
**Descrição**: Remove todos os elementos, liberando toda a memória.

**Funcionamento**: 
1. Chama `removerInicio()` repetidamente até deque ficar vazio
2. Cada chamada libera a memória de um nó

**Complexidade**: O(n), onde n é o número de elementos

## Funções de Interface

### `void exibirMenu(DequeDinamico *deque, int *opcao)`
Exibe menu principal com 10 opções específicas para deque dinâmico.

### `void menuExibirDeque(DequeDinamico *deque)`
Exibe todos os elementos com indicadores visuais:
- Posição no deque
- Marcadores (I) para início, (F) para fim
- Informações dos extremos
- Contador total

### `void menuInserirInicio(DequeDinamico *deque)`
Interface para inserção no início com tratamento de falha de alocação.

### `void menuInserirFim(DequeDinamico *deque)`
Interface para inserção no fim com validação de memória.

### `void menuRemoverInicio(DequeDinamico *deque)`
Interface para remoção do início mostrando:
- Elemento que será removido
- Confirmação da remoção
- Novo primeiro elemento (se houver)

### `void menuRemoverFim(DequeDinamico *deque)`
Interface para remoção do fim com feedback similar.

### `void menuConsultarInicio(DequeDinamico *deque)`
Interface para consultar primeiro elemento sem remover.

### `void menuConsultarFim(DequeDinamico *deque)`
Interface para consultar último elemento sem remover.

### `void menuNavegarDeque(DequeDinamico *deque)`
**Funcionalidade Especial**: Interface de navegação bidirecional que permite:
- Navegar para elemento anterior/próximo
- Saltar para início/fim
- Visualizar elemento atual com contexto
- Demonstrar capacidade de navegação da lista duplamente encadeada

### `void menuLimparDeque(DequeDinamico *deque)`
Interface para limpar todo o deque com:
- Confirmação do usuário
- Liberação completa de memória
- Feedback sobre operação

## Aplicações Práticas

### Editores de Texto
- **Undo/Redo**: Operações em ambas as extremidades
- **Navegação**: Movimento bidirecional no histórico
- **Buffer Circular**: Gerenciamento eficiente de comandos

### Sistemas de Cache
- **LRU Cache**: Elementos recentes no início
- **Eviction Policy**: Remoção flexível de extremidades
- **Hit/Miss Tracking**: Movimentação eficiente de elementos

### Algoritmos de Grafos
- **BFS Bidirecional**: Busca de ambas as extremidades
- **Pathfinding**: Exploração em múltiplas direções
- **Sliding Window**: Janela deslizante otimizada

### Sistemas de Tarefas
- **Priorização Dinâmica**: Tarefas urgentes no início
- **Processamento Flexível**: Remoção de qualquer extremidade
- **Cancelamento**: Remoção eficiente de tarefas

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Análise de Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| **Inicializar** | O(1) | O(1) |
| **Inserir Início** | O(1) | O(1) por elemento |
| **Inserir Fim** | O(1) | O(1) por elemento |
| **Remover Início** | O(1) | O(1) |
| **Remover Fim** | O(1) | O(1) |
| **Consultar** | O(1) | O(1) |
| **Navegar** | O(1) por movimento | O(1) |
| **Liberar Deque** | O(n) | O(1) |
| **Exibir Deque** | O(n) | O(1) |

## Gestão de Memória

### Alocação
- Cada inserção aloca memória para um novo nó
- Verificação de falha na alocação (`malloc` retorna `NULL`)
- Estrutura cresce dinamicamente conforme necessário

### Liberação
- Cada remoção libera memória do nó removido
- Função `liberarDeque()` remove todos os elementos
- Importante chamar antes de encerrar programa

### Boas Práticas
```c
// Sempre verificar retorno das inserções
if (!inserirInicio(&deque, tarefa)) {
    printf("Erro: Memória insuficiente!\n");
}

// Liberar memória antes de sair
liberarDeque(&deque);
```

## Vantagens da Lista Duplamente Encadeada

1. **Navegação Bidirecional**: Movimento em qualquer direção
2. **Remoção Eficiente**: Não precisa buscar nó anterior
3. **Operações Simétricas**: Início e fim têm mesma complexidade
4. **Flexibilidade Máxima**: Suporte completo para deque

## Comparação: Deque Estático vs Dinâmico

| Aspecto | Deque Estático | Deque Dinâmico |
|---------|----------------|----------------|
| **Tamanho** | Fixo | Ilimitado* |
| **Memória** | Pré-alocada | Sob demanda |
| **Navegação** | Índices | Ponteiros |
| **Overhead** | Baixo | Ponteiros extras |
| **Implementação** | Simples | Mais complexa |
| **Falhas** | Overflow | Out of memory |
| **Performance** | Previsível | Dependente do sistema |

*Limitado pela memória disponível do sistema

## Padrões de Uso Avançados

### Deque como Buffer Circular
```c
// Inserir no fim, remover do início (FIFO)
inserirFim(&deque, novaTarefa);
tarefa = removerInicio(&deque);
```

### Deque como Pilha Dupla
```c
// Duas pilhas em uma estrutura
inserirInicio(&deque, tarefaA);  // Pilha A
inserirFim(&deque, tarefaB);     // Pilha B
tarefaA = removerInicio(&deque); // Pop A
tarefaB = removerFim(&deque);    // Pop B
```

### Processamento Bidirecional
```c
// Processar de ambas as extremidades
while (!dequeVazio(&deque)) {
    if (condicaoA) {
        tarefa = removerInicio(&deque);
    } else {
        tarefa = removerFim(&deque);
    }
    processar(tarefa);
}
```

## Considerações de Implementação

1. **Ponteiros Duplos**: Manutenção cuidadosa de `anterior` e `proximo`
2. **Casos Especiais**: Tratamento de deque vazio e único elemento
3. **Liberação de Memória**: Essencial para evitar vazamentos
4. **Verificação de NULL**: Sempre verificar ponteiros antes de usar
5. **Navegação Segura**: Validação de limites na navegação

---

**Desenvolvido como material didático para ensino de Estruturas de Dados em C** 