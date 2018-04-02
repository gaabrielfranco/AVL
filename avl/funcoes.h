/***************
** ARQUIVO: ArvoreBin.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#ifndef FUNCOES_H
#define FUNCOES_H

#include <iostream>
#include <fstream>
#include <string>

#include "ArvoreAvl.h"

using namespace std;

bool leDadosSequencial(string, ArvoreAvl *, bool);

bool leDados(string, ArvoreAvl *);

void limpaTela();

int exibeMenu();

void executaOpcao(int, ArvoreAvl *, bool &);

char leChar();

int converteNum(string);

void salva(string, ArvoreAvl *);

void salvaGrafico(string, ArvoreAvl *);

string leNomeArquivo();

#endif // FUNCOES_H
