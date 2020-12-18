#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(){

	tNo* raiz;
	char input = 'r';
	int key;

	scanf("%c",&input);
	scanf("%d",&key);


	if (input != 'i'){
		printf("A primeira operacao deve ser uma insercao\n");
			return 1;
	}

	raiz = inicia_arvore(key);

	getchar();
	scanf("%c", &input);

	while(input == 'r' || input == 'i'){
		scanf("%d", &key);
		if (input == 'r')
			raiz = excluir(raiz, key);
		else
			raiz = inserir(raiz, key);
		getchar();
		scanf("%c", &input);
	}

	imprime(raiz);

	return 0;
}
