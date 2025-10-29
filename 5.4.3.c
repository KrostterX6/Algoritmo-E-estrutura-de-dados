#include <stdio.h>
#include <stdlib.h>

// O Nó (célula) da lista
typedef struct Celula {
    int dado;
    struct Celula* prox; // Ponteiro pro próximo
    struct Celula* ant;  // Ponteiro pro anterior
} Celula;

// A Fila (guarda o início e o fim)
typedef struct Fila {
    Celula* inicio;
    Celula* fim;
} Fila;

//Cria a fila (vazia).
Fila* criar_fila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}


// Adiciona um número no FIM da fila

void enfileirar(Fila* fila, int dado) {
    //Cria a nova célula
    Celula* nova_celula = (Celula*)malloc(sizeof(Celula));
    if (nova_celula == NULL) {
        printf("Erro de alocacao!\n");
        exit(1);
    }
    nova_celula->dado = dado;
    nova_celula->prox = NULL; // Novo fim, não tem próximo

    //A fila tava vazia?
    if (fila->fim == NULL) {
        nova_celula->ant = NULL;
        fila->inicio = nova_celula;
        fila->fim = nova_celula;
    } 
    //A fila já tinha gente
    else {
        nova_celula->ant = fila->fim; // O anterior dele é o antigo fim
        fila->fim->prox = nova_celula; // O antigo fim aponta pra ele
        fila->fim = nova_celula;       // Atualiza quem é o novo fim
    }
}


// Tira o primeiro cara da fila.

int desenfileirar(Fila* fila) {
    //Fila vazia?
    if (fila->inicio == NULL) {
        printf("Erro: Fila vazia!\n");
        return -1; // Erro
    }

    //Guarda o cara que vai sair
    Celula* celula_removida = fila->inicio;
    int dado_removido = celula_removida->dado;

    // O novo início é o próximo
    fila->inicio = fila->inicio->prox;

    //A fila ficou vazia?
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    } else {
        // Atualiza o ponteiro 'ant' do novo início
        fila->inicio->ant = NULL;
    }

    free(celula_removida);
    return dado_removido;
}


  //Mostra como está a fila.
 
void imprimir_fila(Fila* fila) {
    if (fila->inicio == NULL) {
        printf("Fila: (vazia)\n");
        return;
    }
    printf("Fila (inicio -> fim): ");
    Celula* atual = fila->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

//Libera toda a memória.
void liberar_fila(Fila* fila) {
    Celula* atual = fila->inicio;
    while (atual != NULL) {
        Celula* temp = atual;
        atual = atual->prox;
        free(temp); // Libera célula por célula
    }
    free(fila); // Libera a estrutura da fila
}
//teste

int main() {
    Fila* minha_fila = criar_fila();
    
    // Bota na fila
    enfileirar(minha_fila, 10);
    enfileirar(minha_fila, 20);
    enfileirar(minha_fila, 30);
    imprimir_fila(minha_fila); // Fila: 10 20 30

    // Tira da fila
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 10
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 20
    imprimir_fila(minha_fila); // Fila: 30
    
    printf("Saiu: %d\n", desenfileirar(minha_fila)); // Sai: 30
    imprimir_fila(minha_fila); // Fila: (vazia)

    // Tenta tirar de fila vazia
    desenfileirar(minha_fila); 

    // Limpeza
    liberar_fila(minha_fila);
    return 0;
}

//Eu não tenho ideia de como eu fiz isso funcionar