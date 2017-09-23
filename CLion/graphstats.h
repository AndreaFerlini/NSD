//
// Created by Luca De Mori on 23/09/2017.
//

#ifndef CLION_GRAPHSTATS_H
#define CLION_GRAPHSTATS_H

#include <iostream>
#include <fstream>
#include <set>
#include <ctime>

using namespace std;

/// functions
// Count nodes and Edges and return the value in the variables numNodes and numEdges
int graphSize(string filename, unsigned long &numNodes, unsigned long &numEdges, bool debug="false");

// Count the number of neigbours and print them on the screen
int countDegree(string filename, bool debug="true");

// TODO: CHECK THIS FUNCTION
// Clear self-loop and duplicate edges in filename
int cleaningData(string filename, bool debug="false");

#endif //CLION_FUNCTIONS_H
