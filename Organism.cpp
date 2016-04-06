// Name: Matt Shaw
// File: Organism.cpp
// Created 03-03-2016
// Implements class Organism
// Additional file: Organism.h

#include "Organism.h"

#include <iostream>

int Organism::count = 0;

Organism::Organism()
{
	++count;
	hasMoved = false;
}

Organism::~Organism()
{
	--count;
}

void Organism::move()
{
	setMoved();
	incrementBreed();
}

void Organism::resetStarve()
{
	std::cout << "ERROR! Organism::resetStarve() called.\n";
}

void Organism::starve()
{
	std::cout << "ERROR! Organism::starve() called.\n";
}

void Organism::breed()
{
	std::cout << "ERROR! Organism::breed() called.\n";
}

bool Organism::isStarving() const
{
	std::cout << "ERROR! Organism::isStarving() called.\n";
	return false;
}

void Organism::incrementBreed()
{
	--timeToBreed;
}

bool Organism::hasAlreadyMoved() const
{
	return hasMoved;
}

bool Organism::isBreedingTime() const
{
	return timeToBreed == 0;
}

void Organism::setMoved()
{
	hasMoved = true;
}

void Organism::resetMoved()
{
	hasMoved = false;
}

int Organism::getCount()
{
	return count;
}
