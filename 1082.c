#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 26

// Variáveis globais para o grafo e controle
int adj[MAX][MAX];
int visitados[MAX];
int lista_componente[MAX]; // Armazena nós do componente atual
int tam_lista;             // Quantos nós tem no componente atual
int V, E;

// Função de comparação para o qsort
int compara(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Busca em Profundidade
void dfs(int u) {
    visitados[u] = 1;
    lista_componente[tam_lista] = u;
    tam_lista++;

    for (int v = 0; v < V; v++) {
        // Se existe aresta e v não foi visitado
        if (adj[u][v] == 1 && visitados[v] == 0) {
            dfs(v);
        }
    }
}

int main() {
    int N; // Número de casos de teste
    scanf("%d", &N);

    for (int caso = 1; caso <= N; caso++) {
        scanf("%d %d", &V, &E);

        //Inicializar
        memset(adj, 0, sizeof(adj));
        memset(visitados, 0, sizeof(visitados));

        //Leitura das arestas
        for (int i = 0; i < E; i++) {
            char u_char, v_char;
            // O espaço antes de %c ignora quebras de linha/espaços anteriores
            scanf(" %c %c", &u_char, &v_char);
            
            int u = u_char - 'a';
            int v = v_char - 'a';

            // Grafo não direcionado: aresta vai e volta
            adj[u][v] = 1;
            adj[v][u] = 1;
        }

        printf("Case #%d:\n", caso);

        int componentes_conexos = 0;

        // Iterar sobre todos os vértices para encontrar componentes
        for (int i = 0; i < V; i++) {
            if (visitados[i] == 0) {
                // Novo componente encontrado
                componentes_conexos++;
                tam_lista = 0;
                
                // Coleta todos os nós deste componente
                dfs(i);

                // Ordena os nós para garantir a ordem alfabética na saída
                qsort(lista_componente, tam_lista, sizeof(int), compara);

                // Imprime os nós do componente
                for (int j = 0; j < tam_lista; j++) {
                    printf("%c,", lista_componente[j] + 'a');
                }
                printf("\n");
            }
        }

        // Imprime a contagem total e a linha em branco obrigatória
        printf("%d connected components\n", componentes_conexos);
        printf("\n");
    }

    return 0;
}