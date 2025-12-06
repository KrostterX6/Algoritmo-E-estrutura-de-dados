#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10005 // O limite é 10000, deixei uma margem de segurança

// Estrutura para a fila da BFS
typedef struct {
    int valor;
    int passos;
} Estado;

Estado fila[MAX]; // Fila estática para a BFS

// Função para inverter os dígitos de um número
int inverter(int n) {
    int invertido = 0;
    while (n > 0) {
        invertido = invertido * 10 + n % 10;
        n /= 10;
    }
    return invertido;
}

int bfs(int inicio, int fim) {
    // Vetor para marcar visitados e evitar loops
    bool visitado[MAX];
    memset(visitado, false, sizeof(visitado));

    int frente = 0;
    int tras = 0;

    // Adiciona o estado inicial na fila
    fila[tras].valor = inicio;
    fila[tras].passos = 0;
    tras++;
    visitado[inicio] = true;

    while (frente < tras) {
        Estado atual = fila[frente];
        frente++;

        if (atual.valor == fim) {
            return atual.passos;
        }

        // Tenta a Operação 1: Adicionar 1
        int proximo1 = atual.valor + 1;
        if (proximo1 <= 10000 && !visitado[proximo1]) {
            visitado[proximo1] = true;
            fila[tras].valor = proximo1;
            fila[tras].passos = atual.passos + 1;
            tras++;
        }

        // Tenta a Operação 2: Inverter dígitos
        int proximo2 = inverter(atual.valor);
        if (proximo2 <= 10000 && !visitado[proximo2]) {
            visitado[proximo2] = true;
            fila[tras].valor = proximo2;
            fila[tras].passos = atual.passos + 1;
            tras++;
        }
    }
    return -1; // Caso não encontre (teoricamente não ocorre dada a descrição)
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int A, B;
        scanf("%d %d", &A, &B);
        printf("%d\n", bfs(A, B));
    }

    return 0;
}