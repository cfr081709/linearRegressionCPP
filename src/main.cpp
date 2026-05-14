#include <iostream>
#include <vector>
#include "helperFunctions.cpp"
#include "simpleLinearRegression.cpp"
#include "multipleLinearRegression.cpp"

int main(){
    std::vector<int> xVals = generateXValues(10);
    std::vector<double> yVals = generateRandomYValues(20);
    std::vector<double> trueVals;
    for(int i = 10; i < yVals.size(); i++){
        trueVals.push_back(yVals[i]);
    }
    double slope = generateBestFitSlope(yVals, xVals);
    double yInt = bestFitYIntercept(yVals, xVals);
    std::vector<int> xValsToPredict = {11, 12, 13, 14, 15, 16, 17, 19, 19, 20};
    std::vector<float> predictions = getPrediction(xValsToPredict, yInt, slope);
    float leastSquares = leastSquareMinimization(predictions, trueVals);

    std::cout << "Least Square Minimization Result: " << leastSquares << std::endl;
    std::cout << "Slope: " << slope << std::endl;
    std::cout << "Y-Intercept: " << yInt << std::endl;
}