#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "digraph.h"
#include <fstream>
#include <string.h>
#include <iostream>
struct Point
{
	long long lat;
	long long lon;
};
long long manhattan(const Point& pt1, const Point& pt2){
	//return Manhattan distance between the 2 given points;
	long long distance = abs(pt1.lon -pt2.lon) + abs(pt1.lat-pt2.lat);
}
voidreadGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points) {
	/*Read the Edmonton map data from the provided file
	and load it into the given WDigraph object.
	Store vertex coordinates in Point struct and map
	each vertex to its corresponding Point struct.
	PARAMETERS:
	filename: name of the file describing a road network
	graph: an instance of the weighted directed graph (WDigraph) class
	points: a mapping between vertex identifiers and their coordinates
	*/
	ifstream mapOfEdmonton(filename);
    string inputMap;
    string line;
        if(mapOfEdmonton.is_open()){
        	while(getline(mapOfEdmonton, line)){
        		if(line[0] == 'E'){
        			int counter =2;
					string start;
					while(line[counter] != ','){
						start = start + line[counter];
						counter++;
					}       	
					int startNum = stoi(start);	//convert string to int
					counter = counter +1;
					string endNum;
					while(line[counter] != ','){
						endNum = endNum + line[counter];
						counter++;
					} 
					int EndNum = stoi(endNum);
					graph->addEdge(startNum, EndNum);
					graph->addEdge(EndNum, startNum);
        		}else{
        			int counter =2;
					string vertex;
					while(line[counter] != ','){
						vertex = vertex + line[counter];
						counter++;
					}       	 
					int intVertex = stoi(vertex);//convert string to int
					graph -> addVertex(intVertex);
        		}
        	}
        }
        mapOfEdmonton.close();
        return graph;
}
	




}
int main(){
	graph WDigraph;
	char[] filename = "edmonton-roads-2.0.1.txt";
	voidreadGraph(filename, graph, )




}