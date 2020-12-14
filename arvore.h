
typedef struct tNo {
	int chave;
	struct tNo* esq;
	struct tNo* dir;
} tNo;

tNo* exclui_folha(tNo* no);

tNo* exclui_1filho(tNo* pai, tNo* filho);

tNo* min(tNo* no);

tNo* sucessor(tNo* no);

tNo* exclui_2filhos(tNo* no);

tNo* inicia_arvore(int chave);

tNo* insere(tNo* no, int chave);

tNo* exclui(tNo* no, int chave);

tNo* rotleft(tNo* no);

tNo* rotright(tNo* no);

void imprime(tNo* raiz);

void inorder(tNo* no, int h);
