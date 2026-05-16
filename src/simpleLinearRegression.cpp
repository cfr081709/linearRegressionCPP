#include <vector>
#include <iostream>
#include <algorithm>

double generateBestFitSlope(std::vector<double> yValues, std::vector<int> xValues){
    int n = xValues.size();
    double xAndYSummanation = 0.0;
    for(int i = 0; i < n; i++){
        xAndYSummanation += (double)(xValues[i] * yValues[i]);
    }
    double xValueSummanation = 0.0;
    for(int i = 0; i < n; i++){
        xValueSummanation += (double)(xValues[i]);
    }
    double yValueSummanation = 0.0;
    for(int i = 0; i < n; i++){
        yValueSummanation += yValues[i];
    }
    double bestFitSlopeNumerator = ((n *xAndYSummanation) - (xValueSummanation * yValueSummanation));
    double xSquaredSummunation = 0.0;
    for(int i = 0; i < n; i++){
        xSquaredSummunation += xValues[i] * xValues[i];
    }
    double xSummanationSquared = xValueSummanation * xValueSummanation;
    double bestFitSlopeDenominator = ((n * xSquaredSummunation) - xSummanationSquared);
    double bestFitSlope = bestFitSlopeNumerator / bestFitSlopeDenominator;
    return bestFitSlope;

}

double bestFitYIntercept(std::vector<double> yValues, std::vector<int> xValues){
    int n = xValues.size();
    double bestFitSlope = generateBestFitSlope(yValues, xValues);
    double xValueSummanation = 0.0;
    for(int i = 0; i < n; i++){
        xValueSummanation += xValues[i];
    }
    double summanationYValuesSubtractedByM = 0.0;
    for(int i = 0; i < n; i++){
        summanationYValuesSubtractedByM += yValues[i];
    }
    double yInterceptNumerator = summanationYValuesSubtractedByM - (bestFitSlope * xValueSummanation);
    double bestFitYIntercept = yInterceptNumerator / n;
    return bestFitYIntercept;
}

float getPrediction(float x, float b, float m){
    float value = (m * x) + b;
    return value;
}

std::vector<float> getPrediction(std::vector<int>& xValues, float& b, float& m){
    std::vector<float> results;
    for(int i = 0; i < xValues.size(); i++){
        float value = (m * xValues[i]) + b;
        results.push_back(value);
    }
    return results;
}

float leastSquareMinimization(std::vector<float>& prediction, std::vector<double>& trueValues){
    float leastSquares = 0.0;
    for(int i = 0; i < prediction.size(); i++){
        float residual = trueValues[i] - prediction[i];
        leastSquares += residual * residual;
    }
    return leastSquares;
}

double computeR2(const std::vector<double>& y, const std::vector<double>& yHat) {
    int n = y.size();
    double yMean = 0.0;
    for (double val : y) yMean += val;
    yMean /= n;

    double SS_res = 0.0, SS_tot = 0.0;
    for (int i = 0; i < n; i++) {
        SS_res += pow(y[i] - yHat[i], 2);
        SS_tot += pow(y[i] - yMean,    2);
    }
    return 1.0 - (SS_res / SS_tot);
}

double computeMSE(const std::vector<double>& y, const std::vector<double>& yHat) {
    double sum = 0.0;
    for (int i = 0; i < (int)y.size(); i++)
        sum += pow(y[i] - yHat[i], 2);
    return sum / y.size();
}