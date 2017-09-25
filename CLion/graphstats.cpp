//
// Created by Luca De Mori on 23/09/2017.
//

#include "graphstats.h"

/// calculate the number of nodes and edges
int graphSize(string filename, unsigned int &numNodes, unsigned int &numEdges, bool debug){
    fstream graph;
    numNodes = 0;
    numEdges = 0;
    if (debug) cout << time(nullptr) << "[Graph Size] Begin..." << endl;

    if(debug) cout << time(nullptr) <<  "[Graph Size] Opening the file..." << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){

        if(debug) cout << time(nullptr) <<  "[Graph Size] Succeed! Counting..." << endl;

        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            numEdges++;
            if (node > numNodes){
                numNodes = node;
            }
            if (neighbour > numNodes){
                numNodes = neighbour;
            }
        }

        if(debug) cout << time(nullptr) << "[Graph Size] Done!" << endl;

    }else{
        cout << "[Graph Size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    graph.close();
    return 0;
}

/// calculate the degree of each node
//  This function build an array in which stores the number of neigbours per node. At index 0 there is the first node (ID=1)
int graphDegree(string filename, nDegree& nodeArray, bool debug){

    unsigned int numEdges;

    if (debug) cout << time(nullptr) << "[Graph Degree] Begin..." << endl;


    if (graphSize(filename, nodeArray.size, numEdges, debug))
        return  -1;

    fstream graph;

    nodeArray.array = new int[nodeArray.size]();
    int node, neighbour;

    if (debug) cout << time(nullptr) << "[Graph Degree] Opening the file..." << endl;

    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Graph Degree] Succeed! Counting neigbours..." << endl;


        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            if (node)
                nodeArray.array[node-1]++;
            if (neighbour)
                nodeArray.array[neighbour-1]++;
        }

        if (debug){
            cout << time(nullptr) << "[Graph Degree] Finished! Output:" << endl;
            cout << "  ID\tDegree" << endl;
            cout << "  ---------------------------" << endl;
            nodeArray.print();
        }


    }else{
        cout << time(nullptr) << "[Graph Degree] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    graph.close();

    // if the user have passed a pointer as reference, than i will
    if (debug) cout << time(nullptr) << "[Graph Degree] Return the array" << endl;

    return 0;
}

/// cleaning the file
int cleaningData(string filename, bool debug){
    fstream graph;
    set<pair<int, int> > uniqueEdge;
    graph.open(filename, ios::in);

    if (debug) cout << time(nullptr) << "[Data Cleaning] Begin..." << endl;
    if (debug) cout << time(nullptr) << "[Data Cleaning] Opening file reading mode..." << endl;

    if (graph.is_open()){
        pair<int, int> edge;
        if (debug) cout << time(nullptr) << "[Data Cleaning] Succeed! Cleaning the graph..." << endl;

        while(!graph.eof()){
            edge.first = 0;
            edge.second = 0;

            graph >> edge.first >> edge.second;

            if(edge.first != edge.second){
                uniqueEdge.insert(edge);
            }
        }
        graph.close();
        if (debug) cout << time(nullptr) << "[Data Cleaning] Opening file writing mode..." << endl;
        graph.open(filename, ios::out);
        if (graph.is_open()){
            if (debug) cout << time(nullptr) << "[Data Cleaning] Succeed! Writing cleaned graph..." << endl;
            for (set<pair<int, int> >::iterator it=uniqueEdge.begin(); it!=uniqueEdge.end(); ++it){
                if(it == uniqueEdge.begin()){
                    graph << it->first << " " << it->second;
                }else{
                    graph << endl << it->first << " " << it->second;
                }
            }
        }else{
            cout << time(nullptr) << "[Graph Degree] Error! Unable to open the file " << filename << endl;
            return -1;
        }
    }else{
        cout << time(nullptr) << "[Graph Degree] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    if (debug) cout << time(nullptr) << "[Data Cleaning] Done! Graph file cleaned." << endl;

    graph.close();
    return 0;
}

int graphStats(string filename, gStats& graphStatistics, bool debug){

    if(debug) cout << time(nullptr) << "[Graph stats] Calculating graph size and dnsity..." << endl;
    if (graphSize(filename, graphStatistics.nNodes, graphStatistics.nEdges, debug))
        return -1;

    graphStatistics.density=(float)graphStatistics.nNodes/(float)graphStatistics.nEdges;

    if(debug) cout << time(nullptr) << "[Graph stats] Extracting degree array..." << endl;

    if (graphDegree(filename, graphStatistics.degreeArray, debug))
        return -1;

//    if (degreeArray.size!= 0){
//        cout << "Degree From Main"<< endl;
//        for (unsigned int i=0; i<degreeArray.size; i++){
//            cout << "  " << i+1 << "\t" << degreeArray.array[i] << endl;
//        }
//    }

    graphStatistics.avgDeg = 0;
    graphStatistics.maxDeg = 0;


    if(debug) cout << time(nullptr) << "[Graph stats] Done! Computing stats..." << endl;

    unsigned int index =0;
    while (graphStatistics.degreeArray.array[index]==0) index++;
    graphStatistics.minDeg =  graphStatistics.degreeArray.array[index];
    // parse to calculate statistics
    for (unsigned int i=0; i<graphStatistics.degreeArray.size; i++){

        //average degree
        graphStatistics.avgDeg+=graphStatistics.degreeArray.array[i];


        // find zeros
        if (graphStatistics.degreeArray.array[i]){
            // max degree
            if (graphStatistics.degreeArray.array[i]>graphStatistics.maxDeg)
                graphStatistics.maxDeg=graphStatistics.degreeArray.array[i];

            // min degree
            if (graphStatistics.degreeArray.array[i]<graphStatistics.minDeg)
                graphStatistics.minDeg=graphStatistics.degreeArray.array[i];
        } else {
            graphStatistics.zeroDegNodes.insert(i + 1);
        }

    }

    graphStatistics.avgDeg=graphStatistics.avgDeg/graphStatistics.degreeArray.size;

    if(debug) cout << time(nullptr) << "[Graph stats] Succeed!" << endl;
    cout << endl;


    return 0;
}


int degreeDistribution(string graph_filename, string output_fileneme, bool debug){

    fstream graph;
    fstream distrFile;

    gStats statistics;

    if(debug) cout << time(nullptr) << "[Degree Distribution] Extracting degree array..." << endl;

    if (graphStats(graph_filename, statistics, debug))
        return -1;


    int* distrArray = new int[statistics.maxDeg+1]();

    if(debug) cout << time(nullptr) << "[Degree Distribution] Building distribution..." << endl;

    for(int degree=0;degree<=statistics.maxDeg;degree++){
        for(unsigned int node=0; node<statistics.nNodes; node++){
            if (statistics.degreeArray.array[node]==degree)
                distrArray[degree]++;
        }
    }


    if(debug) cout << time(nullptr) << "[Degree Distribution] Opening file " << output_fileneme << endl;

    distrFile.open(output_fileneme, ios::out);

    if (distrFile.is_open()){

        if(debug) cout << time(nullptr) << "[Degree Distribution] Writing distribution file " << output_fileneme << endl;

        for(int degree=0;degree<=statistics.maxDeg;degree++){
            distrFile << degree << " " << distrArray[degree] << endl;
            if(debug) cout << degree << " " << distrArray[degree] << endl;

        }

    }else{
        cout << time(nullptr) << "[Degree Distribution] Error! Unable to open the file " << output_fileneme << endl;
        return -1;
    }

    return 0;

}