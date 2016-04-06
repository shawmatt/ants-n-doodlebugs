// Name: Matt Shaw
// File: Ant.cpp
// Created 03-03-2016
// Implements class Ant
// Additional files: Organism.h, Organism.cpp, Ant.h

#include "Ant.h"

#include <iostream>

unsigned Ant::count = 0;

Ant::Ant()
{
	Organism();
	timeToBreed = 3;
	++count;
}

Ant::~Ant()
{
	--count;
}

void Ant::move()
{
	setMoved();
	incrementBreed();
}

void Ant::breed()
{
	timeToBreed = 3;
}

unsigned Ant::getCount()
{
	return count;
}
