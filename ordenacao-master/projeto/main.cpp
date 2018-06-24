#include <iostream>
#include <ctime>
#include <cstdlib> //rand
#include "libs/ed_sort.h"

using namespace std;

//cores rgbcymkw
//red, green, blue, cyan, yellow, magenta, black, white

//swap_sort(faz diversas trocas no laço de repeticao)
void swap_sort(vector<int>& vet){
    for(int i = 0; i < (int) vet.size() - 1; i++){
        view_set_faixa(i,vet.size()-1);
        for(int j = i + 1; j < (int) vet.size(); j++){
            view_show(vet, {i, j}, "gy");
            if(vet[j] < vet[i]){
                std::swap(vet[i], vet[j]);
                view_show(vet, {i, j}, "yg");
            }
        }
    }
}

//minimum_sort
//procura o menor dps troca com a primeira posicao
void minimum_sort(vector<int>& vet){
    for(int i = 0; i < (int) vet.size() - 1; i++){
        view_set_faixa(i,vet.size()-1);
        int imenor = i;
        for(int j = i + 1; j < (int) vet.size(); j++){
            view_show(vet, {i, j, imenor}, "gyr");
            if(vet[j] < vet[imenor]){
                imenor = j;
                view_show(vet, {i, j, imenor}, "gyr");
            }
        }
    std::swap(vet[i], vet[imenor]);
    }
}

//reverse_minimum_sort
//ordena do final para o comeco(maior para o menor)
void reverse_minimum_sort(vector<int>& vet){
    int ultimo = vet.size() -1;
    for(int i = 0; i <= ultimo; ultimo--){
        view_set_faixa(i,ultimo);
        int imaior = ultimo;
        for(int j = 0; j < ultimo; j++){
            view_show(vet, {i, j,imaior, ultimo}, "gyrm");
            if(vet[j] > vet[imaior]){
                imaior = j;
             view_show(vet, {i, j,imaior, ultimo}, "gyrm");
            }
        }
        std::swap(vet[imaior], vet[ultimo]);
    }
}

//palma sort
//menor pro comeco e maior pro final
void palma_sort(vector<int>& vet){
    int ultimo = vet.size() -1;
    for(int i = 0; i <= ultimo; i++, ultimo--){
        view_set_faixa(i,ultimo);
        int imenor = i;
        int imaior = i;
        for(int j = i+1; j <= ultimo; j++){
            view_show(vet, {j,imenor,imaior}, "yrm");
            if(vet[j] < vet[imenor]){
                imenor = j;
            }
            else if(vet[j] > vet[imaior]){
                imaior = j;
            }
        }
        std::swap(vet[i],vet[imenor]);
        if(vet[i] == vet[imaior])
            std::swap(vet[imenor],vet[ultimo]);
        else
            std::swap(vet[imaior], vet[ultimo]);
    }
}

//bubble_sort (o menor empurra o maior pro final)
void bubble_sort(vector<int>& vet){
    int ultimo = vet.size()-1;
    for(int i = ultimo; i > 0 ; i--){
        for(int j = 0; j < i; j++){
            view_set_faixa(i,j);
            view_show(vet, {i, j,j+1}, "gyy");
            if(vet[j] > vet[j+1]){
                std::swap(vet[j], vet[j+1]);
                view_show(vet, {i, j, j+1}, "gyy");
            }
        }
    }
}

//insertion_sort
void insertion_sort(vector<int>& vet){
    for(int i=1; i < (int) vet.size(); i++){
        view_set_faixa(0,i);
        for(int j=i; j > 0; j--){
            view_show(vet, {i, j,j-1}, "gyy");
            if(vet[j] < vet[j-1]){
                std::swap(vet[j], vet[j-1]);
                view_show(vet, {i, j, j-1}, "gyy");
            }
            else{
                break;
                view_show(vet, {i, j, j-1}, "gyy");
            }
        }
    }
}

//quick_sort(ordenacao com recursao)

//1 2 3 6 7 9
//c=5;  f=5
void quick_sort(vector<int>& vet, int C, int F){
    if(C >= F) // 5 >= 5 ?
        return;
    int escolhido = vet[C]; //vet[4] = 7
    int i = C; // i=4
    int j = F; // j=5
    while(i <= j){ // 5 <= 3?
        while(vet[i] < escolhido){ //(vet[4]=7) < (vet[4]=7)?
            i++; // i=2
            view_show(vet, {C,F,i, j}, "rgby");
        }
        while(vet[j] > escolhido){ //(vet[4]=7) > (vet[4]=7)?
            j--; //j=4
            view_show(vet, {C,F,i, j}, "rgby");
        }
        if(i <= j){ //4 <= 4 ?
            std::swap(vet[i], vet[j]); //troca vet[4] com vet[4]; 1 2 3 6 7 9
            i++; // i=5
            j--; // j=3
            view_show(vet, {C,F,i, j}, "rgyb");
        }
    }
    quick_sort(vet, C, j); //vet, 4, 3
    quick_sort(vet, i, F); //vet, 5, 5
}

//merge
void merge(vector<int>& vet, int a, int b, int c){
    int i = a;
    int j = b;
    vector<int> vaux;
    vaux.reserve(c - a);
    while((i < b) && (j < c)){ //comparar particoes
        if(vet[i] < vet[j])
            vaux.push_back(vet[i++]);
        else
            vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(i < b){
        vaux.push_back(vet[i++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    while(j < c){
        vaux.push_back(vet[j++]);
        view_show(vet, {a, b, c, i, j}, "rgbyc");
    }
    for(int i = 0; i < (int) vaux.size(); i++){
        vet[a + i] = vaux[i];
        view_show(vet, {a + i}, "r");
    }
}

//mergesort
void mergesort(vector<int>& vet, int a, int c){
    if(c == a + 1)
        return;
    int b = (a + c)/2;
    mergesort(vet, a, b);
    mergesort(vet, b, c);
    merge(vet, a, b, c);
}

void test_sort(vector<int>& vet){
    for(int i=0; i< (int) vet.size()-1;i++){
        if(vet[i] <= vet[i+1]){
            view_show(vet,{i,i+1},"gg");
        }
        else{
            view_show(vet,{i,i+1},"rr");
            view_lock();
        }
    }
}

int main(){
    srand(time(NULL));
    const int qtd = 20;//70;
    vector<int> vet(qtd, 0);

    int min = 10;
    int max = 400;

    for(int i = 0; i < qtd; i++)
        vet[i] = (rand() % (max - min + 1) + min);

    view_set_bar();
    view_set_faixa(0, qtd - 1);

    //swap_sort(vet); //ok
    //minimum_sort(vet); //ok
    //reverse_minimum_sort(vet); //ok
    //palma_sort(vet); //ok
    //bubble_sort(vet); //ok
    //insertion_sort(vet); //ok
    quick_sort(vet,0,vet.size()-1); //ok
    //mergesort(vet, 0, vet.size()); //ok
    test_sort(vet);
    view_lock();
    return 0;
}
