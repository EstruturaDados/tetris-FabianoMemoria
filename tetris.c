#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char tipo; // Tipo da peça (ex: ‘I’, ‘O’, ‘T’, ‘L’)
    int id;    // Identificador único da peça
} Peca;

typedef struct No {
    Peca peca;
    struct No* proximo;
} No;

typedef struct {
    No* frente;
    No* tras;
} FilaPecas;

void inicializarFila(FilaPecas* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

int estaVazia(FilaPecas* fila) {
    return fila->frente == NULL;
}

void adicionarPeca(FilaPecas* fila, char tipo, int id) {
    No* novo = (No*) malloc(sizeof(No));
    novo->peca.tipo = tipo;
    novo->peca.id = id;
    novo->proximo = NULL;
    if (estaVazia(fila)) {
        fila->frente = novo;
        fila->tras = novo;
    } else {
        fila->tras->proximo = novo;
        fila->tras = novo;
    }
}

void jogarPeca(FilaPecas* fila) {
    if (estaVazia(fila)) {
        printf("A fila esta vazia. Nao ha pecas para jogar.\n");
        return;
    }
    No* temp = fila->frente;
    printf("Jogando peca tipo %c com ID %d\n", temp->peca.tipo, temp->peca.id);
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    free(temp);
}

void mostrarFila(FilaPecas* fila) {
    if (estaVazia(fila)) {
        printf("A fila esta vazia.\n");
        return;
    }
    No* atual = fila->frente;
    printf("Fila de pecas futuras:\n");
    while (atual != NULL) {
        printf("Peca tipo %c - ID %d\n", atual->peca.tipo, atual->peca.id);
        atual = atual->proximo;
    }
}

int main() {
    FilaPecas fila;
    inicializarFila(&fila);
    int opcao;
    char tipo;
    int id;

    do {
        printf("\nMenu:\n");
        printf("1 - Visualizar fila\n");
        printf("2 - Jogar peca (remover da frente)\n");
        printf("3 - Adicionar nova peca\n");
        printf("0 - Sair\n");
        printf("Escolha a opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do teclado

        switch (opcao) {
            case 1:
                mostrarFila(&fila);
                break;
            case 2:
                jogarPeca(&fila);
                break;
            case 3:
                printf("Digite o tipo da peca (I, O, T, L): ");
                scanf("%c", &tipo);
                printf("Digite o ID da peca: ");
                scanf("%d", &id);
                adicionarPeca(&fila, tipo, id);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    // Liberar memória restante na fila
    while (!estaVazia(&fila)) {
        jogarPeca(&fila);
    }

    return 0;
}
