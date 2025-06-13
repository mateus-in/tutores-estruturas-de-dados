#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 5

typedef struct
{
  int id;
  char descricao[50];
} Processo;

typedef struct
{
  Processo elementos[MAX_ELEMENTOS];
  int inicio;
  int fim;
  int tamanho;
} FilaEstatica;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

// FUNÇÕES DA FILA ESTÁTICA
void inicializarFila(FilaEstatica *fila)
{
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
}

int filaVazia(FilaEstatica *fila)
{
  return fila->tamanho == 0;
}

int filaCheia(FilaEstatica *fila)
{
  return fila->tamanho == MAX_ELEMENTOS;
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

void exibirCabecalho(FilaEstatica *fila) {
  int total = fila->tamanho;
  char status[20];
  
  if (filaVazia(fila)) {
    strcpy(status, "VAZIA");
  } else if (filaCheia(fila)) {
    strcpy(status, "CHEIA");
  } else {
    strcpy(status, "PARCIAL");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║         FILA ESTATICA                ║\n");
  printf("║       Sistema de Processos           ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Processos: %d/%d   ║\n", status, total, MAX_ELEMENTOS);
  printf("╚══════════════════════════════════════╝\n\n");
}

int enqueue(FilaEstatica *fila, Processo elemento)
{
  if (filaCheia(fila))
    return 0;

  fila->fim = (fila->fim + 1) % MAX_ELEMENTOS;
  fila->elementos[fila->fim] = elemento;
  fila->tamanho++;

  return 1;
}

Processo dequeue(FilaEstatica *fila)
{
  Processo vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  Processo removido = fila->elementos[fila->inicio];
  fila->inicio = (fila->inicio + 1) % MAX_ELEMENTOS;
  fila->tamanho--;

  return removido;
}

Processo consultarProximo(FilaEstatica *fila)
{
  Processo vazio = {-1, ""};
  
  if (filaVazia(fila))
    return vazio;

  return fila->elementos[fila->inicio];
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(FilaEstatica *fila, int *opcao)
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
  printf("│  0 - Sair                           │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirFila(FilaEstatica *fila) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          FILA DE PROCESSOS           ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (filaVazia(fila)) {
    printf("Fila vazia! Nenhum processo na fila.\n");
  } else {
    printf("┌─────────┬────────────────────────────┐\n");
    printf("│ Posicao │    ID - Descricao          │\n");
    printf("├─────────┼────────────────────────────┤\n");
    
    int atual = fila->inicio;
    for (int i = 0; i < fila->tamanho; i++) {
      int posicao = i + 1;
      printf("│ %7d │ %3d - %-18s │\n", posicao, 
             fila->elementos[atual].id, 
             fila->elementos[atual].descricao);
      atual = (atual + 1) % MAX_ELEMENTOS;
    }
    printf("└─────────┴────────────────────────────┘\n");
    printf("\nTotal na fila: %d/%d processos\n", fila->tamanho, MAX_ELEMENTOS);
    printf("Proximo a ser atendido: %d - %s\n", 
           fila->elementos[fila->inicio].id,
           fila->elementos[fila->inicio].descricao);
  }
  
  pausar();
}

void menuEnqueue(FilaEstatica *fila)
{
  int sucesso;
  Processo novoProcesso;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        ENQUEUE (INSERIR)             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaCheia(fila)) {
    printf("Fila cheia! Nao e possivel inserir novos processos.\n");
    pausar();
    return;
  }

  printf("Digite o ID do processo: ");
  scanf("%d", &novoProcesso.id);

  limparBuffer();

  printf("Digite a descricao do processo: ");
  fgets(novoProcesso.descricao, 50, stdin);

  removerQuebraLinha(novoProcesso.descricao);

  sucesso = enqueue(fila, novoProcesso);

  printf("\n");
  if (sucesso)
    printf("Processo inserido na fila com sucesso!\n");
  else
    printf("Erro ao inserir processo na fila!\n");
    
  pausar();
}

void menuDequeue(FilaEstatica *fila) {
  Processo removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        DEQUEUE (REMOVER)             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila vazia! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Processo a ser removido:\n");
  printf("ID: %d - %s\n\n", fila->elementos[fila->inicio].id, 
                            fila->elementos[fila->inicio].descricao);

  removido = dequeue(fila);

  printf("Processo removido da fila: %d - %s\n", removido.id, removido.descricao);
  
  if (!filaVazia(fila)) {
    printf("Proximo da fila: %d - %s\n", 
           fila->elementos[fila->inicio].id,
           fila->elementos[fila->inicio].descricao);
  } else {
    printf("Fila agora esta vazia.\n");
  }
    
  pausar();
}

void menuConsultarProximo(FilaEstatica *fila) {
  Processo proximo;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        CONSULTAR PROXIMO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (filaVazia(fila)) {
    printf("Fila vazia! Nenhum processo para consultar.\n");
    pausar();
    return;
  }

  proximo = consultarProximo(fila);

  printf("Proximo processo a ser atendido:\n");
  printf("┌─────────────┬────────────────────────┐\n");
  printf("│  ID         │ %-22d │\n", proximo.id);
  printf("│  Descricao  │ %-22s │\n", proximo.descricao);
  printf("│  Posicao    │ Primeiro da fila       │\n");
  printf("└─────────────┴────────────────────────┘\n");
  
  pausar();
}

void menuLimparFila(FilaEstatica *fila) {
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

  printf("ATENCAO: Esta operacao ira remover TODOS os processos da fila!\n");
  printf("Processos na fila: %d\n\n", fila->tamanho);
  
  printf("Tem certeza? (s/N): ");
  limparBuffer();
  scanf("%c", &confirmacao);

  if (confirmacao == 's' || confirmacao == 'S') {
    inicializarFila(fila);
    printf("\nFila limpa com sucesso! Todos os processos foram removidos.\n");
  } else {
    printf("\nOperacao cancelada. Fila mantida inalterada.\n");
  }
    
  pausar();
}

int main()
{
  FilaEstatica fila;
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
      
    case 0:
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
      printf("Por favor, escolha uma opcao valida (0-5).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
} 