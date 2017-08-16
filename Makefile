all: compilar

compilar: main.o paises.o gerais.o
	gcc build/paises.o build/main.o build/gerais.o -o controleestoque.bin `pkg-config --libs mysqlclient`

main.o: src/main.c
	gcc -c src/main.c -o build/main.o

paises.o: src/paises.c src/diretivas_conexao.h
	gcc -c src/paises.c -o build/paises.o

gerais.o: src/gerais.c
	gcc -c src/gerais.c -o build/gerais.o

clean:
	rm -rf build/*.o
