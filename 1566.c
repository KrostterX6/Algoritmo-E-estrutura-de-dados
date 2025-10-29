#include <stdio.h>
#include <string.h> // Para usar a função memset

// O tamanho máximo necessário para o array de frequência
#define MAX_ALTURA 231
// devido a questoes de gripe, serei o mais direto possivel nos comentarios deste codigo
int main() {
    int nc; // Número de casos de teste
    scanf("%d", &nc);

    // Array para contar a frequência de cada altura
    int frequencia[MAX_ALTURA];

    while (nc--) {
        int n; // Número de pessoas na cidade
        scanf("%d", &n);

        // 1. Zera o array de frequência para cada novo caso de teste, crucial para não misturar dados de cidades diferentes
        // sizeof(frequencia) calcula o tamanho total do array em bytes
        memset(frequencia, 0, sizeof(frequencia));

        // 2. Lê as N alturas e popula o array de frequência.
        for (int i = 0; i < n; i++) {
            int h; // Altura da pessoa atual
            scanf("%d", &h);
            frequencia[h]++; // Incrementa o contador para a altura 'h'
        }

        // 3 Imprimir as alturas de forma ordenada
        // flag primeiro é usado para controlar os espaços entre os números
        int flag_primeiro = 1;
        
        // Itera por todas as alturas possíveis
        for (int h = 20; h < MAX_ALTURA; h++) {
            // Imprime a altura 'h' quantas vezes ela foi contada
            for (int i = 0; i < frequencia[h]; i++) {
                if (flag_primeiro) {
                    printf("%d", h);
                    flag_primeiro = 0; // A partir daqui, não é mais o primeiro número
                } else {
                    printf(" %d", h);
                }
            }
        }
        printf("\n"); // pura questao estetica, pra pular uma linha e ficar bonitinho no final de cada caso
    }

    return 0;
}