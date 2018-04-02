/***************
** ARQUIVO: ArvoreAvl.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208 
***************/

#include <iostream>
#include "ArvoreBin.h"
#include "ArvoreAvl.h"

using namespace std;

/***************
** NOME:
**	 ArvoreAvl
** DESCRICAO:
**	 Construtor Padrão
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

ArvoreAvl::ArvoreAvl()
{
	this->raiz = this->novo = NULL;
}

/***************
** NOME:
**	 ~ArvoreAvl
** DESCRICAO:
**	 Destrutor
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

ArvoreAvl::~ArvoreAvl()
{
	this->exclui();
}

/***************
** NOME:
**	 fatorBalanceamento
** DESCRICAO:
**	 calcula o fator de balanceamento de um nó
** PARAMETROS:
**	 n: Nó que vai ser calculado o FB
** RETORNO:
**	 int
***************/

int ArvoreAvl::fatorBalanceamento(No* n)
{
    if (!n)
       return 0;
    return this->calculaAltura(n->getFilhoEsq()) - calculaAltura(n->getFilhoDir());
}

/***************
** NOME:
**	 rotacaoSimplesEsquerda
** DESCRICAO:
**	 faz a rotação simples a esquerda a partir de um nó
** PARAMETROS:
**	 n: Nó que vai ser o pivô
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::rotacaoSimplesEsquerda(No* n)
{
    No* aux;

    aux = n->getFilhoDir();
	
	if(n->getPai()) {
		if(n->getPai()->getFilhoDir() == n)
			n->getPai()->setFilhoDir(aux);
		else
			n->getPai()->setFilhoEsq(aux);
	}
	
	aux->setPai(n->getPai());
    n->setPai(aux);
	
    n->setFilhoDir(aux->getFilhoEsq());
	
	if(aux->getFilhoEsq())
		aux->getFilhoEsq()->setPai(n);
    
	aux->setFilhoEsq(n);
    
	if(n == raiz)
		raiz = aux;
}

/***************
** NOME:
**	 rotacaoSimplesDireita
** DESCRICAO:
**	 faz a rotação simples a direita a partir de um nó
** PARAMETROS:
**	 n: Nó que vai ser o pivô
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::rotacaoSimplesDireita(No* n)
{
    No* aux;

    aux = n->getFilhoEsq();
	
	if(n->getPai()) {
		if(n->getPai()->getFilhoDir() == n)
			n->getPai()->setFilhoDir(aux);
		else
			n->getPai()->setFilhoEsq(aux);
	}
	
	aux->setPai(n->getPai());
    n->setPai(aux);
	
	n->setFilhoEsq(aux->getFilhoDir());
    
	if(aux->getFilhoDir())
		aux->getFilhoDir()->setPai(n);
	
	aux->setFilhoDir(n);
    
	if(n == raiz)
		raiz = aux;	
}

/***************
** NOME:
**	 balanceiaEsquerda
** DESCRICAO:
**	 balanceia um Nó a esquerda (verifica se é rotação simples ou dupla a esquerda)
** PARAMETROS:
**	 n: Nó que vai ser o pivô
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::balanceiaEsquerda(No* n)
{
    int fBal = this->fatorBalanceamento(n->getFilhoEsq());

    if (fBal > 0)
        this->rotacaoSimplesDireita(n);
    else if (fBal < 0)
    {
        this->rotacaoSimplesEsquerda(n->getFilhoEsq());
        this->rotacaoSimplesDireita(n);
    }
}

/***************
** NOME:
**	 balanceiaDireita
** DESCRICAO:
**	 balanceia um Nó a direita (verifica se é rotação simples ou dupla a direita)
** PARAMETROS:
**	 n: Nó que vai ser o pivô
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::balanceiaDireita(No* n)
{
    int fBal = this->fatorBalanceamento(n->getFilhoDir());

    if (fBal < 0)
        this->rotacaoSimplesEsquerda(n);
    else if (fBal > 0)
    {
        this->rotacaoSimplesDireita(n->getFilhoDir());
        this->rotacaoSimplesEsquerda(n);
    }
}

/***************
** NOME:
**	 balanceia
** DESCRICAO:
**	 balanceia um nó
** PARAMETROS:
**	 n: Nó que vai ser balanceado
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::balanceia(No* n)
{
	int fBal;
	
	if(n) {
		while (n->getPai()) {
			n = n->getPai();
			
			fBal = this->fatorBalanceamento(n);

			if (fBal > 1)
				this->balanceiaEsquerda(n);
			else if (fBal < -1)
				this->balanceiaDireita(n);
		}
	}
}

/***************
** NOME:
**	 insereNoAvl
** DESCRICAO:
**	 insere um Nó em uma AVL
** PARAMETROS:
**	 n: Nó que vai ser inserido
** RETORNO:
**	 Nenhum
***************/


void ArvoreAvl::insereNoAvl(No* n)
{
    if (!this->raiz)
    {
        this->raiz = n;
        this->raiz->setFilhoEsq(NULL);
        this->raiz->setFilhoDir(NULL);
    }
    else
    {
        this->insereNo(n->getDado()) ;
        this->balanceia(busca(n->getDado()));         //Verificar se funciona
    }
}

/***************
** NOME:
**	 ehAvl
** DESCRICAO:
**	 verifica se a árvore é AVL
** PARAMETROS:
**	 n: Nó raiz da subárvore a ser calculado o balanceado
** RETORNO:
**	 bool
***************/

bool ArvoreAvl::ehAvl(No* n)
{
    int fBal;

    if(!n)
        return true;

    if (!this->ehAvl(n->getFilhoEsq()))
        return false;
    if (!this->ehAvl(n->getFilhoDir()))
        return false;

    fBal = this->fatorBalanceamento(n);

    if (fBal < -1 || fBal > 1)
        return false;
    else
        return true;
}

/***************
** NOME:
**	 insereNoAvl
** DESCRICAO:
**	 insere um Nó em uma AVL
** PARAMETROS:
**	 c: caracter a ser inserido
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::insereNoAvl(char c)
{
    this->novo = new No(c);
    this->insereNoAvl(this->novo);
}

/***************
** NOME:
**	 removeNoAvl
** DESCRICAO:
**	 remove um Nó em uma AVL
** PARAMETROS:
**	 chave: caracter a ser removido
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::removeNoAvl(char chave)
{
    this->removeNo(this->busca(chave));
	rebalanceia(raiz);
}

/***************
** NOME:
**	 rebalanceia
** DESCRICAO:
**	 rebalanceia toda a árvore
** PARAMETROS:
**	 No raíz da subárvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::rebalanceia(No *n) {
	if(n) {
		if(!n->ehFolha()) {
			rebalanceia(n->getFilhoDir());
			rebalanceia(n->getFilhoEsq());
		}
		else
			balanceia(n);
	}
}

/***************
** NOME:
**	 ehAvl
** DESCRICAO:
**	 verifica se a árvore é AVL
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

bool ArvoreAvl::ehAvl()
{
    return this->ehAvl(this->raiz);
}

/***************
** NOME:
**	 exibeFbNos
** DESCRICAO:
**	 exibe o fator de balanceamento da subárvore respectiva
** PARAMETROS:
**	 n: Nó que vai ser exibido o FB
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::exibeFbNos(No* n)
{
    if (!n)
        return;

    exibeFbNos(n->getFilhoEsq());
    exibeFbNos(n->getFilhoDir());
    cout << n->getDado() << ": " << this->fatorBalanceamento(n) << endl;
}

/***************
** NOME:
**	 exibeFbNos
** DESCRICAO:
**	 exibe o fator de balanceamento de cada nó da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreAvl::exibeFbNos()
{
    this->exibeFbNos(this->raiz);
}
