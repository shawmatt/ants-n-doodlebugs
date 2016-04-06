// Name: Matt Shaw
// File: Grid.cpp
// Created 03-03-2016
// Implements class Grid
// Additional files: Grid.h, Organism.h, Organism.cpp, Ant.h, Ant.cpp, Doodlebug.h, Doodlebug.cpp

#include "Grid.h"
#include <iostream>
#include <ctime>

Grid::Grid(unsigned p_rows, unsigned p_columns)
{
	m_orgPtrMatrix.resize(p_rows);
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
		m_orgPtrMatrix[i].resize(p_columns);
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
			m_orgPtrMatrix[i][j] = nullptr;
	cellCount = 0;
}

Grid::~Grid()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
			if (m_orgPtrMatrix[i][j] != nullptr)
				delete m_orgPtrMatrix[i][j];
}

void Grid::displayMatrix() const
{
	using std::cout;
	using std::endl;

	cout << char(201); // right angle for upper left corner
	for (unsigned i = 0; i < m_orgPtrMatrix[0].size(); ++i)
	{
		cout << char(205); // two horizontal lines // << '-';
	}
	cout << char(187) << endl; // right angle for upper right corner
							   // Grid contents:
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		cout << char(186); // two vertical lines on the left of each row
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] == nullptr)
				cout << ' ';
			else
				cout << *m_orgPtrMatrix[i][j];
		}
		cout << char(186) << endl; // two vertical lines on the right of each row
	}
	cout << char(200); // right angle for lower left corner
	for (unsigned i = 0; i < m_orgPtrMatrix[0].size(); ++i)
	{
		cout << char(205); // two horizontal lines // << '-';
	}
	cout << char(188) << endl; // right angle for lower right corner
}

bool Grid::placeDoodlebugs(unsigned numDoodlebugs)
{
	if (numDoodlebugs > m_orgPtrMatrix.size() * m_orgPtrMatrix[0].size() - cellCount)
		return false; // Not enough free cells
	else
	{
		srand(static_cast<unsigned>(time(nullptr)));
		for (unsigned doodlebugsPlaced = 0; doodlebugsPlaced < numDoodlebugs;)
		{
			int x = rand() % m_orgPtrMatrix.size();
			int y = rand() % m_orgPtrMatrix[0].size();
			if (m_orgPtrMatrix[x][y] == nullptr)
			{
				m_orgPtrMatrix[x][y] = new Doodlebug;
				++doodlebugsPlaced;
				++cellCount;
			}
		}
		return true;
	}
}

bool Grid::placeAnts(unsigned numAnts)
{
	if (numAnts > m_orgPtrMatrix.size() * m_orgPtrMatrix[0].size() - cellCount)
		return false; // Not enough free cells
	else
	{
		srand(static_cast<unsigned>(time(nullptr)));
		for (unsigned antsPlaced = 0; antsPlaced < numAnts;)
		{
			int x = rand() % m_orgPtrMatrix.size();
			int y = rand() % m_orgPtrMatrix[0].size();
			if (m_orgPtrMatrix[x][y] == nullptr)
			{
				m_orgPtrMatrix[x][y] = new Ant;
				++antsPlaced;
				++cellCount;
			}
		}
		return true;
	}
}

void Grid::resetAllMoveFlags()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr)
				m_orgPtrMatrix[i][j]->resetMoved();
		}
}

//loop through the matrix, checking each cell for doodlebugs, then do doodlebug move-stuff
void Grid::moveDoodlebugs()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr && dynamic_cast<Doodlebug *>(m_orgPtrMatrix[i][j]) != nullptr && !m_orgPtrMatrix[i][j]->hasAlreadyMoved())
			{
				//check for ants: [i-1][j], [i+1][j], [i][j-1], [i][j+1]
				struct { int row; int col; } targetLocation[4]; // array to hold target locations
				int targetLocSize = 0;
				if ((i > 0) && (m_orgPtrMatrix[i - 1][j] != nullptr) && (dynamic_cast<Ant *>(m_orgPtrMatrix[i - 1][j]) != nullptr))
				{
					targetLocation[targetLocSize].row = i - 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((i < m_orgPtrMatrix.size() - 1) && (m_orgPtrMatrix[i + 1][j] != nullptr) && (dynamic_cast<Ant *>(m_orgPtrMatrix[i + 1][j]) != nullptr))
				{
					targetLocation[targetLocSize].row = i + 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((j > 0) && (m_orgPtrMatrix[i][j - 1] != nullptr) && (dynamic_cast<Ant *>(m_orgPtrMatrix[i][j - 1]) != nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j - 1;
					++targetLocSize;
				}
				if ((j < m_orgPtrMatrix[0].size() - 1) && (m_orgPtrMatrix[i][j + 1] != nullptr) && (dynamic_cast<Ant *>(m_orgPtrMatrix[i][j + 1]) != nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j + 1;
					++targetLocSize;
				}

				m_orgPtrMatrix[i][j]->move();

				srand(static_cast<unsigned>(time(nullptr)));
				if (targetLocSize != 0) // Ant(s) found, eat one
				{
					m_orgPtrMatrix[i][j]->resetStarve(); // hunger averted
					int targetAntIndex = rand() % targetLocSize; // randomly choose one of the 1-4 found ants
					delete m_orgPtrMatrix[targetLocation[targetAntIndex].row][targetLocation[targetAntIndex].col]; // consume ant
					m_orgPtrMatrix[targetLocation[targetAntIndex].row][targetLocation[targetAntIndex].col] = m_orgPtrMatrix[i][j]; // move into its old location
					m_orgPtrMatrix[i][j] = nullptr;
					--cellCount; // one less cell occupied
				}
				else // regular move
				{
					targetLocSize = 0; // reset this to re-use the temporary target location array
					if ((i > 0) && (m_orgPtrMatrix[i - 1][j] == nullptr))
					{
						targetLocation[targetLocSize].row = i - 1;
						targetLocation[targetLocSize].col = j;
						++targetLocSize;
					}
					if ((i < m_orgPtrMatrix.size() - 1) && (m_orgPtrMatrix[i + 1][j] == nullptr))
					{
						targetLocation[targetLocSize].row = i + 1;
						targetLocation[targetLocSize].col = j;
						++targetLocSize;
					}
					if ((j > 0) && (m_orgPtrMatrix[i][j - 1] == nullptr))
					{
						targetLocation[targetLocSize].row = i;
						targetLocation[targetLocSize].col = j - 1;
						++targetLocSize;
					}
					if ((j < m_orgPtrMatrix[0].size() - 1) && (m_orgPtrMatrix[i][j + 1] == nullptr))
					{
						targetLocation[targetLocSize].row = i;
						targetLocation[targetLocSize].col = j + 1;
						++targetLocSize;
					}
					if (targetLocSize != 0) // Empty cell(s) found
					{
						int targetMoveIndex = rand() % targetLocSize; // randomly choose one of the 1-4 empty locations
						m_orgPtrMatrix[targetLocation[targetMoveIndex].row][targetLocation[targetMoveIndex].col] = m_orgPtrMatrix[i][j];
						m_orgPtrMatrix[i][j] = nullptr;
					}
				}
			}
		}
	}
}

//loop through the matrix, checking each cell for doodlebugs, then do doodlebug breed-stuff
void Grid::breedDoodlebugs()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr && dynamic_cast<Doodlebug *>(m_orgPtrMatrix[i][j]) != nullptr && m_orgPtrMatrix[i][j]->isBreedingTime())
			{
				//check for empty cells: [i-1][j], [i+1][j], [i][j-1], [i][j+1]
				struct { int row; int col; } targetLocation[4]; // array to hold target locations
				int targetLocSize = 0;
				if ((i > 0) && (m_orgPtrMatrix[i - 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i - 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((i < m_orgPtrMatrix.size() - 1) && (m_orgPtrMatrix[i + 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i + 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((j > 0) && (m_orgPtrMatrix[i][j - 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j - 1;
					++targetLocSize;
				}
				if ((j < m_orgPtrMatrix[0].size() - 1) && (m_orgPtrMatrix[i][j + 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j + 1;
					++targetLocSize;
				}

				if (targetLocSize != 0) // Empty cell(s) found
				{
					srand(static_cast<unsigned>(time(nullptr)));
					int targetBreedIndex = rand() % targetLocSize; // randomly choose one of the 1-4 empty locations
					m_orgPtrMatrix[targetLocation[targetBreedIndex].row][targetLocation[targetBreedIndex].col] = new Doodlebug;
					m_orgPtrMatrix[i][j]->breed();
					++cellCount; // one more cell occupied
				}
			}
		}
	}
}

//loop through the matrix, checking each cell for ants, then do ant move-stuff
void Grid::moveAnts()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr && dynamic_cast<Ant *>(m_orgPtrMatrix[i][j]) != nullptr && !m_orgPtrMatrix[i][j]->hasAlreadyMoved())
			{
				m_orgPtrMatrix[i][j]->move();

				//check for openings: [i-1][j], [i+1][j], [i][j-1], [i][j+1]
				struct { int row; int col; } targetLocation[4]; // array to hold target locations
				int targetLocSize = 0;
				if ((i > 0) && (m_orgPtrMatrix[i - 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i - 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((i < m_orgPtrMatrix.size() - 1) && (m_orgPtrMatrix[i + 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i + 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((j > 0) && (m_orgPtrMatrix[i][j - 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j - 1;
					++targetLocSize;
				}
				if ((j < m_orgPtrMatrix[0].size() - 1) && (m_orgPtrMatrix[i][j + 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j + 1;
					++targetLocSize;
				}
				if (targetLocSize != 0) // Empty cell(s) found
				{
					srand(static_cast<unsigned>(time(nullptr)));
					int targetMoveIndex = rand() % targetLocSize; // randomly choose one of the 1-4 empty locations
					m_orgPtrMatrix[targetLocation[targetMoveIndex].row][targetLocation[targetMoveIndex].col] = m_orgPtrMatrix[i][j];
					m_orgPtrMatrix[i][j] = nullptr;
				}
			}
		}
	}
}

//loop through the matrix, checking each cell for ants, then do ant breed-stuff
void Grid::breedAnts()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr && dynamic_cast<Ant *>(m_orgPtrMatrix[i][j]) != nullptr && m_orgPtrMatrix[i][j]->isBreedingTime())
			{
				//check for empty cells: [i-1][j], [i+1][j], [i][j-1], [i][j+1]
				struct { int row; int col; } targetLocation[4]; // array to hold target locations
				int targetLocSize = 0;
				if ((i > 0) && (m_orgPtrMatrix[i - 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i - 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((i < m_orgPtrMatrix.size() - 1) && (m_orgPtrMatrix[i + 1][j] == nullptr))
				{
					targetLocation[targetLocSize].row = i + 1;
					targetLocation[targetLocSize].col = j;
					++targetLocSize;
				}
				if ((j > 0) && (m_orgPtrMatrix[i][j - 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j - 1;
					++targetLocSize;
				}
				if ((j < m_orgPtrMatrix[0].size() - 1) && (m_orgPtrMatrix[i][j + 1] == nullptr))
				{
					targetLocation[targetLocSize].row = i;
					targetLocation[targetLocSize].col = j + 1;
					++targetLocSize;
				}

				if (targetLocSize != 0) // Empty cell(s) found
				{
					srand(static_cast<unsigned>(time(nullptr)));
					int targetBreedIndex = rand() % targetLocSize; // randomly choose one of the 1-4 empty locations
					m_orgPtrMatrix[targetLocation[targetBreedIndex].row][targetLocation[targetBreedIndex].col] = new Ant;
					m_orgPtrMatrix[i][j]->breed();
					++cellCount; // one more cell occupied
				}
			}
		}
	}
}

//loop through the matrix, culling the doodlebugs that have starved
void Grid::starveDoodlebugs()
{
	for (unsigned i = 0; i < m_orgPtrMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < m_orgPtrMatrix[0].size(); ++j)
		{
			if (m_orgPtrMatrix[i][j] != nullptr && dynamic_cast<Doodlebug *>(m_orgPtrMatrix[i][j]) != nullptr && m_orgPtrMatrix[i][j]->isStarving())
			{
				delete m_orgPtrMatrix[i][j];
				m_orgPtrMatrix[i][j] = nullptr;
				--cellCount; // one less cell occupied
			}
		}
	}
}

unsigned Grid::numAnts() const // returns number of ants present
{
	return Ant::getCount();
}

unsigned Grid::numDoodlebugs() const // returns number of ants present
{
	return Doodlebug::getCount();
}

unsigned Grid::getCellCount() const // returns number of occupied cells
{
	return cellCount;
}
