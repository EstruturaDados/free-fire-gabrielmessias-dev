#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ===== STRUCTS =====
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ===== VARIÁVEIS GLOBAIS =====
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

No *mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ===== PROTÓTIPOS =====
void inserirItemVetor();
void removerItemVetor();
void listarVetor();
int buscarSequencialVetor(char nome[]);
int buscarBinariaVetor(char nome[]);
void ordenarVetor();

void inserirItemLista();
void removerItemLista();
void listarLista();
void buscarSequencialLista(char nome[]);

void menu();
void limparBuffer();

// ===== MAIN =====
int main() {
    menu();
    return 0;
}

// ===== MENU =====
void menu() {
    int opcao, estrutura;
    char nome[30];

    do {
        printf("\nEscolha a estrutura:\n");
        printf("1 - Vetor\n");
        printf("2 - Lista Encadeada\n");
        printf("0 - Sair\n");
        scanf("%d", &estrutura);
        limparBuffer();

        if (estrutura == 0) break;

        printf("\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar\n");
        scanf("%d", &opcao);
        limparBuffer();

        if (estrutura == 1) {
            switch (opcao) {
                case 1: inserirItemVetor(); break;
                case 2: removerItemVetor(); break;
                case 3: listarVetor(); break;
                case 4:
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    comparacoesSequencial = 0;
                    buscarSequencialVetor(nome);
                    printf("Comparacoes (Sequencial): %d\n", comparacoesSequencial);

                    ordenarVetor();
                    comparacoesBinaria = 0;
                    buscarBinariaVetor(nome);
                    printf("Comparacoes (Binaria): %d\n", comparacoesBinaria);
                    break;
            }
        } else {
            switch (opcao) {
                case 1: inserirItemLista(); break;
                case 2: removerItemLista(); break;
                case 3: listarLista(); break;
                case 4:
                    printf("Nome: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    comparacoesSequencial = 0;
                    buscarSequencialLista(nome);
                    printf("Comparacoes (Lista): %d\n", comparacoesSequencial);
                    break;
            }
        }
    } while (1);
}

// ===== VETOR =====
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) return;

    printf("Nome: ");
    fgets(mochilaVetor[totalVetor].nome, 30, stdin);
    mochilaVetor[totalVetor].nome[strcspn(mochilaVetor[totalVetor].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochilaVetor[totalVetor].tipo, 20, stdin);
    mochilaVetor[totalVetor].tipo[strcspn(mochilaVetor[totalVetor].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalVetor].quantidade);
    limparBuffer();

    totalVetor++;
}

void removerItemVetor() {
    char nome[30];
    printf("Nome: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            totalVetor--;
            return;
        }
    }
}

void listarVetor() {
    for (int i = 0; i < totalVetor; i++)
        printf("%s - %s - %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
}

int buscarSequencialVetor(char nome[]) {
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() {
    Item aux;
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - 1 - i; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                aux = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = aux;
            }
        }
    }
}

int buscarBinariaVetor(char nome[]) {
    int ini = 0, fim = totalVetor - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) return meio;
        if (cmp < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ===== LISTA ENCADEADA =====
void inserirItemLista() {
    No *novo = malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    limparBuffer();

    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

void removerItemLista() {
    char nome[30];
    No *atual = mochilaLista, *anterior = NULL;

    printf("Nome: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else mochilaLista = atual->proximo;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void listarLista() {
    No *aux = mochilaLista;
    while (aux) {
        printf("%s - %s - %d\n",
               aux->dados.nome,
               aux->dados.tipo,
               aux->dados.quantidade);
        aux = aux->proximo;
    }
}

void buscarSequencialLista(char nome[]) {
    No *aux = mochilaLista;
    while (aux) {
        comparacoesSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("Encontrado!\n");
            return;
        }
        aux = aux->proximo;
    }
    printf("Nao encontrado.\n");
}

// ===== UTIL =====
void limparBuffer() {
    while (getchar() != '\n');
}
