#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50005
#define MAX_ID 100005


int fila[MAX_N];

int saiu[MAX_ID]; 

int main() {
    int N, M, id_removido;

    if (scanf("%d", &N) != 1) return 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &fila[i]);
    }


    if (scanf("%d", &M) == 1) {
        for (int i = 0; i < M; i++) {
            scanf("%d", &id_removido);
            saiu[id_removido] = 1;
        }
    }

    int primeiro = 1;
    for (int i = 0; i < N; i++) {
        int id_atual = fila[i];
        
        if (!saiu[id_atual]) {
            if (!primeiro) {
                printf(" ");
            }
            printf("%d", id_atual);
            primeiro = 0;
        }
    }
    
    printf("\n");

    return 0;
}