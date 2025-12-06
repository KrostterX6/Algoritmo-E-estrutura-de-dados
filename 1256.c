#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

void inserir(Node **cabeca, int v) {
    Node *novoNo = (Node *)malloc(sizeof(Node));
    novoNo->valor = v;
    novoNo->prox = NULL;

    if (*cabeca == NULL) {
        *cabeca = novoNo;
    } else {
        Node *temp = *cabeca;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
    }
}

void liberarLista(Node *cabeca) {
    Node *atual = cabeca;
    while (atual != NULL) {
        Node *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

int main() {
    int N; // Quantidade de casos de teste
    scanf("%d", &N);

    // Loop pelos casos de teste
    for (int i = 0; i < N; i++) {
        int M, C;
        scanf("%d %d", &M, &C); // M = tamanho da tabela, C = qtd de chaves

        // Cria a tabela hash (array de ponteiros para Nodes)
        // M <= 100 de acordo com o problema, então 101 é seguro
        Node *tabela[101]; 

        for (int j = 0; j < M; j++) {
            tabela[j] = NULL;
        }

        for (int j = 0; j < C; j++) {
            int chave;
            scanf("%d", &chave);
            
            // Função de dispersão h(x) = x mod M
            int indice = chave % M;
            
            // Insere na lista correspondente ao índice
            inserir(&tabela[indice], chave);
        }

        // Regra de formatação: Linha em branco separando conjuntos de saída
        // Se não for o primeiro caso de teste, imprime uma linha em branco antes
        if (i > 0) {
            printf("\n");
        }

        // Impressão da Tabela Hash
        for (int j = 0; j < M; j++) {
            printf("%d -> ", j);
            
            Node *temp = tabela[j];
            while (temp != NULL) {
                printf("%d -> ", temp->valor);
                temp = temp->prox;
            }
            // O caractere '\' precisa ser escapado como '\\'
            printf("\\\n");
        }

        // Limpeza de memória para o próximo caso de teste
        for (int j = 0; j < M; j++) {
            liberarLista(tabela[j]);
        }
    }

    return 0;
}