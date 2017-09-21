//
//  main.cpp
//  Practical1
//
//  Created by Andrea Ferlini on 20/09/2017.
//  Copyright © 2017 Andrea Ferlini. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include<set>

using namespace std;

// functions
long nodeCounter(string filename);
void loadAdjList(string filename, long numNodes);

int main(int argc, const char * argv[]) {
    
    // string filename = "/Users/AndreaFerlini/Downloads/actor-movie/out.actor-movie";
    // string filename = "/Users/AndreaFerlini/Downloads/com-amazon/out.com-amazon";
    // string filename = "/Users/AndreaFerlini/Downloads/actor-collaboration/out.actor-collaboration";
    string filename = "a.graphs/sample.practical1.graph";

    long nodes;
    long start, end;
    
    start = time(NULL);
    
    cout << nodeCounter(filename) << endl << endl;
    nodes = nodeCounter(filename);
    loadAdjList(filename, nodes);

    end = time(NULL);
    cout << "enlapsed time: " << end-start << endl;
    return 0;
}

///
long nodeCounter(string filename){
    fstream graph;
    long node = 0;
    long countNode = 0;
    
    graph.open(filename, ios::in);
    if(graph.is_open()){
        while(!graph.eof()){
            graph >> node;
            node > countNode ? countNode=node: NULL;
        }
    }else{
        cout << "unable to open the file" << endl;
    }
    
    graph.close();
    return countNode;
}

/// TODO
////     using a set may not be the fastest choice
////     but actually it removes duplicates
////     preventing us from using unique() on a list

/// loading the graph as adjacence list (with a set)
void loadAdjList(string filename, long numNodes){
    fstream graph;
    set<int> *adjList = NULL;

    cout << "loading the graph as an adjacence list" << endl;

    graph.open(filename, ios::in);
    adjList =  new set<int> [numNodes];
    
    /// for some reasons not necessary to reset the content of the set

    if (graph.is_open()){
        cout << "graph is open" << endl;
        int node, neighbour;

        while(!graph.eof()){
            node = 0;
            neighbour = 0;

            graph >> node >> neighbour;
            adjList[node-1].insert(neighbour);
            adjList[neighbour-1].insert(node);
        }
        /// DEBUG
        for(int i=0; i<numNodes; i++){
            cout << i+1 << "->";
            for (set<int>::iterator it = adjList[i].begin(); it != adjList[i].end(); ++it){
                cout << *it << " ";
            }
            cout << endl;
        }
        cout << "graph loaded" << endl << endl;

    }else{
        cout << "unable to open the file" << endl;
    }
    delete [] adjList;
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