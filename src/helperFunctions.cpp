#include <cmath>
#include <vector>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

using Matrix = vector<vector<double>>;
using Vec = vector<double>;

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

Matrix absMaxScaling(const Matrix& x) {
    Matrix scaled = x;

    int nSamples  = x.size();
    int nFeatures = x[0].size();

    for (int f = 0; f < nFeatures; f++) {
        double maxVal = std::numeric_limits<double>::lowest();
        for (int i = 0; i < nSamples; i++)
            maxVal = std::max(maxVal, std::abs(x[i][f]));
        if (maxVal != 0.0) {
            for (int i = 0; i < nSamples; i++)
                scaled[i][f] = x[i][f] / maxVal;
        }
    }
    return scaled;
}

Matrix minMaxScaling(const Matrix& x) {
    int nSamples  = x.size();
    int nFeatures = x[0].size();

    Matrix scaled(nSamples, Vec(nFeatures));

    for (int f = 0; f < nFeatures; f++) {
        double minVal = std::numeric_limits<double>::max();
        double maxVal = std::numeric_limits<double>::lowest();


        for (int i = 0; i < nSamples; i++) {
            if (x[i][f] < minVal) minVal = x[i][f];
            if (x[i][f] > maxVal) maxVal = x[i][f];
        }

        double denominator = maxVal - minVal;

        for (int i = 0; i < nSamples; i++) {
            scaled[i][f] = (denominator != 0.0)
                ? (x[i][f] - minVal) / denominator
                : 0.0;
        }
    }

    return scaled;
}

Matrix normalization(const Matrix& x) {
    int nSamples  = x.size();
    int nFeatures = x[0].size();

    Matrix scaled(nSamples, Vec(nFeatures));
    Vec norms(nFeatures, 0.0);

    for (int f = 0; f < nFeatures; f++) {
        double sum = 0.0;
        for (int i = 0; i < nSamples; i++)
            sum += x[i][f] * x[i][f];
        norms[f] = std::sqrt(sum);
    }

    for (int f = 0; f < nFeatures; f++) {
        for (int i = 0; i < nSamples; i++) {
            scaled[i][f] = (norms[f] != 0.0)
                ? x[i][f] / norms[f]
                : 0.0;
        }
    }

    return scaled;
}

Matrix standardization(const Matrix& x) {
    int nSamples  = x.size();
    int nFeatures = x[0].size();

    Matrix scaled(nSamples, Vec(nFeatures));

    for (int i = 0; i < nSamples; i++) {
        double sum  = std::accumulate(x[i].begin(), x[i].end(), 0.0);
        double mean = sum / nFeatures;

        double variance = 0.0;
        for (double val : x[i])
            variance += std::pow(val - mean, 2);
        variance /= (nFeatures - 1);

        double stdDev = std::sqrt(variance);

        for (int j = 0; j < nFeatures; j++) {
            scaled[i][j] = (stdDev != 0.0)
                ? (x[i][j] - mean) / stdDev
                : 0.0;
        }
    }

    return scaled;
}

Matrix loadCSV(const std::string& filename, bool hasHeader = true) {
    Matrix data;
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    std::string line;

    if (hasHeader)
        std::getline(file, line);

    while (std::getline(file, line)) {
        Vec row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            try {
                row.push_back(std::stod(cell));
            } catch (...) {
                throw std::runtime_error("Non-numeric value found: " + cell);
            }
        }
        if (!row.empty())
            data.push_back(row);
    }

    return data;
}

