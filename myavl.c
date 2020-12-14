#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(){

	tNo* raiz;
	char input = 'r';
	int key;

	scanf("%c",&input);
	printf("primeiro input: %c\n", input);
	scanf("%d",&key);
	printf("primeira chave: %d\n", key);


	if (input != 'i'){
		printf("A primeira operacao deve ser uma insercao\n");
			return 1;
	}

	raiz = inicia_arvore(key);

	getchar();
	scanf("%c", &input);
	printf("segundo input:%c\n", input);
	//getchar();

	while(input == 'r' || input == 'i'){
		scanf("%d", &key);
		printf("chave atual: %d\n", key);
		if (input == 'r')
			raiz = exclui(raiz, key);
		raiz = insere(raiz, key);
		getchar();
		scanf("%c", &input);
		printf("input atual:%c\n", input);
	}

	imprime(raiz);

	return 0;
}
