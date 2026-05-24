#include <stdio.h>     // Entrada e saída
#include <stdlib.h>    // Funções gerais
#include <string.h>    // Manipulação de strings
#include <time.h>      // Medição de tempo

// ================= DEFINES =================

#define MAX_NOME 30
#define MAX_TIPO 20
#define TAM_MAX 20

// ================= STRUCT =================

// Struct que representa o Item
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Item;

// PROTÓTIPOS 
void inicializarMochila(int *numItens);
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItem(Item mochila[], int numItens);
void buscaSequencialIterativa(Item mochila[], int numItens, char nomeBusca[]);
void menuitem();

// ORDENAÇÃO
int buscaBinaria(Item mochila[],int numItens, char nomeBusca[]);
void organizarItens(Item mochila[],int numItens);
void bubbleSortNome(Item mochila[], int tamanho, int *comparacoes);
void insertionSortTipo(Item mochila[],int tamanho,int *comparacoes);
void selectionSortPrioridade(Item mochila[],int tamanho, int *comparacoes);

//FUNÇÃO AUXILIA
void troca_obj(Item *a, Item *b);

//  MAIN 
int main() {
    menuitem();
    return 0;
}

// INICIALIZAR
void inicializarMochila(int *numItens) {
    *numItens = 0;
}
// INSERIR 
void inserirItem(Item mochila[], int *numItens) {

    if (*numItens == TAM_MAX) {
        printf("\n⚠ Limite maximo atingido!\n");
        return;
    }
    printf("\n NOME:" );
    fgets(mochila[*numItens].nome,
          MAX_NOME,
          stdin);
    mochila[*numItens].nome[
        strcspn(mochila[*numItens].nome, "\n")
    ] = 0;

    printf("TIPO: ");
    fgets(mochila[*numItens].tipo,
          MAX_TIPO,
          stdin);
    mochila[*numItens].tipo[
        strcspn(mochila[*numItens].tipo, "\n")
    ] = 0;

    do {
        printf("PRIORIDADE: ");
        scanf("%d",
              &mochila[*numItens].prioridade);
        getchar();

        if (mochila[*numItens].prioridade < 1 ||
            mochila[*numItens].prioridade > 10) {
            printf("⚠ Prioridade invalida!\n");
        }

    } while (mochila[*numItens].prioridade < 1 ||
             mochila[*numItens].prioridade > 10);

    (*numItens)++;

    printf("\n ITEM cadastrado!\n");
}
// REMOVER =================
void removerItem(Item mochila[], int *numItens) {

    if (*numItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    int pos;
    listarItem(mochila, *numItens);
    printf("\nDigite o ID do ITEM para remover: ");
    scanf("%d", &pos);
    getchar();

    if (pos < 1 || pos > *numItens) {
        printf("\n⚠ Posicao invalida!\n");
        return;
    }
    pos--;
    for (int i = pos; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*numItens)--;

    printf("\n ITEM removido!\n");}

//  LISTAR
void listarItem(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n+------+---------------------------+----------------------+------------+\n");
    printf("| %-4s | %-25s | %-20s | %-10s |\n",
           "ID",
           "NOME",
           "TIPO",
           "PRIOR.");
    printf("+------+---------------------------+----------------------+------------+\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-4d | %-25s | %-20s | %-10d |\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].prioridade);
    }
    printf("+------+---------------------------+----------------------+------------+\n");
}
// BUSCA SEQUENCIAL 
void buscaSequencialIterativa(Item mochila[], int numItens, char nomeBusca[]) {
    int achou = 0;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome,
                   nomeBusca) == 0) {

            printf("\n===== ITEM ENCONTRADO =====\n");
            printf("Nome: %s\n",
                   mochila[i].nome);
            printf("Tipo: %s\n",
                   mochila[i].tipo);
            printf("Prioridade: %d\n",
                   mochila[i].prioridade);
            achou = 1;
            break;
        }
    }
    if (!achou) {

        printf("\n ITEM nao encontrado.\n");
    }
}

// BUSCA BINÁRIA 

int buscaBinaria(Item mochila[], int numItens,  char nomeBusca[]) {
    int inicio = 0;
    int fim = numItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int resultado =
        strcmp(mochila[meio].nome,
               nomeBusca);
        if (resultado == 0) {
            return meio;
        }

        else if (resultado < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    return -1;
}

// MENU PRINCIPAL
void menuitem() {
    Item mochila[TAM_MAX];
    int numItens;
    int opcao;
    char nomeBusca[MAX_NOME];
    inicializarMochila(&numItens);

    do {
        printf("\n=========== MOCHILA TATICA ===========\n");

        printf("1 - Inserir \n");
        printf("2 - Remover \n");
        printf("3 - Listar \n");
        printf("4 - Buscar \n");
        printf("5 - Organizar \n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;

            case 2:
                removerItem(mochila, &numItens);
                break;

            case 3:
                listarItem(mochila, numItens);
                break;

            case 4:
                printf("\nDigite o nome do ITEM: ");
                fgets(nomeBusca,
                      MAX_NOME,
                      stdin);
                nomeBusca[ strcspn(nomeBusca, "\n")  ] = 0;

                buscaSequencialIterativa(
                    mochila,
                    numItens,
                    nomeBusca
                );
                break;
            case 5:
                organizarItens(mochila, numItens);
                break;

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\n⚠ Opcao invalida!\n");
        }

    } while (opcao != 0);
}

//  MENU ORDENAÇÃO

void organizarItens(Item mochila[], int numItens) {
    int opcao;
    int comparacoes = 0;
    clock_t inicio, fim;
    double tempo;

    do {

        printf("\n======= ORGANIZAR  =======\n");

        printf("1 - POR NOME\n");
        printf("2 - POR TIPO\n");
        printf("3 - POR PRIORIDADE\n");
        printf("4 - BUSCA POR NOME\n");
        printf("0 - VOLTARr\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(
                    mochila,
                    numItens,
                    &comparacoes
                );
                fim = clock();
                tempo =
                (double)(fim - inicio)
                / CLOCKS_PER_SEC;
                printf("\n Ordenado por NOME!\n");
                printf("Comparacoes: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);
                listarItem(mochila, numItens);
                break;

            case 2:
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(
                    mochila,
                    numItens,
                    &comparacoes
                );
                fim = clock();
                tempo =
                (double)(fim - inicio)
                / CLOCKS_PER_SEC;
                printf("\n✅ Ordenado por TIPO!\n");
                printf("Comparacoes: %d\n", comparacoes);
                printf("Tempo: %.6f segundos\n",tempo);
                listarItem(mochila, numItens);
                break;

            case 3:
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(
                    mochila,
                    numItens,
                    &comparacoes
                );
                fim = clock();
                tempo =
                (double)(fim - inicio)
                / CLOCKS_PER_SEC;

                printf("\n Ordenado por PRIORIDADE!\n");
                printf("Comparacoes: %d\n",comparacoes);
                printf("Tempo: %.6f segundos\n",tempo);
                listarItem(mochila, numItens);
                break;

            case 4: {
                char busca[MAX_NOME];
                bubbleSortNome(
                    mochila,
                    numItens,
                    &comparacoes
                );
                printf("\nDigite o ITEM-chave: ");

                fgets(busca,
                      MAX_NOME, stdin);
                busca[ strcspn(busca, "\n") ] = 0;

                int posicao =
                buscaBinaria(
                    mochila,
                    numItens,
                    busca
                );

                if (posicao != -1) {

                    printf("\nITEM ENCONTRADO!\n");
                    printf("Nome: %s\n", mochila[posicao].nome);

                    printf("Tipo: %s\n",mochila[posicao].tipo);

                    printf("Prioridade: %d\n", mochila[posicao].prioridade);
                }

                else {
                    printf("\nITEN NÃO encontrado.\n");
                }
                break;
            }

            case 0:
                printf("\nVoltando...\n");
                break;

            default:
                printf("\n Opcao invalida!\n");
        }

    } while(opcao != 0);
}

// TROCA 

void troca_obj(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

// BUBBLE SORT
void bubbleSortNome(Item mochila[],int tamanho, int *comparacoes) {

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(mochila[j].nome,
                       mochila[j + 1].nome) > 0) { troca_obj(&mochila[j], &mochila[j + 1]
                );
            }
        }
    }
}

//  INSERTION SORT 

void insertionSortTipo(Item mochila[],int tamanho, int *comparacoes) {
    for (int i = 1; i < tamanho; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            }

            else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

// SELECTION SORT 

void selectionSortPrioridade(Item mochila[], int tamanho, int *comparacoes) {

    for (int i = 0; i < tamanho - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tamanho; j++) { (*comparacoes)++;

            if (mochila[j].prioridade <
                mochila[menor].prioridade) {
                menor = j;
            }
        }

        troca_obj(
            &mochila[i],
            &mochila[menor]
        );
    }
}