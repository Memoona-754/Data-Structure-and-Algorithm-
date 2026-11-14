// PatternDetector.h
#pragma once
#include <cctype>
#include <string>
#include <vector>
#include "Detector.h"
#include "Stack.h"

class PatternDetector : public Detector {
public:
    std::string getName() const override {
        return "PatternDetector";
    }

    void scan(const std::vector<Token>& tokens,
              const std::string& rawText,
              Stack<Evidence>& evidenceStack) override {
        // 1. ALL CAPS Shouting Ratio Check
        int upperCount = 0;
        int letterCount = 0;
        for (char c : rawText) {
            if (std::isalpha((unsigned char)c)) {
                letterCount++;
                if (std::isupper((unsigned char)c)) {
                    upperCount++;
                }
            }
        }

        if (letterCount >= 10) {
            double upperRatio = (double)upperCount / letterCount;
            if (upperRatio >= 0.35) {
                Evidence e;
                e.found = std::to_string((int)(upperRatio * 100)) + "% ALL-CAPS";
                e.category = Category::PATTERN;
                e.weight = 15;
                e.reason = "High proportion of uppercase text (psychological urgency/pressure tactic)";
                evidenceStack.push(e);
            }
        }

        // 2. Excessive Exclamation Spam
        int exclamationCount = 0;
        for (char c : rawText) {
            if (c == '!') exclamationCount++;
        }
        if (exclamationCount >= 3) {
            Evidence e;
            e.found = std::to_string(exclamationCount) + " exclamations";
            e.category = Category::PATTERN;
            e.weight = 10;
            e.reason = "Excessive exclamation marks ('!') used to manufacture false urgency";
            evidenceStack.push(e);
        }

        // 3. Direct Phone Number Lure
        for (const auto& token : tokens) {
            if (token.type == TokenType::PHONE_NUMBER) {
                Evidence e;
                e.found = token.value;
                e.category = Category::PATTERN;
                e.weight = 15;
                e.reason = "Unsolicited direct contact number encouraging private bypass communication";
                evidenceStack.push(e);
            }
        }
    }
};
