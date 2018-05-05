#include <iostream>

using namespace std;

//estrutura do no
struct Node{
    int value;//valor do no
    Node* next;//ponteiro para proximo no

    //construtor
    Node(int value = 0, Node * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

//estrutura da lista
struct SList{
    //ponteiro para o primeiro no
    Node* cabeca;

    //construtor
    SList(){
        this->cabeca = nullptr;
    }

    //destrutor
    ~SList(){
        cabeca = _deletarTudo(cabeca);
    }

    //deletar tudo
private:
    Node* _deletarTudo(Node * node){
        if(node == nullptr)
            return nullptr;
        _deletarTudo(node->next);
        delete node;
        return nullptr;
    }
public:
    void deletar(){
        cabeca = _deletarTudo(cabeca);
    }

    //inserir no inicio (iterativo)
    void push_front(int value){
        this->cabeca = new Node(value, this->cabeca);
    }

    //remover da frente (iterativo)
    void pop_front(){
        if(cabeca == nullptr)
            return;
        Node * aux = cabeca;
        cabeca = cabeca->next;
        delete aux;
    }

    //adicionar no final (iterativo)
    void push_back(int value){
        if(cabeca == nullptr){
            cabeca = new Node(value);
            return;
        }
        auto node = cabeca;
        while(node->next != nullptr)
            node = node->next;
        node->next = new Node(value);
    }

    //adicionar no final (recursivo)
private:
    Node* _rpush_back(Node* node, int value){
        if(node->next == nullptr){
            node->next = new Node(value);
            return node->next;
        }
        node = _rpush_back(node->next, value);
    }
public:
    void rpush_back(int value){
        _rpush_back(cabeca,value);
    }

    //remover do final (iterativo)
    void pop_back(){
        if(cabeca == nullptr)
            return;
        if(cabeca->next == nullptr){
            delete cabeca;
            cabeca = nullptr;
            return;
        }
        auto node = cabeca;
        while(node->next->next != nullptr)
            node = node->next;
        delete node->next;
        node->next = nullptr;
    }

    //remover do final (recursivo)
private:
    Node * _rpop_back(Node * node){
        if(node->next == nullptr){
            delete node;
            return nullptr;
        }
        node->next = _rpop_back(node->next);
    }
public:
    void rpop_back(){
        this->cabeca = _rpop_back(cabeca);
    }

    //mostrar (iterativo)
    void ishow(){
        auto node = cabeca;
        while(node != nullptr){
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }

    //mostrar (recursivo)
private:
    void _rshow(Node * node){
        if(node == nullptr)
            return;
        cout << node->value << " ";
        _rshow(node->next);
        //mostra de tras para frente
        //_rshow(node->next);
        //cout << node->value << " ";
    }
public:
    void rshow(){
        _rshow(cabeca);
        cout << endl;
    }

    //remover por valor (recursivo)
private:
    Node * _remove(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value){
            auto aux = node->next;
            delete node;
            return aux;
        }
        node->next = _remove(node->next, value);
    }
public:
    void rremove(int value){
        cabeca = _remove(cabeca, value);
    }

    //remover pelo valor (iterativo)
    void iremove(int value){
        if(cabeca == nullptr)
            return;
        if(cabeca->value == value && cabeca->next == nullptr){
            delete cabeca;
            cabeca = nullptr;
            return;
        }
        if(cabeca->value == value && cabeca->next != nullptr){
            auto aux = cabeca;
            cabeca = cabeca->next;
            delete aux;
        }
        auto node = cabeca;
        while(node->next != nullptr){
            if(node->next->value == value){
                auto aux = node->next;
                node->next = node->next->next;
                delete aux;
                return;
            }
            node = node->next;
        }
        return;
    }

    //inserir em ordem (iterativo)
    void inserir_ordenado(int value){
        auto node = cabeca;
        if(cabeca == nullptr || cabeca->value > value){
            this->cabeca = new Node(value, cabeca);
            return;
        }
        while(node->next != nullptr && node->next->value < value){
            node = node->next;
        }
        node->next = new Node(value, node->next);
    }

    //inserir em ordem (recursivo)
private:
    Node * _rinserir_ordenado(Node * node, int value){
        if(cabeca == nullptr || cabeca->value > value){
            this->cabeca = new Node(value, cabeca);
            return node;
        }
        if(node->next->value > value){
            node->next = new Node(value,node->next);
            return node;
        }
        node = _rinserir_ordenado(node->next,value);
    }
public:
    void rinserir_ordenado(int value){
        _rinserir_ordenado(cabeca,value);
    }

    //size (iterativo)
    void size(){
        int cont = 0;
        auto node = cabeca;
        while(node != nullptr){
            cont ++;
            node = node->next;
        }
        cout << "total de no: " << cont << endl;
        return;
    }

    //size (recursao)
private:
    int _rsize(Node* node ){
        if(node-> next == nullptr)
            return 1;
        return 1 + _rsize(node->next);
    }
public:
    void rsize(){
        cout << "total de no: " << _rsize(cabeca) << endl;
    }

    //2
    //1 2 3 4
    //procura o valor, remove do rabo em diante
private:
    Node* _cortarRabo(Node* node, int value){
        if(node == nullptr)
            return nullptr;
        node->next = _cortarRabo(node->next, value);
        if(node->next == nullptr){
            if(node->value != value){
                delete node;
                return nullptr;
            }
            else{
                return node;
            }
        }
        return node;
    }
public:
    void rcortaRabo(int value){
        _cortarRabo(cabeca, value);
    }

    //3
    //1 2 3 4 5
    //arranca venta
private:
    Node* _arrancaVenta(Node* node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value)
            return node;
        auto aux = node;
        delete node;
        node = nullptr;
        aux = _arrancaVenta(aux->next, value);
        return aux;
    }
public:
    void arrancaVenta(int value){
        cabeca = _arrancaVenta(cabeca, value);
    }

    //somar (recursivo)
private:
    int _somar(Node* node){
        if(node->next == nullptr)
            return node->value;
        return node->value + _somar(node->next);
    }
public:
    void somar(){
       cout << "a soma eh: " << _somar(cabeca) << endl;
    }

    //menor valor (recursivo)
private:
    int rmin(Node * node){
        if(node->next == nullptr)
            return node->value;
        return std::min(node->value, rmin(node->next));
    }
public:
    void min(){
        cout << "o valor minimo eh: " << rmin(cabeca) << endl;
    }
};


int main()
{
    SList lista;

    //adicionando (recursao e iterativo)
    lista.push_front(23);
    lista.push_back(13);
    lista.rpush_back(12);
    lista.push_back(5);
    lista.push_front(2);
    lista.rpush_back(11);
    lista.push_back(7);
    lista.push_front(20);
    lista.rpush_back(13);

    //mostrando (recursivo)
    cout << "mostrando (recursivo)" << endl;
    lista.rshow();

    // size (iterativo)
    cout << "size (iterativo)" << endl;
    lista.size();

    //removendo por numero (iterativo e recursivo)
    cout << "removendo o 12 e o 23 (iterativo e recursivo) " << endl;
    lista.iremove(12);
    lista.rremove(23);

    //mostrando (iterativo)
    cout << "mostrando (iterativo)" << endl;
    lista.ishow();

    // size (recursivo)
    cout << "size (recursivo)" << endl;
    lista.rsize();

    //removendo inicio/fim (iterativo e recursivo)
    cout << "removendo 2x do final (iterativo e recursivo)" << endl;
    lista.pop_back();
    lista.rpop_back();
    lista.rshow();
    cout << "removendo do inicio" << endl;
    lista.pop_front();
    lista.ishow();

    //adcionando ordenado (iterativo e recursivo)
    cout << "inserindo em ordem o 4 e o 10 (iterativo e recursivo)" << endl;
    lista.inserir_ordenado(4);
    lista.rinserir_ordenado(10);
    lista.rshow();

    //soma e minimo
    lista.somar();
    lista.min();

    //cortar rabo
    cout << "cortando rabo a partir de um valor" << endl;
    lista.rcortaRabo(13);
    lista.rshow();

    //arrancar venta
    cout << "cortando venta a partir de um valor" << endl;
    lista.arrancaVenta(10);
    lista.ishow();

    //removendo tudo
    cout << "deletar toda a lista" << endl;
    lista.deletar();
    lista.rshow();
    return 0;
}
