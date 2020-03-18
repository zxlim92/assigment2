#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include "digraph.h"
#include "wdigraph.h"
#include "dijkstra.h"
#include <fstream>
#include <string.h>
#include <stack>
struct Point
{
	long long lat;
	long long lon;
};
long long manhattan(const Point& pt1, const Point& pt2){
	//return Manhattan distance between the 2 given points;
	long long distance = abs(pt1.lon - pt2.lon) + abs(pt1.lat-pt2.lat);

  return distance;
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
    while(file.good()) {
      // get the line
      getline(file, line);
      // if the first character is V
      if(line.substr(0, 1) == "V") {
        int i = 0;
        // find the location of "," and stop
        while(line.substr(i + 2, 1) != ",") {
          i++;
        }
        // the id
        string temp = line.substr(2, i);
        int id = stoi(temp);
        int j = 0;
        while(line.substr(i + j + 3, 1) != ",") {
          j++;
        }
        // the lat
        temp = line.substr(i + 3, j);
        long long p1 = static_cast <long long> (stold(temp)*100000);
        // the lon
        string temp2 = line.substr(j+i+4, line.size() - 1);
        long long p2 = static_cast <long long> (stold(temp2)*100000);
        // store the point
        point = {p1,p2};
        // store the id
        points[id] = point;
        graph.addVertex(id);
      }
      // if E, connect the id together
      else if(line.substr(0, 1) == "E") {
        int i = 0;
        while(line.substr(i + 2, 1) != ",") {
          i++;
        }
        // first ID
        string temp = line.substr(2, i);
        int start = stoi(temp);
        int j = 0;
        while(line.substr(i + j + 3, 1) != ",") {
          j++;
        }
        // second ID
        temp = line.substr(i + 3, j);
        int end = stoi(temp);
        long long fire = manhattan(points[start], points[end]);
        // add the edge
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
  int counter =0;

  for (auto point : points){
    

    // if(distance < closePoint){
    //   cout<<"bitc ";
    counter ++;
    
  // }
    long long distance = manhattan(point.second , convertPoint);
    if(fillClosePoint ==1){
      closePoint = distance;
      closePointId = point.first;
      fillClosePoint = 0;
    }
    if(closePoint > distance){
      closePoint = distance;
      closePointId = point.first;


    }

  }
  return closePointId;
}

int main(){
	WDigraph graph;
	string map = "edmonton-roads-2.0.1.txt";
	unordered_map<int,Point> points;
	readGraph(map, graph,points);
	long long startLatit, startLong, endLatit, endLong;
  stack<int> path;
  string x;
  while(cin >> x) {
    if(x == "R") {
      cin >> startLatit >> startLong >> endLatit >> endLong;
      int start = convertToMapPoint(startLatit,startLong,points);
      int end = convertToMapPoint(endLatit,endLong,points);
      unordered_map<int, PIL> searchTree;
      dijkstra(graph,start,searchTree);
      cout << "N ";
      if(searchTree.find(end) == searchTree.end()){
        cout <<" 0"<<endl; // if there is no path
      }
      else {
        int node = end;
        while(node != start){
          path.push(node);
          node = searchTree[node].second;
        }
        path.push(start);
        int pathSize = path.size();
        cout << pathSize << endl;
        if(path.size()>1){
          for(int i=0;i<pathSize;i++){
            cin >>x;     
            if(x=="A"){
             Point output = points[path.top()];
             cout << "W "<< output.lat << " " << output.lon << endl;
              path.pop();
           }
         }
         cin >> x;
         cout << "E"<< endl;
  }


}
}
}
}