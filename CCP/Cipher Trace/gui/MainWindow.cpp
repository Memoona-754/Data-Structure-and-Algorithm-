// gui/MainWindow.cpp
#include "MainWindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), recentScans(5), currentScanId(0), isSortedBySeverity(false) {

    // 1. Initialize RuleBook with robust multi-path discovery
    QString appDir = QCoreApplication::applicationDirPath();
    std::vector<std::string> candidatePaths = {
        (appDir + "/rules.txt").toStdString(),
        (appDir + "/../rules.txt").toStdString(),
        (appDir + "/../../rules.txt").toStdString(),
        (appDir + "/../../CODE/rules.txt").toStdString(),
        (appDir + "/../../data/rules.txt").toStdString(),
        "rules.txt",
        "CODE/rules.txt",
        "../CODE/rules.txt",
        "data/rules.txt",
        "../data/rules.txt",
        "C:/Users/LENOVO/OneDrive/Desktop/Data-Structure-and-Algorithm-/CCP/Cipher Trace/CODE/rules.txt",
        "C:/Users/LENOVO/OneDrive/Desktop/Data-Structure-and-Algorithm-/CCP/Cipher Trace/data/rules.txt"
    };

    bool loaded = false;
    for (const auto& path : candidatePaths) {
        if (ruleBook.loadFromFile(path) && ruleBook.size() > 0) {
            loaded = true;
            break;
        }
    }

    // Safety fallback: if no file could be read, populate essential rules directly
    if (!loaded || ruleBook.size() == 0) {
        ruleBook.loadDefaults();
    }

    detective = std::make_unique<Investigator>(ruleBook);

    // 2. Pre-populate sample intelligence into ThreatGraph
    threatGraph.addLink("+923001111111", "http://bit.ly/easypaisa-gift");
    threatGraph.addLink("http://bit.ly/easypaisa-gift", "+923212222222");
    threatGraph.addLink("+923212222222", "easypa1sa-update.xyz");
    threatGraph.addLink("easypa1sa-update.xyz", "+923334444444");
    threatGraph.addLink("+923459999999", "http://bisp-claim.top");

    // 3. Build UI
    setupUi();
    applyDarkForensicStyle();
}

void MainWindow::setupUi() {
    setWindowTitle("CipherTrace - Digital Forensics & Scam Detection Engine");
    resize(1100, 750);

    QTabWidget* tabs = new QTabWidget(this);

    QWidget* tabInvestigate = new QWidget();
    QWidget* tabEvidence    = new QWidget();
    QWidget* tabTopK        = new QWidget();
    QWidget* tabGraph       = new QWidget();
    QWidget* tabAlgoLab     = new QWidget();
    QWidget* tabHistory     = new QWidget();

    setupInvestigateTab(tabInvestigate);
    setupEvidenceTab(tabEvidence);
    setupTopKTab(tabTopK);
    setupGraphTab(tabGraph);
    setupAlgoLabTab(tabAlgoLab);
    setupHistoryTab(tabHistory);

    tabs->addTab(tabInvestigate, "1. Investigate");
    tabs->addTab(tabEvidence,    "2. Evidence Docket (Stack)");
    tabs->addTab(tabTopK,        "3. Top-K Threats & Homographs");
    tabs->addTab(tabGraph,       "4. Syndicate Graph (BFS)");
    tabs->addTab(tabAlgoLab,     "5. Algorithm Lab");
    tabs->addTab(tabHistory,     "6. Audit & Telemetry");

    setCentralWidget(tabs);
}

void MainWindow::setupInvestigateTab(QWidget* tab) {
    QVBoxLayout* mainLayout = new QVBoxLayout(tab);

    QLabel* titleLabel = new QLabel("Suspicious Message Ingestion & Triage (Analyzes ANY message)", tab);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #00e5ff;");
    mainLayout->addWidget(titleLabel);

    messageInput = new QTextEdit(tab);
    messageInput->setPlaceholderText("Type or paste ANY suspicious SMS, WhatsApp message, email, or URL here...");
    messageInput->setMaximumHeight(120);
    mainLayout->addWidget(messageInput);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    QPushButton* samplePhishingBtn = new QPushButton("Preset: Subdomain Phishing", tab);
    QPushButton* sampleLotteryBtn  = new QPushButton("Preset: BISP Lottery Scam", tab);
    QPushButton* sampleSafeBtn     = new QPushButton("Preset: Clean Chat", tab);
    QPushButton* clearBtn          = new QPushButton("Clear Box", tab);
    analyzeBtn                     = new QPushButton("Run Forensic Analysis", tab);
    analyzeBtn->setStyleSheet("background-color: #00c853; font-weight: bold; font-size: 14px; padding: 8px;");

    connect(samplePhishingBtn, &QPushButton::clicked, this, &MainWindow::onLoadSamplePhishing);
    connect(sampleLotteryBtn,  &QPushButton::clicked, this, &MainWindow::onLoadSampleLottery);
    connect(sampleSafeBtn,     &QPushButton::clicked, this, &MainWindow::onLoadSampleSafe);
    connect(clearBtn,          &QPushButton::clicked, [this]() {
        messageInput->clear();
        verdictBanner->setText("VERDICT: AWAITING INPUT");
        verdictBanner->setStyleSheet("font-size: 18px; font-weight: bold; padding: 12px; background: #263238; border-radius: 6px;");
        scoreBar->setValue(0);
        summaryBrowser->clear();
    });
    connect(analyzeBtn,        &QPushButton::clicked, this, &MainWindow::onAnalyzeClicked);

    btnLayout->addWidget(samplePhishingBtn);
    btnLayout->addWidget(sampleLotteryBtn);
    btnLayout->addWidget(sampleSafeBtn);
    btnLayout->addWidget(clearBtn);
    btnLayout->addWidget(analyzeBtn);
    mainLayout->addLayout(btnLayout);

    // Results Dashboard
    QHBoxLayout* statusLayout = new QHBoxLayout();
    verdictBanner = new QLabel("VERDICT: AWAITING INPUT", tab);
    verdictBanner->setAlignment(Qt::AlignCenter);
    verdictBanner->setStyleSheet("font-size: 18px; font-weight: bold; padding: 12px; background: #263238; border-radius: 6px;");

    scoreBar = new QProgressBar(tab);
    scoreBar->setRange(0, 100);
    scoreBar->setValue(0);
    scoreBar->setTextVisible(true);
    scoreBar->setFormat("Threat Score: %v / 100");
    scoreBar->setStyleSheet("height: 30px; font-weight: bold;");

    statusLayout->addWidget(verdictBanner, 1);
    statusLayout->addWidget(scoreBar, 1);
    mainLayout->addLayout(statusLayout);

    QLabel* summaryLabel = new QLabel("Executive Forensic Dossier Summary:", tab);
    summaryLabel->setStyleSheet("font-weight: bold; color: #b0bec5;");
    mainLayout->addWidget(summaryLabel);

    summaryBrowser = new QTextBrowser(tab);
    summaryBrowser->setPlaceholderText("Forensic breakdown, detected red flags, and combo penalties will appear here after analysis.");
    mainLayout->addWidget(summaryBrowser);
}

void MainWindow::setupEvidenceTab(QWidget* tab) {
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QHBoxLayout* topLayout = new QHBoxLayout();
    QLabel* info = new QLabel("Evidence Case File (Popped from LIFO Stack):", tab);
    info->setStyleSheet("font-weight: bold; color: #00e5ff;");
    toggleSortBtn = new QPushButton("Sort by Severity (Custom MergeSort)", tab);
    connect(toggleSortBtn, &QPushButton::clicked, this, &MainWindow::onSortSeverityClicked);

    topLayout->addWidget(info);
    topLayout->addStretch();
    topLayout->addWidget(toggleSortBtn);
    layout->addLayout(topLayout);

    evidenceTable = new QTableWidget(tab);
    evidenceTable->setColumnCount(5);
    evidenceTable->setHorizontalHeaderLabels({"Rank", "Category", "Points", "Flagged Entity", "Forensic Explanation"});
    evidenceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    evidenceTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(evidenceTable);
}

void MainWindow::setupTopKTab(QWidget* tab) {
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QLabel* topKTitle = new QLabel("1. Top-3 Critical Threat Clues (Binary Max-Heap Extracted):", tab);
    topKTitle->setStyleSheet("font-weight: bold; color: #00e5ff; font-size: 14px;");
    layout->addWidget(topKTitle);

    topKTable = new QTableWidget(tab);
    topKTable->setColumnCount(4);
    topKTable->setHorizontalHeaderLabels({"Priority", "Category", "Threat Weight", "Reason"});
    topKTable->horizontalHeader()->setStretchLastSection(true);
    topKTable->setMaximumHeight(160);
    layout->addWidget(topKTable);

    QLabel* typoTitle = new QLabel("2. Dynamic Programming Typosquatting / Homograph Inspector:", tab);
    typoTitle->setStyleSheet("font-weight: bold; color: #00e5ff; font-size: 14px; margin-top: 15px;");
    layout->addWidget(typoTitle);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    candidateDomainInput = new QLineEdit(tab);
    candidateDomainInput->setPlaceholderText("e.g. easypa1sa or paypa1");
    checkTypoBtn = new QPushButton("Compute DP Edit Distance", tab);
    connect(checkTypoBtn, &QPushButton::clicked, this, &MainWindow::onCheckTyposquat);

    inputLayout->addWidget(candidateDomainInput);
    inputLayout->addWidget(checkTypoBtn);
    layout->addLayout(inputLayout);

    typoResultLabel = new QLabel("Enter candidate string above to calculate 2D DP distance against legitimate brand registry.", tab);
    typoResultLabel->setStyleSheet("padding: 10px; background: #263238; border-radius: 4px;");
    layout->addWidget(typoResultLabel);
    layout->addStretch();
}

void MainWindow::setupGraphTab(QWidget* tab) {
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QLabel* graphTitle = new QLabel("Threat Syndicate Network (Graph Adjacency List + BFS):", tab);
    graphTitle->setStyleSheet("font-weight: bold; color: #00e5ff; font-size: 14px;");
    layout->addWidget(graphTitle);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    bfsTargetInput = new QLineEdit(tab);
    bfsTargetInput->setText("+923001111111");
    runBfsBtn = new QPushButton("Run BFS Syndicate Trace", tab);
    connect(runBfsBtn, &QPushButton::clicked, this, &MainWindow::onRunBfsTrace);

    inputLayout->addWidget(new QLabel("Trace Entity:", tab));
    inputLayout->addWidget(bfsTargetInput);
    inputLayout->addWidget(runBfsBtn);
    layout->addLayout(inputLayout);

    graphResultsBrowser = new QTextBrowser(tab);
    layout->addWidget(graphResultsBrowser);
}

void MainWindow::setupAlgoLabTab(QWidget* tab) {
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QLabel* title = new QLabel("Algorithm Benchmarking Lab (Sorting & Searching Step Counters):", tab);
    title->setStyleSheet("font-weight: bold; color: #00e5ff; font-size: 14px;");
    layout->addWidget(title);

    QLabel* sortLabel = new QLabel("Evidence Severity Sorting Comparison (Live Benchmarks):", tab);
    layout->addWidget(sortLabel);

    sortBenchTable = new QTableWidget(tab);
    sortBenchTable->setColumnCount(4);
    sortBenchTable->setHorizontalHeaderLabels({"Algorithm", "Theoretical Big-O", "Actual Comparisons", "Data Swaps"});
    sortBenchTable->horizontalHeader()->setStretchLastSection(true);
    sortBenchTable->setMaximumHeight(150);
    layout->addWidget(sortBenchTable);

    QLabel* searchLabel = new QLabel("RuleBook Searching Benchmark (Binary vs Linear):", tab);
    layout->addWidget(searchLabel);

    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchKeywordInput = new QLineEdit(tab);
    searchKeywordInput->setText("otp");
    searchBenchBtn = new QPushButton("Benchmark Search Step Counts", tab);
    connect(searchBenchBtn, &QPushButton::clicked, [this]() {
        std::string kw = searchKeywordInput->text().toLower().toStdString();
        int bIdx = ruleBook.binarySearch(kw);
        int bSteps = ruleBook.getLastComparisons();
        int lIdx = ruleBook.linearSearch(kw);
        int lSteps = ruleBook.getLastComparisons();

        QString res = QString("Target '%1' -> Binary Search: Index %2 in %3 comparisons (O(log N)) | Linear Search: Index %4 in %5 comparisons (O(N))")
                      .arg(QString::fromStdString(kw)).arg(bIdx).arg(bSteps).arg(lIdx).arg(lSteps);
        searchResultLabel->setText(res);
    });

    searchLayout->addWidget(searchKeywordInput);
    searchLayout->addWidget(searchBenchBtn);
    layout->addLayout(searchLayout);

    searchResultLabel = new QLabel("Click benchmark to view step count difference.", tab);
    searchResultLabel->setStyleSheet("padding: 8px; background: #263238; border-radius: 4px; font-weight: bold;");
    layout->addWidget(searchResultLabel);
    layout->addStretch();
}

void MainWindow::setupHistoryTab(QWidget* tab) {
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QLabel* title = new QLabel("Audit Trail (Doubly Linked List Navigation) & Rolling Telemetry (Circular Buffer):", tab);
    title->setStyleSheet("font-weight: bold; color: #00e5ff; font-size: 14px;");
    layout->addWidget(title);

    QHBoxLayout* navLayout = new QHBoxLayout();
    backHistoryBtn = new QPushButton("< Previous Scan (DoublyList movePrev)", tab);
    forwardHistoryBtn = new QPushButton("Next Scan > (DoublyList moveNext)", tab);
    historyStatusLabel = new QLabel("No history yet.", tab);
    historyStatusLabel->setAlignment(Qt::AlignCenter);

    connect(backHistoryBtn, &QPushButton::clicked, this, &MainWindow::onHistoryBack);
    connect(forwardHistoryBtn, &QPushButton::clicked, this, &MainWindow::onHistoryForward);

    navLayout->addWidget(backHistoryBtn);
    navLayout->addWidget(historyStatusLabel, 1);
    navLayout->addWidget(forwardHistoryBtn);
    layout->addLayout(navLayout);

    QLabel* ringLabel = new QLabel("Recent Telemetry Buffer (Circular Ring Buffer - Capacity: 5):", tab);
    ringLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    layout->addWidget(ringLabel);

    circularBufferTable = new QTableWidget(tab);
    circularBufferTable->setColumnCount(4);
    circularBufferTable->setHorizontalHeaderLabels({"Slot", "Record ID", "Threat Score", "Preview"});
    circularBufferTable->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(circularBufferTable);
}

void MainWindow::onAnalyzeClicked() {
    std::string text = messageInput->toPlainText().toStdString();
    if (text.empty()) {
        QMessageBox::warning(this, "Empty Input", "Please enter or paste a message to analyze.");
        return;
    }

    lastVerdict = detective->analyze(text);
    isSortedBySeverity = false;

    // Update Verdict Banner
    if (lastVerdict.level == ThreatLevel::CRITICAL_SCAM) {
        verdictBanner->setText("VERDICT: CRITICAL SCAM DETECTED");
        verdictBanner->setStyleSheet("font-size: 18px; font-weight: bold; padding: 12px; background: #b71c1c; color: white; border-radius: 6px;");
    } else if (lastVerdict.level == ThreatLevel::SUSPICIOUS) {
        verdictBanner->setText("VERDICT: SUSPICIOUS ACTIVITY");
        verdictBanner->setStyleSheet("font-size: 18px; font-weight: bold; padding: 12px; background: #e65100; color: white; border-radius: 6px;");
    } else {
        verdictBanner->setText("VERDICT: SAFE VERIFIED");
        verdictBanner->setStyleSheet("font-size: 18px; font-weight: bold; padding: 12px; background: #1b5e20; color: white; border-radius: 6px;");
    }

    // Update Score Bar
    scoreBar->setValue(lastVerdict.cappedScore);
    if (lastVerdict.cappedScore >= 60) {
        scoreBar->setStyleSheet("QProgressBar::chunk { background-color: #ff1744; } font-weight: bold;");
    } else if (lastVerdict.cappedScore >= 30) {
        scoreBar->setStyleSheet("QProgressBar::chunk { background-color: #ff9100; } font-weight: bold;");
    } else {
        scoreBar->setStyleSheet("QProgressBar::chunk { background-color: #00e676; } font-weight: bold;");
    }

    // Update Summary
    QString summaryHtml = QString("<h3>%1</h3><p><b>Threat Score:</b> %2 / 100 (Raw: %3)</p>")
                          .arg(QString::fromStdString(lastVerdict.summary))
                          .arg(lastVerdict.cappedScore)
                          .arg(lastVerdict.rawScore);

    if (lastVerdict.comboBonus > 0) {
        summaryHtml += QString("<p style='color: #ff5252;'><b>Combo Bonus Applied:</b> +%1 points (Urgency + Financial/Credential Bait + Link Phishing Triad!)</p>").arg(lastVerdict.comboBonus);
    }
    summaryBrowser->setHtml(summaryHtml);

    // Populate Evidence Table
    evidenceTable->setRowCount((int)lastVerdict.evidenceList.size());
    for (size_t i = 0; i < lastVerdict.evidenceList.size(); i++) {
        const auto& ev = lastVerdict.evidenceList[i];
        evidenceTable->setItem((int)i, 0, new QTableWidgetItem(QString::number(i + 1)));
        evidenceTable->setItem((int)i, 1, new QTableWidgetItem(QString::fromStdString(categoryName(ev.category))));
        evidenceTable->setItem((int)i, 2, new QTableWidgetItem("+" + QString::number(ev.weight)));
        evidenceTable->setItem((int)i, 3, new QTableWidgetItem(QString::fromStdString(ev.found)));
        evidenceTable->setItem((int)i, 4, new QTableWidgetItem(QString::fromStdString(ev.reason)));
    }

    // Populate Top-K Heap
    MaxHeap<Evidence, EvidenceWeightComparator> heap;
    for (const auto& ev : lastVerdict.evidenceList) {
        heap.insert(ev);
    }

    int k = 3;
    int count = std::min(k, heap.size());
    topKTable->setRowCount(count);
    for (int i = 0; i < count; i++) {
        Evidence top = heap.extractMax();
        topKTable->setItem(i, 0, new QTableWidgetItem("Rank #" + QString::number(i + 1)));
        topKTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(categoryName(top.category))));
        topKTable->setItem(i, 2, new QTableWidgetItem("+" + QString::number(top.weight)));
        topKTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(top.reason)));
    }

    // Run Sorting Benchmark in Algo Lab
    if (!lastVerdict.evidenceList.empty()) {
        sortBenchTable->setRowCount(3);

        SortStats bStats, qStats, mStats;
        std::vector<Evidence> bCopy = lastVerdict.evidenceList;
        std::vector<Evidence> qCopy = lastVerdict.evidenceList;
        std::vector<Evidence> mCopy = lastVerdict.evidenceList;

        SortingSuite::bubbleSort(bCopy, bStats);
        SortingSuite::quickSort(qCopy, qStats);
        SortingSuite::mergeSort(mCopy, mStats);

        sortBenchTable->setItem(0, 0, new QTableWidgetItem("Bubble Sort"));
        sortBenchTable->setItem(0, 1, new QTableWidgetItem("O(N^2)"));
        sortBenchTable->setItem(0, 2, new QTableWidgetItem(QString::number(bStats.comparisons)));
        sortBenchTable->setItem(0, 3, new QTableWidgetItem(QString::number(bStats.swaps)));

        sortBenchTable->setItem(1, 0, new QTableWidgetItem("Quick Sort"));
        sortBenchTable->setItem(1, 1, new QTableWidgetItem("O(N log N) avg"));
        sortBenchTable->setItem(1, 2, new QTableWidgetItem(QString::number(qStats.comparisons)));
        sortBenchTable->setItem(1, 3, new QTableWidgetItem(QString::number(qStats.swaps)));

        sortBenchTable->setItem(2, 0, new QTableWidgetItem("Merge Sort"));
        sortBenchTable->setItem(2, 1, new QTableWidgetItem("O(N log N)"));
        sortBenchTable->setItem(2, 2, new QTableWidgetItem(QString::number(mStats.comparisons)));
        sortBenchTable->setItem(2, 3, new QTableWidgetItem(QString::number(mStats.swaps)));
    }

    // Record into DoublyList and CircularBuffer
    currentScanId++;
    GuiAuditRecord record;
    record.id = currentScanId;
    record.preview = text.substr(0, std::min<size_t>(35, text.length())) + "...";
    record.level = lastVerdict.level;
    record.score = lastVerdict.cappedScore;
    record.evidence = lastVerdict.evidenceList;
    record.summary = lastVerdict.summary;

    auditHistory.append(record);
    recentScans.push(record);

    historyStatusLabel->setText(QString("Viewing Record #%1 of %2").arg(record.id).arg(auditHistory.size()));

    // Update Circular Buffer Table
    auto ringItems = recentScans.toVector();
    circularBufferTable->setRowCount((int)ringItems.size());
    for (size_t i = 0; i < ringItems.size(); i++) {
        circularBufferTable->setItem((int)i, 0, new QTableWidgetItem(QString::number(i)));
        circularBufferTable->setItem((int)i, 1, new QTableWidgetItem("Record #" + QString::number(ringItems[i].id)));
        circularBufferTable->setItem((int)i, 2, new QTableWidgetItem(QString::number(ringItems[i].score) + "%"));
        circularBufferTable->setItem((int)i, 3, new QTableWidgetItem(QString::fromStdString(ringItems[i].preview)));
    }
}

void MainWindow::onSortSeverityClicked() {
    if (lastVerdict.evidenceList.empty()) return;

    SortStats stats;
    SortingSuite::mergeSort(lastVerdict.evidenceList, stats);
    isSortedBySeverity = true;

    evidenceTable->setRowCount((int)lastVerdict.evidenceList.size());
    for (size_t i = 0; i < lastVerdict.evidenceList.size(); i++) {
        const auto& ev = lastVerdict.evidenceList[i];
        evidenceTable->setItem((int)i, 0, new QTableWidgetItem("Rank #" + QString::number(i + 1)));
        evidenceTable->setItem((int)i, 1, new QTableWidgetItem(QString::fromStdString(categoryName(ev.category))));
        evidenceTable->setItem((int)i, 2, new QTableWidgetItem("+" + QString::number(ev.weight)));
        evidenceTable->setItem((int)i, 3, new QTableWidgetItem(QString::fromStdString(ev.found)));
        evidenceTable->setItem((int)i, 4, new QTableWidgetItem(QString::fromStdString(ev.reason)));
    }
}

void MainWindow::onLoadSamplePhishing() {
    messageInput->setText("URG3NT ALERT! Your Easypaisa wallet has been suspended. Cl1ck http://login.easypaisa.com.secure-update.xyz to verify your OTP immediately!!!!");
}

void MainWindow::onLoadSampleLottery() {
    messageInput->setText("CONGRATULATIONS WINN3R! You won cash prize of Rs. 100,000 from BISP. Send CNIC and PIN to 03112345678 to claim reward.");
}

void MainWindow::onLoadSampleSafe() {
    messageInput->setText("Assalam-o-Alaikum Ahmed! Are we still meeting tomorrow at 4 PM in the library for our DSA assignment?");
}

void MainWindow::onCheckTyposquat() {
    std::string candidate = candidateDomainInput->text().trimmed().toLower().toStdString();
    if (candidate.empty()) return;

    std::vector<std::string> brands = {"easypaisa", "jazzcash", "paypal", "hbl", "ubl", "bisp"};
    QString report = "<b>Dynamic Programming Matrix Results for: '" + QString::fromStdString(candidate) + "'</b><br>";

    bool foundTyposquat = false;
    for (const auto& b : brands) {
        int dist = Levenshtein::compute(candidate, b);
        bool typo = Levenshtein::isTyposquat(candidate, b, 2);
        if (typo) {
            foundTyposquat = true;
            report += QString("<span style='color: #ff1744; font-weight: bold;'>[!] TYPOSQUATTING ALERT:</span> Distance %1 from authentic brand '%2'<br>")
                      .arg(dist).arg(QString::fromStdString(b));
        } else {
            report += QString("<span style='color: #b0bec5;'>[√]</span> Distance %1 from '%2'<br>")
                      .arg(dist).arg(QString::fromStdString(b));
        }
    }

    typoResultLabel->setText(report);
}

void MainWindow::onRunBfsTrace() {
    std::string target = bfsTargetInput->text().trimmed().toStdString();
    if (target.empty()) return;

    std::vector<std::string> ring = threatGraph.bfsCluster(target);
    QString res = "<h3>Breadth-First Search (BFS) Syndicate Trace</h3>";
    res += QString("<p><b>Seed Node:</b> %1</p>").arg(QString::fromStdString(target));

    if (ring.empty()) {
        res += "<p>Entity not found in current threat graph.</p>";
    } else {
        res += QString("<p style='color: #ff5252;'><b>Discovered %1 Linked Threat Entities in Connected Crime Ring:</b></p><ol>").arg(ring.size());
        for (const auto& node : ring) {
            res += QString("<li><code>%1</code></li>").arg(QString::fromStdString(node));
        }
        res += "</ol>";
    }

    graphResultsBrowser->setHtml(res);
}

void MainWindow::onHistoryBack() {
    if (auditHistory.movePrevious()) {
        const auto& rec = auditHistory.getCurrent();
        historyStatusLabel->setText(QString("Viewing Record #%1 of %2: %3 (Score: %4%)")
                                   .arg(rec.id).arg(auditHistory.size()).arg(QString::fromStdString(rec.preview)).arg(rec.score));
    }
}

void MainWindow::onHistoryForward() {
    if (auditHistory.moveNext()) {
        const auto& rec = auditHistory.getCurrent();
        historyStatusLabel->setText(QString("Viewing Record #%1 of %2: %3 (Score: %4%)")
                                   .arg(rec.id).arg(auditHistory.size()).arg(QString::fromStdString(rec.preview)).arg(rec.score));
    }
}

void MainWindow::applyDarkForensicStyle() {
    QString qss = R"(
        QMainWindow {
            background-color: #12181f;
        }
        QWidget {
            background-color: #12181f;
            color: #eceff1;
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 13px;
        }
        QTabWidget::pane {
            border: 1px solid #263238;
            background-color: #18222c;
            border-radius: 4px;
        }
        QTabBar::tab {
            background: #1e2936;
            color: #90a4ae;
            padding: 10px 16px;
            margin-right: 2px;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
            font-weight: bold;
        }
        QTabBar::tab:selected {
            background: #00838f;
            color: #ffffff;
        }
        QTextEdit, QLineEdit, QTextBrowser, QTableWidget {
            background-color: #1a2531;
            border: 1px solid #37474f;
            border-radius: 4px;
            color: #cfd8dc;
            padding: 4px;
        }
        QPushButton {
            background-color: #00838f;
            color: #ffffff;
            border: none;
            padding: 8px 14px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #00acc1;
        }
        QPushButton:pressed {
            background-color: #006064;
        }
        QHeaderView::section {
            background-color: #263238;
            color: #80deea;
            padding: 6px;
            font-weight: bold;
            border: 1px solid #37474f;
        }
        QProgressBar {
            border: 1px solid #37474f;
            border-radius: 4px;
            text-align: center;
            background-color: #1a2531;
            color: #ffffff;
        }
    )";
    setStyleSheet(qss);
}
