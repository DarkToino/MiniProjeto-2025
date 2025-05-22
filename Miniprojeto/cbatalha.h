#ifndef CBATALHA_H
#define CBATALHA_H

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

const unsigned int MAX_NAME_LENGTH = 10;
const int MAX = 100;

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

		bool pcGame = false;
		int plays = 0; //Numero de jogadas
        bool needSpace = false; //Configuração para ter 1 espaço entre as naves
        int randomShip = 2;

		//Jogadores 1 e 2 e seus nomes e pontuações
		Player player1; 
		Player player2;
		
		//cores para as diferentes naves (https://dev.to/tenry/terminal-colors-in-c-c-3dgc)
		//A -> Caças, B -> Fragatas, C -> Contratorpedeiros, D -> Cruzador, E -> Nave-mãe
		string A[4], B[3], C[2], D[1], E[1];

        //Cores para as naves
        const char* A_color = "\033[32m"; //Verde
        const char* B_color = "\033[33m"; //Amarelo
        const char* C_color = "\033[34m"; //Azul
        const char* D_color = "\033[35m"; //Magenta
        const char* E_color = "\033[36m"; //Cyan
		
		const int tableWidth = 25;  
    	const int spacing = 15;      
		
        //Cores para o menu
		const char* RED = "\033[31m";
		const char* GREEN = "\033[32m";
		const char* YELLOW = "\033[33m";  
		const char* BLUE = "\033[34m";
		const char* MAGENTA = "\033[35m";
        const char* CYAN = "\033[36m";
		const char* RESET = "\033[0m";  //dá reset para a cor default
		const char* corAtual = RESET;
		
	public:
		
		CBatalha();
		void showTab(int);
		void axisSelect(char, int);
		void showShipInstructions(int);
		bool isPlacementValid(int, int, int, char, int, int);
		void placeShip(int, int, int, char, int, int, char);
		void writeInTab(int, int);
		void writeInTab2(int, int);
		void pcGameplay();
		bool verifyWin();
		void shipSelection();
		void game();
		void menu();	
	
};

#endif
