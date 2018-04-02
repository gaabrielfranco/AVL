/***************
** ARQUIVO: No.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#include "No.h"

/***************
** NOME:
**	 No
** DESCRICAO:
**	 Construtor padrão
** PARAMETROS:
**	 n: caracter que vai ser o dado do Nó
** RETORNO:
**	 Nenhum
***************/

No::No(char n) 
{
	dado = n;
	
	setFilhoEsq(NULL);
	setFilhoDir(NULL);
	setPai(NULL);
}

/***************
** NOME:
**	 No
** DESCRICAO:
**	 Construtor de cópia
** PARAMETROS:
**	 outro: Nó que vai ser copiado
** RETORNO:
**	 Nenhum
***************/

No::No(const No &outro) 
{
	*this = outro;
}

/***************
** NOME:
**	 limpa
** DESCRICAO:
**	 Limpa o nó
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

void No::limpa()
{
	this->dado = 0;
	
	this->setFilhoEsq(NULL);
	this->setFilhoDir(NULL);
	this->setPai(NULL);
}

/***************
** NOME:
**	 ~No
** DESCRICAO:
**	 Destrutor
** PARAMETROS:
**	 Nenhum
** RETORNO:
**	 Nenhum
***************/

No::~No() 
{
	this->limpa();
}

/***************
** NOME:
**	 operator=
** DESCRICAO:
**	 Sobrecarregar o operador =
** PARAMETROS:
**	 outro: o Nó que vai ser copiado
** RETORNO:
**	 Nenhum
***************/

No No::operator=(const No &outro) 
{
	
	this->limpa();
	
	this->dado = outro.dado;
	
	setFilhoEsq(NULL);
	setFilhoDir(NULL);
	setPai(NULL);
	
	return *this;
}

/***************
** NOME:
**	 setDado
** DESCRICAO:
**	 Muda o dado atual
** PARAMETROS:
**	 d: caracter que vai ser inserido
** RETORNO:
**	 Nenhum
***************/

void No::setDado(char d) 
{
	this->dado = d;
}

/***************
** NOME:
**	 getDado
** DESCRICAO:
**	 retorna o dado atual
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 char
***************/

char No::getDado() 
{
	return this->dado;
}

/***************
** NOME:
**	 setFilhoEsq
** DESCRICAO:
**	 muda o filho da esquerda do Nó
** PARAMETROS:
**	 filho: é o Nó que vai ser o novo filho do atual
** RETORNO:
**	 Nenhum
***************/

void No::setFilhoEsq(No *filho) 
{
	this->filhoEsq = filho;
}

/***************
** NOME:
**	 getFilhoEsq
** DESCRICAO:
**	 retorna o filho da esquerda do Nó
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 ponteiro pra No
***************/

No* No::getFilhoEsq() 
{
	return this->filhoEsq;
}

/***************
** NOME:
**	 setFilhoDir
** DESCRICAO:
**	 muda o filho da direita do Nó
** PARAMETROS:
**	 filho: é o Nó que vai ser o novo filho do atual
** RETORNO:
**	 Nenhum
***************/

void No::setFilhoDir(No *filho) 
{
	this->filhoDir = filho;
}

/***************
** NOME:
**	 getFilhoDir
** DESCRICAO:
**	 retorna o filho da direita do Nó
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 ponteiro pra Nó
***************/

No* No::getFilhoDir() 
{
	return this->filhoDir;
}

/***************
** NOME:
**	 setPai
** DESCRICAO:
**	 muda o pai do nó atual
** PARAMETROS:
**	 p: nó que vai ser o novo pai do nó atual
** RETORNO:
**	 Nenhum
***************/

void No::setPai(No *p) 
{
	this->pai = p;
}

/***************
** NOME:
**	 getPai
** DESCRICAO:
**	 retorna o pai do nó atual
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 ponteiro para Nó
***************/

No* No::getPai() 
{
	return this->pai;
}

/***************
** NOME:
**	 ehFolha
** DESCRICAO:
**	 Verifica se o nó atual é folha
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 bool
***************/

bool No::ehFolha() 
{
	return !(filhoEsq || filhoDir);
}

/***************
** NOME:
**	 getGrau
** DESCRICAO:
**	 retorna o grau do nó atual
** PARAMETROS:
**	 nenhum
** RETORNO:
**	 int
***************/

int No::getGrau() 
{
	return 0 + getFilhoDir() ? 1 : 0 + getFilhoEsq() ? 1 : 0;
}