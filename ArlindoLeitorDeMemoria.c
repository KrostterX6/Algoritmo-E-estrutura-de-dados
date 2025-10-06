// Uso de Memória Arlindo Versão para Windows

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <psapi.h>   // Para a função GetProce

const int MAX = 2000000;

void print_memory_usage() {
    
    PROCESS_MEMORY_COUNTERS pmc;

    HANDLE hProcess = GetCurrentProcess();

    // Chama a função da API do Windows para preencher a estrutura pmc
    // O primeiro argumento é o handle do processo
    // O segundo é um ponteiro para a estrutura
    // O terceiro é o tamanho da estrutura
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        // PeakWorkingSetSize é o equivalente mais próximo do ru_maxrss do Linux
        // Ele representa o pico de memória RAM física usada pelo processo
        // O valor é fornecido em BYTES, então dividimos por 1024 para ter em KB
        printf("Memory usage: %zu KB\n", pmc.PeakWorkingSetSize / 1024);
    } else {
        printf("Falha ao obter informacoes de memoria.\n");
    }

    // O handle retornado por GetCurrentProcess() é um pseudo-handle
}

int main() {
    // exemplo de uso de memória
    int *array = malloc(MAX * sizeof(int));

    // Verifica se a alocação de memória foi bem-sucedida
    if (array == NULL) {
        printf("Falha ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i < MAX; i++) {
        array[i] = i;
    }

    print_memory_usage();

    free(array);
    return 0;
}