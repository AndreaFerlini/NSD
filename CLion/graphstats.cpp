//
// Created by Luca De Mori on 23/09/2017.
//

#include "graphstats.h"

/// calculate the number of nodes and edges
int graphSize(string filename, unsigned long &numNodes, unsigned long &numEdges, bool debug){
    fstream graph;
    numNodes = 0;
    numEdges = 0;

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

        if(debug) cout << time(nullptr) << "[Graph Size] Done! Counting..." << endl;

    }else{
        cout << "[Graph Size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    graph.close();
    return 0;
}

/// calculate the degree of each node
//  This function build an array in which stores the number of neigbours per node. At index 0 there is the first node (ID=1)
int countDegree(string filename, bool debug){

    unsigned long numNodes;
    unsigned long numEdges;

    if (graphSize(filename, numNodes, numEdges, debug))
        return  -1;


    fstream graph;
    int *nodeArray = new int [numNodes](); // with () it's initialized with all 0s
    int node, neighbour;


    if (debug) cout << time(nullptr) << "[Graph Degree] Opening the file..." << endl;

    graph.open(filename, ios::in);

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Graph Degree] Succeed! Counting neigbours..." << endl;


        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            nodeArray[node-1]++;
            nodeArray[neighbour-1]++;
        }
        if (debug){
            cout << time(nullptr) << "[Graph Degree] Finished! Output:" << endl;
            cout << "  ID\t\tDegree" << endl;
            cout << "  ---------------------------" << endl;
            for (int i=0; i<numNodes; i++){
                 cout << "  " << i+1 << "\t" << nodeArray[i] << endl;
            }
        }

    }else{
        cout << "[Graph Size] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    graph.close();
    delete[] nodeArray;    // deallocate the array
    return 0;
}

/// cleaning the file
int cleaningData(string filename){
    fstream graph;
    set<pair<int, int> > uniqueEdge;
    graph.open(filename, ios::in);

    cout << "cleaning graph data" << endl;

    if (graph.is_open()){
        pair<int, int> edge;

        while(!graph.eof()){
            edge.first = 0;
            edge.second = 0;

            graph >> edge.first >> edge.second;

            if(edge.first != edge.second){
                uniqueEdge.insert(edge);
            }
        }
        graph.close();
        graph.open(filename, ios::out);
        cout << "writing cleaned data on the graph" << endl;
        if (graph.is_open()){
            cout << "opening the file ..." << endl;
            for (set<pair<int, int> >::iterator it=uniqueEdge.begin(); it!=uniqueEdge.end(); ++it){
                if(it == uniqueEdge.begin()){
                    graph << it->first << " " << it->second;
                }else{
                    graph << endl << it->first << " " << it->second;
                }
            }
        }else{
            cout << "unable to open the file" << endl;
            return -1;
        }
    }else{
        cout << "unable to open the file" << endl;
        return -1;
    }
    graph.close();
    cout << "DONE" << endl << endl;
    return 0;
}

