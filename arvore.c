#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

tNo* exclui_folha(tNo * no){

	printf("excluindo folha\n");
	
	free(no);
	return NULL;
}

tNo* exclui_1filho(tNo* pai, tNo* filho){

	tNo* aux;

	printf("excluindo 1 filho\n");
	aux = pai;
	pai = filho;
	pai->pai = aux->pai;
	free(aux);
	return pai;
}

tNo* min(tNo* no){
	
	if( ! (no->esq))
		return no;
	return min(no->esq);
}

tNo* sucessor(tNo* no){
	
	return min(no->dir);
}

tNo* exclui_2filhos(tNo* no){

	printf("excluindo 2 filhos\n");
	
	tNo* s = sucessor(no);
	s->esq = no->esq;
	//s->dir = no->dir;
	if (s->pai->dir == s)
		s->pai->dir = NULL;
	else
		s->pai->esq = NULL;
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

tNo* insere(tNo* no, int chave){

	if( ! no){
		tNo* novo = (tNo*)malloc(sizeof(tNo));
		novo->chave = chave;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	if (no->chave > chave)
		no->esq = insere(no->esq, chave);
	else
		no->dir = insere(no->dir, chave);
	if (no->esq)
		no->esq->pai = no;
	if (no->dir)
		no->dir->pai = no;
	return no;
}

tNo* exclui(tNo* no, int chave){

	if (! no)
	       return no;	
	if ( no->chave == chave){
		if (! (no->esq || no->dir)){//Testa se o no nao tem filhos
			return exclui_folha(no);
		}
		if (no->esq && no->dir)//Caso 2 filhos
			return exclui_2filhos(no);
		if (no->esq)//Apenas filho da esquerda
			return exclui_1filho(no, no->esq);
		return exclui_1filho(no, no->dir);//Apenas filho da direita
	}
	if (no->chave > chave){
		no->esq = exclui(no->esq, chave);
		return no;
	}
	no->dir = exclui(no->dir, chave);
	return no;
}

tNo* rotleft(tNo* no){

	tNo* aux;
	
	aux = no->dir;
	no->dir = aux->esq;
	aux->pai = no->pai;
	no->pai = aux;
	if (aux->esq != NULL)
		aux->esq->pai = no;
	aux->esq = no;
	return aux;

}

tNo* rotright(tNo* no){

	tNo* aux;

	aux = no->esq;
	no->esq = aux->dir;
	aux->pai = no->pai;
	no->pai = aux;
	if (aux->dir != NULL)
		aux->dir->pai = no;
	aux->dir = no;
	return aux;
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
	return 0;
}
