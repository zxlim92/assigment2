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
/* Function : manhattan
Arguements: pt1 and pt2 (the 2 points to find the manhattan distance between)
*/
long long manhattan(const Point& pt1, const Point& pt2){
	//return Manhattan distance between the 2 given points;
	long long distance = abs(pt1.lon - pt2.lon) + abs(pt1.lat-pt2.lat);

  return distance;
}
/*Read the Edmonton map data from the provided file
  and load it into the given WDigraph object.
  Store vertex coordinates in Point struct and map
  each vertex to its corresponding Point struct.
  PARAMETERS:
  filename: name of the file describing a road network
  graph: an instance of the weighted directed graph (WDigraph) class
  points: a mapping between vertex identifiers and their coordinates
  */
void readGraph(string filename, WDigraph& graph, unordered_map<int, Point>& points) {
	
  ifstream file(filename);
  string line;
  Point point; 
  if(file.is_open()) {
    while(file.good()) {
      getline(file, line);
      if(line.substr(0, 1) == "V") {
        int i = 0;
        while(line.substr(i + 2, 1) != ",") {
          i++;
        }

        string temp = line.substr(2, i);
        int id = stoi(temp);
        int j = 0;
        while(line.substr(i + j + 3, 1) != ",") {
          j++;
        }
        temp = line.substr(i + 3, j);
        long long p1 = static_cast <long long> (stold(temp)*100000);
        string temp2 = line.substr(j+i+4, line.size() - 1);
        long long p2 = static_cast <long long> (stold(temp2)*100000);
        point = {p1,p2};
        points[id] = point;
        graph.addVertex(id);
      }
      else if(line.substr(0, 1) == "E") {
        int i = 0;
        while(line.substr(i + 2, 1) != ",") {
          i++;
        }
        string temp = line.substr(2, i);
        int start = stoi(temp);
        int j = 0;
        while(line.substr(i + j + 3, 1) != ",") {
          j++;
        }
        temp = line.substr(i + 3, j);
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
	
/* Function : convertToMapPoint
Arguements: lattitude, longnitude, points
Description: Find the closest waypoint to the input/ textfile point
*/
int convertToMapPoint(long long lattitude , long long longnitude, unordered_map<int, Point>& points ){
  Point convertPoint = {lattitude, longnitude};
  long long closePoint;
  int fillClosePoint =1; // populate closePoint and closePointId for first run so tat there can be comparsion w rest of points
  int closePointId;
  int counter =0;

  for (auto point : points){ // iterate through points to find the point closest way point
    
    counter ++;
    
    long long distance = manhattan(point.second , convertPoint); // calculate manhattan distance from the waypoint to the input point
    if(fillClosePoint ==1){ // check if first run cause need to fill the closePoint and closePointId
      closePoint = distance;
      closePointId = point.first;
      fillClosePoint = 0;
    }
    if(closePoint > distance){ // find the minium manhattan distance and store the id
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
      int start = convertToMapPoint(startLatit,startLong,points); // find closest way point to start 
      int end = convertToMapPoint(endLatit,endLong,points); // same as above line but for end
      unordered_map<int, PIL> searchTree; // build a search tree
      dijkstra(graph,start,searchTree); // make dijsktra graph of the possible path from the start
      cout << "N ";
      if(searchTree.find(end) == searchTree.end()){ // check for no path
        cout <<" 0"<<endl; // if there is no path
      }
      else {
        int node = end; // traverse from the back of the search tree 
        while(node != start){ // loop  till get to starting node and add the nodes on the way to the stack
          path.push(node);  
          node = searchTree[node].second;  
        }
        path.push(start); // make sure to add the start node
        int pathSize = path.size(); // store path size
        cout << pathSize << endl;
        if(path.size()>1){  
          for(int i=0;i<pathSize;i++){ // everytime user press A prints the next node and pops it out from stack
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