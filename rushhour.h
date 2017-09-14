#ifndef RUSHHOUR_H
#define RUSHHOUR_H

#include <vector>
#include <tuple>
#include <cstdio> /* sscanf */
#include <iostream>
#include <fstream>
#include <regex>    /* regular expression */
#include <queue>
#include <stack>
#include <tuple>
#include <set>

// Keep this
enum Direction   { up, left, down, right, undefined };

// Keep this
enum Orientation { horisontal, vertical};

// Keep this
std::ostream& operator<<( std::ostream& os, Direction const& d );

// Keep this
////////////////////////////////////////////////////////////////////////////////
// global functions
std::vector< std::tuple<unsigned, Direction, unsigned> > 
SolveRushHour( std::string const& filename );

std::vector< std::tuple<unsigned, Direction, unsigned> > 
SolveRushHourOptimally( std::string const& filename );

////////////////////////////////////////////////////////////////////////////////
// your stuff
////////////////////////////////////////////////////////////////////////////////

//Tenative plan:
//Non-optimal solution:  vanilla DFS
//Optimal solution:   depth-bounded DFS and BFS



class ParkingLotSolver {
    private:
    
    public:
        std::vector< std::tuple<unsigned, Direction, unsigned> > Solve();
        std::vector< std::tuple<unsigned, Direction, unsigned> > SolveOptimally();
};

#endif
