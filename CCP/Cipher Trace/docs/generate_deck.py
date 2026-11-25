import os
from pptx import Presentation
from pptx.util import Inches, Pt
from pptx.enum.text import PP_ALIGN
from pptx.dml.color import RGBColor
from pptx.enum.shapes import MSO_SHAPE

def create_deck():
    prs = Presentation()
    prs.slide_width  = Inches(13.333)
    prs.slide_height = Inches(7.5)
    blank = prs.slide_layouts[6]

    # ── Colour Palette ──────────────────────────────────────────────────────
    BG       = RGBColor(11,  19,  32)
    CARD_BG  = RGBColor(24,  38,  56)
    CBORDER  = RGBColor(45,  68,  96)
    CYAN     = RGBColor(0,  210, 255)
    GREEN    = RGBColor(0,  230, 118)
    RED      = RGBColor(255, 82,  82)
    GOLD     = RGBColor(255, 193,  7)
    PURPLE   = RGBColor(179, 136, 255)
    WHITE    = RGBColor(240, 244, 248)
    MUTED    = RGBColor(148, 163, 184)
    DARKBLUE = RGBColor(0,   60,  80)

    # ── Helpers ─────────────────────────────────────────────────────────────
    def bg(slide):
        s = slide.shapes.add_shape(MSO_SHAPE.RECTANGLE, 0, 0,
                                   Inches(13.333), Inches(7.5))
        s.fill.solid(); s.fill.fore_color.rgb = BG
        s.line.fill.background()

    def header(slide, title, sub="CIPHERTRACE  |  CS-201  |  3RD SEMESTER DSA PROJECT"):
        t = slide.shapes.add_textbox(Inches(0.8), Inches(0.28), Inches(11.7), Inches(0.3))
        p = t.text_frame.paragraphs[0]
        p.text = sub; p.font.size = Pt(9); p.font.bold = True
        p.font.color.rgb = CYAN

        sep = slide.shapes.add_shape(MSO_SHAPE.RECTANGLE,
                                     Inches(0.8), Inches(0.62),
                                     Inches(11.7), Inches(0.03))
        sep.fill.solid(); sep.fill.fore_color.rgb = CYAN
        sep.line.fill.background()

        t2 = slide.shapes.add_textbox(Inches(0.8), Inches(0.68), Inches(11.7), Inches(0.75))
        p2 = t2.text_frame.paragraphs[0]
        p2.text = title; p2.font.size = Pt(24)
        p2.font.bold = True; p2.font.color.rgb = WHITE

    def card(slide, lx, ty, w, h, title="", bcol=None):
        bcol = bcol or CBORDER
        s = slide.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, lx, ty, w, h)
        s.fill.solid(); s.fill.fore_color.rgb = CARD_BG
        s.line.color.rgb = bcol; s.line.width = Pt(2)
        if title:
            tb = slide.shapes.add_textbox(lx+Inches(0.2), ty+Inches(0.12),
                                          w-Inches(0.4), Inches(0.4))
            p = tb.text_frame.paragraphs[0]
            p.text = title; p.font.size = Pt(13)
            p.font.bold = True; p.font.color.rgb = bcol
        return s

    def txt(slide, lx, ty, w, h, text, size=12, color=None, bold=False,
            wrap=True, align=PP_ALIGN.LEFT):
        color = color or MUTED
        tb = slide.shapes.add_textbox(lx, ty, w, h)
        tb.text_frame.word_wrap = wrap
        p = tb.text_frame.paragraphs[0]
        p.text = text; p.font.size = Pt(size)
        p.font.bold = bold; p.font.color.rgb = color
        p.alignment = align
        return tb

    def bullets(slide, lx, ty, w, items):
        """items = list of (text, color) tuples"""
        tb = slide.shapes.add_textbox(lx, ty, w, Inches(4.5))
        tb.text_frame.word_wrap = True
        for i, (t, c) in enumerate(items):
            p = tb.text_frame.paragraphs[0] if i == 0 else tb.text_frame.add_paragraph()
            p.text = t; p.font.size = Pt(12)
            p.font.color.rgb = c; p.space_after = Pt(5)

    def flow_box(slide, lx, ty, w, h, line1, line2="", bcol=CYAN, fill=None):
        fill = fill or CARD_BG
        s = slide.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, lx, ty, w, h)
        s.fill.solid(); s.fill.fore_color.rgb = fill
        s.line.color.rgb = bcol; s.line.width = Pt(2)
        tb = slide.shapes.add_textbox(lx+Inches(0.1), ty+Inches(0.05),
                                       w-Inches(0.2), h-Inches(0.1))
        tb.text_frame.word_wrap = True
        p1 = tb.text_frame.paragraphs[0]
        p1.text = line1; p1.font.size = Pt(11)
        p1.font.bold = True; p1.font.color.rgb = bcol
        p1.alignment = PP_ALIGN.CENTER
        if line2:
            p2 = tb.text_frame.add_paragraph()
            p2.text = line2; p2.font.size = Pt(9)
            p2.font.color.rgb = MUTED; p2.alignment = PP_ALIGN.CENTER

    def arrow_down(slide, cx, ty, h):
        # stem
        s = slide.shapes.add_shape(MSO_SHAPE.RECTANGLE,
                                   cx-Inches(0.04), ty, Inches(0.08), h-Inches(0.14))
        s.fill.solid(); s.fill.fore_color.rgb = CYAN; s.line.fill.background()
        # arrowhead triangle
        t = slide.shapes.add_shape(MSO_SHAPE.ISOSCELES_TRIANGLE,
                                   cx-Inches(0.12), ty+h-Inches(0.17),
                                   Inches(0.24), Inches(0.17))
        t.fill.solid(); t.fill.fore_color.rgb = CYAN; t.line.fill.background()

    # =========================================================================
    # SLIDE 1 — TITLE + TEAM
    # =========================================================================
    s1 = prs.slides.add_slide(blank); bg(s1)

    # Top badge
    b = s1.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE,
                            Inches(0.8), Inches(0.3), Inches(6.5), Inches(0.4))
    b.fill.solid(); b.fill.fore_color.rgb = DARKBLUE
    b.line.color.rgb = CYAN; b.line.width = Pt(1)
    p = b.text_frame.paragraphs[0]
    p.text = "DATA STRUCTURES & ALGORITHMS  •  CS-201  •  3RD SEMESTER"
    p.font.size = Pt(9); p.font.bold = True
    p.font.color.rgb = CYAN; p.alignment = PP_ALIGN.CENTER

    txt(s1, Inches(0.8), Inches(1.0), Inches(12.0), Inches(1.5),
        "CipherTrace", size=58, color=WHITE, bold=True)

    line = s1.shapes.add_shape(MSO_SHAPE.RECTANGLE,
                               Inches(0.8), Inches(2.3), Inches(5.5), Inches(0.055))
    line.fill.solid(); line.fill.fore_color.rgb = CYAN; line.line.fill.background()

    txt(s1, Inches(0.8), Inches(2.4), Inches(11.5), Inches(0.55),
        "An Explainable Digital Forensics & Scam Detection Engine",
        size=20, color=CYAN)

    txt(s1, Inches(0.8), Inches(3.05), Inches(8.8), Inches(1.3),
        "CipherTrace is a Pakistan-focused cybersecurity engine built in C++17 with a "
        "Qt 6 GUI. It analyzes suspicious SMS, WhatsApp, and email messages using "
        "10 custom Data Structures & Algorithms — producing a fully explainable "
        "forensic verdict with zero cloud dependency and 100% offline privacy.",
        size=13, color=MUTED, wrap=True)

    # Team label
    txt(s1, Inches(0.8), Inches(4.45), Inches(4.0), Inches(0.35),
        "PROJECT TEAM", size=11, color=GOLD, bold=True)

    members = [
        ("Memoona Mehboob", "CT-166", CYAN),
        ("Marium Faheem",   "CT-168", GREEN),
        ("Maryum Mairaj",   "CT-170", GOLD),
    ]
    for i, (name, roll, col) in enumerate(members):
        mx = Inches(0.8 + i * 4.1)
        my = Inches(4.85)
        c = s1.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, mx, my,
                                Inches(3.8), Inches(1.45))
        c.fill.solid(); c.fill.fore_color.rgb = CARD_BG
        c.line.color.rgb = col; c.line.width = Pt(2.5)
        tb = s1.shapes.add_textbox(mx+Inches(0.22), my+Inches(0.18),
                                   Inches(3.4), Inches(1.1))
        tf = tb.text_frame
        p1 = tf.paragraphs[0]
        p1.text = name; p1.font.size = Pt(15)
        p1.font.bold = True; p1.font.color.rgb = col
        p2 = tf.add_paragraph()
        p2.text = roll; p2.font.size = Pt(13); p2.font.color.rgb = MUTED

    s1.notes_slide.notes_text_frame.text = (
        "Good morning respected professors. We are presenting CipherTrace. "
        "Team: Memoona CT-166, Marium Faheem CT-168, Maryum Mairaj CT-170."
    )

    # =========================================================================
    # SLIDE 2 — SYSTEM FLOWCHART
    # =========================================================================
    s2 = prs.slides.add_slide(blank); bg(s2)
    header(s2, "Complete System Architecture — Data Flow & Header Files")

    # ── LEFT: Main processing pipeline ──
    PW   = Inches(5.6)   # pipeline box width
    PH   = Inches(0.57)  # pipeline box height
    PCX  = Inches(3.85)  # center x
    PL   = PCX - PW/2    # left edge

    BOX_Y = [1.60, 2.37, 3.14, 4.03, 4.95, 5.72]  # inch y-positions

    flow_box(s2, PL, Inches(BOX_Y[0]), PW, PH,
             "📩  INPUT MESSAGE",
             "Raw SMS / WhatsApp / Email / URL",
             GOLD, RGBColor(40, 28, 8))
    arrow_down(s2, PCX, Inches(BOX_Y[0]+0.57), Inches(0.24))

    flow_box(s2, PL, Inches(BOX_Y[1]), PW, PH,
             "Normalizer.h  —  Leetspeak Decoder",
             "3→e  0→o  1→i  @→a  |  Protects phone numbers & URLs from decoding",
             CYAN)
    arrow_down(s2, PCX, Inches(BOX_Y[1]+0.57), Inches(0.21))

    flow_box(s2, PL, Inches(BOX_Y[2]), PW, PH,
             "Tokenizer.h  —  Typed Token Extraction",
             "Splits message →  WORD tokens  |  URL tokens  |  PHONE tokens",
             CYAN)
    arrow_down(s2, PCX, Inches(BOX_Y[2]+0.57), Inches(0.3))

    # 3 detector boxes side by side
    DW = Inches(1.73); DH = Inches(0.76); DY = Inches(BOX_Y[3])
    dets = [
        ("KeywordDetector.h", "Binary Search\non RuleBook.h", GREEN),
        ("UrlDetector.h",     "Stack.h Domain\n+ Levenshtein.h DP", RED),
        ("PatternDetector.h", "CAPS Ratio\nPhone Lure\n!!! Spam", PURPLE),
    ]
    for i, (dn, ds, dc) in enumerate(dets):
        flow_box(s2, PL + i*(DW+Inches(0.07)), DY, DW, DH, dn, ds, dc)
    arrow_down(s2, PCX, Inches(BOX_Y[3]+0.76), Inches(0.16))

    flow_box(s2, PL, Inches(BOX_Y[4]), PW, PH,
             "Scorer.h  —  Weighted Evidence Scoring",
             "Weight sum  +  Phishing Triad Combo Penalty +25 pts  →  Verdict thresholds",
             GREEN)
    arrow_down(s2, PCX, Inches(BOX_Y[4]+0.57), Inches(0.20))

    flow_box(s2, PL, Inches(BOX_Y[5]), PW, PH,
             "🎯  FINAL VERDICT  &  FORENSIC REPORT",
             "CRITICAL SCAM (≥80)  |  SUSPICIOUS (≥60)  |  SAFE VERIFIED (<40)",
             GOLD, RGBColor(40, 28, 8))

    # ── RIGHT: Supporting DSA modules ──
    RX = Inches(7.75); RW = Inches(5.25)
    txt(s2, RX, Inches(1.52), RW, Inches(0.35),
        "SUPPORTING DATA STRUCTURES", size=11, color=GOLD, bold=True)

    right = [
        ("MaxHeap.h",               "Top-K Priority Evidence Extraction  |  O(K log N)",         CYAN),
        ("ThreatGraph.h + Queue.h", "Adjacency List Graph + BFS Syndicate Cluster  |  O(V+E)",   RED),
        ("Sorting.h",               "MergeSort / QuickSort / BubbleSort  |  Algorithm Lab",       GREEN),
        ("DoublyList.h",            "Bidirectional Audit Trail  |  O(1) Back/Next navigation",    PURPLE),
        ("CircularBuffer.h",        "Rolling Ring Buffer — last 5 scans  |  O(1) push/overwrite", GOLD),
        ("RuleBook.h + Rule.h",     "Insertion Sort at load + Binary Search at scan  |  O(log N)",CYAN),
    ]
    for i, (rn, rd, rc) in enumerate(right):
        ry = Inches(1.92 + i * 0.87)
        s = s2.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE, RX, ry, RW, Inches(0.74))
        s.fill.solid(); s.fill.fore_color.rgb = CARD_BG
        s.line.color.rgb = rc; s.line.width = Pt(1.5)
        tb = s2.shapes.add_textbox(RX+Inches(0.15), ry+Inches(0.07),
                                   RW-Inches(0.3), Inches(0.63))
        tf = tb.text_frame; tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = rn; p1.font.size = Pt(12)
        p1.font.bold = True; p1.font.color.rgb = rc
        p2 = tf.add_paragraph()
        p2.text = rd; p2.font.size = Pt(10); p2.font.color.rgb = MUTED

    s2.notes_slide.notes_text_frame.text = (
        "This flowchart shows the complete data flow. Left = main scan pipeline. "
        "Right = supporting DSA modules used throughout the system. "
        "Every box maps to a specific header file."
    )

    # =========================================================================
    # SLIDE 3 — PROBLEM STATEMENT
    # =========================================================================
    s3 = prs.slides.add_slide(blank); bg(s3)
    header(s3, "Problem Statement: Why CipherTrace Was Needed")

    cols3 = [
        ("1. The Smishing Epidemic",
         [("• 3.4 billion phishing messages sent globally every day.", MUTED),
          ("• Pakistani users targeted via Easypaisa, JazzCash & BISP lottery scams.", MUTED),
          ("• Attackers use leet-speak (3asypais4) to bypass basic keyword filters.", MUTED),
          ("• Existing tools: English-only, cloud-dependent, unexplainable.", RED)],
         Inches(0.8), CBORDER),
        ("2. The Black-Box AI Flaw",
         [("• ML classifiers output '92% Scam' — zero forensic justification.", MUTED),
          ("• In law enforcement, unexplained AI decisions are legally inadmissible.", MUTED),
          ("• Zero-day evasion defeats models not updated in real-time.", MUTED),
          ("• Privacy risk: sensitive messages sent to remote AI servers.", RED)],
         Inches(4.75), RED),
        ("3. CipherTrace Thesis",
         [("• Every verdict backed by an auditable evidence docket.", WHITE),
          ("• 100% offline — no cloud, no AI, no data leaving the device.", GREEN),
          ("• Pure C++ DSA logic: deterministic microsecond execution.", WHITE),
          ("• Pakistan-specific: Easypaisa, JazzCash, BISP brands built-in.", GREEN)],
         Inches(8.70), GREEN),
    ]
    for title, pts, lx, bc in cols3:
        card(s3, lx, Inches(1.78), Inches(3.65), Inches(5.1), title, bc)
        tb = s3.shapes.add_textbox(lx+Inches(0.2), Inches(2.45),
                                   Inches(3.3), Inches(4.2))
        tf = tb.text_frame; tf.word_wrap = True
        for i, (t, c) in enumerate(pts):
            p = tf.paragraphs[0] if i == 0 else tf.add_paragraph()
            p.text = t; p.font.size = Pt(12.5)
            p.font.color.rgb = c; p.space_after = Pt(6)

    # =========================================================================
    # SLIDE 4 — 6-STAGE PIPELINE + HEADER FILES
    # =========================================================================
    s4 = prs.slides.add_slide(blank); bg(s4)
    header(s4, "Architecture: 6-Stage Forensic Pipeline & Exact Header Files")

    stages = [
        ("Stage 1", "Normalizer.h",       "Leetspeak decode (3→e, 0→o)\nURL & phone number guard\nPunctuation compression",         CYAN),
        ("Stage 2", "Tokenizer.h",        "WORD token extraction\nURL token extraction\nPHONE_NUMBER token extraction",              CYAN),
        ("Stage 3", "KeywordDetector.h",  "Binary Search on RuleBook.h\n20 keywords, O(log N) lookup\nCategory + weight per match",   GREEN),
        ("Stage 4", "UrlDetector.h",      "Stack.h domain reversal\nLevenshtein.h typosquat DP\nHigh-risk TLD detection (.xyz .top)", RED),
        ("Stage 5", "PatternDetector.h",  "ALL-CAPS ratio check\nExclamation spam detector\nPhone-number lure pattern",              PURPLE),
        ("Stage 6", "Scorer.h",           "Weighted score aggregation\nPhishing Triad Combo +25 pts\nVerdict: SCAM / SUSPICIOUS / SAFE", GOLD),
    ]
    for idx, (stage, hfile, desc, col) in enumerate(stages):
        r = idx // 3; c = idx % 3
        lx = Inches(0.8 + c * 4.0); ty = Inches(1.72 + r * 2.72)

        bx = s4.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE,
                                  lx, ty, Inches(3.75), Inches(2.52))
        bx.fill.solid(); bx.fill.fore_color.rgb = CARD_BG
        bx.line.color.rgb = col; bx.line.width = Pt(2)

        # Stage badge
        badge = s4.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE,
                                    lx+Inches(0.18), ty+Inches(0.14),
                                    Inches(0.9), Inches(0.3))
        badge.fill.solid(); badge.fill.fore_color.rgb = col
        badge.line.fill.background()
        p = badge.text_frame.paragraphs[0]
        p.text = stage; p.font.size = Pt(9)
        p.font.bold = True; p.font.color.rgb = BG
        p.alignment = PP_ALIGN.CENTER

        # Header filename
        tb_h = s4.shapes.add_textbox(lx+Inches(1.18), ty+Inches(0.1),
                                     Inches(2.4), Inches(0.42))
        p_h = tb_h.text_frame.paragraphs[0]
        p_h.text = hfile; p_h.font.size = Pt(13)
        p_h.font.bold = True; p_h.font.color.rgb = col

        # Description
        tb_d = s4.shapes.add_textbox(lx+Inches(0.2), ty+Inches(0.58),
                                     Inches(3.35), Inches(1.8))
        tf_d = tb_d.text_frame; tf_d.word_wrap = True
        p_d = tf_d.paragraphs[0]
        p_d.text = desc; p_d.font.size = Pt(12); p_d.font.color.rgb = MUTED

    # =========================================================================
    # SLIDE 5 — MASTER DSA MATRIX
    # =========================================================================
    s5 = prs.slides.add_slide(blank); bg(s5)
    header(s5, "Master DSA Matrix — Header File → Role → Complexity")

    rows5 = [
        ("Stack.h",          "Evidence Docket & URL Reversal",   "LIFO linked list — O(1) push/pop, reverses URL domain labels",   "O(1) / O(L)"),
        ("Queue.h",          "BFS in ThreatGraph.h",             "FIFO linked list — powers Breadth-First Search traversal",       "O(1) enq/deq"),
        ("DoublyList.h",     "Forensic Audit Trail",             "Bidirectional prev/next cursor — O(1) Back/Next navigation",    "O(1) move"),
        ("CircularBuffer.h", "Rolling Telemetry Monitor",        "Modulo-wrap ring buffer — bounded O(1) push, no realloc",       "O(1) push"),
        ("MaxHeap.h",        "Top-K Priority Evidence",          "Array binary heap heapifyUp/Down — K extractions in O(K log N)","O(K log N)"),
        ("ThreatGraph.h",    "Scam Syndicate Network",           "Adjacency list Graph + BFS connected components",               "O(V + E)"),
        ("Levenshtein.h",    "Typosquatting DP",                 "2D DP matrix — catches paypa1.com vs paypal.com (dist=1)",      "O(M × N)"),
        ("Sorting.h",        "Severity Sorter & Algo Lab",       "MergeSort stable + QuickSort in-place + BubbleSort baseline",   "O(N log N)"),
        ("RuleBook.h",       "Keyword Database",                 "Insertion Sort at load, Binary Search at scan — O(log N)",      "O(log N)"),
    ]
    tbl = s5.shapes.add_table(len(rows5)+1, 4,
                               Inches(0.8), Inches(1.60),
                               Inches(11.7), Inches(5.6))
    t = tbl.table
    t.columns[0].width = Inches(2.1)
    t.columns[1].width = Inches(2.7)
    t.columns[2].width = Inches(4.75)
    t.columns[3].width = Inches(2.15)

    for i, h in enumerate(["Header File", "Engine Role", "DSA Justification", "Complexity"]):
        cell = t.cell(0, i)
        cell.fill.solid(); cell.fill.fore_color.rgb = DARKBLUE
        p = cell.text_frame.paragraphs[0]
        p.text = h; p.font.bold = True
        p.font.size = Pt(12); p.font.color.rgb = CYAN

    for ri, row in enumerate(rows5):
        for ci, val in enumerate(row):
            cell = t.cell(ri+1, ci)
            cell.fill.solid()
            cell.fill.fore_color.rgb = (RGBColor(18,28,42)
                                        if ri % 2 == 0 else RGBColor(14,22,34))
            p = cell.text_frame.paragraphs[0]
            p.text = val; p.font.size = Pt(10.5)
            if ci == 0:
                p.font.bold = True; p.font.color.rgb = CYAN
            elif ci == 3:
                p.font.color.rgb = GREEN
            else:
                p.font.color.rgb = MUTED

    # =========================================================================
    # SLIDE 6 — STACK.H DEEP DIVE
    # =========================================================================
    s6 = prs.slides.add_slide(blank); bg(s6)
    header(s6, "Deep Dive: Stack.h — Evidence LIFO Docket & URL Domain Reversal")

    card(s6, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "Stack.h — Role 1: Evidence LIFO Docket")
    bullets(s6, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("• Template class: Node* head, int count", MUTED),
        ("• push() — adds Evidence node at top — O(1)", MUTED),
        ("• pop()  — removes from top (latest first) — O(1)", MUTED),
        ("• Rule of Three: copy ctor = delete; op= = delete", GOLD),
        ("  Prevents double-free heap corruption", GOLD),
        ("• Destructor traverses full chain → deletes every node", GREEN),
        ("• Zero memory leaks — Valgrind/ASan verified clean", GREEN),
    ])

    card(s6, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Stack.h — Role 2: URL Domain Reversal", GOLD)
    bullets(s6, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("Attack URL: login.easypaisa.com.secure-update.xyz", RED),
        ("1. Split on '.'  → push all labels to Stack<string>", MUTED),
        ("2. Pop 1  →  TLD  =  'xyz'", CYAN),
        ("3. Pop 2  →  SLD  =  'secure-update'  ← REAL domain!", CYAN),
        ("4. Registrable domain = secure-update.xyz", GREEN),
        ("5. NOT easypaisa.com!  → Impersonation Flag +35 pts", RED),
        ("   This is impossible with left-to-right parsing alone.", MUTED),
    ])

    # =========================================================================
    # SLIDE 7 — LEVENSHTEIN.H DEEP DIVE
    # =========================================================================
    s7 = prs.slides.add_slide(blank); bg(s7)
    header(s7, "Deep Dive: Levenshtein.h — Dynamic Programming Typosquatting")

    card(s7, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "Levenshtein.h — The Threat: Homograph Domains")
    bullets(s7, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("Attackers register look-alike domains:", MUTED),
        ("  paypa1.com    vs paypal.com    →  distance = 1", RED),
        ("  easypa1sa.pk  vs easypaisa.pk  →  distance = 1", RED),
        ("  jazcash.com   vs jazzcash.com  →  distance = 1", RED),
        ("Exact match FAILS: 'paypa1' ≠ 'paypal' in string compare", GOLD),
        ("Levenshtein DP catches it in O(M × N) time", GREEN),
        ("Checks: easypaisa, jazzcash, paypal, hbl, ubl, bisp", CYAN),
    ])

    card(s7, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Levenshtein.h — 2D DP Recurrence Formula", GREEN)
    bullets(s7, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("dp[0][j] = j   dp[i][0] = i   (base cases)", MUTED),
        ("", MUTED),
        ("if s1[i-1] == s2[j-1]:  dp[i][j] = dp[i-1][j-1]", GOLD),
        ("else: dp[i][j] = 1 + min(", GOLD),
        ("    dp[i-1][j],      // Delete", CYAN),
        ("    dp[i][j-1],      // Insert", CYAN),
        ("    dp[i-1][j-1]     // Replace", CYAN),
        (") → isTyposquat() if dist ≤ 2  →  ALERT +30 pts", RED),
    ])

    # =========================================================================
    # SLIDE 8 — THREATGRAPH.H + QUEUE.H
    # =========================================================================
    s8 = prs.slides.add_slide(blank); bg(s8)
    header(s8, "Deep Dive: ThreatGraph.h + Queue.h — BFS Syndicate Discovery")

    card(s8, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "ThreatGraph.h — Graph Structure (Adjacency List)")
    bullets(s8, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("unordered_map<string, vector<string>> adjList", CYAN),
        ("addEntity(url) — adds node if not present", MUTED),
        ("addLink(A, B) — undirected edge (appeared together)", MUTED),
        ("bfsCluster(start) — BFS using Queue<string>  O(V+E)", GREEN),
        ("findAllSyndicates() — all connected components", GREEN),
        ("Pre-loaded: 2 syndicates ready for live demo!", GOLD),
        ("vertexCount() — returns total nodes in graph", MUTED),
    ])

    card(s8, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Queue.h Powers BFS — FIFO Level-by-Level Traversal", RED)
    bullets(s8, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("Seed: '+923001111111'  →  enqueue", CYAN),
        ("dequeue → visit node → enqueue all unvisited neighbors", MUTED),
        ("Queue guarantees LEVEL-BY-LEVEL (BFS) traversal", MUTED),
        ("Syndicate #1 discovered (5 nodes):", GREEN),
        ("  • http://bit.ly/easypaisa-gift", CYAN),
        ("  • +923212222222 → easypa1sa-update.xyz", CYAN),
        ("  • +923334444444", CYAN),
        ("Syndicate #2: +923459999999 → bisp-claim.top", RED),
    ])

    # =========================================================================
    # SLIDE 9 — MAXHEAP.H + SORTING.H
    # =========================================================================
    s9 = prs.slides.add_slide(blank); bg(s9)
    header(s9, "Deep Dive: MaxHeap.h — Top-K Extraction & Sorting.h Lab")

    card(s9, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "MaxHeap.h — Binary Max-Heap Priority Queue")
    bullets(s9, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("Array-based complete binary tree", MUTED),
        ("parent(i)=(i-1)/2  |  children: 2i+1, 2i+2", CYAN),
        ("insert() → heapifyUp()   — O(log N)", MUTED),
        ("extractMax() → heapifyDown() — O(log N)", MUTED),
        ("EvidenceWeightComparator → sorts by threat weight", GOLD),
        ("Top-3 extraction: O(K log N)  vs  Full sort: O(N log N)", GREEN),
        ("When K=3 and N=20 flags → Heap is 6× faster!", GREEN),
    ])

    card(s9, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Sorting.h — 3 Algorithms with Live SortStats", GOLD)
    bullets(s9, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("All 3 algorithms in Sorting.h with SortStats struct:", MUTED),
        ("BubbleSort  — O(N²)       — worst-case baseline", RED),
        ("QuickSort   — O(N log N) avg, O(N²) worst — in-place", GOLD),
        ("MergeSort   — O(N log N) guaranteed — stable", GREEN),
        ("SortStats tracks: comparisons + swaps in real-time", MUTED),
        ("Tab 5 shows actual live step counts to evaluators", CYAN),
        ("RuleBook.h: Binary Search (O log N) vs Linear (O N)", CYAN),
    ])

    # =========================================================================
    # SLIDE 10 — DOUBLYLIST.H + CIRCULARBUFFER.H
    # =========================================================================
    s10 = prs.slides.add_slide(blank); bg(s10)
    header(s10, "Telemetry: DoublyList.h — Audit Trail & CircularBuffer.h — Ring Buffer")

    card(s10, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "DoublyList.h — Bidirectional Audit Trail")
    bullets(s10, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("Node: T data  +  Node* prev  +  Node* next", CYAN),
        ("append() — adds new scan record at tail", MUTED),
        ("movePrevious() — cursor ← prev node  — O(1)", GREEN),
        ("moveNext()     — cursor → next node  — O(1)", GREEN),
        ("getCurrent()   — returns active scan dossier", MUTED),
        ("Powers '< Previous Scan' & 'Next Scan >' in Tab 6", GOLD),
        ("Full forensic case file — no scan ever deleted", MUTED),
    ])

    card(s10, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "CircularBuffer.h — Rolling Ring Buffer", GREEN)
    bullets(s10, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("Fixed-size array of capacity N (default = 5)", MUTED),
        ("head, tail indices with modulo wrapping:", CYAN),
        ("   tail = (tail + 1) % capacity", CYAN),
        ("push() — O(1), auto-overwrites oldest when full", MUTED),
        ("toVector() — extracts items in chronological order", MUTED),
        ("Zero fragmentation — bounded memory always", GREEN),
        ("Displays last 5 scans in Tab 6 Telemetry panel", GOLD),
    ])

    # =========================================================================
    # SLIDE 11 — OOP & MEMORY SAFETY
    # =========================================================================
    s11 = prs.slides.add_slide(blank); bg(s11)
    header(s11, "Software Engineering: Polymorphism, OOP & Memory Safety")

    card(s11, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "Detector.h — Abstract Base Class + Strategy Pattern")
    bullets(s11, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("Pure virtual:  virtual scan() = 0  → abstract class", CYAN),
        ("Cannot instantiate Detector directly — enforced by C++", MUTED),
        ("3 concrete classes: Keyword / Url / PatternDetector", MUTED),
        ("Investigator.h: vector<unique_ptr<Detector>> detectors", GOLD),
        ("Runtime vtable dispatch → polymorphic scan() calls", GREEN),
        ("Open/Closed Principle: add new Detector without", MUTED),
        ("  changing Investigator.h — zero engine rewrite needed", GREEN),
    ])

    card(s11, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Rule of Three — Memory Safety Across All Headers", RED)
    bullets(s11, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("All templates manage raw Node* heap pointers", MUTED),
        ("Default shallow copy → double-free heap corruption", RED),
        ("Stack.h:      copy ctor = delete;  op= = delete", GOLD),
        ("Queue.h:      copy ctor = delete;  op= = delete", GOLD),
        ("DoublyList.h: copy ctor = delete;  op= = delete", GOLD),
        ("Destructors traverse full chain → delete every node", GREEN),
        ("Result: ZERO memory leaks — Valgrind/ASan verified", GREEN),
    ])

    # =========================================================================
    # SLIDE 12 — QT GUI 6 TABS
    # =========================================================================
    s12 = prs.slides.add_slide(blank); bg(s12)
    header(s12, "Qt 6 Desktop GUI — 6 Interactive Tabs & Their Header Files")

    tabs12 = [
        ("Tab 1: Investigate",
         "Investigator.h → Normalizer.h → Tokenizer.h\nKeywordDetector.h + UrlDetector.h + PatternDetector.h → Scorer.h",
         CYAN),
        ("Tab 2: Evidence Docket (Stack)",
         "Stack.h — LIFO evidence storage\nSorting.h — MergeSort on 'Sort by Severity' button",
         GREEN),
        ("Tab 3: Top-K Threats & Homographs",
         "MaxHeap.h — Top-3 highest-weight evidence extraction\nLevenshtein.h — Live 2D DP typosquat distance calculator",
         GOLD),
        ("Tab 4: Syndicate Graph (BFS)",
         "ThreatGraph.h — Adjacency list graph + syndicate clustering\nQueue.h — Custom FIFO queue powering BFS traversal",
         RED),
        ("Tab 5: Algorithm Lab",
         "Sorting.h — Live BubbleSort / QuickSort / MergeSort benchmarks\nRuleBook.h — Binary Search vs Linear Search step counter",
         PURPLE),
        ("Tab 6: Audit & Telemetry",
         "DoublyList.h — Back/Next bidirectional navigation\nCircularBuffer.h — Rolling last-5-scans telemetry panel",
         CYAN),
    ]
    for idx, (tname, tdesc, col) in enumerate(tabs12):
        r = idx // 2; c = idx % 2
        lx = Inches(0.8 + c * 6.1)
        ty = Inches(1.72 + r * 1.78)

        bx = s12.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE,
                                   lx, ty, Inches(5.8), Inches(1.58))
        bx.fill.solid(); bx.fill.fore_color.rgb = CARD_BG
        bx.line.color.rgb = col; bx.line.width = Pt(2)

        tb = s12.shapes.add_textbox(lx+Inches(0.2), ty+Inches(0.1),
                                    Inches(5.4), Inches(1.4))
        tf = tb.text_frame; tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = tname; p1.font.size = Pt(13)
        p1.font.bold = True; p1.font.color.rgb = col
        p2 = tf.add_paragraph()
        p2.text = tdesc; p2.font.size = Pt(11)
        p2.font.color.rgb = MUTED

    # =========================================================================
    # SLIDE 13 — VIVA Q&A
    # =========================================================================
    s13 = prs.slides.add_slide(blank); bg(s13)
    header(s13, "Viva Defense — Anticipated Evaluator Questions & Winning Answers")

    qa = [
        ("Q: Why implement Stack/Queue from scratch instead of using STL?",
         "A: STL abstracts node allocation. Custom templates demonstrate raw pointer mastery, Rule of Three, O(1) linked-list operations, and proper destructor design — which is the core DSA skill being evaluated.",
         GOLD),
        ("Q: Why use a Stack for URL parsing instead of left-to-right string split?",
         "A: Attackers front-load fake brands in subdomains (login.easypaisa.com.evil.xyz). The real domain is always the LAST 2 labels. Stack.h reverses them in O(L) — the only correct approach for subdomain spoofing.",
         CYAN),
        ("Q: Why MaxHeap over QuickSort for Top-3 extraction?",
         "A: Sorting all N evidence items costs O(N log N). MaxHeap builds in O(N) and extracts K=3 items in O(K log N). When K=3 and N=20 flags, Heap performs ~6× fewer operations.",
         GREEN),
        ("Q: How does BFS detect scam syndicates?",
         "A: Each URL/phone is a graph node. addLink() creates an edge when two entities appear in the same message. BFS from a seed node explores ALL connected nodes via our custom Queue<string> in O(V+E) — revealing the full crime ring.",
         RED),
    ]
    for idx, (q, a, col) in enumerate(qa):
        ty = Inches(1.72 + idx * 1.33)
        bx = s13.shapes.add_shape(MSO_SHAPE.ROUNDED_RECTANGLE,
                                   Inches(0.8), ty, Inches(11.7), Inches(1.18))
        bx.fill.solid(); bx.fill.fore_color.rgb = CARD_BG
        bx.line.color.rgb = col; bx.line.width = Pt(1.8)
        tb = s13.shapes.add_textbox(Inches(1.0), ty+Inches(0.07),
                                    Inches(11.3), Inches(1.05))
        tf = tb.text_frame; tf.word_wrap = True
        p1 = tf.paragraphs[0]
        p1.text = q; p1.font.bold = True
        p1.font.size = Pt(12); p1.font.color.rgb = col
        p2 = tf.add_paragraph()
        p2.text = a; p2.font.size = Pt(11)
        p2.font.color.rgb = WHITE

    # =========================================================================
    # SLIDE 14 — CONCLUSION
    # =========================================================================
    s14 = prs.slides.add_slide(blank); bg(s14)
    header(s14, "Conclusion — Project Achievements & Future Scope")

    card(s14, Inches(0.8), Inches(1.72), Inches(5.65), Inches(5.1),
         "Key Achievements", GREEN)
    bullets(s14, Inches(1.0), Inches(2.42), Inches(5.25), [
        ("✔ 10 Custom DSA implementations — zero STL containers", WHITE),
        ("  Stack.h, Queue.h, DoublyList.h, CircularBuffer.h", CYAN),
        ("  MaxHeap.h, ThreatGraph.h, Levenshtein.h, Sorting.h", CYAN),
        ("  RuleBook.h, Normalizer.h, Tokenizer.h, Detector hierarchy", CYAN),
        ("✔ 100% explainable forensic verdict + Phishing Triad penalty", WHITE),
        ("✔ Dual-mode: CLI test suite + Qt 6 dark-theme GUI", WHITE),
        ("✔ Pakistan-specific: Easypaisa, JazzCash, BISP brands", GREEN),
    ])

    card(s14, Inches(6.8), Inches(1.72), Inches(5.75), Inches(5.1),
         "Future Scope & Extensions", CYAN)
    bullets(s14, Inches(7.0), Inches(2.42), Inches(5.35), [
        ("• Trie + Aho-Corasick: O(k) multi-pattern keyword matching", MUTED),
        ("• Live GSM hook via SIM800L/ADB for real-time SMS scan", MUTED),
        ("• SQLite-backed DoublyList for persistent cross-session audit", MUTED),
        ("• REST API wrapper for web & mobile integration", MUTED),
        ("", MUTED),
        ("Thank you!", GOLD),
        ("We welcome your questions and evaluation.", WHITE),
    ])

    s14.notes_slide.notes_text_frame.text = (
        "Thank you. CipherTrace proves that Data Structures are not just textbook theory "
        "but the foundation of high-performance, explainable cybersecurity systems. "
        "We welcome all questions from the evaluation committee."
    )

    # ── Save ──────────────────────────────────────────────────────────────────
    out = os.path.abspath(
        r"c:\Users\LENOVO\OneDrive\Desktop\Data-Structure-and-Algorithm-"
        r"\CCP\Cipher Trace\docs\CipherTrace_Presentation.pptx"
    )
    os.makedirs(os.path.dirname(out), exist_ok=True)
    prs.save(out)
    print(f"✅  Presentation saved → {out}")
    print(f"📊  Total slides: 14")

if __name__ == "__main__":
    create_deck()
