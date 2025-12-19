#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Definição da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Ponteiro para a mochila (vetor dinâmico)
struct Item *mochila = NULL;
int totalItens = 0;

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();

// Função principal
int main() {
    int opcao;

    // Alocação inicial da mochila
    mochila = (struct Item *) malloc(MAX_ITENS * sizeof(struct Item));

    if (mochila == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    do {
        printf("\n====== MOCHILA DO JOGADOR ======\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    // Liberação da memória antes de encerrar
    free(mochila);
    mochila = NULL;

    return 0;
}

// Função para inserir item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Limite de %d itens.\n", MAX_ITENS);
        return;
    }

    printf("\n--- Cadastro de Item ---\n");

    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

    printf("Tipo do item: ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    limparBuffer();

    totalItens++;
    printf("Item cadastrado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nNome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Deslocamento dos itens
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            encontrado = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

// Função para listar itens
void listarItens() {
    if (totalItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d\n", i + 1);
        printf(" Nome: %s\n", mochila[i].nome);
        printf(" Tipo: %s\n", mochila[i].tipo);
        printf(" Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Busca sequencial
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nNome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado:\n");
            printf(" Nome: %s\n", mochila[i].nome);
            printf(" Tipo: %s\n", mochila[i].tipo);
            printf(" Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

// Limpa buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}
