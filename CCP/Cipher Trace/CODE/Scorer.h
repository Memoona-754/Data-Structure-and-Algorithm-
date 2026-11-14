// Scorer.h
#pragma once
#include <vector>
#include <string>
#include "Rule.h"
#include "Stack.h"

enum class ThreatLevel {
    SAFE,
    SUSPICIOUS,
    CRITICAL_SCAM
};

inline std::string threatLevelString(ThreatLevel level) {
    switch (level) {
        case ThreatLevel::SAFE:          return "SAFE";
        case ThreatLevel::SUSPICIOUS:    return "SUSPICIOUS";
        case ThreatLevel::CRITICAL_SCAM: return "CRITICAL SCAM";
        default:                         return "UNKNOWN";
    }
}

struct ForensicVerdict {
    int rawScore;
    int cappedScore;
    ThreatLevel level;
    int comboBonus;
    std::vector<Evidence> evidenceList;
    std::string summary;
};

class Scorer {
public:
    static ForensicVerdict evaluate(Stack<Evidence>& evidenceStack) {
        ForensicVerdict verdict;
        verdict.rawScore = 0;
        verdict.comboBonus = 0;

        bool hasUrgency = false;
        bool hasMoney = false;
        bool hasCredential = false;
        bool hasLink = false;

        // Pop all evidence from LIFO Stack
        while (!evidenceStack.isEmpty()) {
            Evidence e = evidenceStack.pop();
            verdict.evidenceList.push_back(e);
            verdict.rawScore += e.weight;

            if (e.category == Category::URGENCY)    hasUrgency = true;
            if (e.category == Category::MONEY)      hasMoney = true;
            if (e.category == Category::CREDENTIAL) hasCredential = true;
            if (e.category == Category::LINK)       hasLink = true;
        }

        // ====================================================================
        // FORENSIC COMBO MULTIPLIER:
        // Attackers combine Urgency + Financial Lure + Link/Credential Theft.
        // If all 3 vectors are present simultaneously, apply critical penalty bonus.
        // ====================================================================
        if (hasUrgency && (hasMoney || hasCredential) && hasLink) {
            verdict.comboBonus = 25;
            verdict.rawScore += verdict.comboBonus;
            
            Evidence comboEvidence;
            comboEvidence.found = "TRIPLE-THREAT COMBO";
            comboEvidence.category = Category::PATTERN;
            comboEvidence.weight = 25;
            comboEvidence.reason = "Compound Attack Vector Detected: Urgency + Financial/Credential Bait + Actionable Link";
            verdict.evidenceList.push_back(comboEvidence);
        }

        // Cap score at 100 for GUI meter percentage
        verdict.cappedScore = (verdict.rawScore > 100) ? 100 : verdict.rawScore;

        // Determine Verdict
        if (verdict.cappedScore >= 60) {
            verdict.level = ThreatLevel::CRITICAL_SCAM;
            verdict.summary = "HIGH CONFIDENCE FRAUD: Multiple severe indicators of social engineering and credentials/asset compromise.";
        } else if (verdict.cappedScore >= 30) {
            verdict.level = ThreatLevel::SUSPICIOUS;
            verdict.summary = "ELEVATED RISK: Message exhibits coercive or deceptive patterns. Proceed with caution.";
        } else {
            verdict.level = ThreatLevel::SAFE;
            verdict.summary = "LOW THREAT: No significant cryptographic or social engineering red flags detected.";
        }

        return verdict;
    }
};
