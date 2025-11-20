#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MUDANÇA 1 Estrutura
// Em vez de um vetor fixo, temos um 'No' que aponta para o próximo
typedef struct No {
    char dado;
    struct No *proximo;
} No;

// A Pilha agora guarda apenas o endereço do elemento do topo
typedef struct {
    No *topo;
} Pilha;


void inicializaPilha(Pilha *p) {
    p->topo = NULL; 
}

int estaVazia(Pilha *p) {
    return (p->topo == NULL);
}

void push(Pilha *p, char valor) {
    // Alocação dinâmica de memória
    No *novoNo = (No*) malloc(sizeof(No));
    
    if (novoNo != NULL) {
        novoNo->dado = valor;
        novoNo->proximo = p->topo; // O novo aponta para o antigo topo
        p->topo = novoNo;          // O topo vira o novo nó
    }
}

void pop(Pilha *p) {
    if (!estaVazia(p)) {
        No *temp = p->topo;        // Salva o nó atual para não perder a referência
        p->topo = p->topo->proximo; // O topo desce para o próximo da lista
        free(temp);                // Libera a memória do nó removido
    }
}

//Função extra necessária para listas (para não vazar memória)
void limparPilha(Pilha *p) {
    while (!estaVazia(p)) {
        pop(p);
    }
}

int main() {
    char expressao[1005];

    while (scanf("%s", expressao) != EOF) {
        Pilha p;
        inicializaPilha(&p);
        int erro = 0;

       
        for (int i = 0; expressao[i] != '\0'; i++) {
            
            if (expressao[i] == '(') {
                push(&p, '(');
            }
            else if (expressao[i] == ')') {
                // A verificação lógica
                if (estaVazia(&p)) {
                    erro = 1;
                    break;
                } else {
                    pop(&p);
                }
            }
        }

        // Saída
        if (!erro && estaVazia(&p)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }

        // MUDANÇA 2 Limpeza
        limparPilha(&p);
    }

    return 0;
}