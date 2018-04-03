#include <iostream>
#include <list>

using namespace std;

//funcao mostrar
void mostrar(list<int> fila){
    for(int jog:fila)
        cout << jog<< " ";
    cout << "\n";
}

//funcao rodar
void rodar(list<int>& fila){
    fila.push_back(fila.front());
    fila.pop_front();
}

int main1()
{
    int jogador,qtd,saltos;
    jogador = 0;
    qtd = 0;
    saltos = 0;

    cout << "informe qtd de jogadores,o primeiro e o numero de saltos!" << endl;
    cin >> qtd >> jogador >> saltos;
    cout << "\n";

    //criando e preenchendo a lista
    list<int> fila;
    for(int i = 1; i <= qtd; i++)
        fila.push_back(i);

    //encontrando o primeiro jogador
    while(fila.front() != jogador)
        rodar(fila);
    mostrar(fila);

    //matar jogadores com saltos
    //o jogador nao pode se matar
    while (fila.size() > 1) {
        for(int i = 0; i <= saltos; i++)
            rodar(fila);
        fila.pop_front();
        mostrar(fila);
    }

    return 0;
}

