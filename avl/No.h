/***************
** ARQUIVO: No.h
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#ifndef NO_H
#define NO_H

#include <stdlib.h>

class No {
	protected:
		char dado;
		No *filhoEsq, *filhoDir, *pai;
		void limpa();
	
	public:
		No(char n);
		No(const No &outro);
		~No();
		No operator=(const No &outro);
		void setDado(char d);
		char getDado();
		void setFilhoEsq(No *filho);
		No* getFilhoEsq();
		void setFilhoDir(No *filho);
		No* getFilhoDir();
		void setPai(No *p);
		No* getPai();
		bool ehFolha();
		int getGrau();
};

#endif