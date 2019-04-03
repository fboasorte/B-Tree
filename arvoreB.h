#ifndef ARVOVEB_H
#define ARVOREB_H

#include <iostream>

using namespace std;

template <class TIPO>
class arvoreB;

template <class TIPO>
class Nodo {
    friend class arvoreB<TIPO>;
private:
    int quant_chaves;
    TIPO *chaves;
    Nodo<TIPO> *apontadores;
public:
    Nodo(int grau_max);
    ~Nodo();
    bool eh_folha();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_max){
    this -> quant_chaves = 0;
    //this -> apontadores = new Nodo<TIPO>[grau_max+1];
    this -> chaves = new TIPO[grau_max];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo() {
    delete [] this -> chaves;
    delete [] this -> apontadores;
}

template <class TIPO>
bool Nodo<TIPO>::eh_folha() {
    return (this -> apontadores[0] == NULL);
}

template <class TIPO>
class arvoreB {
private:
    int t, grau_max;
    Nodo<TIPO> *raiz = new Nodo<TIPO>(grau_max);
public:
    arvoreB(int t);
    ~arvoreB();
    Nodo<TIPO>* Busca(Nodo<TIPO> *no,TIPO ch);
    void Insere(TIPO valor);
    void Insere(Nodo<TIPO> *ap,TIPO valor);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t) {
    this -> raiz = NULL;
    this -> t = t;
    this -> grau_max = 2 * t;//deixa 2t para poder inserir e depois partir no caso de superlotamento
}

template <class TIPO>
arvoreB<TIPO>::~arvoreB() {

}

template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor){
    Nodo<TIPO> *no = Busca(raiz,valor);
    Insere(no,valor);
}

template <class TIPO>
void arvoreB<TIPO>::Insere(Nodo<TIPO> *ap,TIPO valor) {
    int i;
    Nodo<TIPO>* novoNo = (Nodo<TIPO>*)malloc(sizeof(Nodo<TIPO>));
    novoNo -> chaves = (int*)malloc(sizeof(int)*4);

    if(this -> raiz == NULL) {
        novoNo -> quant_chaves = 1;
        novoNo -> chaves[0] = valor;
        cout<<"Inseriu o valor "<<valor<<endl;
    }else{

    }
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO ch) {
    int i;
    if(no == NULL){
        cout << "Não tem esse registro na árvore!!!";
        return NULL;
    }else{
        for(i = 0;i < no->quant_chaves;i++){
            if(ch < no->chaves[i]){
                if(no->apontadores[i] != NULL)
                    Busca(no->apontadores[i],ch);
                else
                    return no;
            }else if(ch == no->chaves[i])
                return no;
        }
        if(no->apontadores[i] != NULL)
            Busca(no->apontadores[i],ch);
        else
            return no;
    }
}

#endif //ARVOREB_H
