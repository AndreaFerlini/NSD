//
// Created by Luca De Mori on 23/09/2017.
//

#include "storegaph.h"

/// TODO
////     using a set may not be the fastest choice
////     but actually it removes duplicates
////     preventing us from using unique() on a list

//// TODO Try to implement compact storing (array of adjacencies pointed by array of nodes + array of degree)

/// loading the graph as adjacence list (with a set)
int loadAdjList(string filename, bool debug){
    fstream graph;
    set<int> *adjList;

    unsigned long numNodes;
    unsigned long numEdges;

    if (graphSize(filename, numNodes, numEdges, debug))
        return -1;


    if (debug) cout << time(nullptr) << " [Adjacency List] Opening file..." << endl;

    graph.open(filename, ios::in);

    adjList =  new set<int>[numEdges];

    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Adjacency List] Succeed! Building Adjacency List..." << endl;
        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            adjList[node-1].insert(neighbour);
            adjList[neighbour-1].insert(node);
        }
        if(debug) cout << time(nullptr) << "[Adjacency List] Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug) {
            cout << "  Node\t\tNeighbours" << endl;
            cout << "  ----------------------------" << endl;
            for (int i = 0; i < numNodes; i++) {
                cout << i + 1 << " -> ";
                for (set<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                    cout << *it << " ";
                }
                cout << endl;
            }
        }


    }else{
        cout << "[Adjacency List] Error! Unable to open the file " << filename << endl;
    }
    delete[] adjList;
    graph.close();
}


// /// loading the graph as adjacence list (with a list)
// void loadAdjList(string filename, long numNodes){
//     fstream graph;
//     list<int> *adjList = NULL;

//     cout << "loading the graph as an adjacence list" << endl;

//     graph.open(filename, ios::in);
//     adjList =  new list<int> [numNodes];

//     /// for some reasons not necessary to reset the content of the list

//     if (graph.is_open()){
//         cout << "graph is open" << endl;
//         int node, neighbour;

//         while(!graph.eof()){
//             node = 0;
//             neighbour = 0;

//             graph >> node >> neighbour;
//             adjList[node-1].push_front(neighbour);
//             adjList[neighbour-1].push_front(node);
//         }
//         /// DEBUG
//         for(int i=0; i<numNodes; i++){
//             cout << i+1 << "->";
//             for (list<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
//                 cout << *it << " ";
//             }
//             cout << endl;
//         }
//         cout << "graph loaded" << endl << endl;

//     }else{
//         cout << "unable to open the file" << endl;
//     }
//     delete [] adjList;
//     graph.close();
// }

int loadAdjMat(string filename, bool debug){
    fstream graph;
    unsigned **AdjMat;

    unsigned long numNodes;
    unsigned long numEdges;

    if (graphSize(filename, numNodes, numEdges, debug))
        return -1;


    if (debug) cout << time(nullptr) << " [Adjiacency Matrix] Allocating memory..." << endl;
    AdjMat = new unsigned*[numNodes];

    for (int i = 0; i < numNodes; i++) {
        AdjMat[i] = new unsigned[numNodes];
    }


/// init the matrix
    for (int row = 0; row < numNodes; row++) {
        for (int col = 0; col < numNodes; col++) {
            AdjMat[row][col] = 0;
        }
        cout << endl;
    }

    if (debug) cout << time(nullptr) << " [Adjiacency Matrix] Opening the file..." << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        if (debug) cout << time(nullptr) << " [Adjiacency Matrix] Succeed! Building Adjacency Matrix..." << endl;
        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;
            graph >> node >> neighbour;
            if ((node != 0 && neighbour != 0)){
                AdjMat[node-1][neighbour-1] = 1;
            }
        }
        if (debug) cout << time(nullptr) << " [Adjiacency Matrix] Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug){
            cout << endl << "\tAdjcency Matrix" << endl << "\t   ";

            for (int col = 0; col < numNodes; col++) {
                cout << col+1 << " ";
            }
            cout << endl << "\t";
            for (int col = 0; col < numNodes; col++) {
                cout << "--";
            }

            for (int row = 0; row < numNodes; row++) {
                cout << endl << row+1 << "\t|  ";
                for (int col = 0; col < numNodes; col++) {
                    cout << AdjMat[row][col] << " ";
                }

            }
            cout << endl << endl;

        }


    }else{
        cout << "[Adjacency Matrix] Error! Unable to open the file " << filename << endl;
    }
    for (int i = 0; i < numNodes; i++) {
        delete[] AdjMat[i];
    }
    delete[] AdjMat;
    graph.close();
}