#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  int numero;
  char descricao[80];
} Tarefa;

typedef struct NoDeque
{
  Tarefa dados;
  struct NoDeque *anterior;
  struct NoDeque *proximo;
} NoDeque;

typedef struct
{
  NoDeque *inicio;
  NoDeque *fim;
  int tamanho;
} DequeDinamico;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

// FUNÇÕES DO DEQUE DINÂMICO
void inicializarDeque(DequeDinamico *deque)
{
  deque->inicio = NULL;
  deque->fim = NULL;
  deque->tamanho = 0;
}

int dequeVazio(DequeDinamico *deque)
{
  return deque->inicio == NULL;
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

void exibirCabecalho(DequeDinamico *deque) {
  int total = deque->tamanho;
  char status[20];
  
  if (dequeVazio(deque)) {
    strcpy(status, "VAZIO");
  } else {
    strcpy(status, "ATIVO");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║         DEQUE DINAMICO               ║\n");
  printf("║       Sistema de Tarefas             ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Tarefas: %-9d║\n", status, total);
  printf("╚══════════════════════════════════════╝\n\n");
}

int inserirInicio(DequeDinamico *deque, Tarefa elemento)
{
  NoDeque *novoNo = (NoDeque *)malloc(sizeof(NoDeque));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->anterior = NULL;
  novoNo->proximo = deque->inicio;

  if (dequeVazio(deque)) {
    deque->inicio = novoNo;
    deque->fim = novoNo;
  } else {
    deque->inicio->anterior = novoNo;
    deque->inicio = novoNo;
  }

  deque->tamanho++;
  return 1;
}

int inserirFim(DequeDinamico *deque, Tarefa elemento)
{
  NoDeque *novoNo = (NoDeque *)malloc(sizeof(NoDeque));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->anterior = deque->fim;
  novoNo->proximo = NULL;

  if (dequeVazio(deque)) {
    deque->inicio = novoNo;
    deque->fim = novoNo;
  } else {
    deque->fim->proximo = novoNo;
    deque->fim = novoNo;
  }

  deque->tamanho++;
  return 1;
}

Tarefa removerInicio(DequeDinamico *deque)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  NoDeque *noRemover = deque->inicio;
  Tarefa dadosRemovidos = noRemover->dados;

  if (deque->tamanho == 1) {
    // Único elemento
    deque->inicio = NULL;
    deque->fim = NULL;
  } else {
    deque->inicio = deque->inicio->proximo;
    deque->inicio->anterior = NULL;
  }

  free(noRemover);
  deque->tamanho--;

  return dadosRemovidos;
}

Tarefa removerFim(DequeDinamico *deque)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  NoDeque *noRemover = deque->fim;
  Tarefa dadosRemovidos = noRemover->dados;

  if (deque->tamanho == 1) {
    // Único elemento
    deque->inicio = NULL;
    deque->fim = NULL;
  } else {
    deque->fim = deque->fim->anterior;
    deque->fim->proximo = NULL;
  }

  free(noRemover);
  deque->tamanho--;

  return dadosRemovidos;
}

Tarefa consultarInicio(DequeDinamico *deque)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  return deque->inicio->dados;
}

Tarefa consultarFim(DequeDinamico *deque)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(deque))
    return vazio;

  return deque->fim->dados;
}

void liberarDeque(DequeDinamico *deque)
{
  while (!dequeVazio(deque)) {
    removerInicio(deque);
  }
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(DequeDinamico *deque, int *opcao)
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
  printf("│  8 - Navegar deque                  │\n");
  printf("│  9 - Limpar deque                   │\n");
  printf("│  0 - Sair                           │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirDeque(DequeDinamico *deque) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          DEQUE DE TAREFAS            ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhuma tarefa no deque.\n");
  } else {
    printf("┌─────────┬─────────┬──────────────────────────────┐\n");
    printf("│ Posicao │ Numero  │          Descricao           │\n");
    printf("├─────────┼─────────┼──────────────────────────────┤\n");
    
    NoDeque *atual = deque->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
      char indicador[10] = "";
      
      if (posicao == 1 && posicao == deque->tamanho) {
        strcpy(indicador, " (I/F)");
      } else if (posicao == 1) {
        strcpy(indicador, " (I)");
      } else if (posicao == deque->tamanho) {
        strcpy(indicador, " (F)");
      }
      
      printf("│ %5d%s │ %7d │ %-28s │\n", posicao, indicador,
             atual->dados.numero, 
             atual->dados.descricao);
      atual = atual->proximo;
      posicao++;
    }
    printf("└─────────┴─────────┴──────────────────────────────┘\n");
    printf("\nTotal no deque: %d tarefas\n", deque->tamanho);
    printf("Legenda: (I) = Inicio, (F) = Fim\n");
    
    if (deque->tamanho > 0) {
      printf("\nExtremos do deque:\n");
      printf("- Inicio: %d - %s\n", 
             deque->inicio->dados.numero,
             deque->inicio->dados.descricao);
      printf("- Fim: %d - %s\n", 
             deque->fim->dados.numero,
             deque->fim->dados.descricao);
    }
  }
  
  pausar();
}

void menuInserirInicio(DequeDinamico *deque)
{
  int sucesso;
  Tarefa novaTarefa;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        INSERIR NO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da tarefa: ");
  scanf("%d", &novaTarefa.numero);

  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novaTarefa.descricao, 80, stdin);

  removerQuebraLinha(novaTarefa.descricao);

  sucesso = inserirInicio(deque, novaTarefa);

  printf("\n");
  if (sucesso)
    printf("Tarefa inserida no INICIO do deque com sucesso!\n");
  else
    printf("Erro ao inserir tarefa no deque! (Memoria insuficiente)\n");
    
  pausar();
}

void menuInserirFim(DequeDinamico *deque)
{
  int sucesso;
  Tarefa novaTarefa;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         INSERIR NO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da tarefa: ");
  scanf("%d", &novaTarefa.numero);

  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novaTarefa.descricao, 80, stdin);

  removerQuebraLinha(novaTarefa.descricao);

  sucesso = inserirFim(deque, novaTarefa);

  printf("\n");
  if (sucesso)
    printf("Tarefa inserida no FIM do deque com sucesso!\n");
  else
    printf("Erro ao inserir tarefa no deque! (Memoria insuficiente)\n");
    
  pausar();
}

void menuRemoverInicio(DequeDinamico *deque) {
  Tarefa removida;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        REMOVER DO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Tarefa a ser removida do INICIO:\n");
  printf("Numero: %d - %s\n\n", deque->inicio->dados.numero, 
                                deque->inicio->dados.descricao);

  removida = removerInicio(deque);

  printf("Tarefa removida do inicio: %d - %s\n", removida.numero, removida.descricao);
  
  if (!dequeVazio(deque)) {
    printf("Nova primeira tarefa: %d - %s\n", 
           deque->inicio->dados.numero,
           deque->inicio->dados.descricao);
  } else {
    printf("Deque agora esta vazio.\n");
  }
    
  pausar();
}

void menuRemoverFim(DequeDinamico *deque) {
  Tarefa removida;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         REMOVER DO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Tarefa a ser removida do FIM:\n");
  printf("Numero: %d - %s\n\n", deque->fim->dados.numero, 
                                deque->fim->dados.descricao);

  removida = removerFim(deque);

  printf("Tarefa removida do fim: %d - %s\n", removida.numero, removida.descricao);
  
  if (!dequeVazio(deque)) {
    printf("Nova ultima tarefa: %d - %s\n", 
           deque->fim->dados.numero,
           deque->fim->dados.descricao);
  } else {
    printf("Deque agora esta vazio.\n");
  }
    
  pausar();
}

void menuConsultarInicio(DequeDinamico *deque) {
  Tarefa primeira;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        CONSULTAR INICIO              ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhuma tarefa para consultar.\n");
    pausar();
    return;
  }

  primeira = consultarInicio(deque);

  printf("Primeira tarefa do deque (INICIO):\n");
  printf("┌─────────────┬──────────────────────────┐\n");
  printf("│  Numero     │ %-24d │\n", primeira.numero);
  printf("│  Descricao  │ %-24s │\n", primeira.descricao);
  printf("│  Posicao    │ Inicio do deque          │\n");
  printf("└─────────────┴──────────────────────────┘\n");
  
  pausar();
}

void menuConsultarFim(DequeDinamico *deque) {
  Tarefa ultima;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         CONSULTAR FIM                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhuma tarefa para consultar.\n");
    pausar();
    return;
  }

  ultima = consultarFim(deque);

  printf("Ultima tarefa do deque (FIM):\n");
  printf("┌─────────────┬──────────────────────────┐\n");
  printf("│  Numero     │ %-24d │\n", ultima.numero);
  printf("│  Descricao  │ %-24s │\n", ultima.descricao);
  printf("│  Posicao    │ Fim do deque             │\n");
  printf("└─────────────┴──────────────────────────┘\n");
  
  pausar();
}

void menuNavegarDeque(DequeDinamico *deque) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         NAVEGAR DEQUE                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(deque)) {
    printf("Deque vazio! Nenhuma tarefa para navegar.\n");
    pausar();
    return;
  }

  int opcao;
  NoDeque *atual = deque->inicio;
  int posicao = 1;

  do {
    limparTela();
    printf("╔══════════════════════════════════════╗\n");
    printf("║         NAVEGACAO BIDIRECIONAL       ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    
    printf("Posicao atual: %d/%d\n", posicao, deque->tamanho);
    printf("┌─────────────┬──────────────────────────┐\n");
    printf("│  Numero     │ %-24d │\n", atual->dados.numero);
    printf("│  Descricao  │ %-24s │\n", atual->dados.descricao);
    printf("└─────────────┴──────────────────────────┘\n\n");
    
    printf("Navegacao:\n");
    if (atual->anterior != NULL) {
      printf("1 - Anterior (← %d)\n", atual->anterior->dados.numero);
    } else {
      printf("1 - Anterior (indisponivel)\n");
    }
    
    if (atual->proximo != NULL) {
      printf("2 - Proximo (→ %d)\n", atual->proximo->dados.numero);
    } else {
      printf("2 - Proximo (indisponivel)\n");
    }
    
    printf("3 - Ir para o inicio\n");
    printf("4 - Ir para o fim\n");
    printf("0 - Voltar ao menu principal\n\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    switch (opcao) {
      case 1:
        if (atual->anterior != NULL) {
          atual = atual->anterior;
          posicao--;
        }
        break;
      case 2:
        if (atual->proximo != NULL) {
          atual = atual->proximo;
          posicao++;
        }
        break;
      case 3:
        atual = deque->inicio;
        posicao = 1;
        break;
      case 4:
        atual = deque->fim;
        posicao = deque->tamanho;
        break;
    }
  } while (opcao != 0);
}

void menuLimparDeque(DequeDinamico *deque) {
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

  printf("ATENCAO: Esta operacao ira remover TODAS as tarefas do deque!\n");
  printf("Tarefas no deque: %d\n\n", deque->tamanho);
  
  printf("Tem certeza? (s/N): ");
  limparBuffer();
  scanf("%c", &confirmacao);

  if (confirmacao == 's' || confirmacao == 'S') {
    liberarDeque(deque);
    printf("\nDeque limpo com sucesso! Todas as tarefas foram removidas.\n");
  } else {
    printf("\nOperacao cancelada. Deque mantido inalterado.\n");
  }
    
  pausar();
}

int main()
{
  DequeDinamico deque;
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
      menuNavegarDeque(&deque);
      break;
      
    case 9:
      menuLimparDeque(&deque);
      break;
      
    case 0:
      liberarDeque(&deque); // Liberar memoria antes de sair
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
      printf("Por favor, escolha uma opcao valida (0-9).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
} 