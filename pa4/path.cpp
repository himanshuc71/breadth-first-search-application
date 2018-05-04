#include "path.h"
#include <queue>
#include <stack>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));

    queue<pair<int,int>> q;
    // first point identified and enqueued
    V[start.second][start.first] = true;
    q.push(start);

    while (!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        vector<pair<int,int>> neighborList = neighbors(p);
        for (unsigned int i = 0; i < neighborList.size() ; i++) {
            if(good(V, p, neighborList[i])){
               V[neighborList[i].second][neighborList[i].first] = true;
               q.push(neighborList[i]);
               P[neighborList[i].second][neighborList[i].first] = p;
            }
        }
    }

	pathPts = assemble(P,start,end);
}

PNG path::render(){

    PNG img(image);
    vector<pair<int,int>> pathToRender = getPath();
    for (int i = 0; i < length() ; i++) {
        pair<int,int> point = pathToRender[i];
        RGBAPixel* pixelPtr = img.getPixel(point.first,point.second);
        pixelPtr->r = 255;
        pixelPtr->g = 0;
        pixelPtr->b = 0;
    }

    return img;

}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

    int x,y;
    RGBAPixel p1,p2;
    x = next.first;
    y = next.second;
    bool withinImage = x >= 0 && x < (int) image.width() && y >= 0 && y < (int) image.height();
    if (withinImage){
        bool unvisited = !v[y][x];
        p1 = *image.getPixel(curr.first,curr.second);
        p2 = *image.getPixel(x,y);
        bool colorBound = closeEnough(p1,p2);
        if(unvisited && colorBound)
            return true;
        else
            return false;
    }
    else
        return false;
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;

    //left
    n.push_back(make_pair(curr.first - 1, curr.second));
    //below
    n.push_back(make_pair(curr.first, curr.second + 1));
    //right
    n.push_back(make_pair(curr.first + 1, curr.second));
    //above
    n.push_back(make_pair(curr.first, curr.second - 1));



    return n;
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {

    /* hint, gold code contains the following line:
	stack<pair<int,int>> S; */

    vector<pair<int,int>> shortestPath;
    // when there is no path
    if (p[e.second][e.first] == e){
        shortestPath.push_back(s);
        return shortestPath;
    }

    stack<pair<int,int>> S;

    // end point pushed
    S.push(e);
    pair<int,int> parent = p[e.second][e.first];
    pair<int,int> temp;

    // backtracking
    while (parent != s){
        S.push(parent);
        parent = p[parent.second][parent.first];
    }
    // start point pushed
    S.push(s);


    // reversing the stack
    while(!S.empty()){
        temp = S.top();
        shortestPath.push_back(temp);
        S.pop();
    }

    return shortestPath;
}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
