# ParseMaster 🔍📜

## Overview
**ParseMaster** is a C-based syntax parser designed to analyze tokenized source code using recursive descent parsing guided by BNF grammar rules. It is part of a mini-compiler project and works directly with the lexical analyzer developed in the companion repository **[LexiScan](https://github.com/yourusername/LexiScan)**.

This parser can:
- Recognize valid syntax based on a defined grammar (BNF)
- Parse arithmetic, conditional, and compound statements
- Output errors for invalid syntax using a fault-tolerant mechanism

## Features
- Recursive descent parsing
- Fault-tolerant error detection
- Modular codebase designed to integrate with LexiScan

## 🔧 Requirements
- GCC or any standard C compiler
- The **LexicalAnalyzer.c** file from the [LexiScan repository](https://github.com/yourusername/LexiScan)

## 📁 File Structure
/ParseMaster ├── parser.c # Main syntax parser implementation ├── parser.h  ├── BNF_Rules.png # Visual reference of the grammar rules ├── README.md # You're reading it!
