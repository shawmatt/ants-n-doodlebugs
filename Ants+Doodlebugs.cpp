// Name: Matt Shaw
// File: Ants+Doodlebugs.cpp
// Created 03-03-2016
// Uses the Grid class and methods, which uses the Organism classes and methods, to simulate an interaction of bugs.
// Additional files: Grid.h, Grid.cpp, Organism.h, Organism.cpp, Ant.h, Ant.cpp, Doodlebug.h, Doodlebug.cpp

#include "Grid.h"

#include <iostream>
#include <Windows.h>

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	
	int initDoodlebugs = 5; // initial number of doodlebugs
	int initAnts = 100; // initial number of ants
	int delay = 0; // delay between frames in continuous mode, in ms

	Grid bugGrid; // An empty matrix of organisms

	// Seed the matrix:
	bugGrid.placeDoodlebugs(initDoodlebugs);
	bugGrid.placeAnts(initAnts);

	cout << "The simulation will end when the number of doodlebugs reaches zero.\n";
	cout << "Do you want to run in continuous mode [Y/N] ? ";
	char response;
	cin.get(response).get();
	if (response == 'Y') response = 'y';
	if (response == 'y')
		cout << "Enter the number of milliseconds to delay between frames: ", cin >> delay;

	int turnNumber = 0; // Begin timekeeping

	cout << "TIME: " << turnNumber << endl;
	bugGrid.displayMatrix(); // The grid, at time 0, just before the action happens
	cout << "Ants: " << bugGrid.numAnts() << "\nDoodlebugs: " << bugGrid.numDoodlebugs() << endl;

	do {
		bugGrid.moveDoodlebugs();
		bugGrid.breedDoodlebugs();
		bugGrid.moveAnts();
		bugGrid.breedAnts();
		bugGrid.starveDoodlebugs();
		bugGrid.resetAllMoveFlags();
		++turnNumber;
		if (response != 'y') cout << "Press <ENTER> for next turn.", cin.get();
		else Sleep(delay); // pause for (delay) milliseconds
		system("cls"); // Windows-only screen clearing
		cout << "TIME: " << turnNumber << endl;
		bugGrid.displayMatrix();
		cout << "Ants: " << bugGrid.numAnts() << "\nDoodlebugs: " << bugGrid.numDoodlebugs() << endl;
	} while (bugGrid.numDoodlebugs() != 0);

	cout << "The simulation has ended.\n";
	cout << "The doodlebug society became extinct at time " << turnNumber << ".\n";
	if (bugGrid.numAnts() == 0)
		cout << "But at least they took the ants down with them.\n";
	else
		cout << "The ants will rule the world!\n";

	return 0;
}
