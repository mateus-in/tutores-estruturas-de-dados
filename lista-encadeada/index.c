#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int numCamisa;
  char nome[50];
} Jogador;

typedef struct celula {
  Jogador info;
  struct celula *prox;
} Celula;

void inicializarLista(Celula **lista) {
  (*lista) = NULL;
}

int listaVazia(Celula **lista) {
  if ((*lista) == NULL)
    return 1;

  return 0;
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

int main() {
  Celula *bolinha;

  Jogador j1 = {10, "Joãozin"};
  Jogador j2 = {8, "Betin"};
  Jogador j3 = {3, "Batatinha"};

  inicializarLista(&bolinha);

  exibirElementos(&bolinha);
  inserirFim(&bolinha, j1);
  inserirFim(&bolinha, j2);
  inserirInicio(&bolinha, j3);
  exibirElementos(&bolinha);

  return 0;
}
