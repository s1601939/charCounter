/*****************************************************************//**
 * \file   main.cpp
 * \brief  Demonstration of try-throw-catch with a file handling program
 * 
 * \author Stephen Graham
 * \date   November 2023
 * \requires "StatsBlock.h"
 *********************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <exception>
#include <cctype>
#include "StatsBlock.h"

 /* declare a small error class for demonstration purposes */
class FileError : public std::exception {
private:
    std::string message;
public:
     FileError() : message("Unspecified") {};    /// default constructor
     FileError(std::string s) : message(s) {};   /// parameter constructor s is the error message
     virtual const char* what() const throw() {  /// display the message. could override this in a derived class
         return (message.c_str());
     }
}; 

/**
 * openInput() opens a standard text file for input
 * \param   ifs ifstream& the stream to which the open file will be attached
 * \throw   FileError if there is an error opening the file
 * \return  none
 */
void openInput(std::ifstream& ifs);

/**
 * openOutput() opens a standard text file for output
 * \param   ofs ofstream& the stream to which the open file will be attached
 * \throw   FileError if there is an error opening the file
 * \return  none
 */
void openOutput(std::ofstream& ofs);

/**
 * countStats() counts character statistics from the opened stream until eof().
 * \param   ifs ifstream& the stream from which the characters will be read
 * \param   s   StatsBlock& a StatsBlock object for aggregating stats
 * \throw   FileError if an error is encountered while reading the ifs
 * \return none
 */
void countStats(std::ifstream& ifs, StatsBlock& s);

/**
 * writeStats() writes character statistics from the opened stream until eof().
 * \param   ofs ofstream& the stream to which the stats will be written
 * \param   s   StatsBlock& a StatsBlock object containing the stats to be written
 * \throw   FileError if an error is encountered while writing the ofs
 * \return
 */
void writeStats(std::ofstream& ofs, StatsBlock& s);

int main() {
    try {
        StatsBlock statsBlock;
        std::ifstream ifs;
        std::ofstream ofs;

        openInput(ifs);
        countStats(ifs, statsBlock);
        ifs.close();

        openOutput(ofs);
        writeStats(ofs, statsBlock);
        ofs.close();

        std::cout << "Complete." << std::endl;
    }
    catch (FileError e) {
        std::cerr << "File Error Encountered." << e.what() << std::endl;
    }
}

void openInput(std::ifstream& ifs){
    using namespace std;
    string filename;
    cout << "Enter a filename to open for INPUT: ";
    getline(cin,filename);
    ifs.open(filename.c_str());
    if (ifs.fail() || !ifs.is_open()) throw FileError(" (openInput)");
}

void openOutput(std::ofstream& ofs){
    using namespace std;
    string filename;
    cout << "Enter a filename to open for OUTPUT: ";
    getline(cin, filename);
    ofs.open(filename.c_str());
    if (ofs.fail() || !ofs.is_open()) throw FileError(" (openOutput)");
}

void countStats(std::ifstream& ifs, StatsBlock& s){
    char c{};
    while (ifs.get(c) && ifs.good()) {
        s.incrCount(CharType::Total);
        if (isalpha(c)) s.incrCount(CharType::Alpha);
        if (isupper(c)) s.incrCount(CharType::Uppercase);
        if (islower(c)) s.incrCount(CharType::Lowercase);
        if (isdigit(c)) s.incrCount(CharType::Numeric);
        if (ispunct(c)) s.incrCount(CharType::Punctuation);
        if (isspace(c)) s.incrCount(CharType::Whitespace);
        if (iscntrl(c)) s.incrCount(CharType::Control);
    }
    if (!ifs.eof()) throw FileError(" (countStats)");
}

void writeStats(std::ofstream& ofs, StatsBlock& s){
    using namespace std;
    // save the old stream state
    std::ios oldState(nullptr);
    oldState.copyfmt(std::cout);

    ofs << setw(15) << left << "Category" << setw(5) << right << "Count" << setw(8) << right << "Percent" << endl;
    char oldfill = ofs.fill();
    ofs << setfill('-') << setw(15) << left << "" << setw(5) << right << "" << setw(8) << right << "" << setfill(oldfill) << endl;
    ofs << fixed;
    ofs << setw(15) << left << "Alphabetic"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Alpha)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Alpha) << endl;
    ofs << setw(15) << left << "Uppercase"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Uppercase)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Uppercase) << endl;
    ofs << setw(15) << left << "Lowercase"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Lowercase)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Lowercase) << endl;
    ofs << setw(15) << left << "Numeric"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Numeric)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Numeric) << endl;
    ofs << setw(15) << left << "Punctuation"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Punctuation)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Punctuation) << endl;
    ofs << setw(15) << left << "Whitespace"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Whitespace)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Whitespace) << endl;
    ofs << setw(15) << left << "Control"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Control)
        << setw(8) << setprecision(2) << right << s.getTypePercent(CharType::Control) << endl;
    ofs << setw(15) << left << "Total"
        << setw(5) << setprecision(0) << right << s.getCount(CharType::Total);
    if (ofs.fail()) throw FileError(" (writeStats)");
    
    // restore the old stream state
    ofs.copyfmt(oldState);
}
