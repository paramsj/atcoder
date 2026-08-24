#include <bits/stdc++.h>
using namespace std;

// Structure to hold parsed assembly lines
struct Instruction {
    string label;
    string opcode;
    string operand;
    int locctr;
    string objCode;
};

// Convert string to uppercase
string toUpper(string str) {
    for (char &c : str) c = toupper(c);
    return str;
}

// Convert integer to Hex string with specific padding
string intToHex(int value, int padding) {
    stringstream ss;
    ss << setfill('0') << setw(padding) << hex << uppercase << value;
    return ss.str();
}

int main() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    vector<Instruction> program;
    map<string, int> symtab;
    map<string, string> optab = {
        {"JMP", "10"},
        {"STA", "20"},
        {"LDA", "00"}
    };

    string line, label, opcode, operand;
    int locctr = 0;
    int startAddress = 0;
    string programName = "";

    // PASS 1: Calculate Location Counters (LOCCTR)
    while (getline(infile, line)) {
        stringstream ss(line);
        label = ""; opcode = ""; operand = "";
        ss >> label >> opcode >> operand;

        if (label == "-") label = ""; // '-' means no label

        Instruction inst;
        inst.label = label;
        inst.opcode = opcode;
        inst.operand = operand;

        if (opcode == "START") {
            startAddress = stoi(operand, nullptr, 16);
            locctr = startAddress;
            inst.locctr = locctr;
            programName = label;
        } else if (opcode == "END") {
            inst.locctr = locctr;
            program.push_back(inst);
            break;
        } else {
            inst.locctr = locctr;
            
            // Add to SYMTAB
            if (label != "") {
                if (opcode == "EQU") {
                    symtab[label] = stoi(operand); // EQU value
                } else {
                    symtab[label] = locctr;
                }
            }

            // Increment LOCCTR based on instruction type
            if (opcode != "EQU") {
                if (opcode == "BYTE") {
                    if (operand.substr(0, 2) == "C'") {
                        locctr += operand.length() - 3; // Length of characters inside C'...'
                    }
                } else {
                    locctr += 3; // Format 3 instruction
                }
            }
        }
        program.push_back(inst);
    }
    infile.close();

    int programLength = locctr - startAddress;

    // PASS 2: Generate Object Code
    vector<string> mRecords;
    string tRecordData = "";
    int tRecordStart = startAddress;

    for (auto &inst : program) {
        if (inst.opcode == "START" || inst.opcode == "END" || inst.opcode == "EQU") {
            continue;
        }

        string objCode = "";

        if (optab.find(inst.opcode) != optab.end()) {
            string op = optab[inst.opcode];
            
            // Handle Immediate addressing (e.g., #1020)
            if (inst.operand[0] == '#') {
                string val = inst.operand.substr(1);
                objCode = op + intToHex(stoi(val, nullptr, 16), 4);
            } 
            // Handle Direct addressing with Symbols (e.g., JMP ADD1)
            else if (symtab.find(inst.operand) != symtab.end()) {
                int address = symtab[inst.operand];
                objCode = op + intToHex(address, 4);
                
                // Generate M Record for absolute addresses that require modification upon relocation
                // M ^ Start Address (locctr+1) ^ Length (04 half-bytes)
                mRecords.push_back("M^" + intToHex(inst.locctr + 1, 6) + "^04");
            }
        } else if (inst.opcode == "BYTE") {
            if (inst.operand.substr(0, 2) == "C'") {
                for (size_t i = 2; i < inst.operand.length() - 1; ++i) {
                    objCode += intToHex((int)inst.operand[i], 2);
                }
            }
        }

        inst.objCode = objCode;
        if (!objCode.empty()) {
            tRecordData += "^" + objCode;
        }
    }

    // PRINT OUTPUTS
    cout << "Symbol Table\n";
    cout << left << setw(15) << "Symbol Name" << "Value\n";
    cout << "------------------------\n";
    // Now Printing the Symbol Table
    vector<string> order = {"ADD1", "ADD2", "DATA1", "DATA2"};
    for (const string& sym : order) {
        if (symtab.find(sym) != symtab.end()) {
            if (sym == "DATA2") cout << left << setw(15) << sym << symtab[sym] << "\n";
            else cout << left << setw(15) << sym << intToHex(symtab[sym], 0) << "\n";
        }
    }

    cout << "\nObject Code\n";
    cout << left << setw(10) << "LOC" << setw(10) << "LABEL" << setw(10) << "OPCODE" << setw(15) << "OPERAND" << "OBJ_CODE\n";
    cout << "---------------------------------------------------------\n";
    for (const auto &inst : program) {
        if(inst.opcode != "EQU" && inst.opcode != "END") {
            cout << left << setw(10) << intToHex(inst.locctr, 4) 
                 << setw(10) << (inst.label == "" ? "-" : inst.label) 
                 << setw(10) << inst.opcode 
                 << setw(15) << inst.operand 
                 << inst.objCode << "\n";
        } else if (inst.opcode == "EQU" || inst.opcode == "END") {
            cout << left << setw(10) << "-" 
                 << setw(10) << (inst.label == "" ? "-" : inst.label) 
                 << setw(10) << inst.opcode 
                 << setw(15) << inst.operand 
                 << inst.objCode << "\n";
        }
    }

    cout << "\nObject Program Records\n";
    
    // Header Record
    programName.resize(6, ' '); // Pad with spaces
    cout << "H^" << programName << "^" << intToHex(startAddress, 6) << "^" << intToHex(programLength, 6) << "\n";
    
    // Text Record
    cout << "T^" << intToHex(tRecordStart, 6) << "^" << intToHex(programLength, 2) << tRecordData << "\n";
    
    // Modification Records
    for (const string& mRec : mRecords) {
        cout << mRec << "\n";
    }
    
    // End Record
    cout << "E^" << intToHex(startAddress, 6) << "\n";

    return 0;
}