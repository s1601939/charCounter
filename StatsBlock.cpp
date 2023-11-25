#include "StatsBlock.h"
void StatsBlock::addType(CharType t) {
	stats[static_cast<int>(t)]++;
}
int StatsBlock::getType(CharType t) {
	return stats[static_cast<int>(t)];
}
void StatsBlock::reset() {
	for (int i=0; i < static_cast<int>(CharType::size); ++i) {
		stats[i] = 0;
	}
}

double StatsBlock::getTypePercent(CharType t){
	return (stats[static_cast<int>(CharType::Total)] == 0)
		? 0.0
		: (100.0 * stats[static_cast<int>(t)]) / stats[static_cast<int>(CharType::Total)];
}
