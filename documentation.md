# Linear Regression C++ Documentation

## Overview

This project demonstrates a basic linear regression workflow in C++. The current
working implementation focuses on simple linear regression: fitting a straight
line to one input variable and one output variable, then using that line to make
predictions.

The model uses the equation:

```text
y = mx + b
```

Where:

- `y` is the predicted output value.
- `x` is the input value.
- `m` is the slope of the best-fit line.
- `b` is the y-intercept of the best-fit line.

The program generates sample data, calculates the slope and intercept, predicts
new values, and reports the total squared error for the predictions.

## Project Structure

```text
linearRegressionCPP/
  README.md
  documentation.md
  license.txt
  src/
    main.cpp
    helperFunctions.cpp
    simpleLinearRegression.cpp
    multipleLinearRegression.cpp
    program.exe
```

## Build And Run

From the project root, compile the program with `g++`:

```powershell
g++ src/main.cpp -o src/program.exe
```

Then run it:

```powershell
.\src\program.exe
```

The program prints:

- The least square minimization result
- The generated best-fit slope
- The generated y-intercept

Because the sample `y` values are randomly generated, the output changes each
time the program runs.

## Program Flow

The main program in `src/main.cpp` performs these steps:

1. Generates 10 x-values using `generateXValues(10)`.
2. Generates 20 random y-values using `generateRandomYValues(20)`.
3. Stores the last 10 y-values as true values for comparison.
4. Calculates the best-fit slope with `generateBestFitSlope`.
5. Calculates the y-intercept with `bestFitYIntercept`.
6. Predicts values for a hardcoded list of future x-values.
7. Calculates the sum of squared prediction errors.
8. Prints the results to the console.

## Source File Reference

### `src/helperFunctions.cpp`

Contains helper functions for generating random values and test data.

#### `double generateRandomValue()`

Returns a random floating-point value between `0.0` and `1.0`.

#### `std::vector<int> generateXValues(int n)`

Generates integer x-values from `0` up to `n - 1`.

Example:

```cpp
std::vector<int> xVals = generateXValues(10);
```

This returns:

```text
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
```

#### `std::vector<double> generateRandomYValues(int n)`

Generates `n` random y-values between `0.0` and `1.0`.

#### `std::vector<std::vector<double>> generateRanomMatrix(int length, int width)`

Generates a two-dimensional matrix of random double values.

Note: the function name currently contains a typo: `generateRanomMatrix` should
likely be `generateRandomMatrix`.

### `src/simpleLinearRegression.cpp`

Contains the simple linear regression implementation.

#### `double generateBestFitSlope(std::vector<double> yValues, std::vector<int> xValues)`

Calculates the slope of the best-fit line using the least squares formula:

```text
m = (n * sum(xy) - sum(x) * sum(y)) / (n * sum(x^2) - sum(x)^2)
```

Parameters:

- `yValues`: known output values
- `xValues`: known input values

Returns the slope as a `double`.

Important: `xValues` and `yValues` should contain the same number of elements.
The function uses the size of `xValues` as the number of data points.

#### `double bestFitYIntercept(std::vector<double> yValues, std::vector<int> xValues)`

Calculates the y-intercept of the best-fit line:

```text
b = (sum(y) - m * sum(x)) / n
```

This function calls `generateBestFitSlope` internally.

#### `float getPrediction(float x, float b, float m)`

Predicts a single y-value using:

```text
y = mx + b
```

Parameters:

- `x`: input value
- `b`: y-intercept
- `m`: slope

Returns the predicted value as a `float`.

#### `std::vector<float> getPrediction(std::vector<int> xValues, float b, float m)`

Predicts multiple y-values from a vector of x-values.

Parameters:

- `xValues`: input values to predict
- `b`: y-intercept
- `m`: slope

Returns a vector of predicted `float` values.

#### `float leastSquareMinimization(std::vector<float> prediction, std::vector<double> trueValues)`

Calculates the sum of squared errors:

```text
sum((trueValue - prediction)^2)
```

This is used to measure how far the predictions are from the expected values.

Important: `prediction` and `trueValues` should contain the same number of
elements.

### `src/multipleLinearRegression.cpp`

This file starts a multiple linear regression implementation with a `fit`
function, but it is currently incomplete.

Current behavior:

- Creates an `interceptMatrix` with one extra column.
- Copies the original matrix values into the new matrix.
- Does not yet calculate regression coefficients.
- Does not currently return a value even though the function return type is
  `double`.

This file should be treated as work in progress.

## Example Usage

```cpp
std::vector<int> xVals = generateXValues(10);
std::vector<double> yVals = generateRandomYValues(20);

double slope = generateBestFitSlope(yVals, xVals);
double yIntercept = bestFitYIntercept(yVals, xVals);

std::vector<int> xValsToPredict = {11, 12, 13, 14, 15};
std::vector<float> predictions = getPrediction(xValsToPredict, yIntercept, slope);
```

## Current Limitations

- The project currently includes `.cpp` files directly inside `main.cpp`.
  A larger C++ project would usually use header files and separate compilation.
- Input validation is not currently implemented.
- Several functions assume vectors have matching sizes.
- The model uses randomly generated sample data instead of loading a dataset
  from a file.
- `multipleLinearRegression.cpp` is incomplete.
- `generateRanomMatrix` has a spelling error in its name.

## Suggested Future Improvements

- Add header files for function declarations.
- Add validation for vector sizes before calculations.
- Add dataset loading from CSV files.
- Add unit tests for slope, intercept, prediction, and error calculations.
- Complete the multiple linear regression implementation.
- Rename `generateRanomMatrix` to `generateRandomMatrix`.
- Consider returning mean squared error instead of total squared error if the
  goal is to compare models across different dataset sizes.
