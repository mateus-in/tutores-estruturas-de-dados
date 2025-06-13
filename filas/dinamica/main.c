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
void inicializarFila(NoFila **fila)
{
  *fila = NULL;
}

int filaVazia(NoFila **fila)
{
  return *fila == NULL;
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

int contarElementos(NoFila **fila) {
  if (filaVazia(fila)) {
    return 0;
  }

  NoFila *aux = *fila;
  int contador = 0;
  
  while (aux != NULL) {
    contador++;
    aux = aux->proximo;
  }
  
  return contador;
}

void exibirCabecalho(NoFila **fila) {
  int total = contarElementos(fila);
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

NoFila* encontrarUltimo(NoFila **fila) {
  if (filaVazia(fila)) {
    return NULL;
  }
  
  NoFila *aux = *fila;
  while (aux->proximo != NULL) {
    aux = aux->proximo;
  }
  
  return aux;
}

int enqueue(NoFila **fila, Ticket elemento)
{
  NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->proximo = NULL;

  if (filaVazia(fila)) {
    *fila = novoNo;
  } else {
    NoFila *ultimo = encontrarUltimo(fila);
    ultimo->proximo = novoNo;
  }

  return 1;
}

Ticket dequeue(NoFila **fila)
{
  Ticket vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  NoFila *noRemover = *fila;
  Ticket dadosRemovidos = noRemover->dados;

  *fila = (*fila)->proximo;
  free(noRemover);

  return dadosRemovidos;
}

Ticket consultarProximo(NoFila **fila)
{
  Ticket vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  return (*fila)->dados;
}

void liberarFila(NoFila **fila)
{
  while (!filaVazia(fila)) {
    dequeue(fila);
  }
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(NoFila **fila, int *opcao)
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

void menuExibirFila(NoFila **fila) {
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
    
    NoFila *atual = *fila;
    int posicao = 1;
    
    while (atual != NULL) {
      printf("│ %7d │ %10d │ %-21s │\n", posicao, 
             atual->dados.prioridade, 
             atual->dados.tarefa);
      atual = atual->proximo;
      posicao++;
    }
    printf("└─────────┴────────────┴───────────────────────┘\n");
    printf("\nTotal na fila: %d tickets\n", contarElementos(fila));
    printf("Proximo a ser atendido: Prioridade %d - %s\n", 
           (*fila)->dados.prioridade,
           (*fila)->dados.tarefa);
  }
  
  pausar();
}

void menuEnqueue(NoFila **fila)
{
  int sucesso;
  Ticket novoTicket;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         INSERIR TICKET               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite a prioridade do ticket: ");
  scanf("%d", &novoTicket.prioridade);
  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novoTicket.tarefa, sizeof(novoTicket.tarefa), stdin);
  removerQuebraLinha(novoTicket.tarefa);

  sucesso = enqueue(fila, novoTicket);

  if (sucesso) {
    printf("\n✅ Ticket inserido com sucesso!\n");
    printf("   Prioridade: %d\n", novoTicket.prioridade);
    printf("   Tarefa: %s\n", novoTicket.tarefa);
  } else {
    printf("\n❌ Erro ao inserir ticket! Memoria insuficiente.\n");
  }

  pausar();
}

void menuDequeue(NoFila **fila) {
  Ticket removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         REMOVER TICKET               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("❌ Fila vazia! Nenhum ticket para remover.\n");
  } else {
    printf("Ticket a ser removido:\n");
    printf("┌────────────┬───────────────────────┐\n");
    printf("│ Prioridade │       Tarefa          │\n");
    printf("├────────────┼───────────────────────┤\n");
    printf("│ %10d │ %-21s │\n", 
           (*fila)->dados.prioridade,
           (*fila)->dados.tarefa);
    printf("└────────────┴───────────────────────┘\n\n");

    removido = dequeue(fila);

    if (removido.prioridade != -1) {
      printf("✅ Ticket removido com sucesso!\n");
      printf("   Prioridade: %d\n", removido.prioridade);
      printf("   Tarefa: %s\n", removido.tarefa);
    }
  }

  pausar();
}

void menuConsultarProximo(NoFila **fila) {
  Ticket proximo;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       CONSULTAR PROXIMO              ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("❌ Fila vazia! Nenhum ticket na fila.\n");
  } else {
    proximo = consultarProximo(fila);
    
    printf("Proximo ticket a ser atendido:\n");
    printf("┌────────────┬───────────────────────┐\n");
    printf("│ Prioridade │       Tarefa          │\n");
    printf("├────────────┼───────────────────────┤\n");
    printf("│ %10d │ %-21s │\n", 
           proximo.prioridade,
           proximo.tarefa);
    printf("└────────────┴───────────────────────┘\n");
    
    printf("\n📋 Este ticket sera o proximo a ser processado.\n");
  }

  pausar();
}

void menuLimparFila(NoFila **fila) {
  int confirmacao;
  int totalAntes = contarElementos(fila);

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          LIMPAR FILA                 ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("❌ A fila ja esta vazia!\n");
  } else {
    printf("⚠️  ATENÇÃO: Esta operacao ira remover TODOS os %d tickets da fila!\n", totalAntes);
    printf("   Esta acao nao pode ser desfeita.\n\n");
    printf("Deseja realmente limpar a fila? (1-Sim / 0-Nao): ");
    scanf("%d", &confirmacao);

    if (confirmacao == 1) {
      liberarFila(fila);
      printf("\n✅ Fila limpa com sucesso!\n");
      printf("   %d tickets foram removidos.\n", totalAntes);
    } else {
      printf("\n❌ Operacao cancelada. Fila mantida.\n");
    }
  }

  pausar();
}

void menuEstatisticas(NoFila **fila) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         ESTATISTICAS                 ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  int total = contarElementos(fila);
  
  if (filaVazia(fila)) {
    printf("📊 ESTATISTICAS DA FILA:\n");
    printf("┌─────────────────────────┬─────────┐\n");
    printf("│ Total de tickets        │   %5d │\n", total);
    printf("│ Status                  │   VAZIA │\n");
    printf("│ Memoria utilizada       │   0 KB  │\n");
    printf("└─────────────────────────┴─────────┘\n");
  } else {
    // Calcular estatísticas de prioridade
    int prioridadeMin = (*fila)->dados.prioridade;
    int prioridadeMax = (*fila)->dados.prioridade;
    int somaPrioridades = 0;
    
    NoFila *atual = *fila;
    while (atual != NULL) {
      if (atual->dados.prioridade < prioridadeMin) {
        prioridadeMin = atual->dados.prioridade;
      }
      if (atual->dados.prioridade > prioridadeMax) {
        prioridadeMax = atual->dados.prioridade;
      }
      somaPrioridades += atual->dados.prioridade;
      atual = atual->proximo;
    }
    
    float mediaPrioridade = (float)somaPrioridades / total;
    int memoriaKB = (total * sizeof(NoFila)) / 1024;
    if (memoriaKB == 0) memoriaKB = 1; // Mínimo 1KB
    
    printf("📊 ESTATISTICAS DA FILA:\n");
    printf("┌─────────────────────────┬─────────┐\n");
    printf("│ Total de tickets        │   %5d │\n", total);
    printf("│ Status                  │   ATIVA │\n");
    printf("│ Prioridade minima       │   %5d │\n", prioridadeMin);
    printf("│ Prioridade maxima       │   %5d │\n", prioridadeMax);
    printf("│ Prioridade media        │   %5.1f │\n", mediaPrioridade);
    printf("│ Memoria utilizada       │ %4d KB │\n", memoriaKB);
    printf("└─────────────────────────┴─────────┘\n");
    
    printf("\n🎯 PROXIMO TICKET:\n");
    printf("   Prioridade: %d\n", (*fila)->dados.prioridade);
    printf("   Tarefa: %s\n", (*fila)->dados.tarefa);
  }

  pausar();
}

int main()
{
  NoFila *fila;
  int opcao;

  inicializarFila(&fila);

  do {
    exibirMenu(&fila, &opcao);

    switch (opcao) {
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
        printf("\n👋 Encerrando o programa...\n");
        liberarFila(&fila);
        printf("✅ Memoria liberada com sucesso!\n");
        break;
      default:
        printf("\n❌ Opcao invalida! Tente novamente.\n");
        pausar();
        break;
    }
  } while (opcao != 0);

  return 0;
} 