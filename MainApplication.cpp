#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <stdexcept>

#include "BoardHelper.h"
#include "SimpleHillClimbing.h"
#include "SimulatedAnnealing.h"
#include "MemoryBasedSimpleHillClimbing.h"
#include "CSPSolver.h"
#include "GeneticAlgorithm.h"

class ArgumentParser {
public:
    int N, M, Q, K, tmax;
    std::string fileName, methodName;

    ArgumentParser(int argc, char* argv[]) {
        if (argc != 8) {
            throw std::invalid_argument("Usage: program N M Q K tmax fileName methodName");
        }
        N = std::stoi(argv[1]);
        M = std::stoi(argv[2]);
        Q = std::stoi(argv[3]);
        K = std::stoi(argv[4]);
        tmax = std::stoi(argv[5]);
        fileName = argv[6];
        methodName = argv[7];
    }
};

class MainApplication {
public:
    MainApplication(const ArgumentParser& args) 
        : N(args.N), M(args.M), Q(args.Q), K(args.K), tmax(args.tmax), fileName(args.fileName), methodName(args.methodName) {}

    void run() {
        double startTime = getCurrentTime();
        std::vector<std::vector<int>> finalBoard;
        
        std::unique_ptr<HillClimbing> algorithm;

        if (toLower(trim(methodName)) == "hc") {
            algorithm = std::make_unique<SimpleHillClimbing>();
            finalBoard = algorithm->execute(N, M, Q, K, startTime, tmax);
        } else if (toLower(trim(methodName)) == "sa") {
            algorithm = std::make_unique<SimulatedAnnealing>();
            finalBoard = algorithm->execute(N, M, Q, K, startTime, tmax);
        } else if (toLower(trim(methodName)) == "mhc") {
            algorithm = std::make_unique<MemoryBasedSimpleHillClimbing>();
            finalBoard = algorithm->execute(N, M, Q, K, startTime, tmax);
        } else if (toLower(trim(methodName)) == "csp") {
            CSPSolver cspSolver;
            finalBoard = cspSolver.solve(N, M, Q, K, startTime, tmax);
        } else if (toLower(trim(methodName)) == "ga") {
            GeneticAlgorithm gaSolver;
            finalBoard = gaSolver.solve(N, M, Q, K, startTime, tmax);
        } else {
            throw std::invalid_argument("Unknown method name");
        }

        double endTime = getCurrentTime();
        writeOutput(finalBoard, fileName, endTime - startTime);
    }

private:
    int N, M, Q, K, tmax;
    std::string fileName, methodName;

    double getCurrentTime() {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    std::string toLower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    std::string trim(const std::string& str) {
        auto start = str.begin();
        auto end = str.end();
        while (start != end && std::isspace(*start)) {
            ++start;
        }
        if (start == end) return "";
        do {
            --end;
        } while (std::isspace(*end));
        return std::string(start, end + 1);
    }

    void writeOutput(const std::vector<std::vector<int>>& board, const std::string& fileName, double elapsedTime) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + fileName);
        }

        for (const auto& row : board) {
            std::string line;
            for (const auto& col : row) {
                line += BoardHelper::convertToRepresentation(col) + " ";
            }
            file << line << "\n";
        }

        file << "Total Attacks: " << BoardHelper::getTotalAttack(board) << "\n";
        file << "Elapsed Time: " << elapsedTime << " seconds\n";
        file.close();
    }
};

int main(int argc, char* argv[]) {
    try {
        ArgumentParser args(argc, argv);
        MainApplication app(args);
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
