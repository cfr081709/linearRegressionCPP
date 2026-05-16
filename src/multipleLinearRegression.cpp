#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

using Matrix = vector<vector<double>>;
using Vec    = vector<double>;


void printMatrix(const Matrix& M, const string& label = "") {
    if (!label.empty()) cout << "\n[" << label << "]\n";
    for (const auto& row : M) {
        for (double val : row)
            cout << setw(12) << fixed << setprecision(4) << val;
        cout << "\n";
    }
}

void printVec(const Vec& v, const string& label = "") {
    if (!label.empty()) cout << "\n[" << label << "]\n";
    for (double val : v)
        cout << setw(12) << fixed << setprecision(4) << val;
    cout << "\n";
}

Matrix buildDesignMatrix(const Matrix& X) {
    int n = X.size();
    int p = X[0].size();

    Matrix Xd(n, Vec(p + 1));

    for (int i = 0; i < n; i++) {
        Xd[i][0] = 1.0;
        for (int j = 0; j < p; j++)
            Xd[i][j + 1] = X[i][j];
    }
    return Xd;
}

Matrix transpose(const Matrix& M) {
    int rows = M.size();
    int cols = M[0].size();
    Matrix T(cols, Vec(rows));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            T[j][i] = M[i][j];
    return T;
}

Matrix matMul(const Matrix& A, const Matrix& B) {
    int m = A.size();
    int k = A[0].size();
    int n = B[0].size();
    Matrix C(m, Vec(n, 0.0));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int l = 0; l < k; l++)
                C[i][j] += A[i][l] * B[l][j];
    return C;
}

Vec matVecMul(const Matrix& A, const Vec& v) {
    int m = A.size();
    int n = v.size();
    Vec result(m, 0.0);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            result[i] += A[i][j] * v[j];
    return result;
}

Vec gaussianElimination(Matrix A, Vec b) {
    int n = A.size();

    Matrix aug(n, Vec(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug[i][j] = A[i][j];
        aug[i][n] = b[i];
    }

    for (int col = 0; col < n; col++) {

        int pivotRow = col;
        for (int row = col + 1; row < n; row++)
            if (fabs(aug[row][col]) > fabs(aug[pivotRow][col]))
                pivotRow = row;

        swap(aug[col], aug[pivotRow]);

        double pivot = aug[col][col];
        if (fabs(pivot) < 1e-12)
            throw runtime_error("Matrix is singular — features may be collinear.");

        for (int row = col + 1; row < n; row++) {
            double factor = aug[row][col] / pivot;
            for (int k = col; k <= n; k++)
                aug[row][k] -= factor * aug[col][k];
        }
    }

    Vec x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = aug[i][n];                   
        for (int j = i + 1; j < n; j++)
            x[i] -= aug[i][j] * x[j];       
        x[i] /= aug[i][i];                  
    }

    return x; 
}


Vec fit(const Matrix& X_raw, const Vec& y) {
    int n = X_raw.size();
    if (n == 0) throw runtime_error("Empty dataset.");
    if ((int)y.size() != n) throw runtime_error("X and y size mismatch.");

    Matrix X  = buildDesignMatrix(X_raw);

    Matrix Xt = transpose(X);
    Matrix XtX = matMul(Xt, X);

    Vec Xty = matVecMul(Xt, y);

    Vec beta = gaussianElimination(XtX, Xty);

    return beta;
}

Vec predict(const Matrix& X_raw, const Vec& beta) {
    Matrix X = buildDesignMatrix(X_raw);
    return matVecMul(X, beta);
}

float leastSquareMinimization(const Matrix& X_raw, const Vec& beta, const Vec& trueValues) {
    Matrix X = buildDesignMatrix(X_raw);
    float leastSquares = 0.0;
    for (int i = 0; i < (int)X.size(); i++) {
        float yHat = 0.0;
        for (int j = 0; j < (int)beta.size(); j++)
            yHat += X[i][j] * beta[j];
        float residual = trueValues[i] - yHat;
        leastSquares += residual * residual;
    }
    return leastSquares;
}

