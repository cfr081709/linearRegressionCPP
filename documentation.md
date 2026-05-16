# Linear Regression C++ Documentation

## Overview

This project implements simple and multiple linear regression from scratch in C++,
with no external dependencies. It generates random sample data, fits each model,
produces predictions, and reports the least squares error. It also includes a suite
of feature scaling methods and Euclidean norm utilities.

---

## Project Structure

```
linearRegressionCPP/
  README.md
  documentation.md
  license.txt
  src/
    main.cpp
    helperFunctions.cpp
    simpleLinearRegression.cpp
    multipleLinearRegression.cpp
    featureScaling.cpp
    program.exe
```

---

## Build and Run

```powershell
g++ src/main.cpp -o src/program.exe
.\src\program.exe
```

---

## Program Flow

1. **Simple Linear Regression**
   - Generates 10 x-values and 20 random y-values.
   - Uses the first 10 y-values to fit the model, last 10 as true values.
   - Computes slope and y-intercept.
   - Predicts values for a hardcoded list of x-values.
   - Reports least squares error, slope, and y-intercept.

2. **Multiple Linear Regression**
   - Generates a 15×3 random feature matrix and 15 random target values.
   - Splits into 10 training samples and 5 test samples.
   - Fits the model using OLS via the Normal Equations.
   - Predicts on the test set.
   - Reports the learned coefficients and least squares error on the test set.

3. **Feature Scaling Comparison**
   - Applies each scaler to the training and test matrices independently.
   - Fits a fresh MLR model on each scaled training set.
   - Reports the least squares error on the corresponding scaled test set.
   - Allows direct comparison of how each scaling method affects model error.

4. **Euclidean Norms**
   - Computes and prints column norms, row norms, and the Frobenius norm
     of the training matrix.

---

## Source File Reference

### `helperFunctions.cpp`

Utility functions for generating random data.

#### `double generateRandomValue()`
Returns a random double between `0.0` and `1.0`.

#### `std::vector<int> generateXValues(int n)`
Returns integers `0` through `n - 1`.

#### `std::vector<double> generateRandomYValues(int n)`
Returns `n` random doubles between `0.0` and `1.0`.

#### `std::vector<std::vector<double>> generateRanomMatrix(int length, int width)`
Returns a 2D matrix of random doubles.
Note: function name contains a typo (`generateRanomMatrix` should be `generateRandomMatrix`).

---

### `simpleLinearRegression.cpp`

Simple linear regression: one input variable, one output variable.

#### `double generateBestFitSlope(vector<double> yValues, vector<int> xValues)`
Computes the slope of the best-fit line:
```
m = (n * Σxy - Σx * Σy) / (n * Σx² - (Σx)²)
```

#### `double bestFitYIntercept(vector<double> yValues, vector<int> xValues)`
Computes the y-intercept of the best-fit line:
```
b = (Σy - m * Σx) / n
```

#### `float getPrediction(float x, float b, float m)`
Returns a single prediction: `y = mx + b`.

#### `std::vector<float> getPrediction(vector<int>& xValues, float& b, float& m)`
Returns predictions for a vector of x-values.

#### `float leastSquareMinimization(vector<float>& prediction, vector<double>& trueValues)`
Returns the sum of squared residuals: `Σ(trueValue - prediction)²`.

#### `double computeR2(const vector<double>& y, const vector<double>& yHat)`
Returns R², the proportion of variance in `y` explained by the model:
```
R² = 1 - SS_res / SS_tot
```

#### `double computeMSE(const vector<double>& y, const vector<double>& yHat)`
Returns the mean squared error: `Σ(y - ŷ)² / n`.

---

### `multipleLinearRegression.cpp`

Multiple linear regression: multiple input features, one output variable.
Solves for coefficients using Ordinary Least Squares (OLS).

#### `Matrix buildDesignMatrix(const Matrix& X)`
Prepends a column of 1s to `X` so the intercept is included in the coefficient
vector automatically.

#### `Matrix transpose(const Matrix& M)`
Returns the transpose of a matrix.

#### `Matrix matMul(const Matrix& A, const Matrix& B)`
Returns the matrix product A × B.

#### `Vec matVecMul(const Matrix& A, const Vec& v)`
Returns the product of a matrix and a column vector.

#### `Vec gaussianElimination(Matrix A, Vec b)`
Solves the linear system Ax = b using Gaussian elimination with partial pivoting.
Throws `runtime_error` if the matrix is singular (collinear features).

#### `Vec fit(const Matrix& X_raw, const Vec& y)`
Fits the model by solving the Normal Equations:
```
XᵀXβ = Xᵀy
```
Returns the coefficient vector `β`, where `β[0]` is the intercept.

#### `Vec predict(const Matrix& X_raw, const Vec& beta)`
Returns predicted values: `ŷ = Xd · β`.

#### `float leastSquareMinimization(const Matrix& X_raw, const Vec& beta, const Vec& trueValues)`
Computes predictions from `X_raw` and `beta` internally, then returns the sum of
squared residuals against `trueValues`.

---

### `featureScaling.cpp`

Feature scaling methods and Euclidean norm utilities. All scalers operate
column-by-column so each feature is scaled independently.

#### `Matrix minMaxScaling(const Matrix& x)`
Scales each feature column to the range `[0, 1]`:
```
scaled = (x - min) / (max - min)
```

#### `Matrix absMaxScaling(const Matrix& x)`
Scales each feature column to the range `[-1, 1]` by dividing by the largest
absolute value in the column:
```
scaled = x / max(|x|)
```

#### `Matrix normalization(const Matrix& x)`
Divides each feature column by its Euclidean norm, producing unit-length
feature vectors:
```
scaled = x / ‖x‖
```

#### `Matrix standardization(const Matrix& x)`
Scales each row to zero mean and unit variance using the sample standard deviation:
```
scaled = (x - mean) / std
```

#### `Matrix robustScaler(const Matrix& x)`
Scales each feature column using the median and interquartile range (IQR),
making it resistant to outliers:
```
scaled = (x - median) / IQR     where IQR = Q3 - Q1
```

#### `Vec colNorms(const Matrix& x)`
Returns the Euclidean norm of each feature column:
```
‖column‖ = √(Σ xᵢ²)
```

#### `Vec rowNorms(const Matrix& x)`
Returns the Euclidean norm of each sample row:
```
‖row‖ = √(Σ xⱼ²)
```

#### `double frobeniusNorm(const Matrix& x)`
Returns the Frobenius norm — the square root of the sum of all squared elements:
```
‖X‖_F = √(Σᵢ Σⱼ xᵢⱼ²)
```

---

## Known Limitations

- `.cpp` files are included directly rather than using header files and separate
  compilation units.
- Input validation (mismatched vector sizes, empty inputs) is minimal.
- `generateRanomMatrix` has a typo in its name.
- Sample data is randomly generated rather than loaded from a file.

---

## Suggested Future Improvements

- Add `.h` header files for all function declarations.
- Add k-fold cross-validation for more robust model evaluation.
- Add Ridge regression (L2 regularization) to handle collinear features.
- Add a CSV loader to train on real datasets.
- Add gradient descent as an alternative solver to OLS.
- Add standard errors and p-values per coefficient.
- Rename `generateRanomMatrix` to `generateRandomMatrix`.