// engine/core/RuleBook.h
#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Rule.h"

class RuleBook {
private:
    std::vector<Rule> rules;
    mutable int lastComparisons;

public:
    RuleBook() : lastComparisons(0) {}

    void addRule(const std::string& keyword, Category category, int weight) {
        Rule r;
        r.keyword = keyword;
        r.category = category;
        r.weight = weight;
        rules.push_back(r);
        sortRules();
    }

    void loadDefaults() {
        if (!rules.empty()) return;
        addRule("urgent", Category::URGENCY, 15);
        addRule("immediately", Category::URGENCY, 15);
        addRule("suspended", Category::URGENCY, 15);
        addRule("expires", Category::URGENCY, 10);
        addRule("warning", Category::URGENCY, 15);
        addRule("blocked", Category::URGENCY, 15);
        addRule("prize", Category::MONEY, 20);
        addRule("lottery", Category::MONEY, 25);
        addRule("winner", Category::MONEY, 20);
        addRule("reward", Category::MONEY, 15);
        addRule("cash", Category::MONEY, 10);
        addRule("claim", Category::MONEY, 15);
        addRule("bonus", Category::MONEY, 15);
        addRule("congratulations", Category::MONEY, 15);
        addRule("otp", Category::CREDENTIAL, 30);
        addRule("pin", Category::CREDENTIAL, 20);
        addRule("password", Category::CREDENTIAL, 30);
        addRule("cnic", Category::CREDENTIAL, 25);
        addRule("verify", Category::CREDENTIAL, 15);
        addRule("easypaisa", Category::IMPERSONATION, 15);
        addRule("jazzcash", Category::IMPERSONATION, 15);
        addRule("bank", Category::IMPERSONATION, 10);
        addRule("bisp", Category::IMPERSONATION, 20);
        addRule("click", Category::LINK, 10);
        addRule("link", Category::LINK, 10);
        sortRules();
    }

    bool loadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open())
            return false;

        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            if (line.empty() || line[0] == '#')
                continue;

            size_t c1 = line.find(',');
            size_t c2 = line.find(',', c1 + 1);
            if (c1 == std::string::npos || c2 == std::string::npos)
                continue;

            try {
                Rule r;
                r.keyword  = line.substr(0, c1);
                r.category = categoryFromString(line.substr(c1 + 1, c2 - c1 - 1));
                r.weight   = std::stoi(line.substr(c2 + 1));
                rules.push_back(r);
            } catch (...) {
                continue;
            }
        }
        sortRules();
        return true;
    }

    void sortRules() {
        for (int i = 1; i < (int)rules.size(); i++) {
            Rule current = rules[i];
            int j = i - 1;
            while (j >= 0 && rules[j].keyword > current.keyword) {
                rules[j + 1] = rules[j];
                j--;
            }
            rules[j + 1] = current;
        }
    }

    int binarySearch(const std::string& keyword) const {
        lastComparisons = 0;
        int low = 0;
        int high = (int)rules.size() - 1;

        while (low <= high) {
            lastComparisons++;
            int mid = low + (high - low) / 2;

            if (rules[mid].keyword == keyword)
                return mid;
            else if (rules[mid].keyword < keyword)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1;
    }

    int linearSearch(const std::string& keyword) const {
        lastComparisons = 0;
        for (int i = 0; i < (int)rules.size(); i++) {
            lastComparisons++;
            if (rules[i].keyword == keyword)
                return i;
        }
        return -1;
    }

    const Rule& getRule(int index) const { return rules[index]; }
    int size() const { return (int)rules.size(); }
    int getLastComparisons() const { return lastComparisons; }

    void printAll() const {
        for (int i = 0; i < (int)rules.size(); i++)
            std::cout << i << ": " << rules[i].keyword << " ["
                      << categoryName(rules[i].category) << ", "
                      << rules[i].weight << "]\n";
    }
};
