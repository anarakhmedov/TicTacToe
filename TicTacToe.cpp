#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

const char EMPTY = ' ';
const char NO_ONE = ' ';
const char TIE = '_';

enum class PlayerSymbol {X, O};

void displayBoard(const vector<char>& v) {
    cout << "\n\t" << v[0] << " | " << v[1] << " | " << v[2] << endl;
    cout << "\n\t" << "---------" << endl;
    cout << "\n\t" << v[3] << " | " << v[4] << " | " << v[5] << endl;
    cout << "\n\t" << "---------" << endl;
    cout << "\n\t" << v[6] << " | " << v[7] << " | " << v[8] << endl;
}

int askNumber(string quiestion, int min, int max) {
    int number;
    do
    {
        cout << quiestion << " (" << min << "-" << max << "): ";
        cin >> number;
    } while (number < min || number > max);
    return number;
    
}

bool isLegal(int move, const vector<char>& board) {
    return (board[move - 1] == EMPTY);
}

char psToChar(PlayerSymbol ps) {
    switch (ps) {
        case PlayerSymbol::X:
            return 'X';
        case PlayerSymbol::O:
            return 'O';
    }
}

void humanMove(vector<char>& board, PlayerSymbol ps) {
    cout << psToChar(ps) << " goes" << endl;
    int move = askNumber("Where will you move?", 1, int(board.size()));
    while (!isLegal(move, board)) {
        cout << "That square is already occupied!" << endl;
        move = askNumber("Where will you move?", 1, int(board.size()));
    }
    board[move - 1] = psToChar(ps);
    cout << "Fine." << endl;
}

char winner(const vector<char>& board) {
    const int wr[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6} };
   
    for (int i = 0; i < 8; ++i) {
        if (board[wr[i][0]] == board[wr[i][1]] && board[wr[i][1]] == board[wr[i][2]]) {
            return board[wr[i][0]];
        }
    }
    for (char c: board) {
        if (c == EMPTY) {
            return NO_ONE;
        }
    }
    return TIE;
}

bool moveAgain() {
    return rand()%10 < 2;
}

int main() {
    srand(time(NULL));

    vector<char> board(9, EMPTY);
    displayBoard(board);
    
    PlayerSymbol ps1 = PlayerSymbol::X;
    PlayerSymbol ps2 = PlayerSymbol::O;
    
    bool moveOf1player = true;
    while (winner(board) == NO_ONE) {
        if (moveOf1player) {
            humanMove(board, ps1);
            if !moveAgain() {
                moveOf1player = false;
            } else {
                cout << "Lucky move!" << endl;
            }
        }
        else {
            humanMove(board, ps2);
            if !moveAgain() {
                moveOf1player = true;
            } else {
                cout << "Lucky move!" << endl;
            }
        }
        displayBoard(board);
    }
    int w = winner(board);
    if (w == TIE) {
        cout << "Tie!" << endl;
    } else {
        cout << string(1, w) << " won!" << endl;
    }
    return 0;
}
