#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Aloca e cria um novo nó
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insere um nó na BST (recursivo)
struct Node* insert(struct Node* node, int data) {
    // Caso base: nó nulo, encontramos o local da inserção
    if (node == NULL) {
        return createNode(data);
    }
    
    // Navega para a sub-árvore correta
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    
    // Retorna o ponteiro do nó
    return node;
}

//Funções de Percurso

// Percurso Pré-ordem: Raiz, Esquerda, Direita
void printPreorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf(" %d", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

// Percurso Em-ordem: Esquerda, Raiz, Direita
void printInorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf(" %d", node->data);
    printInorder(node->right);
}

// Percurso Pós-ordem: Esquerda, Direita, Raiz
void printPostorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printPostorder(node->left);
    printPostorder(node->right);
    printf(" %d", node->data);
}

// Libera a memória da árvore (percurso pós-ordem)
void freeTree(struct Node* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    int C, N, i, j, value;
    
    // Número de casos de teste
    scanf("%d", &C);
    
    for (i = 1; i <= C; i++) {
        struct Node* root = NULL; // Raiz de cada árvore
        
        // Número de nós da árvore
        scanf("%d", &N);
        
        // Insere os N nós
        for (j = 0; j < N; j++) {
            scanf("%d", &value);
            root = insert(root, value);
        }
        
        // Imprime a saída
        printf("Case %d:\n", i);
        
        printf("Pre.:");
        printPreorder(root);
        printf("\n");
        
        printf("In.:");
        printInorder(root);
        printf("\n");
        
        printf("Post.:");
        printPostorder(root);
        // Duas novas linhas: uma para esta linha, outra em branco
        printf("\n\n"); 
        
        // Libera a memória da árvore atual
        freeTree(root);
    }
    
    return 0;
}

//Que Lamport abençoe este código e ele funcione, Amém