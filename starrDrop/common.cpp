#include "common.h"

Entry::Entry() {
    this->name = "";
    this->values = vector<double>(REWARD_TYPES.size(), 0.0);
}

void Common::writeToFile(const vector<Entry>& entries, const string& nameLabel, const string& filename) {
    vector<string> content = {nameLabel + " " + strUtil::join(REWARD_TYPES, " ")};
    for (const Entry& entry : entries) {
        content.push_back(entry.name + " " + strUtil::join(absFunc::map<double, string>(entry.values, [] (const double& value) {
            return numUtil::simplify(to_string(value));
        }), " "));
    }
    file::outputVecTo(content, filename);
}