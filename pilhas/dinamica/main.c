#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Estrutura que representa um livro
typedef struct {
    int isbn;
    char titulo[100];
    char autor[50];
    int paginas;
} Livro;

// Estrutura que representa um nó da pilha
typedef struct no {
    Livro info;
    struct no *proximo;
} No;

// ========== FUNÇÕES AUXILIARES ==========

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

// ========== FUNÇÕES DA PILHA ==========

void inicializarPilha(No **pilha) {
    *pilha = NULL;
}

int pilhaVazia(No **pilha) {
    return (*pilha == NULL);
}

int contarElementos(No **pilha) {
    if (pilhaVazia(pilha)) {
        return 0;
    }

    No *aux = *pilha;
    int contador = 0;
    
    while (aux != NULL) {
        contador++;
        aux = aux->proximo;
    }
    
    return contador;
}

void exibirCabecalho(No **pilha) {
    int tamanho = contarElementos(pilha);
    char status[20];
    
    if (pilhaVazia(pilha)) {
        strcpy(status, "VAZIA");
    } else {
        strcpy(status, "COM DADOS");
    }
    
    printf("╔══════════════════════════════════════╗\n");
    printf("║           PILHA DINÂMICA             ║\n");
    printf("║          Sistema de Livros           ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ Status: %-10s | Livros: %-6d      ║\n", status, tamanho);
    printf("╚══════════════════════════════════════╝\n\n");
}

No* criarNo(Livro elemento) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("❌ ERRO: Memória insuficiente!\n");
        return NULL;
    }
    
    novo->info = elemento;
    novo->proximo = NULL;
    return novo;
}

int push(No **pilha, Livro elemento) {
    No *novo = criarNo(elemento);
    if (novo == NULL) {
        return 0; // Falha na alocação
    }
    
    novo->proximo = *pilha;
    *pilha = novo;
    
    return 1; // Sucesso
}

Livro pop(No **pilha) {
    Livro livroVazio = {-1, "", "", 0};
    
    if (pilhaVazia(pilha)) {
        return livroVazio; // Retorna livro inválido
    }
    
    No *removido = *pilha;
    Livro elemento = removido->info;
    
    *pilha = (*pilha)->proximo;
    free(removido);
    
    return elemento;
}

Livro top(No **pilha) {
    Livro livroVazio = {-1, "", "", 0};
    
    if (pilhaVazia(pilha)) {
        return livroVazio; // Retorna livro inválido
    }
    
    return (*pilha)->info;
}

void exibirPilha(No **pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha está vazia!\n");
        return;
    }
    
    int tamanho = contarElementos(pilha);
    
    printf("PILHA DINÂMICA (Topo → Base):\n");
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Pos │ ISBN     │ Título                     │ Autor           │ Pág.│\n");
    printf("├─────┼──────────┼────────────────────────────┼─────────────────┼─────┤\n");
    
    No *atual = *pilha;
    int posicao = tamanho - 1;
    
    while (atual != NULL) {
        char simbolo = (atual == *pilha) ? '>' : '|';
        printf("│ %c%2d │ %-8d │ %-26s │ %-15s │ %3d │\n", 
               simbolo,
               posicao,
               atual->info.isbn,
               atual->info.titulo,
               atual->info.autor,
               atual->info.paginas);
        
        atual = atual->proximo;
        posicao--;
    }
    
    printf("└────────────────────────────────────────────────────────────────────┘\n");
    printf("💡 Topo da pilha: [%d] elementos empilhados\n", tamanho);
}

void liberarPilha(No **pilha) {
    while (!pilhaVazia(pilha)) {
        pop(pilha); // Pop já faz o free() interno
    }
    printf("✅ Memória da pilha liberada com sucesso!\n");
}

// ========== FUNÇÕES DO MENU ==========

void exibirMenu(No **pilha, int *opcao) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("┌──────────────────────────────────────┐\n");
    printf("│                MENU                  │\n");
    printf("├──────────────────────────────────────┤\n");
    printf("│  1 - Exibir pilha                    │\n");
    printf("│  2 - Empilhar (Push)                 │\n");
    printf("│  3 - Desempilhar (Pop)               │\n");
    printf("│  4 - Consultar topo                  │\n");
    printf("│  5 - Verificar se está vazia         │\n");
    printf("│  6 - Consultar tamanho               │\n");
    printf("│  7 - Liberar pilha                   │\n");
    printf("│  0 - Sair                            │\n");
    printf("└──────────────────────────────────────┘\n\n");
    
    printf("Escolha uma opção: ");
    scanf("%d", opcao);
    limparBuffer();
}

void menuExibirPilha(No **pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VISUALIZAR PILHA ═══════════════\n\n");
    exibirPilha(pilha);
    
    if (!pilhaVazia(pilha)) {
        printf("\n📊 Informações da Pilha:\n");
        printf("   • Total de livros: %d\n", contarElementos(pilha));
        printf("   • Memória utilizada: ~%lu bytes\n", contarElementos(pilha) * sizeof(No));
        printf("   • Último livro empilhado: %s\n", (*pilha)->info.titulo);
    }
    
    pausar();
}

void menuPush(No **pilha) {
    Livro novoLivro;
    int sucesso;
    
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ EMPILHAR LIVRO ═══════════════\n\n");
    
    printf("📚 Digite os dados do livro:\n\n");
    
    printf("ISBN: ");
    scanf("%d", &novoLivro.isbn);
    limparBuffer();
    
    printf("Título: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    removerQuebraLinha(novoLivro.titulo);
    
    printf("Autor: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    removerQuebraLinha(novoLivro.autor);
    
    printf("Páginas: ");
    scanf("%d", &novoLivro.paginas);
    limparBuffer();
    
    sucesso = push(pilha, novoLivro);
    
    printf("\n");
    if (sucesso) {
        printf("✅ Livro empilhado com sucesso!\n");
        printf("   📖 %s - %s\n", novoLivro.titulo, novoLivro.autor);
        printf("   📊 Total na pilha: %d livros\n", contarElementos(pilha));
    } else {
        printf("❌ Erro ao empilhar livro! Memória insuficiente.\n");
    }
    
    pausar();
}

void menuPop(No **pilha) {
    Livro removido;
    
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ DESEMPILHAR LIVRO ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("❌ ERRO: Pilha vazia! Não há livros para desempilhar.\n");
        printf("💡 Dica: Empilhe alguns livros primeiro.\n");
        pausar();
        return;
    }
    
    printf("📚 Livro no topo da pilha:\n");
    removido = pop(pilha);
    
    if (removido.isbn != -1) {
        printf("\n✅ Livro desempilhado com sucesso!\n");
        printf("   📖 %s - %s\n", removido.titulo, removido.autor);
        printf("   📊 Restam na pilha: %d livros\n", contarElementos(pilha));
        
        if (!pilhaVazia(pilha)) {
            printf("\n🔝 Novo topo: %s\n", (*pilha)->info.titulo);
        } else {
            printf("\n📭 Pilha agora está vazia!\n");
        }
    } else {
        printf("\n❌ Erro ao desempilhar livro!\n");
    }
    
    pausar();
}

void menuConsultarTopo(No **pilha) {
    Livro topo;
    
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TOPO ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("❌ ERRO: Pilha vazia! Não há livros no topo.\n");
        printf("💡 Dica: Empilhe alguns livros primeiro.\n");
        pausar();
        return;
    }
    
    topo = top(pilha);
    
    printf("🔝 LIVRO NO TOPO DA PILHA:\n");
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ ISBN: %-10d                                              │\n", topo.isbn);
    printf("│ Título: %-55s │\n", topo.titulo);
    printf("│ Autor: %-56s │\n", topo.autor);
    printf("│ Páginas: %-53d │\n", topo.paginas);
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    
    printf("\n📊 Informações da Pilha:\n");
    printf("   • Total de livros: %d\n", contarElementos(pilha));
    printf("   • Endereço do topo: %p\n", (void*)(*pilha));
    printf("   • Próximo elemento: %p\n", (void*)(*pilha)->proximo);
    
    pausar();
}

void menuVerificarVazia(No **pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VERIFICAR SE ESTÁ VAZIA ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("✅ A pilha está VAZIA!\n");
        printf("📊 Livros na pilha: 0\n");
        printf("💾 Memória utilizada: 0 bytes\n");
        printf("🎯 Ponteiro do topo: NULL\n");
        printf("💡 Dica: Use a opção 2 para empilhar livros.\n");
    } else {
        printf("❌ A pilha NÃO está vazia!\n");
        printf("📊 Livros na pilha: %d\n", contarElementos(pilha));
        printf("💾 Memória utilizada: ~%lu bytes\n", contarElementos(pilha) * sizeof(No));
        printf("🎯 Ponteiro do topo: %p\n", (void*)(*pilha));
        printf("📚 Livro no topo: %s\n", (*pilha)->info.titulo);
        printf("💡 Dica: Use a opção 3 para desempilhar livros.\n");
    }
    
    pausar();
}

void menuConsultarTamanho(No **pilha) {
    int tamanho = contarElementos(pilha);
    
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TAMANHO ═══════════════\n\n");
    
    printf("📊 INFORMAÇÕES DA PILHA:\n");
    printf("┌─────────────────────────┬─────────┐\n");
    printf("│ Total de livros         │   %5d │\n", tamanho);
    
    if (tamanho == 0) {
        printf("│ Status                  │   VAZIA │\n");
        printf("│ Memória utilizada       │   0 KB  │\n");
    } else {
        printf("│ Status                  │   ATIVA │\n");
        printf("│ Memória utilizada       │ %4d KB │\n", 
               (tamanho * (int)sizeof(No)) / 1024 + 1);
        printf("│ Livro no topo           │ %-7s │\n", (*pilha)->info.titulo);
    }
    
    printf("└─────────────────────────┴─────────┘\n");
    
    if (tamanho > 0) {
        printf("\n📈 ESTATÍSTICAS:\n");
        
        // Calcular estatísticas
        int totalPaginas = 0;
        int isbnMin = (*pilha)->info.isbn;
        int isbnMax = (*pilha)->info.isbn;
        
        No *atual = *pilha;
        while (atual != NULL) {
            totalPaginas += atual->info.paginas;
            if (atual->info.isbn < isbnMin) isbnMin = atual->info.isbn;
            if (atual->info.isbn > isbnMax) isbnMax = atual->info.isbn;
            atual = atual->proximo;
        }
        
        float mediaPaginas = (float)totalPaginas / tamanho;
        
        printf("   • Páginas totais: %d\n", totalPaginas);
        printf("   • Média de páginas: %.1f\n", mediaPaginas);
        printf("   • ISBN menor: %d\n", isbnMin);
        printf("   • ISBN maior: %d\n", isbnMax);
    }
    
    pausar();
}

void menuLiberarPilha(No **pilha) {
    int confirmacao;
    int totalAntes = contarElementos(pilha);
    
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ LIBERAR PILHA ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("ℹ️ A pilha já está vazia! Não há memória para liberar.\n");
        pausar();
        return;
    }
    
    printf("⚠️ ATENÇÃO: Esta operação irá remover TODOS os %d livros da pilha!\n", totalAntes);
    printf("📊 Livros a serem removidos:\n");
    
    No *atual = *pilha;
    int contador = 1;
    while (atual != NULL && contador <= 3) { // Mostrar apenas os 3 primeiros
        printf("   %d. %s - %s\n", contador, atual->info.titulo, atual->info.autor);
        atual = atual->proximo;
        contador++;
    }
    if (totalAntes > 3) {
        printf("   ... e mais %d livros\n", totalAntes - 3);
    }
    
    printf("\nDeseja realmente liberar toda a pilha? (1-Sim / 0-Não): ");
    scanf("%d", &confirmacao);
    
    if (confirmacao == 1) {
        printf("\n🔄 Liberando memória");
        
        // Animação visual
        for (int i = 0; i < 3; i++) {
            printf(".");
            fflush(stdout);
            #ifdef _WIN32
                Sleep(500);
            #else
                usleep(500000);
            #endif
        }
        
        liberarPilha(pilha);
        
        printf("\n✅ Pilha liberada com sucesso!\n");
        printf("📊 Livros removidos: %d\n", totalAntes);
        printf("💾 Memória liberada: ~%lu bytes\n", totalAntes * sizeof(No));
        printf("🎯 Status atual: VAZIA\n");
    } else {
        printf("\n↩️ Operação cancelada. Pilha mantida intacta.\n");
    }
    
    pausar();
}

// ========== FUNÇÃO PRINCIPAL ==========

int main() {
    No *pilha;
    int opcao;
    
    inicializarPilha(&pilha);
    
    do {
        exibirMenu(&pilha, &opcao);
        
        switch (opcao) {
            case 1:
                menuExibirPilha(&pilha);
                break;
            case 2:
                menuPush(&pilha);
                break;
            case 3:
                menuPop(&pilha);
                break;
            case 4:
                menuConsultarTopo(&pilha);
                break;
            case 5:
                menuVerificarVazia(&pilha);
                break;
            case 6:
                menuConsultarTamanho(&pilha);
                break;
            case 7:
                menuLiberarPilha(&pilha);
                break;
            case 0:
                // Cleanup automático antes de sair
                if (!pilhaVazia(&pilha)) {
                    printf("\n🔄 Limpando memória antes de sair...\n");
                    liberarPilha(&pilha);
                }
                
                limparTela();
                printf("╔══════════════════════════════════════╗\n");
                printf("║       PROGRAMA FINALIZADO!           ║\n");
                printf("║                                      ║\n");
                printf("║  Obrigado por usar o sistema de      ║\n");
                printf("║        Pilha Dinâmica! 🚀           ║\n");
                printf("║                                      ║\n");
                printf("║   Memória liberada com segurança     ║\n");
                printf("╚══════════════════════════════════════╝\n");
                break;
            default:
                limparTela();
                printf("❌ Opção inválida! Tente novamente.\n");
                pausar();
                break;
        }
    } while (opcao != 0);
    
    return 0;
} 