#include <bits/stdc++.h>
#include "arvore_rb.h"

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int n, x, r;
	Tree T;
	cout << "Quantidade de elementos na Árvore: ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		T.insere(x);
		//T.imprimir();
	}
	cout << "\nÁrvore resultante:" << endl;
	T.imprimir();
	cout << "Elemento a ser removido: ";
	cin >> r;
	T.deletar(T.search(r));
	cout << "\nÁrvore após remoção:" << endl;
	T.imprimir();
	cout << endl;
}
