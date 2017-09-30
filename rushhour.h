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
#include <functional>
#include <list>

// Keep this
enum Direction   { up, left, down, right, undefined };

// Keep this
enum Orientation { horisontal, vertical};

// Keep this
std::ostream& operator<<( std::ostream& os, Direction const& d );



////////////////////////////////////////////////////////////////////////////////
// your stuff
////////////////////////////////////////////////////////////////////////////////

//Tenative plan:
//Non-optimal solution:  vanilla DFS
//Optimal solution:   depth-bounded DFS and BFS

class BoardState;

class RushHour {
  


private:
	unsigned height;// = 0;           // size of parking lot  x
	unsigned width;// = 0;            // size of parking lot  x
	unsigned ** parking_lot;// = nullptr;      // parking lot   x
	Direction exit_direction;// = undefined;    // exit direction   x
	unsigned car;// = 0;            // car to be navigated   x
	std::string filename;// = std::string();// filename for data   x

										 //State actions - store these in list thing
	int carSwaps;
	int treeDepth;
	Orientation myOrientation;
	unsigned numCars;
	std::tuple <unsigned, Direction, unsigned> moveToGetHere;
	RushHour* parent = nullptr;
	unsigned myCar;



										 //My stuff
	//filename(""), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0, left, 0), exit_direction(left)


public:
	friend std::ostream& operator<<(std::ostream& os, RushHour const& pl);
	void Print(std::string const& filename_out);
	unsigned const& Car() const { return car; }
	Direction const& Dir() const { return exit_direction; }

	RushHour(std::string const&  filename);
	~RushHour();

	void makeMove(std::tuple< unsigned, Direction, unsigned > move);
	/*
	std::vector< std::tuple<unsigned, Direction, unsigned> > Solve()
	{
		return SolveRushHour(filename);
	}
	std::vector< std::tuple<unsigned, Direction, unsigned> > SolveOptimally()
	{
		return SolveRushHourOptimally(filename);
	}
	*/
	bool IsSolved() const;
	int Check(std::vector< std::tuple<unsigned, Direction, unsigned> > const& sol);
	int CheckBrief(std::vector< std::tuple<unsigned, Direction, unsigned> > const& sol);

	//My stuff
	// bool isSameBoardState( ... )
	Orientation getOrientation(unsigned car)const;  //ASSUMES CAR EXISTS!!!
	unsigned getHeight() const { return height; }
	unsigned getWidth() const { return width; }
	unsigned getGoalCar() const { return car; }
	unsigned** getParkingLot() const { return parking_lot; }
	Direction getExitDirection() const { return exit_direction; }
	unsigned getLotIndex(int x, int y) const { return parking_lot[x][y]; }

	const RushHour& operator=(const RushHour& other);
	bool operator==(const RushHour& other);
	RushHour(RushHour& other);
	//bool IsSolved() const;




	std::vector<RushHour> spawnChildren();
	void spawnChildrenPerCar(unsigned car, std::vector<RushHour>& vec);
	

	friend bool operator<(const RushHour& b1, const RushHour& b2) { return b1.carSwaps < b2.carSwaps; }
	friend bool operator>(const RushHour& b1, const RushHour& b2) { return b1.carSwaps > b2.carSwaps; }
	RushHour() : filename(""), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0, left, 0), exit_direction(left) {}
	
	RushHour(const RushHour& other) : filename(other.filename), myCar(other.myCar), car(other.car), carSwaps(other.carSwaps), myOrientation(other.myOrientation), width(other.width), height(other.width), numCars(other.numCars), moveToGetHere(other.moveToGetHere), exit_direction(other.exit_direction)
	{

		for (unsigned i = 0; i < height; i++)
		{
			parking_lot[i] = new unsigned[width];
			for (unsigned j = 0; j < width; j++)
			{
				parking_lot[i][j] = other.parking_lot[i][j];
			}
		}
	}

	
	std::vector<std::tuple<unsigned, Direction, unsigned>> RHSolveBFS()
	{
		//std::priority_queue<BoardState, std::vector<BoardState>, std::greater<BoardState> > openList;
		std::priority_queue<RushHour, std::vector<RushHour>, std::greater<RushHour>> openList;
		std::list<RushHour> closedList;

		RushHour startingState(filename);
		openList.push(startingState);
		std::vector<RushHour> stateHolder;
		std::vector<std::tuple<unsigned, Direction, unsigned>> output;
		bool isOnClosedList = false;
		RushHour tempState;
		while (!openList.empty())
		{
			//isOnClosedList = false;
			tempState = openList.top();
			openList.pop();


			if (tempState.IsSolved())
			{
				//Loop back through moves until you get to the start, push them into vector one by one
				output.push_back(tempState.moveToGetHere);
				while (tempState.parent)
				{
					tempState = *tempState.parent;
					output.push_back(tempState.moveToGetHere);
				}

				std::reverse(output.begin(), output.end());

				return output;
			}



			//if (!isOnClosedList)
			//{
//			std::swap(&stateHolder, tempState.spawnChildren());
			stateHolder = tempState.spawnChildren();
			for (unsigned x = 0; x < stateHolder.size(); x++)
			{
				isOnClosedList = false;
				for (auto i = closedList.begin(); i != closedList.end(); i++)
				{
					if (stateHolder[x] == (*i))
					{
						isOnClosedList = true;
						if (stateHolder[x].carSwaps < (*i).carSwaps)
						{

							openList.push(stateHolder[x]);
							closedList.remove(*i);

						}
						i = closedList.end();
						//isOnClosedList = true;


					}
				}

				if (!isOnClosedList)
				{
					openList.push(stateHolder[x]);
				}
			}



			//}
			//std::swap(stateHolder, 

		}
		return output;





	}

	

	std::vector < std::tuple<unsigned, Direction, unsigned>> RHSolveDFS()
	{

		std::stack<RushHour> openList;
		std::list<RushHour> closedList;


		RushHour startingState(filename);
		openList.push(startingState);
		RushHour tempState;
		std::vector<RushHour> stateHolder;
		std::vector<std::tuple<unsigned, Direction, unsigned>> output;
		bool isOnClosedList = false;
		unsigned depth = 2;
		while (true)
		{
			while (!openList.empty())
			{
				//isOnClosedList = false;
				tempState = openList.top();
				openList.pop();


				if (tempState.IsSolved())
				{
					//Loop back through moves until you get to the start, push them into vector one by one
					output.push_back(tempState.moveToGetHere);
					while (tempState.parent)
					{
						tempState = *tempState.parent;
						output.push_back(tempState.moveToGetHere);
					}

					std::reverse(output.begin(), output.end());

					return output;
				}



				//if (!isOnClosedList)
				//{
			//	std::swap(stateHolder, tempState.spawnChildren());

				stateHolder = tempState.spawnChildren();

				for (unsigned x = 0; x < stateHolder.size(); x++)
				{
					isOnClosedList = false;
					for (auto i = closedList.begin(); i != closedList.end(); i++)
					{
						if (stateHolder[x] == (*i))
						{
							isOnClosedList = true;
							if (stateHolder[x].carSwaps < (*i).carSwaps)
							{

								openList.push(stateHolder[x]);
								closedList.remove(*i);

							}
							i = closedList.end();
							//isOnClosedList = true;


						}
					}

					if (!isOnClosedList && stateHolder[x].treeDepth < depth)
					{
						openList.push(stateHolder[x]);
					}
				}



				//}
				//std::swap(stateHolder, 

			}
			depth++;
		}
		//	return output;


	}

	
	
	
	// private:
    
  //  public:
      //  std::vector< std::tuple<unsigned, Direction, unsigned> > Solve();
      //  std::vector< std::tuple<unsigned, Direction, unsigned> > SolveOptimally();
	




};









// Keep this
////////////////////////////////////////////////////////////////////////////////
// global functions
std::vector < std::tuple<unsigned, Direction, unsigned> >
	SolveRushHourBFS(std::string const& filename);
std::vector< std::tuple<unsigned, Direction, unsigned> >
SolveRushHourDFS(std::string const& filename);


#endif
