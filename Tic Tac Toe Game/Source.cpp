#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string WIN_FILE = "wins.txt";

int read_wins() {
    ifstream file(WIN_FILE);
    int wins = 0;
    if (file.is_open()) {
        file >> wins;
        file.close();
    }
    return wins;
}

void write_wins(int wins) {
    ofstream file(WIN_FILE);
    if (file.is_open()) {
        file << wins;
        file.close();
    }
}

void print_board(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool check_win(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool is_draw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

void play_game() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char player = 'X';
    int wins = read_wins();

    cout << "Current number of wins: " << wins << endl;

    while (true) {
        print_board(board);
        int row, col;
        cout << "Player " << player << ", enter row (0-3) and column (0-3): ";
        cin >> row >> col;

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move, try again." << endl;
            continue;
        }

        board[row][col] = player;

        if (check_win(board, player)) {
            print_board(board);
            cout << "Player " << player << " wins!" << endl;
            if (player == 'X') {
                wins++;
                write_wins(wins);
                cout << "Number of wins updated: " << wins << endl;
            }
            break;
        }

        if (is_draw(board)) {
            print_board(board);
            cout << "It's a draw!" << endl;
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

int main() {
    char play_again;
    do {
        play_game();
        cout << "Do you want to play again? (y/n): ";
        cin >> play_again;
    } while (play_again == 'y');
    return 0;
}
