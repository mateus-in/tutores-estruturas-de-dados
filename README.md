# Tutoriais - Estruturas de Dados em C

Este repositório contém implementações completas e didáticas de estruturas de dados fundamentais em linguagem C. Cada estrutura possui interface de usuário amigável, documentação detalhada e código bem comentado.

## Estruturas Implementadas

### 1. Lista Estática
Uma estrutura de dados de tamanho fixo que armazena elementos em posições contíguas de memória.

**Características:**
- Tamanho fixo definido em tempo de compilação
- Acesso direto por índice
- Inserção e remoção com deslocamento de elementos
- Sistema de gerenciamento de alunos

**Documentação:** [Lista Estática](listas/estatica/README.md)

**Arquivo:** `listas/estatica/main.c`

---

### 2. Lista Encadeada
Uma estrutura dinâmica onde elementos são conectados através de ponteiros.

**Características:**
- Tamanho dinâmico (limitado apenas pela memória)
- Alocação dinâmica com malloc/free
- Inserção eficiente no início e fim
- Sistema de gerenciamento de jogadores

**Documentação:** [Lista Encadeada](listas/encadeada/README.md)

**Arquivo:** `listas/encadeada/main.c`

---

### 3. Lista Encadeada Ordenada
Variação da lista encadeada que mantém elementos automaticamente ordenados.

**Características:**
- Inserção automática na posição correta
- Sempre mantém elementos em ordem alfabética
- Otimizações de busca aproveitando a ordenação
- Sistema de gerenciamento de jogadores ordenados

**Documentação:** [Lista Encadeada Ordenada](listas/encadeada-ordenada/README.md)

**Arquivo:** `listas/encadeada-ordenada/main.c`

---

### 4. Lista Duplamente Encadeada
Uma estrutura dinâmica onde cada elemento possui ponteiros para o próximo e para o anterior.

**Características:**
- Navegação bidirecional (frente e trás)
- Dois ponteiros por nó (ante e prox)
- Operações simétricas de inserção/remoção
- Remoção mais eficiente (não precisa buscar anterior)
- Sistema de gerenciamento de jogadores

**Documentação:** [Lista Duplamente Encadeada](listas/duplamente-encadeada/README.md)

**Arquivo:** `listas/duplamente-encadeada/main.c`

---

## Filas (Queues)

### 5. Fila Estática
Uma estrutura de dados FIFO (First In, First Out) implementada com array circular.

**Características:**
- Princípio FIFO: primeiro a entrar, primeiro a sair
- Implementação circular para otimizar uso do array
- Tamanho fixo definido em tempo de compilação
- Operações de enqueue (inserir) e dequeue (remover)
- Sistema de gerenciamento de processos

**Documentação:** [Fila Estática](filas/estatica/README.md)

**Arquivo:** `filas/estatica/main.c`

---

### 6. Fila Dinâmica
Uma estrutura FIFO implementada com lista encadeada, sem limitação de tamanho.

**Características:**
- Crescimento dinâmico conforme demanda
- Gestão automática de memória
- Ponteiros para início e fim para operações O(1)
- Estatísticas de uso de memória
- Sistema de gerenciamento de tickets

**Documentação:** [Fila Dinâmica](filas/dinamica/README.md)

**Arquivo:** `filas/dinamica/main.c`

---

## Funcionalidades Comuns

Todas as implementações incluem:

### Interface de Usuario
- Menu interativo com navegação clara
- Limpeza de tela automática
- Status da estrutura no cabeçalho
- Pausas para visualização de resultados
- Tratamento de entrada com validações

### Operações Básicas
- Inserção de elementos
- Remoção de elementos
- Busca/Pesquisa
- Exibição formatada
- Contagem de elementos

### Qualidade de Código
- Código bem estruturado e comentado
- Funções auxiliares para interface
- Tratamento de erros
- Gerenciamento adequado de memória
- Portabilidade entre sistemas

## Como Compilar e Executar

### Pré-requisitos
- Compilador GCC
- Sistema operacional compatível (Windows, Linux, macOS)

### Compilação Individual
Para compilar qualquer uma das estruturas:

```bash
# Lista Estática
cd listas/estatica
gcc -o programa main.c
./programa

# Lista Encadeada
cd listas/encadeada
gcc -o programa main.c
./programa

# Lista Encadeada Ordenada
cd listas/encadeada-ordenada
gcc -o programa main.c
./programa

# Lista Duplamente Encadeada
cd listas/duplamente-encadeada
gcc -o programa main.c
./programa

# Fila Estática
cd filas/estatica
gcc -o programa main.c
./programa

# Fila Dinâmica
cd filas/dinamica
gcc -o programa main.c
./programa
```

### Compilação com Make (Opcional)
```bash
# Para criar um Makefile personalizado
make lista-estatica
make lista-encadeada
make lista-ordenada
make lista-duplamente
```

## Estrutura do Projeto

```
tutores-estruturas-de-dados/
├── README.md                     # Este arquivo
├── listas/
│   ├── estatica/
│   │   ├── main.c               # Implementação da lista estática
│   │   └── README.md            # Documentação detalhada
│   ├── encadeada/
│   │   ├── main.c               # Implementação da lista encadeada
│   │   └── README.md            # Documentação detalhada
│   ├── encadeada-ordenada/
│   │   ├── main.c               # Implementação da lista ordenada
│   │   └── README.md            # Documentação detalhada
│   └── duplamente-encadeada/
│       ├── main.c               # Implementação da lista duplamente encadeada
│       └── README.md            # Documentação detalhada
├── filas/
│   ├── estatica/
│   │   ├── main.c               # Implementação da fila estática
│   │   └── README.md            # Documentação detalhada
│   └── dinamica/
│       ├── main.c               # Implementação da fila dinâmica
│       └── README.md            # Documentação detalhada
```

## Características Técnicas

### Lista Estática
- **Elemento:** Aluno (matrícula + nome)
- **Tamanho:** 3 elementos (configurável)
- **Operações:** Inserir por posição/fim, remover por posição, modificar, pesquisar

### Lista Encadeada
- **Elemento:** Jogador (número da camisa + nome)
- **Tamanho:** Dinâmico
- **Operações:** Inserir início/fim, remover início/fim, pesquisar, remover específico

### Lista Encadeada Ordenada
- **Elemento:** Jogador (número da camisa + nome)
- **Ordenação:** Alfabética por nome
- **Operações:** Inserir ordenado, remover início/fim, pesquisar, remover específico

### Lista Duplamente Encadeada
- **Elemento:** Jogador (número da camisa + nome)
- **Navegação:** Bidirecional (ante + prox)
- **Operações:** Inserir início/fim, remover início/fim, pesquisar, remover específico

### Fila Estática
- **Elemento:** Processo (ID + descrição)
- **Princípio:** FIFO (First In, First Out)
- **Implementação:** Array circular
- **Operações:** Enqueue (inserir fim), dequeue (remover início), consultar próximo

### Fila Dinâmica
- **Elemento:** Ticket (prioridade + tarefa)
- **Princípio:** FIFO (First In, First Out)
- **Implementação:** Lista encadeada
- **Operações:** Enqueue (inserir fim), dequeue (remover início), estatísticas

## Conceitos Abordados

### Gerenciamento de Memória
- Alocação estática (lista estática)
- Alocação dinâmica (listas encadeadas)
- Liberação adequada de memória
- Prevenção de vazamentos

### Algoritmos
- Inserção com deslocamento
- Inserção ordenada
- Busca linear
- Remoção com reorganização

### Estruturas de Dados
- Arrays e ponteiros
- Estruturas (structs)
- Ponteiros para estruturas
- Encadeamento de nós
- Filas e princípio FIFO
- Arrays circulares

## Objetivos Educacionais

Este projeto foi desenvolvido para:

1. **Ensinar conceitos fundamentais** de estruturas de dados
2. **Demonstrar diferentes abordagens** para o mesmo problema
3. **Mostrar trade-offs** entre diferentes implementações
4. **Fornecer código limpo e bem documentado** para estudo
5. **Incluir interface prática** para teste das implementações

## Comparação entre Estruturas

| Aspecto | Lista Estática | Lista Encadeada | Lista Ordenada | Lista Dupla | Fila Estática | Fila Dinâmica |
|---------|---------------|-----------------|----------------|-------------|---------------|---------------|
| **Tamanho** | Fixo | Dinâmico | Dinâmico | Dinâmico | Fixo | Dinâmico |
| **Memória** | Contígua | Fragmentada | Fragmentada | Fragmentada | Contígua | Fragmentada |
| **Navegação** | Índice | Unidirecional | Unidirecional | Bidirecional | FIFO apenas | FIFO apenas |
| **Inserção** | O(n) | O(1)/O(n) | O(n) | O(1)/O(n) | O(1) | O(1) |
| **Remoção** | O(n) | O(1)/O(n) | O(1)/O(n) | O(1)/O(n) | O(1) | O(1) |
| **Busca** | O(n) | O(n) | O(n)* | O(n) | N/A | N/A |
| **Ordenação** | Manual | Manual | Automática | Manual | N/A | N/A |
| **Acesso** | Qualquer | Sequencial | Sequencial | Sequencial | Extremidades | Extremidades |
| **Complexidade** | Baixa | Média | Alta | Alta | Baixa | Média |

*Pode terminar antes devido à ordenação  
N/A = Não aplicável (filas permitem acesso apenas às extremidades)

## Contribuições

Este projeto é educacional e pode ser usado como:
- Material de estudo para estruturas de dados
- Base para projetos mais complexos
- Referência para implementações em C
- Exercícios práticos de programação

## Licença

Este projeto é de domínio público e pode ser usado livremente para fins educacionais.

---

**Desenvolvido como material didático para ensino de Estruturas de Dados em C** 