//#include <iostream>
#include "rushhour.h"
// Keep this
////////////////////////////////////////////////////////////////////////////////
// global functions
std::vector< std::tuple<unsigned, Direction, unsigned> >
SolveRushHourOptimally(std::string const& filename) { RushHour solver(filename);  return solver.RHSolveBFS(); }

std::vector< std::tuple<unsigned, Direction, unsigned> >
SolveRushHour(std::string const& filename) { RushHour solver(filename);  return solver.RHSolveDFS(); }

// Keep this
std::ostream& operator<<( std::ostream& os, Direction const& d ) {
    switch ( d ) {
        case up:    os << "up "; break;
        case left:  os << "left "; break;
        case down:  os << "down "; break;
        case right: os << "right "; break;
        default:    os << "undefined"; break;
    }
    return os;
}

//class RushHour;
/*
class BoardState
{
public:

	BoardState* parent;
	unsigned** myState;
	unsigned myCar;
	int carSwaps;
	int treeDepth;
	Orientation myOrientation;
	unsigned boardWidth;
	unsigned boardHeight;
	unsigned numCars;
	Direction exitDirection;
	std::tuple<unsigned, Direction, unsigned> moveToGetHere;
	unsigned goalCar;


	friend bool operator<(const BoardState& b1, const BoardState& b2) { return b1.carSwaps < b2.carSwaps; }
	friend bool operator>(const BoardState& b1, const BoardState& b2) { return b1.carSwaps > b2.carSwaps; }







	const BoardState& operator=(BoardState& other)
	{
		if (&other != this)
		{
			parent = other.parent;
			myCar = other.myCar;
			carSwaps = other.carSwaps;
			treeDepth = other.treeDepth;
			myOrientation = other.myOrientation;
			boardWidth = other.boardWidth;
			boardHeight = other.boardHeight;
			numCars = other.numCars;
			exitDirection = other.exitDirection;
			goalCar = other.goalCar;


			std::get<0>(moveToGetHere) = std::get<0>(other.moveToGetHere);
			std::get<1>(moveToGetHere) = std::get<1>(other.moveToGetHere);
			std::get<2>(moveToGetHere) = std::get<2>(other.moveToGetHere);


			for (int i = 0; i < boardHeight; i++)
			{
				//myState[i] = new unsigned[boardWidth];
				for (int j = 0; j < boardWidth; j++)
				{
					myState[i][j] = other.myState[i][j];
				}
			}

		}
	}




	bool BoardState::isSolved() const
	{


		unsigned i_car_pos = boardHeight;
		unsigned j_car_pos = boardWidth;
		Orientation orientation = horisontal;
		bool done = false;
		for (unsigned i = 0; i<boardHeight && !done; ++i) {
			for (unsigned j = 0; j<boardWidth && !done; ++j) {
				if (myState[i][j] == goalCar) {
					if (i_car_pos == boardHeight) { // first time seeing car
						i_car_pos = i;
						j_car_pos = j;
					}
					else { //second time - ready to make decision 
						if (j_car_pos == j) { // default is horisontal
							orientation = vertical;
						}
						done = true;
					}
				}
			}
		}

		bool solved = false;
		switch (exitDirection) {
		case up:    solved = orientation == vertical   && myState[0][j_car_pos] == goalCar; break;
		case left:  solved = orientation == horisontal && myState[i_car_pos][0] == goalCar; break;
		case down:  solved = orientation == vertical   && myState[boardHeight - 1][j_car_pos] == goalCar; break;
		case right: solved = orientation == horisontal && myState[i_car_pos][boardWidth - 1] == goalCar; break;
		default: break;
		}
		return solved;

	}



	BoardState() : parent(NULL), myState(NULL), myCar(0), goalCar(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), boardWidth(0), boardHeight(0), numCars(0), moveToGetHere(0, left, 0), exitDirection(left) {}
	BoardState(const std::string& filename) : parent(NULL), myState(NULL), myCar(0), goalCar(myCar), carSwaps(0), treeDepth(0), myOrientation(horisontal), boardWidth(0), boardHeight(0), moveToGetHere(0, left, 0), exitDirection(left) {}
	

	//Car swap does NOT update here, but tree depth DOES
	




	//BoardState(std::string const& filename) : BoardState(new RushHour(filename)) {}   //Double check this -- might need a copy constructor / assignment operator to make this work right??


																				  //Delete array but do NOT delete parent??   Do not delete children??
	~BoardState() {
		if (myState)
		{
			for (int i = 0; i < boardHeight; i++)
			{
				delete myState[i];
			}
			delete myState;
		}
	}



	
	Orientation BoardState::getOrientation(unsigned car) const

	{
		for (int i = 0; i<boardHeight; i++)
		{
			for (int j = 0; j < boardWidth; j++)
			{
				if (myState[i][j] == car)
				{
					//If the next ROW is also this car, it has vertical orientation
					//If the next COLUMN also has this car, it has horizontal orientation
					if (myState[i + 1][j] == car)
					{
						return vertical;
					}
					else
					{
						return horisontal;
					}
				}
			}
		}
	}
	


	//Use the given 'make a move' logic to determine what moves to try

	

	move = car,    direction, num positions
	void RushHour::makeMove(std::tuple< unsigned, Direction, unsigned > move)
	{



	int d = std::get<1>(move); // convert direction to int
	int di = (d - 1)*((3 - d) % 2);    // see comment before function
	int dj = (d - 2)*(d % 2);        // see comment before function
	int scan_direction = di + dj; // -1 (up,left) or 1 (down,right)

	unsigned num_positions = std::get<2>(move);
	unsigned car = std::get<0>(move);

	unsigned i_start = (scan_direction == 1) ? height - 1 : 0;
	unsigned j_start = (scan_direction == 1) ? width - 1 : 0;
	for (unsigned step = 0; step<num_positions; ++step) { // move car 1 position at a time
	for (unsigned i = i_start; i<height; i -= scan_direction) {
	for (unsigned j = j_start; j<width; j -= scan_direction) {
	if (parking_lot[i][j] == car) {
	parking_lot[i][j] = 0;
	// check if legal
	if (i + di >= height && j + dj >= width) {
	throw("Car moved outside of parking lot");
	return;
	}
	if (parking_lot[i + di][j + dj] > 0) {
	throw("Car moved on top of another car");
	return;
	}
	parking_lot[i + di][j + dj] = car;
	}
	}
	}
	}
	}


	

	


	



	//private:

	//How the fuck do I delete this monstrosity without leaks aaaaaa
};




BoardState::BoardState(const std::string& filename)
{
	//unsigned w = r.getWidth();
	//unsigned h = r.getHeight();

	RushHour r(filename);

	myState = new unsigned*[boardHeight];

	for (int i = 0; i < boardHeight; i++)
	{
		myState[i] = new unsigned[boardWidth];
		for (int j = 0; j < boardWidth; j++)
		{
			myState[i][j] = r.getLotIndex(i, j);
			numCars = std::max(numCars, myState[i][j]);
		}
	}
	
}

*/

//My stuff
//filename(""), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0, left, 0), exit_direction(left)


	const RushHour& RushHour::operator=(const RushHour& other)
	{
		//filename(""), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0, left, 0), exit_direction(left)

		if (&other != this)
		{
			parent = other.parent;
			myCar = other.myCar;
			carSwaps = other.carSwaps;
			treeDepth = other.treeDepth;
			myOrientation = other.myOrientation;
			width = other.width;
			height = other.height;
			numCars = other.numCars;
			exit_direction = other.exit_direction;
			car = other.car;


			std::get<0>(moveToGetHere) = std::get<0>(other.moveToGetHere);
			std::get<1>(moveToGetHere) = std::get<1>(other.moveToGetHere);
			std::get<2>(moveToGetHere) = std::get<2>(other.moveToGetHere);


			for (unsigned i = 0; i < height; i++)
			{
				//myState[i] = new unsigned[boardWidth];
				for (unsigned j = 0; j < width; j++)
				{
					parking_lot[i][j] = other.parking_lot[i][j];
				}
			}

		}

		return *this;
	}


void RushHour::spawnChildrenPerCar(unsigned car, std::vector<RushHour>& vec)   //Will have to loop through & call this for each car
{
	Direction directions[2] = { left, right };
	unsigned spacesToCheck = width;
	bool isVertical = (this->getOrientation(car) == vertical);
	if (isVertical)
	{
		directions[0] = up;
		directions[1] = down;
		spacesToCheck = height;
	}

	for (int x = 0; x < 2; x++)   //For each direction
	{

		for (unsigned y = 1; y <= spacesToCheck; y++)
		{
			std::tuple<unsigned, Direction, unsigned> move(car, directions[x], y);
			//void RushHour::makeMove(std::tuple< unsigned, Direction, unsigned > move)




			int d = std::get<1>(move); // convert direction to int
			int di = (d - 1)*((3 - d) % 2);    // see comment before function
			int dj = (d - 2)*(d % 2);        // see comment before function
			int scan_direction = di + dj; // -1 (up,left) or 1 (down,right)

			unsigned num_positions = std::get<2>(move);
			unsigned carToMove = std::get<0>(move);

			unsigned i_start = (scan_direction == 1) ? height - 1 : 0;
			unsigned j_start = (scan_direction == 1) ? width - 1 : 0;
			for (unsigned step = 0; step < num_positions; ++step) { // move car 1 position at a time
				for (unsigned i = i_start; i < height; i -= scan_direction) {
					for (unsigned j = j_start; j < width; j -= scan_direction) {
						if (parking_lot[i][j] == carToMove) {

							//Instead of editing MY state, check that the move will be valid, then make a new board state

							//		myState[i][j] = 0;
							// check if legal
							if ((i + di >= height && j + dj >= width) || (parking_lot[i + di][j + dj] > 0))  //If invalid move, do nothing
							{//	throw("Car moved outside of parking lot");
							 //	return;


							 //	throw("Car moved on top of another car");
							 //	return;




							}
							else {
								//boardState[i + di][j + dj] = car;

								//Make child board state, make move on child
								RushHour child(*this);

								if (carToMove != this->myCar)
								{
									child.myCar = carToMove;
									child.carSwaps++;

								}

								child.parking_lot[i][j] = 0;
								child.parking_lot[i + di][j + dj] = carToMove;
								child.moveToGetHere = move;

								//IF THIS STATE IS ALREADY ON CLOSED LIST, DELETE THIS CHILD AND IGNORE IT
								//OTHERWISE, PUSH ONTO CLOSED LIST
								//But do that ouside of this function for the sake of my sanity


								vec.push_back(child);
								//


							}
						}
					}
				}
			}
		}











	}



}



std::vector<RushHour> RushHour::spawnChildren()
{
	std::vector<RushHour> out;
	for (unsigned i = 1; i <= numCars; i++)
	{
		spawnChildrenPerCar(i, out);
	}
	return out;
}
//My stuff
//filename(""), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0, left, 0), exit_direction(left)



RushHour::RushHour(RushHour& other) : filename(other.filename), parent(&other), myCar(other.myCar), car(other.car), carSwaps(other.carSwaps), treeDepth(other.treeDepth +1), myOrientation(other.myOrientation), width(other.width), height(other.height), numCars(other.numCars), moveToGetHere(other.moveToGetHere), exit_direction(other.exit_direction)
{
	/*
		filename = other.filename;
		parent = &other;
		myCar = other.myCar;
		carSwaps = other.carSwaps;
		treeDepth = other.treeDepth + 1;

		myOrientation = other.myOrientation;
		
		width = other.width;
		height = other.height;
		numCars = other.numCars;
		moveToGetHere = std::tuple<unsigned, Direction, unsigned>(std::get<0>(other.moveToGetHere), std::get<1>(other.moveToGetHere), std::get<2>(other.moveToGetHere));
		*/

		parking_lot = new unsigned*[height];

		for (unsigned i = 0; i < height; i++)
		{
			parking_lot[i] = new unsigned[width];
			for (unsigned j = 0; j < width; j++)
			{
				parking_lot[i][j] = other.parking_lot[i][j];
			}
		}

	
}




Orientation RushHour::getOrientation(unsigned car) const
{
	for(unsigned i=0;i<height;i++)
	{
		for (unsigned j = 0; j < width; j++)
		{
			if (parking_lot[i][j] == car)
			{
			//If the next ROW is also this car, it has vertical orientation
			//If the next COLUMN also has this car, it has horizontal orientation
				if (parking_lot[i + 1][j] == car)
				{
					return vertical;
				}
				else
				{
					return horisontal;
				}
			}
		}
	}

	return vertical;
}


/**/
// RushHour implementation
//filename, parent, parking_lot, myCar, car, carSwaps, treeDepth, myOrientation, width, height, numCars, moveToGetHere,exit_direction

RushHour::RushHour(std::string const&  filename) : filename(filename), parent(NULL), parking_lot(NULL), myCar(0), car(0), carSwaps(0), treeDepth(0), myOrientation(horisontal), width(0), height(0), numCars(0), moveToGetHere(0,left,0),exit_direction(left)
{
	std::ifstream infile(filename);
	std::string   data; // all data from input file

	if (!infile.is_open()) {
		std::cerr << "Errors in input file: cannot open \"" << filename << "\"" << std::endl;
		throw "Errors in input file: cannot open";
	}

	// read the whole file into a string
	while (!infile.eof()) {
		std::string line;
		std::getline(infile, line);
		data.append(line);
		data.append(" ");
	}

	infile.close();

	// parse data
	std::smatch match;

	if (std::regex_match(data, match, std::regex(".*width\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		// The first sub_match is the whole string; the next
		// sub_match is the first parenthesized expression.
		width = std::stoi(match[1]);
		data = std::regex_replace(data, std::regex("width\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"width\"" << std::endl;
		throw "Errors in input file: cannot find \"width\"";
	}
	if (std::regex_match(data, match, std::regex(".*height\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		height = std::stoi(match[1]);
		data = std::regex_replace(data, std::regex("height\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"height\"" << std::endl;
		throw "Errors in input file: cannot find \"height\"";
	}
	if (std::regex_match(data, match, std::regex(".*car\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		car = std::stoi(match[1]);
		myCar = car;
		data = std::regex_replace(data, std::regex("car\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"car\"" << std::endl;
		throw "Errors in input file: cannot find \"car\"";
	}
	if (std::regex_match(data, match, std::regex(".*exit\\s+([a-z]+).*", std::regex_constants::icase)) && match.size() == 2) {
		std::string dir_str = match[1].str();
		if (dir_str == "left") { exit_direction = left; }
		else if (dir_str == "right") { exit_direction = right; }
		else if (dir_str == "up") { exit_direction = up; }
		else if (dir_str == "down") { exit_direction = down; }
		else { throw "unknown exit direction "; }
		data = std::regex_replace(data, std::regex("exit\\s+[a-z]+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"exit\"" << std::endl;
		throw "Errors in input file: cannot find \"exit\"";
	}

	// only cells are left in the data
	std::regex re_cell("(\\d+)"); // each cell is a number or dot
	std::sregex_iterator cell_matches_begin = std::sregex_iterator(data.begin(), data.end(), re_cell);
	std::sregex_iterator cell_matches_end = std::sregex_iterator();
	
	
	
	unsigned maxCarNum = 0;
	// should have exactly height*width numbers and dots
	if (std::distance(cell_matches_begin, cell_matches_end) == height*width) {
		
		unsigned * parking_lot_data = new unsigned[height*width];
		parking_lot = new unsigned*[height];
		for (unsigned i = 0; i<height; ++i) {
			parking_lot[i] = parking_lot_data + i*width;
		}
		unsigned pos = 0;
		for (std::sregex_iterator iter = cell_matches_begin; iter != cell_matches_end; ++iter) {
			parking_lot_data[pos++] = std::stoi((*iter).str());
	
			if (parking_lot_data[pos] > maxCarNum)
			{
				maxCarNum = parking_lot_data[pos];
			}

		}
	}
	else {
		std::cerr << "Errors in input file: number of cells should be " << height << "*" << width << ". Found " << std::distance(cell_matches_begin, cell_matches_end) << std::endl;
		throw "Errors in input file: number of cells";
	}

	numCars = maxCarNum;


}

// Direction is an enum (see header):
// +------------>j
// |    ^ 0
// |    |
// |1<--+-->3     
// |    |
// |    V 2
// V        update (i,j) given 1 step in direction d
// i        i += (d-1)*((3-d)%2)    j += (d-2)*(d%2)
// 0 = -1,0
// 1 = 0,-1
// 2 = 1,0
// 3 = 0,1
//

//                                move = car,    direction, num positions
void RushHour::makeMove(std::tuple< unsigned, Direction, unsigned > move)
{



	int d = std::get<1>(move); // convert direction to int
	int di = (d - 1)*((3 - d) % 2);    // see comment before function
	int dj = (d - 2)*(d % 2);        // see comment before function
	int scan_direction = di + dj; // -1 (up,left) or 1 (down,right)

	unsigned num_positions = std::get<2>(move);
	unsigned car = std::get<0>(move);

	unsigned i_start = (scan_direction == 1) ? height - 1 : 0;
	unsigned j_start = (scan_direction == 1) ? width - 1 : 0;
	for (unsigned step = 0; step<num_positions; ++step) { // move car 1 position at a time
		for (unsigned i = i_start; i<height; i -= scan_direction) {
			for (unsigned j = j_start; j<width; j -= scan_direction) {
				if (parking_lot[i][j] == car) {
					parking_lot[i][j] = 0;
					// check if legal
					if (i + di >= height && j + dj >= width) {
						throw("Car moved outside of parking lot");
						return;
					}
					if (parking_lot[i + di][j + dj] > 0) {
						throw("Car moved on top of another car");
						return;
					}
					parking_lot[i + di][j + dj] = car;
				}
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, RushHour const& pl) {
	//    os << pl.height << std::endl;
	//    os << pl.width << std::endl;
	for (unsigned i = 0; i<pl.height; ++i) {
		for (unsigned j = 0; j<pl.width; ++j) {
			os << pl.parking_lot[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}


bool RushHour::operator==(const RushHour& other)
{
	for (unsigned i = 0; i < height; i++)
	{
		//myState[i] = new unsigned[boardWidth];
		for (unsigned j = 0; j < width; j++)
		{

			if (parking_lot[i][j] != other.parking_lot[i][j])
			{
				return false;
			}
		}
	}
	return true;
}






bool RushHour::IsSolved() const
{
	unsigned i_car_pos = height;
	unsigned j_car_pos = width;
	Orientation orientation = horisontal;
	bool done = false;
	for (unsigned i = 0; i<height && !done; ++i) {
		for (unsigned j = 0; j<width && !done; ++j) {
			if (parking_lot[i][j] == car) {
				if (i_car_pos == height) { // first time seeing car
					i_car_pos = i;
					j_car_pos = j;
				}
				else { //second time - ready to make decision 
					if (j_car_pos == j) { // default is horisontal
						orientation = vertical;
					}
					done = true;
				}
			}
		}
	}

	bool solved = false;
	switch (exit_direction) {
	case up:    solved = orientation == vertical   && parking_lot[0][j_car_pos] == car; break;
	case left:  solved = orientation == horisontal && parking_lot[i_car_pos][0] == car; break;
	case down:  solved = orientation == vertical   && parking_lot[height - 1][j_car_pos] == car; break;
	case right: solved = orientation == horisontal && parking_lot[i_car_pos][width - 1] == car; break;
	default: break;
	}
	return solved;
}

int RushHour::Check(std::vector< std::tuple<unsigned, Direction, unsigned> > const& sol)
{
	try {
		// Print( "solution.txt" );
		for (std::tuple<unsigned, Direction, unsigned> const& m : sol) {
			std::cout << "Car " << std::get<0>(m) << " to be moved " << std::get<1>(m) << " " << std::get<2>(m) << " positions\n";
			makeMove(m);
			// Print( "solution.txt" );
			std::cout << *this;
		}
		bool final_pos = IsSolved();
		std::cout << "Number of steps = " << sol.size() << std::endl;
		std::cout << "Solved = " << final_pos << std::endl;
		return final_pos;
	}
	catch (char const * msg) {
		std::cout << "ERROR - " << msg << std::endl;
		return 1;
	}
}

int RushHour::CheckBrief(std::vector< std::tuple<unsigned, Direction, unsigned> > const& sol)
{
	std::cout << "Number of steps = " << sol.size() << std::endl;
	try {
		for (std::tuple<unsigned, Direction, unsigned> const& m : sol) {
			makeMove(m);
		}
		bool final_pos = IsSolved();
		std::cout << "Solved = " << final_pos << std::endl;
		return final_pos;
	}
	catch (char const * msg) {
		std::cout << "ERROR - " << msg << std::endl;
		return 1;
	}
}
RushHour::~RushHour()
{
	if (parking_lot)
	{
		for(unsigned i=0;i<height;++i)
		{
			for (unsigned j = 0; j < width;++j)
			{
				if (parking_lot[i])
				{
					delete[] parking_lot[i];
				}
			}
		}
		//delete[] parking_lot[0];
		delete[] parking_lot;
	}
}

void RushHour::Print(std::string const& filename_out)
{
	std::ofstream os;
	os.open(filename_out, std::ofstream::out | std::ofstream::app);
	for (unsigned i = 0; i<height; ++i) {
		for (unsigned j = 0; j<width; ++j) {
			os << parking_lot[i][j] << " ";
		}
	}
	os << std::endl;
}


