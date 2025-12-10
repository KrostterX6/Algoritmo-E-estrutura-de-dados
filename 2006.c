#include <stdio.h>

int main() {
    int T;
    int resposta;
    int acertos = 0;
    int i;

    scanf("%d", &T);

    for (i = 0; i < 5; i++) {
        scanf("%d", &resposta);
        
        if (resposta == T) {
            acertos++;
        }
    }

    printf("%d\n", acertos);

    return 0;
}