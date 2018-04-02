/***************
** ARQUIVO: ArvoreBin.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#include <iostream>
#include "ArvoreBin.h"

/***************
** NOME:
**	 insereNo
** DESCRICAO:
**	 insere um Nó em uma ABB
** PARAMETROS:
**	 n: Nó que vai ser inserido
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::insereNo(No *n) 
{
	if(!n) {
		this->raiz = this->novo;
		this->novo = NULL;
		
		return;
	}
	
	if(this->novo->getDado() == n->getDado())
		return;
	else if(this->novo->getDado() > n->getDado()) {
		if(n->getFilhoDir()) 
			return this->insereNo(n->getFilhoDir());
		
		n->setFilhoDir(this->novo);
		this->novo->setPai(n);
		this->novo = NULL;
	}
	else {
		if(n->getFilhoEsq()) 
			return this->insereNo(n->getFilhoEsq());
		
		n->setFilhoEsq(this->novo);
		this->novo->setPai(n);
		this->novo = NULL;
	}
}

/***************
** NOME:
**	 removeNo
** DESCRICAO:
**	 Remove um nó em uma ABB
** PARAMETROS:
**	 n: Nó que vai ser removido
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::removeNo(No *n) 
{
	if(n) {
		int g = 0 + n->getFilhoEsq() ? 1 : 0 + n->getFilhoDir() ? 1 : 0;
		No *d = this->buscaSubstituto(n);
		
		if(d) {	
			if(d->ehFolha()) {
				if(d->getPai()->getFilhoDir() == d)
					d->getPai()->setFilhoDir(NULL);
				else
					d->getPai()->setFilhoEsq(NULL);
			}
			else {
				if(d->getPai()->getFilhoDir() == d) {
					d->getPai()->setFilhoDir(d->getFilhoEsq());
					
					if(d->getFilhoEsq())
						d->getFilhoEsq()->setPai(d->getPai());
				}
				else {
					d->getPai()->setFilhoEsq(d->getFilhoDir());
					
					if(d->getFilhoDir())
						d->getFilhoDir()->setPai(d->getPai());
				}
			}
			if(n->getPai()) {
				if(n->getPai()->getFilhoDir() == n)
					n->getPai()->setFilhoDir(d);
				else 
					n->getPai()->setFilhoEsq(d);
			} 
		
			d->setFilhoEsq(n->getFilhoEsq());
			
			if(n->getFilhoEsq())
				n->getFilhoEsq()->setPai(d);
				
			d->setFilhoDir(n->getFilhoDir());
			
			if(n->getFilhoDir())
				n->getFilhoDir()->setPai(d);
				
			d->setPai(n->getPai());
		}
		
		if(n == this->raiz)
			this->raiz = d;
			
		delete n; 
	}
}

/***************
** NOME:
**	 buscaSubstituto
** DESCRICAO:
**	 busca um substituto pra entrar no lugar do termo que vai ser removido
** PARAMETROS:
**	 n: Nó que vai ser removido
** RETORNO:
**	 ponteiro para Nó
***************/

No* ArvoreBin::buscaSubstituto(No *n) 
{
	if(!n)
		return NULL;
	
	No *cursor = NULL;
	
	if(n->getFilhoEsq()) {
		cursor = n->getFilhoEsq();
		
		while(cursor->getFilhoDir())
			cursor = cursor->getFilhoDir();
	}
	else if(n->getFilhoDir()) {
		cursor = n->getFilhoDir();
		
		while(cursor->getFilhoEsq())
			cursor = cursor->getFilhoEsq();
	}
	
	return cursor;
}

/***************
** NOME:
**	 exclui
** DESCRICAO:
**	 Exclui a subárvore inteira de um determinado Nó
** PARAMETROS:
**	 n: Nó que vai ser excluido
** RETORNO:
**	 ponteiro para Nó
***************/

No* ArvoreBin::exclui(No *n) 
{
	if(n) {
		this->exclui(n->getFilhoDir());
		this->exclui(n->getFilhoEsq());
		
		delete n;
	}
}

/***************
** NOME:
**	 calculaAltura
** DESCRICAO:
**	 calcula a altura da árvore a partir de um determinado Nó
** PARAMETROS:
**	 n: Nó que vai ser usado para calcular a altura
** RETORNO:
**	 int
***************/

int ArvoreBin::calculaAltura(No *n) 
{
	if(n) 
		return 1 + max(this->calculaAltura(n->getFilhoEsq()), this->calculaAltura(n->getFilhoDir()));
	
	return 0;
}

/***************
** NOME:
**	 busca
** DESCRICAO:
**	 busca a chave (caracter) a partir de um Nó
** PARAMETROS:
**	 n: Nó que vai ser iniciada a busca
**	 chave: caracter que vai ser buscado
** RETORNO:
**	 ponteiro para Nó
***************/

No* ArvoreBin::busca(No *n, char chave) 
{
	if(!n || n->getDado() == chave)
		return n;
	else if(n->getDado() < chave)
		return this->busca(n->getFilhoDir(), chave);
	else
		return this->busca(n->getFilhoEsq(), chave);
}

/***************
** NOME:
**	 exibePreFixa
** DESCRICAO:
**	 exibe a árvore a partir de um nó na notação pre-fixa
** PARAMETROS:
**	 n: raiz da árvore ou subárvore a ser exibida
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePreFixa(No* n) {
	if(n) {
		printf("%c ", n->getDado());
		this->exibePreFixa(n->getFilhoEsq());
		this->exibePreFixa(n->getFilhoDir());
	}
}

/***************
** NOME:
**	 exibePosFixa
** DESCRICAO:
**	 exibe a árvore a partir de um nó na notação pos-fixa
** PARAMETROS:
**	 n: raiz da árvore ou subárvore a ser exibida
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePosFixa(No* n) 
{
	if(n) {
		this->exibePosFixa(n->getFilhoEsq());
		this->exibePosFixa(n->getFilhoDir());
		printf("%c ", n->getDado());
	}
}

/***************
** NOME:
**	 exibeInFixa
** DESCRICAO:
**	 exibe a árvore a partir de um nó na notação infixa
** PARAMETROS:
**	 n: raiz da árvore ou subárvore a ser exibida
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeInFixa(No* n) 
{
	if(n) {
		this->exibeInFixa(n->getFilhoEsq());
		printf("%c ", n->getDado());
		this->exibeInFixa(n->getFilhoDir());
	}
}

/***************
** NOME:
**	 ArvoreBin
** DESCRICAO:
**	 Construtor padrão
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

ArvoreBin::ArvoreBin() 
{
	this->raiz = this->novo = NULL;
}

/***************
** NOME:
**	 ArvoreBin
** DESCRICAO:
**	 Construtor
** PARAMETROS:
**	 sequencia: sequencia de caracteres que vai formar a árvore
** RETORNO:
**	 Nenhum
***************/

ArvoreBin::ArvoreBin(string sequencia) 
{
	this->insereTextual(sequencia);
}

/***************
** NOME:
**	 ~ArvoreBin
** DESCRICAO:
**	 Destrutor
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

ArvoreBin::~ArvoreBin() 
{
	this->exclui();
}

/***************
** NOME:
**	 insereNo
** DESCRICAO:
**	 insere um Nó na árvore
** PARAMETROS:
**	 c: caracter que vai ser o dado do Nó
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::insereNo(char c) 
{
	this->novo = new No(c);
	
	this->insereNo(this->raiz);
}

/***************
** NOME:
**	 removeNo
** DESCRICAO:
**	 remove um nó da árvore que contenha um caracter. Se não tiver o caracter na árvore, não faz nada
** PARAMETROS:
**	 c: caracter que vai ser removido da Árvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::removeNo(char c) 
{
	if(this->busca(c)) 
		this->removeNo(busca(c));
}

/***************
** NOME:
**	 exclui
** DESCRICAO:
**	 exclui toda a arvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exclui() 
{
	this->exclui(this->raiz);
	this->raiz = NULL;
}

/***************
** NOME:
**	 getAltura
** DESCRICAO:
**	 calcula a altura da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 int
***************/

int ArvoreBin::getAltura() 
{
	return this->calculaAltura(this->raiz);
}

/***************
** NOME:
**	 busca
** DESCRICAO:
**	 busca um determinado Nó com a chave fornecida
** PARAMETROS:
**	 chave: caracter que vai ser o dado do Nó buscado
** RETORNO:
**	 ponteiro pra Nó
***************/

No* ArvoreBin::busca(char chave) 
{
	return this->busca(raiz, chave);
}

/***************
** NOME:
**	 exibePreFixa
** DESCRICAO:
**	 exibe a árvore inteira em notação pre-fixa
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePreFixa() 
{
	this->exibePreFixa(this->raiz);
}

/***************
** NOME:
**	 exibePosFixa
** DESCRICAO:
**	 exibe a árvore inteira em notação pos-fixa
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePosFixa() {
	this->exibePosFixa(this->raiz);
}

/***************
** NOME:
**	 exibeInFixa
** DESCRICAO:
**	 exibe a árvore inteira em notação infixa
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeInFixa() {
	this->exibeInFixa(this->raiz);
}

/***************
** NOME:
**	 exibeCaminho
** DESCRICAO:
**	 exibe o caminho da raiz até encontrar o Nó com a chave
** PARAMETROS:
**	 chave: caracter que vai ser o dado do Nó procurado
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeCaminho(char chave) {
	No *atual = raiz;
	
	if(busca(chave)) {
		while(atual->getDado() != chave) {
			printf("%c ", atual->getDado());
			
			if(chave > atual->getDado())
				atual = atual->getFilhoDir();
			else
				atual = atual->getFilhoEsq();
		}
		
		printf("%c\n", chave);
	}
	else 
		puts("Chave nao encontrada!");
	
	return;
}

/***************
** NOME:
**	 exibeCaminhoInverso
** DESCRICAO:
**	 exibe o caminho desde a chave até a raiz
** PARAMETROS:
**	 chave: caracter que vai ser o dado do Nó procurado
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeCaminhoInverso(char chave) {
	No *atual = busca(chave);
	
	if(atual) {
		while(atual->getPai()) {
			printf("%c ", atual->getDado());
			atual = atual->getPai();
		}
		
		printf("%c\n", atual->getDado());
	}
	else
		puts("Chave nao encontrada!");
}

/***************
** NOME:
**	 exibeCaminhoFolhas
** DESCRICAO:
**	 exibe o caminho da raíz até todas as folhas da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeCaminhoFolhas() {
	this->exibeCaminhoFolhas(this->raiz);
}

/***************
** NOME:
**	 exibeCaminhoFolhas
** DESCRICAO:
**	 exibe o caminho de um nó para todas as folhas da sua subárvore
** PARAMETROS:
**	 n: Nó que é a raíz da subárvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeCaminhoFolhas(No *n) {
	if(!n)
		return;
		
	if(!n->ehFolha()) {
		this->exibeCaminhoFolhas(n->getFilhoEsq());
		this->exibeCaminhoFolhas(n->getFilhoDir());
	}
	else
		this->exibeCaminho(n->getDado());
}

/***************
** NOME:
**	 exibeNiveisNos
** DESCRICAO:
**	 exibe o nível de cada nó da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeNiveisNos() {
	puts("Exibindo os niveis de cada no da arvore:");
	this->exibeNiveisNos(raiz, 0);
}

/***************
** NOME:
**	 exibeNiveisNos
** DESCRICAO:
**	 exibe o nível de um nó e da subárvore respectiva
** PARAMETROS:
**	 n: Nó que é a raíz da subárvore
**   nivel: nível atual do Nó 
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeNiveisNos(No *n, int nivel) {
	if(n) {
		printf("%c: %d\n", n->getDado(), nivel);
		this->exibeNiveisNos(n->getFilhoEsq(), nivel+1);
		this->exibeNiveisNos(n->getFilhoDir(), nivel+1);
	}
}

/***************
** NOME:
**	 exibeAlturaNos
** DESCRICAO:
**	 exibe a altura de cada nó da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeAlturaNos() {
	puts("Exibindo as alturas de cada no da arvore:");
	this->exibeAlturaNos(raiz, getAltura());
}

/***************
** NOME:
**	 exibeAlturaNos
** DESCRICAO:
**	 exibe a altura de um nó e dos nós da sua subárvore
** PARAMETROS:
**	 n: Nó raíz da subárvore
**   altura: altura do Nó atual
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeAlturaNos(No *n, int altura) {
	if(n) {
		printf("%c: %d\n", n->getDado(), altura);
		this->exibeAlturaNos(n->getFilhoEsq(), altura-1);
		this->exibeAlturaNos(n->getFilhoDir(), altura-1);
	}
}

/***************
** NOME:
**	 exibeGrausNos
** DESCRICAO:
**	 exibe o grau de todos os nós da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeGrausNos() {
	puts("Exibindo os graus de cada no da arvore:");
	this->exibeGrausNos(raiz);
}

/***************
** NOME:
**	 exibeGrausNos
** DESCRICAO:
**	 exibe o grau do respectivo nó e de sua subárvore
** PARAMETROS:
**	 n: Nó que vai ser a raíz da subárvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeGrausNos(No *n) {
	if(n) {
		printf("%c: %d\n", n->getDado(), 0 + n->getFilhoDir() ? 1 : 0 + n->getFilhoEsq() ? 1 : 0);
		this->exibeGrausNos(n->getFilhoEsq());
		this->exibeGrausNos(n->getFilhoDir());
	}
}

/***************
** NOME:
**	 exibePaisNos
** DESCRICAO:
**	 exibe os pais de todos os nós da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePaisNos() {
	puts("Exibindo os pais de cada no da arvore:");
	this->exibePaisNos(this->raiz);
}

/***************
** NOME:
**	 exibePaisNos
** DESCRICAO:
**	 exibe os pais de um respectivo Nó e de sua subárvore
** PARAMETROS:
**	 n: Nó que é a raiz da subárvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibePaisNos(No *n) {
	if(n) {
		printf("%c: ", n->getDado());
		
		if(n->getPai()) 
			printf("%c\n", n->getPai()->getDado());
		else
			puts("NULL");
			
		this->exibePaisNos(n->getFilhoEsq());
		this->exibePaisNos(n->getFilhoDir());
	}
}

/***************
** NOME:
**	 exibeEnderecosNos
** DESCRICAO:
**	 exibe o endereço de todos os nós da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeEnderecosNos() {
	puts("Exibindo os enderecos de cada no da arvore:");
	this->exibeEnderecosNos(raiz);
}

/***************
** NOME:
**	 exibeEnderecosNos
** DESCRICAO:
**	 exibe o endereço dos nós a partir de um nó
** PARAMETROS:
**	 n: No raiz da subárvore
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::exibeEnderecosNos(No *n) {
	if(n) {
		printf("%c: %p\n", n->getDado(), n);
		this->exibeEnderecosNos(n->getFilhoEsq());
		this->exibeEnderecosNos(n->getFilhoDir());
	}
}
/***************
** NOME:
**	 geraString
** DESCRICAO:
**	 exibe a árvore em notação textual
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 string
***************/

string ArvoreBin::geraString() {
	return this->geraString(this->raiz);
}

/***************
** NOME:
**	 geraString
** DESCRICAO:
**	 exibe em notação textual a partir de um nó
** PARAMETROS:
**	 n: Nó que é a raiz da subárvore a ser exibida
** RETORNO:
**	 string
***************/

string ArvoreBin::geraString(No *n) {
	string atual;
	
	atual += "<";
	
	if(n) {
		atual += this->geraString(n->getFilhoEsq());
		atual += n->getDado();
		atual += this->geraString(n->getFilhoDir());
	}
	else 
		atual += " ";
	atual += ">";
	
	return atual;
}

/***************
** NOME:
**	 insereTextual
** DESCRICAO:
**	 insere na árvore por uma string
** PARAMETROS:
**	 sequencia: string a ser inserida
** RETORNO:
**	 Nenhum
***************/

void ArvoreBin::insereTextual(string sequencia) {
	cursor = raiz;
	bool ignorarProximo = false;
	
	for(int i = 0; i < sequencia.size(); i++) {
		if(ignorarProximo == false) 
			ignorarProximo = this->insereTextual(sequencia[i]);
		else
			ignorarProximo = false;
	}
	
	cursor = NULL;
}

/***************
** NOME:
**	 insereTextual
** DESCRICAO:
**	 insere textual a partir de um token e um cursor
** PARAMETROS:
**	 token: caracter a ser inserido
**   cursor: ponteiro pra percorrer a árvore
** RETORNO:
**	 bool
***************/

bool ArvoreBin::insereTextual(char token) {
	if(token == '>')
		cursor = cursor->getPai();
	else if(token == '<') {
		novo = new No(0);
		
		printf("%p\n", novo);
		
		if(!this->raiz)
			raiz = novo;
		else
			cursor->setFilhoEsq(novo);
		
		novo->setPai(cursor);
		cursor = novo;
		
		novo = NULL;
	}
	else if(token == ' ') {
		novo = cursor->getPai();
		
		if(novo->getFilhoDir() == cursor)
			novo->setFilhoDir(NULL);
		else
			novo->setFilhoEsq(NULL);
			
		delete cursor;
		
		cursor = novo;
		
		novo = NULL;
		
		return true;
	}
	else {
		cursor->setDado(token);
		
		novo = new No(0);
		
		cursor->setFilhoDir(novo);
		novo->setPai(cursor);
		
		cursor = novo;
		
		novo = NULL;
		
		return true;
	}
	
	return false;
}

/***************
** NOME:
**	 getRaiz
** DESCRICAO:
**	 retorna a raíz da árvore
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 ponteiro pra Nó
***************/

No* ArvoreBin::getRaiz() {
	return this->raiz;
}