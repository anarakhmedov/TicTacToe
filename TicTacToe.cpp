#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>

using namespace std;

const char EMPTY = ' ';
const char NO_ONE = ' ';
const char TIE = '_';

enum class PlayerSymbol {X, O};

void displayBoard(const vector<char>& v) {
    int size = sqrt(v.size());
    for (int i = 0; i < size; ++i) {
        cout << endl << "\t";
        for (int j = 0; j < size; ++j) {
            cout << v[i * size + j];
            if (j < size - 1) {
                cout << " | ";
            }
        }
        cout << endl;
        if (i < size - 1) {
            cout << "\n\t";
            // TODO: different multiplier for different size
            for (int k = 0; k < size * 3; k++) {
               cout << "-";
            }
            cout << endl;
        }
    }
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

int remainingCell(const vector<char>& board) {
    int emptyCount = 0;
    int emptyCellNum = -1;

    for (int i = 0; i < board.size(); ++i) {
        if (board[i] == EMPTY) {
            ++emptyCount;
            emptyCellNum = i + 1;
        }
    }

    if (emptyCount == 1) {
        return emptyCellNum;
    }

    return -1;
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

    int move = remainingCell(board);
    if (move == -1) { // autofill didn't work
        move = askNumber("Where will you move?", 1, int(board.size()));
        while (!isLegal(move, board)) {
            cout << "That square is already occupied!" << endl;
            move = askNumber("Where will you move?", 1, int(board.size()));
        }
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
    return rand()%10 < 1;
}

int main() {
    srand(time(NULL));

    vector<char> board(9, EMPTY);
    displayBoard(board);
    
    PlayerSymbol ps1 = PlayerSymbol::X;
    PlayerSymbol ps2 = PlayerSymbol::O;
    
    bool moveOfPlayer1 = true;
    while (winner(board) == NO_ONE) {
        PlayerSymbol curSymbol;
        if (moveOfPlayer1) {
        	curSymbol = ps1;
        } else {
        	curSymbol = ps2;
        }

        humanMove(board, curSymbol);
        displayBoard(board);

        if (!moveAgain()) {
            moveOfPlayer1 = !moveOfPlayer1;
        } else {
            cout << "Lucky move!" << endl;
        }
    }
    int w = winner(board);
    if (w == TIE) {
        cout << "Tie!" << endl;
    } else {
        cout << string(1, w) << " won!" << endl;
    }
    return 0;
}
