#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para representar uma estrada (aresta)
typedef struct {
    int u, v;  // Junções (nós) conectadas
    int peso;  // Custo (peso) da estrada
} Estrada;

int comparaEstradas(const void *a, const void *b) {
    return ((Estrada*)a)->peso - ((Estrada*)b)->peso;
}

int *pai;

// Função para inicializar o Union-Find
void inicializaUnionFind(int numJuncoes) {
    pai = (int*)malloc((numJuncoes + 1) * sizeof(int));
    for (int i = 0; i <= numJuncoes; i++) {
        pai[i] = i; // Inicialmente, cada junção é seu próprio pai
    }
}

// Função Find
int find(int i) {
    if (pai[i] == i) {
        return i;
    }
    return pai[i] = find(pai[i]);
}

// Função Union
int uniao(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);

    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j; // Faz a raiz de i apontar para a raiz de j
        return 1;
    }
    return 0;
}
void resolve() {
    int m, n; // m = número de junções, n = número de estradas

    // Loop para ler múltiplos casos de teste até encontrar m=0 e n=0
    while (scanf("%d %d", &m, &n) == 2 && (m != 0 || n != 0)) {
        // Aloca o array de estradas
        Estrada *estradas = (Estrada*)malloc(n * sizeof(Estrada));
        long long custoTotal = 0; // Usamos long long para garantir que o custo não estoure

        // Leitura das estradas e cálculo do custo total
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &estradas[i].u, &estradas[i].v, &estradas[i].peso);
            custoTotal += estradas[i].peso;
        }

        //Inicializa a estrutura Union-Find
        inicializaUnionFind(m);

        //Ordena as estradas por peso (custo)
        qsort(estradas, n, sizeof(Estrada), comparaEstradas);

        //Aplica o Algoritmo de Kruskal para encontrar o Custo da AGM
        long long custoAGM = 0;
        int arestasAGM = 0;

        for (int i = 0; i < n; i++) {
            // Tenta unir as junções u e v
            if (uniao(estradas[i].u, estradas[i].v)) {
                // Se a união for bem-sucedida (não forma ciclo), adiciona à AGM
                custoAGM += estradas[i].peso;
                arestasAGM++;

                // O algoritmo pode parar quando m-1 arestas forem adicionadas
                if (arestasAGM == m - 1) {
                    break;
                }
            }
        }

        //Calcula a economia máxima: Custo Total - Custo da AGM
        long long economiaMaxima = custoTotal - custoAGM;

        // Saída
        printf("%lld\n", economiaMaxima);

        // Libera a memória alocada
        free(estradas);
        free(pai);
    }
}

int main() {
    resolve();

    return 0;
}