#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10001 // N documentos, de 1 a N. uso índice de 1 a N
#define MAX_EDGES 30001

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Array de listas de adjacências
Node* adj[MAX_NODES];

// Array para armazenar o estado de visitação de cada nó
//0: Nao visitado
//1: Em processamento (na pilha de recursão atual)
//2: Processado (completo)
int visited[MAX_NODES];

// Variável global para armazenar se um ciclo foi encontrado
bool has_cycle;

// Função auxiliar para liberar a memória alocada para as listas de adjacências
void free_graph(int N) {
    for (int i = 1; i <= N; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        adj[i] = NULL; // Garante que o ponteiro é NULL para o próximo caso de teste
    }
}

// Função para adicionar uma aresta (dependência)
// A depende de B, então a aresta é de A -> B.
void add_edge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }
    newNode->dest = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// Função DFS para detecção de ciclos
// u: nó atual
void dfs(int u) {
    // Se um ciclo já foi encontrado, podemos parar a busca
    if (has_cycle) return;

    // Marca o nó como "Em processamento"
    visited[u] = 1;

    // Percorre todos os nós que 'u' depende
    Node* current = adj[u];
    while (current != NULL) {
        int v = current->dest;

        //Caso 1: Ciclo encontrado
        // Se o vizinho 'v' está "Em processamento", é um nó que 'u' depende
        // e que já está no caminho da recursão atual. Isso forma um ciclo
        if (visited[v] == 1) {
            has_cycle = true;
            return;
        }

        // Caso 2: Se 'v' não foi visitado, continua a DFS
        if (visited[v] == 0) {
            dfs(v);
            //Verifica novamente após a chamada recursiva, pois a recursão pode ter encontrado um ciclo
            if (has_cycle) return; 
        }

        // Caso 3: Se 'v' está "Processado", ele e seu subgrafo já foram explorados
        // Não é preciso visitá-lo novamente.

        current = current->next;
    }

    // Marca o nó como "Processado" (completo)
    // Isso é importante para evitar reprocessar subgrafos sem ciclos.
    visited[u] = 2;
}

void solve() {
    int N, M; // N: número de documentos, M: número de dependências
    
    // Leitura dos valores de N e M
    if (scanf("%d %d", &N, &M) != 2) return;

    // 1. Inicializa o estado de visitação
    for (int i = 1; i <= N; i++) {
        visited[i] = 0;
        adj[i] = NULL; // Inicializa a lista de adjacências
    }

    //leitura e construção do grafo
    for (int i = 0; i < M; i++) {
        int A, B; // A depende de B
        if (scanf("%d %d", &A, &B) != 2) {
             // Tenta garantir que a memória seja liberada mesmo em caso de erro de leitura
             free_graph(N); 
             return;
        }
        add_edge(A, B);
    }

    //Detecção de ciclos
    has_cycle = false;
    for (int i = 1; i <= N; i++) {
        //Inicia a DFS apenas para nós não visitados (componentes desconexas)
        if (visited[i] == 0) {
            dfs(i);
        }
        //Se um ciclo for encontrado, podemos sair do loop principal
        if (has_cycle) {
            break; 
        }
    }

    //Saída
    if (has_cycle) {
        printf("SIM\n");
    } else {
        printf("NAO\n");
    }

    //Limpeza de memória para o próximo caso de teste
    free_graph(N);
}

int main() {
    int T; //Número de casos de teste
    
    //Leitura do número de casos de teste
    if (scanf("%d", &T) != 1) return 0;
    
    //Processa cada caso de teste
    while (T--) {
        solve();
    }

    return 0;
}