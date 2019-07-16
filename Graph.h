#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Graph
{
public:
	int ox = 6; // offset for x-axis
	int oy = 2; // offset for y-axis
	int width = 80; // not encountered in file downloaded, stated here
	int height = 24; // not encountered in file downloaded, stated here

	struct RANGE
	{
		int minX;
		int minY;
		int maxX;
		int maxY;
	};
	struct RANGE range;
	vector< pair<int, int> > coords;
	string label;
	vector<string> left_ticks;
	vector<string> bottom_ticks;
	map<pair <int, int>, char> map_char;
	map<pair <int, int>, string> map_string;

	Graph();
	Graph(string fileName);
	virtual ~Graph();

	void parse(string fileName);
	void frame();
	void ticks();
	void botlabel();
	void data();
	void draw();
	int xscale(int x);
	int yscale(int y);
	void plot(int x, int y, char c);
	void splot(int x, int y, string s);
};

#endif // GRAPH_H_INCLUDED
