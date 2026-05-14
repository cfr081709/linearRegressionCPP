#include <vector>
#include <iostream>
#include <algorithm>

double fit(std::vector<std::vector<float>> baseMatrix){
    std::vector<std::vector<float>> interceptMatrix(baseMatrix.size(), std::vector<float>(baseMatrix[0].size() + 1, 0));
    for(int i = 0; i < baseMatrix.size(); i++){
        for(int j = 0; j < baseMatrix[0].size(); j++){
            interceptMatrix[i][j] = baseMatrix[i][j];

        }
    }
}


