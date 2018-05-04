
#ifndef _PATH_H
#define _PATH_H

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>
using namespace std;
using namespace cs221util;

class path {

public:

    // initializes variables and calls BFS to initialize path.
	path(const PNG & im,pair<int,int> s,pair<int,int> e);

	//draws path points in red on a copy of the image and returns it
	PNG render();

	//returns path of points
	vector<pair<int,int> > getPath();

	//returns length of shortest path of points
	int length();

private:

    // used to initialize member variable pathPts.
    // called by constructor to create path if it 
    // exists. 
    //
    // requires: neighbors, good, assemble helpers
    //
    // See the interfaces for good and assemble
    // to get a hint on two auxiliary structures
    // you will want to build: predecessor table,
    // and visited table.
   void BFS();

    // tests a neighbor (adjacent vertex) to see if it is 
    // 1. within the image, 2. unvisited, and 3. close in color to curr.
    // An entry in table V is true if a cell has previously been 
    // visited.
	bool good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next);

    // builds a vector containing the locations of the 
    // four vertices adjacent to curr:
    // above, left, right, below (no particular order). 
    // does not pay any attention to whether or not the neighbors are 
    // valid (in the image, previously visited, or the right color).
	vector<pair<int,int>> neighbors(pair<int,int> curr) ;

    // Assumes the predecessor table, built in the BFS as follows: For each 
    // location in the image reachable from the start vertex, "loc", the 
    // table contains the location "pred" from which "loc" was first seen.
    // ("pred", "loc") is thus an edge in the shortest path from s to 
    // "loc".
    //
    // returns the set of points on the shortest path from s to e, if 
    // it exists. Call this vector P.
    //
    // if there is a shortest path: position 0 should contain s, 
    // and for all 0 < i < size, P[0] to P[i] is the set of points
    // on the shortest path from s to point P[i]. P[size-1] == e.

    // if no path from s to e exists, then just return a single element
    // vector P with P[0] == s.
  
	vector<pair<int,int>> assemble(vector<vector<pair<int,int>>> & p,
		pair<int,int> s, pair<int,int> e);


    // tests whether p1 and p2 are near in color. returns 
    // true if the sum of squared difference over color channels
    // is less than or equal to 80. 
    bool closeEnough(RGBAPixel p1, RGBAPixel p2);

// ========= private member variables ================

	// stores the points in the path
	// pathPts[0] == start, pathPts[size-1] == end.
    // if no path exists, then only pathPts[0] == start 
    // see description for assemble for more details.
	vector <pair<int,int>> pathPts;

	pair<int,int> start;
	pair<int,int> end;
	PNG image;

};

#endif
