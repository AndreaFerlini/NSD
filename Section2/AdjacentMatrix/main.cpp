//
//  main.cpp
//  Practical1
//
//  Created by Andrea Ferlini on 20/09/2017.
//  Copyright © 2017 Andrea Ferlini. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <set>

using namespace std;

// functions
long nodeCounter(string filename);
void loadAdjMat(string filename, const long numNodes, unsigned** AdjMat);

int main(int argc, const char * argv[]) {
    
    // string filename = "/Users/AndreaFerlini/Downloads/actor-movie/out.actor-movie";
    // string filename = "/Users/AndreaFerlini/Downloads/com-amazon/out.com-amazon";
    // string filename = "/Users/AndreaFerlini/Downloads/actor-collaboration/out.actor-collaboration";
    string filename = "a.graphs/sample.practical1.graph";

    long nodes;
    long start, end;
    unsigned** AdjMArtix;

    start = time(NULL);
    cout << nodeCounter(filename) << endl << endl;
    nodes = nodeCounter(filename);
    loadAdjMat(filename, nodes, AdjMArtix);

    end = time(NULL);
    cout << "enlapsed time: " << end-start << endl;
    return 0;
}

///
long nodeCounter(const string filename){
    fstream graph;
    long node = 0;
    long countNode = 0;
    cout << "Counting the nodes: opening the file..." << endl;
    graph.open(filename, fstream::in);
    if(graph.is_open()){
        cout << "File open. Counting..." << endl;
        while(!graph.eof()){
            graph >> node;
            if(node>countNode) countNode=node;
        }
    }else{
        cout << "[ERROR] Counting the nodes: unable to open the file" << endl;
    }
    
    graph.close();
    return countNode;
}

/// calculate the number of nodes and edges
void loadAdjMat(string filename, const long numNodes, unsigned** AdjMat){
	fstream graph;
	
    cout << "Writing adjacent matrix: allocating memory..." << endl;
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

    cout << "Writing adjacent matrix: opening the file..." << endl;
    graph.open(filename, ios::in);
    if (graph.is_open()){
        cout << "File open. Writing..." << endl;
		int node, neighbour;

		while(!graph.eof()){
			node = 0;
			neighbour = 0;
			graph >> node >> neighbour;
			if ((node != 0 && neighbour != 0)){
                AdjMat[node-1][neighbour-1] = 1;
            }
		}

		/// DEBUG
		cout << endl << "Adjcency Matrix" << endl;
		for (int row = 0; row < numNodes; row++) {
			for (int col = 0; col < numNodes; col++) {
				cout << AdjMat[row][col] << " ";
			}
			cout << endl;
		}

	}else{
		cout << "[ERROR] Writing adjacent matrix: unable to open the file" << endl;
	}
	for (int i = 0; i < numNodes; i++) {
		delete[] AdjMat[i];
	}
	delete[] AdjMat;
	graph.close();
}