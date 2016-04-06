// Name: Matt Shaw
// File: Ant.h
// Created 03-03-2016
// Defines class Ant
// Additional files: Organism.h, Organism.cpp, Ant.cpp

#ifndef MATT_SHAW_ANT_H
#define MATT_SHAW_ANT_H

#include "Organism.h"

class Ant : public Organism
{
public:
	Ant();
	~Ant();
	void move();
	void breed();

	static unsigned getCount();

private:
	static unsigned count; // tracks how many ants exist

	std::ostream& display(std::ostream& out) const { std::cout << "O"; return out; }
};

#endif

