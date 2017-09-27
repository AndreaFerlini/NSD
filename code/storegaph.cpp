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

    if (debug) cout << time(nullptr) << " [Adjacency List] Starting..." << endl;

    unsigned int numNodes;
    unsigned int numEdges;

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
            // cout << node << endl;
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
        if(debug) cout << time(nullptr) << "[Adjacency List]  Done..." << endl;

        graph.close();

    }else{
        cout << "[Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    delete[] adjList;

    return 0;
}


int loadAdjListCompact(string filename, bool debug){
    fstream graph;

    nDegree nodesDegree;
    graphDegree(filename, nodesDegree, debug);

    unsigned long totDegree=0;

    for (unsigned int i=0; i<nodesDegree.size; i++){
        totDegree+=nodesDegree.array[i];
    }

    unsigned int* neighboursList=new unsigned int[totDegree];  // contains all the list of neighbours in a compact way

    for (unsigned int i=0; i<nodesDegree.size; i++){
        totDegree+=nodesDegree.array[i];
    }

    unsigned int* listBegining=new unsigned int[nodesDegree.size](); // contains the index of the array neigboursList where its neignbour starts

    // initialize the array listBeginning (which index is the node ID) to point at the beginning of their list
    unsigned int pointer=0;
    for (unsigned int node_idx=0; node_idx<nodesDegree.size; node_idx++){
        listBegining[node_idx] = pointer;
        pointer+=nodesDegree.array[node_idx];
    }

    graph.open(filename, ios::in);
    if (graph.is_open()){
        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Succeed! Building Adjacency List..." << endl;
        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            if (node) {
                neighboursList[listBegining[node-1]]=neighbour;
                listBegining[node-1]++;  // Increase the pointer by one so the next time i will write the next neighbour in the correct position
            }
            if(neighbour) {
                neighboursList[listBegining[neighbour - 1]] = node;
                listBegining[neighbour -1]++;// Increase the pointer by one so the next time i will write the next neighbour in the correct position
            }
        }

        // reset to the original beginning position (going backwards of a nr of steps equalto the degree of the node)
        for (unsigned int node_idx=0; node_idx<nodesDegree.size; node_idx++){
            listBegining[node_idx]-=nodesDegree.array[node_idx];
        }

        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Finished! Graph loaded." << endl;

        /// DEBUG
        if (debug) {
            cout << "  Node\t\tNeighbours" << endl;
            cout << "  ----------------------------" << endl;
            for (unsigned int node = 0; node < nodesDegree.size; node++) {
                cout << node + 1 << " -> ";
                for (unsigned int neigh_index = 0; neigh_index<nodesDegree.array[node]; neigh_index++) {
                    cout << neighboursList[listBegining[node]+neigh_index] << " ";
                }
                cout << endl;
            }
        }
        if(debug) cout << time(nullptr) << "[Compact Adjacency List]  Done..." << endl;


    }else{
        cout << "[Compact Adjacency List] Error! Unable to open the file " << filename << endl;
        return -1;
    }

    delete[] listBegining;
    delete[] neighboursList;
    graph.close();
    return 0;
}

// /// loading the graph as adjacence list (with a list)
// void loadAdjList(string filename, int numNodes){
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

//     graph.close();
//     }else{
//         cout << "unable to open the file" << endl;
//     }
//     delete [] adjList;
// }

int loadAdjMat(string filename, bool debug){
    fstream graph;
    char **AdjMat;

    if (debug) cout << time(nullptr) << " [Adjacency Matrix] Starting..." << endl;

    unsigned int numNodes;
    unsigned int numEdges;

    if (graphSize(filename, numNodes, numEdges, debug))
        return -1;


    if (debug) cout << time(nullptr) << " [Adjiacency Matrix] Allocating memory..." << endl;
    AdjMat = new char*[numNodes];

    for (int i = 0; i < numNodes; i++) {
        AdjMat[i] = new char[numNodes];
    }


/// init the matrix
    for (int row = 0; row < numNodes; row++) {
        for (int col = 0; col < numNodes; col++) {
            AdjMat[row][col] = 0;
        }
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
                    cout << (int)AdjMat[row][col] << " ";
                }

            }
            cout << endl << endl;

        }

        graph.close();

    }else{
        cout << "[Adjacency Matrix] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    for (int i = 0; i < numNodes; i++) {
        delete[] AdjMat[i];
    }
    delete[] AdjMat;
    return 0;
}


/// calculate the number of nodes and edges
int loadEdgeList(string filename, bool debug){
    fstream graph;
    pair<int,int> *edgeArray = NULL;

    if (debug) cout << time(nullptr) << " [Edge List] Starting..." << endl;

    unsigned int numNodes;
    unsigned int numEdges;

    if (graphSize(filename, numNodes, numEdges, debug))
        return -1;

    if (debug) cout << time(nullptr) << " [Edge List] Opening file..." << endl;

    graph.open(filename, ios::in);
    edgeArray =  new pair<int,int> [numEdges];

    /// TODO not efficient
    for(int i=0; i<numEdges; i++){
        edgeArray[i].first = 0;
        edgeArray[i].second = 0;
    }

    if (graph.is_open()){
        if (debug) cout << time(nullptr) << " [Edge List] Succeed! Loading Edges..." << endl;
        int node, neighbour;
        int e=0;

        while(!graph.eof()){
            graph >> edgeArray[e].first >> edgeArray[e].second;
            e++;
        }

        /// DEBUG
        if (debug){
            for(int i=0; i<numEdges; i++){
                cout << edgeArray[i].first << " " << edgeArray[i].second << endl;
            }
        }

        if (debug) cout << time(nullptr) << " [Edge List] Done!..." << endl;

        graph.close();


    }else{
        cout << "[Edge List] Error! Unable to open the file " << filename << endl;
        return -1;
    }
    delete [] edgeArray;
    return 0;
}