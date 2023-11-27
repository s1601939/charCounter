/*****************************************************************//**
 * \file   StatsBlock.h
 * \brief  INTERFACE file for the StatsBlock used in the character counter
 * 
 * \author Stephen Graham
 * \date   November 2023
 *********************************************************************/
#pragma once
/** this enum class numbers from zero. The last element is size.
    beware that the CharType::size could be used as a value **/
enum class CharType {Total = 0, Alpha, Lowercase, Uppercase, Numeric, Punctuation, Whitespace, Control, size };

class StatsBlock {
private:
    /** an array of stats--one integer space for each type in the CharType enum */
    int stats[static_cast<int>(CharType::size) + 1] = {}; // +1 for safety
public:
    /**
     * incrCount() increments the array element for the specified CharType.
     * 
     * \param t The CharType designator for the element to be incremented
     * \post    The array element for the specified CharType is incremented
     */
    void incrCount(CharType t);

    /**
     * getCount() returns the array element for the specified CharType.
     * 
     * \param t The CharType designator for the element to be retrieved
     * \return the count for the requested CharType
     */
    int getCount(CharType t);

    /**
     * getTypePercent() returns the percentage of the total count represented by t.
     * 
     * \param t The CharType designator for the element to be retrieved
     * \return The percent of the total characters represented (or 0 if there are no characters)
     */
    double getTypePercent(CharType t);

    /**
     * reset() sets all the values in the stats array to 0.
     * 
     */
    void reset();
};
