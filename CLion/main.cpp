#include <iostream>
#include "storegaph.h"
#include <ctime>

using namespace std;

void printHelp(){

    cout << "Usage is <graph_file> <output_file>" << endl;
//    cout << "Usage is -m <mode_id> -g <graphfile> [OPTIONS]" << endl; // Inform the user of how to use the program
//    cout << "Modes:" << endl;
//    cout << "  0  Size:" << endl;
//    cout << "  1  Nodes Degree:" << endl;
//    cout << "  2  Clear Data:" << endl;
//    cout << "  3  Statistics:" << endl;
//    cout << "OPTIONS:" << endl;
//    cout << "  -s <store_mode>  Store the graph. Modes: '1'=AdjacencyList; '2'=AdjacencyMatrix; " << endl;
//    cout << "                                           '3'=EdgeList" << endl;
//
}

int main(int argc, char* argv[]) {


    string filename;
    string outputFile;

    if (argc < 2) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        printHelp();
        return -1;
    } else {
        filename = argv[1];
        outputFile = argv[2];


//        filename = "../../graphs/with_zdn.graph";
//        outputFile = "../../graphs/with_zdn.distr";
        //string filename = "/Users/AndreaFerlini/Downloads/actor-movie/out.actor-movie";
        // string filename = "/Users/AndreaFerlini/Downloads/com-amazon/out.com-amazon";
        // string filename = "/Users/AndreaFerlini/Downloads/actor-collaboration/out.actor-collaboration";
        // string filename = "a.graphs/sample.practical1.graph";

        unsigned long nodes;
        unsigned long edges;
        long start, end;
        bool debug = false;

        start = time(nullptr);

/*
        if (graphSize(filename, nodes, edges, debug))
            return -1;
        cout << nodes << endl << edges << endl;


        nDegree degreeArray;
        if (graphSize(filename, nodes, edges, debug))
            return -1;
        degreeArray.print();


        if (cleaningData(filename, debug))
            return -1;
*/
        gStats Statistics;

        if (graphStats(filename, Statistics, debug))
            return -1;

        Statistics.print();


        if (loadAdjList(filename, debug))
            return -1;


        if (loadAdjMat(filename, debug))
            return -1;


        if (loadEdgeList(filename, debug))
            return -1;


        if (degreeDistribution(filename, outputFile, debug))
            return -1;

        end = time(nullptr);
        cout << endl << "Program executed in: " << end - start << "s" << endl;
        //... some more code

        system("gnuplot ../Plot/plot_distr.plt");
        return 0;
    }
}
