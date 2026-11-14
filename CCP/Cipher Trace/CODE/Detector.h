// Detector.h
#pragma once
#include <vector>
#include <string>
#include "Rule.h"
#include "Stack.h"
#include "Tokenizer.h"

// Abstract Base Class for all forensic detectors (Demonstrates OOP Polymorphism)
class Detector {
public:
    virtual ~Detector() = default;
    
    // Pure virtual method: scans tokens and pushes discovered Evidence onto the Stack
    virtual void scan(const std::vector<Token>& tokens,
                      const std::string& rawText,
                      Stack<Evidence>& evidenceStack) = 0;

    virtual std::string getName() const = 0;
};
