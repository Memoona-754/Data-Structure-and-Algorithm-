// Normalizer.h
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

class Normalizer {
public:
    // Transforms obfuscated text into clean, searchable lowercase text
    // Preserves raw URLs and phone numbers intact to protect forensic integrity!
    static std::string normalize(const std::string& input) {
        std::stringstream ss(input);
        std::string word;
        std::string result = "";

        while (ss >> word) {
            std::string cleanedWord = normalizeWord(word);
            if (!result.empty()) {
                result += " ";
            }
            result += cleanedWord;
        }

        std::string compressed = "";
        for (char c : result) {
            if (isPunctuation(c)) {
                if (!compressed.empty() && compressed.back() == c) {
                    continue;
                }
            }
            compressed += c;
        }

        return compressed;
    }

private:
    static bool isUrl(const std::string& s) {
        return (s.rfind("http://", 0) == 0 || s.rfind("https://", 0) == 0 || 
                s.rfind("www.", 0) == 0 || s.find(".xyz") != std::string::npos ||
                s.find(".com") != std::string::npos || s.find(".top") != std::string::npos);
    }

    static bool isPureNumberOrPhone(const std::string& s) {
        int digits = 0;
        int letters = 0;
        for (char c : s) {
            if (std::isdigit((unsigned char)c)) digits++;
            else if (std::isalpha((unsigned char)c)) letters++;
        }
        return (letters == 0 && digits > 0) || (digits >= 8);
    }

    static std::string normalizeWord(const std::string& word) {
        // URLs and phone numbers must preserve exact literal characters for forensic accuracy
        if (isUrl(word) || isPureNumberOrPhone(word)) {
            std::string res = "";
            for (char c : word) {
                res += (char)std::tolower((unsigned char)c);
            }
            return res;
        }

        // Standard text: decode leetspeak
        std::string res = "";
        for (char c : word) {
            switch (c) {
                case '0': res += 'o'; break;
                case '1': res += 'i'; break;
                case '3': res += 'e'; break;
                case '4': res += 'a'; break;
                case '5': res += 's'; break;
                case '7': res += 't'; break;
                case '@': res += 'a'; break;
                case '$': res += 's'; break;
                default:
                    res += (char)std::tolower((unsigned char)c);
                    break;
            }
        }
        return res;
    }

    static bool isPunctuation(char c) {
        return c == '!' || c == '?' || c == '.' || c == ',' || c == '-' || c == '_';
    }
};
