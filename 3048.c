#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    int numero_atual;
    int ultimo_marcado = 0; 
    int quantidade_maxima_marcada = 0;

    if (scanf("%d", &N) != 1) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &numero_atual) != 1) {
            break;
        }

        if (numero_atual != ultimo_marcado) {
            quantidade_maxima_marcada++;

            ultimo_marcado = numero_atual;
        }
    }

    printf("%d\n", quantidade_maxima_marcada);

    return 0;
}