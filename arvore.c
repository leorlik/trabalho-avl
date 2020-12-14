#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

tNo* exclui_folha(tNo * no){

	printf("excluindo folha\n");
	free(no);
	no = NULL;
	return no;
}

tNo* exclui_1filho(tNo* pai, tNo* filho){

	tNo* aux;

	printf("excluindo 1 filho\n");
	aux = pai;
	pai = filho;
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
	s->dir = no->dir;
	free(no);
	return s;

}


tNo* inicia_arvore(int chave){
	
	tNo* raiz = (tNo*)malloc(sizeof(tNo));
	raiz->esq = NULL;
	raiz->dir = NULL;
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
	if (no->chave > chave){
		no->esq = insere(no->esq, chave);
		return no;
	}
	no->dir = insere(no->dir, chave);
	return no;
}

tNo* exclui(tNo* no, int chave){

	if (! no)
	       return no;	
	if ( no->chave == chave){
		if (! (no->esq || no->dir))//Testa se o no nao tem filhos
			return exclui_folha(no);
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

tNo* rotleft(tNo* no);

tNo* rotright(tNo* no);

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
