#include <stdio.h>

// Definindo o tamanho máximo (1024 x 1024)
#define MAX 1030 

char grid[MAX][MAX];

// Filas para o BFS (armazenam coordenadas linha e coluna)
// Tamanho suficiente para cobrir toda a matriz
int q_row[MAX * MAX];
int q_col[MAX * MAX];

// Vetores de direção: Cima, Baixo, Esquerda, Direita
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int N, M;

void bfs(int start_r, int start_c) {
    int head = 0, tail = 0;
    
    // Adiciona o ponto inicial na fila
    q_row[tail] = start_r;
    q_col[tail] = start_c;
    tail++;
    
    // Marca como visitado imediatamente (transforma em 'o')
    grid[start_r][start_c] = 'o';
    
    while(head < tail) {
        int r = q_row[head];
        int c = q_col[head];
        head++;
        
        // Verifica os 4 vizinhos
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // Se estiver dentro dos limites e for um pixel branco '.'
            if(nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] == '.') {
                // Marca como visitado
                grid[nr][nc] = 'o';
                
                // Adiciona na fila para processar depois
                q_row[tail] = nr;
                q_col[tail] = nc;
                tail++;
            }
        }
    }
}

int main() {
    // Leitura das dimensões
    if (scanf("%d %d", &N, &M) != 2) return 0;
    
    // Leitura do grid
    for(int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
    }
    
    int cliques = 0;
    
    // Percorre a matriz procurando por regiões não visitadas ('.')
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(grid[i][j] == '.') {
                // Nova região encontrada
                cliques++;
                // Preenche toda a região conectada para não contar de novo
                bfs(i, j);
            }
        }
    }
    
    printf("%d\n", cliques);
    
    return 0;
}