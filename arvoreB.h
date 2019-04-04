#ifndef ARVOVEB_H
#define ARVOREB_H
#include <iostream>
using namespace std;

template <class TIPO>
class arvoreB;

template <class TIPO>
class Nodo{
    friend class arvoreB<TIPO>;
	private:
        int quant_chaves;
        TIPO *chaves;
        Nodo **apontadores;
        bool folha;
	public:
        Nodo(int grau_maximo, bool folha);
        ~Nodo();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_maximo, bool folha){ 
    this -> folha = folha;
    this -> quant_chaves = 0;
    this -> apontadores = new Nodo*[grau_maximo];
    this -> chaves = new TIPO[grau_maximo];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo(){
    delete [] this -> chaves;
    delete [] this -> apontadores;
}

template <class TIPO>
class arvoreB{
    private:
        int t, grau_maximo;
        Nodo<TIPO> *raiz;
    public:
        arvoreB(int t);
        ~arvoreB();
        Nodo<TIPO>* busca(Nodo<TIPO> *no,TIPO ch);
        void insere(TIPO valor);
};

template <class TIPO>
arvoreB<TIPO>::arvoreB(int t){
   this -> raiz = NULL;
   this -> t = t;
   this -> grau_maximo = 2 * t;//deixa 2t para poder inserir e depois partir no caso de superlotamento
}

template <class TIPO>
arvoreB<TIPO>::~arvoreB(){
}

template <class TIPO>
void arvoreB<TIPO>::insere(TIPO valor){
    if(this -> raiz == NULL){//Caso a arvore nao tiver nenhum valor
        Nodo<TIPO>* NovaRaiz = new Nodo<TIPO>(grau_maximo, true);
        this -> raiz = NovaRaiz;
        this -> raiz -> quant_chaves = 1;
        this -> raiz -> chaves[0] = valor;
        cout<<"Valor "<<valor<<" inserido com sucesso"<<endl;
    }
    else{//Caso ja exista algo na arvore
    }
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::busca(Nodo<TIPO> *no,TIPO chave) {
    int i = 0;
    if(no == NULL){
        cout << "Não tem esse registro na árvore!!!";
        return no;
    }
    else{
        while(i < no->quant_chaves && chave > no->chaves[i])
            i++;
            if(chave == no->chaves[i])
                return no;
            if(chave < no->chaves[i])
                Busca(no->apontadores[i-1],chave);
            else
                Busca(no->apontadores[i],chave);
    }
}

#endif //ARVOREB_H
