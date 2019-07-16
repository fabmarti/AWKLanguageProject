#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>


#include "Graph.h"
using namespace std;

Graph::Graph()
{
	//default ctor
}

Graph::Graph(string fileName)
{
	parse(fileName);

}

Graph::~Graph()
{
	//dtor
}

void Graph::frame()
{
	for (int i = ox; i < width; i++) // bottom
	{
		plot(i, oy, '-');
	}
	for (int i = ox; i < width; i++) // top
	{
		plot(i, height - 1, '-');
	}
	for (int i = oy; i < height; i++) // left
	{
		plot(ox, i, '|');
	}
	for (int i = oy; i < height; i++) // right
	{
		plot(width - 1, i, '|');
	}
} // end of frame()

void Graph::ticks()
{
	for (unsigned int i = 0; i <= bottom_ticks.size(); i++)
	{
		plot(xscale(bottom_ticks.at(i)), oy, '|');
		splot(xscale(bottom_ticks.at(i)) - 1, 1, bottom_ticks.at(i));
	}
	for (int i = 0; i <= left_ticks.size(); i++)
	{
		plot(ox, yscale(left_ticks.at(i)), '-');
		splot(0, yscale(left_ticks.at(i)), left_ticks.at(i));
	}
} // end of ticks()

void Graph::botlabel()
{
	splot(int((width + ox - label.size()) / 2), 0, label);
} // end of botlabel()

void Graph::data()
{
	for (int i = 0; i < coords.size(); i++)
	{
		plot(xscale(coords[i].first), yscale(coords[i].second), '*');
	}
} // end of data()

void Graph::draw()
{
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			cout << map_char.at(i, j);
		}
	}
} // end of draw()

int Graph::xscale(unsigned int x)
{
	return int((x - range.minX) / (range.maxX - range.minX) * (width - 1 - ox) + ox + 0.5);
} // end of xscale()

int Graph::yscale(unsigned int y)
{
	return int((y - range.minY) / (range.maxY - range.minY) * (height - 1 - oy) + oy + 0.5);
} // end of yscale()

void Graph::plot(int x, int y, char c)
{
	map_char.emplace(make_pair(coords[x].first, coords[y].second), c);
} // end of plot()

void Graph::splot(int x, int y, string s)
{
	map_string.emplace(make_pair(x, y), s);
} // end of splot()

void Graph::parse(string fileName)
{
	ifstream inFS(fileName.c_str());
	//reading the file and parsing
	//Based on https://stackoverflow.com/questions/2880903/simple-string-parsing-with-c
	//Author: Nikko, May 21 2010
	string temp;
	while (getline(inFS, temp))
	{
		istringstream iss(temp);
		istringstream iss_coord(temp); // orig iss couldn't be used to properly read coordinates due to while(iss >> result) below
		string result;
		while (iss >> result/*getline(iss, result, ' ')*/)
		{
			iss.ignore();
			if (result == "label")
			{
				//cout << "Label: ";
				while (getline(iss, label))
				{
					//cout << label << " ";;
				}
				iss.clear();
				//cout << endl;
			} // end of "label"

			else if (result == "range")
			{
				string range_string;
				int counter = 1;
				while (getline(iss, range_string, ' '))
				{
					int x = atoi(range_string.c_str());

					switch (counter)
					{
					case 1:
						range.minX = x;
					case 2:
						range.minY = x;
					case 3:
						range.maxX = x;
					case 4:
						range.maxY = x;
					}
					counter++;
				}
				cout << "Range(x,y,X,Y): (" << range.minX << ", " << range.minY << ", " << range.maxX << ", " << range.maxY << ")" << endl;
				iss.clear();
			} // end of "range"

			else if (result == "left")
			{
				string lTicks;
				int counter = 0;

				cout << "Left Ticks: ";
				while (getline(iss, lTicks, ' '))
				{
					if (lTicks != "ticks") // so not to add "ticks" into vector
					{
						left_ticks.push_back(lTicks);
						cout << left_ticks.at(counter) << " ";
						counter++;
					}
				}
				cout << endl;
				iss.clear();
			} // end of "left ticks"

			else if (result == "bottom")
			{
				string bTicks;
				int counter = 0;

				//cout << "Bottom Ticks: ";
				while (getline(iss, bTicks, ' '))
				{
					if (bTicks != "ticks") // so not to add "ticks" into vector
					{
						bottom_ticks.push_back(bTicks);
						//cout << bottom_ticks.at(counter) << " ";
						counter++;
					}
				}
				//cout << endl;
				iss.clear();
			} // end of "bottom ticks"

			else
			{
				string coord_tmpString;
				int align = 0;
				int counter = 0;
				int x;
				int y;
				while (iss_coord >> coord_tmpString)
				{
					if (align % 2 == 0 || align == 0)
					{
						x = atoi(coord_tmpString.c_str());
						//coords[counter].first = x;
						//cout << "(" << x << ", ";
						//cout << coord_tmpString << endl;
						align++;
					}
					else if (align % 2 != 0)
					{
						y = atoi(coord_tmpString.c_str());
						coords.push_back(make_pair(x, y));
						//cout << "(" << x << ", " << y << ")" << endl;
						//coords[counter].second = x;
						//cout << y << ")" << endl;
						//cout << coords[counter].second << endl;
						counter++;
						align++;
					}
				}
			} // end of coordinates
		} // end of "result"
	} // end of first while( getline() )
}
