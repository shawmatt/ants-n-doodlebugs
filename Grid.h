// Name: Matt Shaw
// File: Grid.h
// Created 03-03-2016
// Defines class Grid
// Additional files: Grid.cpp, Organism.h, Organism.cpp, Ant.h, Ant.cpp, Doodlebug.h, Doodlebug.cpp

#ifndef MATT_SHAW_GRID_H
#define MATT_SHAW_GRID_H

#include "Ant.h"
#include "Doodlebug.h"
#include "Organism.h"
#include <vector>

class Grid
{
public:
	Grid(unsigned p_rows = 20, unsigned p_columns = 20); // default size 20 X 20
	~Grid();
	bool placeDoodlebugs(unsigned);	 // Randomly places the specified number of doodlebugs on the grid
								// Returns false if there is not enough space
	bool placeAnts(unsigned); // Randomly places the specified number of ants on the grid
						// Returns false if there is not enough space
	void displayMatrix() const;
	void resetAllMoveFlags();
	void moveDoodlebugs();
	void breedDoodlebugs();
	void moveAnts();
	void breedAnts();
	void starveDoodlebugs(); // Culls the doodlebugs that have starved
	unsigned numAnts() const; // returns number of ants present
	unsigned numDoodlebugs() const; // returns number of doodlebugs present
	unsigned getCellCount() const; // returns number of occupied cells

private:
	std::vector< std::vector<Organism*> > m_orgPtrMatrix;   // Declare a rowsXcolumns matrix of pointers-to-Organism
															// The size is expected to remain for the duration of the object
	unsigned cellCount; // tracks number of occupied cells; easier than using a loop of .size() calls and some math every time

};

#endif
