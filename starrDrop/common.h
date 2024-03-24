#ifndef COMMON_DOT_H
#define COMMON_DOT_H

#include "general/vectorUtility.h"
#include "general/mapUtility.h"
#include "general/file.h"
#include "general/numberUtility.h"

const int COINS = 0;
const int PPT = 1;
const int DOUBLERS = 2;
const int CREDITS = 3;
const int COSMETICS = 4;
const int HYPER = 5;

const vector<string> REWARD_TYPES = {"coins", "ppt", "doublers", "credits", "cosmetics", "hyper"};
const map<string, int> REWARD_TYPE_TO_INDEX = mapUtil::makeElementToIndexMap(REWARD_TYPES);

struct Entry {

    string name;
    vector<double> values;

    Entry();

};

namespace Common {
    void writeToFile(const vector<Entry>& entries, const string& nameLabel, const string& filename);
}

#endif