#include <iostream>
#include <ctime>
#include <windows.h>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>
using namespace std;
int pos = 10; // posicao do jogador
#define ln 21 // numero de linhas
#define cl 20 // numero de colunas
#define colisao 19 // linha em que a colisao é checada
#define veloPadrao 500000 // velocidade padrão do modo facil
#define objPadrao 50 // objetivo de pontos
char player;
int vidas, pontos, objetivo, velocidade, tempo;
int menu = 0;
int modo[2] = {0, 0};
int star1 = 5, star2 = 15;
int key, key2;
char grid[ln][cl];

void movimento(){   // movimento do player
    if(kbhit()){    // leitura da tecla.
        key = getch();
        key2 = getch(); // numero da tecla especial.
    }
    switch(key2){
        case 75: // esquerda
            if(pos!=1){
                grid[ln-2][pos] = ' ';
                pos--;
                grid[ln-2][pos] = player;
            }
            break;
        case 77: // direita
            if(pos!=18){
                grid[ln-2][pos] = ' ';
                pos++;
                grid[ln-2][pos] = player;
            }
            break;
    }
    if(key==27){
        exit(0);
    }
}

void field(){   // campo do jogo, interface.


    for(int x = 0; x<ln; x++){  // imprime as linhas da matriz
        for(int y = 0; y<cl; y++){
            if(x!=1) cout << grid[x][y]; // imprime 
        }
        if(x!=1) cout << endl; // separa as linhas
    }
    if(modo[0] == 1) cout << "Vidas: " << vidas << "     Tempo:" << pontos <<"/"<< objetivo <<endl; // output final do jogo meteoro
    if(modo[0] == 2) cout << "Meta: " << objetivo <<"/" << pontos <<"     Tempo:" << tempo/4 << endl;// output final do jogo coleta

}

void spawnMeteoro(){ // spawn de meteoro aleatorio
    grid[1][star1] = ' '; // limpa a casa acima da estrela
    grid[1][star2] = ' ';
    star1 = rand()%18+1;
    star2 = rand()%18+1;
    grid[1][star1] = '*'; // geração de estrela
    grid[1][star2] = '*';
}

void spawnColeta(){ // spawn de estrela aleatorio
    grid[1][star1] = ' ';
    star1 = (rand()%(ln-3)+1);
    grid[1][star1] = '*'; // geração de estrelas
}

void coleta(){   // modo de jogo coleta
    velocidade = veloPadrao;
    pontos = 0;
     for(int x = 0; x<ln; x++){
        for(int y = 0; y<cl; y++){
            if(x == 0 || x == ln-1 || y == 0 || y == cl-1){
                grid[x][y] = '#';
            }
            else if(x == (ln-2) && y == pos){
                grid[x][y] = player;
            }
            else grid[x][y] = ' ';
        }
    }
    if(modo[1] == 1){
        objetivo = objPadrao/3;
    }
    if(modo[1] == 2){
        objetivo = objPadrao/2;
    }
    if(modo[1] == 3){
        objetivo = objPadrao;
    }

    while(pontos != objetivo){
        usleep(velocidade);
        system("CLS");
        field();
        movimento();
        spawnColeta();
        for(int x = ln-2; x>(ln-20); x--){ // limpa o campo
            for(int y = 1; y<cl-1; y++){
                if(grid[x][y]!= player) // não apaga o jogador
                grid[x][y] = grid[x-1][y]; // desce as estrelas
                if(grid[x][y]==player){
                    if(grid[x-1][y]=='*') {
                        pontos++;
                        velocidade -= pontos*400; // aumento exponencial de velocidade
                    }
                }
            }
        }
        key2 = 0;
        tempo++;
    }
    system("CLS");
    cout << "Parabens! Voce atingiu a meta de pontos em " << (tempo/2) << " segundos" <<endl;
    sleep(5);
     system("CLS");
    
}

void meteoro(){ // modo de jogo meteoros
    if(modo[1]==1) {
        vidas = 3;
        objetivo = objPadrao;
        velocidade = veloPadrao;
    }
    if(modo[1]==2){
        vidas = 2;
        objetivo = objPadrao*2;
        velocidade = veloPadrao/2;
    }
    if(modo[1]==3) {
        vidas = 1;
        objetivo = objPadrao*4;
        velocidade = veloPadrao/4;
    }

    for(int x = 0; x<ln; x++){ // preenche a matriz
        for(int y = 0; y<cl; y++){
            if(x == 0 || x == ln-1 || y == 0 || y == cl-1){
                grid[x][y] = '#';
            }
            else if(x == (ln-2) && y == pos){
                grid[x][y] = player;
            }
            else grid[x][y] = ' ';
        }
    }

    while(vidas>=0 && pontos<objetivo){
        usleep(velocidade);
        system("CLS");
        field();
        movimento();

        spawnMeteoro();

        for(int x = (ln-2); x>1; x--){ // limpa o campo
            for(int y = 1; y<cl-1; y++){
                if(grid[x][y]!= player) // não apaga o jogador
                grid[x][y] = grid[x-1][y]; // desce as estrelas
                if(grid[x][y]==player){
                    if(grid[x-1][y]=='*') vidas--;
                }
            }
        }
        key2 = 0; // reseta o movimento
        pontos++; // aumenta os pontos
    }
    system("CLS");
    if(vidas<0){
    cout << "" << endl;
    cout << "" << endl;
    cout << "=============" << endl;
    cout << "  GAME OVER  " << endl;
    cout << "=============" << endl;
    cout << "" << endl;
    cout << "" << endl;
    }
    if(vidas>=0){
    cout << "" << endl;
    cout << "" << endl;
    cout << "==============" << endl;
    cout << " VOCE GANHOU! " << endl;
    cout << "==============" << endl;
    cout << "" << endl;
    cout << "" << endl;
    }
    sleep(5);
    system("CLS");
}
        
void menuModo(){ // escolhe modo de jogo
    cout << "============== Escolha o modo de jogo ===============" << endl;
    cout << "                   1. Modo meteoro       " << endl;
    cout << "       Desvie dos meteoros ate o tempo acabar.      " << endl << endl;
    cout << "                   2. Modo Coleta     " << endl;
    cout << "       Colete modo quantidade de estrelas conforme o nivel        " << endl;
    cin >> modo[0];
    system("CLS");
    if(modo[0] == 1){
        cout << "============== Escolha a Dificuldade ================" <<endl;
        cout << "                   1. Facil" <<endl;
        cout << "                   2. Medio" <<endl;
        cout << "                   3. Dificil" <<endl;
        cin >> modo[1];
        system("CLS");
        cout << "Escolha seu caractere: ";
        cin >> player;
        system("CLS");
        meteoro();
    }
    if(modo[0] == 2){
        cout << "============== Escolha o objetivo ================" <<endl;
        cout << "                      1. 15 estrelas" <<endl;
        cout << "                      2. 30 estrelas" <<endl;
        cout << "                      3. 50 estrelas" <<endl;
        cin >> modo[1];
        system("CLS");
        cout << "Escolha seu caractere: ";
        cin >> player;
        system("CLS");
        coleta();
    }

}

void creditos(){ // creditos do jogo
        cout << "        Criadores:" << endl << endl;
        cout << "       Luiz Eduardo" << endl ;
        cout << "       Wendel Rocha" << endl << endl;
        cout << "1 Ano Ciencia da Computacao" << endl << "        Unicentro";
        sleep(10);
        system("CLS");
}

void menu1(){ // menu inicial
    cout << ":       1. Ir para o modo de jogo       :" << endl;
    cout << ":           2. Creditos                 :"<< endl;
    cout << ":          3. Sair do jogo              :" << endl;

    cout << "         Escolha uma opcao: "; cin >>menu; cout << endl; 

    if(menu == 1){
        system("CLS");
        menuModo();
    }
    if(menu == 2){
        system("CLS");
        creditos();
    }
}

int main(){ // Chama o menu e encerra o jogo
    srand(time(NULL));
    while(menu!=3){
        menu1();
    }
    return 0;
}