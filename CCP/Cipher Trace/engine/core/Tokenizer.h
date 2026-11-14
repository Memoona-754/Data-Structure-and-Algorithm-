// engine/core/Tokenizer.h
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

enum class TokenType {
    WORD,
    URL,
    PHONE_NUMBER
};

struct Token {
    std::string value;
    TokenType type;
};

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& text) {
        std::vector<Token> tokens;
        std::stringstream ss(text);
        std::string raw;

        while (ss >> raw) {
            if (raw.empty()) continue;

            if (isUrl(raw)) {
                tokens.push_back({stripTrailingPunct(raw), TokenType::URL});
                continue;
            }

            if (isPhoneNumber(raw)) {
                tokens.push_back({stripTrailingPunct(raw), TokenType::PHONE_NUMBER});
                continue;
            }

            std::string cleaned = cleanWord(raw);
            if (!cleaned.empty()) {
                tokens.push_back({cleaned, TokenType::WORD});
            }
        }

        return tokens;
    }

    static std::vector<std::string> getWordList(const std::vector<Token>& tokens) {
        std::vector<std::string> words;
        for (const auto& t : tokens) {
            words.push_back(t.value);
        }
        return words;
    }

private:
    static bool isUrl(const std::string& s) {
        if (s.rfind("http://", 0) == 0 || s.rfind("https://", 0) == 0 || s.rfind("www.", 0) == 0) {
            return true;
        }
        if (s.find(".com") != std::string::npos ||
            s.find(".xyz") != std::string::npos ||
            s.find(".pk")  != std::string::npos ||
            s.find(".top") != std::string::npos ||
            s.find(".info")!= std::string::npos) {
            return true;
        }
        return false;
    }

    static bool isPhoneNumber(const std::string& s) {
        size_t digits = 0;
        for (char c : s) {
            if (std::isdigit((unsigned char)c)) digits++;
        }
        return (digits >= 10 && digits <= 13);
    }

    static std::string stripTrailingPunct(const std::string& s) {
        std::string res = s;
        while (!res.empty() && (res.back() == '!' || res.back() == '?' || res.back() == '.' || 
                                res.back() == ',' || res.back() == '"' || res.back() == '\'')) {
            res.pop_back();
        }
        return res;
    }

    static std::string cleanWord(const std::string& s) {
        size_t start = 0;
        while (start < s.length() && (std::ispunct((unsigned char)s[start]) || std::isspace((unsigned char)s[start]))) {
            start++;
        }

        if (start >= s.length()) return "";

        size_t end = s.length() - 1;
        while (end > start && (std::ispunct((unsigned char)s[end]) || std::isspace((unsigned char)s[end]))) {
            end--;
        }

        return s.substr(start, end - start + 1);
    }
};
