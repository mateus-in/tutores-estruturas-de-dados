#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  int prioridade;
  char tarefa[100];
} Ticket;

typedef struct NoFila
{
  Ticket dados;
  struct NoFila *proximo;
} NoFila;

typedef struct
{
  NoFila *inicio;
  NoFila *fim;
  int tamanho;
} FilaDinamica;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

// FUNÇÕES DA FILA DINÂMICA
void inicializarFila(FilaDinamica *fila)
{
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;
}

int filaVazia(FilaDinamica *fila)
{
  return fila->inicio == NULL;
}

// FUNÇÕES AUXILIARES PARA INTERFACE
void limparTela() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void pausar() {
  printf("\nPressione ENTER para continuar...");
  limparBuffer();
  getchar();
}

void exibirCabecalho(FilaDinamica *fila) {
  int total = fila->tamanho;
  char status[20];
  
  if (filaVazia(fila)) {
    strcpy(status, "VAZIA");
  } else {
    strcpy(status, "ATIVA");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║         FILA DINAMICA                ║\n");
  printf("║       Sistema de Tickets             ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Tickets: %-9d║\n", status, total);
  printf("╚══════════════════════════════════════╝\n\n");
}

int enqueue(FilaDinamica *fila, Ticket elemento)
{
  NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->proximo = NULL;

  if (filaVazia(fila)) {
    fila->inicio = novoNo;
    fila->fim = novoNo;
  } else {
    fila->fim->proximo = novoNo;
    fila->fim = novoNo;
  }

  fila->tamanho++;
  return 1;
}

Ticket dequeue(FilaDinamica *fila)
{
  Ticket vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  NoFila *noRemover = fila->inicio;
  Ticket dadosRemovidos = noRemover->dados;

  fila->inicio = fila->inicio->proximo;
  
  if (fila->inicio == NULL) {
    fila->fim = NULL; // Fila ficou vazia
  }

  free(noRemover);
  fila->tamanho--;

  return dadosRemovidos;
}

Ticket consultarProximo(FilaDinamica *fila)
{
  Ticket vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  return fila->inicio->dados;
}

void liberarFila(FilaDinamica *fila)
{
  while (!filaVazia(fila)) {
    dequeue(fila);
  }
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(FilaDinamica *fila, int *opcao)
{
  limparTela();
  exibirCabecalho(fila);
  
  printf("┌──────────────────────────────────────┐\n");
  printf("│                MENU                  │\n");
  printf("├──────────────────────────────────────┤\n");
  printf("│  1 - Exibir fila                    │\n");
  printf("│  2 - Enqueue (inserir)              │\n");
  printf("│  3 - Dequeue (remover)              │\n");
  printf("│  4 - Consultar proximo              │\n");
  printf("│  5 - Limpar fila                    │\n");
  printf("│  6 - Estatisticas                   │\n");
  printf("│  0 - Sair                           │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirFila(FilaDinamica *fila) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          FILA DE TICKETS             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (filaVazia(fila)) {
    printf("Fila vazia! Nenhum ticket na fila.\n");
  } else {
    printf("┌─────────┬────────────┬───────────────────────┐\n");
    printf("│ Posicao │ Prioridade │       Tarefa          │\n");
    printf("├─────────┼────────────┼───────────────────────┤\n");
    
    NoFila *atual = fila->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
      printf("│ %7d │ %10d │ %-21s │\n", posicao, 
             atual->dados.prioridade, 
             atual->dados.tarefa);
      atual = atual->proximo;
      posicao++;
    }
    printf("└─────────┴────────────┴───────────────────────┘\n");
    printf("\nTotal na fila: %d tickets\n", fila->tamanho);
    printf("Proximo a ser atendido: Prioridade %d - %s\n", 
           fila->inicio->dados.prioridade,
           fila->inicio->dados.tarefa);
  }
  
  pausar();
}

void menuEnqueue(FilaDinamica *fila)
{
  int sucesso;
  Ticket novoTicket;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        ENQUEUE (INSERIR)             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite a prioridade do ticket (1-10): ");
  scanf("%d", &novoTicket.prioridade);

  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novoTicket.tarefa, 100, stdin);

  removerQuebraLinha(novoTicket.tarefa);

  sucesso = enqueue(fila, novoTicket);

  printf("\n");
  if (sucesso)
    printf("Ticket inserido na fila com sucesso!\n");
  else
    printf("Erro ao inserir ticket na fila! (Memoria insuficiente)\n");
    
  pausar();
}

void menuDequeue(FilaDinamica *fila) {
  Ticket removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        DEQUEUE (REMOVER)             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila vazia! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Ticket a ser removido:\n");
  printf("Prioridade: %d - %s\n\n", fila->inicio->dados.prioridade, 
                                    fila->inicio->dados.tarefa);

  removido = dequeue(fila);

  printf("Ticket removido da fila: Prioridade %d - %s\n", 
         removido.prioridade, removido.tarefa);
  
  if (!filaVazia(fila)) {
    printf("Proximo da fila: Prioridade %d - %s\n", 
           fila->inicio->dados.prioridade,
           fila->inicio->dados.tarefa);
  } else {
    printf("Fila agora esta vazia.\n");
  }
    
  pausar();
}

void menuConsultarProximo(FilaDinamica *fila) {
  Ticket proximo;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        CONSULTAR PROXIMO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila vazia! Nenhum ticket para consultar.\n");
    pausar();
    return;
  }

  proximo = consultarProximo(fila);

  printf("Proximo ticket a ser atendido:\n");
  printf("┌─────────────┬──────────────────────────┐\n");
  printf("│  Prioridade │ %-24d │\n", proximo.prioridade);
  printf("│  Tarefa     │ %-24s │\n", proximo.tarefa);
  printf("│  Posicao    │ Primeiro da fila         │\n");
  printf("└─────────────┴──────────────────────────┘\n");
  
  pausar();
}

void menuLimparFila(FilaDinamica *fila) {
  char confirmacao;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          LIMPAR FILA                 ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila ja esta vazia!\n");
    pausar();
    return;
  }

  printf("ATENCAO: Esta operacao ira remover TODOS os tickets da fila!\n");
  printf("Tickets na fila: %d\n\n", fila->tamanho);
  
  printf("Tem certeza? (s/N): ");
  limparBuffer();
  scanf("%c", &confirmacao);

  if (confirmacao == 's' || confirmacao == 'S') {
    liberarFila(fila);
    printf("\nFila limpa com sucesso! Todos os tickets foram removidos.\n");
  } else {
    printf("\nOperacao cancelada. Fila mantida inalterada.\n");
  }
    
  pausar();
}

void menuEstatisticas(FilaDinamica *fila) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         ESTATISTICAS                 ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila vazia! Nenhuma estatistica disponivel.\n");
    pausar();
    return;
  }

  // Calcular estatísticas
  int totalTickets = fila->tamanho;
  int somaprioridades = 0;
  int prioridadeMax = fila->inicio->dados.prioridade;
  int prioridadeMin = fila->inicio->dados.prioridade;
  
  NoFila *atual = fila->inicio;
  while (atual != NULL) {
    somaprioridades += atual->dados.prioridade;
    if (atual->dados.prioridade > prioridadeMax) {
      prioridadeMax = atual->dados.prioridade;
    }
    if (atual->dados.prioridade < prioridadeMin) {
      prioridadeMin = atual->dados.prioridade;
    }
    atual = atual->proximo;
  }
  
  float mediaPrioridade = (float)somaprioridades / totalTickets;
  
  printf("┌─────────────────────┬─────────────┐\n");
  printf("│ Total de Tickets    │ %11d │\n", totalTickets);
  printf("│ Prioridade Media    │ %11.1f │\n", mediaPrioridade);
  printf("│ Prioridade Maxima   │ %11d │\n", prioridadeMax);
  printf("│ Prioridade Minima   │ %11d │\n", prioridadeMin);
  printf("│ Memoria Utilizada   │ %8d KB │\n", totalTickets * (int)sizeof(NoFila) / 1024 + 1);
  printf("└─────────────────────┴─────────────┘\n");
  
  printf("\nDetalhes da estrutura:\n");
  printf("- Cada no ocupa %zu bytes\n", sizeof(NoFila));
  printf("- Memoria total estimada: %zu bytes\n", totalTickets * sizeof(NoFila));
  printf("- Fila implementada como lista encadeada\n");
  printf("- Crescimento dinamico de memoria\n");
  
  pausar();
}

int main()
{
  FilaDinamica fila;
  int opcao;

  inicializarFila(&fila);

  do
  {
    exibirMenu(&fila, &opcao);

    switch (opcao)
    {
    case 1:
      menuExibirFila(&fila);
      break;

    case 2:
      menuEnqueue(&fila);
      break;

    case 3:
      menuDequeue(&fila);
      break;

    case 4:
      menuConsultarProximo(&fila);
      break;

    case 5:
      menuLimparFila(&fila);
      break;
      
    case 6:
      menuEstatisticas(&fila);
      break;
      
    case 0:
      liberarFila(&fila); // Liberar memoria antes de sair
      limparTela();
      printf("╔══════════════════════════════════════╗\n");
      printf("║         ATE A PROXIMA!               ║\n");
      printf("║                                      ║\n");
      printf("║    Obrigado por usar o sistema!      ║\n");
      printf("╚══════════════════════════════════════╝\n\n");
      break;

    default:
      limparTela();
      printf("╔══════════════════════════════════════╗\n");
      printf("║          OPCAO INVALIDA!             ║\n");
      printf("╚══════════════════════════════════════╝\n\n");
      printf("Por favor, escolha uma opcao valida (0-6).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
} 