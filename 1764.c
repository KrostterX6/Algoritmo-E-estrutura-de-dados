#include <stdio.h>
#include <stdlib.h>

#define MAX_M 40005 // Máximo de cidades
#define MAX_N 50005 // Máximo de caminhos

//rota
typedef struct {
    int u; // Cidade de origem
    int v; // Cidade de destino
    int w; // Peso (distância)
} Aresta;

//para não estourar a pilha
Aresta arestas[MAX_N];
int pai[MAX_M];

// Função de comparação para o qsort
int comparar(const void *a, const void *b) {
    Aresta *arestaA = (Aresta *)a;
    Aresta *arestaB = (Aresta *)b;
    return arestaA->w - arestaB->w;
}

// Função Find do Union-Find (com compressão de caminho)
// Encontra o representante (raiz) do conjunto da cidade i
int find(int i) {
    if (pai[i] == i)
        return i;
    // Compressão de caminho: aponta o nó diretamente para a raiz
    return pai[i] = find(pai[i]);
}

// Une os conjuntos de duas cidades i e j
void uniao(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);
    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j;
    }
}

int main() {
    int m, n;

    // Lê M e N. O loop para quando M e N forem 0
    while (scanf("%d %d", &m, &n) && (m != 0 || n != 0)) {
        
        // Leitura das arestas
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &arestas[i].u, &arestas[i].v, &arestas[i].w);
        }

        //Ordenar as arestas pelo peso
        qsort(arestas, n, sizeof(Aresta), comparar);

        // Inicializacada cidade é pai de si mesma inicialmente
        for (int i = 0; i < m; i++) {
            pai[i] = i;
        }

        int soma_distancias = 0;
        
        // Kruskal Iterar pelas arestas ordenadas
        for (int i = 0; i < n; i++) {
            int u = arestas[i].u;
            int v = arestas[i].v;
            int w = arestas[i].w;

            // Se as cidades u e v não estão no mesmo conjunto (não formam ciclo)
            if (find(u) != find(v)) {
                uniao(u, v);          // Conecta as cidades
                soma_distancias += w; // Adiciona a distância ao total
            }
        }

        printf("%d\n", soma_distancias);
    }

    return 0;
}