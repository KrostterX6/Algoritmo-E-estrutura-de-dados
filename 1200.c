#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char info;
    struct Node *left;
    struct Node *right;
} Node;


// Aloca e cria um nó novinho em folha
Node* createNode(char val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->info = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Limpa a memória da árvore (usa pós-ordem pra limpar de baixo pra cima)
void free_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Insere um char na árvore (recursivo)
Node* insert(Node* root, char val) {
    // Caso base: se a árvore/galho tá vazia, cria o nó aqui
    if (root == NULL) {
        return createNode(val);
    }

    // Caso recursivo: decide se vai para a esquerda ou direita
    if (val < root->info) {
        root->left = insert(root->left, val);
    } else if (val > root->info) {
        // O problema garante que não tem repetido
        root->right = insert(root->right, val);
    }
    
    return root;
}

// Procura um char na árvore
int search(Node* root, char val) {
    // Caso base 1: Bateu num galho seco (NULL), não achou
    if (root == NULL) {
        return 0;
    }
    // Caso base 2: Achou
    if (root->info == val) {
        return 1;
    }
    
    // Caso recursivo: continua procurando no lado certo
    if (val < root->info) {
        return search(root->left, val);
    } else {
        return search(root->right, val);
    }
}

void print_inorder(Node* root, int* isFirst) {
    if (root == NULL) {
        return;
    }
    print_inorder(root->left, isFirst);
    
    if (*isFirst) {
        printf("%c", root->info);
        *isFirst = 0; // Os próximos não serão o primeiro
    } else {
        printf(" %c", root->info);
    }
    
    print_inorder(root->right, isFirst);
}

// Imprime PREFIXA (raiz, esquerda, direita)
void print_prefix(Node* root, int* isFirst) {
    if (root == NULL) {
        return;
    }
    
    if (*isFirst) {
        printf("%c", root->info);
        *isFirst = 0;
    } else {
        printf(" %c", root->info);
    }

    print_prefix(root->left, isFirst);
    print_prefix(root->right, isFirst);
}

// Imprime POSFIXA (esquerda, direita, raiz)
void print_postfix(Node* root, int* isFirst) {
    if (root == NULL) {
        return;
    }
    print_postfix(root->left, isFirst);
    print_postfix(root->right, isFirst);
    
    if (*isFirst) {
        printf("%c", root->info);
        *isFirst = 0;
    } else {
        printf(" %c", root->info);
    }
}


int main() {
    Node* root = NULL;  // A árvore começa vazia
    char command[20];   // Guarda o comando
    char value;         // Guarda a letra

    // Lê comandos até o final do arquivo (EOF)
    while (scanf("%s", command) != EOF) {
        
        if (strcmp(command, "I") == 0) {
            // "I" -> Inserir
            // O " %c" ignora espaços ou newlines que sobraram
            scanf(" %c", &value);
            root = insert(root, value);
            // Inserção não imprime nada

        } else if (strcmp(command, "P") == 0) {
            // "P" -> Pesquisar
            scanf(" %c", &value);
            if (search(root, value)) {
                printf("%c existe\n", value);
            } else {
                printf("%c nao existe\n", value);
            }

        } else if (strcmp(command, "INFIXA") == 0) {
            int first = 1; // Reseta a flag do truque do espaço
            print_inorder(root, &first);
            printf("\n");

        } else if (strcmp(command, "PREFIXA") == 0) {
            int first = 1; // Reseta a flag
            print_prefix(root, &first);
            printf("\n");

        } else if (strcmp(command, "POSFIXA") == 0) {
            int first = 1; // Reseta a flag
            print_postfix(root, &first);
            printf("\n");
        }
    }

    // Limpa a bagunça
    free_tree(root);

    return 0;
}