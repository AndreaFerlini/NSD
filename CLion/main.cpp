#include <iostream>
#include "storegaph.h"
#include <ctime>

using namespace std;

int main() {
    string filename = "../graphs/test0.graph";
    //string filename = "/Users/AndreaFerlini/Downloads/actor-movie/out.actor-movie";
    // string filename = "/Users/AndreaFerlini/Downloads/com-amazon/out.com-amazon";
    // string filename = "/Users/AndreaFerlini/Downloads/actor-collaboration/out.actor-collaboration";
    // string filename = "a.graphs/sample.practical1.graph";

    unsigned long nodes;
    unsigned long edges;
    double start, end;

    start = time(NULL);

    if (graphSize(filename, nodes, edges, true))
        return -1;

    if (countDegree(filename, true))
        return -1;

    /*if (cleaningData(filename))
        return -1;
*/

    if (loadAdjList(filename,true))
        return -1;

    if (loadAdjMat(filename, true))
        return -1;

    end = time(NULL);
    cout << end-start << endl;
    return 0;
}