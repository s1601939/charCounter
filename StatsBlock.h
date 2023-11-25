#pragma once
#pragma once
/** this enum class numbers from zero. The last element is size.
    beware that the CharType::size could be used as a value **/
enum class CharType {Total = 0, Alpha, Lowercase, Uppercase, Numeric, Punctuation, Whitespace, Control, size };

class StatsBlock {
private:
    int stats[static_cast<int>(CharType::size) + 1] = {}; // +1 for safety
public:
    void addType(CharType t);
    int getType(CharType t);
    double getTypePercent(CharType t);
    void reset();
};
