#include <stdio.h>
#include <stdlib.h>

int compara_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int n_casos;
    
    if (scanf("%d", &n_casos) != 1) return 0;
    
    while (n_casos--) {
        int m_alunos;
        scanf("%d", &m_alunos);
        
        int fila_original[1000];
        int fila_ordenada[1000];
        
        for (int i = 0; i < m_alunos; i++) {
            scanf("%d", &fila_original[i]);
            fila_ordenada[i] = fila_original[i];
        }
        
        qsort(fila_ordenada, m_alunos, sizeof(int), compara_desc);
        
        int nao_trocaram = 0;
        
        for (int i = 0; i < m_alunos; i++) {
            if (fila_original[i] == fila_ordenada[i]) {
                nao_trocaram++;
            }
        }
        
        printf("%d\n", nao_trocaram);
    }
    
    return 0;
}

//fiquei com preguiça de comentar, o algoritmo é meio simples demais, eu sei o que tudo faz por instinto