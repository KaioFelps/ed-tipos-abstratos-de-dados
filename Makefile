all:
	if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	clang++ -std=c++20 -c lista_sequencial.cpp -o build/lista_sequencial.o
	clang++ -std=c++20 -c lista_sequencial_main.cpp -o build/lista_sequencial_main.o
	clang++ -std=c++20 build/lista_sequencial.o build/lista_sequencial_main.o -o build/main
	
clean:
	rm -rf build/