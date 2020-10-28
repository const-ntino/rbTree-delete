#include <bits/stdc++.h>
#define BLACK 1
#define RED 2

using namespace std;


/*
* Estrutura que contém uma árvore.
* @param_value contém o dado que vai ser armazenado naquele nó.
* @param_color contém a cor do nó, que pode ser vermelho ou preto.
* @param_left um ponteiro pro filho esquerdo desse nó.
* @param_right um ponteiro pro filho direito desse nó.
* @param_p um ponteiro pro pai desse nó.
*/
struct node{
		int value, color;
		struct node *left, *right, *p;
};

/*
* Classe que contém uma árvore.
* @param_root contém um ponteiro pra raiz da árvore.
* @param_T_NIL contém um nó "sentinela", usado para representar um nó nulo, seu valor é predefinido durante a construção.
* @function_TREE() Construtor da árvore, aloca @param_T_NIL e o coloca como raiz da árvore.
* @function_~TREE() Desaloca toda a árvore.
* @function_insere() Recebe como parâmetro o número a ser inserido. Ao final da função, á arvore terá esse nó devidamente inserido.
* @function_insertFix_RB() Corrige a árvore, rotacionando ou pintando nós até as propriedades da RB estarem restauradas.
* @function_deletar() Deleta o nó que é passado por paramêtro da árvore.
* @function_deleteFix_RB() Restaura as propriedades da RB que podem ter sido violadas após uma remoção.
* @function_rotacionar_esquerda() Faz uma rotação em torno desse nó para a esquerda.
* @function_rotacionar_direita() Faz uma rotação em torno desse nó para a direita.

*/ 

class Tree{
private:
	node *root;
	node *T_NIL;
public:
	Tree();
	~Tree();
	void insere(int x);
	void insertFix_RB(node *no);
	void deletar(node *z);
	void deleteFix_RB(node *x);
	void rotacionar_esquerda(node *no);
	void rotacionar_direita(node *no);
	void transplant(node *u, node *v);
	node *minimum(node *x);
	node *search(int x);
	void imprimir();

};

void imprime(node *no, node *T_NIL);

void limpar(node *no, node *T_NIL);

node *criar_no(int x,node *T_NIL);