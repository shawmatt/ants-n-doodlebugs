// Name: Matt Shaw
// File: Doodlebug.cpp
// Created 03-03-2016
// Implements class Doodlebug
// Additional files: Organism.h, Organism.cpp, Doodlebug.h

#include "Doodlebug.h"

#include <iostream>

unsigned Doodlebug::count = 0;

Doodlebug::Doodlebug()
{
	timeToBreed = 8;
	timeToStarve = 3;
	++count;
}

Doodlebug::~Doodlebug()
{
	--count;
}

void Doodlebug::move()
{
	setMoved();
	incrementBreed();
	starve();
}

void Doodlebug::resetStarve()
{
	timeToStarve = 3;
}

void Doodlebug::breed()
{
	timeToBreed = 8;
}

void Doodlebug::starve()
{
	--timeToStarve;
}

bool Doodlebug::isStarving() const
{
	return timeToStarve == 0;
}

unsigned Doodlebug::getCount()
{
	return count;
}