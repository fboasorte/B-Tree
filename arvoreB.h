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
        Nodo(int grau_maximo);
        ~Nodo();
        bool Eh_folha();
        TIPO Get_Chave(int i);
        int Get_Quant_Chave();
};

//contrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::Nodo(int grau_maximo){ 
    this -> folha = folha;
    this -> quant_chaves = 0;
    this -> apontadores = new Nodo*[grau_maximo + 1];
    this -> chaves = new TIPO[grau_maximo];
}

//destrutora da classe Nodo
template <class TIPO>
Nodo<TIPO>::~Nodo(){
    delete [] this -> chaves;
    delete [] this -> apontadores;
}

template <class TIPO>
int Nodo<TIPO>::Get_Quant_Chave(){
    return this -> quant_chaves;
}

template <class TIPO>
TIPO Nodo<TIPO>::Get_Chave(int i){
    return chaves[i];
}

template <class TIPO>
bool Nodo<TIPO>::Eh_folha(){
    return(this -> apontadores[0] == NULL);
}

template <class TIPO>
class arvoreB{
    private:
        int t, grau_maximo;
        Nodo<TIPO> *raiz;
    public:
        arvoreB(int t);
        ~arvoreB();
        Nodo<TIPO>* Busca(TIPO valor);
        Nodo<TIPO>* Busca(Nodo<TIPO> *no, TIPO valor);
        void Insere(TIPO valor);
        void Insere_Raiz_Nula(TIPO valor);
        void Imprime();
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

//Inicio dos Metodos de Insercao
template <class TIPO>
void arvoreB<TIPO>::Insere(TIPO valor){
    if(this -> raiz == NULL){//Caso a arvore nao tiver nenhum valor
        Insere_Raiz_Nula(valor);
    }
    else{//Caso ja exista algo na arvore
    }
}

template <class TIPO>
void arvoreB<TIPO>::Insere_Raiz_Nula(TIPO valor){
    Nodo<TIPO>* NovaRaiz = new Nodo<TIPO>(grau_maximo);
    this -> raiz = NovaRaiz;
    this -> raiz -> quant_chaves = 1;
    this -> raiz -> chaves[0] = valor;
    for(int i = 0; i < grau_maximo; i++)
        this -> raiz -> apontadores[i] = NULL;
    cout<<"Valor "<<valor<<" inserido com sucesso"<<endl;
}
//Fim dos metodos de Insercao

//Inicio dos Metodos de Busca
template<class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(TIPO valor){
    Busca(this -> raiz, valor);
}

template <class TIPO>
Nodo<TIPO>* arvoreB<TIPO>::Busca(Nodo<TIPO> *no,TIPO valor) {
    int i = 0;
    if(no == NULL){
        cout << "Não tem esse registro na árvore!!!";
        return no;
    }
    else{
        while(i < no->quant_chaves && valor > no->chaves[i])
            i++;
            if(valor == no->chaves[i])
                return no;
            if(valor < no->chaves[i])
                Busca(no->apontadores[i-1],valor);
            else
                Busca(no->apontadores[i],valor);
    }
}
//Fim dos metodos de busca

//Metodo de Impressao
template <class TIPO>
void arvoreB<TIPO>::Imprime(){

}

#endif //ARVOREB_H
