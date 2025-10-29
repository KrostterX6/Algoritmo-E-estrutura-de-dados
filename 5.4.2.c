#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int dado;
    struct Celula* prox;
    struct Celula* ant;
} Celula;

// A Fila (guarda APENAS a célula-cabeça)
typedef struct Fila {
    Celula* cabeca;
} Fila;


Fila* criar_fila() {
    //Aloca a estrutura da fila
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro de alocacao (fila)!\n");
        exit(1);
    }

    //Aloca a CÉLULA-CABEÇA
    fila->cabeca = (Celula*)malloc(sizeof(Celula));
    if (fila->cabeca == NULL) {
        printf("Erro de alocacao (cabeca)!\n");
        exit(1);
    }
    
    //Inicializa a lista circular vazia
    // A cabeça aponta para si mesma (prox e ant)
    fila->cabeca->prox = fila->cabeca;
    fila->cabeca->ant = fila->cabeca;
    
    return fila;
}

void enfileirar(Fila* fila, int dado) {
    //Cria a nova célula
    Celula* nova_celula = (Celula*)malloc(sizeof(Celula));
    if (nova_celula == NULL) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    nova_celula->dado = dado;

    //Pega os vizinhos (o último antigo e a cabeça)
    Celula* ultimo_antigo = fila->cabeca->ant;
    Celula* cabeca = fila->cabeca;

    //Conecta a nova célula na lista
    nova_celula->prox = cabeca;         // O próximo do novo é a cabeça
    nova_celula->ant = ultimo_antigo; // O anterior do novo é o último antigo

    //Atualiza os vizinhos para apontarem pro novo
    cabeca->ant = nova_celula;
    ultimo_antigo->prox = nova_celula;
}

int desenfileirar(Fila* fila) {
    Celula* cabeca = fila->cabeca;

    //Fila vazia? (Se o próximo da cabeça é ela mesma)
    if (cabeca->prox == cabeca) {
        printf("Erro: Fila vazia!\n");
        return -1; // Erro
    }

    //Pega a célula a ser removida (o primeiro da fila)
    Celula* celula_removida = cabeca->prox;
    int dado_removido = celula_removida->dado;

    //Pega o novo primeiro
    Celula* novo_inicio = celula_removida->prox;

    //"Pula" a célula removida, ligando a cabeça ao novo início
    cabeca->prox = novo_inicio;
    novo_inicio->ant = cabeca;

    //Libera a memória e retorna o dado
    free(celula_removida);
    return dado_removido;
}

void imprimir_fila(Fila* fila) {
    Celula* cabeca = fila->cabeca;
    
    if (cabeca->prox == cabeca) {
        printf("Fila: (vazia)\n");
        return;
    }
    
    // Começa no primeiro (depois da cabeça) e para quando voltar pra cabeça
    printf("Fila (inicio -> fim): ");
    Celula* atual = cabeca->prox;
    while (atual != cabeca) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}


void liberar_fila(Fila* fila) {
    Celula* cabeca = fila->cabeca;
    Celula* atual = cabeca->prox;
    
    // Libera todas as células de dados
    while (atual != cabeca) {
        Celula* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    
    free(cabeca); // Libera a célula-cabeça
    free(fila);   // Libera a estrutura da fila
}



int main() {
    Fila* minha_fila = criar_fila();
    
    // Bota na fila
    enfileirar(minha_fila, 10);
    enfileirar(minha_fila, 20);
    enfileirar(minha_fila, 30);
    imprimir_fila(minha_fila); // Fila: 10 20 30

    // Tira da fila (FIFO)
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 10
    imprimir_fila(minha_fila); // Fila: 20 30
    
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 20
    
    // Bota mais um
    enfileirar(minha_fila, 40);
    imprimir_fila(minha_fila); // Fila: 30 40
    
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 30
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 40
    imprimir_fila(minha_fila); // Fila: (vazia)
    
    // Tenta tirar de fila vazia
    desenfileirar(minha_fila); 

    // Limpeza
    liberar_fila(minha_fila);
    return 0;
}