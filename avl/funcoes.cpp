/***************
** ARQUIVO: ArvoreBin.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>

#include "ArvoreBin.h"
#include "No.h"
#include "Visualizador.h"

using namespace std;

/***************
** NOME:
**	 salva
** DESCRICAO:
**	 abre um arquivo e salva a árvore
** PARAMETROS:
**	 nomeArquivo: nome do arquivo
**   arvore: ponteiro pra arvore
** RETORNO:
**	 Nenhum
***************/

void salva(string nomeArquivo, ArvoreAvl *arvore) {	
	ofstream arq(nomeArquivo.c_str());
	
	if(arq.is_open()) {
		arq << arvore->geraString();
		arq.close();
	}
}

/***************
** NOME:
**	 leDados
** DESCRICAO:
**	 le os dados de um arquivo e insere na árvore
** PARAMETROS:
**	 nomeArquivo: nome do arquivo
**   arvore: ponteiro pra arvore
** RETORNO:
**	 Nenhum
***************/

bool leDados(string nomeArquivo, ArvoreAvl *arvore) {
	string textual;
	ifstream arq(nomeArquivo.c_str());
	
	if(arq.is_open()) {
		getline(arq, textual);
		arq.close();
	}
	
	arvore->insereTextual(textual);
}

bool salvaGrafico(string nomeArquivo, ArvoreAvl *arvore) {
    Visualizador v(arvore);
    string dados = v.retornaString();

    ofstream arq(nomeArquivo.c_str());

    if (arq.is_open()) {
        arq << dados;
        arq.close();

        return true;
    }

    return false;
}

bool leDadosSequencial(string nomeArquivo, ArvoreAvl *arvore, bool avl) {
    string linha;
    ifstream arq(nomeArquivo.c_str());
    int tam;

    arvore->exclui();

    if (arq.is_open()) {
        while (getline(arq,linha)) {
            tam = linha.length();
            for (int i = 0; i < tam; i++)
                if (avl)
                    arvore->insereNoAvl(linha[i]);
                else
                    arvore->insereNo(linha[i]);
        }
        arq.close();
        return true;
    }

    return false;
}

string leNomeArquivo() {
    cout << endl << "Informe o nome do arquivo: " << flush;
    string nome;
    cin >> nome;

    return nome;
}

void limpaTela() {
    for (int i = 0; i < 70; i++) cout << endl;
}

int converteNum(string s) {
    int tam = s.length();
    for (int i = 0; i < tam; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }

    return atoi(s.c_str());
}

int exibeMenu() {
    string opcao;
    int opcaoNum;
    do {
        limpaTela();
        cout << "======================================================== ARVORES BINARIAS ========================================================" << endl;
        cout << "MENU DE OPCOES:" << endl;
        cout << endl << "--- TIPO DE ARVORE ---" << endl;
        cout << "\t 1) MUDAR O TIPO DE ARVORE" << endl;
        cout << "\t 2) EXIBIR TIPO DE ARVORE" << endl;
        cout << endl << "--- ARQUIVOS ---" << endl;
        cout << "\t 3) CARREGAR DADOS DE ARQUIVO COM SEQUENCIA DE DADOS PARA ARVORE" << endl;
        cout << "\t 4) CARREGAR DADOS DE ARQUIVO COM NOTACAO TEXTUAL PARA ARVORE" << endl;
        cout << "\t 5) SALVAR ARVORE EM ARQUIVO" << endl;
        cout << "\t 6) SALVAR REPRESENTACAO GRAFICA DE ARVORE EM ARQUIVO" << endl;
        cout << endl << "--- EDITAR ARVORE ---" << endl;
        cout << "\t 7) INSERIR MANUALMENTE UM VALOR NA ARVORE" << endl;
        cout << "\t 8) REMOVER UM VALOR DA ARVORE" << endl;
        cout << "\t 9) ESVAZIAR ARVORE" << endl;
        cout << endl << "--- VISUALIZACAO DE DADOS DE NOS ---" << endl;
        cout << "\t10) EXIBIR NIVEIS DOS NOS DA ARVORE" << endl;
        cout << "\t11) EXIBIR ALTURAS DOS NOS DA ARVORE" << endl;
        cout << "\t12) EXIBIR GRAUS DOS NOS DA ARVORE" << endl;
        cout << "\t13) EXIBIR PAIS DOS NOS DA ARVORE" << endl;
        cout << "\t14) EXIBIR ENDERECOS DOS NOS DA ARVORE" << endl;
        cout << "\t15) EXIBIR FATORES DE BALANCEAMENTOS DOS NOS DA ARVORE" << endl;
        cout << endl << "--- VISUALIZACAO DA ARVORE ---" << endl;
        cout << "\t16) VISUALIZAR ARVORE" << endl;
        cout << "\t17) EXIBIR ARVORE EM NOTACAO PREFIXA" << endl;
        cout << "\t18) EXIBIR ARVORE EM NOTACAO POSFIXA" << endl;
        cout << "\t19) EXIBIR ARVORE EM NOTACAO INFIXA" << endl;
        cout << "\t20) EXIBIR ALTURA DA ARVORE" << endl;
        cout << endl << "--- CAMINHAMENTO ---" << endl;
        cout << "\t21) EXIBIR CAMINHO ATE NO DA ARVORE" << endl;
        cout << "\t22) EXIBIR CAMINHO DO NO DA ARVORE ATE RAIZ" << endl;
        cout << "\t23) EXIBIR CAMINHOS ATE FOLHAS DA ARVORE" << endl;
        cout << endl << "-------" << endl;
        cout << "\t24) SAIR" << endl;
        cout << "ESCOLHA A OPCAO DESEJADA: " << flush;
        cin >> opcao;

        opcaoNum = converteNum(opcao);

        if (opcaoNum < 1 || opcaoNum > 24) {
            cout << "OPCAO INVALIDA! TENTE NOVAMENTE!" << endl;
            cout << "DIGITE ENTER PARA CONTINUAR" << endl;
            getchar();
            getchar();
        }

    } while (opcaoNum < 1 || opcaoNum > 24);
    return opcaoNum;
}

char leChar() {
    char c;
    do {
        cout << endl << "Informe um caractere: " << flush;
        cin >> c;
        if (c == ' ' || c == '<' || c == '>') {
            cout << "Erro: o caractere " << c << " eh reservado para a representacao textual da arvore. Nao pode ser utilizado como dado." << endl;
        }
    } while (c == ' ' || c == '<' || c == '>');

    return c;
}

/***************
** NOME:
**	 executaOpcao
** DESCRICAO:
**	 abre o menu e executa a opção que o usuário escolher
** PARAMETROS:
**   opcao: é o numero da opção escolhida
**	 arvore: ponteiro pra árvore
**   AVL: verifica o tipo da árvore
** RETORNO:
**	 Nenhum
***************/

void executaOpcao(int opcao, ArvoreAvl *arvore, bool &AVL) {
	string nome;
	Visualizador v(arvore);
	char c;
	
	switch(opcao) {
		case 1:
			AVL = !AVL;
		break;
		case 2:
			printf("Arvore %s\n", AVL ? "AVL" : "ABB"); 
		break;
		case 3:
			printf("Qual o nome do arquivo?\n");
			cin >> nome;
			leDadosSequencial(nome, arvore, AVL);
		break;		
		case 4:
			printf("Qual o nome do arquivo?\n");
			cin >> nome;
			leDados(nome, arvore);
		break;
		case 5:
			printf("Qual o nome do arquivo que deseja salvar?\n");
			cin >> nome;
			salva(nome, arvore);
		break;
		case 6:
			printf("Qual o nome do arquivo que deseja salvar?\n");
			cin >> nome;
			salvaGrafico(nome, arvore);
		break;
		case 7:
			printf("Qual valor deseja adicionar? ");
			cin >> c;
			
			if(AVL)
				arvore->insereNoAvl(c);
			else
				arvore->insereNo(c);
		break;
		case 8:
			printf("Qual valor deseja remover? ");
			cin >> c;
			
			if(AVL)
				arvore->removeNoAvl(c);
			else
				arvore->removeNo(c);
		break;
		case 9:
			arvore->exclui();
		break;
		case 10:
			arvore->exibeNiveisNos();
		break;
		case 11:
			arvore->exibeAlturaNos();
		break;
		case 12:
			arvore->exibeGrausNos();
		break;
		case 13:
			arvore->exibePaisNos();
		break;
		case 14:
			arvore->exibeEnderecosNos();
		break;
		case 15:
			arvore->exibeFbNos();
		break;
		case 16:
			cout << v.retornaString();
		break;
		case 17:
			arvore->exibePreFixa();
		break;
		case 18:
			arvore->exibePosFixa();
		break;
		case 19:
			arvore->exibeInFixa();
		break;
		case 20:
			printf("A altura da arvore eh %d\n", arvore->getAltura());
		break;
		case 21:
			printf("Ate qual No deseja caminhar? ");
			cin >> c;
			arvore->exibeCaminho(c);
		break;
		case 22:
			printf("A partir de qual No deseja caminhar? ");
			cin >> c;
			arvore->exibeCaminho(c);
		break;
		case 23:
			arvore->exibeCaminhoFolhas();
		break;
	};
}
