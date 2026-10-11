
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool dfs(vector<vector<char>>& board, string& word,
             int i, int j, int index) {

        // All letters of the word have been found
        if (index == word.size()) {
            return true;
        }

        // Check boundaries and current character
        if (i < 0 || j < 0 ||
            i >= board.size() || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }

        // Mark the cell as visited
        char temp = board[i][j];
        board[i][j] = '#';

        // Search in all four directions
        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);

        // Backtrack: restore the original character
        board[i][j] = temp;

        return found;
    }
};

int main() {
    vector<vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    string word = "ABCCED";

    Solution obj;

    if (obj.exist(board, word)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
