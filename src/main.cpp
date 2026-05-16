#include <iostream>
#include <vector>
#include <numeric>
#include "helperFunctions.cpp"
#include "simpleLinearRegression.cpp"
#include "multipleLinearRegression.cpp"

int main(){
    // ── Simple Linear Regression ──────────────────────────────────────────────
    std::vector<int> xVals = generateXValues(10);
    std::vector<double> yVals = generateRandomYValues(20);
    std::vector<double> trueVals;
    for(int i = 10; i < (int)yVals.size(); i++){
        trueVals.push_back(yVals[i]);
    }
    double slope = generateBestFitSlope(yVals, xVals);
    double yInt = bestFitYIntercept(yVals, xVals);
    std::vector<int> xValsToPredict = {11, 12, 13, 14, 15, 16, 17, 19, 19, 20};
    float slopeF = (float)slope;
    float yIntF  = (float)yInt;
    std::vector<float> predictions = getPrediction(xValsToPredict, yIntF, slopeF);
    float leastSquares = leastSquareMinimization(predictions, trueVals);

    std::cout << "=== Simple Linear Regression ===" << std::endl;
    std::cout << "Least Squares:  " << leastSquares << std::endl;
    std::cout << "Slope:          " << slope << std::endl;
    std::cout << "Y-Intercept:    " << yInt << std::endl;

    // ── Multiple Linear Regression ────────────────────────────────────────────
    int nSamples  = 15;
    int nFeatures = 3;
    Matrix X_all = generateRanomMatrix(nSamples, nFeatures);
    Vec    y_all = generateRandomYValues(nSamples);

    Matrix X_train(X_all.begin(),      X_all.begin() + 10);
    Matrix X_test (X_all.begin() + 10, X_all.end());
    Vec    y_train(y_all.begin(),      y_all.begin() + 10);
    Vec    y_test (y_all.begin() + 10, y_all.end());

    Vec beta = fit(X_train, y_train);
    Vec y_pred = predict(X_test, beta);
    float mlrLeastSquares = leastSquareMinimization(X_test, beta, y_test);

    std::cout << "\n=== Multiple Linear Regression ===" << std::endl;
    std::cout << "Coefficients (intercept first):" << std::endl;
    for(int i = 0; i < (int)beta.size(); i++)
        std::cout << "  b" << i << " = " << beta[i] << std::endl;
    std::cout << "Least Squares (test): " << mlrLeastSquares << std::endl;

    // ── Feature Scaling Comparison ────────────────────────────────────────────
    Matrix X_train_minMax  = minMaxScaling(X_train);
    Matrix X_train_absMax  = absMaxScaling(X_train);
    Matrix X_train_norm    = normalization(X_train);
    Matrix X_train_std     = standardization(X_train);

    Matrix X_test_minMax   = minMaxScaling(X_test);
    Matrix X_test_absMax   = absMaxScaling(X_test);
    Matrix X_test_norm     = normalization(X_test);
    Matrix X_test_std      = standardization(X_test);

    auto evalScaled = [&](const Matrix& scaledTrain, const Matrix& scaledTest, const std::string& label){
        Vec b  = fit(scaledTrain, y_train);
        float ls = leastSquareMinimization(scaledTest, b, y_test);
        std::cout << "  " << label << ": " << ls << std::endl;
    };

    std::cout << "\n=== Feature Scaling Comparison (least squares on test set) ===" << std::endl;
    evalScaled(X_train_minMax, X_test_minMax, "MinMax      ");
    evalScaled(X_train_absMax, X_test_absMax, "AbsMax      ");
    evalScaled(X_train_norm,   X_test_norm,   "Normalized  ");
    evalScaled(X_train_std,    X_test_std,    "Standardized");

    return 0;
}