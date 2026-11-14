import os
from pptx import Presentation
from pptx.util import Inches, Pt
from pptx.enum.text import PP_ALIGN
from pptx.dml.color import RGBColor
from pptx.enum.shapes import MSO_SHAPE

def create_deck():
    prs = Presentation()
    prs.slide_width = Inches(13.333)
    prs.slide_height = Inches(7.5)
    blank_layout = prs.slide_layouts[6]

    # Color Palette (Cyber Dark Theme)
    BG_COLOR = RGBColor(11, 19, 32)        # Deep Navy #0B1320
    CARD_BG = RGBColor(24, 38, 56)         # Slate Blue #182638
    CARD_BORDER = RGBColor(45, 68, 96)     # Muted Border
    ACCENT_CYAN = RGBColor(0, 210, 255)    # Neon Cyan #00D2FF
    ACCENT_GREEN = RGBColor(0, 230, 118)   # Emerald #00E676
    ACCENT_RED = RGBColor(255, 82, 82)     # Alert Red #FF5252
    TEXT_LIGHT = RGBColor(240, 244, 248)   # Off-white
    TEXT_MUTED = RGBColor(148, 163, 184)   # Slate gray
    ACCENT_GOLD = RGBColor(255, 193, 7)    # Gold

    def add_bg(slide):
        bg = slide.shapes.add_shape(MSO_SHAPE.RECTANGLE, 0, 0, Inches(13.333), Inches(7.5))
        bg.fill.solid()
        bg.fill.fore_color.rgb = BG_COLOR
        bg.line.fill.background()
        return bg

    def add_header(slide, title_text, category="CIPHERTRACE | 3RD SEMESTER DSA PROJECT"):
        cat_box = slide.shapes.add_textbox(Inches(0.8), Inches(0.4), Inches(11.7), Inches(0.4))
        tf_cat = cat_box.text_frame
        tf_cat.word_wrap = True
        p_cat = tf_cat.paragraphs[0]
        p_cat.text = category.upper()
        p_cat.font.size = Pt(11)
        p_cat.font.bold = True
        p_cat.font.color.rgb = ACCENT_CYAN

        title_box = slide.shapes.add_textbox(Inches(0.8), Inches(0.7), Inches(11.7), Inches(0.8))
        tf_title = title_box.text_frame
        tf_title.word_wrap = True
        p_title = tf_title.paragraphs[0]
        p_title.text = title_text
        p_title.font.size = Pt(24)
        p_title.font.bold = True
        p_title.font.color.rgb = TEXT_LIGHT

    def add_card(slide, left, top, width, height, title="", border_color=CARD_BORDER):
        card = slide.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, left, top, width, height)
        card.fill.solid()
        card.fill.fore_color.rgb = CARD_BG
        card.line.color.rgb = border_color
        card.line.width = Pt(1.5)
        
        if title:
            tb = slide.shapes.add_textbox(left + Inches(0.2), top + Inches(0.15), width - Inches(0.4), Inches(0.5))
            tf = tb.text_frame
            tf.word_wrap = True
            p = tf.paragraphs[0]
            p.text = title
            p.font.size = Pt(14)
            p.font.bold = True
            p.font.color.rgb = ACCENT_CYAN
        return card

    # =========================================================================
    # SLIDE 1: TITLE SLIDE
    # =========================================================================
    s1 = prs.slides.add_slide(blank_layout)
    add_bg(s1)

    # Accent badge
    badge = s1.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, Inches(1.0), Inches(1.5), Inches(4.5), Inches(0.45))
    badge.fill.solid()
    badge.fill.fore_color.rgb = CARD_BG
    badge.line.color.rgb = ACCENT_CYAN
    tf_b = badge.text_frame
    p_b = tf_b.paragraphs[0]
    p_b.text = "DATA STRUCTURES & ALGORITHMS • SEMESTER PROJECT"
    p_b.font.size = Pt(10)
    p_b.font.bold = True
    p_b.font.color.rgb = ACCENT_CYAN
    p_b.alignment = PP_ALIGN.CENTER

    tb_t = s1.shapes.add_textbox(Inches(1.0), Inches(2.2), Inches(11.0), Inches(1.8))
    p_t = tb_t.text_frame.paragraphs[0]
    p_t.text = "CipherTrace"
    p_t.font.size = Pt(54)
    p_t.font.bold = True
    p_t.font.color.rgb = TEXT_LIGHT

    tb_sub = s1.shapes.add_textbox(Inches(1.0), Inches(3.6), Inches(10.5), Inches(1.0))
    p_sub = tb_sub.text_frame.paragraphs[0]
    p_sub.text = "An Explainable Digital Forensics & Scam Detection Engine\nPowered by Custom Data Structures & Dynamic Programming"
    p_sub.font.size = Pt(20)
    p_sub.font.color.rgb = ACCENT_CYAN

    # Meta card
    meta = add_card(s1, Inches(1.0), Inches(5.0), Inches(11.3), Inches(1.5))
    tb_m = s1.shapes.add_textbox(Inches(1.2), Inches(5.15), Inches(11.0), Inches(1.2))
    tf_m = tb_m.text_frame
    p_m1 = tf_m.paragraphs[0]
    p_m1.text = "Evaluation Level: 3rd-Semester Academic Defense • Subject: Data Structures & Algorithms (CS-201)"
    p_m1.font.size = Pt(13)
    p_m1.font.bold = True
    p_m1.font.color.rgb = TEXT_LIGHT

    p_m2 = tf_m.add_paragraph()
    p_m2.text = "Implementation: 100% Custom Non-STL Templates (Stack, Queue, DoublyList, CircularBuffer, Heap, Graph) + Qt 6 GUI"
    p_m2.font.size = Pt(12)
    p_m2.font.color.rgb = TEXT_MUTED

    # Notes
    s1.notes_slide.notes_text_frame.text = (
        "Good morning respected professors and evaluators. Today we present CipherTrace: an explainable digital "
        "forensics engine engineered to deconstruct and score suspicious communications using custom-built data structures."
    )

    # =========================================================================
    # SLIDE 2: PROBLEM STATEMENT & MOTIVATION
    # =========================================================================
    s2 = prs.slides.add_slide(blank_layout)
    add_bg(s2)
    add_header(s2, "Problem Statement: The Explainability Crisis in Cybersecurity")

    c1 = add_card(s2, Inches(0.8), Inches(1.8), Inches(3.6), Inches(4.8), "1. The Smishing Epidemic")
    tb = s2.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(3.2), Inches(3.8))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Over 3.4 billion phishing & smishing messages transmitted globally each day."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Localized threats target millions via Easypaisa, JazzCash, BISP, and fake banking OTP suspension lures."
    p.font.size = Pt(13)
    p.font.color.rgb = TEXT_MUTED
    p2 = tf.add_paragraph()
    p2.text = "• Attackers exploit psychological urgency, financial lures, and evasive leetspeak substitutions."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_MUTED

    c2 = add_card(s2, Inches(4.8), Inches(1.8), Inches(3.6), Inches(4.8), "2. The 'Black-Box' Flaw", ACCENT_RED)
    tb = s2.shapes.add_textbox(Inches(5.0), Inches(2.5), Inches(3.2), Inches(3.8))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Modern AI / ML classifiers output opaque probabilities (e.g. '92% Scam') without justification."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• In digital forensics, law enforcement, and financial audits, unexplainable decisions are legally inadmissible."
    p.font.size = Pt(13)
    p.font.color.rgb = TEXT_MUTED
    p2 = tf.add_paragraph()
    p2.text = "• Black-box systems are easily deceived by zero-day evasion techniques and subdomain masking."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_MUTED

    c3 = add_card(s2, Inches(8.8), Inches(1.8), Inches(3.7), Inches(4.8), "3. The CipherTrace Thesis", ACCENT_GREEN)
    tb = s2.shapes.add_textbox(Inches(9.0), Inches(2.5), Inches(3.3), Inches(3.8))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Foundational Data Structures provide the ideal architecture for auditable, transparent security."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_LIGHT
    p = tf.add_paragraph()
    p.text = "• Every verdict is backed by an auditable, chronological docket of cryptographic & pattern evidence."
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "• Achieves deterministic microsecond execution without requiring heavy GPU or neural-net overhead."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    s2.notes_slide.notes_text_frame.text = (
        "Here we establish our core motivation: machine learning models cannot tell an investigator *why* a message "
        "was blocked. CipherTrace acts like a forensic detective, producing a court-admissible evidence case file."
    )

    # =========================================================================
    # SLIDE 3: 6-STAGE FORENSIC PIPELINE
    # =========================================================================
    s3 = prs.slides.add_slide(blank_layout)
    add_bg(s3)
    add_header(s3, "Architecture: The 6-Stage Forensic Pipeline")

    stages = [
        ("Stage 1: Normalizer", "Decodes evasive leetspeak (fr33 ➔ free) & compresses repetitive punctuation.", ACCENT_CYAN),
        ("Stage 2: Tokenizer", "Separates stream into typed tokens: Clean Words, URLs, & Contact Numbers.", ACCENT_CYAN),
        ("Stage 3: Detectors", "Polymorphic battery (RuleBook Binary Search, Domain Stack, Pattern Analysis).", ACCENT_CYAN),
        ("Stage 4: Evidence Stack", "Custom Stack<Evidence> stores all red flags in reverse chronological docket.", ACCENT_GOLD),
        ("Stage 5: Scorer & Heap", "Weighted scoring, +25 Phishing Triad Combo penalty, & Max-Heap Top-3 threats.", ACCENT_GREEN),
        ("Stage 6: Threat Graph", "Graph Adjacency List + BFS unmasks multi-message organized scam syndicates.", ACCENT_RED),
    ]

    for idx, (st_title, st_desc, color) in enumerate(stages):
        row = idx // 3
        col = idx % 3
        l = Inches(0.8 + col * 4.0)
        t = Inches(1.8 + row * 2.6)
        card = add_card(s3, l, t, Inches(3.7), Inches(2.2), st_title, color)
        tb = s3.shapes.add_textbox(l + Inches(0.2), t + Inches(0.7), Inches(3.3), Inches(1.3))
        tf = tb.text_frame
        tf.word_wrap = True
        tf.paragraphs[0].text = st_desc
        tf.paragraphs[0].font.size = Pt(12)
        tf.paragraphs[0].font.color.rgb = TEXT_MUTED

    s3.notes_slide.notes_text_frame.text = (
        "Notice the complete separation of concerns: each stage is an isolated class. The core engine knows "
        "nothing about Qt GUI, meaning it can be compiled into a headless server, embedded device, or desktop app."
    )

    # =========================================================================
    # SLIDE 4: THE MASTER DSA MATRIX
    # =========================================================================
    s4 = prs.slides.add_slide(blank_layout)
    add_bg(s4)
    add_header(s4, "The Master DSA Matrix: Where & Why Structures Are Used")

    rows = [
        ("Singly Linked List", "Stack & Queue Backbone", "Dynamic allocation, zero resizing overhead", "O(1) push/pop"),
        ("Stack (LIFO)", "Evidence Docket & Domain Parser", "Chronological report + Reverse domain label split", "O(1) / O(L)"),
        ("Queue (FIFO)", "Batch Ingestion & BFS Queue", "First-come fair triage + Graph Breadth-First Search", "O(1) enqueue"),
        ("Doubly Linked List", "Forensic Audit Trail", "Bidirectional O(1) Back/Next past scan navigation", "O(1) move"),
        ("Circular Ring Buffer", "Recent Scans Monitor", "Fixed memory telemetry; overwrites oldest entries", "O(1) push"),
        ("Binary Max-Heap", "Top-K Priority Threats", "Extracts 3 worst clues without full O(N log N) sort", "O(K log N)"),
        ("Dynamic Programming", "Levenshtein Typosquatting", "Catches homograph domain spoofing (paypa1.com)", "O(M * N)"),
        ("Graph (Adjacency List)", "Syndicate Network Analysis", "Vertices = Phones/URLs, Edges = Shared messages", "O(V + E)"),
        ("Sorting Suite", "Severity Sorter & Algo Lab", "MergeSort, QuickSort, BubbleSort comparisons", "O(N log N)"),
    ]

    table_shape = s4.shapes.add_table(len(rows) + 1, 4, Inches(0.8), Inches(1.7), Inches(11.7), Inches(5.1))
    table = table_shape.table
    table.columns[0].width = Inches(2.2)
    table.columns[1].width = Inches(2.7)
    table.columns[2].width = Inches(4.8)
    table.columns[3].width = Inches(2.0)

    headers = ["Data Structure", "Engine Component", "Engineering Justification", "Time Complexity"]
    for i, h in enumerate(headers):
        cell = table.cell(0, i)
        cell.fill.solid()
        cell.fill.fore_color.rgb = CARD_BG
        p = cell.text_frame.paragraphs[0]
        p.text = h
        p.font.bold = True
        p.font.size = Pt(12)
        p.font.color.rgb = ACCENT_CYAN

    for r_idx, r_data in enumerate(rows):
        for c_idx, val in enumerate(r_data):
            cell = table.cell(r_idx + 1, c_idx)
            cell.fill.solid()
            cell.fill.fore_color.rgb = RGBColor(18, 28, 42) if r_idx % 2 == 0 else RGBColor(14, 22, 34)
            p = cell.text_frame.paragraphs[0]
            p.text = val
            p.font.size = Pt(10.5)
            p.font.color.rgb = TEXT_LIGHT if c_idx == 0 else (ACCENT_GREEN if c_idx == 3 else TEXT_MUTED)

    s4.notes_slide.notes_text_frame.text = (
        "This is the most critical slide in our evaluation. It directly proves that zero structures were 'bolted on'. "
        "Every single structure fulfills an asymptotic requirement in the cybersecurity domain."
    )

    # =========================================================================
    # SLIDE 5: DEEP DIVE - STACK & DOMAIN PARSER
    # =========================================================================
    s5 = prs.slides.add_slide(blank_layout)
    add_bg(s5)
    add_header(s5, "Deep Dive: Custom Stack<T> & Reverse Domain Resolution")

    c1 = add_card(s5, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "Role 1: The Evidence Docket (LIFO)")
    tb = s5.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Detection modules execute in real-time and push findings onto Stack<Evidence>."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Popping items at analysis conclusion guarantees latest discovered anomalies appear first in the forensic docket."
    p.font.size = Pt(13)
    p.font.color.rgb = TEXT_MUTED
    p2 = tf.add_paragraph()
    p2.text = "• Guarantees O(1) push and pop operations with zero dynamic array reallocation penalties."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    c2 = add_card(s5, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "Role 2: Defeating Subdomain Spoofing", ACCENT_GOLD)
    tb = s5.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(5.3), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• The Attack: http://login.easypaisa.com.secure-update.xyz\n  Attackers place authentic brand names in subdomains to fool users."
    tf.paragraphs[0].font.size = Pt(12)
    tf.paragraphs[0].font.color.rgb = ACCENT_RED
    p = tf.add_paragraph()
    p.text = "\n• The Stack Solution:\n  1. Split host on dot ('.') into tokens: ['login', 'easypaisa', 'com', 'secure-update', 'xyz']\n  2. Push all labels onto Stack<string>.\n  3. Pop 1 ➔ TLD = 'xyz'\n  4. Pop 2 ➔ SLD = 'secure-update'\n  5. Registrable Domain = 'secure-update.xyz'"
    p.font.size = Pt(12)
    p.font.color.rgb = TEXT_LIGHT
    p2 = tf.add_paragraph()
    p2.text = "\n• Forensic Finding: Real domain is NOT easypaisa.com! Flagged as Critical Impersonation (+35 pts)."
    p2.font.size = Pt(12)
    p2.font.color.rgb = ACCENT_GREEN

    s5.notes_slide.notes_text_frame.text = (
        "Examiners love asking: 'Where did you use a stack besides undo/redo?'. Our second application is the "
        "reverse domain parser. The true domain of a URL is at the very end, so a Stack naturally reverses it in O(L) time."
    )

    # =========================================================================
    # SLIDE 6: DEEP DIVE - DYNAMIC PROGRAMMING
    # =========================================================================
    s6 = prs.slides.add_slide(blank_layout)
    add_bg(s6)
    add_header(s6, "Deep Dive: Dynamic Programming (Levenshtein Matrix)")

    c1 = add_card(s6, Inches(0.8), Inches(1.8), Inches(6.0), Inches(5.0), "The Typosquatting / Homograph Threat")
    tb = s6.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.6), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Attackers register look-alike domains to deceive visual inspection:"
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "   - paypa1.com vs paypal.com   (1 edit: '1' -> 'l')\n   - easypa1sa.pk vs easypaisa.pk (1 edit: '1' -> 'i')\n   - jazcash.com vs jazzcash.com  (1 edit: missing 'z')"
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "\n• Traditional dictionary lookups fail because the string does not match any exact blacklisted token."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_MUTED

    c2 = add_card(s6, Inches(7.2), Inches(1.8), Inches(5.3), Inches(5.0), "2D DP Recurrence Relation", ACCENT_GREEN)
    tb = s6.shapes.add_textbox(Inches(7.4), Inches(2.5), Inches(4.9), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Computes optimal edit distance in O(M × N) time & space:"
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_LIGHT
    p = tf.add_paragraph()
    p.text = "dp[i][j] = min(\n    dp[i-1][j] + 1,       // Deletion\n    dp[i][j-1] + 1,       // Insertion\n    dp[i-1][j-1] + cost   // Substitution\n)"
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_GOLD
    p2 = tf.add_paragraph()
    p2.text = "\n• If 0 < distance <= 2 from a recognized financial brand:\n  Triggers CRITICAL HOMOGRAPH ALERT (+30 pts)."
    p2.font.size = Pt(12)
    p2.font.color.rgb = ACCENT_RED

    s6.notes_slide.notes_text_frame.text = (
        "Here we show our Dynamic Programming implementation. In 3rd semester DSA, DP is a premier topic. "
        "We implemented the 2D Levenshtein table to detect homograph attacks mathematically."
    )

    # =========================================================================
    # SLIDE 7: DEEP DIVE - THREAT GRAPH & BFS
    # =========================================================================
    s7 = prs.slides.add_slide(blank_layout)
    add_bg(s7)
    add_header(s7, "Deep Dive: Threat Syndicate Graph & BFS Crime Ring Discovery")

    c1 = add_card(s7, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "Adjacency List Graph Formulation")
    tb = s7.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Real scammers distribute attacks across multiple burner numbers and redirect links."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Mathematical Graph Formulation G = (V, E):\n   - V (Vertices): Phone numbers, mule accounts, malicious URLs.\n   - E (Edges): Appeared together in the same suspicious payload."
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "• Stored as an Adjacency List using unordered hash maps for O(1) edge additions and compact O(V + E) space."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    c2 = add_card(s7, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "BFS Cluster Traversal", ACCENT_RED)
    tb = s7.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(5.3), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Breadth-First Search (BFS) Traversal:\n  Uses our custom Queue<string> from Phase 1 to traverse connected components in O(V + E) time."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_LIGHT
    p = tf.add_paragraph()
    p.text = "\n• Live Demonstration:\n  Seed: '+923001111111'\n  ➔ BFS Traversal Discovers:\n     • http://bit.ly/easypaisa-gift\n     • +923212222222\n     • easypa1sa-update.xyz\n     • +923334444444"
    p.font.size = Pt(12)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "\n• Result: Unmasks 5 distinct assets operated by Syndicate #1!"
    p2.font.size = Pt(12)
    p2.font.color.rgb = ACCENT_GREEN

    s7.notes_slide.notes_text_frame.text = (
        "Notice the reuse of our custom Queue in the BFS algorithm. When given one reported phone number, "
        "BFS crawls the adjacency list to unmask the entire syndicate operating in the shadows."
    )

    # =========================================================================
    # SLIDE 8: BINARY MAX-HEAP & ALGORITHM LAB
    # =========================================================================
    s8 = prs.slides.add_slide(blank_layout)
    add_bg(s8)
    add_header(s8, "Deep Dive: Binary Max-Heap & Algorithm Benchmarking Lab")

    c1 = add_card(s8, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "Binary Max-Heap: Top-K Clues")
    tb = s8.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Array-based complete binary tree where parent(i) >= children(i)."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Asymptotics vs Sorting:\n  - QuickSort sorts entire array: O(N log N)\n  - Max-Heap extracts K items: O(K log N)"
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "• When analyzing messages with dozens of flags, the executive dashboard extracts the Top-3 critical red flags instantaneously."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    c2 = add_card(s8, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "The Algorithm Lab: Live Benchmarks", ACCENT_GOLD)
    tb = s8.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(2.5), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Built directly into Tab 5 of the GUI to display real algorithmic metrics to evaluators:"
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Live Sorting Comparison:\n  - Bubble Sort: O(N^2) baseline\n  - Quick Sort: O(N log N) in-place\n  - Merge Sort: O(N log N) stable"
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_GOLD
    p2 = tf.add_paragraph()
    p2.text = "• Real step-counters track actual comparison and swap operations in real-time."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    s8.notes_slide.notes_text_frame.text = (
        "The Algorithm Lab is our showpiece for examiners. We can load an evidence docket and benchmark "
        "MergeSort against QuickSort and BubbleSort right before their eyes, showing real step counts."
    )

    # =========================================================================
    # SLIDE 9: DOUBLY LINKED LIST & CIRCULAR BUFFER
    # =========================================================================
    s9 = prs.slides.add_slide(blank_layout)
    add_bg(s9)
    add_header(s9, "Telemetry: Doubly Linked List & Circular Ring Buffer")

    c1 = add_card(s9, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "DoublyList<T>: Audit Trail Navigation")
    tb = s9.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Contains both next and prev pointers with an active cursor pointer."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Powers the '< Previous Scan' and 'Next Scan >' buttons in Tab 6."
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "• Provides O(1) bidirectional inspection of past investigation dossiers without search queries or array reallocation."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT

    c2 = add_card(s9, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "CircularBuffer<T>: Rolling Telemetry", ACCENT_GREEN)
    tb = s9.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(5.3), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Fixed-capacity memory buffer with head and tail index wrapping: tail = (tail + 1) % capacity"
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_LIGHT
    p = tf.add_paragraph()
    p.text = "\n• Purpose: Real-time Telemetry Monitor\n  Keeps exactly the last N (e.g. 5) processed scans in bounded memory."
    p.font.size = Pt(13)
    p.font.color.rgb = ACCENT_GREEN
    p2 = tf.add_paragraph()
    p2.text = "\n• Zero Memory Fragmentation: When capacity is reached, oldest scans are evicted automatically in O(1) time."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_MUTED

    s9.notes_slide.notes_text_frame.text = (
        "Here we show the telemetry structures. Doubly linked lists provide O(1) bidirectional cursor stepping, "
        "while circular ring buffers allow bounded, zero-leak rolling telemetry."
    )

    # =========================================================================
    # SLIDE 10: OOP & MEMORY SAFETY
    # =========================================================================
    s10 = prs.slides.add_slide(blank_layout)
    add_bg(s10)
    add_header(s10, "Software Engineering: Polymorphism & The Rule of Three")

    c1 = add_card(s10, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "Polymorphic Detector Battery")
    tb = s10.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Abstract Base Class Detector with pure virtual scan() method:"
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "   virtual void scan(const vector<Token>&,\n                     const string& raw,\n                     Stack<Evidence>&) = 0;"
    p.font.size = Pt(11.5)
    p.font.color.rgb = ACCENT_CYAN
    p2 = tf.add_paragraph()
    p2.text = "\n• Derived classes: KeywordDetector, UrlDetector, PatternDetector.\n• Satisfies Open/Closed Principle: Add new heuristic detectors without touching core engine."
    p2.font.size = Pt(12)
    p2.font.color.rgb = TEXT_LIGHT

    c2 = add_card(s10, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "Rule of Three & Pointer Safety", ACCENT_RED)
    tb = s10.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(5.3), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Manual Dynamic Memory Management:\n  Because structures manage raw heap pointers, default shallow copying causes double-free heap corruption."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "   Stack(const Stack&) = delete;\n   Stack& operator=(const Stack&) = delete;"
    p.font.size = Pt(12)
    p.font.color.rgb = ACCENT_GOLD
    p2 = tf.add_paragraph()
    p2.text = "\n• Rock-solid destructors traverse and delete all allocated nodes, ensuring ZERO memory leaks under Valgrind/ASan."
    p2.font.size = Pt(12)
    p2.font.color.rgb = ACCENT_GREEN

    s10.notes_slide.notes_text_frame.text = (
        "Memory safety is a major grading factor in C++. By deleting shallow copy constructors and implementing "
        "clean linked list destructors, we ensure rock-solid memory safety."
    )

    # =========================================================================
    # SLIDE 11: THE QT DESKTOP GUI
    # =========================================================================
    s11 = prs.slides.add_slide(blank_layout)
    add_bg(s11)
    add_header(s11, "Interactive Deployment: The Qt 6 Desktop GUI")

    tabs_info = [
        ("Tab 1: Investigate", "Live text triage, one-click presets, color-coded verdict banner, animated gauge."),
        ("Tab 2: Evidence Docket", "LIFO Stack view with a toggle to re-sort by severity via Custom Merge Sort."),
        ("Tab 3: Top-K & Homographs", "Max-Heap Top-3 threats + interactive 2D DP Levenshtein distance calculator."),
        ("Tab 4: Syndicate Graph", "Interactive BFS trace unmasking connected phone numbers and scam domains."),
        ("Tab 5: Algorithm Lab", "Live step-counter comparisons of Bubble Sort vs Quick Sort vs Merge Sort."),
        ("Tab 6: Audit & Telemetry", "Doubly Linked List Back/Next buttons + Circular Buffer recent scans."),
    ]

    for idx, (t_name, t_desc) in enumerate(tabs_info):
        r = idx // 2
        c = idx % 2
        l = Inches(0.8 + c * 5.9)
        t = Inches(1.8 + r * 1.7)
        card = add_card(s11, l, t, Inches(5.6), Inches(1.5), t_name)
        tb = s11.shapes.add_textbox(l + Inches(0.2), t + Inches(0.55), Inches(5.2), Inches(0.85))
        tf = tb.text_frame
        tf.word_wrap = True
        tf.paragraphs[0].text = t_desc
        tf.paragraphs[0].font.size = Pt(11.5)
        tf.paragraphs[0].font.color.rgb = TEXT_MUTED

    s11.notes_slide.notes_text_frame.text = (
        "Here we summarize the Qt 6 GUI. It's not just a wrapper — each tab corresponds to a specific data "
        "structure and algorithm, giving professors a live window into how the engine works."
    )

    # =========================================================================
    # SLIDE 12: VIVA DEFENSE & Q&A
    # =========================================================================
    s12 = prs.slides.add_slide(blank_layout)
    add_bg(s12)
    add_header(s12, "Viva Defense: Anticipated Evaluator Q&A")

    qa_list = [
        ("Q: Why not use STL std::stack and std::queue?",
         "A: STL containers abstract away node allocation. Custom templates demonstrate mastery of raw pointers, dynamic memory, and the Rule of Three from scratch."),
        ("Q: Why use a Stack for URLs instead of parsing left-to-right?",
         "A: Attackers front-load fake brand subdomains. The actual destination is always the final two labels. Pushing to a Stack and popping reverses labels in O(L) time."),
        ("Q: Why is Max-Heap superior to QuickSort for Top-K extraction?",
         "A: Sorting entire evidence takes O(N log N). A Max-Heap builds in O(N) and extracts K elements in O(K log N). When K << N, Heap is asymptotically faster."),
        ("Q: How does BFS unmask scam syndicates?",
         "A: Messages link phone numbers to URLs. BFS explores the Adjacency List to find connected components, proving distinct messages belong to one crime ring.")
    ]

    for idx, (q, a) in enumerate(qa_list):
        t = Inches(1.8 + idx * 1.3)
        card = add_card(s12, Inches(0.8), t, Inches(11.7), Inches(1.15))
        tb = s12.shapes.add_textbox(Inches(1.0), t + Inches(0.1), Inches(11.3), Inches(0.95))
        tf = tb.text_frame
        tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = q
        p1.font.bold = True
        p1.font.size = Pt(12)
        p1.font.color.rgb = ACCENT_GOLD
        p2 = tf.add_paragraph()
        p2.text = a
        p2.font.size = Pt(11)
        p2.font.color.rgb = TEXT_LIGHT

    s12.notes_slide.notes_text_frame.text = (
        "These four questions represent the exact topics examiners focus on. By addressing asymptotic advantages, "
        "pointer mechanics, and real-world domain requirements, our defense is mathematically bulletproof."
    )

    # =========================================================================
    # SLIDE 13: CONCLUSION & IMPACT
    # =========================================================================
    s13 = prs.slides.add_slide(blank_layout)
    add_bg(s13)
    add_header(s13, "Conclusion & Project Achievements")

    c1 = add_card(s13, Inches(0.8), Inches(1.8), Inches(5.6), Inches(5.0), "Key Achievements", ACCENT_GREEN)
    tb = s13.shapes.add_textbox(Inches(1.0), Inches(2.5), Inches(5.2), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "✔ 10 Core DSA Concepts implemented from scratch without STL crutches."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_LIGHT
    p = tf.add_paragraph()
    p.text = "✔ 100% Explainable Forensic Reports with Compound Threat Multiplier scoring."
    p.font.size = Pt(13)
    p.font.color.rgb = TEXT_LIGHT
    p2 = tf.add_paragraph()
    p2.text = "✔ Dual-mode interface: Standalone CLI Test Suite + Interactive Qt 6 GUI."
    p2.font.size = Pt(13)
    p2.font.color.rgb = TEXT_LIGHT
    p3 = tf.add_paragraph()
    p3.text = "✔ Sub-millisecond deterministic triage suitable for high-throughput gateway filtering."
    p3.font.size = Pt(13)
    p3.font.color.rgb = ACCENT_CYAN

    c2 = add_card(s13, Inches(6.8), Inches(1.8), Inches(5.7), Inches(5.0), "Future Scope & Extensions", ACCENT_CYAN)
    tb = s13.shapes.add_textbox(Inches(7.0), Inches(2.5), Inches(5.3), Inches(4.0))
    tf = tb.text_frame
    tf.word_wrap = True
    tf.paragraphs[0].text = "• Aho-Corasick Automaton: Upgrade Trie with failure transitions for single-pass multi-pattern matching."
    tf.paragraphs[0].font.size = Pt(13)
    tf.paragraphs[0].font.color.rgb = TEXT_MUTED
    p = tf.add_paragraph()
    p.text = "• Live GSM Modem Sniffer: Direct serial hook to SIM800L / Android ADB for real-time incoming SMS packet triage."
    p.font.size = Pt(13)
    p.font.color.rgb = TEXT_MUTED
    p2 = tf.add_paragraph()
    p2.text = "\nThank you!\nWe are now open for faculty evaluation and questions."
    p2.font.size = Pt(16)
    p2.font.bold = True
    p2.font.color.rgb = ACCENT_GOLD

    s13.notes_slide.notes_text_frame.text = (
        "Thank you for your time and evaluation. CipherTrace demonstrates that data structures are not just textbook "
        "theory, but the foundation of high-performance cyber intelligence. We welcome your questions."
    )

    output_path = os.path.abspath(r"c:\Users\LENOVO\OneDrive\Desktop\Data-Structure-and-Algorithm-\CCP\Cipher Trace\docs\CipherTrace_Presentation.pptx")
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    prs.save(output_path)
    print(f"Presentation saved successfully to: {output_path}")

if __name__ == "__main__":
    create_deck()
