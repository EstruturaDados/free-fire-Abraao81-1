#include <stdio.h>    // entrada e saída
#include <stdlib.h>   // funções gerais
#include <string.h>   // manipulação de strings

#define MAX_STR_LEN 30
#define TAM_MAX 10

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
typedef struct {
    char nome[MAX_STR_LEN];
    char tipo[MAX_STR_LEN];
} Item;

// PROTÓTIPOS
void inicializarMochila(int *numItens);
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItem(Item mochila[], int numItens);
void menuitem();

// MAIN
int main() {

    menuitem(); // Menu principal com opções:

    return 0;
}

// Funções
// INICIALIZAÇÃO
void inicializarMochila(int *numItens) {
    *numItens = 0; // começa vazia
}

// INSERIR ITEM
void inserirItem(Item mochila[], int *numItens) {

    if (*numItens == TAM_MAX) {
        printf("\n⚠ Mochila cheia! Remova um item antes de inserir outro.\n");
        return;
    }

    printf("Nome: ");
    fgets(mochila[*numItens].nome, MAX_STR_LEN, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = 0;

    printf("Tipo: ");
    fgets(mochila[*numItens].tipo, MAX_STR_LEN, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = 0;

    (*numItens)++;

    printf("Item inserido!\n");
}
// REMOVER ITEM (usuário escolhe)
void removerItem(Item mochila[], int *numItens) {

    if (*numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    int pos;

    listarItem(mochila, *numItens);

    printf("Digite o numero do item para remover: ");
    scanf("%d", &pos);
    getchar();

    if (pos < 1 || pos > *numItens) {
        printf("Posicao invalida!\n");
        return;
    }

    // ajusta índice (usuário começa em 1)
    pos--;

    // desloca os elementos
    for (int i = pos; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*numItens)--;

    printf("Item removido!\n");
}

// LISTAR
void listarItem(Item mochila[], int numItens) {

    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");

    for (int i = 0; i < numItens; i++) {
        printf("%d - %s (%s)\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo);
    }
}

// MENU
void menuitem() {

    Item mochila[TAM_MAX]; // Vetor mochila:
    int numItens;

    inicializarMochila(&numItens);

    int opcao;

    do {
        printf("\n@@@@ MOCHILA TATICA @@@@\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

            case 1:
                inserirItem(mochila, &numItens);// 1. Adicionar um item
                break;

            case 2:
                removerItem(mochila, &numItens); // 2. Remover um item
                break;

            case 3:
                listarItem(mochila, numItens);  // 3. Listar todos os itens
                break;
        }

    } while (opcao != 0);    // 0. Sair
}
