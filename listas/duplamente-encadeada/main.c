#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int numCamisa;
  char nome[50];
} Jogador;

typedef struct celula {
    struct celula* ante;
    Jogador elemento;
    struct celula* prox;
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

int inserirNoFim(Celula **lista, Jogador novo) {
    // Armazenará o endereço de memória de uma nova célula;
    Celula * novaCelula;
    // Ponteiro auxiliar que será utilizado para percorrer a lista.
    Celula * auxiliar;
    
    // Obtendo uma nova célula para o novo elemento.
    novaCelula = criarCelula();
    // Verificar se foi possível alocar memória
    if (novaCelula == NULL) {
        printf("Erro: Memória cheia.\n");
        return 0;
    }
    
    // Colocando o novo elemento dentro da nova célula
    novaCelula->elemento = novo;
    novaCelula->prox = NULL;
    novaCelula->ante = NULL;
    
    // Se a lista estiver vazia, o ponteiro
    // externo apontará para a nova célula.
    if (listaVazia(lista)) {
        (*lista) = novaCelula;
        return 1;
    }
    
    // Auxiliar começa na primeira célula
    auxiliar = (*lista);
    // Percorre a lista até a última célula
    while (auxiliar->prox != NULL) {
        auxiliar = auxiliar->prox;
    }
    
    // O campo prox da última célula agora
    // apontará para a nova célula
    novaCelula->ante = auxiliar;
    auxiliar->prox = novaCelula;
    return 1;
}

int inserirNoInicio(Celula ** lista, Jogador novo) {
    Celula * novaCelula = criarCelula();
    
    // Se lista vazia, chama inserirNoFim()
    if (listaVazia(lista)) {
        return inserirNoFim(lista, novo);
    }
    
    // Preenchendo a nova célula
    novaCelula->elemento = novo;
    novaCelula->ante = NULL;
    // Fazendo o campo prox da nova célula apontar
    // para a primeira célula da lista
    novaCelula->prox = (*lista);
    (*lista)->ante = novaCelula;
    
    // Fazendo o ponteiro externo
    // apontar para a nova célula.
    (*lista) = novaCelula;
    return 1;
}

Jogador criarElemento(int numCamisa, char nome[]) {
    Jogador elemento;
    strcpy(elemento.nome, nome);
    elemento.numCamisa = numCamisa;
    return elemento;
}

Jogador removerNoInicio(Celula ** lista) {
    Celula * removida;
    Jogador removido = criarElemento(-1, "");
    
    // Se a lista vazia, não é possível remover
    if (listaVazia(lista)) {
        printf("Erro: Lista vazia");
        return removido; // removido = elemento vazio
    }
    
    // Guarda o endereço da célula que será removida
    removida = (*lista);
    // Faz uma cópia do elemento da célula removida
    removido = removida->elemento;
    
    // Faz a lista apontar para a segunda célula
    (*lista) = (*lista)->prox;
    // Se ainda há elementos na lista
    if ((*lista) != NULL) {
        (*lista)->ante = NULL;
    }
    
    // Remove a primeira célula
    free(removida);
    return removido;
}

Jogador removerNoFim(Celula ** lista) {
    Celula * removida;
    Jogador removido = criarElemento(-1, "");
    
    // Verifica se lista vazia
    if (listaVazia(lista)) {
        printf("Erro: Lista vazia\n");
        return removido;
    }
    
    // Encontrando a última célula
    removida = (*lista);
    while (removida->prox != NULL) {
        removida = removida->prox;
    }
    
    // Se só tiver 1 elemento na lista
    if (removida == (*lista)) {
        return removerNoInicio(lista);
    }
    
    removida->ante->prox = NULL;
    // Removendo a última célula
    removido = removida->elemento;
    free(removida);
    return removido;
}

Celula * pesquisar(Celula ** lista, Jogador pesquisado) {
    Celula * auxiliar;
    
    // Se lista vazia, retorna NULL
    if (listaVazia(lista)) {
        printf("Erro: Lista vazia\n");
        return NULL;
    }
    
    // Auxiliar começa a pesquisa na primeira célula
    auxiliar = (*lista);
    
    // Enquanto diferente de fim da lista
    while (auxiliar != NULL) {
        // Se o elemento pesquisado é = o da célula
        if (strcmp(auxiliar->elemento.nome, pesquisado.nome) == 0) {
            return auxiliar; // Retorna o end. da célula
        }
        
        // Auxiliar agora é o elemento da frente
        auxiliar = auxiliar->prox;
    }
    
    // Se chegar até aqui, então o elemento pesquisado
    // não foi encontrado, portanto retorna NULL
    return NULL;
}

Jogador removerElemento(Celula ** lista, Jogador elemento) {
    Celula * removida;
    Jogador removido = criarElemento(-1, "");
    
    // Se lista vazia
    if (listaVazia(lista)) {
        printf("Erro: Lista vazia\n");
        return removido;
    }
    
    // Pesquisar o elemento na lista
    removida = pesquisar(lista, elemento);
    
    // Caso o elemento pesquisado não esteja na lista
    if (removida == NULL) {
        printf("Erro: elemento nao encontrado.\n");
        return removido;
    }
    
    removido = removida->elemento;
    
    // Caso o elemento pesquisado seja o primeiro
    if (removida == (*lista)) {
        return removerNoInicio(lista);
    }
    
    // Caso o elemento pesquisado seja o último
    if (removida->prox == NULL) {
        return removerNoFim(lista);
    }
    
    // Fazer a ligação da lista
    removida->ante->prox = removida->prox;
    removida->prox->ante = removida->ante;
    
    // Remover o elemento pesquisado
    free(removida);
    return removido;
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = 0;
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
    printf("║     LISTA DUPLAMENTE ENCADEADA       ║\n");
    printf("║         Sistema de Jogadores         ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ Status: %-8s | Jogadores: %d      ║\n", status, total);
    printf("╚══════════════════════════════════════╝\n\n");
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
            aux->elemento.numCamisa,
            aux->elemento.nome
        );

        aux = aux->prox;
    }
}

int compararElemento(Jogador j1, Jogador j2) {
    return strcmp(j1.nome, j2.nome);
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
            printf("│ %11d │ %-22s │\n", aux->elemento.numCamisa, aux->elemento.nome);
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

    sucesso = inserirNoInicio(lista, novoJogador);

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

    sucesso = inserirNoFim(lista, novoJogador);

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

    removido = removerNoInicio(lista);

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

    removido = removerNoFim(lista);

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
        printf("│ Num. Camisa │ %-22d │\n", encontrado->elemento.numCamisa);
        printf("│ Nome        │ %-22s │\n", encontrado->elemento.nome);
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
