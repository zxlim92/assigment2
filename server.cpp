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
#include <iostream>
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

  char graphID, comma;
    int ID, start, end;
  double lat, lon;
  string name;
    Point point;

  // input validation
  ifstream textIn(filename);

  while (textIn >> graphID >> comma) {
        if (graphID == 'V') {
            // vertex format: V,ID,Lat,Lon
            textIn >> ID >> comma >> lat >> comma >> lon;
            long long convertedLon = static_cast<long long>(lon * 100000);
            long long convertedLat = static_cast<long long>(lat * 100000);

            point = {convertedLat, convertedLon};
            points[ID] = point;
            graph.addVertex(ID);
        } else if (graphID == 'E') {
            // edge format: E,start,end,name
            textIn >> start >> comma >> end >> comma;
            getline(textIn, name);

            // find points and get manhattan distance
            long long distance = manhattan(points[start], points[end]);
            graph.addEdge(start, end, distance);
        }
    }
    textIn.close();
  // ifstream file(filename);
  // string line;
  // Point point; 
  // if(file.is_open()) {
  //   while(!file.eof()) {
  //     getline(file, line);
  //     if(line.substr(0, 1) == "V") {
  //       int i = 1;
  //       while(line.substr(i + 1, 1) != ",") {
  //         i++;
  //       }

  //       string temp = line.substr(2, i - 1);
  //       int id = stoi(temp);
  //       int j =1;
  //       while(line.substr(i + j + 2, 1) != ",") {
  //         j++;
  //       }
  //       temp = line.substr(i + 2, j);

  //       long long p1 = static_cast <long long> (stold(temp)*100000);
  //       int x =1;
		//     while(line.substr(x + j+i + 2, 1) != "") {
  //         x++;
  //       }

  //       string temp2 = line.substr(j+i+3, x);
  //       long long p2 = static_cast <long long> (stold(temp)*100000);
  //       point = {p1,p2};
  //       points[id] = point;
  //       graph.addVertex(id);
  //     }
  //     else if(line.substr(0, 1) == "E") {
  //       int i = 1;
  //       while(line.substr(i + 1, 1) != ",") {
  //         i++;
  //       }
  //       string temp = line.substr(2, i - 1);
  //       int start = stoi(temp);
  //       int j = 1;
  //       while(line.substr(i + j + 2, 1) != ",") {
  //         j++;
  //       }
  //       temp = line.substr(i + 2, j);
  //       int end = stoi(temp);
  //       long long fire = manhattan(points[start], points[end]);
  //       graph.addEdge(start, end,fire);
  //     }
  //     else {
  //       break;
  //     }
  //   }
  //   file.close();
  // }
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

int main(int argc, char* argv[]){
	WDigraph graph;
	char map[] = "edmonton-roads-2.0.1.txt";
	unordered_map<int,Point> points;
	readGraph(map, graph,points);
	long long startLatit, startLong, endLatit, endLong;
  stack<int> path;
  ifstream inputFile;
  ofstream outputFile;
  inputFile.open(argv[1]);
  outputFile.open("mysol.txt");
  string x;
  while(inputFile >> x) {
    if(x == "R") {
      inputFile >> startLatit >> startLong >> endLatit >> endLong;

      int start = convertToMapPoint(startLatit,startLong,points);
      int end = convertToMapPoint(endLatit,endLong,points);
      unordered_map<int, PIL> searchTree;
      dijkstra(graph,start,searchTree);
      outputFile << "N ";
      //TODO
      if(searchTree.find(end) == searchTree.end()){
        outputFile<<" 0"<<endl; // if there is no path
      }
      else{
      //TODO
        int node = end;
        while(node != start){
          path.push(node);
          node = searchTree[node].second;
        }
        path.push(start);
        int pathSize = path.size();
        outputFile << pathSize<<endl;
        if(path.size()>1){
          for(int i=0;i<pathSize;i++){
            inputFile >>x;     
            if(x=="A"){
             Point output = points[path.top()];
             outputFile << "W "<< output.lat << " " << output.lon << endl;
             cout << "W "<< output.lat << " " << output.lon << endl;
              path.pop();
           }
         }
         inputFile >>x;
         outputFile<<"E"<<endl;
  }
  inputFile.close();
  outputFile.close();


}
}
}
}