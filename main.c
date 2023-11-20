#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 40

typedef struct {
    char nome[20];
    float nota;
    char status;
} Aluno;

typedef struct {
    Aluno alunos[MAX_ALUNOS];
    int quantidade;
} ListaChamada;

void inicializarLista(ListaChamada *lista) {
    lista->quantidade = 0;
}

void incluirAluno(ListaChamada *lista, const char *nome, float nota, char status) {
    if (lista->quantidade < MAX_ALUNOS) {
        Aluno aluno;
        strcpy(aluno.nome, nome);
        aluno.nota = nota;
        aluno.status = status;

        lista->alunos[lista->quantidade] = aluno;
        lista->quantidade++;
    } else {
        printf("A lista de chamada está cheia. Impossível incluir mais alunos.\n");
    }
}

void excluirAluno(ListaChamada *lista, const char *nome) {
    int i, j;
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->alunos[i].nome, nome) == 0) {
            // Remove o aluno movendo os elementos à frente para trás
            for (j = i; j < lista->quantidade - 1; j++) {
                lista->alunos[j] = lista->alunos[j + 1];
            }
            lista->quantidade--;
            printf("Aluno %s removido com sucesso.\n", nome);
            return;
        }
    }
    printf("Aluno %s não encontrado na lista.\n", nome);
}

void ordenarPorNotaDecrescente(ListaChamada *lista) {
    int i, j;
    Aluno temp;
    for (i = 0; i < lista->quantidade - 1; i++) {
        for (j = i + 1; j < lista->quantidade; j++) {
            if (lista->alunos[i].nota < lista->alunos[j].nota) {
                // Troca os elementos se estiverem fora de ordem
                temp = lista->alunos[i];
                lista->alunos[i] = lista->alunos[j];
                lista->alunos[j] = temp;
            }
        }
    }
}

void imprimirListaChamada(ListaChamada *lista) {
    printf("Relação total de alunos:\n");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("Nome: %s, Nota: %.2f, Status: %c\n", lista->alunos[i].nome, lista->alunos[i].nota, lista->alunos[i].status);
    }
}

void imprimirAlunosAtivos(ListaChamada *lista) {
    printf("Alunos com matrícula ativa:\n");
    for (int i = 0; i < lista->quantidade; i++) {
        if (lista->alunos[i].status == 'A' || lista->alunos[i].status == 'a') {
            printf("Nome: %s, Nota: %.2f\n", lista->alunos[i].nome, lista->alunos[i].nota);
        }
    }
}

int main() {
    ListaChamada lista;
    inicializarLista(&lista);

    incluirAluno(&lista, "Joao", 8.5, 'A');
    incluirAluno(&lista, "Maria", 7.0, 'A');
    incluirAluno(&lista, "Pedro", 9.2, 'C');

    imprimirListaChamada(&lista);

    ordenarPorNotaDecrescente(&lista);

    printf("\nLista ordenada por nota decrescente:\n");
    imprimirListaChamada(&lista);

    printf("\n");
    imprimirAlunosAtivos(&lista);

    excluirAluno(&lista, "Maria");

    return 0;
}
