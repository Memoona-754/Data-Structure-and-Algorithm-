// engine/core/Rule.h
#pragma once
#include <string>

// Categories of forensic scam red flags
enum class Category {
    URGENCY,
    MONEY,
    CREDENTIAL,
    IMPERSONATION,
    LINK,
    PATTERN
};

inline std::string categoryName(Category c) {
    switch (c) {
        case Category::URGENCY:       return "URGENCY";
        case Category::MONEY:         return "MONEY";
        case Category::CREDENTIAL:    return "CREDENTIAL";
        case Category::IMPERSONATION: return "IMPERSONATION";
        case Category::LINK:          return "LINK";
        default:                      return "PATTERN";
    }
}

inline Category categoryFromString(const std::string& s) {
    if (s == "URGENCY")       return Category::URGENCY;
    if (s == "MONEY")         return Category::MONEY;
    if (s == "CREDENTIAL")    return Category::CREDENTIAL;
    if (s == "IMPERSONATION") return Category::IMPERSONATION;
    if (s == "LINK")          return Category::LINK;
    return Category::PATTERN;
}

// Single detection rule in our dictionary
struct Rule {
    std::string keyword;
    Category category;
    int weight;
};

// Single piece of detected forensic evidence
struct Evidence {
    std::string found;
    Category category;
    int weight;
    std::string reason;
};
