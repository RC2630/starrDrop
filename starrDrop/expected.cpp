#include "expected.h"

ExpectedTable::ExpectedTable() {

    vector<string> lines;
    file::inputStrVecFrom(lines, EXPECTED_IN_FILE);
    lines.push_back("");
    Entry entry;

    for (const string& line : lines) {
        
        // separator line
        if (line.empty()) {
            this->entries.push_back(entry);
            entry = Entry();
            continue;
        }

        // rarity line
        if (strUtil::endsWith(line, ":")) {
            string rarity = strUtil::removeAllAfterChar(line, ' ');
            string percent = strUtil::removeAllBeforeChar(line, ' ', true);
            percent = percent.substr(0, percent.size() - 1);
            double rarityProb = stod(percent) / 100;
            this->rarityProbs.push_back(rarityProb);
            string prob = numUtil::simplify(to_string(rarityProb));
            entry.name = rarity + " " + prob;
            continue;
        }

        // data line
        vector<string> parts = strUtil::split(line, ": ");
        int index = REWARD_TYPE_TO_INDEX.at(parts.front());
        double value = calculateValue(parts.back());
        entry.values.at(index) = value;

    }

    Entry overall;
    overall.name = "OVERALL NA";
    for (int i = 0; i < overall.values.size(); i++) {
        for (int j = 0; j < this->entries.size(); j++) {
            overall.values.at(i) += this->rarityProbs.at(j) * this->entries.at(j).values.at(i);
        }
    }
    this->entries.push_back(overall);

}

void ExpectedTable::writeToFile() const {
    Common::writeToFile(this->entries, "rarity prob", EXPECTED_OUT_FILE);
}

double calculateValue(const string& expression) {
    
    vector<string> parts = strUtil::split(expression, ", ");
    double result = 0;

    for (const string& part : parts) {

        vector<string> amountAndPercent = strUtil::split(part, " ");
        string percent = amountAndPercent.back();
        double expected = calculatePercentExpression(percent);

        if (amountAndPercent.size() == 2) {
            expected *= stod(amountAndPercent.front());
        }

        result += expected;

    }

    return result;

}

double calculatePercentExpression(const string& expression) {
    vector<string> components = strUtil::split(expression, "+");
    return accumulate(components.begin(), components.end(), 0.0, [] (double rsf, const string& curr) {
        return rsf + stod(curr);
    }) / 100;
}