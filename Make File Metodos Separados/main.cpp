#include <iostream>
#include <fstream>
#include "metodos.h"

using namespace std;

int main(){
	Menu();
	
	string NomeArq;
	cin >> NomeArq;
	
	ifstream ArqEntrada(NomeArq.c_str());
	ofstream ArqSaida("Ordenado.bin");
	
	MergeExterno(ArqEntrada,ArqSaida);
	
	ArqEntrada.close();
	ArqSaida.close();
	
	return 0;
}
