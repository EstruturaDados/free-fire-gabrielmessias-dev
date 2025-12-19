#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ===== STRUCT =====
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===== PROTÓTIPOS =====
void cadastrarComponentes(Componente[], int *);
void mostrarComponentes(Componente[], int);

void bubbleSortNome(Componente[], int, long *);
void insertionSortTipo(Componente[], int, long *);
void selectionSortPrioridade(Componente[], int, long *);

int buscaBinariaPorNome(Componente[], int, char[], long *);

void limparBuffer();

// ===== MAIN =====
int main() {
    Componente torre[MAX];
    int total = 0;
    int opcao;
    char chave[30];
    long comparacoes = 0;
    clock_t inicio, fim;

    cadastrarComponentes(torre, &total);

    do {
        printf("\n=== TORRE DE FUGA - SAFE ZONE FINAL ===\n");
        printf("1 - Ordenar por NOME (Bubble Sort)\n");
        printf("2 - Ordenar por TIPO (Insertion Sort)\n");
        printf("3 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        comparacoes = 0;
        inicio = clock();

        switch (opcao) {
            case 1:
                bubbleSortNome(torre, total, &comparacoes);
                break;
            case 2:
                insertionSortTipo(torre, total, &comparacoes);
                break;
            case 3:
                selectionSortPrioridade(torre, total, &comparacoes);
                break;
            case 0:
                printf("Encerrando simulacao...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                continue;
        }

        fim = clock();

        if (opcao != 0) {
            mostrarComponentes(torre, total);
            printf("\nComparacoes: %ld", comparacoes);
            printf("\nTempo: %.6f segundos\n",
                   (double)(fim - inicio) / CLOCKS_PER_SEC);

            if (opcao == 1) {
                printf("\nDigite o componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';

                comparacoes = 0;
                int pos = buscaBinariaPorNome(torre, total, chave, &comparacoes);

                if (pos != -1)
                    printf("Componente-chave ENCONTRADO! Torre ativada.\n");
                else
                    printf("Componente-chave NAO encontrado.\n");

                printf("Comparacoes na busca binaria: %ld\n", comparacoes);
            }
        }

    } while (opcao != 0);

    return 0;
}

// ===== FUNÇÕES =====

void cadastrarComponentes(Componente v[], int *n) {
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX);
    scanf("%d", n);
    limparBuffer();

    for (int i = 0; i < *n; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d", &v[i].prioridade);
        limparBuffer();
    }
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES DA TORRE ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ===== ORDENAÇÕES =====

void bubbleSortNome(Componente v[], int n, long *comp) {
    Componente aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            (*comp)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void insertionSortTipo(Componente v[], int n, long *comp) {
    Componente chave;
    int j;

    for (int i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && (++(*comp), strcmp(v[j].tipo, chave.tipo) > 0)) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSortPrioridade(Componente v[], int n, long *comp) {
    int menor;
    Componente aux;

    for (int i = 0; i < n - 1; i++) {
        menor = i;
        for (int j = i + 1; j < n; j++) {
            (*comp)++;
            if (v[j].prioridade < v[menor].prioridade)
                menor = j;
        }
        aux = v[i];
        v[i] = v[menor];
        v[menor] = aux;
    }
}

// ===== BUSCA BINÁRIA =====

int buscaBinariaPorNome(Componente v[], int n, char chave[], long *comp) {
    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comp)++;

        int r = strcmp(v[meio].nome, chave);
        if (r == 0) return meio;
        if (r < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ===== UTIL =====
void limparBuffer() {
    while (getchar() != '\n');
}
