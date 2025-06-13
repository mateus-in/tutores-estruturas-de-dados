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

// Estrutura que representa a pilha dinâmica
typedef struct {
    No *topo;
    int tamanho;
} PilhaDinamica;

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

void inicializarPilha(PilhaDinamica *pilha) {
    pilha->topo = NULL;
    pilha->tamanho = 0;
}

int pilhaVazia(PilhaDinamica *pilha) {
    return (pilha->topo == NULL);
}

int tamanho(PilhaDinamica *pilha) {
    return pilha->tamanho;
}

void exibirCabecalho(PilhaDinamica *pilha) {
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
    printf("║ Status: %-10s | Livros: %-6d      ║\n", status, pilha->tamanho);
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

int push(PilhaDinamica *pilha, Livro elemento) {
    No *novo = criarNo(elemento);
    if (novo == NULL) {
        return 0; // Falha na alocação
    }
    
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    
    return 1; // Sucesso
}

Livro pop(PilhaDinamica *pilha) {
    Livro livroVazio = {-1, "", "", 0};
    
    if (pilhaVazia(pilha)) {
        return livroVazio; // Retorna livro inválido
    }
    
    No *removido = pilha->topo;
    Livro elemento = removido->info;
    
    pilha->topo = pilha->topo->proximo;
    free(removido);
    pilha->tamanho--;
    
    return elemento;
}

Livro top(PilhaDinamica *pilha) {
    Livro livroVazio = {-1, "", "", 0};
    
    if (pilhaVazia(pilha)) {
        return livroVazio; // Retorna livro inválido
    }
    
    return pilha->topo->info;
}

void exibirPilha(PilhaDinamica *pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha está vazia!\n");
        return;
    }
    
    printf("PILHA DINÂMICA (Topo → Base):\n");
    printf("┌────────────────────────────────────────────────────────────────────┐\n");
    printf("│ Pos │ ISBN     │ Título                     │ Autor           │ Pág.│\n");
    printf("├─────┼──────────┼────────────────────────────┼─────────────────┼─────┤\n");
    
    No *atual = pilha->topo;
    int posicao = pilha->tamanho - 1;
    
    while (atual != NULL) {
        char simbolo = (atual == pilha->topo) ? '>' : '|';
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
    printf("💡 Topo da pilha: [%d] elementos empilhados\n", pilha->tamanho);
}

void liberarPilha(PilhaDinamica *pilha) {
    while (!pilhaVazia(pilha)) {
        pop(pilha); // Pop já faz o free() interno
    }
    printf("✅ Memória da pilha liberada com sucesso!\n");
}

// ========== FUNÇÕES DO MENU ==========

void exibirMenu(PilhaDinamica *pilha, int *opcao) {
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

void menuExibirPilha(PilhaDinamica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VISUALIZAR PILHA ═══════════════\n\n");
    exibirPilha(pilha);
    
    if (!pilhaVazia(pilha)) {
        printf("\n📊 Informações da Pilha:\n");
        printf("   • Total de livros: %d\n", pilha->tamanho);
        printf("   • Memória utilizada: ~%lu bytes\n", pilha->tamanho * sizeof(No));
        printf("   • Último livro empilhado: %s\n", pilha->topo->info.titulo);
    }
    
    pausar();
}

void menuPush(PilhaDinamica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ EMPILHAR LIVRO ═══════════════\n\n");
    
    Livro livro;
    
    printf("📚 Digite os dados do livro:\n\n");
    
    printf("ISBN: ");
    scanf("%d", &livro.isbn);
    limparBuffer();
    
    printf("Título: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    removerQuebraLinha(livro.titulo);
    
    printf("Autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    removerQuebraLinha(livro.autor);
    
    printf("Páginas: ");
    scanf("%d", &livro.paginas);
    limparBuffer();
    
    if (push(pilha, livro)) {
        printf("\n✅ Livro empilhado com sucesso!\n");
        printf("📊 Livros na pilha: %d\n", tamanho(pilha));
        printf("📚 Novo topo: %s\n", livro.titulo);
    } else {
        printf("\n❌ Erro ao empilhar livro! (Memória insuficiente)\n");
    }
    
    pausar();
}

void menuPop(PilhaDinamica *pilha) {
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
    Livro topo = top(pilha);
    printf("   ISBN: %d\n", topo.isbn);
    printf("   Título: %s\n", topo.titulo);
    printf("   Autor: %s\n", topo.autor);
    printf("   Páginas: %d\n\n", topo.paginas);
    
    printf("❓ Deseja realmente desempilhar este livro? (s/n): ");
    char resposta;
    scanf("%c", &resposta);
    limparBuffer();
    
    if (resposta == 's' || resposta == 'S') {
        Livro removido = pop(pilha);
        if (removido.isbn != -1) {
            printf("\n✅ Livro desempilhado com sucesso!\n");
            printf("📚 Livro removido: %s\n", removido.titulo);
            printf("📊 Livros restantes: %d\n", tamanho(pilha));
            printf("💾 Memória liberada: ~%lu bytes\n", sizeof(No));
        } else {
            printf("\n❌ Erro ao desempilhar livro!\n");
        }
    } else {
        printf("\n↩️ Operação cancelada.\n");
    }
    
    pausar();
}

void menuConsultarTopo(PilhaDinamica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TOPO ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("❌ ERRO: Pilha vazia! Não há livros no topo.\n");
        printf("💡 Dica: Empilhe alguns livros primeiro.\n");
        pausar();
        return;
    }
    
    Livro topo = top(pilha);
    
    printf("🔝 LIVRO NO TOPO DA PILHA:\n");
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ ISBN: %-10d                                              │\n", topo.isbn);
    printf("│ Título: %-55s │\n", topo.titulo);
    printf("│ Autor: %-56s │\n", topo.autor);
    printf("│ Páginas: %-53d │\n", topo.paginas);
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    
    printf("\n📊 Informações da Pilha:\n");
    printf("   • Total de livros: %d\n", pilha->tamanho);
    printf("   • Endereço do topo: %p\n", (void*)pilha->topo);
    printf("   • Próximo elemento: %p\n", (void*)pilha->topo->proximo);
    
    pausar();
}

void menuVerificarVazia(PilhaDinamica *pilha) {
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
        printf("📊 Livros na pilha: %d\n", tamanho(pilha));
        printf("💾 Memória utilizada: ~%lu bytes\n", pilha->tamanho * sizeof(No));
        printf("🎯 Ponteiro do topo: %p\n", (void*)pilha->topo);
        printf("📚 Livro no topo: %s\n", pilha->topo->info.titulo);
        printf("💡 Dica: Use a opção 3 para desempilhar livros.\n");
    }
    
    pausar();
}

void menuConsultarTamanho(PilhaDinamica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TAMANHO ═══════════════\n\n");
    
    int total = tamanho(pilha);
    size_t memoriaUsada = total * sizeof(No);
    size_t memoriaTotal = memoriaUsada + sizeof(PilhaDinamica);
    
    printf("📊 ESTATÍSTICAS DA PILHA DINÂMICA:\n");
    printf("┌─────────────────────────────────────────────────────────────────┐\n");
    printf("│ Total de livros: %-10d                                      │\n", total);
    printf("│ Memória por nó: %-10lu bytes                                │\n", sizeof(No));
    printf("│ Memória dos nós: %-10lu bytes                               │\n", memoriaUsada);
    printf("│ Memória da estrutura: %-10lu bytes                          │\n", sizeof(PilhaDinamica));
    printf("│ Memória total: %-10lu bytes                                 │\n", memoriaTotal);
    printf("│ Ponteiro do topo: %p                                     │\n", (void*)pilha->topo);
    printf("└─────────────────────────────────────────────────────────────────┘\n");
    
    if (total > 0) {
        printf("\n📈 REPRESENTAÇÃO DA PILHA:\n");
                 printf("Topo -> ");
         
         No *atual = pilha->topo;
         int count = 0;
         while (atual != NULL && count < 5) { // Mostra até 5 elementos
             printf("[%d]", atual->info.isbn);
             if (atual->proximo != NULL && count < 4) {
                 printf(" -> ");
             }
             atual = atual->proximo;
             count++;
         }
         
         if (atual != NULL) {
             printf(" -> ... (%d mais)", total - 5);
         }
         printf(" -> NULL\n");
    }
    
    pausar();
}

void menuLiberarPilha(PilhaDinamica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ LIBERAR PILHA ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("ℹ️ A pilha já está vazia! Não há memória para liberar.\n");
        pausar();
        return;
    }
    
    int totalAntes = tamanho(pilha);
    size_t memoriaLiberada = totalAntes * sizeof(No);
    
    printf("⚠️ ATENÇÃO: Esta operação irá remover TODOS os livros da pilha!\n");
    printf("📊 Livros a serem removidos: %d\n", totalAntes);
    printf("💾 Memória a ser liberada: ~%lu bytes\n", memoriaLiberada);
    
    printf("\n❓ Deseja realmente liberar toda a pilha? (s/n): ");
    char resposta;
    scanf("%c", &resposta);
    limparBuffer();
    
    if (resposta == 's' || resposta == 'S') {
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
        printf("💾 Memória liberada: ~%lu bytes\n", memoriaLiberada);
        printf("🎯 Status atual: VAZIA\n");
    } else {
        printf("\n↩️ Operação cancelada. Pilha mantida intacta.\n");
    }
    
    pausar();
}

// ========== FUNÇÃO PRINCIPAL ==========

int main() {
    PilhaDinamica pilha;
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