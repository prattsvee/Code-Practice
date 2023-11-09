#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int INF = 9999; // A large number representing infinity

void floydWarshall(std::vector<std::vector<int>>& graph, int n, int caseNumber, std::ofstream& outputFile) {
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, 0));

    // Initialize dist matrix with graph values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Output to console
    std::cout << "Problem " << caseNumber << ": n = " << n << std::endl;

    // Output original adjacency matrix as "P matrix" to console
    std::cout << "P matrix:" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; i++) {
        std::cout << "V" << i + 1 << "-Vj: shortest path and length" << std::endl;
        outputFile << "V" << i + 1 << "-Vj: shortest path and length" << std::endl;
        for (int j = 0; j < n; j++) {
            //std::cout << "V" << i + 1 << " V" << j + 1 << ": ";
            //outputFile << "V" << i + 1 << " V" << j + 1 << ": ";
            if (dist[i][j] != INF) {
                std::cout << "V" << i + 1 << " ";
                outputFile << "V" << i + 1 << " ";
                for (int k = 0; k < n; k++) {
                    if (k != i && k != j && dist[i][k] != INF && dist[k][j] != INF && dist[i][j] == dist[i][k] + dist[k][j]) {
                        std::cout << "V" << k + 1 << " ";
                        outputFile << "V" << k + 1 << " ";
                    }
                }
                std::cout << "V" << j + 1 << ":" << dist[i][j] << std::endl;
                outputFile << "V" << j + 1 << ":" << dist[i][j] << std::endl;
            } else {
                std::cout << "No path" << std::endl;
                outputFile << "No path" << std::endl;
            }
        }
    }

    std::cout << std::endl;
    outputFile << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sampleinputfile.txt>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::ofstream outputFile("output.txt");
    if (!outputFile) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    int caseNumber = 1;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find("n = ") != std::string::npos) {
            int n = std::stoi(line.substr(line.find("n = ") + 4));

            std::vector<std::vector<int>> graph(n, std::vector<int>(n, 0));

            // Read the adjacency matrix
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    inputFile >> graph[i][j];
                }
            }

            floydWarshall(graph, n, caseNumber, outputFile);

            caseNumber++;
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
