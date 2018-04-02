avl: main.o funcoes.o ArvoreAvl.o ArvoreBin.o No.o
	g++ -o avl main.o funcoes.o ArvoreAvl.o ArvoreBin.o No.o

main.o: No.h ArvoreBin.h ArvoreAvl.h Visualizador.h funcoes.h
	g++ -c main.cpp
	
funcoes.o: ArvoreBin.o ArvoreAvl.o No.o
	g++ -c funcoes.cpp

ArvoreAvl.o: ArvoreBin.o ArvoreAvl.cpp ArvoreAvl.h
	g++ -c ArvoreAvl.cpp

ArvoreBin.o: No.o ArvoreBin.h ArvoreBin.cpp
	g++ -c ArvoreBin.cpp

No.o: No.h No.cpp
	g++ -c No.cpp

clean:
	rm avl *.o