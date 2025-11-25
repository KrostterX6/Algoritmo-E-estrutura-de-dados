#include <stdio.h>
#include <stdbool.h>

#define MAX 1005

int main() {
    int n;
    
    // Estruturas de dados simuladas
    int stack[MAX];
    int queue[MAX];
    int pqueue[MAX]; // Para simular a fila de prioridade
    
    while (scanf("%d", &n) != EOF) {
        
        // Variáveis de controle para Pilha
        int s_top = 0;
        bool is_stack = true;
        
        // Variáveis de controle para Fila
        int q_front = 0, q_rear = 0;
        bool is_queue = true;
        
        // Variáveis de controle para Fila de Prioridade
        int pq_size = 0;
        bool is_pqueue = true;
        
        for (int i = 0; i < n; i++) {
            int command, x;
            scanf("%d %d", &command, &x);
            
            if (command == 1) {
                
                // Pilha: insere no topo
                if (is_stack) stack[s_top++] = x;
                
                // Fila: insere no final
                if (is_queue) queue[q_rear++] = x;
                
                // PQ: insere no array
                if (is_pqueue) pqueue[pq_size++] = x;
                
            } else {
                // Remover e verificar (Pop/Dequeue)
                
                // Verifica Pilha
                if (is_stack) {
                    if (s_top == 0 || stack[--s_top] != x) {
                        is_stack = false;
                    }
                }
                
                // Verifica Fila
                if (is_queue) {
                    if (q_front == q_rear || queue[q_front++] != x) {
                        is_queue = false;
                    }
                }
                
                // Verifica Fila de Prioridade
                if (is_pqueue) {
                    if (pq_size == 0) {
                        is_pqueue = false;
                    } else {
                        // Encontra o índice do maior elemento
                        int max_idx = 0;
                        int max_val = pqueue[0];
                        for (int k = 1; k < pq_size; k++) {
                            if (pqueue[k] > max_val) {
                                max_val = pqueue[k];
                                max_idx = k;
                            }
                        }
                        
                        // Verifica se o maior é igual a X
                        if (max_val != x) {
                            is_pqueue = false;
                        } else {
                            // Remove o elemento movendo o último para a posição dele
                            pqueue[max_idx] = pqueue[pq_size - 1];
                            pq_size--;
                        }
                    }
                }
            }
        }
        
        // Lógica de Saída
        int valid_count = 0;
        if (is_stack) valid_count++;
        if (is_queue) valid_count++;
        if (is_pqueue) valid_count++;
        
        if (valid_count == 0) {
            printf("impossible\n");
        } else if (valid_count > 1) {
            printf("not sure\n");
        } else {
            if (is_stack) printf("stack\n");
            else if (is_queue) printf("queue\n");
            else if (is_pqueue) printf("priority queue\n");
        }
    }

    return 0;
}