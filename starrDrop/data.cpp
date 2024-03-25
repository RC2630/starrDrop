#include "data.h"

DataTable::DataTable() {

    vector<string> equivalent;
    file::inputStrVecFrom(equivalent, EQUIVALENT_IN_FILE);

    vector<pair<string, string>> equivPairs = absFunc::map<string, pair<string, string>>(equivalent, [] (const string& line) {
        vector<string> parts = strUtil::split(line, ": ");
        return pair<string, string>(parts.front(), parts.back());
    });

    map<string, string> equivMap = mapUtil::makeMapFromVectorOfPairs(equivPairs);

    vector<string> lines;
    file::inputStrVecFrom(lines, DATA_IN_FILE);

    for (const string& line : lines) {
        
        Entry entry;
        string rarity = strUtil::removeAllAfterChar(line, ' ');
        string reward = strUtil::removeAllBeforeChar(line, ' ', true);
        entry.name = rarity;
        reward = mapUtil::getOrSelf(equivMap, reward);

        vector<string> parts = strUtil::split(reward, " ");
        string rewardType = parts.back();
        int rewardCount = (parts.size() == 2) ? stoi(parts.front()) : 1;

        entry.values.at(REWARD_TYPE_TO_INDEX.at(rewardType)) = rewardCount;
        this->entries.push_back(entry);

    }

}

void DataTable::writeToFile() const {
    Common::writeToFile(this->entries, "rarity", DATA_OUT_FILE);
}