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

        cout << "Fine." << endl;

    } else {
        cout << "Automatic move." << endl;
    }
    board[move - 1] = psToChar(ps);
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
