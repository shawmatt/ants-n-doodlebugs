// Name: Matt Shaw
// File: Organism.h
// Created 03-03-2016
// Defines class Organism
// Additional file: Organism.cpp

#ifndef MATT_SHAW_ORGANISM_H
#define MATT_SHAW_ORGANISM_H

#include <iostream>

class Organism
{
public:
	Organism();
	virtual ~Organism();
	virtual void move();
	virtual void resetStarve();
	virtual void starve();
	virtual void breed();
	virtual bool isStarving() const;
	void incrementBreed();
	bool hasAlreadyMoved() const;
	bool isBreedingTime() const;
	void setMoved();
	void resetMoved();

	static int getCount();

	friend std::ostream& operator<<(std::ostream& out, const Organism& printMe) { return printMe.display(out); }

protected:
	int timeToBreed; // How many turns left to breed; breed @0
	bool hasMoved; // Has the organism moved yet this turn?

private:
	static int count; // tracks how many organisms exist

	virtual std::ostream& display(std::ostream& out) const { std::cout << "ERROR"; return out; }
};

#endif
