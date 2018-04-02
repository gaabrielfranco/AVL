/***************
** ARQUIVO: ArvoreBin.h
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#ifndef ArvoreBin_H
#define ArvoreBin_H

#include <string>		//Tipo string
#include <algorithm>	//Função max
#include <cstdio>		//Função printf

#include "No.h"

using namespace std;

class ArvoreBin {
	protected:
		No *raiz, *novo, *cursor;
		void insereNo(No *n);
		void removeNo(No *n);
		No* exclui(No *n);
		int calculaAltura(No *n);
		No* busca(No *n, char chave);
		No* buscaSubstituto(No *n) ;
		void exibePreFixa(No* n);
		void exibePosFixa(No* n);
		void exibeInFixa(No* n);
		string geraString(No* n);
		void exibeCaminhoFolhas(No *n);
		void exibeNiveisNos(No *n, int nivel);
		void exibeAlturaNos(No *n, int altura);
		void exibeGrausNos(No *n);
		void exibePaisNos(No *n);
		void exibeEnderecosNos(No *n);
		
	public:
		ArvoreBin();
		ArvoreBin(string sequencia);
		~ArvoreBin();
		void insereNo(char c);
		void removeNo(char c);
		void exclui();
		No* getRaiz();
		int getAltura();
		No* busca(char chave);
		void exibePreFixa();
		void exibePosFixa();
		void exibeInFixa();
		void exibeCaminho(char chave);
		void exibeCaminhoInverso(char chave);
		void exibeCaminhoFolhas();
		void exibeNiveisNos();
		void exibeAlturaNos();
		void exibeGrausNos();
		void exibePaisNos();
		void exibeEnderecosNos();
		void insereTextual(string sequencia);
		string geraString();
		bool insereTextual(char token);
};

#endif