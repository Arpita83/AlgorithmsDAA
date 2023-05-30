#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> transposeMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<int>> transposed(cols, vector<int>(rows));

    // Transpose the matrix in-place
    for (int i = 0; i < rows + cols - 1; i++) {
        int start_row = max(0, i - cols + 1);
        int count = min(i + 1, rows, cols) - start_row;

        for (int j = 0; j < count; j++) {
            int row = start_row + j;
            int col = i - start_row - j;

            // Swap elements across the diagonal
            transposed[col][row] = matrix[row][col];
        }
    }

    return transposed;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

int main() {
    // Example matrix
    vector<vector<int>> matrix = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9}};

    // Transpose the matrix
    vector<vector<int>> transposedMatrix = transposeMatrix(matrix);

    // Print the transposed matrix
    printMatrix(transposedMatrix);

    return 0;
}
