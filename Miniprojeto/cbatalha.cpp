#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
//#include "cbatalha.h"
using namespace std;

const unsigned int MAX_NAME_LENGTH = 10;

struct Player {
    int score = 0;
    char name[MAX_NAME_LENGTH];
};

class CBatalha{
	private:
		char tab1[10][10][10];
		char tab2[10][10][10];
		char emptyTab1[10][10][10];
		char emptyTab2[10][10][10];
		
		//cores para as diferentes naves (https://dev.to/tenry/terminal-colors-in-c-c-3dgc)
		//A -> Caças, B -> Fragatas, C -> Contratorpedeiros, D -> Cruzador, E -> Nave-mãe
		string A[4], B[3], C[2], D[1], E[1];
		
		
		const char* RED = "\033[31m";
		const char* GREEN = "\033[32m";
		const char* YELLOW = "\033[33m";  
		const char* BLUE = "\033[34m";
		const char* MAGENTA = "\033[35m";
		const char* RESET = "\033[0m";  //dá reset para a cor default

		const int tableWidth = 25;  
    	const int spacing = 8;      
		
		
	public:
		
		CBatalha();
		
		void menu();
		void game();
		void showTab(int);
		void axisSelect(char, int);
		void writeInTab(int);
	
};

CBatalha::CBatalha(){
	//inicializar jogo vazio
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				tab1[i][j][k] = ' ';
				tab2[i][j][k] = ' ';
				emptyTab1[i][j][k] = ' ';
				emptyTab2[i][j][k] = ' ';
			}
		}
	}
	//inicializar as cores nas naves
	/*
	for (int i = 3; i >= 0; i--){
		A[i] += RED;
		if (i < 3){
			B[i] += GREEN;
			if (i < 2){
				C[i] += YELLOW;
				if (i < 1){
					D[i] += BLUE;
					E[i] += MAGENTA;
				}
			}
		}
	}
	*/
}

void CBatalha::showTab(int tabIndex) {
    if (tabIndex == 1 || tabIndex == 2) {
        // Imprime a primeira parte da tabela (X-Z)
        cout << " ^" << endl;
        cout << "Z|____________________" << endl;
        for (int i = 9; i >= 0; i--) {
            cout << i << "|";
            for (int j = 0; j < 10; j++) {
                if(tabIndex == 1)
                    cout << tab1[j][0][i] << "|";
                else // tabIndex == 2
                    cout << tab2[j][0][i] << "|";
            }
            cout << endl;
        }
        cout << " +---------------------->" << endl;
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
        cout << endl;
        
        // Imprime a segunda parte da tabela (X-Y)
        cout << " ^" << endl;
        cout << "Y|____________________" << endl;
        for (int i = 9; i >= 0; i--) {
            cout << i << "|";
            for (int j = 0; j < 10; j++) {
                if(tabIndex == 1)
                    cout << tab1[0][j][i] << "|"; 
                else
                    cout << tab2[0][j][i] << "|"; 
            }
            cout << endl;
        }
        cout << " +---------------------->" << endl;
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
        cout << endl;
    }

    if (tabIndex == 3) {
		/*
		Estas primeiras 6 linhas servem apenas para escrever o ínicio da tabela
		O spacing é o espaço entre a tabela e a linha do meio (pode ser aumentado)
		1- Topo
		2- *primeira linha da tabela* | *segunda linha da tabela*
		3- Fim
		Tem alguns cálculos de pixeis aqui pelo meio para melhorar a consistência
		*/

        //Primeiro (X-Z)
        cout << left << setw(tableWidth) << " ^";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " ^" << endl;
        
        cout << left << setw(tableWidth) << "Z|____________________";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << "Z|____________________" << endl;

        for (int i = 9; i >= 0; i--) {
			//Imprime primeira tabela por linhas
            cout << left << i << "|";
            for (int j = 0; j < 10; j++)
                cout << tab1[j][0][i] << "|";
            
			//Escreve o espaço livre entre os números e o verdadeiro fim da tabela
            int leftSize = 3 + 20;
            if (leftSize < tableWidth) {
                cout << setw(tableWidth - leftSize + 1) << " ";
            }
            
            //Linha no meio a dividir
            cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
            
			//Imprime segunda tabela por linhas
            cout << i << "|";
            for (int j = 0; j < 10; j++) 
                cout << tab2[j][0][i] << "|";

            cout << endl;
        }
        
		//Imprime segunda parte das tabelas (finalizar a tabela)
        cout << left << setw(tableWidth) << " +---------------------->";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " +---------------------->" << endl;
        
        cout << left << setw(tableWidth) << " |0|1|2|3|4|5|6|7|8|9|  X";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
        
		//1 linha de espaço entre a tabela X-Z e a X-Y
        cout << left << setw(tableWidth) << " ";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " " << endl;
        
		//Segundo (X-Y)
        cout << left << setw(tableWidth) << " ^";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " ^" << endl;
        
        cout << left << setw(tableWidth) << "Y|____________________";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << "Y|____________________" << endl;

        for (int i = 9; i >= 0; i--) {
			//Imprime primeira tabela por linhas
            cout << left << i << "|";
            for (int j = 0; j < 10; j++) 
                cout << tab1[0][j][i] << "|";
            
			//Escreve o espaço livre entre os números e o verdadeiro fim da tabela
            int leftSize = 3 + 20; 
            if (leftSize < tableWidth) {
                cout << setw(tableWidth - leftSize + 1) << " ";
            }
            
            //Linha no meio
            cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
            
			//Imprime segunda tabela por linhas
            cout << i << "|";
            for (int j = 0; j < 10; j++) 
                cout << tab2[0][j][i] << "|";
    
            cout << endl;
        }
		
		//Imprime segunda parte das tabelas (finalizar a tabela)
        cout << left << setw(tableWidth) << " +---------------------->";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " +---------------------->" << endl;
        
        cout << left << setw(tableWidth) << " |0|1|2|3|4|5|6|7|8|9|  X";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
    }
}

void CBatalha:: axisSelect(char axis, int player){
	int firstDigit, secondDigit, temp;
	//Caso o player selecione X, mostrar o eixo (Y-Z)
	if (axis == 'X' || axis == 'x'){
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab[0][i][j] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
		cout << endl;
		cout << "Em seguida escolhe uma coordenada para atacar (ex.00)" << endl;

		cin >> temp;
		firstDigit = temp / 10;
		secondDigit = temp % 10;
		
		for (int i = 0; i < 10; i++){
			if (tab1[i][firstDigit][secondDigit] == '+')
				tab1[i][firstDigit][secondDigit] = 'X';
			else
				tab1[i][firstDigit][secondDigit] = 'o';
		}
		showTab(1);
	}
	//Caso o player selecione Y, mostrar o eixo (X-Z)
	else if (axis == 'Y' || axis == 'y'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab[i][0][j] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
		cout << endl;
		cout << "Em seguida escolhe uma coordenada para atacar (ex.00)" << endl;

		cin >> temp;
		firstDigit = temp / 10;
		secondDigit = temp % 10;

		for (int i = 0; i < 10; i++){
			if (tab1[firstDigit][secondDigit][i] == '+')
				tab1[firstDigit][secondDigit][i] = 'X';
			else
				tab1[firstDigit][secondDigit][i] = 'o';
		}
		showTab(1);
	}		
	//Caso o player selecione Z, mostrar o eixo (X-Y)
	else if (axis == 'Z' || axis == 'z'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab[i][j][0] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Y" << endl;
		cout << endl;
		cout << "Em seguida escolhe uma coordenada para atacar (ex.00)" << endl;

		cin >> temp;
		firstDigit = temp / 10;
		secondDigit = temp % 10;

		for (int i = 0; i < 10; i++){
			if (tab1[firstDigit][secondDigit][i] == '+')
				tab1[firstDigit][secondDigit][i] = 'X';
			else
				tab1[firstDigit][secondDigit][i] = 'o';
		}
		showTab(1);
	}else{
		cout << "Tem de inserir um eixo correto! (X, Y ou Z)" << endl;
		return;
	}
}

void CBatalha:: writeInTab(int type){
	int temp, firstDigit, secondDigit, thirdDigit;
	cout << "Insira as coordenadas em que deseja colocar a nave (ex. 000)" << endl;
	cin >> temp;
	
	//pega nas coords por exemplo 000, divide por 100 obtem o primeiro, divide por 10 e vê o resto por 10 obtem o segundo, ve o resto por 10 obtem o terceiro
	firstDigit = temp / 100;
    secondDigit = (temp / 10) % 10;
    thirdDigit = temp % 10;
	
	switch(type){
		case 1:
			tab1[firstDigit][secondDigit][thirdDigit] = '+';
		case 2:
			tab1[firstDigit][secondDigit][thirdDigit] = '+';
		case 3:
			tab1[firstDigit][secondDigit][thirdDigit] = '+';
		case 4:
			tab1[firstDigit][secondDigit][thirdDigit] = '+';
		case 5:
			tab1[firstDigit][secondDigit][thirdDigit] = '+';
	}
}
	

void CBatalha:: game(){
	Player player1;
	Player player2;
	
	char axis;
	
	system ("cls");
		
cout << "========================================" << endl;
cout << "|                                      |" << endl;
cout << "|   Insira o nome do primeiro jogador  |" << endl;
cout << "|                                      |" << endl;
cout << "========================================" << endl;
cout<<"Nick:";

	cin >> player1.name;
	
	system ("cls");
	
	for (int i = 0; i < 4; i++){	//caça são classe 1
		showTab(1);
		writeInTab(1);	
		system ("cls");
	}
	for (int i = 0; i < 3; i++){	//fragatas são classe 2
		showTab(1);
		writeInTab(2);	
		system ("cls");
	}
	for (int i = 0; i < 2; i++){	//contratorpedeiros são classe 3
		showTab(1);
		writeInTab(3);	
		system ("cls");
	}
	//cruzador são classe 4
		showTab(1);
		writeInTab(4);	
		system ("cls");
	//name-mãe são classe 5
		showTab(1);
		writeInTab(5);	
		system ("cls");
					
cout << "========================================" << endl;
cout << "|                                      |" << endl;
cout << "|   Insira o nome do segundo jogador   |" << endl;
cout << "|                                      |" << endl;
cout << "========================================" << endl;
cout<<"Nick:";

	cin >> player2.name;
		
	system ("cls");
		
	for (int i = 0; i < 4; i++){	//caça são classe 1
		showTab(2);
		writeInTab(1);	
		system ("cls");
	}
	for (int i = 0; i < 3; i++){	//fragatas são classe 2
		showTab(2);
		writeInTab(2);	
		system ("cls");
	}
	for (int i = 0; i < 2; i++){	//contratorpedeiros são classe 3
		showTab(2);
		writeInTab(3);	
		system ("cls");
	}
	//cruzador são classe 4
		showTab(2);
		writeInTab(4);	
		system ("cls");
	//name-mãe são classe 5
		showTab(2);
		writeInTab(5);	
		system ("cls");

	cout << player1.name << " es o primeiro a jogar! Comeca por escolher um eixo para lancar o disparo" << endl;
	cin >> axis;

	axisSelect(axis, 1);
}
	
void CBatalha:: menu(){ 
	int optionM, option1, option4, option0; //, option2, option3
	bool sair = false;
	showTab(3);
	cin >> optionM;
	do{
		system("cls");
		
		cout << "==========================================" << endl;
		cout << "|             MENU PRINCIPAL             |" << endl;
		cout << "==========================================" << endl;
		cout << "| 1. Iniciar Novo Jogo                   |" << endl;
		cout << "| 2. Configuracoes                       |" << endl;
		cout << "| 3. Historico                           |" << endl;
		cout << "| 4. Como Jogar                          |" << endl;
		cout << "|                                        |" << endl;
		cout << "|                                        |" << endl;
		cout << "| 0. Sair                                |" << endl;
		cout << "==========================================" << endl;
		cout<<"Selecione a opcao:";

        cin >> optionM;        
			
	}while(optionM > 4 || optionM  < 0);
	
	do{
		switch(optionM){
			case 1:
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "|              NOVO JOGO               |" << endl;
					cout << "========================================" << endl;
					cout << "|   Comecar novo jogo?                 |" << endl;
					cout << "|                                      |" << endl;
					cout << "|   1. Sim                             |" << endl;
					cout << "|   0. Nao                             |" << endl;
					cout << "|                                      |" << endl;
					cout << "========================================" << endl;
					cout << "Selecione a opcao:";
					cin >> option1;
					
					if (option1 == 1)
						game();
					if (option1 == 0)
						menu();
						
				}while (option1 > 1 || option1 < 0);
				
			/*case 2:
				do{
					system ("cls");
					
					cout << "========================================" << endl;
					cout << "
					cout << endl;
					cout << "========================================" << endl;
				}while();
				
			case 3:
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "
					cout << endl;
					cout << "========================================" << endl;
				}while();
			*/	
			case 4:						//ou adicionar mais linguas ou alguma forma de traduzir um texto fornecido
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "|              COMO JOGAR              |" << endl;
					cout << "========================================" << endl;
					cout << "|  Escolher a linguagem de preferencia:|" << endl;
					cout << "|                                      |" << endl;
					cout << "|  1. Portugues                        |" << endl;
					cout << "|  2. Ingles                           |" << endl;
					cout << "|                                      |" << endl;
					cout << "|  0. Sair                             |" << endl;
					cout << "|                                      |" << endl;
					cout << "========================================" << endl;
					cout << "Selecione uma opcao:";

					
					cin >> option4;
					
					if (option4 == 1){
					}
					
					if (option4 == 2){
					}
					
					if (option4 == 0) menu();
					
				}while (option4 >2 || option4 < 0);
				
			case 0:							//criar uma opção se ainda houver um jogo aberto
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "|                SAIR                  |" << endl;
					cout << "========================================" << endl;
					cout << "|  Tem certeza?                        |" << endl;
					cout << "|                                      |" << endl;
					cout << "|  1. Sim                              |" << endl;
					cout << "|  0. Nao                              |" << endl;
					cout << "|                                      |" << endl;
					cout << "========================================" << endl;
					cout << "Selecione uma opcao:";

					
					cin >> option0;
					
					if (option0 == 1){
						system("cls");
						
						cout << "========================================" << endl;
						cout << "|                                      |" << endl;
						cout << "|             A ENCERRAR...            |" << endl;
						cout << "|                                      |" << endl;
						cout << "========================================" << endl;

						sair = true;
						break;
					}
					
					if (option0 == 0) menu();
					break;
					
				}while(option0 > 1 || option0 < 0);
				break;
				
		system("cls");
		}	
	}while(!sair);
}

int main() {
    CBatalha START;

    START.menu();

    return 0;
}