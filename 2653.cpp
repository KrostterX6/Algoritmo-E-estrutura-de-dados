#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<string> tipos_de_joias_distintas;
    
    string joia;

    // Loop para ler todas as linhas (strings de joias) da entrada padrão
    // O loop continua até que não haja mais dados para ler (EOF)
    while (cin >> joia) {
        // Insere a string lida no conjunto. Se a joia já estiver lá
        // a inserção é ignorada, mantendo apenas tipos distintos.
        tipos_de_joias_distintas.insert(joia);
    }

    // O resultado é simplesmente o número de elementos no conjunto
    // Imprime o tamanho do conjunto seguido de uma quebra de linha
    cout << tipos_de_joias_distintas.size() << "\n";

    return 0;
}

//observação: Foi uma das minhas primeiras tentativas com c++, por favor tornar irrelevante erro de indentação att: Wellbinho