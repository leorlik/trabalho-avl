#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>


tNo* exclui_folha(tNo * no){

	
	free(no);
	return NULL;
}

tNo* exclui_1filho(tNo* pai, tNo* filho){

	tNo* aux;

	aux = pai;
	pai = filho;//Ponteiro para o nodo excluido troca
	pai->pai = aux->pai;//O unico ajuste necessario
	//eh acertar o ponteiro pai
	free(aux);
	return pai;
}

tNo* min(tNo* no){
	
	if( ! (no->esq))//Testa se o filho da esquerda eh nulo
		return no;
	return min(no->esq);
}

tNo* sucessor(tNo* no){
	
	//Chama min no filho da direita para obter o sucessor
	return min(no->dir);
}

tNo* exclui_2filhos(tNo* no){

	
	tNo* s = sucessor(no);
	tNo* aux = s->dir;

	s->esq = no->esq;

	//Cuida caso o filho da direita do nodo excluido nao tiver filhos
	if (no->dir != s)
		s->dir = no->dir;


	//Talvez seja redundante, ajusta o filho
	if (s->pai->dir == s)
		s->pai->dir = aux;
	else
		s->pai->esq = aux;


	if(aux)//Ajusta o ponteiro pai do filho da direita do sucessor
		aux->pai = s->pai;

	s->pai = no->pai;
	free(no);
	return s;

}


tNo* inicia_arvore(int chave){
	
	tNo* raiz = (tNo*)malloc(sizeof(tNo));
	raiz->esq = NULL;
	raiz->dir = NULL;
	raiz->pai = NULL;
	raiz->chave = chave;
	return raiz;
}

tNo* inserir(tNo* no, int chave){

	tNo* b = NULL;

	no = insere(no, chave, &b);//Chama a funcao que insere

	//Enquanto b nao eh nulo, balanceia-o e entao sobe para seu pai
	while(b){
		balanceia(b);
		no = b;
		b = b->pai;
	}

	return no;//No sempre eh a raiz
}

tNo* insere(tNo* no, int chave, tNo** b){

	//Caso ache o no vago
	if( ! no){
		tNo* novo = (tNo*)malloc(sizeof(tNo));
		novo->chave = chave;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}


	*b = no;//b sempre apontara para o pai do nodo inserido
	if (no->chave > chave)
		no->esq = insere(no->esq, chave, b);
	else
		no->dir = insere(no->dir, chave, b);

	//Ajusta o ponteiro pai
	//Implementacao nao-otimizada
	if (no->esq)
		no->esq->pai = no;
	if (no->dir)
		no->dir->pai = no;


	return no;
}

tNo* exclui(tNo* no, int chave, tNo** b){

	//Caso nao haver a chave na arvore
	if (! no)
	       return no;	

	//Caso ache o nodo
	if ( no->chave == chave){


		if (! (no->esq || no->dir))//Testa se o no nao tem filhos
			return exclui_folha(no);



		if (no->esq && no->dir){//Caso 2 filhos
			//b eh o sucessor de no
			(*b) = exclui_2filhos(no);
			return (*b);
		}

		if (no->esq)//Apenas filho da esquerda
			return exclui_1filho(no, no->esq);



		return exclui_1filho(no, no->dir);//Apenas filho da direita
	}
	*b = no;//b eh o pai do nodo excluido, exceto no caso
	//2 filhos
	



	//Caso ande pra esquerda
	if (no->chave > chave){
		no->esq = exclui(no->esq, chave, b);
		return no;
	}

	//Caso ande pra direita
	no->dir = exclui(no->dir, chave, b);
	return no;
}

tNo* excluir(tNo* no, int chave){

	tNo* b = NULL;
	
	no = exclui(no, chave, &b);

	//Rotina para balancear a arvore
	while (b){
		balanceia(b);
		no = b;
		b = b->pai;
	}

	return no;//No eh sempre a raiz
}

tNo* ajusta_raiz(tNo* no){

	tNo* raiz = no;

	while( raiz->pai)
		raiz = raiz->pai;

	return raiz;
}

void rotleft(tNo* no){

	tNo* aux;
	tNo* pai;
	
	pai = no->pai;

	aux = no->dir;
	no->dir = aux->esq;
	aux->pai = no->pai;
	no->pai = aux;


	if (aux->esq)
		aux->esq->pai = no;

	aux->esq = no;

	//Ajusta o pai da subarvore rotada, caso nao seja nulo
	if (pai){
		if (pai->esq == no)
			pai->esq = aux;
		else
			pai->dir = aux;
	}

}

void rotright(tNo* no){

	tNo* aux;
	tNo* pai;

	pai = no->pai;

	aux = no->esq;
	no->esq = aux->dir;
	aux->pai = no->pai;
	no->pai = aux;


	if (aux->dir)
		aux->dir->pai = no;
	aux->dir = no;


	//Ajusta o pai da subarvore rotada, caso nao seja nulo
	if (pai){
		if (pai->esq == no)
			pai->esq = aux;
		else
			pai->dir = aux;
	}
}

void imprime(tNo* raiz){

	inorder(raiz, 0);

}

void inorder(tNo* no, int h){

	if (no){
		inorder(no->esq, h+1);
		printf("%d,%d\n", no->chave, h);
		inorder(no->dir, h+1);
	}
}

int altura(tNo* no){

	if (no){
		int he, hd;

		he = 1 + altura(no->esq);
		hd = 1 + altura(no->dir);
		if (he > hd)
			return he;
		return hd;

	}
	return 0;//Para retornar a altura real, aqui deve ser -1, porem para facilidade de codigo
}

void balanceia(tNo* no){

	int he, hd, diff;

	he = altura(no->esq);
	hd = altura(no->dir);

	diff = he - hd;

	//Subarvores da esquerda desbalanceadas
	if (diff > 2){
		balanceia(no->esq);
		balanceia(no);

	}

	//Arvore desbalanceada pra esquerda
	else if (diff == 2){
		rotright(no);

		//Caso de rotacao dupla
		if (altura(no->pai->esq) - altura(no->pai->dir) == -2){
			rotright(no);
			balanceia(no->pai);
		}
	}

	//Arvore desbalanceada pra direita
	else if (diff == -2){
		rotleft(no);

		//Caso de rotacao dupla
		if (altura(no->pai->esq) - altura(no->pai->dir) == 2){
			rotleft(no);
			balanceia(no->pai);
		}
	}

	//Subarvores da direita desbalanceadas
	else if (diff < -2){
		balanceia(no->dir);
		balanceia(no);
	}
}


