#include <stdio.h>
#include <string.h>

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

// FUNÇÕES DA LISTA ESTÁTICA
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
void exibirMenu(int *opcao)
{
  printf("*****Lista Estática*****\n\n");
  printf("1 - Exibir elementos\n");
  printf("2 - Inserir na posição\n");
  printf("3 - Inserir no fim\n");
  printf("4 - Remover na posição\n");
  printf("5 - Modificar elemento\n");
  printf("6 - Pesquisar elemento\n");
  printf("0 - Sair\n\n");
  printf("Escolha uma opção: ");
  scanf("%d", opcao);
}

void menuExibirElementos(ListaEstatica *lista) {
  exibirElementos(lista);
}

void menuInserirPosicao(ListaEstatica *lista)
{
  int posicao, sucesso;
  Aluno novoElemento;

  printf("Digite a posição: ");
  scanf("%d", &posicao);

  printf("Digite a matrícula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  sucesso = inserirPosicao(lista, posicao, novoElemento);

  if (sucesso)
    printf("Elemento inserido com sucesso!\n");
  else
    printf("Erro ao inserir elemento!\n");
}

void menuInserirFim(ListaEstatica *lista)
{
  int sucesso;
  Aluno novoElemento;

  printf("Digite a matrícula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  sucesso = inserirFim(lista, novoElemento);

  if (sucesso)
    printf("Elemento inserido com sucesso!\n");
  else
    printf("Erro ao inserir elemento!\n");
}

void menuRemoverPosicao(ListaEstatica *lista) {
  int sucesso, posicao;

  printf("Digite a posição: ");
  scanf("%d", &posicao);

  sucesso = removerPosicao(lista, posicao);

  if (sucesso)
    printf("Elemento removido com sucesso!\n");
  else
    printf("Erro ao remover elemento!\n");
}

void menuModificarElemento(ListaEstatica *lista)
{
  int posicao, sucesso;
  Aluno novoElemento;

  printf("Digite a posição: ");
  scanf("%d", &posicao);

  printf("Digite a matrícula do aluno: ");
  scanf("%d", &novoElemento.matricula);

  limparBuffer();

  printf("Digite o nome do aluno: ");
  fgets(novoElemento.nome, 50, stdin);

  sucesso = modificarElemento(lista, posicao, novoElemento);

  if (sucesso)
    printf("Elemento modificado com sucesso!\n");
  else
    printf("Erro ao modificar elemento!\n");
}

void menuPesquisarElemento(ListaEstatica *lista) {
  int matricula, encontrado;

  printf("Matrícula para pesquisar: ");
  scanf("%d", &matricula);

  encontrado = pesquisarElemento(lista, matricula);

  if (encontrado >= 0) {
    printf("%d - %s\n", lista->elementos[encontrado].matricula, lista->elementos[encontrado].nome);
  } else {
    printf("Elemento não encontrado!\n");
  }
}

int main()
{
  ListaEstatica lista;
  int opcao;

  inicializarLista(&lista);

  do
  {
    exibirMenu(&opcao);

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

    default:
      break;
    }
  } while (opcao != 0);

  return 0;
}
