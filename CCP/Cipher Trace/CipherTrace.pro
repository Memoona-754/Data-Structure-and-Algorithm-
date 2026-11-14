QT += core gui widgets

CONFIG += c++17

TARGET = CipherTraceGUI
TEMPLATE = app

INCLUDEPATH += CODE engine/ds engine/core engine/detectors engine/algo

SOURCES += \
    gui/main_gui.cpp \
    gui/MainWindow.cpp

HEADERS += \
    gui/MainWindow.h \
    CODE/Stack.h \
    CODE/Queue.h \
    CODE/Rule.h \
    CODE/RuleBook.h \
    CODE/Normalizer.h \
    CODE/Tokenizer.h \
    CODE/Detector.h \
    CODE/KeywordDetector.h \
    CODE/UrlDetector.h \
    CODE/PatternDetector.h \
    CODE/Scorer.h \
    CODE/Investigator.h \
    CODE/DoublyList.h \
    CODE/CircularBuffer.h \
    CODE/Sorting.h \
    CODE/Levenshtein.h \
    CODE/MaxHeap.h \
    CODE/ThreatGraph.h

DISTFILES += \
    CODE/rules.txt
