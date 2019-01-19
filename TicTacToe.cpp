#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
using namespace std;

const char EMPTY = ' ';

const char NO_ONE = ' ';
const char TIE = '_';

const int LUCKY_MOVE_PROB_PCNT = 5;

const int WIN_COUNT = 3;

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
        cout << "Automatic move to " << move << " cell" <<  endl;
    }
    board[move - 1] = psToChar(ps);
}

char winner(const vector<char>& board) {
    int size = sqrt(board.size());

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i*size + j] != EMPTY) {
                // check
                char cur = board[i*size + j];

                // to the right
                int k = 1;
                while (k < WIN_COUNT) {
                    int nxtIndx = i*size + j + k;
                    if (nxtIndx >= board.size()) break;
                    if (board[nxtIndx] != cur) break;
                    ++k;
                }
                if (k == WIN_COUNT) {
                    return cur;
                }

                // to the bottom
                k = 1;
                while (k < WIN_COUNT) {
                    int nxtIndx = (i + k)*size + j;
                    if (nxtIndx >= board.size()) break;
                    if (board[(i + k)*size + j] != cur) break;
                    ++k;
                }
                if (k == WIN_COUNT) {
                    return cur;
                }

                // to the bottom-right
                k = 1;
                while (k < WIN_COUNT) {
                    int nxtIndx = (i + k)*size + j + k;
                    if (nxtIndx >= board.size()) break;
                    if (board[(i + k)*size + j + k] != cur) break;
                    ++k;
                }
                if (k == WIN_COUNT) {
                    return cur;
                }
            }
        }
    }

    return NO_ONE;
}

bool moveAgain() {
    return rand()%100 < LUCKY_MOVE_PROB_PCNT;
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
