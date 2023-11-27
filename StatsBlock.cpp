/*****************************************************************//**
 * \file   StatsBlock.cpp
 * \brief  IMPLEMENTATION for the StatsBlock class for a character counter
 * 
 * \author Stephen Graham
 * \date   November 2023
 *********************************************************************/
#include "StatsBlock.h"

void StatsBlock::incrCount(CharType t) {
	stats[static_cast<int>(t)]++;
}

int StatsBlock::getCount(CharType t) {
	return stats[static_cast<int>(t)];
}

void StatsBlock::reset() {
	for (int i=0; i < (static_cast<int>(CharType::size)+1); ++i) { // +1 to match the array safety
		stats[i] = 0;
	}
}

double StatsBlock::getTypePercent(CharType t){
	return (stats[static_cast<int>(CharType::Total)] == 0)
		? 0.0
		: (100.0 * stats[static_cast<int>(t)]) / stats[static_cast<int>(CharType::Total)];
}
