#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAGOES 1005

typedef struct {
    int items[MAX_VAGOES];
    int top;
} Stack;

// Inicializa a pilha
void init_stack(Stack* s) {
    s->top = -1;
}

// Verifica se a pilha está vazia
bool is_empty(Stack* s) {
    return s->top == -1;
}

// Adiciona um elemento ao topo da pilha
void push(Stack* s, int value) {
    if (s->top < MAX_VAGOES - 1) {
        s->top++;
        s->items[s->top] = value;
    }
}

// Remove e retorna o elemento do topo da pilha
int pop(Stack* s) {
    if (!is_empty(s)) {
        int value = s->items[s->top];
        s->top--;
        return value;
    }
    return -1; // Erro (pilha vazia)
}

// Retorna o elemento do topo sem remover
int peek(Stack* s) {
    if (!is_empty(s)) {
        return s->items[s->top];
    }
    return -1; // Erro (pilha vazia)
}

// Função principal para resolver o problema para um dado N e permutação
void solve() {
    int N;
    // Loop principal: Continua lendo N até que seja 0
    while (scanf("%d", &N) == 1 && N != 0) {
        int desired_output[N];
        int first_vagon;

        while (true) {
            // Tenta ler o primeiro vagão da próxima permutação
            if (scanf("%d", &first_vagon) != 1) return; // Erro na leitura ou EOF

            if (first_vagon == 0) {
                // Fim do bloco de permutações para o N atual
                printf("\n"); // Linha em branco após o bloco, conforme o exemplo
                break;
            }

            // Armazena o primeiro vagão
            desired_output[0] = first_vagon;

            // Lê o restante da permutação (N-1 vagões)
            for (int i = 1; i < N; i++) {
                if (scanf("%d", &desired_output[i]) != 1) return; // Erro na leitura ou EOF
            }

            Stack station;
            init_stack(&station);

            int next_input_vagon = 1; // Próximo vagão chegando da direção A (1, 2, 3...)
            bool possible = true; // Assumimos que é possível inicialmente

            // Percorre a sequência de saída desejada
            for (int i = 0; i < N; i++) {
                int target_vagon = desired_output[i];

                //O vagão desejado está na Estação?
                if (!is_empty(&station) && peek(&station) == target_vagon) {
                    pop(&station); // Sai da Estação para a direção B
                }
                //O vagão desejado ainda não chegou ou está chegando?
                else if (target_vagon >= next_input_vagon) {
                    // Mover vagões de A para a Estação (Stack) até encontrar o desejado
                    while (next_input_vagon < target_vagon) {
                        push(&station, next_input_vagon);
                        next_input_vagon++;
                    }
                    next_input_vagon++;
                }
                //O vagão desejado não está na Estação e já passou pela entrada (já deveria ter saído)
                else {
                    possible = false;
                    break; // Impossível
                }
            }

            //Resultado
            if (possible) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }

        } // Fim do loop de permutações para o N atual
    } // Fim do loop principal (N != 0)
}

int main() {
    
    solve();

    return 0;
}