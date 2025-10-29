#include <stdio.h>
#define MAX_SIZE 51

typedef struct {
    int items[MAX_SIZE];
    int front; // Índice do primeiro elemento
    int rear;  // Índice do último elemento
    int count; // Número de elementos na fila
} Queue;

// Inicializa a fila
void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

// Verifica se a fila está vazia
int isEmpty(Queue *q) {
    return q->count == 0;
}

// Retorna o tamanho da fila
int size(Queue *q) {
    return q->count;
}

// Adiciona um item ao final da fila (enqueue)
void enqueue(Queue *q, int value) {
    // Usa aritmética modular para fazer a fila "circular"
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    q->count++;
}

// Remove e retorna o item da frente da fila (dequeue)
int dequeue(Queue *q) {
    int item = q->items[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return item;
}

/*Fim da Implementação da Fila */


int main() {
    int n;

    // Continua lendo até que a entrada seja 0
    while (scanf("%d", &n) == 1 && n != 0) {
        
        Queue cardQueue;
        initQueue(&cardQueue);

        // 1.Preenche a fila com as cartas de 1 a n
        for (int i = 1; i <= n; i++) {
            enqueue(&cardQueue, i);
        }

        // Array para guardar as cartas descartadas
        // n-1 cartas serão descartadas no máximo (se n > 0)
        int discardedCards[MAX_SIZE];
        int discardedCount = 0;

        // 2.Simula o processo
        while (size(&cardQueue) > 1) {
            
            // Passo 1:Joga fora a carta do topo
            discardedCards[discardedCount++] = dequeue(&cardQueue);
            
            // Passo 2: Move a próxima carta para a base
            
            int topCard = dequeue(&cardQueue);
            enqueue(&cardQueue, topCard);
        }

        //Pega a carta que sobrou
        int remainingCard = 0;
        if (!isEmpty(&cardQueue)) {
            remainingCard = dequeue(&cardQueue);
        }
        

        //Imprime as cartas descartadas
        printf("Discarded cards:");
        for (int i = 0; i < discardedCount; i++) {
            printf(" %d", discardedCards[i]);
            //Adiciona vírgula, exceto no último número
            if (i < discardedCount - 1) {
                printf(",");
            }
        }
        printf("\n");

        //Imprime a carta remanescente
        printf("Remaining card: %d\n", remainingCard);
    }

    return 0;
}