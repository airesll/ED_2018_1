#include <iostream>

using namespace std;

//estrutura do vetor
struct Vetor{
    int * data; //bloco de dados
    int capacidade; //tamanho maximo do vetor
    int _size; // quantidade de elementos que ja estao no vetor

    //construtor passando como parametro capacidade
    Vetor(int capacidade){
        this->data = new int[capacidade];
        this->capacidade = capacidade;
        this->_size = 0;
    }

    //insere novo elemento ao final do vetor
    void push_back(int valor){
        if(this->_size == this->capacidade)
            this->reserve(2 * this->capacidade);
        this->data[this->_size] = valor;
        this->_size += 1;
    }

    //tira o ultimo elemento do vetor
    void pop_back(){
        if(this->_size == 0)
            return;
        this->data[_size] = 0;
        this->_size -= 1;
    }

    //retornar a refencia à variavel dessa posicao
    int& at(int indice){
        return this->data[indice];
    }

    //retorna a referencia a primeira posicao do vetor e possivel modificar
    int& front(){
        return this->data[0];
    }

    //retorna a referencia da ultima posicao do vetor e possivel modificar
    int& back(){
        return this->data[this->_size - 1];
    }

    //nao e modificavel
    int * begin(){
        return &this->data[0];
    }

    //nao e modificavel
    int * end(){
        return &this->data[this->_size];
    }

    //retorna quantos elementos tem no vetor
    int size(){
        return this->_size;
    }

    //retorna a capacidade do vetor
    int capacity(){
        return this->capacidade;
    }

    //metodo reserve modifica a capacidade
    void reserve(int capacidade){
        if(this->capacidade == capacidade){
            return;
        }
        if(this->capacidade > capacidade){
            if(this->_size > capacidade){
                this->_size = capacidade;
                this->capacidade = capacidade;
                for(int i=0; i < this->_size - capacidade; i++)
                    pop_back();
                return;
            }
            if(this->_size <= capacidade){
                this->capacidade = capacidade;
                return;
            }
        }
        if(this->capacidade < capacidade){
            Vetor novovet(this->_size);
            for(int i=0;i<this->_size;i++){
                novovet.at(i) = this->data[i];
            }
            this->data = new int[capacidade];
            this->capacidade = capacidade;
            for(int i=0;i<this->_size;i++){
                this->data[i] = novovet.at(i);
            }
            return;
        }
    }
};


int main()
{
    //criando um vetor de 5 posicoes e colocando valores
    Vetor vevet(5);
    vevet.push_back(5);
    vevet.push_back(3);
    vevet.push_back(1);
    vevet.push_back(7);

    for(int i=0; i<vevet.size();i++)
        cout << vevet.at(i) << " ";
    cout << endl;
    cout << "capacidade: " << vevet.capacity() << endl; //testando o capacity
    cout << "size: " << vevet.size() << endl; //testando o size
    cout << "posicao 2 do vetor: " << vevet.at(2) << endl; //testando o at

    //modificando a primeira e ultima posicao pelos metodos front e back
    cout << "modificando o vetor" << endl;
    vevet.front() = 9;
    vevet.back() = 12;
    for(int i=0; i<vevet.size();i++)
        cout << vevet.at(i) << " ";
    cout << endl;

    //testando o pop_back
    cout << "removendo o ultimo elemento" << endl;
    vevet.pop_back();
    for(int i=0; i<vevet.size();i++)
        cout << vevet.at(i) << " ";
    cout << endl;
    cout << "size: " << vevet.size() << endl;
    cout << "capacidade: " << vevet.capacity() << endl;

    //testando o reserve
    cout << "modificando a capacidade" << endl;
    vevet.reserve(2);
    for(int i=0; i<vevet.size();i++)
        cout << vevet.at(i) << " ";
    cout << endl;
    cout << "capacidade: " << vevet.capacity() << endl; //testando o capacity
    cout << "size: " << vevet.size() << endl; //testando o size

    //testando o push_back passando da capacidade
    vevet.push_back(12);
    vevet.push_back(56);
    vevet.push_back(87);
    vevet.push_back(14);
    for(int i=0; i<vevet.size();i++)
        cout << vevet.at(i) << " ";
    cout << endl;
    cout << "capacidade: " << vevet.capacity() << endl; //testando o capacity
    cout << "size: " << vevet.size() << endl; //testando o size
    return 0;
}

