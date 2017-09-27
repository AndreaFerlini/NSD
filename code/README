--------------------------------------
Practical1.README
--------------------------------------

Authors: Andrea Ferlini, Luca De Mori
Date: 26/09/2017

--------------------------------------

1. FOLDER STRUCTURE

The main directory contains the following folders:
	
	a. /code   	: Contains all the functions
	b. /graphs 	: Where to put graph files. It contains the script to skip comments and blank lines
	c. /plot	: Contains the scripts to plot the degree distribution with gnuplot

2. CODE STRUCTURE

	2.1 FILE ARTICULATION

	The code provides two files containing the required functions.

		a. graphstats.cpp contains functions to compute the statistics of the graph:

			graphSize 	 -> computes the number of nodes
			graphDegree  -> counts the degree of each node
			graphStats 	 -> provide the overall statistics (size, degree, min, max and avg degree, density)
			cleaningData -> remove self-loops and duplicated edges in the file
			degreeDistribution -> writes a file containing the points of the degree distributon histogram

		b. storegraph.cpp contains the functions to store the graph in memory

			loadAdjList  -> Loads the graph as adjacency list
			loadAdjListCompact	-> Loads the graph as adjacency list with contiguous storage
			loadAdjMat 	 -> Load the graph as adjacency matrix
			loadEdgeList -> load the grapg as list of edges

	In graphstats.h two structures are defined. In particular:

		nDegree -> Store the array for the degree of each node
		gStats  -> Store the graph statistics

	Note: storegraph.h includes graphstats.h in order to use some functioncs


3. USAGE
	
	3.1 GRAPH FILE FORMAT

	Our program works with graphs stored in a file as a list of edges identified by its vertex (node) id separaded by a space

		x y

	where x and y are positive integers greater than 1.
	We consider that the isolated nodes (node with degree = 0) are the ones not present in the list of edges:
	Example:
		1 2
		2 4
		4 1
		------------------> 3 is an isolated node for this graph


	3.2 LAUNCH THE PROGRAM

	The file main.cpp contains already the code to run some calculations.

	Follow the steps:
		a. Uncomment the required section:
		b. Edit the variable "filename" with the path to the graph file;
		c. Edit the variable "outputFile" with the path to the file where to save the degree distribution; 
		  	the program will automatically generate also the .eps (vector image) file with the plot.
		d. Compile everything in the folder:
			g++ <program_name> main.cpp graphstats.cpp graphstats.h storegaph.cpp storegaph.h
		e. Run ./program_name
	

	4. COMMENTS ON SCALABILITY

	The code has been executed on a bunch of graphs from konect (1. orkut_link, 2. youtube_friendship, 3. youtube_affiliation, 4. _, 5. _), chosen between directed and undireced ones.

		1. 3072441 nodes | 117184899 edges | contiguous adj. list: 75s | list of edges: 40 s| adj. matrix: - 
		2. 1157827 nodes |   2987624 edges | contiguous adj. list: 1 s | list of edges: 9 s | adj. matrix: -
		3.   94238 nodes |    293361 edges | contiguous adj. list: 0 s | list of edges: 0 s | adj. matrix: 32s
		

		a. Loading the graph as list of edges is extremely fast, however this is not efficient for other pourposes;
		b. The matrix is not scalable: having an high number of edges n leads to a n*n matrix, which may be to big to fit the memory. Moreover, it implies a huge waste of space whenever the density is low;
		c. Adjacency list is more efficient than adjacency matrix in terms of memory loading. It is also more performing than a regular list of edges, since it lends itself to be used for more complex searching operations, etc.;
		d. Appling Contiguous storage to the adjacency list makes it much more faster, since it has to access only one big array.
