#include <stdio.h>
#include <stdlib.h>

// Estrutura para o nó da Árvore Binária de Busca (ABB)
typedef struct Node {
    int height;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

//Função para criar um novo nó
Node* createNode(int h) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Trata falha na alocação de memória
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }
    newNode->height = h;
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na ABB
Node* insert(Node* root, int h) {
    // Se a raiz é NULL, cria um novo nó e o retorna
    if (root == NULL) {
        return createNode(h);
    }

    // Se a altura já existe, incrementa a contagem
    if (h == root->height) {
        root->count++;
    } 
    // Se a altura é menor, insere na subárvore esquerda
    else if (h < root->height) {
        root->left = insert(root->left, h);
    } 
    // Se a altura é maior, insere na subárvore direita
    else {
        root->right = insert(root->right, h);
    }

    return root;
}

// Variável global para controlar a impressão do espaço (apenas para o percurso)
static int first_element = 1;

// Função para percorrer a ABB em ordem e imprimir os elementos
void inorder(Node* root) {
    if (root != NULL) {
        // Visita a subárvore esquerda (menores)
        inorder(root->left);

        // Visita o nó atual: imprime a altura 'count' vezes
        for (int i = 0; i < root->count; i++) {
            if (!first_element) {
                printf(" ");
            }
            printf("%d", root->height);
            first_element = 0;
        }

        // Visita a subárvore direita (maiores)
        inorder(root->right);
    }
}


void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {

    int NC;
    // Lê o número de casos
    if (scanf("%d", &NC) != 1) return 1;

    while (NC--) {
        int N;
        // Lê a quantidade de pessoas.
        if (scanf("%d", &N) != 1) return 1;

        Node* root = NULL; // Inicializa a raiz da ABB

        for (int i = 0; i < N; ++i) {
            int h;
            // Lê a altura.
            if (scanf("%d", &h) != 1) return 1;
            // Insere na Árvore Binária de Busca.
            root = insert(root, h);
        }

        // Prepara para o percurso
        first_element = 1;

        // Percorre a ABB em ordem
        inorder(root);
        
        printf("\n"); // Nova linha após cada caso de teste

        freeTree(root);
    }

    return 0;
}