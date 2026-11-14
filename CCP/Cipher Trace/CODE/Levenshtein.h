// Levenshtein.h
#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Levenshtein {
public:
    // Computes the minimum edit distance using a 2D Dynamic Programming Table
    // Time Complexity:  O(M * N)
    // Space Complexity: O(M * N)
    static int compute(const std::string& s1, const std::string& s2) {
        int m = (int)s1.length();
        int n = (int)s2.length();

        // dp[i][j] stores the minimum edits to convert s1[0..i-1] into s2[0..j-1]
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

        // Base cases: converting empty string to target requires insertions
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        // Fill DP matrix using optimal substructure
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1]; // Characters match, zero cost
                } else {
                    int insertion    = dp[i][j - 1] + 1;
                    int deletion     = dp[i - 1][j] + 1;
                    int substitution = dp[i - 1][j - 1] + 1;
                    dp[i][j] = std::min({insertion, deletion, substitution});
                }
            }
        }

        return dp[m][n];
    }

    // Checks if candidate is a typosquat/homograph spoof of a genuine brand
    // (e.g. "paypa1" vs "paypal" has distance 1 -> TRUE)
    static bool isTyposquat(const std::string& candidate, const std::string& genuineBrand, int maxDistance = 2) {
        if (candidate == genuineBrand) {
            return false; // Identical, not a typosquat
        }
        int dist = compute(candidate, genuineBrand);
        return (dist > 0 && dist <= maxDistance);
    }
};
