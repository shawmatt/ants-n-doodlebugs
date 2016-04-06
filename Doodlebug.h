// Name: Matt Shaw
// File: Doodlebug.h
// Created 03-03-2016
// Defines class Doodlebug
// Additional file: Organism.h, Organism.cpp, Doodlebug.cpp

#ifndef MATT_SHAW_DOODLEBUG_H
#define MATT_SHAW_DOODLEBUG_H

#include "Organism.h"

class Doodlebug : public Organism
{
public:
	Doodlebug();
	~Doodlebug();
	void move();
	void breed();
	void resetStarve();
	bool isStarving() const;

	static unsigned getCount();

private:
	void starve(); // get closer to starving
	int timeToStarve; // How many turns left to starve; starve @0

	static unsigned count; // tracks how many doodlebugs exist

	std::ostream& display(std::ostream& out) const { std::cout << "X"; return out; }
};

#endif
