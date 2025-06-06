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

int main() {
  Celula *lista;

  //

  return 0;
}
