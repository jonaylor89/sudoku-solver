#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

typedef struct {
    vector<int> adj;
    int color = 0;
    int weight = 0;
    int degree = 0;
} NodeInfo;

map<int, NodeInfo> graph;
int originalNumColors = 0;

vector<string> splitLine(string *line) {
    vector<string> parts;
    stringstream ss(*line);
    string buffer;
    while (ss>>buffer) {
        parts.push_back(buffer);
    }
    return parts;
}

int readInGraph(string inputFile) {
    ifstream file(inputFile);
    string line;
    getline(file, line);
    vector<string> parts = splitLine(&line);
    int numNodes = atoi(parts[0].c_str());
    int numEdges = atoi(parts[1].c_str());
    printf("Graph has %i nodes and %i edges\n", numNodes, numEdges);
    for (int i = 0; i < numNodes; i++) {
        NodeInfo nodeInfo;
        graph.insert(make_pair(i, nodeInfo));
    }
    for (int i = 0; i < numEdges; i++) {
        getline(file, line);
        parts = splitLine(&line);

        int from = atoi(parts[0].c_str()) - 1; // to fix the awful 1 indexing...
        int to = atoi(parts[1].c_str()) - 1;
        graph[from].adj.push_back(to);
        graph[to].adj.push_back(from);
    }

    getline(file, line);
    parts = splitLine(&line);
    for (int i = 0; i < numNodes; i++) {
        graph[i].color = atoi(parts[i].c_str());
        originalNumColors = max(originalNumColors, graph[i].color);
    }
    return numNodes;
}

void printGraph(int numNodes) {
    int numColors = 0;
    for (int i = 0; i < numNodes; ++i) {
        numColors = max(graph[i].color, numColors);
        printf("Node %i has color %i and is adjacent to:\t", i, graph[i].color);
        for (int j = 0; j < graph[i].adj.size(); j++) {
            printf("%i ", graph[i].adj[j]);
        }
        printf("\n");
    }
    printf("%i colors in the graph\n", numColors);
}

int minElementNotIn(vector<int> elements, int numNodes) {
    set<int> possibilities;
    for (int i = 1; i < numNodes + 1; ++i) {
        possibilities.insert(i);
    }
    for (int j = 0; j < elements.size(); ++j) {
        possibilities.erase(elements[j]);
    }
    vector<int> possVec(possibilities.begin(), possibilities.end());
    return *min_element(possibilities.begin(), possibilities.end());
}

std::random_device rd;
std::mt19937 gen(rd());

int random(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

map<int, NodeInfo> assignWeights(map<int, NodeInfo> g) {
    vector<int> weights;
    for (int i = 0; i < g.size(); ++i) {
        int weight = random(0, (g.size() * 100));
        while (std::find(weights.begin(), weights.end(), weight) != weights.end()) {
            weight = random(0, (g.size() * 100)); // already used this weight lets reroll...
        }
        g[i].weight = weight;
        weights.push_back(weight);
//        printf("weight is %i\n", weight);
    }
    return g;
}

bool compareByDegree(const NodeInfo &a, const NodeInfo &b) {
    // printf("a has %i neighbors b has %i neighbors\n",a.adj.size(),b.adj.size());
    return a.adj.size() > b.adj.size();
}

map<int, NodeInfo> jonesPlassmann(map<int, NodeInfo> g, int numNodes) {
    map<int, NodeInfo> u = assignWeights(g);
    vector<NodeInfo> nodes;
    for (int i = 0; i < numNodes; i++) {
        nodes.push_back(u[i]);
    }
    sort(nodes.begin(), nodes.end(), compareByDegree);
    printf("max degree is %i\n",nodes[0].adj.size());
//#pragma omp parallel for
    for (int i = 0; i < numNodes; i++) {
        vector<int> neighbors = u[i].adj;
        vector<int> neighborColors;
        for (int j = 0; j < neighbors.size(); j++) {
            neighborColors.push_back(u[neighbors[j]].color);
        }
        int newColor = minElementNotIn(neighborColors, numNodes);
        u[i].color = newColor;
    }
    return u;
}

void writeOutput(int numNodes, string outputFile) {
    int numColors = 0;
    stringstream ss;
    string outputPath = outputFile;
    if (outputFile.length() == 0) {
        outputPath = "./output.txt";
    }
    for (int i = 0; i < numNodes; i++) {
        numColors = max(graph[i].color, numColors);
        ss<<graph[i].color;
        ss<<" ";
    }
    printf("%i\n", (numColors - originalNumColors));
    std::cout<<ss.str()<<endl;
    ofstream out(outputPath);
    out<<(numColors - originalNumColors)<<endl;
    out<<ss.str()<<endl;
    out.close();
}


int main(int argc, char *argv[]) {
//    string input = "../inputs/input.txt";
//    string input = "../inputs/sample2.txt";
//    string input = "../inputs/sample3.txt";
//    string input = "../inputs/sample4.txt";
//    string input = "../inputs/sample5.txt";
    string input = "../inputs/sample6.txt";
//    string input = "../inputs/coloringSudoku.txt";
    string output;
    if (argc > 1) {
        input = argv[1];
    }
    if (argc > 2) {
        output = argv[2];
    }

    struct timespec start, end;
    int numNodes = readInGraph(input);

//    printGraph(numNodes);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    graph = jonesPlassmann(graph, numNodes);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t diff = (1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec) / 1e6;
//    printGraph(numNodes);
    printf("The Jones-Plassmann algorithm took %llu ms CPU time.\n", (long long unsigned int) diff);

    writeOutput(numNodes, output);
    return 0;
}