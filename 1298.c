#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 605
#define MAX_SIZE (MAX_N * MAX_N)

// Estrutura Union-Find
int parent[MAX_SIZE];
int rank_uf[MAX_SIZE]; 

// Inicializa a estrutura Union-Find
void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank_uf[i] = 0;
    }
}

// Encontra a raiz do conjunto (com Path Compression)
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

// Une dois conjuntos (com Union by Rank)
// Retorna 1 se a união for bem-sucedida, 0 se já estiverem no mesmo conjunto (ciclo)
int union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank_uf[a] < rank_uf[b]) {
            int temp = a; a = b; b = temp;
        }
        parent[b] = a;
        if (rank_uf[a] == rank_uf[b])
            rank_uf[a]++;
        return 1; 
    }
    return 0; 
}

// Função para calcular o índice 1D da célula (r, c)
// Células são 1-indexadas, mas o array é 0-indexado
int get_cell_index(int r, int c, int N) {
    // r e c são 1-indexados (de 1 a N)
    return (r - 1) * N + (c - 1);
}

void solve() {
    int N;
    while (scanf("%d", &N) == 1) {
        // A matriz de entrada tem 2*N-1 linhas, cada uma com N caracteres.
        // As linhas são lidas como strings
        
        char input[2 * MAX_N][MAX_N + 1];
        
        for (int i = 0; i < 2 * N - 1; i++) {
            scanf("%s", input[i]);
        }
        //vértices do grafo
        int total_cells = N * N;
        make_set(total_cells);
        
        int interrupcoes = 0;
        int connected = 0;
        
        //linhas de entrada
        for (int i = 0; i < 2 * N - 1; i++) {
            int y_barreira = i + 1;
            
            // As linhas ímpares (i=0, 2, 4, ...) descrevem barreiras com y_barreira ímpar.
            if (y_barreira % 2 != 0) {
                // Barreira Horizontal (H esperada)
                int r1 = (y_barreira + 1) / 2; 
                int r2 = r1 + 1;             
                
                // Validação de limite para barreiras horizontais:
                // Se r2 > N, a barreira está na borda externa inferior e não separa duas células internas.
                if (r2 > N) continue; 

                for (int j = 0; j < N; j++) {
                    int c = j + 1; 
                    char orientacao = input[i][j];

                    // Barreira está no estado correto (instalada): 'H'
                    if (orientacao == 'H') {
                        int idx1 = get_cell_index(r1, c, N);
                        int idx2 = get_cell_index(r2, c, N);
                        if (union_sets(idx1, idx2) == 0) {
                            // Ciclo detectado: esta barreira deve ser interrompida.
                            interrupcoes++; 
                        } else {
                            connected++;
                        }
                    } else { // Barreira está no estado incorreto (interrompida): 'V'
                         // Esta barreira deve ser instalada (girada de V para H).
                    }
                }
            } else {
                // Barreira Vertical (V esperada)
                int r = y_barreira / 2; 
                
                for (int j = 0; j < N; j++) {
                    int c1 = j + 1; 
                    int c2 = c1 + 1; 
                    
                    // Validação de limite para barreiras verticais:
                    // Se c2 > N, a barreira está na borda externa direita e não separa duas células internas.
                    if (c2 > N) continue;

                    char orientacao = input[i][j];

                    // Barreira está no estado correto (instalada): 'V
                    if (orientacao == 'V') {
                        // Tenta unir as duas células. Se já estiverem unidas, cria um ciclo
                        int idx1 = get_cell_index(r, c1, N);
                        int idx2 = get_cell_index(r, c2, N);
                        if (union_sets(idx1, idx2) == 0) {
                             // Ciclo detectado: esta barreira deve ser interrompida
                            interrupcoes++; 
                        } else {
                            connected++;
                        }
                    } else { // Barreira está no estado incorreto (interrompida): 'H'
                        // Esta barreira deve ser instalada (girada de H para V)
                    }
                }
            }
        }
        
        printf("%d\n", interrupcoes + (total_cells - 1 - connected));
    }
}

int main() {
    solve();
    return 0;
}

//por algum motivo esse código só não estava funcionando quando eu mandava par ao beecrwod :P
//depois eu arrumo