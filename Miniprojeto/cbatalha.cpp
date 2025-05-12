#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <windows.h>
//#include "cbatalha.h"
using namespace std;

const unsigned int MAX_NAME_LENGTH = 10;

struct Player {
    int score = 0;
    char name[MAX_NAME_LENGTH];
};

class CBatalha{
	private:
		char tab1[10][10][10];	//Naves do jogador 1
		char tab2[10][10][10];	//Naves do jogador 2
		char gameTab1[10][10][10];	//Jogadas do jogador 1
		char gameTab2[10][10][10];	//Jogadas do jogador 2
		
		//cores para as diferentes naves (https://dev.to/tenry/terminal-colors-in-c-c-3dgc)
		//A -> Caças, B -> Fragatas, C -> Contratorpedeiros, D -> Cruzador, E -> Nave-mãe
		string A[4], B[3], C[2], D[1], E[1];
		
		const int tableWidth = 25;  
    	const int spacing = 8;      
		

		const char* RED = "\033[31m";
		const char* GREEN = "\033[32m";
		const char* YELLOW = "\033[33m";  
		const char* BLUE = "\033[34m";
		const char* MAGENTA = "\033[35m";
		const char* RESET = "\033[0m";  //dá reset para a cor default
		
	public:
		
		CBatalha();
		
		void menu();
		void game();
		void showTab(int);
		void axisSelect(char, int);
		void writeInTab(int, int);
	
};

CBatalha::CBatalha(){
	//inicializar jogo vazio
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				tab1[i][j][k] = ' ';
				tab2[i][j][k] = ' ';
				gameTab1[i][j][k] = ' ';
				gameTab2[i][j][k] = ' ';
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

/*
CRIAR UMA FUNÇÃO QUE MOSTRA A TABELA DUPLA VAZIA

Esta tabela é usada para as jogadas de cada jogador
Compara as jogadas com a tabela original com as naves e atualiza esta tabela com as naves destruídas e com os locais falhados
*/

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
                else 
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
                cout << gameTab1[j][0][i] << "|";
            
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
                cout << gameTab2[j][0][i] << "|";

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
                cout << gameTab1[0][j][i] << "|";
            
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
                cout << gameTab2[0][j][i] << "|";
    
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

void CBatalha:: axisSelect(char axis, int tabIndex){
	int firstDigit, secondDigit, temp;
	//Caso o player selecione X, mostrar o eixo (Y-Z)
	if (axis == 'X' || axis == 'x'){
		cout << " ^" << endl;
		cout << "Y|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				if (tabIndex == 1)
					cout << gameTab1[0][i][j] << "|";
				else
					cout << gameTab2[0][i][j] << "|";
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
			if (tabIndex == 1){
				if (tab1[i][firstDigit][secondDigit] == '+'){
					gameTab1[i][firstDigit][secondDigit] = 'X';
					cout << "Foi atinjida uma nave inimiga!" << endl;
				}
				else {
					gameTab1[i][firstDigit][secondDigit] = 'o';
					cout << "Nada foi atinjido" << endl;
				}
			}
			else{
				if (tab2[i][firstDigit][secondDigit] == '+'){
					gameTab2[i][firstDigit][secondDigit] = 'X';
					cout << "Foi atinjida uma nave inimiga!" << endl;
					}
				else {
					gameTab2[i][firstDigit][secondDigit] = 'o';
					cout << "Nada foi atinjido" << endl;
				}
			}
		}
		system ("cls");
		showTab(3);
	}
	//Caso o player selecione Y, mostrar o eixo (X-Z)
	else if (axis == 'Y' || axis == 'y'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				if (tabIndex == 1)
					cout << gameTab1[i][0][j] << "|";
				else
					cout << gameTab2[i][0][j] << "|";
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
			if (tabIndex == 1){
				if (tab1[firstDigit][i][secondDigit] == '+')
					gameTab1[firstDigit][i][secondDigit] = 'X';
				else
					gameTab1[firstDigit][i][secondDigit] = 'o';
			}
			else {
				if (tab1[firstDigit][i][secondDigit] == '+')
					gameTab2[firstDigit][i][secondDigit] = 'X';
				else
					gameTab2[firstDigit][i][secondDigit] = 'o';
			}
		}
		showTab(3);
	}		
	//Caso o player selecione Z, mostrar o eixo (X-Y)
	else if (axis == 'Z' || axis == 'z'){
		cout << " ^" << endl;
		cout << "X|____________________" << endl;
		for (int i = 9; i >= 0; i--){
			cout << i << "|";
			for (int j = 0; j < 10; j++){
				if (tabIndex == 1)
					cout << gameTab1[i][j][0] << "|";
				else
					cout << gameTab2[i][j][0] << "|";
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
			if (tabIndex == 1){
				if (tab1[firstDigit][secondDigit][i] == '+')
					gameTab1[firstDigit][secondDigit][i] = 'X';
				else
					gameTab1[firstDigit][secondDigit][i] = 'o';
			}
			else {
				if (tab1[firstDigit][secondDigit][i] == '+')
					gameTab2[firstDigit][secondDigit][i] = 'X';
				else
					gameTab2[firstDigit][secondDigit][i] = 'o';
			}
		}
		showTab(3);
	}else{
		cout << "Tem de inserir um eixo correto! (X, Y ou Z)" << endl;
		return;
	}
}

void CBatalha:: writeInTab(int type, int tabIndex){
	int temp, firstDigit, secondDigit, thirdDigit;
	cout << "Insira as coordenadas em que deseja colocar a nave (ex. 000)" << endl;
	cin >> temp;
	
	//pega nas coords por exemplo 000, divide por 100 obtem o primeiro, divide por 10 e vê o resto por 10 obtem o segundo, ve o resto por 10 obtem o terceiro
	firstDigit = temp / 100;
    secondDigit = (temp / 10) % 10;
    thirdDigit = temp % 10;
	
	switch(type){
		case 1:
			if (tabIndex == 1)
				tab1[firstDigit][secondDigit][thirdDigit] = '+';
			else
				tab2[firstDigit][secondDigit][thirdDigit] = '+';
			break;

		case 2:
			if (tabIndex == 1)
				tab1[firstDigit][secondDigit][thirdDigit] = '+';
			else
				tab2[firstDigit][secondDigit][thirdDigit] = '+';
			break;

		case 3:
			if (tabIndex == 1)
				tab1[firstDigit][secondDigit][thirdDigit] = '+';
			else
				tab2[firstDigit][secondDigit][thirdDigit] = '+';
			break;

		case 4:
			if (tabIndex == 1)
				tab1[firstDigit][secondDigit][thirdDigit] = '+';
			else
				tab2[firstDigit][secondDigit][thirdDigit] = '+';
			break;
			
		case 5:
			if (tabIndex == 1)
				tab1[firstDigit][secondDigit][thirdDigit] = '+';
			else
				tab2[firstDigit][secondDigit][thirdDigit] = '+';
			break;
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
cout << "Nickname:";

	cin >> player1.name;
	
	system ("cls");
	
	for (int i = 0; i < 4; i++){	//caça são classe 1
		showTab(1);
		writeInTab(1, 1);	
		system ("cls");
	}
	for (int i = 0; i < 3; i++){	//fragatas são classe 2
		showTab(1);
		writeInTab(2, 1);	
		system ("cls");
	}
	for (int i = 0; i < 2; i++){	//contratorpedeiros são classe 3
		showTab(1);
		writeInTab(3, 1);	
		system ("cls");
	}
	//cruzador são classe 4
		showTab(1);
		writeInTab(4, 1);	
		system ("cls");
	//name-mãe são classe 5
		showTab(1);
		writeInTab(5, 1);	
		system ("cls");
					
cout << "========================================" << endl;
cout << "|                                      |" << endl;
cout << "|   Insira o nome do segundo jogador   |" << endl;
cout << "|                                      |" << endl;
cout << "========================================" << endl;
cout << "Nickname:";

	cin >> player2.name;
		
	system ("cls");
		
	for (int i = 0; i < 4; i++){	//caça são classe 1
		showTab(2);
		writeInTab(1, 2);	
		system ("cls");
	}
	for (int i = 0; i < 3; i++){	//fragatas são classe 2
		showTab(2);
		writeInTab(2, 2);	
		system ("cls");
	}
	for (int i = 0; i < 2; i++){	//contratorpedeiros são classe 3
		showTab(2);
		writeInTab(3, 2);	
		system ("cls");
	}
	//cruzador são classe 4
		showTab(2);
		writeInTab(4, 2);	
		system ("cls");
	//name-mãe são classe 5
		showTab(2);
		writeInTab(5, 2);	
		system ("cls");

	cout << player1.name << " es o primeiro a jogar! Comeca por escolher um eixo para lancar o disparo" << endl;
	cin >> axis;

	axisSelect(axis, 1);
	cin >> axis; 		//teste
	menu();
}
	
void CBatalha:: menu(){ 
	int optionM, option1, option4, option0; //, option2, option3
	bool sair = false;

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
		if (optionM >= 0 && optionM <= 4) 
              Beep(600, 150);
            
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
					if (option1 == 1) {
					Beep(600, 150);
						game();            }
					else if (option1 == 0) {
					Beep(600, 150);
					return menu();
															}
						
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
					Beep(600, 150);
				if (option4 == 1) {
            system("cls");
            Beep(600, 150);
        cout << "========================================" << endl;
		cout << "|              COMO JOGAR              |" << endl;
		cout << "========================================" << endl;
		cout << "|  Batalha Naval 3D  um jogo por turnos|" << endl;
		cout << "|  onde o objetivo e afundar todos os  |" << endl;
		cout << "|  navios do inimigo. O jogo ocorre em |" << endl;
		cout << "|  um espaco 3D.                       |" << endl;
		cout << "|                                      |" << endl;
		cout << "|  REGRAS:                             |" << endl;
		cout << "|  - Posicione seus navios no espaco.  |" << endl;
		cout << "|  - Em cada turno, informe 3 coords.  |" << endl;
		cout << "|    Exemplo: 2 5 3 (x,y,z)            |" << endl;
		cout << "|  - O jogador e informado se acertou  |" << endl;
		cout<< "|     acertou ou errou 		       |" << endl;
		cout << "|  - Vence quem afundar todos os navios|"<< endl;
		cout << "|    do oponente primeiro.             |" << endl;
		cout << "|                                      |" << endl;
		cout << "========================================" << endl;
		cout << "| Pressione ENTER para voltar ao menu  |" << endl;
		cout << "========================================" << endl;

            cin.ignore(); // limpa o enter anterior
            cin.get();    // espera que o utilizador digite qualquer tecla
            Beep(600, 150);
            return menu(); 
        }
					
					if (option4 == 2){
				system("cls");
				Beep(600, 150);
		cout << "========================================" << endl;
		cout << "|               HOW TO PLAY            |" << endl;
		cout << "========================================" << endl;
		cout << "|  3D Battleship is a turn-based game  |" << endl;
		cout << "|  where the goal is to sink all the   |" << endl;
		cout << "|  enemy's ships. The game takes place |" << endl;
		cout << "|  in a 3D space.                      |" << endl;
		cout << "|                                      |" << endl;
		cout << "|  RULES:                              |" << endl;
		cout << "|  - Position your ships in the space. |" << endl;
		cout << "|  - In each turn provide 3 coordinates|" << endl;
		cout << "|    Example: 2 5 3 (x, y, z)          |" << endl;
		cout << "|  - The player is informed if they hit|" << endl;
		cout << "|    or miss        	 	       |" << endl;
		cout << "|  - The winner is the one who sinks   |" << endl;
		cout << "|    all the opponent's ships first.   |" << endl;
		cout << "|                                      |" << endl;
		cout << "========================================" << endl;
		cout << "| Press ENTER to return to the menu    |" << endl;
		cout << "========================================" << endl;
			cin.ignore(); // limpa o enter anterior
            cin.get();    // espera que o utilizador digite qualquer tecla
            Beep(600, 150);
            return menu(); 
					}
					
					if (option4 == 0)
						Beep(600, 150);
					 menu();
					
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
					Beep(600, 150);
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
