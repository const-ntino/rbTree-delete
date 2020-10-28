#include "arvore_rb.h"

// Construtor da árvore
Tree::Tree()
{
	// Aloco o nó que irei usar como sentinela.
	this->T_NIL = criar_no(0, this->T_NIL);
	// Pinto ele de preto.
	this->T_NIL->color = BLACK;
	// Faço a raiz apontar pra ele
	this->root = this->T_NIL;
}

Tree::~Tree()
{
	limpar(this->root, this->T_NIL); // Desaloco a árvore da mémoria
	free(this->T_NIL);				 // Limpo o nó sentinela
}

void Tree::insere(int x)
{
	if (this->root == this->T_NIL)
	{										   // Se a raiz for nula
		this->root = criar_no(x, this->T_NIL); // Crio um nó pra raiz, com pai T_NIL.
		this->root->color = BLACK;			   // Pinto a raiz de preto.
		return;
	}
	// Se não for nula, preciso encontrar o lugar certo a ser inserido.
	node *tmp = this->root, *y;
	while (tmp != this->T_NIL)
	{			 // Então percorro em um loop, até encontrar o lugar a ser inserido.
		y = tmp; // Salvo tmp em y, pois ele pode ser o possivel pai do nó que será inserido
		if (tmp->value > x)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	}
	tmp = criar_no(x, T_NIL);       // Crio um novo nó e o aloco em tmp.
	tmp->p = y;				        // O pai do nó inserido será y.
	if (tmp->value < y->value)
		y->left = tmp;              // Se tmp for menor que y, então ele é filho da direita
	else
		y->right = tmp;				// Se não, é filho da esquerda
	tmp->right = tmp->left = T_NIL; // Os filhos de tmp serão a sentinela.
	insertFix_RB(tmp);				// Chamo a função para restaurar as propriedades RB.
}

void Tree::transplant(node *u, node *v)
{ // Função que transforma um nó em outro.
	if (u->p == T_NIL)
		this->root = v; // Se o nó u for a raiz, v vira a raiz
	else if (u == u->p->left)
		u->p->left = v; // Se ele for filho da esquerda, v vira filho da esquerda
	else
		u->p->right = v; // Se não, ele vira filho da direita
	v->p = u->p;		 // O pai de u vira o pai de v.
	free(u);
}

void Tree::deletar(node *z)
{								   // Função que deleta um nó passado por parametro.
	node *y = z, *x;			   // Declaro algumas variaveis.
	int yOriginalColor = y->color; // Guardo a cor original da RB, será importante 
	if (z->left == T_NIL)          // para manter suas propriedades.
	{							   // Se z não tem filho da esquerda.
		x = z->right;			   // X vira o filho da direita.
		transplant(z, z->right);   // Substituo z pelo filho da direita.
	}
	else if (z->right == T_NIL)
	{							// Se z não tiver filho da direita.
		x = z->left;			// x vira o filho da esquerda
		transplant(z, z->left); // Substituo z pelo filho da esquerda
	}
	else
	{							   // Se z tem os dois filhos.
		y = minimum(y->right);	   // Encontro o menor filho da subárvore esquerda.
		yOriginalColor = y->color; // A cor de y será igual a cor do seu menor filho da esquerda.
		x = y->right;			   // x vira o filho da direita do menor elemento da subárvore esquerda.
		if (y->p == z)
			x->p = y; // se o pai de y for igual o nó a ser removido, o pai do seu filho direito é ele mesmo.
		else
		{
			transplant(y, y->right); // Substituo y pelo seu filho da direita.
			y->right = z->right;	 // O filho da direita de vira o filho da direita de z.
			y->right->p = y;
		}
		transplant(z, y);	 // Substituo z por y
		y->left = z->left;	 // O filho da esquerda de y vira o filho da esquerda de z.
		y->left->p = y;		 // O pai do filho da esquerda de y vira y.
		y->color = z->color; // A cor de y vira a cor de z, que foi transplantado pra y
	}
	if (yOriginalColor == BLACK)
		deleteFix_RB(x); // Se a cor original de y for preta, violamos a RB, então consertamos.
}

void Tree::rotacionar_esquerda(node *x)
{						// Função que totaciona a árvore pra esquerda
	node *y = x->right; // Pego o filho da direita
	x->right = y->left; // O filho da esquerda de y vira o filho da direita de x
	if (y->left != T_NIL)
	{					// Se existir filho
		y->left->p = x; // Altero o pai dele pra ser x;
	}
	y->left = x; // O filho da esquerda de y vira x;
	if (x->p == this->T_NIL)
		this->root = y; // Se x não tiver pai, então é raiz, logo y vira raiz
	else if (x->p->left == x)
		x->p->left = y; // Se não coloco o pai correto
	else
		x->p->right = y;
	y->p = x->p; // O pai de x vira o pai de y.
	x->p = y;	 // O pai de x vira y
}

void Tree::rotacionar_direita(node *x)
{ // Exatamente a função anterior, só que pra direita.
	node *y = x->left;
	x->left = y->right;
	if (y->right != T_NIL)
	{
		y->right->p = x;
	}
	y->right = x;
	if (x->p == this->T_NIL)
		this->root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->p = x->p;
	x->p = y;
}

node *Tree::search(int x)
{ // Procuro um nó na árvore.
	node *tmp = this->root;
	while (tmp != T_NIL && tmp->value != x)
	{
		if (tmp->value > x)
		{
			tmp = tmp->left;
		}
		else if (tmp->value < x)
		{
			tmp = tmp->right;
		}
	}
	return tmp;
}

node *Tree::minimum(node *x)
{ // Pego o menor elemento começando na subárvore com raiz x.
	while (x->left != T_NIL)
	{
		x = x->left;
	}
	return x;
}

void Tree::insertFix_RB(node *x)
{			 // Consertar a árvore após inserção
	node *y; // Variavel temporaria.
	while (x->p->color == RED)
	{ // Se o pai de x for vermelho, temos um problema pois x é vermelho e isso violaria a prioridade.
		if (x->p == x->p->p->left)
		{						// Se o pai de x for o filho esquerdo
			y = x->p->p->right; // Pego o tio de x.
			if (y->color == RED)
			{						  // Se o tio for vermelho, então eu apenas preciso pintar, chamo isso de Caso 1:
				x->p->color = BLACK;  // O pai de x vira preto
				y->color = BLACK;	  // O tio de x também vira preto
				x->p->p->color = RED; // O avô de x vira vermelho, assim mantemos a propriedade.
				x = x->p->p;		  // Passo x para ser avô, para ver se as propriedades ainda estão sendo violadas.
			}
			else
			{ // Se o tio não for vermelho, precisamos consertar
				if (x == x->p->right)
				{							// Se x for filho da direita, precisamos rotacionar pra esquerda
					x = x->p;				// x recebe seu pai
					rotacionar_esquerda(x); // rotaciono x para esquerda, abaixando o nó vermelho.
				}
				x->p->color = BLACK;  // o pai de x vira preto
				x->p->p->color = RED; // o avo de x fica vermelho
				// Nesse momento, x ainda é vermelho.
				/*
				* Então temos  R
				*            B   B
				*           R R R R
				*/
				rotacionar_direita(x->p->p); // Rotaciono pra direita
											 // Nesse momento, x ainda é vermelho.
				/*
				* Então temos  R
				*            B   B
				*           R R R R
				*/
			}
		}
		else
		{
			y = x->p->p->left;
			if (y->color == RED)
			{
				x->p->color = BLACK;
				y->color = BLACK;
				x->p->p->color = RED;
				x = x->p->p;
			}
			else
			{
				if (x == x->p->left)
				{
					x = x->p;
					rotacionar_direita(x);
				}
				x->p->color = BLACK;
				x->p->p->color = RED;
				rotacionar_esquerda(x->p->p);
			}
		}
	}
	this->root->color = BLACK;
}

void Tree::deleteFix_RB(node *x)
{
	node *w;
	while (x != this->root && x->color == BLACK)
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				rotacionar_esquerda(x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if (w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->left->color = RED;
					rotacionar_direita(w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				rotacionar_esquerda(x->p);
				x = this->root;
			}
		}
		else
		{
			w = x->p->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->p->color = RED;
				rotacionar_direita(x->p);
				w = x->p->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->p;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->right->color = RED;
					rotacionar_esquerda(w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rotacionar_direita(x->p);
				x = this->root;
			}
		}
	}
	x->color = BLACK;
}

void Tree::imprimir()
{
	imprime(this->root, this->T_NIL);
}

node *criar_no(int x, node *T_NIL)
{
	node *no = (node *)malloc(sizeof(node));
	no->left = no->right = no->p = T_NIL;
	no->value = x;
	no->color = RED;
	return no;
}

void imprime(node *no, node *T_NIL)
{
	if (no == NULL)
		return;
	queue<int> sp;
	queue<node *> q;
	q.push(no);
	sp.push(0);
	while (!q.empty())
	{
		node *tmp = q.front();
		int spaces = sp.front();
		sp.pop();
		q.pop();
		for (int i = 0; i < spaces; i++)
		{
			cout << "-";
		}
		if (tmp->color == RED)
			cout << "\033[1;31m " << tmp->value << "\033[0m" << endl;
		else
			cout << tmp->value << endl;
		if (tmp->left != T_NIL)
		{
			q.push(tmp->left);
			sp.push(spaces + 7);
		}
		if (tmp->right != T_NIL)
		{
			q.push(tmp->right);
			sp.push(spaces + 7);
		}
	}
}

void limpar(node *no, node *T_NIL)
{
	if (no == T_NIL)
		return;
	limpar(no->left, T_NIL);
	limpar(no->right, T_NIL);
	free(no);
}
