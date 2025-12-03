//deixo aqui registrado meu desprezo a este exercicio, uma vez que entendi ele se torna notavelmente facíl, até la.... jesus

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 505
#define INF 100000000 // Um valor grande para representar infinito

// Matriz de adjacência para guardar os pesos das arestas
int adj[MAXN][MAXN];
int dist[MAXN];
bool visited[MAXN];
int N, E;

// Função Dijkstra para encontrar o menor caminho de src até dest
int dijkstra(int src, int dest) {
    // Inicialização
    for (int i = 0; i <= N; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    
    dist[src] = 0;

    for (int i = 0; i < N; i++) {
        int u = -1;
        int minVal = INF;

        // Encontrar o vértice não visitado com a menor distância atual
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < minVal) {
                minVal = dist[j];
                u = j;
            }
        }

        // Se não alcançamos nenhum novo vértice ou o destino é inalcançável
        if (u == -1 || dist[u] == INF) break;

        visited[u] = true;
        
        // Se chegamos ao destino, podemos parar (opcional, mas otimiza)
        if (u == dest) return dist[u];

        // Relaxamento das arestas
        for (int v = 1; v <= N; v++) {
            if (adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    return dist[dest];
}

int main() {
    // Leitura até que N e E sejam 0
    while (scanf("%d %d", &N, &E) && (N != 0 || E != 0)) {
        
        // Limpar / Inicializar o grafo com INF
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                adj[i][j] = INF;
            }
        }

        // Ler as arestas
        for (int i = 0; i < E; i++) {
            int x, y, h;
            scanf("%d %d %d", &x, &y, &h);
            // Se houver múltiplas arestas, pega a menor (boa prática), 
            // embora o problema não especifique duplicatas.
            if (adj[x][y] > h) {
                adj[x][y] = h;
            }
        }

        // Aplicar a regra do "Mesmo País"
        // Se existe ida (x->y) E volta (y->x), o custo vira 0 instantaneamente.
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (adj[i][j] != INF && adj[j][i] != INF) {
                    adj[i][j] = 0;
                    adj[j][i] = 0;
                }
            }
        }

        //Processar as consultas
        int K;
        scanf("%d", &K);
        
        while (K--) {
            int O, D;
            scanf("%d %d", &O, &D);
            
            int ans = dijkstra(O, D);
            
            if (ans == INF) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", ans);
            }
        }
        
        printf("\n");
    }

    return 0;
}