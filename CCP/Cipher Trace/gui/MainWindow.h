// gui/MainWindow.h
#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidget>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../CODE/RuleBook.h"
#include "../CODE/Investigator.h"
#include "../CODE/DoublyList.h"
#include "../CODE/CircularBuffer.h"
#include "../CODE/Sorting.h"
#include "../CODE/Levenshtein.h"
#include "../CODE/MaxHeap.h"
#include "../CODE/ThreatGraph.h"

struct GuiAuditRecord {
    int id;
    std::string preview;
    ThreatLevel level;
    int score;
    std::vector<Evidence> evidence;
    std::string summary;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private slots:
    void onAnalyzeClicked();
    void onLoadSamplePhishing();
    void onLoadSampleLottery();
    void onLoadSampleSafe();
    void onSortSeverityClicked();
    void onRunBfsTrace();
    void onCheckTyposquat();
    void onHistoryBack();
    void onHistoryForward();

private:
    void setupUi();
    void setupInvestigateTab(QWidget* tab);
    void setupEvidenceTab(QWidget* tab);
    void setupTopKTab(QWidget* tab);
    void setupGraphTab(QWidget* tab);
    void setupAlgoLabTab(QWidget* tab);
    void setupHistoryTab(QWidget* tab);
    void applyDarkForensicStyle();

    // Core Engine Instances
    RuleBook ruleBook;
    std::unique_ptr<Investigator> detective;
    ThreatGraph threatGraph;
    DoublyList<GuiAuditRecord> auditHistory;
    CircularBuffer<GuiAuditRecord> recentScans;
    int currentScanId;

    // Last Analysis Cache
    ForensicVerdict lastVerdict;
    bool isSortedBySeverity;

    // UI Widgets - Tab 1 (Investigate)
    QTextEdit* messageInput;
    QPushButton* analyzeBtn;
    QLabel* verdictBanner;
    QProgressBar* scoreBar;
    QTextBrowser* summaryBrowser;

    // UI Widgets - Tab 2 (Evidence Docket)
    QTableWidget* evidenceTable;
    QPushButton* toggleSortBtn;

    // UI Widgets - Tab 3 (Top-K & Homograph DP)
    QTableWidget* topKTable;
    QLineEdit* candidateDomainInput;
    QPushButton* checkTypoBtn;
    QLabel* typoResultLabel;

    // UI Widgets - Tab 4 (Syndicate Graph)
    QLineEdit* bfsTargetInput;
    QPushButton* runBfsBtn;
    QTextBrowser* graphResultsBrowser;

    // UI Widgets - Tab 5 (Algorithm Lab)
    QTableWidget* sortBenchTable;
    QLineEdit* searchKeywordInput;
    QPushButton* searchBenchBtn;
    QLabel* searchResultLabel;

    // UI Widgets - Tab 6 (Audit & Telemetry)
    QPushButton* backHistoryBtn;
    QPushButton* forwardHistoryBtn;
    QLabel* historyStatusLabel;
    QTableWidget* circularBufferTable;
};
