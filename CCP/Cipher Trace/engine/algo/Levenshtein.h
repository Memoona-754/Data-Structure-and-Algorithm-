// engine/algo/Levenshtein.h
#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Levenshtein {
public:
    static int compute(const std::string& s1, const std::string& s2) {
        int m = (int)s1.length();
        int n = (int)s2.length();
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i][j - 1] + 1,
                                         dp[i - 1][j] + 1,
                                         dp[i - 1][j - 1] + 1});
                }
            }
        }
        return dp[m][n];
    }

    static bool isTyposquat(const std::string& candidate, const std::string& genuineBrand, int maxDistance = 2) {
        if (candidate == genuineBrand) return false;
        int dist = compute(candidate, genuineBrand);
        return (dist > 0 && dist <= maxDistance);
    }
};
