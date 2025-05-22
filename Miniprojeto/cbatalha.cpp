#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include "cbatalha.h" 
using namespace std;

CBatalha::CBatalha() {
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

        // Imprime a terceira parte da tabela (Y-Z)
        cout << " ^" << endl;
        cout << "Y|____________________" << endl;
        for (int i = 9; i >= 0; i--) {
            cout << i << "|";
            for (int j = 0; j < 10; j++) {
                if(tabIndex == 1)
                    cout << tab1[0][i][j] << "|"; 
                else
                    cout << tab2[0][i][j] << "|"; 
            }
            cout << endl;
        }
        cout << " +---------------------->" << endl;
        cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
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
                if (gameTab1[j][0][i] == 'A') {cout << A_color << gameTab1[j][0][i] << "|";}
                else if (gameTab1[j][0][i] == 'B') {cout << B_color << gameTab1[j][0][i] << "|";}
                else if (gameTab1[j][0][i] == 'C') {cout << C_color << gameTab1[j][0][i] << "|";}
                else if (gameTab1[j][0][i] == 'D') {cout << D_color << gameTab1[j][0][i] << "|";}
                else if (gameTab1[j][0][i] == 'E') {cout << E_color << gameTab1[j][0][i] << "|";}
                else {cout << gameTab1[j][0][i] << "|";}
            
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
                if (gameTab2[j][0][i] == 'A') {cout << A_color << gameTab2[j][0][i] << "|";}
                else if (gameTab2[j][0][i] == 'B') {cout << B_color << gameTab2[j][0][i] << "|";}
                else if (gameTab2[j][0][i] == 'C') {cout << C_color << gameTab2[j][0][i] << "|";}
                else if (gameTab2[j][0][i] == 'D') {cout << D_color << gameTab2[j][0][i] << "|";}
                else if (gameTab2[j][0][i] == 'E') {cout << E_color << gameTab2[j][0][i] << "|";}
                else {cout << gameTab2[j][0][i] << "|";}

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
                if (gameTab1[j][i][0] == 'A') {cout << A_color << gameTab1[j][i][0] << "|";}
                else if (gameTab1[j][i][0] == 'B') {cout << B_color << gameTab1[j][i][0] << "|";}
                else if (gameTab1[j][i][0] == 'C') {cout << C_color << gameTab1[j][i][0] << "|";}
                else if (gameTab1[j][i][0] == 'D') {cout << D_color << gameTab1[j][i][0] << "|";}
                else if (gameTab1[j][i][0] == 'E') {cout << E_color << gameTab1[j][i][0] << "|";}
                else {cout << gameTab1[j][i][0] << "|";}
            
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
                if (gameTab2[j][i][0] == 'A') {cout << A_color << gameTab2[j][i][0] << "|";}
                else if (gameTab2[j][i][0] == 'B') {cout << B_color << gameTab2[j][i][0] << "|";}
                else if (gameTab2[j][i][0] == 'C') {cout << C_color << gameTab2[j][i][0] << "|";}
                else if (gameTab2[j][i][0] == 'D') {cout << D_color << gameTab2[j][i][0] << "|";}
                else if (gameTab2[j][i][0] == 'E') {cout << E_color << gameTab2[j][i][0] << "|";}
                else {cout << gameTab2[j][i][0] << "|";}
    
            cout << endl;
        }
		
		//Imprime segunda parte das tabelas (finalizar a tabela)
        cout << left << setw(tableWidth) << " +---------------------->";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " +---------------------->" << endl;
        
        cout << left << setw(tableWidth) << " |0|1|2|3|4|5|6|7|8|9|  X";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " |0|1|2|3|4|5|6|7|8|9|  X" << endl;

        cout << left << setw(tableWidth) << " ";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " " << endl;

        //Terceiro (Y-Z)
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
                if (gameTab1[0][i][j] == 'A') {cout << A_color << gameTab1[0][i][j] << "|";}
                else if (gameTab1[0][i][j] == 'B') {cout << B_color << gameTab1[0][i][j] << "|";}
                else if (gameTab1[0][i][j] == 'C') {cout << C_color << gameTab1[0][i][j] << "|";}
                else if (gameTab1[0][i][j] == 'D') {cout << D_color << gameTab1[0][i][j] << "|";}
                else if (gameTab1[0][i][j] == 'E') {cout << E_color << gameTab1[0][i][j] << "|";}
                else {cout << gameTab1[0][i][j] << "|";}
            
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
                if (gameTab2[0][i][j] == 'A') {cout << A_color << gameTab2[0][i][j] << "|";}
                else if (gameTab2[0][i][j] == 'B') {cout << B_color << gameTab2[0][i][j] << "|";}
                else if (gameTab2[0][i][j] == 'C') {cout << C_color << gameTab2[0][i][j] << "|";}
                else if (gameTab2[0][i][j] == 'D') {cout << D_color << gameTab2[0][i][j] << "|";}
                else if (gameTab2[0][i][j] == 'E') {cout << E_color << gameTab2[0][i][j] << "|";}
                else {cout << gameTab2[0][i][j] << "|";}
    
            cout << endl;
        }
		
		//Imprime segunda parte das tabelas (finalizar a tabela)
        cout << left << setw(tableWidth) << " +---------------------->";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " +---------------------->" << endl;
        
        cout << left << setw(tableWidth) << " |0|1|2|3|4|5|6|7|8|9|  Z";
        cout << setw(spacing) << " " << "|" << setw(spacing) << " ";
        cout << " |0|1|2|3|4|5|6|7|8|9|  Z" << endl;
    }
}

void CBatalha::axisSelect(char axis, int tabIndex){
    char (*currentTab)[10][10] = (tabIndex == 1) ? gameTab1 : gameTab2;
    char (*playTab)[10][10] = (tabIndex == 1) ? tab1 : tab2;
    int firstDigit, secondDigit, temp;
    bool hit = false;
    const char* shipNames[] = {"", "Caca", "Fragata", "Contratorpedeiro", "Cruzador", "Nave-mae"};

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
        
           // Verificar todas as camadas para encontrar um navio
            for (int i = 0; i < 10; i++){
                char cellValue = playTab[i][firstDigit][secondDigit];
                
                if (cellValue == 'A') {currentTab[i][firstDigit][secondDigit] = 'X'; hit = true; temp = 1;}
                else if (cellValue == 'B') {currentTab[i][firstDigit][secondDigit] = 'X'; hit = true; temp = 2;}
                else if (cellValue == 'C') {currentTab[i][firstDigit][secondDigit] = 'X'; hit = true; temp = 3;}
                else if (cellValue == 'D') {currentTab[i][firstDigit][secondDigit] = 'X'; hit = true; temp = 4;}
                else if (cellValue == 'E') {currentTab[i][firstDigit][secondDigit] = 'X'; hit = true; temp = 5;}
                else {currentTab[i][firstDigit][secondDigit] = 'o';}
            }
            
            if (hit) {cout << "Foi atinjida uma "<< shipNames[temp] << " inimiga!" << endl;}
            else {cout << "Nada foi atinjido" << endl;}

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

            // Verificar todas as camadas para encontrar um navio
            for (int i = 0; i < 10; i++){
                char cellValue = playTab[firstDigit][i][secondDigit];
                
                if (cellValue == 'A') {currentTab[firstDigit][i][secondDigit] = 'X'; hit = true; temp = 1;}
                else if (cellValue == 'B') {currentTab[firstDigit][i][secondDigit] = 'X'; hit = true; temp = 2;}
                else if (cellValue == 'C') {currentTab[firstDigit][i][secondDigit] = 'X'; hit = true; temp = 3;}
                else if (cellValue == 'D') {currentTab[firstDigit][i][secondDigit] = 'X'; hit = true; temp = 4;}
                else if (cellValue == 'E') {currentTab[firstDigit][i][secondDigit] = 'X'; hit = true; temp = 5;}
                else {currentTab[firstDigit][i][secondDigit] = 'o';}
            }

            if (hit) {cout << "Foi atinjida uma "<< shipNames[temp] << " inimiga!" << endl;}
            else {cout << "Nada foi atinjido" << endl;}

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
            
            // Verificar todas as camadas para encontrar um navio
            for (int i = 0; i < 10; i++){
                char cellValue = playTab[firstDigit][secondDigit][i];
                
                if (cellValue == 'A') {currentTab[firstDigit][secondDigit][i] = 'X'; hit = true; temp = 1;}
                else if (cellValue == 'B') {currentTab[firstDigit][secondDigit][i] = 'X'; hit = true; temp = 2;}
                else if (cellValue == 'C') {currentTab[firstDigit][secondDigit][i] = 'X'; hit = true; temp = 3;}
                else if (cellValue == 'D') {currentTab[firstDigit][secondDigit][i] = 'X'; hit = true; temp = 4;}
                else if (cellValue == 'E') {currentTab[firstDigit][secondDigit][i] = 'X'; hit = true; temp = 5;}
                else {currentTab[firstDigit][secondDigit][i] = 'o';}
            }
            
            if (hit) {cout << "Foi atinjida uma "<< shipNames[temp] << " inimiga!" << endl;}
            else {cout << "Nada foi atinjido" << endl;}

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

    // Caça
    if (shipSize == 1) {
        if (currentTab[x][y][z] != ' ') return false;

        if (needSpace) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {								//ve a area ao redor
                    for (int dz = -1; dz <= 1; dz++) {
                        int nx = x + dx, ny = y + dy, nz = z + dz;
                        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && nz >= 0 && nz < 10) {
                            if (currentTab[nx][ny][nz] != ' ') return false;
                        }
                    }
                }																	//a area ao redor e vazia
            }
        }
        return true;
    }

    // nave mae
    if (shipSize == 9) {
        if (x + 2 >= 10 || y + 2 >= 10 || z + 2 >= 10) return false;			//verifica se o cubo esta no limite

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {										//verifica se ao redor esta vazio
                for (int k = 0; k < 3; k++) {
                    if (currentTab[x + i][y + j][z + k] != ' ') return false;
                }
            }																//espaco ao redor vazio
        }

        if (needSpace) {
            for (int i = -1; i <= 3; i++) {
                for (int j = -1; j <= 3; j++) {
                    for (int k = -1; k <= 3; k++) {
                        int nx = x + i, ny = y + j, nz = z + k;
                        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && nz >= 0 && nz < 10) {
                           
                            if (i >= 0 && i < 3 && j >= 0 && j < 3 && k >= 0 && k < 3) continue;  // Ignora as próprias células da nave
                            if (currentTab[nx][ny][nz] != ' ') return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    // Outras naves em linha (X, Y, Z)
    int dx = 0, dy = 0, dz = 0;
    switch (direction) {
        case 'X': case 'x': dx = 1; break;
        case 'Y': case 'y': dy = 1; break;
        case 'Z': case 'z': dz = 1; break;
        default: return false;
    }

    int endX = x + dx * (shipSize - 1);
    int endY = y + dy * (shipSize - 1);
    int endZ = z + dz * (shipSize - 1);

    if (endX >= 10 || endY >= 10 || endZ >= 10) return false;

    for (int i = 0; i < shipSize; i++) {
        int nx = x + dx * i;
        int ny = y + dy * i;
        int nz = z + dz * i;
        if (currentTab[nx][ny][nz] != ' ') return false;
    }

    if (needSpace) {
		//verifica o espaco a redor da linha da nave
        for (int i = -1; i <= shipSize; i++) {
            for (int j = -1; j <= 1; j++) {
                for (int k = -1; k <= 1; k++) {
					//coordenadas  ao redor da linha
                    int nx = x + dx * i + dy * j + dz * k;
                    int ny = y + dy * i + dx * j + dz * k;
                    int nz = z + dz * i + dx * k + dy * j;

                    if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && nz >= 0 && nz < 10) { // Ignora a propria nave
                        
                        bool dentro = false;
                        for (int s = 0; s < shipSize; s++) {
                            if (nx == x + dx * s && ny == y + dy * s && nz == z + dz * s) {
                                dentro = true;
                                break;
                            }
                        }
                        if (dentro) continue;

                        if (currentTab[nx][ny][nz] != ' ') return false;			//Celula ocupada
                    }
                }
            }
        }
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
    
    if (randomShip == 2) showShipInstructions(type);
    
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
            else {
                cout << "Posicao invalida! Verifique se ha espaco suficiente e nao ha sobreposicao." << endl;
                cout << "Pressione ENTER para continuar...";
                cin.ignore();
                cin.get();
            }
        }
    } while (true);
}

void CBatalha::writeInTab2(int type, int tabIndex) {
    int x, y, z;
    int shipSize;
    char shipType;
    
    // Determinar tamanho e tipo da nave
    switch(type) {
        case 1: shipSize = 1; shipType = 'A'; break;
        case 2: shipSize = 2; shipType = 'B'; break;
        case 3: shipSize = 3; shipType = 'C'; break;
        case 4: shipSize = 4; shipType = 'D'; break;
        case 5: shipSize = 9; shipType = 'E'; break;
        default: return;
    }
    
    do {
        srand(time(0));
        int temp = rand() % 1000;
        
        x = temp / 100;
        y = (temp / 10) % 10;
        z = temp % 10;

        char axis[3] = {'X', 'Y', 'Z'};
        char direction = axis[rand() % 3];

        //Para caça não precisa de direção
        if (type == 1) {
            if (isPlacementValid(x, y, z, ' ', shipSize, tabIndex)) {
                placeShip(x, y, z, ' ', shipSize, tabIndex, shipType);
                break;
            }
            else {continue;}
        }
        //Para nave-mãe não precisa de direção
        if (type == 5) {
            if (isPlacementValid(x, y, z, ' ', shipSize, tabIndex)) {
                placeShip(x, y, z, ' ', shipSize, tabIndex, shipType);
                break;
            } 
            else {continue;}
        } 
        else {        
            if (isPlacementValid(x, y, z, direction, shipSize, tabIndex)) {
                placeShip(x, y, z, direction, shipSize, tabIndex, shipType);
                break;
            } 
            else {continue;}
        }
    } while (true);
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
		
        do {
            cout << "Deseja colocar as naves de forma:" << endl;
            cout << "1 - Aleatoria" << endl;
            cout << "2 - Manual" << endl;
            cin >> randomShip;

            system ("cls");
        } while (randomShip != 1 && randomShip != 2);

        if (randomShip == 2){
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
        else {
            for (int i = 0; i < 4; i++) {writeInTab2(1, j);}
            for (int i = 0; i < 3; i++) {writeInTab2(2, j);}
            for (int i = 0; i < 3; i++) {writeInTab2(3, j);}
            writeInTab2(4, j);
            writeInTab2(5, j);

            cout << "Todas as naves foram colocadas!" << endl;
            cout << "Pressione ENTER para continuar...";
            cin.ignore();
            cin.get();
            system ("cls");
        }
	}
}

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
		else {	//Vez do jogador 2
			cout << player2.name << " e a tua vez de jogar! Escolhe um eixo para lancar o disparo" << endl;
		}
	
	    cin >> axis;
    
        if (randomNum == 1) randomNum = 2;
	    else {randomNum = 1;}
	    axisSelect(axis, randomNum);

	}while (!verifyWin());
}

void CBatalha::menu() { 
    int optionM, option1, option2, option4, option0;
    bool sair = false;

    do {
        system("cls");
        
        cout << "==========================================" << endl;
        cout << "|             MENU PRINCIPAL             |" << endl;
        cout << "==========================================" << endl;
        cout << "| 1. Iniciar Novo Jogo                   |" << endl;
        cout << "| 2. Configuracoes                       |" << endl;
        cout << "| 3. Historico                           |" << endl;
        cout << "| 4. Como Jogar                          |" << endl;
        cout << "| 5. Musica                              |" << endl;
        cout << "| 6. Cor                                 |" << endl;
        cout << "|                                        |" << endl;
        cout << "| 0. Sair                                |" << endl;
        cout << "==========================================" << endl;
        cout << "Selecione a opcao:";

        cin >> optionM;        
        if (optionM >= 0 && optionM <= 6) {Beep(600, 150); break;}
            
    } while (true);
    
    do {
        switch (optionM) {
            case 1:
                do {
                    system("cls");
                    
                    cout << "==========================================" << endl;
                    cout << "|               NOVO JOGO                |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|   Comecar novo jogo?                   |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|   1. Sim                               |" << endl;
                    cout << "|   0. Nao                               |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "==========================================" << endl;
                    cout << "Selecione uma opcao:";
                    cin >> option1;

                    if (option1 == 1) {Beep(600, 150); cout << RESET; game();}
                    if (option1 == 0) {Beep(600, 150); menu();}
                        
                } while (true);
                
            case 2:
                do {
                    system("cls");
                    
                    cout << "==========================================" << endl;
                    cout << "|             CONFIGURACOES              |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  1. Espaco entre naves                 |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  0. Sair                               |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "==========================================" << endl;
                    cout << "Selecione uma opcao:";
                    cin >> option2;

                    if (option2 == 1) {
                        Beep(600, 150); 

                        if (needSpace == false) {needSpace = true; cout << "Agora as naves precisam de pelo menos 1 espaco entre elas!" << endl;}
                        else {needSpace = false; cout << "Agora as naves nao precisam de espaco entre elas!" << endl;}
                        cout << "Pressione ENTER para continuar...";
                        cin.ignore();
                        cin.get();

                    } else {Beep(600, 150); return menu();}

                } while (true);
                
            case 3: 
                do {
                    system("cls");
                    cout << "==========================================" << endl;
                    cout << "|           HISTORICO DOS JOGOS          |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|  Mostrando os ultimos 100 jogos...     |" << endl;
                    cout << "==========================================" << endl;

                    string historico[MAX];  
                    int total = 0;

                   
                    ifstream inFile("historico.txt");
                    if (inFile.is_open()) { //abre ficheiro para leitura das 100 linhas se nao der da erro
                        while (total < MAX && getline(inFile, historico[total])) {total++;}
                        inFile.close();  
                    } else {cout << "Nao foi possivel abrir o arquivo de historico." << endl;}

                    for (int i = 0; i < total; i++) {
                        cout << "| " << left << setw(38) << historico[i] << " |" << endl; //escreve todas as linhas do ficheiro txt
                    }

                    cout << endl;
                    cout << "==========================================" << endl;
                    cout << "| Pressione ENTER para voltar ao menu    |" << endl;
                    cout << "==========================================" << endl;

                    cin.ignore(); 
                    cin.get();   
                    Beep(600, 150);

                    ofstream outFile("historico.txt", ios::trunc);  //limpa o texto e reescreve oque guardou la em cima
                    if (outFile.is_open()) { //faz com que a linha mais "antiga" desapareca
               
                        for (int i = 0; i < total; i++) {outFile << historico[i] << endl;} //imprime os 100 linhas
                        outFile.close();
                    } else {cout << "Nao foi possivel abrir o arquivo para reescrever." << endl;}

                    return menu();  
                } while (true);  //fica o texto na tela ate ser imprmido o enter
           
                
            case 4:                        
                do {
                    system("cls");
                    
                    cout << "==========================================" << endl;
                    cout << "|               COMO JOGAR               |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|  Escolher a linguagem de preferencia:  |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  1. Portugues                          |" << endl;
                    cout << "|  2. Ingles                             |" << endl;
                    cout << "|  3. Espanhol                           |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  0. Sair                               |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "==========================================" << endl;
                    cout << "Selecione uma opcao:";

                    cin >> option4;
                    Beep(600, 150);

                    if (option4 == 1) {
                        system("cls");
                        Beep(600, 150);
                        cout << "==========================================" << endl;
                        cout << "|               COMO JOGAR               |" << endl;
                        cout << "========================================" << endl;
                        cout << "|  Batalha Naval 3D  um jogo por turnos  |" << endl;
                        cout << "|  onde o objetivo e afundar todos os    |" << endl;
                        cout << "|  navios do inimigo. O jogo ocorre em   |" << endl;
                        cout << "|  um espaco 3D.                         |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "|  REGRAS:                               |" << endl;
                        cout << "|  - Posicione seus navios no espaco.    |" << endl;
                        cout << "|  - Em cada turno, informe 3 coords.    |" << endl;
                        cout << "|    Exemplo: 2 5 3 (x,y,z)              |" << endl;
                        cout << "|  - O jogador e informado se acertou    |" << endl;
                        cout << "|     acertou ou errou 		          |" << endl;
                        cout << "|  - Vence quem afundar todos os navios  |"<< endl;
                        cout << "|    do oponente primeiro.               |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "==========================================" << endl;
                        cout << "|   Pressione ENTER para voltar ao menu  |" << endl;
                        cout << "==========================================" << endl;

                        cin.ignore(); // limpa o enter anterior
                        cin.get();    // espera que o utilizador digite qualquer tecla
                        Beep(600, 150);
                        return menu(); 
                    }
                    
                    if (option4 == 2) {
                        system("cls");
                        Beep(600, 150);
                        cout << "==========================================" << endl;
                        cout << "|               HOW TO PLAY              |" << endl;
                        cout << "==========================================" << endl;
                        cout << "|  3D Battleship is a turn-based game    |" << endl;
                        cout << "|  where the goal is to sink all the     |" << endl;
                        cout << "|  enemy's ships. The game takes place   |" << endl;
                        cout << "|  in a 3D space.                        |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "|  RULES:                                |" << endl;
                        cout << "|  - Position your ships in the space.   |" << endl;
                        cout << "|  - In each turn provide 3 coordinates  |" << endl;
                        cout << "|    Example: 2 5 3 (x, y, z)            |" << endl;
                        cout << "|  - The player is informed if they hit  |" << endl;
                        cout << "|    or miss        	 	              |" << endl;
                        cout << "|  - The winner is the one who sinks     |" << endl;
                        cout << "|    all the opponent's ships first.     |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "==========================================" << endl;
                        cout << "|   Press ENTER to return to the menu    |" << endl;
                        cout << "==========================================" << endl;
                        cin.ignore(); // limpa o enter anterior
                        cin.get();    // espera que o utilizador digite qualquer tecla
                        Beep(600, 150);
                        return menu(); 
                    }
                    
                    if (option4 == 3) {
                        system("cls");
                        Beep(600, 150);
                        cout << "==========================================" << endl;
                        cout << "|              COMO JUGAR                |" << endl;
                        cout << "==========================================" << endl;
                        cout << "|  Batalla Naval 3D es un juego por      |" << endl;
                        cout << "|  turnos cuyo objetivo es hundir todos  |" << endl;
                        cout << "|  los barcos enemigos. El juego se      |" << endl;
                        cout << "|  desarrolla en un espacio 3D.          |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "|  REGLAS:                               |" << endl;
                        cout << "|  - Coloca tus barcos en el espacio.    |" << endl;
                        cout << "|  - En cada turno, ingresa 3 coords.    |" << endl;
                        cout << "|    Ejemplo: 2 5 3 (x, y, z)            |" << endl;
                        cout << "|  - Se informa si acertaste o fallaste  |" << endl;
                        cout << "|  - Gana el primero en hundir todos     |" << endl;
                        cout << "|    los barcos del oponente.            |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "==========================================" << endl;
                        cout << "|   Presiona ENTER para volver al menu   |" << endl;
                        cout << "==========================================" << endl;

                        cin.ignore();
                        cin.get();    
                        Beep(600, 150);
                        return menu(); 
                    }
                    
                    if (option4 == 0) {Beep(600, 150); return menu();}
                } while (true);
            
            case 5: {
                int optionMusic;
                do {
                    system("cls");
                    cout << "==========================================" << endl;
                    cout << "|             MENU DE MUSICA             |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|  Deseja ligar ou desligar a musica?    |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  1. Ligar musica                       |" << endl;
                    cout << "|  2. Desligar musica                    |" << endl;
                    cout << "|                                        |" << endl;  
                    cout << "|  0. Sair                               |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "==========================================" << endl;
                    cout << "Selecione uma opcao: ";
                    cin >> optionMusic;
                    Beep(600, 150);
                    
                    if (optionMusic == 1) {PlaySound("undertale.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);}  //ativa a musica ou repete
                    if (optionMusic == 2) {PlaySound(NULL, NULL, 0);}  // para a musica
                    if (optionMusic == 0) {return menu();} // volta para menu com a musica se estiver ligado
                } while (true); 
            }

            case 6: {
                int opcaoCor;
                do {
                    system("cls");
                    cout << corAtual;    
                    cout << "==========================================" << endl;
                    cout << "|          ESCOLHER COR DO MENU          |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|      Atencao, as naves tem cores       |" << endl;
                    cout << "|             predefinidas!              |" << endl; 
                    cout << "|                                        |" << endl;       
                    cout << "| 1. Vermelho                            |" << endl;
                    cout << "| 2. Verde                               |" << endl;
                    cout << "| 3. Amarelo                             |" << endl;
                    cout << "| 4. Azul                                |" << endl;
                    cout << "| 5. Magenta                             |" << endl;
                    cout << "| 6. Ciano                               |" << endl;
                    cout << "| 7. Reset(Branco)                       |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "| 0. Sair                                |" << endl;
                    cout << "|                                        |" << endl;  
                    cout << "==========================================" << endl;
                    cout << "Escolha uma cor: ";
                    cin >> opcaoCor;
                    Beep(600, 150);

                    switch (opcaoCor) {
                        case 1: corAtual = RED; break;
                        case 2: corAtual = GREEN; break;
                        case 3: corAtual = YELLOW; break;
                        case 4: corAtual = BLUE; break;
                        case 5: corAtual = MAGENTA; break;
                        case 6: corAtual = CYAN; break;
                        case 7: corAtual = RESET; break;
                        case 0: return menu();
                    }
                } while (true);
            }
            
            case 0: // criar uma opção se ainda houver um jogo aberto
                do {
                    system("cls");
                    
                    cout << "==========================================" << endl;
                    cout << "|                 SAIR                   |" << endl;
                    cout << "==========================================" << endl;
                    cout << "|  Tem certeza?                          |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "|  1. Sim                                |" << endl;
                    cout << "|  0. Nao                                |" << endl;
                    cout << "|                                        |" << endl;
                    cout << "==========================================" << endl;
                    cout << "Selecione uma opcao:";

                    
                    cin >> option0;
                    Beep(600, 150);

                    if (option0 == 1) {
                        system("cls");
                        
                        cout << "==========================================" << endl;
                        cout << "|                                        |" << endl;
                        cout << "|              A ENCERRAR...             |" << endl;
                        cout << "|                                        |" << endl;
                        cout << "==========================================" << endl;

                        sair = true;
                        break;
                    }
                    
                    if (option0 == 0) return menu();
                    break;
                    
                } while(true);
                break;
                
            system("cls");
        }    
    } while(!sair);
}
