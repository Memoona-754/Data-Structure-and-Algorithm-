// KeywordDetector.h
#pragma once
#include "Detector.h"
#include "RuleBook.h"

class KeywordDetector : public Detector {
private:
    const RuleBook& ruleBook;

public:
    KeywordDetector(const RuleBook& rb) : ruleBook(rb) {}

    std::string getName() const override {
        return "KeywordDetector";
    }

    void scan(const std::vector<Token>& tokens,
              const std::string& /*rawText*/,
              Stack<Evidence>& evidenceStack) override {
        for (const auto& token : tokens) {
            if (token.type == TokenType::WORD) {
                int idx = ruleBook.binarySearch(token.value);
                if (idx != -1) {
                    const Rule& r = ruleBook.getRule(idx);
                    Evidence e;
                    e.found = token.value;
                    e.category = r.category;
                    e.weight = r.weight;
                    e.reason = "Matched scam dictionary keyword '" + r.keyword + 
                               "' [" + categoryName(r.category) + "]";
                    evidenceStack.push(e);
                }
            }
        }
    }
};
