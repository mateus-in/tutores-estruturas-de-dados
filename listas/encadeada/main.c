#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int numCamisa;
  char nome[50];
} Jogador;

typedef struct celula {
  Jogador info;
  struct celula *prox;
} Celula;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

void inicializarLista(Celula **lista) {
  (*lista) = NULL;
}

int listaVazia(Celula **lista) {
  if ((*lista) == NULL)
    return 1;

  return 0;
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

int contarElementos(Celula **lista) {
  if (listaVazia(lista)) {
    return 0;
  }

  Celula *aux = (*lista);
  int contador = 0;
  
  while (aux != NULL) {
    contador++;
    aux = aux->prox;
  }
  
  return contador;
}

void exibirCabecalho(Celula **lista) {
  int total = contarElementos(lista);
  char status[20];
  
  if (listaVazia(lista)) {
    strcpy(status, "VAZIA");
  } else {
    strcpy(status, "COM DADOS");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║        LISTA ENCADEADA               ║\n");
  printf("║         Sistema de Jogadores         ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Jogadores: %d      ║\n", status, total);
  printf("╚══════════════════════════════════════╝\n\n");
}

Celula * criarCelula() {
  Celula *nova = (Celula*) malloc(sizeof(Celula));
  return nova;
}

int inserirFim(Celula **lista, Jogador elemento) {
  Celula *novaCelula;
  Celula *aux;

  novaCelula = criarCelula();

  if (novaCelula == NULL) {
    return 0;
  }

  novaCelula->info = elemento;
  novaCelula->prox = NULL;

  if (listaVazia(lista)) {
    (*lista) = novaCelula;
    return 1;
  }

  aux = (*lista);
  while(aux->prox != NULL) {
    aux = aux->prox;
  }

  aux->prox = novaCelula;

  return 1;
}

int inserirInicio(Celula **lista, Jogador elemento) {
  Celula *novaCelula = criarCelula();

  if (novaCelula == NULL)
    return 0;

  if(listaVazia(lista))
    return inserirFim(lista, elemento);

  novaCelula->info = elemento;
  novaCelula->prox = (*lista);

  (*lista) = novaCelula;

  return 1;
}

void exibirElementos(Celula **lista) {
  if (listaVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }

  Celula *aux = (*lista);

  while (aux != NULL) {
    printf(
      "%d - %s\n",
      aux->info.numCamisa,
      aux->info.nome
    );

    aux = aux->prox;
  }
}

Jogador criarElemento(int numCamisa, char nome[]) {
  Jogador elemento;

  strcpy(elemento.nome, nome);
  elemento.numCamisa = numCamisa;

  return elemento;
}

Jogador removerInicio(Celula **lista) {
  Celula *removida;
  Jogador removido = criarElemento(-1, "");

  if(listaVazia(lista)) {
    return removido;
  }

  removida = (*lista);
  removido = removida->info;

  (*lista) = (*lista)->prox;

  free(removida);

  return removido;
}

Jogador removerFim(Celula **lista) {
  Celula *removida;
  Celula *anterior;
  Jogador removido = criarElemento(-1, "");

  if(listaVazia(lista)) {
    return removido;
  }

  if((*lista)->prox == NULL) {
    return removerInicio(lista);
  }

  removida = (*lista);
  while(removida->prox != NULL) {
    anterior = removida;
    removida = removida->prox;
  }

  removido = removida->info;
  anterior->prox = NULL;

  free(removida);

  return removido;
}

int compararElemento(Jogador j1, Jogador j2) {
  return strcmp(j1.nome, j2.nome);
}

Celula * pesquisar(Celula **lista, Jogador pesquisado) {
  Celula *aux;

  if(listaVazia(lista)) {
    return NULL;
  }

  aux = (*lista);
  while(aux != NULL) {
    if (compararElemento(aux->info, pesquisado) == 0) {
      return aux;
    }

    aux = aux->prox;
  }

  return NULL;
}

Jogador removerElemento(Celula **lista, Jogador elemento) {
  Celula *removida;
  Celula *anterior;
  Jogador removido = criarElemento(-1, "");

  if(listaVazia(lista)) {
    return removido;
  }

  removida = pesquisar(lista, elemento);
  if(removida == NULL) {
    return removido;
  }

  if(removida == (*lista)) {
    return removerInicio(lista);
  }

  removido = removida->info;

  anterior = (*lista);
  while(anterior->prox != removida) {
    anterior = anterior->prox;
  }

  anterior->prox = removida->prox;

  free(removida);

  return removido;
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(Celula **lista, int *opcao)
{
  limparTela();
  exibirCabecalho(lista);
  
  printf("┌──────────────────────────────────────┐\n");
  printf("│                MENU                  │\n");
  printf("├──────────────────────────────────────┤\n");
  printf("│  1 - Exibir elementos                │\n");
  printf("│  2 - Inserir no inicio               │\n");
  printf("│  3 - Inserir no fim                  │\n");
  printf("│  4 - Remover do inicio               │\n");
  printf("│  5 - Remover do fim                  │\n");
  printf("│  6 - Pesquisar elemento              │\n");
  printf("│  7 - Remover elemento especifico     │\n");
  printf("│  0 - Sair                            │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirElementos(Celula **lista) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         LISTA DE JOGADORES           ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (listaVazia(lista)) {
    printf("Lista vazia! Nenhum jogador cadastrado.\n");
  } else {
    printf("┌─────────────┬────────────────────────┐\n");
    printf("│ Num. Camisa │         Nome           │\n");
    printf("├─────────────┼────────────────────────┤\n");
    
    Celula *aux = (*lista);
    while (aux != NULL) {
      printf("│ %11d │ %-22s │\n", aux->info.numCamisa, aux->info.nome);
      aux = aux->prox;
    }
    printf("└─────────────┴────────────────────────┘\n");
    printf("\nTotal de jogadores: %d\n", contarElementos(lista));
  }
  
  pausar();
}

void menuInserirInicio(Celula **lista)
{
  int sucesso;
  Jogador novoJogador;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        INSERIR NO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da camisa: ");
  scanf("%d", &novoJogador.numCamisa);

  limparBuffer();

  printf("Digite o nome do jogador: ");
  fgets(novoJogador.nome, 50, stdin);

  removerQuebraLinha(novoJogador.nome);

  sucesso = inserirInicio(lista, novoJogador);

  printf("\n");
  if (sucesso)
    printf("Jogador inserido com sucesso!\n");
  else
    printf("Erro ao inserir jogador!\n");
    
  pausar();
}

void menuInserirFim(Celula **lista)
{
  int sucesso;
  Jogador novoJogador;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         INSERIR NO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  printf("Digite o numero da camisa: ");
  scanf("%d", &novoJogador.numCamisa);

  limparBuffer();

  printf("Digite o nome do jogador: ");
  fgets(novoJogador.nome, 50, stdin);

  removerQuebraLinha(novoJogador.nome);

  sucesso = inserirFim(lista, novoJogador);

  printf("\n");
  if (sucesso)
    printf("Jogador inserido com sucesso!\n");
  else
    printf("Erro ao inserir jogador!\n");
    
  pausar();
}

void menuRemoverInicio(Celula **lista) {
  Jogador removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        REMOVER DO INICIO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para remover.\n");
    pausar();
    return;
  }

  removido = removerInicio(lista);

  printf("\n");
  if (removido.numCamisa != -1)
    printf("Jogador removido: %d - %s\n", removido.numCamisa, removido.nome);
  else
    printf("Erro ao remover jogador!\n");
    
  pausar();
}

void menuRemoverFim(Celula **lista) {
  Jogador removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         REMOVER DO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para remover.\n");
    pausar();
    return;
  }

  removido = removerFim(lista);

  printf("\n");
  if (removido.numCamisa != -1)
    printf("Jogador removido: %d - %s\n", removido.numCamisa, removido.nome);
  else
    printf("Erro ao remover jogador!\n");
    
  pausar();
}

void menuPesquisarElemento(Celula **lista) {
  char nome[50];
  Jogador pesquisado;
  Celula *encontrado;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        PESQUISAR ELEMENTO            ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para pesquisar.\n");
    pausar();
    return;
  }

  limparBuffer();
  printf("Digite o nome para pesquisar: ");
  fgets(nome, 50, stdin);
  removerQuebraLinha(nome);

  pesquisado = criarElemento(0, nome);
  encontrado = pesquisar(lista, pesquisado);

  printf("\n");
  if (encontrado != NULL) {
    printf("Elemento encontrado!\n");
    printf("┌─────────────┬────────────────────────┐\n");
    printf("│ Num. Camisa │ %-22d │\n", encontrado->info.numCamisa);
    printf("│ Nome        │ %-22s │\n", encontrado->info.nome);
    printf("└─────────────┴────────────────────────┘\n");
  } else {
    printf("Elemento nao encontrado!\n");
  }
  
  pausar();
}

void menuRemoverElemento(Celula **lista) {
  char nome[50];
  Jogador pesquisado, removido;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║      REMOVER ELEMENTO ESPECIFICO     ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para remover.\n");
    pausar();
    return;
  }

  limparBuffer();
  printf("Digite o nome do jogador a remover: ");
  fgets(nome, 50, stdin);
  removerQuebraLinha(nome);

  pesquisado = criarElemento(0, nome);
  removido = removerElemento(lista, pesquisado);

  printf("\n");
  if (removido.numCamisa != -1)
    printf("Jogador removido: %d - %s\n", removido.numCamisa, removido.nome);
  else
    printf("Jogador nao encontrado!\n");
    
  pausar();
}

int main() {
  Celula *lista;
  int opcao;

  inicializarLista(&lista);

  do
  {
    exibirMenu(&lista, &opcao);

    switch (opcao)
    {
    case 1:
      menuExibirElementos(&lista);
      break;

    case 2:
      menuInserirInicio(&lista);
      break;

    case 3:
      menuInserirFim(&lista);
      break;

    case 4:
      menuRemoverInicio(&lista);
      break;

    case 5:
      menuRemoverFim(&lista);
      break;

    case 6:
      menuPesquisarElemento(&lista);
      break;
      
    case 7:
      menuRemoverElemento(&lista);
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
      printf("Por favor, escolha uma opcao valida (0-7).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
}
