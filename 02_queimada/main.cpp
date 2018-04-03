#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;


const int nc = 60;
const int nl = 20;

//criando uma estrutura "par"
struct Par{
    int l, c;

    //construtor
    Par(int l = 0, int c = 0){
        this->l = l;
        this->c = c;
    }
};

//criando um vetor e preenchendo com varios "pares"
vector<Par> getNeib(Par p){
    vector<Par> v;
    v.push_back(Par(p.l, p.c + 1));
    v.push_back(Par(p.l, p.c - 1));
    v.push_back(Par(p.l + 1, p.c));
    v.push_back(Par(p.l - 1, p.c));
    return v;
}

//funcao mostrar a matriz
void mostrar(vector<string>& mat){
    cout << string(50, '\n');
    for(string s : mat)
        cout << s << endl;
    getchar();
}

//funcao embaralhar
vector<Par> embaralhar(vector<Par> vet){
    for(int i = 0; i < (int) vet.size(); i++){
        int aleat = rand() % vet.size();
        swap(vet[i], vet[aleat]);
    }
    return vet;
}

//funcao queimar
int queimar(vector<string> &mat, int l, int c, int nivel){
    //contador de arvores queimadas
    int cont = 0;

    if(l < 0 || l >= nl)
        return cont;
    if(c < 0 || c >= nc)
        return cont;
    if(mat[l][c] != '#')
        return cont;
    if(mat[l][c] == '#')
        mat[l][c] = '0' + nivel % 10;
        cont = 1;
        mostrar(mat);
        //for range
        for(Par p : embaralhar(getNeib(Par(l, c))))
            cont += queimar(mat, p.l, p.c, nivel + 1); //contador ja recebe o retorno da funcao, que pode ser 0 ou 1
            //quando a recursao volta
            mat[l][c] = '.'; //coloca o ponto na posicao
    return cont;
}

int main()
{
    int nivel = 0; //variavel para contar o nivel da funcao

    srand(time(NULL));
    vector<string> mat(nl, string(nc, ' '));
    int narvores = nl * nc * 1.5;
    for(int i = 0; i < narvores; i++){
        mat[rand() % nl][rand() % nc] = '#';
    }

    mostrar(mat);

    int total = queimar(mat, 0, 0, nivel); //variavel que recebe o total de arvores queimadas
    cout << total << " arvores queimaram\n";

    return 0;
}
