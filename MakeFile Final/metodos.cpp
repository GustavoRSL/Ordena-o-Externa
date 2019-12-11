#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct Dado {
	string No;
	string Time;
	string Source;
	string Destination;
	string Protocol;
	string Length;
	string Info;
};

void Menu(){
	cout << "================================================" << endl;
	cout << "==  Informe o nome do arquivo a ser ordenado. ==" << endl;
	cout << "================================================" << endl;
}

bool intercalaBloco(ifstream auxE[2], ofstream auxS[2], int passo, int saida) {
    // consideramos inicialmente que nÃ£o irÃ¡ fazer nenhuma intercalaÃ§Ã£o
    bool intercalou = false;
    Dado dados[2];
    // posiÃ§Ã£o relativa de leitura em cada um dos arquivos
    int pos[2] = {0,0};
    // variÃ¡vel para informar se os dados do arquivo sÃ£o vÃ¡lidos
    // (se foram lidos do arquivo de entrada e ainda nÃ£o gravados
    // no arquivo de saÃ­da)
    bool valido[2] = {false,false};
    
    string dado0,dado1,Linha,Linha2;

    // em cada passo de tamanho n lemos n dados de cada arquivo
    // e fazemos a intercalaÃ§Ã£o parcial em um novo bloco de
    // tamanho 2*n no arquivo de saÃ­da utilizado
    while ( (pos[0] + pos[1]) < (2 * passo) ) {
        // inicialmente verificamos se hÃ¡ dados para ler
        if ( (pos[0] < passo) and (not valido[0]) ) {
            // tentamos ler do arquivo, verificando se a leitura foi vÃ¡lida
            // leitura invÃ¡lida -> final de arquivo
            if(getline(auxE[0],dados[0].No,','))
			{
				getline(auxE[0],dados[0].Time,',');
				getline(auxE[0],dados[0].Source,',');
				getline(auxE[0],dados[0].Destination,',');
				getline(auxE[0],dados[0].Protocol,',');
				getline(auxE[0],dados[0].Length,',');
				getline(auxE[0],dados[0].Info); //Não possui delimitador para pegar o resto do registro
				valido[0] = true; //Conseguiu ler o arquivo
				//String para gravação de acordo no arquivo
				dado0 = dados[0].No +','+ dados[0].Time +','+ dados[0].Source + ',' + dados[0].Destination +
				',' + dados[0].Protocol + ',' + dados[0].Length + ',' + dados[0].Info;
			}
            else {
                // para encerrar o while e nÃ£o entrar no if novamente
                pos[0] = passo;
                // cout << "arq1 terminou" << endl;
            }
        }
        // repetimos o processo para o segundo arquivo
        if (pos[1] < passo and (not valido[1])) {
            // tentamos ler do arquivo, verificando se a leitura foi vÃ¡lida
            // leitura invÃ¡lida -> final de arquivo
            if(getline(auxE[1],dados[1].No,','))
			{
				getline(auxE[1],dados[1].Time,',');
				getline(auxE[1],dados[1].Source,',');
				getline(auxE[1],dados[1].Destination,',');
				getline(auxE[1],dados[1].Protocol,',');
				getline(auxE[1],dados[1].Length,',');
				getline(auxE[1],dados[1].Info);
				valido[1] = true; //Conseguiu ler o arquivo
				dado1 = dados[1].No +','+ dados[1].Time +','+ dados[1].Source + ',' + dados[1].Destination +
				',' + dados[1].Protocol + ',' + dados[1].Length + ',' + dados[1].Info;
            } 
            else {
                // para encerrar o while e nÃ£o entrar no if novamente
                pos[1] = passo;
                // cout << "arq2 terminou" << endl;
            }
        }

        // nesse momento temos dados lidos dos dois arquivos
        // a nÃ£o ser que um (ou ambos) tenham chegado ao fim
			string Variavel0,Variavel1;
			
			Variavel0 = dados[0].Destination;
			Variavel1 = dados[1].Destination;
			
			if(Variavel0 == Variavel1) {
				Variavel0 = dados[0].Protocol;
				Variavel1 = dados[1].Protocol;
			}
			
			
        // 1o caso, os dois dados sÃ£o vÃ¡lidos
        	if ( valido[0] and valido[1] ) {
            // marca que intercalou
            intercalou = true;
            // gravamos o menor valor no arquivo de saida
			if(Variavel0 <= Variavel1 ) 
			{
                auxS[saida].write((const char*) dado0.c_str(),sizeof(char)*dado0.length()) << endl;
                // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
                valido[0] = false;
                pos[0]++;
            } else {
                auxS[saida].write((const char*) dado1.c_str(),sizeof(char)*dado1.length()) << endl;
                // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
                valido[1] = false;
                pos[1]++;
            }
        }
        // 2o caso, apenas o primeiro dado Ã© vÃ¡lido
        else if ( valido[0] ) {
            // marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) dado0.c_str(),sizeof(char)*dado0.length()) << endl;
            // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
            valido[0] = false;
            pos[0]++;
        }
        // 3o caso, apenas o segundo dado Ã© vÃ¡lido
        else if (valido[1] ) {
            // marca que intercalou
            intercalou = true;
            auxS[saida].write((const char*) dado1.c_str(),sizeof(char)*dado1.length()) << endl;
            // dado utilizado nÃ£o Ã© mais vÃ¡lido, avanÃ§a posiÃ§Ã£o
            valido[1] = false;
            pos[1]++;
        }
        // se chegou aqui, termina o while na prÃ³xima iteraÃ§Ã£o
        else {
            // cout << "circulando, circulando... " << endl;
        }
    }
    return intercalou;
}


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
	
    while (getline(auxEnt,linha) ) {
        arqSaida.write((const char*) linha.c_str(),sizeof(char)*linha.length()) << endl;
    }

    auxEnt.close();

    // cereja do bolo: apagar arquivos auxiliares
    remove("arqB1.dat");
    remove("arqB2.dat");
    remove("arqC1.dat");
    remove("arqC2.dat");

}
