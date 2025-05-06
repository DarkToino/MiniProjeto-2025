#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
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
		
		//cores para as diferentes naves (https://dev.to/tenry/terminal-colors-in-c-c-3dgc)
		//A -> Caças, B -> Fragatas, C -> Contratorpedeiros, D -> Cruzador, E -> Nave-mãe
		string A[4], B[3], C[2], D[1], E[1];
		
		
		const char* RED = "\033[31m";
		const char* GREEN = "\033[32m";
		const char* YELLOW = "\033[33m";  
		const char* BLUE = "\033[34m";
		const char* MAGENTA = "\033[35m";
		const char* RESET = "\033[0m";  //dá reset para a cor default

		const int terminal_width = 80;
		const int left_width = 30;
		const int center_pos = terminal_width / 2;
		const int right_pos = center_pos + 2;
		
		
	public:
		
		CBatalha();
		
		void menu();
		void game();
		void showTab(int);
		void axisSelect(char);
		void writeInTab(int);
	
};

CBatalha::CBatalha(){
	//inicializar jogo vazio
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				tab1[i][j][k] = ' ';
				tab2[i][j][k] = ' ';
			}
		}
	}
	//inicializar as cores nas naves
	/*
	for (int i = 3; i >= 0; i++){
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

void CBatalha:: showTab(int a){
	if (a == 1){
		//imprime a primeira parte da tabela
		cout << " ^" << endl;
		cout << "Z|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[j][0][i] << "|";
			}
			cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
		//imprime a segunda parte da tabela
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[0][j][i] << "|";
			}
			cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
	}
	if (a == 2){
		//imprime a primeira parte da tabela
		cout << " ^" << endl;
		cout << "Z|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab2[j][0][i] << "|";
			}
			cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
		//imprime a segunda parte da tabela
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab2[0][j][i] << "|";
			}
			cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
	}
	if (a == 3){
		//imprime a primeira parte da tabela
		cout << " ^" << endl;
		cout << left << setw(left_width) << "Z|____________________" 
			 << setw(center_ - left_width) << " | "
			 << right << setw(right_pos - center_pos - 1) << "Z|____________________" << endl; 
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[j][0][i] << "|";
			}
			cout << endl;
		}
		cout << setw(center_ - left_width) << " | "
			 << right << setw(right_pos - center_pos - 1) << tab2[j][0][i] << "|";
			 
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
		//imprime a segunda parte da tabela
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[0][j][i] << "|";
			}
			cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
		cout << endl;
	}	
}

void CBatalha:: axisSelect(char axis){
	//Caso o player selecione X, mostrar o eixo (Y-Z)
	if (axis == 'X' || axis == 'x'){
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[0][i][j] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
		cout << endl;
	}
	//Caso o player selecione Y, mostrar o eixo (X-Z)
	else if (axis == 'Y' || axis == 'y'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[i][0][j] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
		cout << endl;
	}		
	//Caso o player selecione Z, mostrar o eixo (X-Y)
	else if (axis == 'Z' || axis == 'z'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				cout << tab1[i][j][0] << "|";
			}
		cout << endl;
		}
		cout << " +---------------------->" << endl;
		cout << " |0|1|2|3|4|5|6|7|8|9|  Y" << endl;
		cout << endl;
	}else{
		cout << "Tem de inserir um eixo correto! (X, Y ou Z)" << endl;
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
			tab1[firstDigit][secondDigit][thirdDigit] = 'X';
		case 2:
			tab1[firstDigit][secondDigit][thirdDigit] = 'X';
		case 3:
			tab1[firstDigit][secondDigit][thirdDigit] = 'X';
		case 4:
			tab1[firstDigit][secondDigit][thirdDigit] = 'X';
		case 5:
			tab1[firstDigit][secondDigit][thirdDigit] = 'X';
	}
}
	

void CBatalha:: game(){
	Player player1;
	Player player2;
	
	//a char axis;
	
	system ("cls");
		
	cout << "========================================" << endl;
	cout << endl;
	cout << "   Insira o nome do primeiro jogador    " << endl;
	cout << endl;
	cout << "========================================" << endl;
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
	cout << endl;
	cout << "    Insira o nome do segundo jogador    " << endl;
	cout << endl;
	cout << "========================================" << endl;
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
}
	
void CBatalha:: menu(){ 
	int optionM, option1, option4, option0; //, option2, option3
	bool sair = false;
	do{
		system("cls");
		
		cout << "========================================" << endl;
        cout << "                  MENU                  " << endl;
        cout << endl;
        cout << "1. Novo jogo" << endl;
        cout << "2. Configuracao" << endl;
        cout << "3. Historico" << endl;
        cout << "4. Como jogar" << endl;
        cout << endl;
        cout << "0. Sair" << endl;
        cout << endl;
        cout << "========================================" << endl;

        cin >> optionM;        
			
	}while(optionM > 4 || optionM  < 0);
	
	do{
		switch(optionM){
			case 1:
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "                NOVO JOGO               " << endl;
					cout << endl;
					cout << "Comecar novo jogo?" << endl;
					cout << "1. Sim" << endl;
					cout << "0. Nao" << endl;
					cout << endl;
					cout << "========================================" << endl;
					
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
					cout << "               COMO JOGAR               " << endl;
					cout << endl;
					cout << "Escolher a linguagem de preferencia:" << endl;
					cout << "1. Portugues" << endl;
					cout << "2. Ingles" << endl;
					cout << endl;
					cout << "0. Sair" << endl;
					cout << endl;
					cout << "========================================" << endl;
					
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
					cout << "                  SAIR                  " << endl;
					cout << endl;
					cout << "Tem a certeza?" << endl;
					cout << "1. Sim" << endl;
					cout << "0. Nao" << endl;
					cout << endl;
					cout << "========================================" << endl;
					
					cin >> option0;
					
					if (option0 == 1){
						system("cls");
						
						cout << "========================================" << endl;
						cout << endl;
						cout << "              A encerrar                " << endl;
						cout << endl;
						cout << "========================================" << endl;
						sair = true;
						break;
					}
					
					if (option0 == 0) menu();
					
				}while(option0 > 1 || option0 < 0);
				
		system("cls");
		}	
	}while(!sair);
}

int main() {
    CBatalha START;

    START.menu();

    return 0;
}
