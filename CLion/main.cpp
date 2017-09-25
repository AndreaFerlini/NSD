#include <iostream>
#include "storegaph.h"
#include <string>
#include <ctime>
#include <cstring>

using namespace std;


int main(int argc, char *argv[]) {


    string  filename,
            distr_file;

    filename = "../graphs/out.com-amazon";
    distr_file = "../plots/com-amazon.distr";


    string command = "../graphs/clear_graph_file.sh " + filename;
    system(command.c_str());

    unsigned int nodes;
    unsigned int edges;
    int start, end;
    bool debug = false;

    start = time(nullptr);

/// --- calculate number of nodes and edges---
//    if (graphSize(filename, nodes, edges, debug))
//        return -1;
/// ------------------------------------------

/// --- calculate the degree of the graph ---
//    {
//        nDegree degreeArray;
//        if (graphDegree(filename, degreeArray, debug))
//            return -1;
//        degreeArray.print();
//    }
/// ------------------------------------------


/// --- clear self-loop and double edges ---
//    if (cleaningData(filename, debug))
//        return -1;

/// ------------------------------------------


/// --- calculate size, degree array, min, max and avg degree, density ---
    {
        gStats Statistics;

        if (graphStats(filename, Statistics, debug))
            return -1;

        Statistics.print();
        //Statistics.degreeArray.print();
    }
/// --------------------------------------------------------


/// --------- load graph as adjacency list ---------
//    {
//        if (loadAdjList(filename, true))
//            return -1;
//    }

/// --------------------------------------------------------


/// --------- load graph as adjacency matrix ---------

/// ------------------------------------------------------------



///// --------- load graph as adjacency matrix ---------
//    {
//        if (loadEdgeList(filename, false))
//            return -1;
//    }
/// ------------------------------------------------------------



/// --------- load graph as adjacency list in compact way ---------
//    {
//        if (loadAdjListCompact(filename, true))
//            return -1;
//    }
/// ------------------------------------------------------------


/// --- calculate degree distributuion and plot the histogram ---
    {
        if (degreeDistribution(filename, distr_file, debug))
            return -1;


        command = "cd ../plots && ./plot_degree_distribution.sh " + distr_file;
        system(command.c_str());
    }
/// ------------------------------------------------------------


    end = time(nullptr);
    cout << endl << "Program executed in: " << end - start << "s" << endl;
    //... some more code
    return 0;

}
