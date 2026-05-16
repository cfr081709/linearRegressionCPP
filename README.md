# Linear Regression in C++

## Overview

This project implements simple and multiple linear regression from scratch in C++,
with no external dependencies. It generates random sample data, fits each model,
makes predictions, reports least squares error, and compares the effect of different
feature scaling methods.

---

## Models

### Simple Linear Regression

Fits a straight line to one input variable and one output variable:

```
y = mx + b
```

- `m` — slope of the best-fit line
- `b` — y-intercept of the best-fit line

### Multiple Linear Regression

Fits a linear model to multiple input features:

```
y = b0 + b1*x1 + b2*x2 + ... + bn*xn
```

Coefficients are solved using Ordinary Least Squares (OLS) via the Normal Equations:

```
β = (XᵀX)⁻¹ Xᵀy
```

The system is solved with Gaussian elimination rather than explicit matrix inversion.

---

## Feature Scaling

Five scaling methods are implemented, all operating column-by-column (per feature):

| Method | Formula | Best used when |
|---|---|---|
| MinMax | `(x - min) / (max - min)` | No outliers, need `[0, 1]` range |
| AbsMax | `x / max(|x|)` | Need `[-1, 1]` range |
| Normalization | `x / ‖x‖` | Need unit-length feature vectors |
| Standardization | `(x - mean) / std` | Normally distributed features |
| Robust | `(x - median) / IQR` | Data contains outliers |

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

## Output

```
=== Simple Linear Regression ===
Least Squares:  ...
Slope:          ...
Y-Intercept:    ...

=== Multiple Linear Regression ===
Coefficients (intercept first):
  b0 = ...
  b1 = ...
  b2 = ...
  b3 = ...
Least Squares (test): ...

=== Feature Scaling Comparison (least squares on test set) ===
  MinMax      : ...
  AbsMax      : ...
  Normalized  : ...
  Standardized: ...
  Robust      : ...

=== Euclidean Norms (training matrix) ===
  Column norms: ...
  Row norms:    ...
  Frobenius:    ...
```

Because the sample data is randomly generated, values change on every run.