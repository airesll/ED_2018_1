#include "libs/ed_base.h"
#include "libs/ed_mat.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm> //random_shuffle
#include <cstdlib>
#include <ctime>

using namespace std;

const char PAREDE = 'k'; //PARREDES, PRETAS
const char ABERTO = 'w'; //CAMINHO, BRANCO
const char EMBUSCA = 'y'; //PROCURANDO, AMARELO
const char CAMINHO = 'b'; //LOCAL POR ONDE ESTA INDO, PRETO
const char ABATIDO = 'm'; // POR ONDE A RECURSAO VOLTOU

//metodo mostar matriz
void mostrarMatriz(matchar& matriz, vector<Par> pilha, Par inicio, Par final){
    mat_draw(matriz);
    for(Par par : pilha)
        mat_focus(par, 'c');
    if(pilha.size() > 0)
        mat_focus(pilha.back(), 'k');
    mat_focus(inicio, 'g');
    mat_focus(final, 'r');
}

//metodo pegar vizinhos
vector<Par> buscaVizinhos(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l + 1, par.c));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l, par.c - 1));
    return vizinhos;
}

//metodo contar vizinhos abertos para serem furados
int contarVizinhosAbertos(matchar &matriz, Par par){
    int contador = 0;
    for(auto vizinho : buscaVizinhos(par))
        if(matriz.is_inside(vizinho) || matriz.get(vizinho) != PAREDE)
            contador++;
    return contador;
}

//metodo embaralhar vetor de vizinhos
vector<Par> embaralhar(vector<Par> vetor){
    std::random_shuffle(vetor.begin(), vetor.end());
    return vetor;
}

//metodo furar vizinho aberto
void furarAberto(matchar &matriz, Par par){
    if(!matriz.equals(par, PAREDE || contarVizinhosAbertos(matriz, par) > 1))
        return;
    matriz.get(par) = ABERTO;
    for(Par vizinho : embaralhar(buscaVizinhos(par)))
        furarAberto(matriz, vizinho);
}

//metodo encontar caminho no labirinto
bool encontarCaminho(matchar& mat, Par inicio, Par final){
    vector<Par> pilha;
    pilha.push_back(inicio);
    mat.get(inicio) = EMBUSCA;

    while(pilha.size() != 0){
        Par topo = pilha.back();
        if(topo == final){
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
            return true;
        }

        vector<Par> vizinhosAbertos;
        mostrarMatriz(mat, pilha, inicio, final);
        for(Par par : buscaVizinhos(topo)){
            if(mat.get(par) == ABERTO){
                vizinhosAbertos.push_back(par);
                mat_focus(par, 'r');
            }
        }

        ed_show();
        if(vizinhosAbertos.size() == 0){
            pilha.pop_back();
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
        }
        else{
            Par escolhido = vizinhosAbertos[rand()% vizinhosAbertos.size()];
            mat.get(escolhido) = EMBUSCA;
            pilha.push_back(escolhido);

            //mostrar a matriz
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
        }
    }
    mostrarMatriz(mat, pilha, inicio, final);
    ed_show();
    return false;
}

//saber se é furavel ou nao
bool furavel(matchar& mat, Par p){
    int contador = 0;
    if(!mat.equals(p, PAREDE))
        return false;
    for(auto &viz : buscaVizinhos(p)){
        if(mat.equals(viz, PAREDE))
            contador++;
    }
    return (contador >= 3);
}

//sortear um numero
int sortear(int x){
    return rand() % x;
}

//mostrar labirinto
void mostarLab(matchar& mat, vector<Par> pilha){
    mat_draw(mat);
    vector<Par> aux;
    while(pilha.size() != 0){
        mat_focus(pilha.back(),'y');
        //aux.push_back(pilha.back());
        pilha.pop_back();
    }
    ed_show();
    while(aux.size() != 0){
        pilha.push_back(aux.back());
        aux.pop_back();
    }
}

//criar labirinto
void criarLab(matchar& mat, vector<Par> pilha){
    mat.get(Par(1, 1)) = ABERTO;
    pilha.push_back(Par(1, 1));
    while(pilha.size() != 0){
        vector<Par> furaveis;
        for(auto viz : buscaVizinhos(pilha.back()))
            if(furavel(mat, viz))
                furaveis.push_back(viz);
        if(furaveis.size() == 0){
            pilha.pop_back();
            mostarLab(mat, pilha);
        }
        else{
           Par sortudo = furaveis[sortear(furaveis.size())];
           mat.get(sortudo) = ABERTO;
           pilha.push_back(sortudo);
           mostarLab(mat, pilha);
        }
    }
}

int main(){
    srand(time(NULL));
    vector<Par> pilha;
    matchar mat(20, 35, PAREDE);
    //furar(mat, Par(1, 1));//chama a função recursiva
    criarLab(mat, pilha);
    mat_draw(mat);
    ed_show();

    Par inicio = mat_get_click(mat, "digite o local de inicio");

    Par final = mat_get_click(mat, "digite o local de fim");
    mat_draw(mat);
    ed_show();

    encontarCaminho(mat, inicio, final);
    ed_lock();//impede que termine abruptamente
    return 0;
}
