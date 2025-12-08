#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

// Função para criar um novo nó
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um valor na Árvore Binária de Busca
Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    
    return root;
}

//limpeza
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Função para realizar o percurso por nível
void bfs(Node* root) {
    if (root == NULL) return;

    // Como N <= 500
    Node* queue[505];
    int front = 0;
    int rear = 0;

    // Enfileira a raiz
    queue[rear++] = root;

    int first = 1; // Flag para controlar os espaços

    while (front < rear) {
        // Desenfileira
        Node* current = queue[front++];

        // Imprime com formatação correta
        if (!first) {
            printf(" ");
        }
        printf("%d", current->val);
        first = 0;

        // Enfileira filhos se existirem
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}

int main() {
    int C, N, val;
    
    // Lê o número de casos de teste
    scanf("%d", &C);
    
    for (int i = 1; i <= C; i++) {
        scanf("%d", &N);
        
        Node* root = NULL;
        
        // Lê os valores e constrói a árvore
        for (int j = 0; j < N; j++) {
            scanf("%d", &val);
            root = insert(root, val);
        }
        
        // Saída formatada
        printf("Case %d:\n", i);
        bfs(root);
        printf("\n"); // Linha em branco obrigatória após cada caso
        
        // Limpa a memória para o próximo caso
        freeTree(root);
    }
    
    return 0;
}