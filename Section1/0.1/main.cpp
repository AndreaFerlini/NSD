//
//  main.cpp
//  Practical1
//
//  Created by Andrea Ferlini on 19/09/2017.
//  Copyright © 2017 Andrea Ferlini. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <set>

using namespace std;

// functions
int graphSize(string filename, unsigned long &numNodes, unsigned long &numEdges);
int countDegree(string filename, unsigned long numNodes);
int cleaningData(string filename);

int main(int argc, const char * argv[]) {
    
    string filename = "/Users/AndreaFerlini/Downloads/actor-movie/out.actor-movie";
    // string filename = "/Users/AndreaFerlini/Downloads/com-amazon/out.com-amazon";
    // string filename = "/Users/AndreaFerlini/Downloads/actor-collaboration/out.actor-collaboration";
    // string filename = "a.graphs/sample.practical1.graph";
    
    unsigned long nodes;
    unsigned long edges;
    long start, end;
    
    start = time(NULL);
    cout << "graphSize call" << endl;
    
    graphSize(filename, nodes, edges);
    //countDegree(filename, nodes);
    //cleaningData(filename);
    //graphSize(filename, nodes, edges);
    end = time(NULL);
    cout << end-start << endl;
    return 0;
}

/// calculate the number of nodes and edges
int graphSize(string filename, unsigned long &numNodes, unsigned long &numEdges){
    fstream graph;
    numNodes = 0;
    numEdges = 0;

    cout << "calculating the size of the graph" << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        cout << "graph is open" << endl;
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
    }else{
        cout << "unable to open the file" << endl;
        return -1;
    }
    
    cout << "Nodes: " << numNodes << endl;
    cout << "Edges: " << numEdges << endl << endl;
    graph.close();
    return 0;
}

/// calculate the degree of each node
int countDegree(string filename, unsigned long numNodes){
    fstream graph;
    int *nodeArray = new int [numNodes];
    int node, neighbour;
    
    cout << "calculating the degree of each node of the graph" << endl;

    graph.open(filename, ios::in);
    if (graph.is_open()){
        cout << "graph is open" << endl;
        /// reset the memory allocated for nodeArray
        memset (nodeArray, 0 ,sizeof(int)*numNodes);
        while(!graph.eof()){
                node = 0;
                neighbour = 0;

                graph >> node >> neighbour;
                nodeArray[node-1] ++;
                nodeArray[neighbour-1] ++;
        }
        for (int i=0; i<numNodes; i++){
            cout << "degree of node: " << i+1 << " = " << nodeArray[i] << endl;
        }
    }else{
        cout << "unable to open the file" << endl;
        return -1;
    }
    graph.close();
    delete [] nodeArray;
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