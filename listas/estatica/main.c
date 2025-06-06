#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 3

typedef struct
{
  int matricula;
  char nome[50];
} Aluno;

typedef struct
{
  Aluno elementos[MAX_ELEMENTOS];
  int ultimo;
} ListaEstatica;

void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void removerQuebraLinha(char *str) {
  str[strcspn(str, "\n")] = 0;
}

void inicializarLista(ListaEstatica *lista)
{
  lista->ultimo = -1;
}

int listaVazia(ListaEstatica *lista)
{
  if (lista->ultimo == -1)
    return 1;

  return 0;
}

int listaCheia(ListaEstatica *lista)
{
  if (lista->ultimo == (MAX_ELEMENTOS - 1))
    return 1;

  return 0;
}

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

void exibirCabecalho(ListaEstatica *lista) {
  int total = lista->ultimo + 1;
  char status[20];
  
  if (listaVazia(lista)) {
    strcpy(status, "VAZIA");
  } else if (listaCheia(lista)) {
    strcpy(status, "CHEIA");
  } else {
    strcpy(status, "PARCIAL");
  }
  
  printf("╔══════════════════════════════════════╗\n");
  printf("║         LISTA ESTATICA               ║\n");
  printf("║         Sistema de Alunos            ║\n");
  printf("╠══════════════════════════════════════╣\n");
  printf("║ Status: %-8s | Alunos: %d/%d         ║\n", status, total, MAX_ELEMENTOS);
  printf("╚══════════════════════════════════════╝\n\n");
}

void exibirElementos(ListaEstatica *lista)
{
  if (listaVazia(lista))
  {
    printf("Lista vazia!\n");
    return;
  }

  for (int i = 0; i <= lista->ultimo; i++)
    printf("%d - %s\n", lista->elementos[i].matricula, lista->elementos[i].nome);
}

int inserirFim(ListaEstatica *lista, Aluno elemento)
{
  if (listaCheia(lista))
    return 0;

  lista->elementos[lista->ultimo + 1] = elemento;
  lista->ultimo++;

  return 1;
}

int inserirPosicao(ListaEstatica *lista, int posicao, Aluno elemento)
{
  if (listaCheia(lista))
  {
    printf("Lista cheia!\n");
    return 0;
  }

  if (posicao < 0 || posicao > lista->ultimo + 1)
  {
    printf("Posição inválida!\n");
    return 0;
  }

  for (int i = lista->ultimo; i >= posicao; i--)
    lista->elementos[i + 1] = lista->elementos[i];

  lista->elementos[posicao] = elemento;
  lista->ultimo++;

  return 1;
}

int removerPosicao(ListaEstatica *lista, int posicao) {
  if(listaVazia(lista)) {
    printf("Nada para remover\n");
    return 0;
  }

  if (posicao < 0 || posicao > lista->ultimo + 1)
  {
    printf("Posição inválida!\n");
    return 0;
  }

  for(int i = posicao; i < lista->ultimo; i++)
    lista->elementos[i] = lista->elementos[i + 1];

  lista->ultimo--;

  return 1;
}

int modificarElemento(ListaEstatica *lista, int posicao, Aluno elemento) {
  if (listaVazia(lista))
  {
    printf("Lista vazia!\n");
    return 0;
  }

  if (posicao < 0 || posicao > lista->ultimo + 1)
  {
    printf("Posição inválida!\n");
    return 0;
  }

  lista->elementos[posicao] = elemento;

  return 1;
}

int pesquisarElemento(ListaEstatica *lista, int matricula) {
  if (listaVazia(lista)) {
    printf("Lista vazia!\n");
    return -1;
  }

  for(int i = 0; i <= lista->ultimo; i++) {
    if (lista->elementos[i].matricula == matricula) {
      return i;
    }
  }

  return -1;
}

// FUNÇÕES UTILIZADAS PELO MENU
void exibirMenu(ListaEstatica *lista, int *opcao)
{
  limparTela();
  exibirCabecalho(lista);
  
  printf("┌──────────────────────────────────────┐\n");
  printf("│                MENU                  │\n");
  printf("├──────────────────────────────────────┤\n");
  printf("│  1 - Exibir elementos                │\n");
  printf("│  2 - Inserir na posicao              │\n");
  printf("│  3 - Inserir no fim                  │\n");
  printf("│  4 - Remover na posicao              │\n");
  printf("│  5 - Modificar elemento              │\n");
  printf("│  6 - Pesquisar elemento              │\n");
  printf("│  0 - Sair                            │\n");
  printf("└──────────────────────────────────────┘\n\n");
  printf("Escolha uma opcao: ");
  scanf("%d", opcao);
}

void menuExibirElementos(ListaEstatica *lista) {
  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║          LISTA DE ALUNOS             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");
  
  if (listaVazia(lista)) {
    printf("Lista vazia! Nenhum aluno cadastrado.\n");
  } else {
    printf("┌─────────────┬────────────────────────┐\n");
    printf("│  Matrícula  │         Nome           │\n");
    printf("├─────────────┼────────────────────────┤\n");
    
    for (int i = 0; i <= lista->ultimo; i++) {
      printf("│ %11d │ %-22s │\n", lista->elementos[i].matricula, lista->elementos[i].nome);
    }
    printf("└─────────────┴────────────────────────┘\n");
    printf("\nTotal de alunos: %d/%d\n", lista->ultimo + 1, MAX_ELEMENTOS);
  }
  
  pausar();
}

void menuInserirPosicao(ListaEstatica *lista)
{
  int posicao, sucesso;
  Aluno novoElemento;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       INSERIR NA POSICAO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaCheia(lista)) {
    printf("Lista cheia! Nao e possivel inserir novos elementos.\n");
    pausar();
    return;
  }

  printf("Digite a posicao (0 a %d): ", lista->ultimo + 1);
  scanf("%d", &posicao);

  printf("Digite a matricula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  removerQuebraLinha(novoElemento.nome);

  sucesso = inserirPosicao(lista, posicao, novoElemento);

  printf("\n");
  if (sucesso)
    printf("Elemento inserido com sucesso!\n");
  else
    printf("Erro ao inserir elemento!\n");
    
  pausar();
}

void menuInserirFim(ListaEstatica *lista)
{
  int sucesso;
  Aluno novoElemento;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║         INSERIR NO FIM               ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaCheia(lista)) {
    printf("Lista cheia! Nao e possivel inserir novos elementos.\n");
    pausar();
    return;
  }

  printf("Digite a matricula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  removerQuebraLinha(novoElemento.nome);

  sucesso = inserirFim(lista, novoElemento);

  printf("\n");
  if (sucesso)
    printf("Elemento inserido com sucesso!\n");
  else
    printf("Erro ao inserir elemento!\n");
    
  pausar();
}

void menuRemoverPosicao(ListaEstatica *lista) {
  int sucesso, posicao;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        REMOVER DA POSICAO            ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para remover.\n");
    pausar();
    return;
  }

  printf("Lista atual:\n");
  for (int i = 0; i <= lista->ultimo; i++) {
    printf("   [%d] %d - %s\n", i, lista->elementos[i].matricula, lista->elementos[i].nome);
  }

  printf("\nDigite a posicao a remover (0 a %d): ", lista->ultimo);
  scanf("%d", &posicao);

  sucesso = removerPosicao(lista, posicao);

  printf("\n");
  if (sucesso)
    printf("Elemento removido com sucesso!\n");
  else
    printf("Erro ao remover elemento!\n");
    
  pausar();
}

void menuModificarElemento(ListaEstatica *lista)
{
  int posicao, sucesso;
  Aluno novoElemento;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║       MODIFICAR ELEMENTO             ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para modificar.\n");
    pausar();
    return;
  }

  printf("Lista atual:\n");
  for (int i = 0; i <= lista->ultimo; i++) {
    printf("   [%d] %d - %s\n", i, lista->elementos[i].matricula, lista->elementos[i].nome);
  }

  printf("\nDigite a posicao a modificar (0 a %d): ", lista->ultimo);
  scanf("%d", &posicao);

  if (posicao < 0 || posicao > lista->ultimo) {
    printf("Posicao invalida!\n");
    pausar();
    return;
  }

  printf("Digite a nova matricula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o novo nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  removerQuebraLinha(novoElemento.nome);

  sucesso = modificarElemento(lista, posicao, novoElemento);

  printf("\n");
  if (sucesso)
    printf("Elemento modificado com sucesso!\n");
  else
    printf("Erro ao modificar elemento!\n");
    
  pausar();
}

void menuPesquisarElemento(ListaEstatica *lista) {
  int matricula, encontrado;

  limparTela();
  printf("╔══════════════════════════════════════╗\n");
  printf("║        PESQUISAR ELEMENTO            ║\n");
  printf("╚══════════════════════════════════════╝\n\n");

  if (listaVazia(lista)) {
    printf("Lista vazia! Nada para pesquisar.\n");
    pausar();
    return;
  }

  printf("Digite a matricula para pesquisar: ");
  scanf("%d", &matricula);

  encontrado = pesquisarElemento(lista, matricula);

  printf("\n");
  if (encontrado >= 0) {
    printf("Elemento encontrado!\n");
    printf("┌─────────────┬────────────────────────┐\n");
    printf("│  Posicao    │ %2d                    │\n", encontrado);
    printf("│  Matricula  │ %-22d                  │\n", lista->elementos[encontrado].matricula);
    printf("│  Nome       │ %-22s                  │\n", lista->elementos[encontrado].nome);
    printf("└─────────────┴────────────────────────┘\n");
  } else {
    printf("Elemento nao encontrado!\n");
  }
  
  pausar();
}

int main()
{
  ListaEstatica lista;
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
      menuInserirPosicao(&lista);
      break;

    case 3:
      menuInserirFim(&lista);
      break;

    case 4:
      menuRemoverPosicao(&lista);
      break;

    case 5:
      menuModificarElemento(&lista);
      break;

    case 6:
      menuPesquisarElemento(&lista);
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
      printf("Por favor, escolha uma opcao valida (0-6).\n");
      pausar();
      break;
    }
  } while (opcao != 0);

  return 0;
}
