#include <stdio.h>
#include <string.h>

//Aviso, os comentarios neste código são extremamente informais
//Porem eles estão neste formato para que eu consiga decorar melhor futuramente o que esses códigos faziam e como eu fiz (Eu tenho o hábito de esquecer)

int ehSudokuValido(int matriz[9][9]) {
    int verificador[10]; // Array para marcar uns numeors

    // Verificar linha
    for (int i = 0; i < 9; i++) {
        // Zera o array verificador para cada nova linha
        memset(verificador, 0, sizeof(verificador));

        for (int j = 0; j < 9; j++) {
            int num = matriz[i][j];
            // Se ja foi visto mandar falso
            if (verificador[num] == 1) {
                return 0;
            }
            // Marca o número como visto
            verificador[num] = 1;
        }
    }

    // checar coluna
    for (int j = 0; j < 9; j++) {
        //era o array verificador para cada nova coluna
        memset(verificador, 0, sizeof(verificador));

        for (int i = 0; i < 9; i++) {
            int num = matriz[i][j];
            //invalidar se tiver numro
            if (verificador[num] == 1) {
                return 0; 
            }
            // Marca o número como visto
            verificador[num] = 1;
        }
    }

    // verificar quadrados 3x3
    for (int blocoLinha = 0; blocoLinha < 9; blocoLinha += 3) {
        for (int blocoColuna = 0; blocoColuna < 9; blocoColuna += 3) {
            // Zera o array verificador para cada novo sub-quadrado
            memset(verificador, 0, sizeof(verificador));

            // Itera dentro do sub-quadrado 3x3 atual
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = matriz[blocoLinha + i][blocoColuna + j];
                    // Se o número já foi visto neste sub-quadrado, a solução é inválida
                    if (verificador[num] == 1) {
                        return 0; // Retorna 0 (falso)
                    }
                    // Marca o número como visto
                    verificador[num] = 1;
                }
            }
        }
    }

    // Se todas as verificações passaram, a solução é válida
    return 1;
}

int main() {
    int n; //funfar matriz
    int instancia;

    // Lê o número total de instâncias a serem testadas
    scanf("%d", &n);

    // Loop para processar cada instância
    for (instancia = 1; instancia <= n; instancia++) {
        int sudoku[9][9];

        // Lê a matriz 9x9 do Sudoku da entrada padrão
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &sudoku[i][j]);
            }
        }

        // Imprime
        printf("Instancia %d\n", instancia);

        // Chama a função de validação e imprime o resultado
        if (ehSudokuValido(sudoku)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }

        // Imprime uma linha em branco após cada instância, como solicitado
        printf("\n");
    }

    return 0;
}

//Gabe Newell me abençoe que este código funcione, Amém