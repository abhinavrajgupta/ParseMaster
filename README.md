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
/ParseMaster ├── parser.c # Main syntax parser implementation 
             ├── parser.h  
             ├── BNF_Rules.png # Visual reference of the grammar rules 
             ├── README.md # You're reading it!


## 🚀 Getting Started

### 1. Clone this repository:
```bash
git clone https://github.com/yourusername/ParseMaster.git
cd ParseMaster

2. Place LexicalAnalyzer.c in the same folder:
⚠️ This project requires the lexical analyzer code from LexiScan. Make sure LexicalAnalyzer.c is in this directory.


🧠 Learn More
To learn more about how this parser works and how it's tied to compiler design theory, check out the visual BNF rule file (BNF_Rules.png) and inline code comments.

📎 Related Projects
🔤 LexiScan – The lexical analyzer that feeds tokens into ParseMaster: https://github.com/abhinavrajgupta/LexiScan


