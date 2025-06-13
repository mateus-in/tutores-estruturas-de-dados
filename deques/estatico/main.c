#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 6

typedef struct
{
  int codigo;
  char nome[60];
} Cliente;

typedef struct
{
  Cliente elementos[MAX_ELEMENTOS];
  int inicio;
  int fim;
  int tamanho;
} DequeEstatico;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

// FUNÇÕES DO DEQUE ESTÁTICO
void inicializarDeque(DequeEstatico *deque)
{
  deque->inicio = 0;
  deque->fim = -1;
  deque->tamanho = 0;
}

int dequeVazio(DequeEstatico *deque)
{
  return deque->tamanho == 0;
}

int dequeCheio(DequeEstatico *deque)
{
  return deque->tamanho == MAX_ELEMENTOS;
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

void exibirCabecalho(DequeEstatico *deque) {
  int total = deque->tamanho;
  char status[20];
  
  if (dequeVazio(deque)) {
    strcpy(status, "VAZIO");
  } else if (dequeCheio(deque)) {
    strcpy(status, "CHEIO");
  } else {
    strcpy(status, "PARCIAL");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║         DEQUE ESTATICO               ║\n");
  printf("║       Sistema de Clientes            ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Clientes: %d/%d   ║\n", status, total, MAX_ELEMENTOS);
  printf("╚══════════════════════════════════════╝\n\n");
}

int inserirInicio(DequeEstatico *deque, Cliente elemento)
{
  if (dequeCheio(deque))
    return 0;

  deque->inicio = (deque->inicio - 1 + MAX_ELEMENTOS) % MAX_ELEMENTOS;
  deque->elementos[deque->inicio] = elemento;
  deque->tamanho++;

  return 1;
}

int inserirFim(DequeEstatico *deque, Cliente elemento)
{
  if (dequeCheio(deque))
    return 0;

  deque->fim = (deque->fim + 1) % MAX_ELEMENTOS;
  deque->elementos[deque->fim] = elemento;
  deque->tamanho++;

  return 1;
}

Cliente removerInicio(DequeEstatico *deque)
{
  Cliente vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  Cliente removido = deque->elementos[deque->inicio];
  deque->inicio = (deque->inicio + 1) % MAX_ELEMENTOS;
  deque->tamanho--;

  return removido;
}

Cliente removerFim(DequeEstatico *deque)
{
  Cliente vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  Cliente removido = deque->elementos[deque->fim];
  deque->fim = (deque->fim - 1 + MAX_ELEMENTOS) % MAX_ELEMENTOS;
  deque->tamanho--;

  return removido;
}

Cliente consultarInicio(DequeEstatico *deque)
{
  Cliente vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  return deque->elementos[deque->inicio];
}

Cliente consultarFim(DequeEstatico *deque)
{
  Cliente vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  return deque->elementos[deque->fim];
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(DequeEstatico *deque, int *opcao)
{
  limparTela();
  exibirCabecalho(deque);
  
  printf("┌──────────────────────────────────────┐\n");
  printf("│                MENU                  │\n");
  printf("├──────────────────────────────────────┤\n");
  printf("│  1 - Exibir deque                   │\n");
  printf("│  2 - Inserir no inicio              │\n");
  printf("│  3 - Inserir no fim                 │\n");
  printf("│  4 - Remover do inicio              │\n");
  printf("│  5 - Remover do fim                 │\n");
  printf("│  6 - Consultar inicio               │\n");
  printf("│  7 - Consultar fim                  │\n");
  printf("│  8 - Limpar deque                   │\n");
  printf("│  0 - Sair                           │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirDeque(DequeEstatico *deque) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          DEQUE DE CLIENTES           ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhum cliente no deque.\n");
  } else {
    printf("┌─────────┬─────────┬──────────────────────┐\n");
    printf("│ Posicao │ Codigo  │        Nome          │\n");
    printf("├─────────┼─────────┼──────────────────────┤\n");
    
    int atual = deque->inicio;
    for (int i = 0; i < deque->tamanho; i++) {
      int posicao = i + 1;
      char indicador[10] = "";
      
      if (i == 0 && i == deque->tamanho - 1) {
        strcpy(indicador, " (I/F)");
      } else if (i == 0) {
        strcpy(indicador, " (I)");
      } else if (i == deque->tamanho - 1) {
        strcpy(indicador, " (F)");
      }
      
      printf("│ %5d%s │ %7d │ %-20s │\n", posicao, indicador,
             deque->elementos[atual].codigo, 
             deque->elementos[atual].nome);
      atual = (atual + 1) % MAX_ELEMENTOS;
    }
    printf("└─────────┴─────────┴──────────────────────┘\n");
    printf("\nTotal no deque: %d/%d clientes\n", deque->tamanho, MAX_ELEMENTOS);
    printf("Legenda: (I) = Inicio, (F) = Fim\n");
    
    if (deque->tamanho > 0) {
      printf("\nExtremos do deque:\n");
      printf("- Inicio: %d - %s\n", 
             deque->elementos[deque->inicio].codigo,
             deque->elementos[deque->inicio].nome);
      printf("- Fim: %d - %s\n", 
             deque->elementos[deque->fim].codigo,
             deque->elementos[deque->fim].nome);
    }
  }
  
  pausar();
}

void menuInserirInicio(DequeEstatico *deque)
{
  int sucesso;
  Cliente novoCliente;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        INSERIR NO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeCheio(deque)) {
    printf("Deque cheio! Nao e possivel inserir novos clientes.\n");
    pausar();
    return;
  }

  printf("Digite o codigo do cliente: ");
  scanf("%d", &novoCliente.codigo);

  limparBuffer();

  printf("Digite o nome do cliente: ");
  fgets(novoCliente.nome, 60, stdin);

  removerQuebraLinha(novoCliente.nome);

  sucesso = inserirInicio(deque, novoCliente);

  printf("\n");
  if (sucesso)
    printf("Cliente inserido no INICIO do deque com sucesso!\n");
  else
    printf("Erro ao inserir cliente no deque!\n");
    
  pausar();
}

void menuInserirFim(DequeEstatico *deque)
{
  int sucesso;
  Cliente novoCliente;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         INSERIR NO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeCheio(deque)) {
    printf("Deque cheio! Nao e possivel inserir novos clientes.\n");
    pausar();
    return;
  }

  printf("Digite o codigo do cliente: ");
  scanf("%d", &novoCliente.codigo);

  limparBuffer();

  printf("Digite o nome do cliente: ");
  fgets(novoCliente.nome, 60, stdin);

  removerQuebraLinha(novoCliente.nome);

  sucesso = inserirFim(deque, novoCliente);

  printf("\n");
  if (sucesso)
    printf("Cliente inserido no FIM do deque com sucesso!\n");
  else
    printf("Erro ao inserir cliente no deque!\n");
    
  pausar();
}

void menuRemoverInicio(DequeEstatico *deque) {
  Cliente removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        REMOVER DO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Cliente a ser removido do INICIO:\n");
  printf("Codigo: %d - %s\n\n", deque->elementos[deque->inicio].codigo, 
                                deque->elementos[deque->inicio].nome);

  removido = removerInicio(deque);

  printf("Cliente removido do inicio: %d - %s\n", removido.codigo, removido.nome);
  
  if (!dequeVazio(deque)) {
    printf("Novo primeiro cliente: %d - %s\n", 
           deque->elementos[deque->inicio].codigo,
           deque->elementos[deque->inicio].nome);
  } else {
    printf("Deque agora esta vazio.\n");
  }
    
  pausar();
}

void menuRemoverFim(DequeEstatico *deque) {
  Cliente removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         REMOVER DO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Cliente a ser removido do FIM:\n");
  printf("Codigo: %d - %s\n\n", deque->elementos[deque->fim].codigo, 
                                deque->elementos[deque->fim].nome);

  removido = removerFim(deque);

  printf("Cliente removido do fim: %d - %s\n", removido.codigo, removido.nome);
  
  if (!dequeVazio(deque)) {
    printf("Novo ultimo cliente: %d - %s\n", 
           deque->elementos[deque->fim].codigo,
           deque->elementos[deque->fim].nome);
  } else {
    printf("Deque agora esta vazio.\n");
  }
    
  pausar();
}

void menuConsultarInicio(DequeEstatico *deque) {
  Cliente primeiro;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        CONSULTAR INICIO              ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhum cliente para consultar.\n");
    pausar();
    return;
  }

  primeiro = consultarInicio(deque);

  printf("Primeiro cliente do deque (INICIO):\n");
  printf("┌─────────────┬──────────────────────────┐\n");
  printf("│  Codigo     │ %-24d │\n", primeiro.codigo);
  printf("│  Nome       │ %-24s │\n", primeiro.nome);
  printf("│  Posicao    │ Inicio do deque          │\n");
  printf("└─────────────┴──────────────────────────┘\n");
  
  pausar();
}

void menuConsultarFim(DequeEstatico *deque) {
  Cliente ultimo;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         CONSULTAR FIM                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhum cliente para consultar.\n");
    pausar();
    return;
  }

  ultimo = consultarFim(deque);

  printf("Ultimo cliente do deque (FIM):\n");
  printf("┌─────────────┬──────────────────────────┐\n");
  printf("│  Codigo     │ %-24d │\n", ultimo.codigo);
  printf("│  Nome       │ %-24s │\n", ultimo.nome);
  printf("│  Posicao    │ Fim do deque             │\n");
  printf("└─────────────┴──────────────────────────┘\n");
  
  pausar();
}

void menuLimparDeque(DequeEstatico *deque) {
  char confirmacao;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          LIMPAR DEQUE                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque ja esta vazio!\n");
    pausar();
    return;
  }

  printf("ATENCAO: Esta operacao ira remover TODOS os clientes do deque!\n");
  printf("Clientes no deque: %d\n\n", deque->tamanho);
  
  printf("Tem certeza? (s/N): ");
  limparBuffer();
  scanf("%c", &confirmacao);

  if (confirmacao == 's' || confirmacao == 'S') {
    inicializarDeque(deque);
    printf("\nDeque limpo com sucesso! Todos os clientes foram removidos.\n");
  } else {
    printf("\nOperacao cancelada. Deque mantido inalterado.\n");
  }
    
  pausar();
}

int main()
{
  DequeEstatico deque;
  int opcao;

  inicializarDeque(&deque);

  do
  {
    exibirMenu(&deque, &opcao);

    switch (opcao)
    {
    case 1:
      menuExibirDeque(&deque);
      break;

    case 2:
      menuInserirInicio(&deque);
      break;

    case 3:
      menuInserirFim(&deque);
      break;

    case 4:
      menuRemoverInicio(&deque);
      break;

    case 5:
      menuRemoverFim(&deque);
      break;
      
    case 6:
      menuConsultarInicio(&deque);
      break;
      
    case 7:
      menuConsultarFim(&deque);
      break;
      
    case 8:
      menuLimparDeque(&deque);
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
      printf("Por favor, escolha uma opcao valida (0-8).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
} 