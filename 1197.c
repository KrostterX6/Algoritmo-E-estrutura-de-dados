#include <stdio.h>

int main() {
    int v, t;

    while (scanf("%d %d", &v, &t) != EOF) {
        
        int resultado = 2 * v * t;

        printf("%d\n", resultado);
    }

    return 0;
}