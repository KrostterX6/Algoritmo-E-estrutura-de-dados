#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 255
#define INF 100000000 //valor grande para representar infinito

// Variáveis globais para o grafo e Dijkstra
int adj[MAXN][MAXN]; // Matriz de adjacência
int dist[MAXN];      // Array
int visited[MAXN];   // Array
int N, M, C, K;

void solve() {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        visited[i] = 0;
        for (int j = 0; j < N; j++) {
            adj[i][j] = INF;
        }
    }

    // Leitura das estradas
    for (int i = 0; i < M; i++) {
        int u, v, p;
        scanf("%d %d %d", &u, &v, &p);
        
        // Como o grafo é não-direcionado inicialmente, salvamos nos dois sentidos
        // Se houver múltiplas estradas pegamos a menor
        if (p < adj[u][v]) {
            adj[u][v] = p;
            adj[v][u] = p;
        }
    }

    // Algoritmo de Dijkstra
    dist[K] = 0; // A distância para a origem é 0

    for (int i = 0; i < N; i++) {
        int u = -1;
        int minVal = INF;

        // Encontrar o nó não visitado com a menor distância
        for (int j = 0; j < N; j++) {
            if (!visited[j] && dist[j] < minVal) {
                minVal = dist[j];
                u = j;
            }
        }

        // Se não houver mais nós alcançáveis ou chegarmos ao destino
        if (u == -1 || dist[u] == INF) break;
        
        visited[u] = 1;

        if (u == C - 1) break;

        // Relaxar vizinhos com base nas restrições
        if (u < C - 1) {
            // só podemos ir para a próxima cidade da sequência (u -> u+1).
            int v = u + 1;
            if (adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        } else {
            //se estamos fora da rota, podemos ir para qualquer vizinho.
            for (int v = 0; v < N; v++) {
                if (adj[u][v] != INF) {
                    if (dist[u] + adj[u][v] < dist[v]) {
                        dist[v] = dist[u] + adj[u][v];
                    }
                }
            }
        }
    }

    printf("%d\n", dist[C-1]);
}

int main() {
    // Loop de leitura até encontrar "0 0 0 0"
    while (scanf("%d %d %d %d", &N, &M, &C, &K) && (N || M || C || K)) {
        solve();
    }
    return 0;
}
