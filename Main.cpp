/* 
Fabian Martinez
12-04-18

This program is based off an AWK Language project, "Little Languages".  It parses through
airplane data from a .txt file, and graphs all the information from data points, to axes.

Graph.h:
All the necessary variables and function initializations will be found here.

Graph.cpp:
Declarations of the Graph.h fields are found here.  However, I am unable to figure out the error
of "bottom_ticks" and "left_ticks" that are vector<string> types, to compare with ints.  The data
inside the vectors are ints, and I know there exists a simple solution to parse the strings into ints,
yet it eludes me.
*/

#include "Graph.h"

using namespace std;

int main()
{
	Graph myGraph("little_languages_graph_data.txt");

	return 0;
}
