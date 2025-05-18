#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <mmsystem.h> 
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

		int plays = 0; //Numero de jogadas
        bool space = false; //Configuração para ter 1 espaço entre as naves

		//Jogadores 1 e 2 e seus nomes e pontuações
		Player player1; 
		Player player2;
		
		//cores para as diferentes naves (https://dev.to/tenry/terminal-colors-in-c-c-3dgc)
		//A -> Caças, B -> Fragatas, C -> Contratorpedeiros, D -> Cruzador, E -> Nave-mãe
		string A[4], B[3], C[2], D[1], E[1];
		
		const int tableWidth = 25;  
    	const int spacing = 15;      
		

		const char* RED = "\033[31m";
		const char* GREEN = "\033[32m";
		const char* YELLOW = "\033[33m";  
		const char* BLUE = "\033[34m";
		const char* MAGENTA = "\033[35m";
		const char* RESET = "\033[0m";  //dá reset para a cor default
		
	public:
		
		CBatalha();
		
		void menu();
		void shipSelection();
		void showTab(int);
		void axisSelect(char, int);
		void writeInTab(int, int);
		bool verifyWin();
		void game();
		bool isPlacementValid(int x, int y, int z, char direction, int shipSize, int tabIndex);
		void placeShip(int x, int y, int z, char direction, int shipSize, int tabIndex, char shipType);
		void showShipInstructions(int shipType);
	
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
                    cout << tab1[j][i][0] << "|"; 
                else
                    cout << tab2[j][i][0] << "|"; 
            }
            cout << endl;
        }
        cout << " +---------------------->" << endl;
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;
        cout << endl;
    }

    if (tabIndex == 3) {
		/*
		Estas primeiras linhas servem apenas para escrever o ínicio da tabela
		O spacing é o espaço entre a tabela e a linha do meio (pode ser aumentado)
		1- Topo
		2- *primeira linha da tabela* | *segunda linha da tabela*
		3- Fim
		Tem alguns cálculos de pixeis aqui pelo meio para melhorar a consistência
		*/

        //Primeiro (X-Z)
		cout << left << setw(tableWidth) << (string("Jogador 1: ") + string(player1.name));
		cout << setw(spacing - 4) << " " << "Jogada: " << plays << setw(spacing - 4) << " ";
		cout << "Jogador 2: " << player2.name << endl;

		cout << left << setw(tableWidth) << (string("Pontuacao: ") + to_string(player1.score));
		cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
		cout << "Pontuacao: " << player2.score << endl;

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

void CBatalha::axisSelect(char axis, int tabIndex){
    char (*currentTab)[10][10] = (tabIndex == 1) ? gameTab1 : gameTab2;
    int firstDigit, secondDigit, temp;
    switch(axis){
        case 'X':
        case 'x':
            cout << " ^" << endl;
            cout << "Y|____________________" << endl;
            for (int i = 9; i >= 0; i--){
                cout << i << "|";
                for (int j = 0; j < 10; j++){
                        cout << currentTab[0][j][i] << "|";
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
                    if (tab1[i][firstDigit][secondDigit] != ' '){
                        gameTab1[i][firstDigit][secondDigit] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab1[i][firstDigit][secondDigit] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
                else{
                    if (tab2[i][firstDigit][secondDigit] != ' '){
                        gameTab2[i][firstDigit][secondDigit] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab2[i][firstDigit][secondDigit] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
            }
            cout << "Press ENTER para continuar..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            break;
        
        case 'Y':
        case 'y':
            cout << " ^" << endl;
            cout << "X|____________________" << endl;
            for (int i = 9; i >= 0; i--){
                cout << i << "|";
                for (int j = 0; j < 10; j++){
                    cout << currentTab[i][0][j] << "|";
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
                    if (tab1[firstDigit][i][secondDigit] != ' '){
                        gameTab1[firstDigit][i][secondDigit] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab1[firstDigit][i][secondDigit] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
                else {
                    if (tab2[firstDigit][i][secondDigit] != ' '){
                        gameTab2[firstDigit][i][secondDigit] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab2[firstDigit][i][secondDigit] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
            }
            cout << "Press ENTER para continuar..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            break;
        
        case 'Z':
        case 'z':
            cout << " ^" << endl;
            cout << "X|____________________" << endl;
            for (int i = 9; i >= 0; i--){
                cout << i << "|";
                for (int j = 0; j < 10; j++){
                    cout << currentTab[i][j][0] << "|";
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
                    if (tab1[firstDigit][secondDigit][i] != ' '){
                        gameTab1[firstDigit][secondDigit][i] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab1[firstDigit][secondDigit][i] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
                else {
                    if (tab2[firstDigit][secondDigit][i] != ' '){
                        gameTab2[firstDigit][secondDigit][i] = 'X';
                        cout << "Foi atinjida uma nave inimiga!" << endl;
                    }
                    else {
                        gameTab2[firstDigit][secondDigit][i] = 'o';
                        cout << "Nada foi atinjido" << endl;
                    }
                }
            }
            cout << "Press ENTER para continuar..." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            break;
            
        default:
            cout << "Tem de inserir um eixo correto! (X, Y ou Z)" << endl;
            cout << "Press ENTER para continuar..." << endl;
            cin.ignore();
            cin.get();
            return;
    }    
}

void CBatalha::showShipInstructions(int shipType) {
    cout << "=== COLOCACAO DE NAVES ===" << endl;
    switch(shipType) {
        case 1:
            //4 Caças de 1 cubo cada
            cout << "Caca (1 cubo) - Total: 4" << endl;     
            cout << "Esta nave ocupa apenas 1 posicao." << endl;
            break;
        case 2:
            //3 Fragatas de 2 cubos cada
            cout << "Fragata (2 cubos em linha) - Total: 3" << endl;    
            cout << "Esta nave pode ser colocada:" << endl;
            cout << "- Horizontalmente no eixo X (X)" << endl;
            cout << "- Horizontalmente no eixo Y (Y)" << endl;
            cout << "- Verticalmente no eixo Z (Z)" << endl;
            break;
        case 3:
            //2 Contratorpedeiros de 3 cubos cada
            cout << "Contratorpedeiro (3 cubos em linha) - Total: 2" << endl;
            cout << "Esta nave pode ser colocada:" << endl;
            cout << "- Horizontalmente no eixo X (X)" << endl;
            cout << "- Horizontalmente no eixo Y (Y)" << endl;
            cout << "- Verticalmente no eixo Z (Z)" << endl;
            break;
        case 4:
            //1 Cruzador de 4 cubos
            cout << "Cruzador (4 cubos em linha) - Total: 1" << endl;
            cout << "Esta nave pode ser colocada:" << endl;
            cout << "- Horizontalmente no eixo X (X)" << endl;
            cout << "- Horizontalmente no eixo Y (Y)" << endl;
            cout << "- Verticalmente no eixo Z (Z)" << endl;
            break;
        case 5:
            //1 Nave mãe de 9 cubos 3x3x3
            cout << "Nave-mae (9 cubos em cubo 3x3x3) - Total: 1" << endl;
            cout << "Esta nave ocupa um cubo de 3x3x3 a partir da posicao escolhida." << endl;
            cout << "Nao necessita de direcao." << endl;
            break;
    }
    cout << "==========================" << endl;
}

bool CBatalha::isPlacementValid(int x, int y, int z, char direction, int shipSize, int tabIndex) {
    char (*currentTab)[10][10] = (tabIndex == 1) ? tab1 : tab2;
    
    // Para caça 
    if (shipSize == 1) {if (currentTab[x][y][z] != ' ') return false; else return true;}

    // Para nave-mãe (cubo 3x3x3)
    if (shipSize == 9) {
        // Verifica se cabe no tabuleiro
        if (x + 2 >= 10 || y + 2 >= 10 || z + 2 >= 10) return false;
        
        // Verifica se não há sobreposição
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (currentTab[x + i][y + j][z + k] != ' ') return false;
                }
            }
        }
        return true;
    }
    
    // Para outras naves (linha)
    switch(direction) {
        case 'X':
        case 'x':
            if (x + shipSize > 10) return false;
            for (int i = 0; i < shipSize; i++) {
                if (currentTab[x + i][y][z] != ' ') return false;   //Não permite colocar a nave se ela sair do tabuleiro
            }
            break;
        case 'Y':
        case 'y':
            if (y + shipSize > 10) return false;
            for (int i = 0; i < shipSize; i++) {
                if (currentTab[x][y + i][z] != ' ') return false;   //Não permite colocar a nave se ela sair do tabuleiro
            }
            break;
        case 'Z':
        case 'z':
            if (z + shipSize > 10) return false;
            for (int i = 0; i < shipSize; i++) {
                if (currentTab[x][y][z + i] != ' ') return false;   //Não permite colocar a nave se ela sair do tabuleiro
            }
            break;
        default:
            return false;
    }
    return true;
}

void CBatalha::placeShip(int x, int y, int z, char direction, int shipSize, int tabIndex, char shipType) {
    //Esta linha é muito importante, ela cria um ponteiro apontado para a tabela atual
    //Em seguida, ela compara com a tabela 1 e 2 para saber qual é a tabela correta e com isso não é preciso usar "tabIndex" a toda a hora
    char (*currentTab)[10][10] = (tabIndex == 1) ? tab1 : tab2;
    
    //Para caça
    if (shipSize == 1) {currentTab[x][y][z] = shipType; return;}

    // Para nave-mãe (cubo 3x3x3)
    if (shipSize == 9) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    currentTab[x + i][y + j][z + k] = shipType;
                }
            }
        }
        return;
    }
    
    // Para outras naves (linha)
    switch(direction) {
        case 'X':
        case 'x':
            for (int i = 0; i < shipSize; i++) {
                currentTab[x + i][y][z] = shipType;
            }
            break;
        case 'Y':
        case 'y':
            for (int i = 0; i < shipSize; i++) {
                currentTab[x][y + i][z] = shipType;
            }
            break;
        case 'Z':
        case 'z':
            for (int i = 0; i < shipSize; i++) {
                currentTab[x][y][z + i] = shipType;
            }
            break;
    }
}

void CBatalha::writeInTab(int type, int tabIndex) {
    int temp, x, y, z;
    char direction = ' ';
    int shipSize;
    char shipType;
    //Existe uma "nave 0" vazia para ser mais fácil associar o tipo de nave ao tamanho dela
    const char* shipNames[] = {"", "Caca", "Fragata", "Contratorpedeiro", "Cruzador", "Nave-mae"};
    
    // Determinar tamanho e tipo da nave
    switch(type) {
        case 1: shipSize = 1; shipType = 'A'; break;
        case 2: shipSize = 2; shipType = 'B'; break;
        case 3: shipSize = 3; shipType = 'C'; break;
        case 4: shipSize = 4; shipType = 'D'; break;
        case 5: shipSize = 9; shipType = 'E'; break;
        default: return;
    }
    
    showShipInstructions(type);
    
    do {
        cout << "Insira as coordenadas para colocar o " << shipNames[type] << " (ex. 000): ";
        cin >> temp;
        
        if (temp > 999 || temp < 0) {
            cout << "O valor deve estar entre 0 e 999!" << endl;
            continue;
        }
        
        x = temp / 100;
        y = (temp / 10) % 10;
        z = temp % 10;
        
        //Para caça não precisa de direção
        if (type == 1) {
            if (isPlacementValid(x, y, z, ' ', shipSize, tabIndex)) {
                placeShip(x, y, z, ' ', shipSize, tabIndex, shipType);
                cout << "Caca colocada com sucesso!" << endl;
                break;
            }
        }
        //Para nave-mãe não precisa de direção
        if (type == 5) {
            if (isPlacementValid(x, y, z, ' ', shipSize, tabIndex)) {
                placeShip(x, y, z, ' ', shipSize, tabIndex, shipType);
                cout << "Nave-mae colocada com sucesso!" << endl;
                break;
            } 
            else {cout << "Posicao invalida! A nave-mae precisa de espaco 3x3x3 livre." << endl;}
        } 
        else {
            // Para outras naves, pedir direção
            cout << "Escolha a direcao (X/Y/Z): ";
            cin >> direction;
            
            if (isPlacementValid(x, y, z, direction, shipSize, tabIndex)) {
                placeShip(x, y, z, direction, shipSize, tabIndex, shipType);
                cout << shipNames[type] << " colocado com sucesso!" << endl;
                break;
            } 
            else {cout << "Posicao invalida! Verifique se ha espaco suficiente e nao ha sobreposicao." << endl;}
        }
    } while (true);
    
    cout << "Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

bool CBatalha::verifyWin(){
	player1.score = player2.score = 0;
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			for (int k = 0; k < 10; k++){
				if (gameTab1[i][j][k] == 'X') player1.score++;
				if (gameTab2[i][j][k] == 'X') player2.score++;	
			}
		}
	}
	//4 caças (4x1) + 3 fragatas (3x2) + 2 contratorpedeiros (2x3) + 1 cruzador (1x4) + 1 nave-mãe (1x9) = 4+6+6+4+9 = 29

	if (player1.score == 29) {
        cout << player1.name << " venceu!" << endl;
        
        // Salvar resultado no histórico
        ofstream outFile("historico.txt", ios::app);
        if (outFile.is_open()) {
            time_t now = time(0);
            char* currentTime = ctime(&now);
            outFile << "Vencedor: " << player1.name << " vs " << player2.name << " - " << currentTime << endl;
            outFile.close();
        }
        return true;
    }
    if (player2.score == 29) {
        cout << player2.name << " venceu!" << endl;
        
        // Salvar resultado no histórico
        ofstream outFile("historico.txt", ios::app);
        if (outFile.is_open()) {
            time_t now = time(0);
            char* currentTime = ctime(&now);
            outFile << "Vencedor: " << player2.name << " vs " << player1.name << " - " << currentTime << endl;
            outFile.close();
        }
        return true;
    }
    return false;
}

void CBatalha::shipSelection(){
	//1 = player1, 2 = player2
	for (int j = 1; j <= 2; j++){
		system ("cls");
		
		if (j == 1){
			cout << "========================================" << endl;
			cout << "|                                      |" << endl;
			cout << "|   Insira o nome do primeiro jogador  |" << endl;
			cout << "|                                      |" << endl;
			cout << "========================================" << endl;
			cout << "Nickname: ";

			cin >> player1.name;
		}
		else {
			cout << "========================================" << endl;
			cout << "|                                      |" << endl;
			cout << "|   Insira o nome do segundo jogador   |" << endl;
			cout << "|                                      |" << endl;
			cout << "========================================" << endl;
			cout << "Nickname: ";

			cin >> player2.name;
		}
		
		system ("cls");
		
		// Colocar 4 caças
		for (int i = 0; i < 4; i++){
			cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
			cout << "Colocando caca " << (i + 1) << " de 4" << endl;
			showTab(j);
			writeInTab(1, j);
			system ("cls");
		}
		
		// Colocar 3 fragatas
		for (int i = 0; i < 3; i++){
			cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
			cout << "Colocando fragata " << (i + 1) << " de 3" << endl;
			showTab(j);
			writeInTab(2, j);
			system ("cls");
		}
		
		// Colocar 2 contratorpedeiros
		for (int i = 0; i < 2; i++){
			cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
			cout << "Colocando contratorpedeiro " << (i + 1) << " de 2" << endl;
			showTab(j);
			writeInTab(3, j);
			system ("cls");	
		}
		
		// Colocar 1 cruzador
		cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
		cout << "Colocando cruzador" << endl;
		showTab(j);
		writeInTab(4, j);
		system ("cls");	
		
		// Colocar 1 nave-mãe
		cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
		cout << "Colocando nave-mae" << endl;
		showTab(j);
		writeInTab(5, j);
		system ("cls");
		
		cout << "Jogador: " << (j == 1 ? player1.name : player2.name) << endl;
		cout << "Todas as naves foram colocadas!" << endl;
		cout << "Pressione ENTER para continuar...";
		cin.ignore();
		cin.get();
        system ("cls");
	}
}

/*
bool CBatalha::spaceConfig(){
    return true;
}*/
void CBatalha::game(){
	srand(time(0));
	int randomNum = (rand() % 2) + 1;
	char axis;
	plays = 0;		//Número de jogadas
	shipSelection();

	do{
		plays++;
		showTab(3);	
		if (randomNum == 1){	//Vez do jogador 1
			cout << player1.name << " e a tua vez de jogar! Escolhe um eixo para lancar o disparo" << endl;
		}
		if (randomNum == 2){	//Vez do jogador 2
			cout << player2.name << " e a tua vez de jogar! Escolhe um eixo para lancar o disparo" << endl;
		}
	
	cin >> axis;

	axisSelect(axis, randomNum);
		if (randomNum == 1) randomNum++;
		if (randomNum == 2) randomNum--;
	}while (!verifyWin());
}
void CBatalha:: menu(){ 
	int optionM, option1, option2, option4, option0;
	bool sair = false;
    space = false;

	do{
		system("cls");
		
		cout << "==========================================" << endl;
		cout << "|             MENU PRINCIPAL             |" << endl;
		cout << "==========================================" << endl;
		cout << "| 1. Iniciar Novo Jogo                   |" << endl;
		cout << "| 2. Configuracoes                       |" << endl;
		cout << "| 3. Historico                           |" << endl;
		cout << "| 4. Como Jogar                          |" << endl;
		cout << "| 5. Musica                              |" << endl;
		cout << "|                                        |" << endl;
		cout << "|                                        |" << endl;
		cout << "| 0. Sair                                |" << endl;
		cout << "==========================================" << endl;
		cout<<"Selecione a opcao:";

        cin >> optionM;        
		if (optionM >= 0 && optionM <= 5) Beep(600, 150);
            
	}while(optionM > 5 || optionM  < 0);
	
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
					cout << "Selecione uma opcao:";
					cin >> option1;

					if (option1 == 1) {Beep(600, 150); game();}
					else if (option1 == 0) { Beep(600, 150); menu();}
						
				}while (option1 > 1 || option1 < 0);
				
			case 2:
				do{
					system ("cls");
					
					cout << "========================================" << endl;
					cout << "|            CONFIGURACOES             |" << endl;
                    cout << "|                                      |" << endl;
					cout << "|  1. Espaco entre naves               |" << endl;
                    cout << "|                                      |" << endl;
                    cout << "|  0. Sair                             |" << endl;
					cout << "========================================" << endl;
                    cout << "Selecione uma opcao:";
                    cin >> option2;

                    if (option2 == 1) {Beep(600, 150); /*config();*/}
                    else if (option0 == 0) {Beep(600, 150); menu();}

				}while(option2 < 0 || option2 > 1);
				
			case 3: 
            do {
                system("cls");
                cout << "==========================================" << endl;
                cout << "|           HISTORICO DOS JOGOS          |" << endl;
                cout << "==========================================" << endl;
                cout << "|  Mostrando os ultimos 100 jogos...     |" << endl;
                cout << "==========================================" << endl;

                const int MAX = 20; 				//meti os 20 para ser mais facil testar (depois podes mudar isto para variável global fora de tudo mesmo no inicio)
                string historico[MAX];  
                int total = 0;

               
                ifstream inFile("historico.txt");
                if (inFile.is_open()) {
                    while (total < MAX && getline(inFile, historico[total])) {			//abre ficheiro para leitura das 100 linhas se nao der da erro
                        total++;
                    }
                    inFile.close();  
                } else {
                    cout << "Nao foi possivel abrir o arquivo de historico." << endl;
                }

               
                for (int i = 0; i < total; i++) {
                    cout << historico[i] << endl; 							//escreve todas as linhas do ficheiro txt
                }

                cout << endl;
                cout << "==========================================" << endl;
                cout << "| Pressione ENTER para voltar ao menu    |" << endl;
                cout << "==========================================" << endl;

                cin.ignore(); 
				cin.get();   
				Beep(600, 150);
				ofstream outFile("historico.txt", ios::trunc);  //limpa o texto e reescreve oque guardou la em cima
                if (outFile.is_open()) {												//faz com que a linha mais "antiga" desapareca
           
                for (int i = 0; i < total; i++) {outFile << historico[i] << endl;}		//imprime os 100 linhas
                outFile.close();
                } else {cout << "Nao foi possivel abrir o arquivo para reescrever." << endl;}

                menu();  

            } while (true);  //fica o texto na tela ate ser imprmido o enter
       
            
			case 4:						
				do{
					system("cls");
					
					cout << "========================================" << endl;
					cout << "|              COMO JOGAR              |" << endl;
					cout << "========================================" << endl;
					cout << "|  Escolher a linguagem de preferencia:|" << endl;
					cout << "|                                      |" << endl;
					cout << "|  1. Portugues                        |" << endl;
					cout << "|  2. Ingles                           |" << endl;
					cout << "|  3. Espanhol                         |" << endl;
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
		cout << "|     acertou ou errou 		        |" << endl;
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
		cout << "|    or miss        	 	            |" << endl;
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
					if (option4 == 3){
				system("cls");
				Beep(600, 150);
	cout << "========================================" << endl;
	cout << "|            COMO JUGAR                |" << endl;
	cout << "========================================" << endl;
	cout << "|  Batalla Naval 3D es un juego por    |" << endl;
	cout << "|  turnos cuyo objetivo es hundir todos|" << endl;
	cout << "|  los barcos enemigos. El juego se    |" << endl;
	cout << "|  desarrolla en un espacio 3D.        |" << endl;
	cout << "|                                      |" << endl;
	cout << "|  REGLAS:                             |" << endl;
	cout << "|  - Coloca tus barcos en el espacio.  |" << endl;
	cout << "|  - En cada turno, ingresa 3 coords.  |" << endl;
	cout << "|    Ejemplo: 2 5 3 (x, y, z)          |" << endl;
	cout << "|  - Se informa si acertaste o fallaste|" << endl;
	cout << "|  - Gana el primero en hundir todos   |" << endl;
	cout << "|    los barcos del oponente.          |" << endl;
	cout << "|                                      |" << endl;
	cout << "========================================" << endl;
	cout << "| Presiona ENTER para volver al menu   |" << endl;
	cout << "========================================" << endl;

			cin.ignore();
            cin.get();    
            Beep(600, 150);
            return menu(); 
					}
					
					if (option4 == 0)
						Beep(600, 150);
					 menu();
					
				}while (option4 >2 || option4 < 0);
			
			case 5: 
    int optionMusic;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "|            MENU DE MUSICA            |" << endl;
        cout << "========================================" << endl;
        cout << "|  Deseja ligar ou desligar a musica?  |" << endl;
        cout << "|                                      |" << endl;
        cout << "|  1. Ligar musica                     |" << endl;
        cout << "|  2. Desligar musica                  |" << endl;
        cout << "|  0. Sair                             |" << endl;
        cout << "|                                      |" << endl;
        cout << "========================================" << endl;
        cout << "Selecione uma opcao: ";
        cin >> optionMusic;
        Beep(600, 150);
        
           if (optionMusic == 1) {
            PlaySound("undertale.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //ativa a musica ou repete																																								
        }
        if (optionMusic == 2) {
            PlaySound(NULL, NULL, 0);  // para a musica
        }
        if (optionMusic == 0) {          // volta para menu com a musica se estiver ligado
            break;  
        }

    } while (optionMusic != 0); 
    return menu(); 

    
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
