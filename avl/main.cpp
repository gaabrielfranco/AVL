/***************
** ARQUIVO: ArvoreBin.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#include <cstdio>

#include "ArvoreAvl.h"
#include "funcoes.h"

#define AVL 1
#define ABB 0

using namespace std;

int main () {
	int opcao;
	bool tipo = AVL;
	ArvoreAvl arvore;
	
	opcao = exibeMenu();
	
	while(opcao != 24) {
		limpaTela();
	
		executaOpcao(opcao, &arvore, tipo);
		
		printf("\nPrecione qualquer tecla para continuar...");
		
		getc(stdin);
		getc(stdin);
		
		opcao = exibeMenu();
	}
	
	return 0;
}