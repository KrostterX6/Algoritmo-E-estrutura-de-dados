#include <stdio.h>

int main() {

    int N, M;

    if (scanf("%d", &N) != 1) {
        return 1;
    }
    if (scanf("%d", &M) != 1) {
        return 1;
    }
    int diferenca = N - M;

    printf("%d\n", diferenca);

    return 0;
}