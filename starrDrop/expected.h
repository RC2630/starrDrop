#ifndef EXPECTED_DOT_H
#define EXPECTED_DOT_H

#include "common.h"
#include "general/stringUtility.h"
#include <numeric>

const string EXPECTED_IN_FILE = "file/input/expected.txt";
const string EXPECTED_OUT_FILE = "file/output/expected.txt";

struct ExpectedTable {

    vector<Entry> entries;
    vector<double> rarityProbs;

    ExpectedTable();
    void writeToFile() const;

};

double calculateValue(const string& expression);
double calculatePercentExpression(const string& expression);

#endif