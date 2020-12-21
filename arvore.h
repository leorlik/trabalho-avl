
//Estrutura tNo que representa os nodos, com ponteiro pra filho e pai
typedef struct tNo {
	int chave;
	struct tNo* esq;
	struct tNo* dir;
	struct tNo* pai;
} tNo;


//Funcao utilizada para excluir um nodo folha. Retorna NULL
tNo* exclui_folha(tNo* no);


//Funcao utilizada para excluir um nodo(pai) com apenas um filho(filho). Retorna o filho do nodo excluido 
tNo* exclui_1filho(tNo* pai, tNo* filho);


//Acha a chave minima de uma subarvore e a retorna
tNo* min(tNo* no);


//Acha o sucessor de um nodo e o retorna
tNo* sucessor(tNo* no);


//Funcao utilizada para excluir um nodo com dois filhos
//Retorna o sucessor dele
tNo* exclui_2filhos(tNo* no);


//Funcao para inicializar a AVL. Retorna a raiz, contendo
//chave como sua chave
tNo* inicia_arvore(int chave);


//Insere um nodo com chave "chave" a partir da raiz no
//Retorna a raiz da AVL balanceada
tNo* inserir(tNo* no, int chave);


//Funcao interna utilizada para inserir e balancear
//NAO USE ESSA FUNCAO
//Retorna a raiz da AVL NAO BALANCEADA e em b o pai
//do nodo inserido para balancear
tNo* insere(tNo* no, int chave, tNo** b);


//Exclui o nodo com chave "chave"
//retorna a raiz da AVL balanceada
tNo* excluir(tNo* no, int chave);


//Funcao interna utilizada para excluir e balancear
//NAO USE ESSA FUNCAO
//Retorna a raiz da AVL NAO BALANCEADA e em b 
//O nodo a partir do qual sera feito o balanceamento
tNo* exclui(tNo* no, int chave, tNo** b);


//Funcao descartada do codigo para achar a raiz
//NAO FOI UTILIZADA NO TRABALHO
//Retorna a raiz de uma arvore, percorrendo o pai
tNo* ajusta_raiz(tNo* no);

//Funcao que faz a rotacao para esquerda a partir do nodo no
//Nao tem retorno
void rotleft(tNo* no);


//Funcao que faz a rotacao para esquerda a partir do nodo no
//Nao tem retorno
void rotright(tNo* no);


//Retorna a altura da subarvore cuja raiz eh o nodo no +1
//para facilitar o uso por funcoes
//PARA UTILIZAR ESSA FUNCAO PARA RETORNAR A ALTURA REAL
//SUBTRAIA 1 DO RESULTADO
int altura(tNo* no);


//Imprime uma AVL in order no formato <chave>,<altura do nodo>
void imprime(tNo* raiz);


//Funcao chamada por imprime
//Com o argumento h sendo a altura da raiz(0)
void inorder(tNo* no, int h);


//Balanceia uma subarvore com raiz no assumindo
//Que as subarvores possiveis a partir da raiz
//estao balanceadas
//Chamar ela na raiz pode nao balancear sua AVL corretamente
void balanceia(tNo* no);
