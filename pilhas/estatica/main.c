#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 5

// Estrutura que representa um produto
typedef struct {
    int codigo;
    char nome[50];
    float preco;
} Produto;

// Estrutura que representa a pilha estática
typedef struct {
    Produto elementos[MAX_ELEMENTOS];
    int topo;
} PilhaEstatica;

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

void inicializarPilha(PilhaEstatica *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(PilhaEstatica *pilha) {
    return (pilha->topo == -1);
}

int pilhaCheia(PilhaEstatica *pilha) {
    return (pilha->topo == (MAX_ELEMENTOS - 1));
}

void exibirCabecalho(PilhaEstatica *pilha) {
    int total = pilha->topo + 1;
    char status[20];
    
    if (pilhaVazia(pilha)) {
        strcpy(status, "VAZIA");
    } else if (pilhaCheia(pilha)) {
        strcpy(status, "CHEIA");
    } else {
        strcpy(status, "PARCIAL");
    }
    
    printf("╔══════════════════════════════════════╗\n");
    printf("║            PILHA ESTÁTICA            ║\n");
    printf("║         Sistema de Produtos          ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ Status: %-8s | Produtos: %d/%d      ║\n", status, total, MAX_ELEMENTOS);
    printf("╚══════════════════════════════════════╝\n\n");
}

int push(PilhaEstatica *pilha, Produto elemento) {
    if (pilhaCheia(pilha)) {
        return 0; // Falha: pilha cheia
    }
    
    pilha->topo++;
    pilha->elementos[pilha->topo] = elemento;
    return 1; // Sucesso
}

Produto pop(PilhaEstatica *pilha) {
    Produto elementoVazio = {-1, "", 0.0};
    
    if (pilhaVazia(pilha)) {
        return elementoVazio; // Retorna elemento inválido
    }
    
    Produto elemento = pilha->elementos[pilha->topo];
    pilha->topo--;
    return elemento;
}

Produto top(PilhaEstatica *pilha) {
    Produto elementoVazio = {-1, "", 0.0};
    
    if (pilhaVazia(pilha)) {
        return elementoVazio; // Retorna elemento inválido
    }
    
    return pilha->elementos[pilha->topo];
}

int tamanho(PilhaEstatica *pilha) {
    return (pilha->topo + 1);
}

void exibirPilha(PilhaEstatica *pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha está vazia!\n");
        return;
    }
    
    printf("PILHA (Topo → Base):\n");
    printf("┌─────────────────────────────────────────────────────┐\n");
    printf("│ Pos │ Código │ Nome                  │ Preço         │\n");
    printf("├─────┼────────┼───────────────────────┼───────────────┤\n");
    
    for (int i = pilha->topo; i >= 0; i--) {
        printf("│ [%d] │ %-6d │ %-20s │ R$ %10.2f │\n", 
               i, 
               pilha->elementos[i].codigo,
               pilha->elementos[i].nome,
               pilha->elementos[i].preco);
    }
    
    printf("└─────────────────────────────────────────────────────┘\n");
    printf("💡 Elemento [%d] é o TOPO da pilha\n", pilha->topo);
}

// ========== FUNÇÕES DO MENU ==========

void exibirMenu(PilhaEstatica *pilha, int *opcao) {
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
    printf("│  6 - Verificar se está cheia         │\n");
    printf("│  7 - Consultar tamanho               │\n");
    printf("│  0 - Sair                            │\n");
    printf("└──────────────────────────────────────┘\n\n");
    
    printf("Escolha uma opção: ");
    scanf("%d", opcao);
    limparBuffer();
}

void menuExibirPilha(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VISUALIZAR PILHA ═══════════════\n\n");
    exibirPilha(pilha);
    
    pausar();
}

void menuPush(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ EMPILHAR PRODUTO ═══════════════\n\n");
    
    if (pilhaCheia(pilha)) {
        printf("❌ ERRO: Pilha cheia! Não é possível empilhar.\n");
        printf("💡 Dica: Desempilhe alguns produtos primeiro.\n");
        pausar();
        return;
    }
    
    Produto produto;
    
    printf("📦 Digite os dados do produto:\n\n");
    
    printf("Código: ");
    scanf("%d", &produto.codigo);
    limparBuffer();
    
    printf("Nome: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    removerQuebraLinha(produto.nome);
    
    printf("Preço: R$ ");
    scanf("%f", &produto.preco);
    limparBuffer();
    
    if (push(pilha, produto)) {
        printf("\n✅ Produto empilhado com sucesso!\n");
        printf("📊 Produtos na pilha: %d/%d\n", tamanho(pilha), MAX_ELEMENTOS);
    } else {
        printf("\n❌ Erro ao empilhar produto!\n");
    }
    
    pausar();
}

void menuPop(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ DESEMPILHAR PRODUTO ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("❌ ERRO: Pilha vazia! Não há produtos para desempilhar.\n");
        printf("💡 Dica: Empilhe alguns produtos primeiro.\n");
        pausar();
        return;
    }
    
    printf("📦 Produto no topo da pilha:\n");
    Produto topo = top(pilha);
    printf("   Código: %d\n", topo.codigo);
    printf("   Nome: %s\n", topo.nome);
    printf("   Preço: R$ %.2f\n\n", topo.preco);
    
    printf("❓ Deseja realmente desempilhar este produto? (s/n): ");
    char resposta;
    scanf("%c", &resposta);
    limparBuffer();
    
    if (resposta == 's' || resposta == 'S') {
        Produto removido = pop(pilha);
        if (removido.codigo != -1) {
            printf("\n✅ Produto desempilhado com sucesso!\n");
            printf("📦 Produto removido: %s\n", removido.nome);
            printf("📊 Produtos restantes: %d/%d\n", tamanho(pilha), MAX_ELEMENTOS);
        } else {
            printf("\n❌ Erro ao desempilhar produto!\n");
        }
    } else {
        printf("\n↩️ Operação cancelada.\n");
    }
    
    pausar();
}

void menuConsultarTopo(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TOPO ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("❌ ERRO: Pilha vazia! Não há produtos no topo.\n");
        printf("💡 Dica: Empilhe alguns produtos primeiro.\n");
        pausar();
        return;
    }
    
    Produto topo = top(pilha);
    
    printf("🔝 PRODUTO NO TOPO DA PILHA:\n");
    printf("┌─────────────────────────────────────────────────────┐\n");
    printf("│ Código: %-6d                                     │\n", topo.codigo);
    printf("│ Nome: %-40s │\n", topo.nome);
    printf("│ Preço: R$ %-10.2f                              │\n", topo.preco);
    printf("└─────────────────────────────────────────────────────┘\n");
    
    printf("\n📊 Posição do topo: [%d]\n", pilha->topo);
    printf("📊 Total de produtos: %d/%d\n", tamanho(pilha), MAX_ELEMENTOS);
    
    pausar();
}

void menuVerificarVazia(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VERIFICAR SE ESTÁ VAZIA ═══════════════\n\n");
    
    if (pilhaVazia(pilha)) {
        printf("✅ A pilha está VAZIA!\n");
        printf("📊 Produtos na pilha: 0/%d\n", MAX_ELEMENTOS);
        printf("💡 Dica: Use a opção 2 para empilhar produtos.\n");
    } else {
        printf("❌ A pilha NÃO está vazia!\n");
        printf("📊 Produtos na pilha: %d/%d\n", tamanho(pilha), MAX_ELEMENTOS);
        printf("💡 Dica: Use a opção 3 para desempilhar produtos.\n");
    }
    
    pausar();
}

void menuVerificarCheia(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ VERIFICAR SE ESTÁ CHEIA ═══════════════\n\n");
    
    if (pilhaCheia(pilha)) {
        printf("✅ A pilha está CHEIA!\n");
        printf("📊 Produtos na pilha: %d/%d\n", MAX_ELEMENTOS, MAX_ELEMENTOS);
        printf("💡 Dica: Use a opção 3 para desempilhar produtos.\n");
    } else {
        printf("❌ A pilha NÃO está cheia!\n");
        printf("📊 Produtos na pilha: %d/%d\n", tamanho(pilha), MAX_ELEMENTOS);
        printf("📊 Espaços livres: %d\n", MAX_ELEMENTOS - tamanho(pilha));
        printf("💡 Dica: Use a opção 2 para empilhar mais produtos.\n");
    }
    
    pausar();
}

void menuConsultarTamanho(PilhaEstatica *pilha) {
    limparTela();
    exibirCabecalho(pilha);
    
    printf("═══════════════ CONSULTAR TAMANHO ═══════════════\n\n");
    
    int total = tamanho(pilha);
    int livres = MAX_ELEMENTOS - total;
    float percentual = (float)total / MAX_ELEMENTOS * 100;
    
    printf("📊 ESTATÍSTICAS DA PILHA:\n");
    printf("┌─────────────────────────────────────────────────────┐\n");
    printf("│ Total de produtos: %-6d                           │\n", total);
    printf("│ Capacidade máxima: %-6d                           │\n", MAX_ELEMENTOS);
    printf("│ Espaços livres: %-6d                              │\n", livres);
    printf("│ Percentual usado: %.1f%%                            │\n", percentual);
    printf("│ Índice do topo: %-6d                              │\n", pilha->topo);
    printf("└─────────────────────────────────────────────────────┘\n");
    
    printf("\n📈 REPRESENTAÇÃO VISUAL:\n");
    printf("Pilha: [");
    for (int i = 0; i < MAX_ELEMENTOS; i++) {
        if (i <= pilha->topo) {
            printf("█");
        } else {
            printf("░");
        }
    }
    printf("] %.1f%%\n", percentual);
    
    pausar();
}

// ========== FUNÇÃO PRINCIPAL ==========

int main() {
    PilhaEstatica pilha;
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
                menuVerificarCheia(&pilha);
                break;
            case 7:
                menuConsultarTamanho(&pilha);
                break;
            case 0:
                limparTela();
                printf("╔══════════════════════════════════════╗\n");
                printf("║       PROGRAMA FINALIZADO!           ║\n");
                printf("║                                      ║\n");
                printf("║  Obrigado por usar o sistema de      ║\n");
                printf("║         Pilha Estática! 🚀          ║\n");
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