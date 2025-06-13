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
void inicializarDeque(NoDeque **inicio, NoDeque **fim)
{
  *inicio = NULL;
  *fim = NULL;
}

int dequeVazio(NoDeque **inicio)
{
  return *inicio == NULL;
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

int contarElementos(NoDeque **inicio) {
  if (dequeVazio(inicio)) {
    return 0;
  }

  NoDeque *aux = *inicio;
  int contador = 0;
  
  while (aux != NULL) {
    contador++;
    aux = aux->proximo;
  }
  
  return contador;
}

void exibirCabecalho(NoDeque **inicio) {
  int total = contarElementos(inicio);
  char status[20];
  
  if (dequeVazio(inicio)) {
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

int inserirInicio(NoDeque **inicio, NoDeque **fim, Tarefa elemento)
{
  NoDeque *novoNo = (NoDeque *)malloc(sizeof(NoDeque));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->anterior = NULL;
  novoNo->proximo = *inicio;

  if (dequeVazio(inicio)) {
    *inicio = novoNo;
    *fim = novoNo;
  } else {
    (*inicio)->anterior = novoNo;
    *inicio = novoNo;
  }

  return 1;
}

int inserirFim(NoDeque **inicio, NoDeque **fim, Tarefa elemento)
{
  NoDeque *novoNo = (NoDeque *)malloc(sizeof(NoDeque));
  
  if (novoNo == NULL)
    return 0; // Falha na alocação

  novoNo->dados = elemento;
  novoNo->anterior = *fim;
  novoNo->proximo = NULL;

  if (dequeVazio(inicio)) {
    *inicio = novoNo;
    *fim = novoNo;
  } else {
    (*fim)->proximo = novoNo;
    *fim = novoNo;
  }

  return 1;
}

Tarefa removerInicio(NoDeque **inicio, NoDeque **fim)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(inicio))
    return vazio;

  NoDeque *noRemover = *inicio;
  Tarefa dadosRemovidos = noRemover->dados;

  if (*inicio == *fim) {
    // Único elemento
    *inicio = NULL;
    *fim = NULL;
  } else {
    *inicio = (*inicio)->proximo;
    (*inicio)->anterior = NULL;
  }

  free(noRemover);

  return dadosRemovidos;
}

Tarefa removerFim(NoDeque **inicio, NoDeque **fim)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(inicio))
    return vazio;

  NoDeque *noRemover = *fim;
  Tarefa dadosRemovidos = noRemover->dados;

  if (*inicio == *fim) {
    // Único elemento
    *inicio = NULL;
    *fim = NULL;
  } else {
    *fim = (*fim)->anterior;
    (*fim)->proximo = NULL;
  }

  free(noRemover);

  return dadosRemovidos;
}

Tarefa consultarInicio(NoDeque **inicio)
{
  Tarefa vazio = {-1, ""};
  
  if (dequeVazio(inicio))
    return vazio;

  return (*inicio)->dados;
}

Tarefa consultarFim(NoDeque **fim)
{
  Tarefa vazio = {-1, ""};
  
  if (*fim == NULL)
    return vazio;

  return (*fim)->dados;
}

void liberarDeque(NoDeque **inicio, NoDeque **fim)
{
  while (!dequeVazio(inicio)) {
    removerInicio(inicio, fim);
  }
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(NoDeque **inicio, int *opcao)
{
  limparTela();
  exibirCabecalho(inicio);
  
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
  printf("│  8 - Navegar pelo deque             │\n");
  printf("│  9 - Limpar deque                   │\n");
  printf("│  0 - Sair                           │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirDeque(NoDeque **inicio) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          DEQUE DE TAREFAS            ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (dequeVazio(inicio)) {
    printf("Deque vazio! Nenhuma tarefa no deque.\n");
  } else {
    printf("┌─────────┬────────┬─────────────────────────────────────────┐\n");
    printf("│ Posicao │ Numero │              Descricao                  │\n");
    printf("├─────────┼────────┼─────────────────────────────────────────┤\n");
    
    NoDeque *atual = *inicio;
    int posicao = 1;
    
    while (atual != NULL) {
      printf("│ %7d │ %6d │ %-39s │\n", posicao, 
             atual->dados.numero, 
             atual->dados.descricao);
      atual = atual->proximo;
      posicao++;
    }
    printf("└─────────┴────────┴─────────────────────────────────────────┘\n");
    printf("\nTotal no deque: %d tarefas\n", contarElementos(inicio));
    
    // Mostrar informações dos extremos
    NoDeque *ultimo = *inicio;
    while (ultimo->proximo != NULL) {
      ultimo = ultimo->proximo;
    }
    
    printf("Inicio: Tarefa %d - %s\n", (*inicio)->dados.numero, (*inicio)->dados.descricao);
    printf("Fim: Tarefa %d - %s\n", ultimo->dados.numero, ultimo->dados.descricao);
  }
  
  pausar();
}

void menuInserirInicio(NoDeque **inicio, NoDeque **fim)
{
  int sucesso;
  Tarefa novaTarefa;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       INSERIR NO INICIO              ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da tarefa: ");
  scanf("%d", &novaTarefa.numero);
  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
  removerQuebraLinha(novaTarefa.descricao);

  sucesso = inserirInicio(inicio, fim, novaTarefa);

  if (sucesso) {
    printf("\n✅ Tarefa inserida no inicio com sucesso!\n");
    printf("   Numero: %d\n", novaTarefa.numero);
    printf("   Descricao: %s\n", novaTarefa.descricao);
  } else {
    printf("\n❌ Erro ao inserir tarefa! Memoria insuficiente.\n");
  }

  pausar();
}

void menuInserirFim(NoDeque **inicio, NoDeque **fim)
{
  int sucesso;
  Tarefa novaTarefa;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        INSERIR NO FIM                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da tarefa: ");
  scanf("%d", &novaTarefa.numero);
  limparBuffer();

  printf("Digite a descricao da tarefa: ");
  fgets(novaTarefa.descricao, sizeof(novaTarefa.descricao), stdin);
  removerQuebraLinha(novaTarefa.descricao);

  sucesso = inserirFim(inicio, fim, novaTarefa);

  if (sucesso) {
    printf("\n✅ Tarefa inserida no fim com sucesso!\n");
    printf("   Numero: %d\n", novaTarefa.numero);
    printf("   Descricao: %s\n", novaTarefa.descricao);
  } else {
    printf("\n❌ Erro ao inserir tarefa! Memoria insuficiente.\n");
  }

  pausar();
}

void menuRemoverInicio(NoDeque **inicio, NoDeque **fim) {
  Tarefa removida;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       REMOVER DO INICIO              ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(inicio)) {
    printf("❌ Deque vazio! Nenhuma tarefa para remover.\n");
  } else {
    printf("Tarefa a ser removida do inicio:\n");
    printf("┌────────┬─────────────────────────────────────────┐\n");
    printf("│ Numero │              Descricao                  │\n");
    printf("├────────┼─────────────────────────────────────────┤\n");
    printf("│ %6d │ %-39s │\n", 
           (*inicio)->dados.numero,
           (*inicio)->dados.descricao);
    printf("└────────┴─────────────────────────────────────────┘\n\n");

    removida = removerInicio(inicio, fim);

    if (removida.numero != -1) {
      printf("✅ Tarefa removida do inicio com sucesso!\n");
      printf("   Numero: %d\n", removida.numero);
      printf("   Descricao: %s\n", removida.descricao);
    }
  }

  pausar();
}

void menuRemoverFim(NoDeque **inicio, NoDeque **fim) {
  Tarefa removida;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        REMOVER DO FIM                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(inicio)) {
    printf("❌ Deque vazio! Nenhuma tarefa para remover.\n");
  } else {
    // Encontrar o último elemento
    NoDeque *ultimo = *inicio;
    while (ultimo->proximo != NULL) {
      ultimo = ultimo->proximo;
    }
    
    printf("Tarefa a ser removida do fim:\n");
    printf("┌────────┬─────────────────────────────────────────┐\n");
    printf("│ Numero │              Descricao                  │\n");
    printf("├────────┼─────────────────────────────────────────┤\n");
    printf("│ %6d │ %-39s │\n", 
           ultimo->dados.numero,
           ultimo->dados.descricao);
    printf("└────────┴─────────────────────────────────────────┘\n\n");

    removida = removerFim(inicio, fim);

    if (removida.numero != -1) {
      printf("✅ Tarefa removida do fim com sucesso!\n");
      printf("   Numero: %d\n", removida.numero);
      printf("   Descricao: %s\n", removida.descricao);
    }
  }

  pausar();
}

void menuConsultarInicio(NoDeque **inicio) {
  Tarefa primeira;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       CONSULTAR INICIO               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(inicio)) {
    printf("❌ Deque vazio! Nenhuma tarefa no inicio.\n");
  } else {
    primeira = consultarInicio(inicio);
    
    printf("Primeira tarefa do deque:\n");
    printf("┌────────┬─────────────────────────────────────────┐\n");
    printf("│ Numero │              Descricao                  │\n");
    printf("├────────┼─────────────────────────────────────────┤\n");
    printf("│ %6d │ %-39s │\n", 
           primeira.numero,
           primeira.descricao);
    printf("└────────┴─────────────────────────────────────────┘\n");
    
    printf("\n📋 Esta e a primeira tarefa do deque.\n");
  }

  pausar();
}

void menuConsultarFim(NoDeque **inicio, NoDeque **fim) {
  Tarefa ultima;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        CONSULTAR FIM                 ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(inicio)) {
    printf("❌ Deque vazio! Nenhuma tarefa no fim.\n");
  } else {
    ultima = consultarFim(fim);
    
    printf("Ultima tarefa do deque:\n");
    printf("┌────────┬─────────────────────────────────────────┐\n");
    printf("│ Numero │              Descricao                  │\n");
    printf("├────────┼─────────────────────────────────────────┤\n");
    printf("│ %6d │ %-39s │\n", 
           ultima.numero,
           ultima.descricao);
    printf("└────────┴─────────────────────────────────────────┘\n");
    
    printf("\n📋 Esta e a ultima tarefa do deque.\n");
  }

  pausar();
}

void menuNavegarDeque(NoDeque **inicio) {
  if (dequeVazio(inicio)) {
    limparTela();
    printf("╔══════════════════════════════════════╗\n");
    printf("║       NAVEGAR PELO DEQUE             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    printf("❌ Deque vazio! Nenhuma tarefa para navegar.\n");
    pausar();
    return;
  }

  NoDeque *atual = *inicio;
  int posicao = 1;
  int total = contarElementos(inicio);
  int opcao;

  do {
    limparTela();
    printf("╔══════════════════════════════════════╗\n");
    printf("║       NAVEGAR PELO DEQUE             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
    
    printf("📍 Posição: %d de %d\n", posicao, total);
    printf("┌────────┬─────────────────────────────────────────┐\n");
    printf("│ Numero │              Descricao                  │\n");
    printf("├────────┼─────────────────────────────────────────┤\n");
    printf("│ %6d │ %-39s │\n", 
           atual->dados.numero,
           atual->dados.descricao);
    printf("└────────┴─────────────────────────────────────────┘\n\n");
    
    printf("┌──────────────────────────────────────┐\n");
    printf("│           NAVEGAÇÃO                  │\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│  1 - Proximo (→)                    │\n");
    printf("│  2 - Anterior (←)                   │\n");
    printf("│  3 - Ir para o inicio               │\n");
    printf("│  4 - Ir para o fim                  │\n");
    printf("│  0 - Voltar ao menu principal       │\n");
    printf("└──────────────────────────────────────┘\n\n");
    
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    switch (opcao) {
      case 1: // Próximo
        if (atual->proximo != NULL) {
          atual = atual->proximo;
          posicao++;
        } else {
          printf("\n❌ Ja esta na ultima tarefa!\n");
          pausar();
        }
        break;
        
      case 2: // Anterior
        if (atual->anterior != NULL) {
          atual = atual->anterior;
          posicao--;
        } else {
          printf("\n❌ Ja esta na primeira tarefa!\n");
          pausar();
        }
        break;
        
      case 3: // Ir para o início
        atual = *inicio;
        posicao = 1;
        printf("\n✅ Navegou para o inicio do deque!\n");
        pausar();
        break;
        
      case 4: // Ir para o fim
        atual = *inicio;
        posicao = 1;
        while (atual->proximo != NULL) {
          atual = atual->proximo;
          posicao++;
        }
        printf("\n✅ Navegou para o fim do deque!\n");
        pausar();
        break;
        
      case 0:
        break;
        
      default:
        printf("\n❌ Opcao invalida! Tente novamente.\n");
        pausar();
        break;
    }
  } while (opcao != 0);
}

void menuLimparDeque(NoDeque **inicio, NoDeque **fim) {
  int confirmacao;
  int totalAntes = contarElementos(inicio);

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          LIMPAR DEQUE                ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (dequeVazio(inicio)) {
    printf("❌ O deque ja esta vazio!\n");
  } else {
    printf("⚠️  ATENÇÃO: Esta operacao ira remover TODAS as %d tarefas do deque!\n", totalAntes);
    printf("   Esta acao nao pode ser desfeita.\n\n");
    printf("Deseja realmente limpar o deque? (1-Sim / 0-Nao): ");
    scanf("%d", &confirmacao);

    if (confirmacao == 1) {
      liberarDeque(inicio, fim);
      printf("\n✅ Deque limpo com sucesso!\n");
      printf("   %d tarefas foram removidas.\n", totalAntes);
    } else {
      printf("\n❌ Operacao cancelada. Deque mantido.\n");
    }
  }

  pausar();
}

int main()
{
  NoDeque *inicio, *fim;
  int opcao;

  inicializarDeque(&inicio, &fim);

  do {
    exibirMenu(&inicio, &opcao);

    switch (opcao) {
      case 1:
        menuExibirDeque(&inicio);
        break;
      case 2:
        menuInserirInicio(&inicio, &fim);
        break;
      case 3:
        menuInserirFim(&inicio, &fim);
        break;
      case 4:
        menuRemoverInicio(&inicio, &fim);
        break;
      case 5:
        menuRemoverFim(&inicio, &fim);
        break;
      case 6:
        menuConsultarInicio(&inicio);
        break;
      case 7:
        menuConsultarFim(&inicio, &fim);
        break;
      case 8:
        menuNavegarDeque(&inicio);
        break;
      case 9:
        menuLimparDeque(&inicio, &fim);
        break;
      case 0:
        printf("\n👋 Encerrando o programa...\n");
        liberarDeque(&inicio, &fim);
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