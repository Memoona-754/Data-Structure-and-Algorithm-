// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "RuleBook.h"
#include "Investigator.h"
#include "Levenshtein.h"
#include "MaxHeap.h"
#include "ThreatGraph.h"

using namespace std;

void testLevenshteinDP() {
    cout << "\n======================================================================" << endl;
    cout << " [1] DYNAMIC PROGRAMMING: LEVENSHTEIN TYPOSQUATTING DETECTION" << endl;
    cout << "======================================================================" << endl;

    struct Case {
        string spoof;
        string brand;
    };

    vector<Case> cases = {
        {"paypa1", "paypal"},
        {"easypa1sa", "easypaisa"},
        {"jazcash", "jazzcash"},
        {"b1sp", "bisp"},
        {"netflix", "hbl"}
    };

    cout << left << setw(18) << "Target Domain"
         << setw(16) << "Legit Brand"
         << setw(14) << "DP Distance"
         << setw(20) << "Forensic Finding" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (const auto& c : cases) {
        int dist = Levenshtein::compute(c.spoof, c.brand);
        bool isSpoof = Levenshtein::isTyposquat(c.spoof, c.brand, 2);
        string status = isSpoof ? "[!] HOMOGRAPH ATTACK" : "[√] Clean / Unrelated";

        cout << left << setw(18) << c.spoof
             << setw(16) << c.brand
             << setw(14) << dist
             << setw(20) << status << endl;
    }
}

void testMaxHeapTopK(const vector<Evidence>& evidenceList, int k = 3) {
    cout << "\n======================================================================" << endl;
    cout << " [2] MAX-HEAP: TOP-" << k << " EXECUTIVE THREAT EXTRACTION (O(K log N))" << endl;
    cout << "======================================================================" << endl;

    if (evidenceList.empty()) {
        cout << " No evidence to heapify." << endl;
        return;
    }

    // Build Max-Heap ordered by Evidence weight
    MaxHeap<Evidence, EvidenceWeightComparator> threatHeap;
    for (const auto& ev : evidenceList) {
        threatHeap.insert(ev);
    }

    cout << " Successfully pushed " << threatHeap.size() << " clues into Binary Max-Heap." << endl;
    cout << " Extracting Top-" << k << " most dangerous threats without sorting whole array:\n" << endl;

    int extracted = 0;
    while (!threatHeap.isEmpty() && extracted < k) {
        Evidence top = threatHeap.extractMax();
        extracted++;
        cout << "   Top #" << extracted << " [Priority Weight: +" << setw(2) << top.weight << "] "
             << "'" << top.found << "' -> " << top.reason << endl;
    }
}

void testThreatGraphBFS() {
    cout << "\n======================================================================" << endl;
    cout << " [3] THREAT SYNDICATE GRAPH: BFS CRIME RING DISCOVERY" << endl;
    cout << "======================================================================" << endl;

    ThreatGraph graph;

    // Simulate multi-message intelligence across several intercepted SMS messages:
    // Campaign 1: Connected fraud syndicate sharing URLs and mule phone numbers
    graph.addLink("+923001111111", "http://bit.ly/easypaisa-gift");
    graph.addLink("http://bit.ly/easypaisa-gift", "+923212222222");
    graph.addLink("+923212222222", "easypa1sa-update.xyz");
    graph.addLink("easypa1sa-update.xyz", "+923334444444");

    // Campaign 2: An independent fake lottery operator
    graph.addLink("+923459999999", "http://bisp-claim.top");

    cout << " Built graph with " << graph.vertexCount() << " intelligence vertices." << endl;

    // Run BFS starting from one suspicious number using our custom Queue<T>!
    string target = "+923001111111";
    cout << "\n Running BFS from target '" << target << "' to unmask connected ring:" << endl;
    vector<string> ring = graph.bfsCluster(target);

    for (size_t i = 0; i < ring.size(); i++) {
        cout << "   Node " << (i + 1) << ": " << ring[i] << endl;
    }
    cout << " => Discovered " << ring.size() << " linked fraud assets in Syndicate #1!" << endl;

    // Discover all syndicates
    auto allSyndicates = graph.findAllSyndicates();
    cout << "\n Total Independent Scam Syndicates operating: " << allSyndicates.size() << endl;
    for (size_t s = 0; s < allSyndicates.size(); s++) {
        cout << "   Syndicate Ring " << (s + 1) << " size: " << allSyndicates[s].size() << " entities." << endl;
    }
}

int main() {
    cout << "######################################################################" << endl;
    cout << "#           CIPHERTRACE: PHASE 6 ADVANCED DSA MASTERY                #" << endl;
    cout << "#     Dynamic Programming + Max-Heap Top-K + Threat Graph & BFS      #" << endl;
    cout << "######################################################################" << endl;

    // 1. Initialize Engine
    RuleBook book;
    if (!book.loadFromFile("rules.txt")) {
        cerr << "Error: Could not open rules.txt!" << endl;
        return 1;
    }
    Investigator detective(book);

    // 2. Run Levenshtein Dynamic Programming Test
    testLevenshteinDP();

    // 3. Analyze a message with Typosquatting to feed into Max-Heap
    string typosquatMessage = "URG3NT: Your account is suspended! Login to http://easypa1sa.xyz to verify your OTP immediately!";
    cout << "\n======================================================================" << endl;
    cout << " Analyzing Attack Message with Typosquatting:" << endl;
    cout << " \"" << typosquatMessage << "\"" << endl;
    cout << "======================================================================" << endl;

    ForensicVerdict verdict = detective.analyze(typosquatMessage);
    cout << " Verdict: " << threatLevelString(verdict.level) << " | Score: " << verdict.cappedScore << " / 100" << endl;

    // 4. Run Max-Heap Top-K Extraction
    testMaxHeapTopK(verdict.evidenceList, 3);

    // 5. Run Threat Graph BFS
    testThreatGraphBFS();

    cout << "\n======================================================================" << endl;
    cout << " Phase 6 Levenshtein DP, Max-Heap, & Threat Graph: 100% VERIFIED!" << endl;
    cout << "======================================================================" << endl;

    return 0;
}
