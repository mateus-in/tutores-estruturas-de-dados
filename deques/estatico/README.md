# Deque Estático em C

## Conceito

Um **Deque** (Double-ended Queue - Fila de Duas Pontas) é uma estrutura de dados linear que permite inserção e remoção de elementos em ambas as extremidades. Combina características de pilhas (LIFO) e filas (FIFO), oferecendo máxima flexibilidade para operações nas extremidades. A implementação estática utiliza um array circular com controle de início e fim.

### Características Principais

- **Dupla Extremidade**: Inserção e remoção no início e no fim
- **Flexibilidade**: Pode funcionar como pilha ou fila
- **Array Circular**: Otimiza o uso do espaço disponível
- **Tamanho Fixo**: Definido em tempo de compilação
- **Operações O(1)**: Todas as operações básicas são constantes

### Vantagens

- **Versatilidade**: Combina pilha e fila em uma estrutura
- **Eficiência**: Operações O(1) em ambas as extremidades
- **Simplicidade**: Implementação direta com array
- **Previsibilidade**: Comportamento determinístico de memória
- **Baixo Overhead**: Não requer ponteiros extras

### Desvantagens

- **Tamanho Limitado**: Não pode exceder o tamanho pré-definido
- **Rigidez**: Tamanho não pode ser alterado durante execução
- **Desperdício Potencial**: Pode reservar mais espaço que necessário

## Estrutura de Dados

### Definição do Elemento (Cliente)
```c
typedef struct {
    int codigo;
    char nome[60];
} Cliente;
```

### Definição do Deque Estático
```c
typedef struct {
    Cliente elementos[MAX_ELEMENTOS];
    int inicio;
    int fim;
    int tamanho;
} DequeEstatico;
```

- `elementos[]`: Array que armazena os dados
- `inicio`: Índice do primeiro elemento
- `fim`: Índice do último elemento
- `tamanho`: Número atual de elementos no deque

## Funcionamento do Array Circular

O deque utiliza **array circular** para maximizar eficiência:

```
Estado Inicial: [_, _, _, _, _, _]  inicio=0, fim=-1, tamanho=0

Inserir A no fim: [A, _, _, _, _, _]  inicio=0, fim=0, tamanho=1
Inserir B no início: [A, _, _, _, _, B]  inicio=5, fim=0, tamanho=2
Inserir C no fim: [A, C, _, _, _, B]  inicio=5, fim=1, tamanho=3

Visualização lógica: B ← A ← C
                     ↑       ↑
                   início   fim
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

#### `void exibirCabecalho(DequeEstatico *deque)`
Exibe cabeçalho com status do deque (VAZIO/PARCIAL/CHEIO) e contador.

### Funções de Manipulação do Deque

#### `void inicializarDeque(DequeEstatico *deque)`
**Descrição**: Inicializa um deque estático vazio.

**Parâmetros**:
- `deque`: Ponteiro para a estrutura do deque

**Funcionamento**: 
- Define `inicio = 0`
- Define `fim = -1` 
- Define `tamanho = 0`

**Complexidade**: O(1)

---

#### `int dequeVazio(DequeEstatico *deque)`
**Descrição**: Verifica se o deque está vazio.

**Retorno**: 
- `1` se vazio (`tamanho == 0`)
- `0` se contém elementos

**Complexidade**: O(1)

---

#### `int dequeCheio(DequeEstatico *deque)`
**Descrição**: Verifica se o deque atingiu capacidade máxima.

**Retorno**: 
- `1` se cheio (`tamanho == MAX_ELEMENTOS`)
- `0` se há espaço disponível

**Complexidade**: O(1)

---

#### `int inserirInicio(DequeEstatico *deque, Cliente elemento)`
**Descrição**: Insere elemento no início do deque.

**Parâmetros**:
- `deque`: Ponteiro para a estrutura do deque
- `elemento`: Cliente a ser inserido

**Retorno**: 
- `1` se inserção bem-sucedida
- `0` se deque cheio

**Funcionamento**: 
1. Verifica se deque está cheio
2. Calcula nova posição do início: `(inicio - 1 + MAX_ELEMENTOS) % MAX_ELEMENTOS`
3. Insere elemento na nova posição
4. Incrementa tamanho

**Complexidade**: O(1)

**Exemplo**:
```c
Cliente c = {101, "João Silva"};
if (inserirInicio(&deque, c)) {
    printf("Cliente inserido no início!\n");
}
```

---

#### `int inserirFim(DequeEstatico *deque, Cliente elemento)`
**Descrição**: Insere elemento no fim do deque.

**Funcionamento**: 
1. Verifica se deque está cheio
2. Calcula nova posição do fim: `(fim + 1) % MAX_ELEMENTOS`
3. Insere elemento na nova posição
4. Incrementa tamanho

**Complexidade**: O(1)

---

#### `Cliente removerInicio(DequeEstatico *deque)`
**Descrição**: Remove elemento do início do deque.

**Retorno**: 
- Cliente removido
- Cliente com código -1 se deque vazio

**Funcionamento**: 
1. Verifica se deque está vazio
2. Salva elemento a ser removido
3. Atualiza início: `(inicio + 1) % MAX_ELEMENTOS`
4. Decrementa tamanho
5. Retorna elemento removido

**Complexidade**: O(1)

---

#### `Cliente removerFim(DequeEstatico *deque)`
**Descrição**: Remove elemento do fim do deque.

**Funcionamento**: 
1. Verifica se deque está vazio
2. Salva elemento a ser removido
3. Atualiza fim: `(fim - 1 + MAX_ELEMENTOS) % MAX_ELEMENTOS`
4. Decrementa tamanho
5. Retorna elemento removido

**Complexidade**: O(1)

---

#### `Cliente consultarInicio(DequeEstatico *deque)`
**Descrição**: Consulta primeiro elemento sem removê-lo.

**Retorno**: Cliente do início ou código -1 se vazio

**Complexidade**: O(1)

---

#### `Cliente consultarFim(DequeEstatico *deque)`
**Descrição**: Consulta último elemento sem removê-lo.

**Retorno**: Cliente do fim ou código -1 se vazio

**Complexidade**: O(1)

## Funções de Interface

### `void exibirMenu(DequeEstatico *deque, int *opcao)`
Exibe menu principal com 9 opções específicas para deque.

### `void menuExibirDeque(DequeEstatico *deque)`
Exibe todos os elementos com indicadores visuais:
- Posição no deque
- Marcadores (I) para início, (F) para fim
- Informações dos extremos
- Contador total

### `void menuInserirInicio(DequeEstatico *deque)`
Interface para inserção no início com validação de deque cheio.

### `void menuInserirFim(DequeEstatico *deque)`
Interface para inserção no fim com validação de deque cheio.

### `void menuRemoverInicio(DequeEstatico *deque)`
Interface para remoção do início mostrando:
- Elemento que será removido
- Confirmação da remoção
- Novo primeiro elemento (se houver)

### `void menuRemoverFim(DequeEstatico *deque)`
Interface para remoção do fim com feedback similar.

### `void menuConsultarInicio(DequeEstatico *deque)`
Interface para consultar primeiro elemento sem remover.

### `void menuConsultarFim(DequeEstatico *deque)`
Interface para consultar último elemento sem remover.

### `void menuLimparDeque(DequeEstatico *deque)`
Interface para limpar todo o deque com confirmação do usuário.

## Aplicações Práticas

### Sistemas de Atendimento
- **Fila Prioritária**: Clientes VIP entram no início
- **Atendimento Flexível**: Remoção de ambas as extremidades
- **Cancelamentos**: Remoção do fim para últimos inseridos

### Algoritmos
- **Busca Bidirecional**: Exploração de ambas as direções
- **Sliding Window**: Janela deslizante em arrays
- **Palindrome Check**: Verificação de palíndromos

### Sistemas de Cache
- **LRU Cache**: Elementos recentes no início
- **Eviction Policy**: Remoção flexível de extremidades

## Compilação e Execução

```bash
gcc -o programa main.c
./programa
```

## Análise de Complexidade

| Operação | Complexidade Temporal | Complexidade Espacial |
|----------|----------------------|----------------------|
| **Inicializar** | O(1) | O(1) |
| **Inserir Início** | O(1) | O(1) |
| **Inserir Fim** | O(1) | O(1) |
| **Remover Início** | O(1) | O(1) |
| **Remover Fim** | O(1) | O(1) |
| **Consultar** | O(1) | O(1) |
| **Verificar Estado** | O(1) | O(1) |
| **Exibir Deque** | O(n) | O(1) |

## Vantagens da Implementação Circular

1. **Reutilização Eficiente**: Posições liberadas são reutilizadas
2. **Operações Simétricas**: Início e fim têm mesma eficiência
3. **Sem Deslocamentos**: Não move elementos desnecessariamente
4. **Aproveitamento Máximo**: Usa todo o espaço do array

## Padrões de Uso

### Como Pilha (LIFO)
```c
// Inserir e remover sempre do mesmo lado
inserirInicio(&deque, elemento);
elemento = removerInicio(&deque);
```

### Como Fila (FIFO)
```c
// Inserir em um lado, remover do outro
inserirFim(&deque, elemento);
elemento = removerInicio(&deque);
```

### Como Deque (Flexível)
```c
// Operações em ambas as extremidades conforme necessário
inserirInicio(&deque, elementoUrgente);
inserirFim(&deque, elementoNormal);
elemento = removerInicio(&deque);  // Processa urgente primeiro
```

## Comparação: Deque vs Outras Estruturas

| Aspecto | Deque | Pilha | Fila | Lista |
|---------|-------|-------|------|-------|
| **Inserção** | Início/Fim | Apenas topo | Apenas fim | Qualquer posição |
| **Remoção** | Início/Fim | Apenas topo | Apenas início | Qualquer posição |
| **Flexibilidade** | Alta | Baixa | Baixa | Muito Alta |
| **Eficiência** | O(1) extremos | O(1) topo | O(1) extremos | O(n) geral |
| **Uso de Memória** | Eficiente | Eficiente | Eficiente | Variável |

## Considerações de Implementação

1. **Aritmética Modular**: Essencial para comportamento circular
2. **Controle de Estado**: Distinção entre vazio e cheio
3. **Validações**: Verificações em todas as operações
4. **Interface Clara**: Indicadores visuais para extremos
5. **Consistência**: Manutenção de invariantes da estrutura

---

**Desenvolvido como material didático para ensino de Estruturas de Dados em C** 