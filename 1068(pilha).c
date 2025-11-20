#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1005

// Estrutura da Pilha
typedef struct {
    char dados[MAX];
    int topo;
} Pilha;

// Função para inicializar a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Função para empilhar (Push)
void push(Pilha *p, char valor) {
    if (p->topo < MAX - 1) {
        p->topo++;
        p->dados[p->topo] = valor;
    }
}

// Função para desempilhar (Pop)
void pop(Pilha *p) {
    if (p->topo >= 0) {
        p->topo--;
    }
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return (p->topo == -1);
}

int main() {
    char expressao[MAX];

    // O loop lê strings até o fim do arquivo
    while (scanf("%s", expressao) != EOF) {
        Pilha p;
        inicializaPilha(&p);
        int erro = 0;

        // Percorre cada caractere da expressão
        for (int i = 0; expressao[i] != '\0'; i++) {
            
            // Se achou '(', empilha
            if (expressao[i] == '(') {
                push(&p, '(');
            }
            // Se achou ')', tenta desempilhar
            else if (expressao[i] == ')') {
                if (estaVazia(&p)) {
                    // Se a pilha está vazia e chegou um ')', está errado
                    erro = 1;
                    break;
                } else {
                    // Remove o parêntese '(' correspondente do topo
                    pop(&p);
                }
            }
        }

        if (!erro && estaVazia(&p)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}