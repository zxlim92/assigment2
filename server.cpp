#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "digraph.h"
#include "wdigraph.h"
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
void readGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points) {
	/*Read the Edmonton map data from the provided file
	and load it into the given WDigraph object.
	Store vertex coordinates in Point struct and map
	each vertex to its corresponding Point struct.
	PARAMETERS:
	filename: name of the file describing a road network
	graph: an instance of the weighted directed graph (WDigraph) class
	points: a mapping between vertex identifiers and their coordinates
	*/
  ifstream file(filename);
  string line;
  Point point; 
  if(file.is_open()) {
    while(!file.eof()) {
      getline(file, line);
      if(line.substr(0, 1) == "V") {
        int i = 1;
        while(line.substr(i + 1, 1) != ",") {
          i++;
        }

        string temp = line.substr(2, i - 1);
        int id = stoi(temp);
        int j =1;
        while(line.substr(i + j + 2, 1) != ",") {
          j++;
        }
        temp = line.substr(i + 2, j);

        long long p1 = static_cast <long long> (stold(temp)*100000);
        int x =1;
		while(line.substr(x + j+i + 2, 1) != "") {
          x++;
        }

        string temp2 = line.substr(j+i+3, x);
        long long p2 = static_cast <long long> (stold(temp)*100000);
        
      }
      else if(line.substr(0, 1) == "E") {
        int i = 1;
        while(line.substr(i + 1, 1) != ",") {
          i++;
        }
        string temp = line.substr(2, i - 1);
        int start = stoi(temp);
        int j = 1;
        while(line.substr(i + j + 2, 1) != ",") {
          j++;
        }
        temp = line.substr(i + 2, j);
        int end = stoi(temp);
        long long fire = manhattan(points[start], points[end]);
        graph.addEdge(start, end,fire);
      }
      else {
        break;
      }
    }
    file.close();
  }
}
	

int convertToMapPoint(long long lattitude , long long longnitude, unordered_map<int, Point>& points ){
  Point convertPoint = {lattitude, longnitude};
  long long closePoint;
  int fillClosePoint =1; // populate closePoint and closePointId for first run so tat there can be comparsion w rest of points
  int closePointId;
  cout<<"hellllooo"<<endl;
  for (auto point : points){
    long long distance = manhattan(point.second , convertPoint);
    if(fillClosePoint ==1){
      closePoint = distance;
      closePointId = point.first;
      fillClosePoint = 0;
    }
    else if(closePoint > distance){
      closePoint = distance;
      closePointId = point.first;

    }
      cout<<distance<<endl;
  }
  return closePointId;
}

int main(int argc, char* argv[]){
	WDigraph graph;
	char map[] = "edmonton-roads-2.0.1.txt";
	unordered_map<int,Point> points;
	readGraph(map, graph,points);
	long long startLatit, startLong, endLatit, endLong;
  ifstream inputFile;
  ofstream outputFile;
  inputFile.open(argv[1]);
  outputFile.open("mysoln.txt");
  char x;
  inputFile >> x >> x;
  cout<<x<<endl;
  while(inputFile >> x) {
    if(x == 'R') {
      cout<<"hello"<<endl;
      inputFile >> startLatit >> startLong >> endLatit >> endLong;
      inputFile.ignore(256, '\n');
      int start = convertToMapPoint(startLatit,startLong,points);
      int end = convertToMapPoint(endLatit,endLong,points);
      outputFile << "N ";
      //TODO
    }
    else if(x == 'A') {
      //TODO
    }
  }
  inputFile.close();
  outputFile.close();


}