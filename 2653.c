//Esta dando time limit, porém funciona, depois eu volto e corrijo o código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOIAS 500005 
#define MAX_TAMANHO 105  

char joias[MAX_JOIAS][MAX_TAMANHO];

int compara_strings(const void *a, const void *b) {
    const char *str_a = (const char *)a;
    const char *str_b = (const char *)b;
    return strcmp(str_a, str_b);
}

int main() {

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    
    int total_lido = 0;
    
    while (scanf("%s", joias[total_lido]) != EOF) {
        total_lido++;
        if (total_lido >= MAX_JOIAS) break;
    }
    
    if (total_lido == 0) {
        printf("0\n");
        return 0;
    }

    qsort(joias, total_lido, sizeof(joias[0]), compara_strings);

    int joias_distintas = 0;
    
    if (total_lido > 0) {
        joias_distintas = 1;
        
        for (int i = 1; i < total_lido; i++) {
            if (strcmp(joias[i], joias[i-1]) != 0) {
                joias_distintas++;
            }
        }
    }

    printf("%d\n", joias_distintas);

    return 0;
}