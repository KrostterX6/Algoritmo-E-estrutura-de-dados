#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_C 10005
#define MAX_V 50005
#define INF INT_MAX

// Estrutura para representar o Estado na fila de prioridade
typedef struct {
    int custo;
    int u;      // cidade atual
    int par;    // 0 para par, 1 para ímpar
} State;

// Estruturas para o Grafo
typedef struct {
    int v;
    int peso;
    int next;
} Aresta;

Aresta arestas[MAX_V * 2];
int head[MAX_C];
int total_arestas = 0;

// Matriz de distâncias: dist[cidade][paridade]
int dist[MAX_C][2];

// Min-Heap (Fila de Prioridade)
State heap[MAX_V * 4]; // Tamanho seguro
int heap_size = 0;

// Função para adicionar aresta no grafo
void add_edge(int u, int v, int p) {
    arestas[total_arestas].v = v;
    arestas[total_arestas].peso = p;
    arestas[total_arestas].next = head[u];
    head[u] = total_arestas++;
}

// Funções da Heap
void swap(State *a, State *b) {
    State temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(int custo, int u, int par) {
    heap[heap_size].custo = custo;
    heap[heap_size].u = u;
    heap[heap_size].par = par;
    
    int i = heap_size;
    heap_size++;
    
    // Bubble up
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].custo <= heap[i].custo) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

State heap_pop() {
    State ret = heap[0];
    heap_size--;
    heap[0] = heap[heap_size];
    
    // Bubble down
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = left;
        
        if (right < heap_size && heap[right].custo < heap[left].custo) {
            smallest = right;
        }
        
        if (heap[i].custo <= heap[smallest].custo) break;
        
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
    
    return ret;
}

int main() {
    int C, V;
    
    // Leitura rápida
    if (scanf("%d %d", &C, &V) != 2) return 0;
    
    // Inicializar grafo
    for (int i = 0; i <= C; i++) head[i] = -1;
    
    for (int i = 0; i < V; i++) {
        int u, v, g;
        scanf("%d %d %d", &u, &v, &g);
        add_edge(u, v, g);
        add_edge(v, u, g); // Bidirecional
    }
    
    // Inicializar Dijkstra
    for (int i = 1; i <= C; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    
    // Ponto de partida: Cidade 1, custo 0, paridade 0
    dist[1][0] = 0;
    heap_push(0, 1, 0);
    
    while (heap_size > 0) {
        State atual = heap_pop();
        int d = atual.custo;
        int u = atual.u;
        int par = atual.par;
        
        // Se já achamos um caminho melhor para este estado, ignora
        if (d > dist[u][par]) continue;
        
        // Itera
        for (int i = head[u]; i != -1; i = arestas[i].next) {
            int v = arestas[i].v;
            int peso = arestas[i].peso;
            
            int novo_par = 1 - par; // Inverte paridade (0->1, 1->0)
            int novo_custo = d + peso;
            
            if (novo_custo < dist[v][novo_par]) {
                dist[v][novo_par] = novo_custo;
                heap_push(novo_custo, v, novo_par);
            }
        }
    }
    
    // O resultado é o custo para chegar na cidade C com paridade 0 (PAR)
    if (dist[C][0] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[C][0]);
    }
    
    return 0;
}