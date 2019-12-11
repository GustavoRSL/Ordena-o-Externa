#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "metodos.h"

using namespace std;

void MergeExterno(ifstream &arqEntrada, ofstream &arqSaida) {
    
    ofstream arqB1 ("arqB1.dat",ios::binary);
	ofstream arqB2 ("arqB2.dat",ios::binary);
	 if ( (not arqB1) or (not arqB2) ) {
        cerr << "Arquivos auxiliares nÃ£o puderam ser abertos" << endl;
    }
	
   arqEntrada.seekg(0,ios::beg);
   string linha;
	int cont = 0;
    fflush(stdin);
      if (arqEntrada.is_open()) {
        while(getline(arqEntrada,linha)) {
			cont++;
        }
      }else {
        cout << "Nao foi possivel abrir o arquivo \n";
        remove("arqB1.dat");
		remove("arqB2.dat");
        exit(0);
	   }
    int NumRegistros = --cont;
    int Metade = (NumRegistros/2.0) + 0.5;
    arqEntrada.close();
    arqEntrada.open("Teste.csv");
  
    
    string cabeca;
    getline(arqEntrada,cabeca);
    
    for (int i = 0; i < Metade; i++) {
		getline(arqEntrada,linha);
		arqB1.write((char*) (linha.c_str()),sizeof(char)*linha.length()) << endl;
	}
	for (int i = Metade; i < NumRegistros; i++) {
		getline(arqEntrada,linha);
		arqB2.write((char*) (linha.c_str()),sizeof(char)*linha.length()) << endl;
	}
	//finalizado a primeira etapa
	arqB1.close();
	arqB2.close();
	arqEntrada.close();
	
	 // arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida[2];

    // variÃ¡veis de controle
    int passo = 1;
    bool ida = true;
    bool ultimo[2];

    // laÃ§o principal
    while (passo <= NumRegistros) {
        if (ida) {
            auxEntrada[0].open("arqB1.dat",ios::binary);
			auxEntrada[1].open("arqB2.dat",ios::binary);
			auxSaida[0].open("arqC1.dat",ios::binary);
			auxSaida[1].open("arqC2.dat",ios::binary);
        } else {
            auxEntrada[0].open("arqC1.dat",ios::binary);
			auxEntrada[1].open("arqC2.dat",ios::binary);
			auxSaida[0].open("arqB1.dat",ios::binary);
			auxSaida[1].open("arqB2.dat",ios::binary);
        }

        if ( (not auxEntrada[0]) or (not auxEntrada[1]) or (not auxSaida[0]) or (not auxSaida[1]) ) {
            cerr << "Arquivos auxiliares nÃ£o puderam ser abertos" << endl;
            exit(EXIT_FAILURE);
        }
        // enquanto nÃ£o chegar ao final dos arquivos de entrada
        // vai intercalando os blocos
        while ((not auxEntrada[0].eof()) and (not auxEntrada[1].eof())) {
            ultimo[0] = intercalaBloco(auxEntrada, auxSaida, passo, 0);
            ultimo[1] = intercalaBloco(auxEntrada, auxSaida, passo, 1);
        }
        
        // fecha arquivos para permitir troca (escrita <-> leitura)
        // na prÃ³xima iteraÃ§Ã£o
        auxEntrada[0].close();
        auxEntrada[1].close();
        auxSaida[0].close();
        auxSaida[1].close();

        // prepara prÃ³xima iteraÃ§Ã£o, invertendo arquivos
        // e dobrando tamanho do passo
        ida = not(ida);
        passo *= 2;

    }

    // merge terminado, agora lemos do arquivo auxiliar
    // para arquivo de saÃ­da
    ifstream auxEnt;

    // identifica o arquivo auxiliar com dados ordenados
    if(ida) {
		if(ultimo[0])
			auxEnt.open("arqB1.dat",ios::binary);
		else
			auxEnt.open("arqB2.dat",ios::binary);
	}
	else {
		if(ultimo[0])
			auxEnt.open("arqC1.dat",ios::binary);
		else
			auxEnt.open("arqC2.dat",ios::binary);
	}

    if (not auxEnt) {
        cerr << "Arquivos auxiliar nÃ£o pode ser aberto" << endl;
        exit(EXIT_FAILURE);
    }
    
	arqSaida.write((const char*) cabeca.c_str(),sizeof(char)*cabeca.length()) << endl;
	float Porcentagem = 0;
	float Total = NumRegistros + 1;
	cout << fixed << setprecision(1);
    while (getline(auxEnt,linha) ) {
		Porcentagem++;
		cout << ((Porcentagem/Total) * 100) << "%" << endl;
        arqSaida.write((const char*) linha.c_str(),sizeof(char)*linha.length()) << endl;
    }
    
    cout << "100%" << endl;
    cout << "Programa Finalizado!" << endl;
    

    auxEnt.close();

    // cereja do bolo: apagar arquivos auxiliares
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");

}
