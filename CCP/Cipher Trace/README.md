# CipherTrace — Digital Forensics & Scam Detection Engine

A comprehensive 3rd-Semester Data Structures and Algorithms project implementing custom data structures and an explainable forensic investigation pipeline to detect and analyze suspicious text messages (SMS, WhatsApp, Email, Phishing).

---

## 🛠️ Complete DSA Implementations Included

1. **Singly Linked Lists**: Custom `Stack<T>` and `Queue<T>` templates (Rule of Three, leak-free).
2. **Stack (LIFO)**:
   - Forensic Evidence Docket (chronological reversal).
   - Domain Reversal Stack (splits host by dots, pops TLD and SLD to defeat subdomain spoofing).
3. **Queue (FIFO)**: Ingestion queue and BFS queue.
4. **Doubly Linked List**: Bidirectional `movePrevious()` / `moveNext()` audit trail navigation.
5. **Circular Queue (Ring Buffer)**: Fixed-capacity telemetry buffer automatically overwriting oldest scans.
6. **Binary Max-Heap**: Top-$K$ priority threat extraction in $\mathcal{O}(K \log N)$.
7. **Graph & BFS**: Adjacency list Threat Syndicate Network discovering connected fraud rings.
8. **Dynamic Programming**: 2D Levenshtein distance matrix detecting typosquatting & homograph attacks.
9. **Sorting Suite**: Custom Merge Sort, Quick Sort, and Bubble Sort with live step counters.
10. **Searching**: Insertion Sort + Binary Search ($\mathcal{O}(\log N)$) vs Linear Search ($\mathcal{O}(N)$).
11. **Object-Oriented Design**: Clean polymorphic `Detector` hierarchy.

---

## 🚀 Running the Console Engine (No Qt Required)

You can compile and run the engine directly using MinGW/GCC in your terminal:

```powershell
cd CODE
g++ -std=c++17 main.cpp -o main.exe
.\main.exe
```

---

## 🖥️ Running the Qt GUI (Phase 7)

The Qt GUI provides an interactive dark-themed dashboard with 6 specialized tabs:
- **Tab 1: Investigate**: Real-time message triage, color-coded verdict banner, score gauge, and executive summary.
- **Tab 2: Evidence Docket**: LIFO Stack inspector with a button to rank by severity via Merge Sort.
- **Tab 3: Top-K & Homographs**: Max-Heap priority threats and live 2D DP Levenshtein distance calculator.
- **Tab 4: Syndicate Graph**: Interactive BFS trace unmasking connected phone numbers and scam domains.
- **Tab 5: Algorithm Lab**: Live step-counter comparisons of Bubble Sort vs Quick Sort vs Merge Sort.
- **Tab 6: Audit & Telemetry**: Doubly Linked List Back/Next buttons + Circular Buffer recent scans.

### How to Open & Run in Qt Creator:
1. Open **Qt Creator**.
2. Click **File -> Open File or Project...**
3. Select either:
   - `CipherTrace.pro` (qmake), or
   - `CMakeLists.txt` (CMake).
4. Select your Desktop Kit (MinGW or MSVC) and click **Configure Project**.
5. Click the green **Run (Play)** button or press `Ctrl + R`!
