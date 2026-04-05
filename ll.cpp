#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <iomanip>

using namespace std;

// Split input into individual tokens
vector<string> get_tokens(string input) {
    vector<string> tokens;
    stringstream ss(input);
    string buf;
    while (ss >> buf) tokens.push_back(buf);
    tokens.push_back("$"); 
    return tokens;
}

void run_ll1_parser(string expr) {
    vector<string> tokens = get_tokens(expr);
    stack<string> parse_stack;
    parse_stack.push("$");
    parse_stack.push("S");

    // LL(1) Parsing Table
    // Transformed to remove left-recursion
    map<string, map<string, vector<string>>> table;
    
    table["S"]["id"]  = {"id", "=", "E"};
    table["E"]["id"]  = {"T", "E'"};
    table["E"]["num"] = {"T", "E'"};
    table["E'"]["+"]  = {"+", "T", "E'"};
    table["E'"]["$"]  = {}; 
    table["T"]["id"]  = {"F", "T'"};
    table["T"]["num"] = {"F", "T'"};
    table["T'"]["*"]  = {"*", "F", "T'"};
    table["T'"]["+"]  = {}; 
    table["T'"]["$"]  = {}; 
    table["F"]["id"]  = {"id"};
    table["F"]["num"] = {"num"};

    cout << "\nAnalyzing: " << expr << endl;
    cout << left << setw(20) << "Stack" << " | " << setw(20) << "Input" << " | Action" << endl;
    cout << string(60, '-') << endl;

    int pos = 0;
    while (!parse_stack.empty()) {
        // Stringify stack for output
        stack<string> display_s = parse_stack;
        string s_out = "";
        while(!display_s.empty()) { s_out += display_s.top() + " "; display_s.pop(); }
        
        // Stringify remaining input for output
        string in_out = "";
        for(int i = pos; i < tokens.size(); ++i) in_out += tokens[i] + " ";

        string top = parse_stack.top();
        parse_stack.pop();
        string lookahead = tokens[pos];

        if (top == lookahead) {
            cout << setw(20) << s_out << " | " << setw(20) << in_out << " | Match " << lookahead << endl;
            pos++;
        } else if (table.count(top)) {
            if (table[top].count(lookahead)) {
                vector<string> derivation = table[top][lookahead];
                
                string der_str = top + " -> ";
                if(derivation.empty()) der_str += "ε";
                else for(auto& sym : derivation) der_str += sym + " ";
                
                cout << setw(20) << s_out << " | " << setw(20) << in_out << " | " << der_str << endl;

                // Push onto stack in reverse
                for (int i = derivation.size() - 1; i >= 0; i--) {
                    parse_stack.push(derivation[i]);
                }
            } else {
                cout << setw(20) << s_out << " | " << setw(20) << in_out << " | Error: Unexpected token" << endl;
                cout << "Result: Reject" << endl; return;
            }
        } else {
            cout << setw(20) << s_out << " | " << setw(20) << in_out << " | Error: Mismatch" << endl;
            cout << "Result: Reject" << endl; return;
        }
    }

    if (pos == tokens.size()) cout << "\nResult: Accept" << endl;
    else cout << "\nResult: Reject" << endl;
}

int main() {
    run_ll1_parser("id = id + num * id");
    run_ll1_parser("id = + id * num");
    return 0;
}