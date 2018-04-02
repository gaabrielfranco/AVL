/***************
** ARQUIVO: ArvoreAvl.h
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include <iostream>
#include "No.h"
#include "ArvoreBin.h"


using namespace std;

class ArvoreAvl : public ArvoreBin
{
    protected:
        int fatorBalanceamento(No*);
        void rotacaoSimplesEsquerda(No*);
        void rotacaoSimplesDireita(No*);
        void balanceiaEsquerda(No*);
        void balanceiaDireita(No*);
        void balanceia(No*);
        void insereNoAvl(No*);
        bool ehAvl(No*);
        void exibeFbNos(No*);
		void rebalanceia(No *n);
    public:
		ArvoreAvl();
		~ArvoreAvl();
        void insereNoAvl(char);
        void removeNoAvl(char);
        bool ehAvl();
        void exibeFbNos();
};

#endif
