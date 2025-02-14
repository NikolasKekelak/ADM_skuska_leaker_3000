

#include <iomanip>
#include <vector>
using namespace std;
#ifndef MATRIX_H
#define MATRIX_H


#define UPPER_RAND 5
#define LOWER_RAND -5
#define v_MATRIX vector<vector<int>>
extern ofstream odpovede;

v_MATRIX minor(v_MATRIX input, int row, int col) {
    v_MATRIX result;
    for (int i = 0; i < input.size(); i++) {
        vector<int> temp;
        if (i == row )continue;
        for (int j = 0; j < input[0].size(); j++) {
            if (j == col) continue;
            temp.push_back(input[i][j]);
        }
        result.push_back(temp);
    }

    return result;
}

float determinant(v_MATRIX input) {
    if (input.size() == 1 )
        return input[0][0];
    float det=0;
    for (int i = 0; i < input.size(); i++)
        det += input[0][i]*(pow(-1,i))*determinant(minor(input, 0, i));
    return det;
}

template <class T>
class MATRIX {
    public:
    vector<vector<T>> matrix;

    //constructory
    MATRIX(int row, int col) : matrix(row, vector<T> (col)) {} ;
    MATRIX(const MATRIX& matrix) : matrix(matrix.matrix) {} ;
    MATRIX(int row, int col, const T& value) : matrix(row, vector<T> (col), value) {}
    MATRIX(int row, int col , string parameter) : matrix(row, vector<T> (col)) {

        if (parameter == "rand") {
                for (auto &row : matrix)
                for (auto &col : row)col = rand() % (UPPER_RAND-LOWER_RAND) + LOWER_RAND;
        }

        if (parameter == "rand-det_not_null") {
            do {
                for (auto &row : matrix)
                for (auto &col : row)col = rand() % (UPPER_RAND-LOWER_RAND) + LOWER_RAND;
            }while (det() == 0);

        }
        if (parameter == "rand-nice_inverse") {
            do {
                for (auto &row : matrix)
                    for (auto &col : row)col = rand() % (3) -1;
            }while (det() != 1);

        }
        if (parameter == "rand-L") {
            do {
                for (auto &row : matrix)
                    for (auto &col : row)col = rand() % (9) -4;
            }while (det() != 0);
            for (int i =0; i < matrix.size(); i++)
                for (int j = 0; j < matrix[0].size(); j++) {
                    if (j>i) matrix[i][j]=0;
                    if (i==j) matrix[i][j]=1;
                }

        }
        if (parameter == "rand-U") {
            do {
                for (auto &row : matrix)
                    for (auto &col : row)col = rand() % (9) -4;
            }while (det() != 0);
            for (int i =0; i < matrix.size(); i++)
                for (int j = 0; j < matrix[0].size(); j++)
                    if (j<i) matrix[i][j]=0;
            if (matrix[0][0]==0) matrix[0][0]=1;
        }

    }

    void display() {
        for (auto &row : matrix) {
            odpovede<<" [ ";
            for (auto &col : row) {
                odpovede<<setw(4)<<col;
            }
            odpovede<<" ]\n";
        }
    }
    void display(const vector<int> &b) {
        int i =0;
        for (auto &row : matrix) {
            odpovede<<" [ ";
            for (auto &col : row) {
                odpovede<<setw(4)<<col;
            }
            odpovede<<" ][ ";
            odpovede<<setw(4)<<b[i++];
            odpovede<<" ]\n";
        }
    }

    void latex_display(ofstream &output,const vector<int> &b) {
        output<<"\\[\n\\begin{bmatrix}\n";
        for (auto &row : matrix) {
            for (auto &col : row) {
                output<<setw(4)<<col<<" & ";
            }
            output<<" \\\\\n ";

        }
        output<<"\\end{bmatrix}\n";
        output<<"\\begin{bmatrix}\n";
        for (auto row : b) {
            output<<row<<"\\\\\n";
        }
        output<<"\\end{bmatrix}\n\\]\n";

    }
    void latex_display(ofstream &output) {
        output<<"\\[\n\\begin{bmatrix}\n";
        for (auto &row : matrix) {
            for (auto &col : row) {
                output<<setw(4)<<col<<" & ";
            }
            output<<" \\\\\n ";

        }

        output<<"\\end{bmatrix}\n\\]\n";

    }
    int det() {
        return determinant(matrix);
    }
    void assign_vector(vector<int> &vec) {

        vector<int> x; //vector x-iek
        if ( !vec.empty() ) {
            x=vec;
            vec.clear();
        }
        else {
            for (int i =0 ; i < matrix.size(); i++)
                x.push_back(rand() % (UPPER_RAND-LOWER_RAND) + LOWER_RAND);
        }

        for (int i = 0; i < matrix.size(); i++) {
            int sum = 0;
            for (int j = 0; j < matrix.size(); j++)
                sum += matrix[i][j]*x[j];
            vec.push_back(sum);
        }
    }
    MATRIX<int> int_inverse() {
        int det = determinant(matrix);
        MATRIX<int> result(matrix.size(), matrix[0].size());
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < matrix.size(); j++) {
                result.matrix[j][i] = (pow(-1,i+j))*determinant(minor(matrix, i, j))/det;
            }
        return result;
    }

    MATRIX<T> operator* (MATRIX<T> B) {
        MATRIX<T> result(matrix.size(), B.matrix[0].size());
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < B.matrix.size(); j++)
                for (int k = 0; k < B.matrix[0].size(); k++)
                    result.matrix[i][j] += matrix[i][k]*B.matrix[k][j];
        return result;
    }
};

#endif //MATRIX_H
