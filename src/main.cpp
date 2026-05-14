#include <random>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

std::vector<int> generateXValues(int n){
    std::vector<int> xValues;
    for(int i = 0; i < n; i++){
        xValues.push_back(i);
    }
    return xValues;
}

std::vector<double> generateRandomYValues(int n){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    std::vector<double> yValues;
    for(int i = 0; i < n; i++){
        yValues.push_back(dis(gen));
    }
    return yValues;
}

std::vector<double> generateSlopeAndYIntercept(std::vector<int> xValues, std::vector<double> yValues){
    int index;
    auto it = std::find(xValues.begin(), xValues.end(), 0);
    if(it != xValues.end()){
        index = std::distance(xValues.begin(), it);
    }
    else {
        exit(1);
    }
    double a = yValues.at(index);
    double yValuesAdded = 0.0;
    for(int i = 0; i < yValues.size(); i++){
        yValuesAdded += yValues[i];
    }
    double m = yValuesAdded/(double) xValues.size();
    std::vector<double> values;
    values.push_back(a);
    values.push_back(m);
    return values;
}

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
        summanationYValuesSubtractedByM += yValues[i] - bestFitSlope;
    }
    double yInterceptNumerator = summanationYValuesSubtractedByM - xValueSummanation;
    double bestFitYIntercept = yInterceptNumerator / n;
    return bestFitYIntercept;
}

float getPrediction(float x, float a, float m){
    float value = (m * x) + a;
    return value;
}

int main(){
    std::vector<double> yValues = generateRandomYValues(5);
    std::vector<int> xValues = generateXValues(5);
    double bValue = bestFitYIntercept(yValues, xValues);
    double mValue = generateBestFitSlope(yValues, xValues);
    return 0;
}