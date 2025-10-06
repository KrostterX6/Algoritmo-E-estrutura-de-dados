#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
     int Nqualquer;
    char linha[1000];
    scanf("%d", &Nqualquer);
    getchar(); //comer enter

    //criar uma pila que vai receber caracteres especiais e interpretar como diamantes
    //grãos de areia são irrelevantes então não fiz nada sobre isso

    for (int i = 0; i < Nqualquer; i++) {
        fgets(linha, 1000, stdin); // ler o caso
        int pilha = 0, diamantes = 0;
        for (int j = 0; linha[j] != '\0'; j++) {
            if (linha[j] == '<') {
                pilha++; //empilar uma ponta do diamante
            } else if (linha[j] == '>' && pilha > 0) {
                diamantes++; //diamante encontrado
                pilha--; // desempilhar
            }
        }
        printf("%d\n", diamantes);
    }
    return 0;
}