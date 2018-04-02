/***************
** ARQUIVO: ArvoreBin.cpp
** GRUPO:
** Marcos Valério de Carvalho Loures - 81827
** Gabriel Vita Silva Franco - 79208
***************/

#ifndef ALTURA_MAXIMA
#define ALTURA_MAXIMA 1000
#endif // ALTURA_MAXIMA

#ifndef INFINITO
#define INFINITO (1<<20)
#endif // INFINITO

#ifndef VISUALIZADOR_H
#define VISUALIZADOR_H

#include <iostream>
#include <string>

#include "ArvoreAvl.h"
#include "No.h"

using namespace std;

class NoAscii {
friend class Visualizador;
protected:
    NoAscii *esq;
    NoAscii *dir;

    // comprimento do no ate seus filhos
    int comprimento;

    int altura;

    int tamRotulo;

    //-1=esquerda, 0=raiz, 1=direita
    int dirPai;

    string rotulo;
};

class Visualizador {
protected:
    ArvoreAvl *arvoreAvl;
    NoAscii *raiz;
    int recuoEsq[ALTURA_MAXIMA];
    int recuoDir[ALTURA_MAXIMA];
    int espaco;

    int imprimeProximo;

    NoAscii *constroiArvoreAscii(No *);
    void constroiArvoreAscii();

    void liberaArvoreAscii(NoAscii *);

    void calculaRecuoEsq(NoAscii *, int, int);
    void calculaRecuoDir(NoAscii *, int, int);

    void calculaComprimentos(NoAscii *);

    void exibeNivel(NoAscii *, int, int);

    void atualiza();

    string retornaNivel(NoAscii *, int, int);

public:
    Visualizador(ArvoreAvl *);
    ~Visualizador();

    void setArvore(ArvoreAvl *);

    void exibe();

    string retornaString();
};

Visualizador::Visualizador(ArvoreAvl *a) {
    this->espaco = 3;
    this->setArvore(a);
    this->constroiArvoreAscii();
}

Visualizador::~Visualizador() {
    this->liberaArvoreAscii(this->raiz);
}

void Visualizador::setArvore(ArvoreAvl *a) {
    this->arvoreAvl = a;
}

void Visualizador::atualiza() {
    this->liberaArvoreAscii(this->raiz);
    this->constroiArvoreAscii();
}

NoAscii *Visualizador::constroiArvoreAscii(No *n) {
    NoAscii * no;

    if (!n) return NULL;

    no = new NoAscii();
    no->esq = constroiArvoreAscii(n->getFilhoEsq());
    no->dir = constroiArvoreAscii(n->getFilhoDir());

    if (no->esq) {
        no->esq->dirPai = -1;
    }

    if (no->dir) {
        no->dir->dirPai = 1;
    }

    no->rotulo = n->getDado();
    no->tamRotulo = no->rotulo.length();

    return no;
}

void Visualizador::constroiArvoreAscii() {
    this->raiz = this->constroiArvoreAscii(this->arvoreAvl->getRaiz());
    if (this->raiz) {
        this->raiz->dirPai = 0;
    }
}

void Visualizador::liberaArvoreAscii(NoAscii *n) {
    if (n) {
        this->liberaArvoreAscii(n->esq);
        this->liberaArvoreAscii(n->dir);
        delete n;
    }
}

void Visualizador::calculaRecuoEsq(NoAscii *n, int x, int y) {
    if (n) {
        int dirEsq = (n->dirPai == -1);
        this->recuoEsq[y] = min(recuoEsq[y], x-((n->tamRotulo-dirEsq)/2));
        if (n->esq) {
            for (int i=1; i <= n->comprimento && y+i < ALTURA_MAXIMA; i++) {
                this->recuoEsq[y+i] = min(this->recuoEsq[y+i], x-i);
            }
        }
        this->calculaRecuoEsq(n->esq, x-n->comprimento-1, y+n->comprimento+1);
        this->calculaRecuoEsq(n->dir, x+n->comprimento+1, y+n->comprimento+1);
    }
}

void Visualizador::calculaRecuoDir(NoAscii *n, int x, int y) {
    if (n) {
        int dirDir = (n->dirPai != -1);
        this->recuoDir[y] = max(this->recuoDir[y], x+((n->tamRotulo-dirDir)/2));
        if (n->dir != NULL) {
            for (int i=1; i <= n->comprimento && y+i < ALTURA_MAXIMA; i++) {
                this->recuoDir[y+i] = max(this->recuoDir[y+i], x+i);
            }
        }
        this->calculaRecuoDir(n->esq, x-n->comprimento-1, y+n->comprimento+1);
        this->calculaRecuoDir(n->dir, x+n->comprimento+1, y+n->comprimento+1);
    }
}

void Visualizador::calculaComprimentos(NoAscii *n) {
    if (n) {
        int h, hmin, i, delta;
        this->calculaComprimentos(n->esq);
        this->calculaComprimentos(n->dir);

        if (n->dir == NULL && n->esq == NULL) {
            n->comprimento = 0;
        } else {
            if (n->esq != NULL) {
                for (i=0; i<n->esq->altura && i < ALTURA_MAXIMA; i++) {
                    this->recuoDir[i] = -INFINITO;
                }
                this->calculaRecuoDir(n->esq, 0, 0);
                hmin = n->esq->altura;
            } else {
                hmin = 0;
            }
            if (n->dir != NULL) {
                for (i=0; i<n->dir->altura && i < ALTURA_MAXIMA; i++) {
                    this->recuoEsq[i] = INFINITO;
                }
                this->calculaRecuoEsq(n->dir, 0, 0);
                hmin = min(n->dir->altura, hmin);
            } else {
                hmin = 0;
            }
            delta = 4;
            for (i=0; i<hmin; i++) {
                delta = max(delta, this->espaco + 1 + this->recuoDir[i] - this->recuoEsq[i]);
            }

            if (((n->esq != NULL && n->esq->altura == 1) || (n->dir != NULL && n->dir->altura == 1)) && delta>4) {
                delta--;
            }

            n->comprimento = ((delta+1)/2) - 1;
        }

        h = 1;
        if (n->esq != NULL) {
            h = max(n->esq->altura + n->comprimento + 1, h);
        }
        if (n->dir != NULL) {
            h = max(n->dir->altura + n->comprimento + 1, h);
        }
        n->altura = h;
    }
}

void Visualizador::exibeNivel(NoAscii *n, int x, int nivel) {
    if (n) {
        int i, dirEsq;
        dirEsq = (n->dirPai == -1);
        if (nivel == 0) {
            for (i=0; i<(x-this->imprimeProximo-((n->tamRotulo-dirEsq)/2)); i++) {
                cout << " ";
            }
            this->imprimeProximo += i;
            cout << n->rotulo;
            this->imprimeProximo += n->tamRotulo;
        }
        else if (n->comprimento >= nivel) {
            if (n->esq != NULL) {
                for (i=0; i<(x-this->imprimeProximo-(nivel)); i++) {
                    cout << " ";
                }
                this->imprimeProximo += i;
                cout << "/";
                this->imprimeProximo++;
            }
            if (n->dir != NULL) {
                for (i=0; i<(x-this->imprimeProximo+(nivel)); i++) {
                    cout << " ";
                }
                this->imprimeProximo += i;
                cout << "\\";
                this->imprimeProximo++;
            }
        } else {
            this->exibeNivel(n->esq, x-n->comprimento-1, nivel-n->comprimento-1);
            this->exibeNivel(n->dir, x+n->comprimento+1, nivel-n->comprimento-1);
        }
    }
}

string Visualizador::retornaNivel(NoAscii *n, int x, int nivel) {
    string s = "";
    if (n) {
        int i, dirEsq;
        dirEsq = (n->dirPai == -1);
        if (nivel == 0) {
            for (i=0; i<(x-this->imprimeProximo-((n->tamRotulo-dirEsq)/2)); i++) {
                s += " ";
            }
            this->imprimeProximo += i;
            s += n->rotulo;
            this->imprimeProximo += n->tamRotulo;
        }
        else if (n->comprimento >= nivel) {
            if (n->esq != NULL) {
                for (i=0; i<(x-this->imprimeProximo-(nivel)); i++) {
                    s += " ";
                }
                this->imprimeProximo += i;
                s += "/";
                this->imprimeProximo++;
            }
            if (n->dir != NULL) {
                for (i=0; i<(x-this->imprimeProximo+(nivel)); i++) {
                    s += " ";
                }
                this->imprimeProximo += i;
                s += "\\";
                this->imprimeProximo++;
            }
        } else {
            s += this->retornaNivel(n->esq, x-n->comprimento-1, nivel-n->comprimento-1);
            s += this->retornaNivel(n->dir, x+n->comprimento+1, nivel-n->comprimento-1);
        }
    }

    return s;
}

void Visualizador::exibe() {
    this->atualiza();
    cout << endl << "Arvore Atual: " << endl;
    if (this->arvoreAvl->getRaiz()) {
        int xmin, i;
        this->calculaComprimentos(this->raiz);
        for (i=0; i<this->raiz->altura && i < ALTURA_MAXIMA; i++) {
            this->recuoEsq[i] = INFINITO;
        }
        this->calculaRecuoEsq(this->raiz, 0, 0);
        xmin = 0;
        for (i = 0; i < this->raiz->altura && i < ALTURA_MAXIMA; i++) {
            xmin = min(xmin, this->recuoEsq[i]);
        }
        for (i = 0; i < this->raiz->altura; i++) {
            this->imprimeProximo = 0;
            this->exibeNivel(this->raiz, -xmin, i);
            cout << endl;
        }
        if (this->raiz->altura >= ALTURA_MAXIMA) {
            cout << "A arvore pode ser impressa incorretamente, pois eh muito alta" << endl;
        }
    } else {
        cout << "Arvore vazia." << endl;
    }

    cout << "Tipo: " << flush;
    if (this->arvoreAvl->ehAvl()) {
        cout << " AVL" << endl;
    } else {
        cout << " ABB comum" << endl;
    }
}

string Visualizador::retornaString() {
    string s = "";
    this->atualiza();
    s += "\n";
    s += "Arvore Atual: \n";
    if (this->arvoreAvl->getRaiz()) {
        int xmin, i;
        this->calculaComprimentos(this->raiz);
        for (i=0; i<this->raiz->altura && i < ALTURA_MAXIMA; i++) {
            this->recuoEsq[i] = INFINITO;
        }
        this->calculaRecuoEsq(this->raiz, 0, 0);
        xmin = 0;
        for (i = 0; i < this->raiz->altura && i < ALTURA_MAXIMA; i++) {
            xmin = min(xmin, this->recuoEsq[i]);
        }
        for (i = 0; i < this->raiz->altura; i++) {
            this->imprimeProximo = 0;
            s += this->retornaNivel(this->raiz, -xmin, i);
            s += "\n";
        }
        if (this->raiz->altura >= ALTURA_MAXIMA) {
            s += "A arvore pode ser impressa incorretamente, pois eh muito alta\n";
        }
    } else {
        s += "Arvore vazia.\n";
    }

    s += "Tipo: ";
    if (this->arvoreAvl->ehAvl()) {
        s += " AVL\n";
    } else {
        s += " ABB comum\n";
    }

    return s;
}

#endif // VISUALIZADOR_H

