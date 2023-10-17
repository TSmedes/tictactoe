//
// Created by tobys on 10/16/2023.
//

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::setw;
using std::right;

int Options();
int RunGame(int option);
int UpdateBoard(char board[3][3], int move, int player);
void DrawBoard(char board[3][3]);
int CheckWinner(char board[3][3], int player);

int main() {
    int winner = -1;
    while(winner != 0) {
        cout << setw(25) << right << "Welcome to Tic Tac Toe!" << endl << setw(27) << "How would you like to play?" << endl;
        winner = RunGame(Options());
        if (winner == 1 || winner == 2) {
            cout << "Congratulations player " << winner << "! You Won!" << endl << endl;
        }
        else if (winner == -1) {
            cout << "It was a tie!" << endl << endl;
        }
    }
    return 0;
}
int Options() {
    int option;
    cout << "1.\t1 person" << endl << "2.\t2 persons" << endl << "3.\tQuit" << endl;
    do {
        cin >> option;
        if(option < 1 || option > 3) {
            cout << "Not an option, please try again" << endl;
        }
    }while (option < 1 || option > 3);
    return option;
}

int RunGame(int option) {
    int winner = 0, player = 1, move;
    char board[3][3] = {0};
    if(option == 1){
        //FIXME CPU game
        cerr << "Feature not ready yet. Try another option." << endl;
        return 3;
    }
    else if(option == 2) {
        DrawBoard(board);
        for(int i = 3; winner == 0; ++i) {
            cout << "Player " << player << ", your turn. Enter your square (1-9)" << endl;
            cin >> move;
            while(UpdateBoard(board, move, player) == -1) {
                cin >> move;
            }
            DrawBoard(board);
            int winner = CheckWinner(board, player);
            if(winner == player) {
                return player;
            }
            else if(winner == -1) return -1;
            player = (i % 2) + 1;
        }
    }
    else {
        return winner;
    }
}

int UpdateBoard(char board[3][3], int move, int player){
    if(move < 1 || move > 9) {
        cout << "Please enter your move as a number (1-9). Try again." << endl;
        return -1;
    }
   int x = (move - 1) / 3;
   int y = (move - 1) % 3;
   if(board[x][y] != 0) {
       cout << "Someone already played there, silly goose! Try again." << endl;
       return -1;
   }
   if(player == 1) {
       board[x][y] = 'X';
   }
   else {
       board[x][y] = 'O';
   }
   return 1;
}

void DrawBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if(i != 0) {
            cout << " ---------" << endl;
        }
        for (int j = 0; j < 3; ++j) {
            if(j != 0) {
                cout << "|";
            }
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int CheckWinner(char board[3][3], int player) {
    char symbol;
    if(player == 1) symbol = 'X';
    else symbol = 'O';
    //Checks for column wins
    for (int i = 0; i < 3; ++i) {
        if(board[0][i] != symbol) continue;
        if(board[1][i] != symbol) continue;
        if(board[2][i] != symbol) continue;
        return player;
    }
    //Checks for row wins
    for (int i = 0; i < 3; ++i) {
        if(board[i][0] != symbol) continue;
        if(board[i][1] != symbol) continue;
        if(board[i][2] != symbol) continue;
        return player;
    }
    //Checks for diagonal wins
    for (int i = 0; i < 3; ++i) {
        if(board[i][i] != symbol) break;
        if(i == 2) return player;
    }
    for (int i = 0; i < 3; ++i) {
        if(board[i][2 - i] != symbol) break;
        if(i == 2) return player;
    }
    //Checks for a full board (tie)
    bool full = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(board[i][j] == 0) {
                full = false;
                break;
            }
            if(!full) break;
        }
    }
    if(full) return -1;
    //No wins found
    return 0;
}