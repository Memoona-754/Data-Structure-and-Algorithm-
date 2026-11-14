// UrlDetector.h
#pragma once
#include <sstream>
#include <vector>
#include "Detector.h"
#include "Stack.h"
#include "Levenshtein.h"

class UrlDetector : public Detector {
public:
    std::string getName() const override {
        return "UrlDetector";
    }

    void scan(const std::vector<Token>& tokens,
              const std::string& /*rawText*/,
              Stack<Evidence>& evidenceStack) override {
        for (const auto& token : tokens) {
            if (token.type == TokenType::URL) {
                analyzeUrl(token.value, evidenceStack);
            }
        }
    }

private:
    void analyzeUrl(const std::string& url, Stack<Evidence>& evidenceStack) {
        // Base link evidence
        Evidence baseLink;
        baseLink.found = url;
        baseLink.category = Category::LINK;
        baseLink.weight = 15;
        baseLink.reason = "Unsolicited clickable URL found in message";
        evidenceStack.push(baseLink);

        std::string host = extractHost(url);
        if (host.empty()) return;

        // ====================================================================
        // DSA FEATURE: DOMAIN REVERSAL STACK
        // ====================================================================
        Stack<std::string> labelStack;
        std::stringstream ss(host);
        std::string label;
        while (std::getline(ss, label, '.')) {
            if (!label.empty()) {
                labelStack.push(label);
            }
        }

        if (labelStack.size() >= 2) {
            std::string tld = labelStack.pop();
            std::string sld = labelStack.pop();
            std::string realDomain = sld + "." + tld;

            // 1. High-risk TLD check
            if (isSuspiciousTld(tld)) {
                Evidence e;
                e.found = "." + tld;
                e.category = Category::LINK;
                e.weight = 20;
                e.reason = "High-risk, disposable TLD (." + tld + ") often used in phishing";
                evidenceStack.push(e);
            }

            // 2. Subdomain Spoofing check
            std::vector<std::string> trustedBrands = {"easypaisa", "jazzcash", "paypal", "hbl", "ubl", "bisp"};
            for (const auto& brand : trustedBrands) {
                if (host.find(brand) != std::string::npos && realDomain.find(brand) == std::string::npos) {
                    Evidence spoof;
                    spoof.found = host;
                    spoof.category = Category::IMPERSONATION;
                    spoof.weight = 35;
                    spoof.reason = "CRITICAL SUBDOMAIN SPOOFING: Host fakes brand '" + brand + 
                                   "', but true registered domain (via Domain Stack) is '" + realDomain + "'";
                    evidenceStack.push(spoof);
                    break;
                }
            }

            // ====================================================================
            // DSA FEATURE: DYNAMIC PROGRAMMING LEVENSHTEIN (Typosquatting Detection)
            // Checks if second-level domain (sld) is a deceptive homograph (e.g. "paypa1", "easypa1sa")
            // ====================================================================
            for (const auto& brand : trustedBrands) {
                if (Levenshtein::isTyposquat(sld, brand, 2)) {
                    int dist = Levenshtein::compute(sld, brand);
                    Evidence typo;
                    typo.found = sld;
                    typo.category = Category::IMPERSONATION;
                    typo.weight = 30;
                    typo.reason = "TYPOSQUATTING HOMOGRAPH DETECTED: '" + sld + 
                                   "' is edit-distance " + std::to_string(dist) + 
                                   " from genuine brand '" + brand + "' (2D DP Matrix)";
                    evidenceStack.push(typo);
                    break;
                }
            }
        }
    }

    static std::string extractHost(const std::string& url) {
        std::string host = url;
        size_t scheme = host.find("://");
        if (scheme != std::string::npos) {
            host = host.substr(scheme + 3);
        }
        size_t slash = host.find('/');
        if (slash != std::string::npos) {
            host = host.substr(0, slash);
        }
        size_t colon = host.find(':');
        if (colon != std::string::npos) {
            host = host.substr(0, colon);
        }
        return host;
    }

    static bool isSuspiciousTld(const std::string& tld) {
        return (tld == "xyz" || tld == "top" || tld == "tk" || tld == "ml" || 
                tld == "ga"  || tld == "cf"  || tld == "icu"|| tld == "live");
    }
};
