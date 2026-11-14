// engine/detectors/Detector.h
#pragma once
#include <vector>
#include <string>
#include "../core/Rule.h"
#include "../ds/Stack.h"
#include "../core/Tokenizer.h"

class Detector {
public:
    virtual ~Detector() = default;
    virtual void scan(const std::vector<Token>& tokens,
                      const std::string& rawText,
                      Stack<Evidence>& evidenceStack) = 0;
    virtual std::string getName() const = 0;
};
