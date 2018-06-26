#include <iostream>

using namespace std;

struct Elem{
    int key;
    string valor;

    Elem(int key=0,string valor=""){
        this->key = key;
        this->valor = valor;
    }

    ///comparando elementos
    bool operator == (Elem outro){
        return this->key == outro.key;
    }

    ///imprimir um elemento
    friend ostream& operator <<(ostream& os, Elem e){
        os << e.key << "," << e.valor;
        return os;
    }
};

#include<vector>
#include<list>
#include<algorithm>

struct hashLista{
    vector<list<Elem>>* vet;
    int qtdElem=0;

    hashLista(int tamanho){
        vet = new vector<list<Elem>>(tamanho);
    }

    ///buscar elemento
    bool buscar(Elem elem){
        int pos = elem.key % vet->size();
        auto& lista = vet->at(pos);
        auto it = find(lista.begin(),lista.end(),elem);
        return (it != lista.end());
    }

    ///inserir elemento
    bool inserir(Elem elem){
        int pos = elem.key % vet->size();
        auto& lista = vet->at(pos);
        auto it = find(lista.begin(),lista.end(),elem);
        if(it != lista.end())
            return false; ///nao posso inserir,elemento ja existe
        lista.push_back(elem);
        qtdElem++;
        return true;
    }

    ///remover elemento
    bool remover(Elem elem){
        int pos = elem.key % vet->size();
        auto& lista = vet->at(pos);
        auto it = find(lista.begin(),lista.end(),elem);
        if(it == lista.end())
            return false;
        lista.erase(it);
        return true;
    }

    ///alterar tamanho do vetor
    void resizer(int novoTamanho){
        auto vetAntigo = vet;
        vet = new vector<list<Elem>>(novoTamanho);
        for(auto& lista : *vetAntigo)
            for(auto& elem : lista)
                this->inserir(elem);
        delete vetAntigo;
    }

    ///mostrar elementos
    void mostrar(){
        for(auto& lista : *vet)
            for(auto& elem : lista)
                cout << elem << ";" << endl;
    }
};

int main()
{
    Elem elem1(0,"ok");
    Elem elem2(23,"ok");
    Elem elem3(12,"ok");
    Elem elem4(11,"ok");
    Elem elem5(98,"ok");

    hashLista vetList(4);
    vetList.inserir(elem1);
    vetList.inserir(elem2);
    vetList.inserir(elem3);
    vetList.inserir(elem4);

    cout << vetList.qtdElem << endl;
    vetList.mostrar();

    cout << "removendo o 23" << endl;
    vetList.remover(elem2);
    vetList.mostrar();

    cout << "aumentando o tamanho" << endl;
    vetList.resizer(5);
    vetList.inserir(elem2);
    vetList.inserir(elem5);
    vetList.mostrar();
    /*cout << "buscando o elemento5" << endl;
    if(!hashLista.buscar(elem5))
        cout << "ok";
    */
    return 0;
}
