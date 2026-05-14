#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0.0, 1.0);

double generateRandomValue(){
    return dis(gen);
}

std::vector<int> generateXValues(int n){
    std::vector<int> xValues;
    for(int i = 0; i < n; i++){
        xValues.push_back(i);
    }
    return xValues;
}

std::vector<double> generateRandomYValues(int n){
    std::vector<double> yValues;
    for(int i = 0; i < n; i++){
        yValues.push_back(dis(gen));
    }
    return yValues;
}

std::vector<std::vector<double>> generateRanomMatrix (int length, int width){
    std::vector<std::vector<double>> matrix(length, std::vector<double>(width, 0));
    for(int i = 0; i < length; i++){
        for(int j = 0; j < width; j++){
            matrix[i][j] = generateRandomValue();
        }
    }
    return matrix;
}