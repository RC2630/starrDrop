#ifndef DATA_DOT_H
#define DATA_DOT_H

#include "common.h"

const string DATA_IN_FILE = "file/input/data.txt";
const string EQUIVALENT_IN_FILE = "file/input/equivalent.txt";
const string DATA_OUT_FILE = "file/output/table.txt";

struct DataTable {

    vector<Entry> entries;

    DataTable();
    void writeToFile() const;

};

#endif