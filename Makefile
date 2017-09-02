all: compilar

compilar: main.o paises.o gerais.o produtos.o
	gcc build/paises.o build/main.o build/gerais.o build/produtos.o -o controleestoque.bin `mysql_config --libs`

main.o: src/main.c
	gcc -c src/main.c -o build/main.o

paises.o: src/paises.c src/diretivas_conexao.h
	gcc -c src/paises.c -o build/paises.o
	
produtos.o: src/produtos.c src/diretivas_conexao.h
	gcc -c src/produtos.c -o build/produtos.o

gerais.o: src/gerais.c
	gcc -c src/gerais.c -o build/gerais.o	

clean:
	rm -rf build/*.o fasdfa
