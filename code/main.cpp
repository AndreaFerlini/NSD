#include <iostream>
#include "storegaph.h"
#include <string>
#include <ctime>
#include <cstring>

using namespace std;


int main(int argc, char *argv[]) {


    string  filename,
            distr_file;

    filename = "../graphs/out.orkut-links";
    distr_file = "../plots/orkut-links.distr";

    bool is_directed= true;

    string command = "../graphs/clear_graph_file.sh " + filename;
    cout << command << endl;
    system(command.c_str());

    unsigned int nodes;
    unsigned int edges;
    int start, end;
    bool debug = false;

    start = time(nullptr);

/// --- calculate number of nodes and edges---
//    if (graphSize(filename, nodes, edges, debug))
//        return -1;
//    cout << "nodes: " << nodes << "edges: " << edges;
//    cin.get();
/// ------------------------------------------

/// --- calculate the degree of the graph ---
//    {
//        nDegree degreeArray;
//        if (graphDegree(filename, degreeArray, debug))
//            exit(-1);
//        degreeArray.print();
//    }
/// ------------------------------------------


/// --- clear self-loop and double edges ---
//    if (cleaningData(filename, debug))
//        return -1;

/// ------------------------------------------


/// --- calculate size, degree array, min, max and avg degree, density ---
//    {
//        gStats Statistics;
//
//        if (graphStats(filename, is_directed, Statistics, debug))
//            exit(-1);
//
//        Statistics.print(debug);
//        //Statistics.degreeArray.print();
//    }
//    cin.get();

/// --------------------------------------------------------


/// --------- load graph as adjacency list ---------
//    {
//        if (loadAdjList(filename, debug))
//            return -1;
//    }

/// --------------------------------------------------------


/// --------- load graph as adjacency matrix ---------
//    {
//        if (loadAdjMat(filename, debug))
//            return -1;
//    }

/// ------------------------------------------------------------



///// --------- load graph as adjacency matrix ---------
//    {
//        if (loadEdgeList(filename, debug))
//            return -1;
//    }
/// ------------------------------------------------------------



/// --------- load graph as adjacency list in compact way ---------
    {
        if (loadAdjListCompact(filename, debug))
            exit(-1);
    }
/// ------------------------------------------------------------


/// --- calculate degree distributuion and plot the histogram ---
//    {
//        if (degreeDistribution(filename, distr_file, debug))
//            return -1;
//
//
//        command = "cd ../plots && ./plot_degree_distribution.sh " + distr_file;
//        system(command.c_str());
//    }
/// ------------------------------------------------------------


    end = time(nullptr);
    cout << endl << "Program executed in: " << end - start << "s" << endl;
    //... some more code
    return 0;

}
