// Investigator.h
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Detector.h"
#include "KeywordDetector.h"
#include "UrlDetector.h"
#include "PatternDetector.h"
#include "Normalizer.h"
#include "Tokenizer.h"
#include "Scorer.h"
#include "Stack.h"

class Investigator {
private:
    std::vector<std::unique_ptr<Detector>> detectors;

public:
    Investigator(const RuleBook& ruleBook) {
        // Register all polymorphic detectors into the investigative battery
        detectors.push_back(std::make_unique<KeywordDetector>(ruleBook));
        detectors.push_back(std::make_unique<UrlDetector>());
        detectors.push_back(std::make_unique<PatternDetector>());
    }

    // Executes the complete end-to-end investigative pipeline on a message
    ForensicVerdict analyze(const std::string& rawMessage) {
        // 1. Text Normalization (De-obfuscate leetspeak)
        std::string normalized = Normalizer::normalize(rawMessage);

        // 2. Tokenization (Extract words, links, numbers)
        std::vector<Token> tokens = Tokenizer::tokenize(normalized);

        // 3. Evidence Docket Stack (LIFO)
        Stack<Evidence> evidenceStack;

        // 4. Run each polymorphic detector
        for (const auto& detector : detectors) {
            detector->scan(tokens, rawMessage, evidenceStack);
        }

        // 5. Evaluate threat score & apply combo penalties
        return Scorer::evaluate(evidenceStack);
    }
};
