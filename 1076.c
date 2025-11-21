#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_V 100

int main() {
    int T; // Número de casos de teste
    
    // Lê o número de casos de teste
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int N; // Ponto de início
        scanf("%d", &N);

        int V, A; // V = Vértices, A = Arestas (linhas no input)
        scanf("%d %d", &V, &A);

        // Matriz de adjacência para rastrear quais arestas ja foram

        bool arestas[MAX_V][MAX_V];
        
        // Limpa a matriz para o caso atual (preenche com false/0)
        memset(arestas, 0, sizeof(arestas));

        int arestas_unicas = 0;

        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);

            // Verifica se essa aresta (ou sua inversa) já foi contabilizada
            if (!arestas[u][v] && !arestas[v][u]) {
                // Marca como vista nas duas direções
                arestas[u][v] = true;
                arestas[v][u] = true;
                arestas_unicas++;
            }
        }


        printf("%d\n", arestas_unicas * 2);
    }

    return 0;
}