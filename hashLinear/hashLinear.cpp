#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

enum Marcador {VAZIO = 0, CHEIO = 1, DELETADO = 2};

//estrutura do elemento
struct Elem{
	int key;
	string valor;
	
	//construtor
	Elem(int key = 0, string valor = ""){	
		this->key = key;
		this->valor = valor;
	}

	//comparando dois elementos
	bool operator == (Elem outro){
		return this->key == outro.key;
	}

	//imprimir um elemento
	friend ostream& operator << (ostream& os, Elem elem){
		os << elem.key << "," << elem.valor;
		return os;
	}
};

//estrutura do hashLinear
struct hashLinear{
	pair<Elem, Marcador> *vet;
	int capacidade;
	int qtd =0;

	//construtor
	hashLinear(int capacidade){
		vet =  new pair<Elem, Marcador> [capacidade];
		this->capacidade = capacidade;
		this->qtd;		
	}

	//encontrando posicao de um elemento
	int find(Elem elem){
		int base = elem.key % this->capacidade;
		int pos = base;
		int i = 0;
		while(!(vet[pos].second == VAZIO) && !(vet[pos].first == elem)){
			i++;
			pos = (base + i*i) % capacidade;
		}
		if(vet[pos].second == VAZIO)
			return -1;
		return pos;
	}

	//inserir
	bool insert(Elem elem){
		int it = find(elem);
		if(it != -1)
			return false;
		int pos = elem.key % this->capacidade;
		while(vet[pos].second != VAZIO)
			pos = (pos + 1) % this->capacidade;
		this->vet[pos].first = elem;
		this->vet[pos].second = CHEIO;
		this->qtd ++;
		return true;
	}

	//novo tamanho
	void resize(int novaCap){
		pair<Elem, Marcador> *vetAntigo = vet;
		vet = new pair<Elem, Marcador> [novaCap];
		for(int i = 0; i < this->qtd; i++){
			vet[i].second = VAZIO;
		}
		for(int i = 0; i < this->qtd; i++)
			insert(vetAntigo[i].first);
		delete vetAntigo;
	}

	//deletar com marcacao
	bool remove(Elem elem){
		int pos = find(elem);
		if(pos == -1)
			return false;
		this->vet[pos].second = DELETADO;
		this->qtd--;
	}

	//deletar sem marcacao
	bool sm_remove(Elem elem){
		int pos = find(elem);
		if(pos == -1)
			return false;
		vet[pos].second = VAZIO;
		this-> qtd--;
		pos = (pos+1) % this->capacidade;
		while(vet[pos].second != VAZIO){
			vet[pos].second = VAZIO;	
			insert(vet[pos].first);
			pos = (pos +1) % this->capacidade;	
		}
		return true;
	}
	
	//capacidade
	int capacity(){
	    return this->capacidade;   
	}
	
	//size
	int size(){
	    return qtd;
	}
};

int main(){
	Elem elem1 = Elem(12, "ok");
	Elem elem2 = Elem(54, "ok");
	Elem elem3 = Elem(7, "ok");
	Elem elem4 = Elem(21, "ok");
	
	
	hashLinear vetHash = hashLinear(5);
	cout << "capacidade: " << vetHash.capacity() << endl;
	
	cout << "add elementos:" << endl;
	
	if(vetHash.insert(elem1) && vetHash.insert(elem2) && vetHash.insert(elem3)){
	    cout << "ok, adicionado!!" << endl;
	}
	cout << "total de elementos: " << vetHash.size() << endl;
	
	cout << "removendo elemento que nao existe" << endl;
	if(vetHash.remove(elem4))
	    cout << "ok, temovido" << endl;
	else
	    cout << "elemento nao existe" << endl;
	
	cout << "removendo sem marcacao" << endl;
	if(vetHash.sm_remove(elem2))
	    cout << "ok, removido" << endl;
	else
	    cout << "erro!!" << endl;
	    
	cout << "capacidade: " << vetHash.capacity() << endl;
    	cout << "total de elementos: " << vetHash.size() << endl;
    
    	cout << "aumentando o tamanho para 6:" << endl; 
	vetHash.resize(6);
	cout << "capacidade: " << vetHash.capacity() << endl;
   	cout << "total de elementos: " << vetHash.size() << endl;

	return 0;
}
