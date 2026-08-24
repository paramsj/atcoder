#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <iomanip>
#include <set>

using namespace std;

struct Rule {
    string lhs;
    vector<string> rhs;
};

// Global Table Data
map<int, Rule> rules;
map<pair<int, string>, string> action;
map<pair<int, string>, int> goto_table;
vector<string> terminals = {"id", "num", "+", "=", "*", "$"};
vector<string> non_terminals = {"S", "E", "T", "F"};

void print_table() {
    cout << "\nLR Parsing Table" << endl;
    cout << string(90, '=') << endl;
    cout << left << setw(8) << "State" << " | ";
    for (const auto& t : terminals) cout << setw(8) << t << " ";
    cout << " | ";
    for (const auto& nt : non_terminals) cout << setw(5) << nt << " ";
    cout << endl << string(90, '-') << endl;

    for (int i = 0; i <= 12; ++i) {
        cout << setw(8) << i << " | ";
        for (const auto& t : terminals) {
            string val = action.count({i, t}) ? action[{i, t}] : "-";
            cout << setw(8) << val << " ";
        }
        cout << " | ";
        for (const auto& nt : non_terminals) {
            string val = goto_table.count({i, nt}) ? to_string(goto_table[{i, nt}]) : "-";
            cout << setw(5) << val << " ";
        }
        cout << endl;
    }
    cout << string(90, '=') << endl;
}

vector<string> tokenize(string input) {
    vector<string> tokens;
    stringstream ss(input);
    string buf;
    while (ss >> buf) tokens.push_back(buf);
    tokens.push_back("$");
    return tokens;
}

void run_lr_parser(string input_str) {
    vector<string> tokens = tokenize(input_str);
    stack<int> state_stack;
    stack<string> sym_stack;
    state_stack.push(0);

    cout << "\nAnalyzing: " << input_str << endl;
    cout << left << setw(15) << "States" << " | " << setw(12) << "Symbols" << " | " << setw(18) << "Input" << " | Action" << endl;
    cout << string(75, '-') << endl;

    int idx = 0;
    while (true) {
        int state = state_stack.top();
        string lookahead = tokens[idx];

        // Format stacks for printing
        string states_str = ""; stack<int> st_copy = state_stack; 
        while(!st_copy.empty()) { states_str = to_string(st_copy.top()) + " " + states_str; st_copy.pop(); }
        
        string syms_str = ""; stack<string> sy_copy = sym_stack;
        while(!sy_copy.empty()) { syms_str = sy_copy.top() + syms_str; sy_copy.pop(); }

        string input_rem = "";
        for(int i=idx; i<tokens.size(); ++i) input_rem += tokens[i] + " ";

        if (action.count({state, lookahead})) {
            string act = action[{state, lookahead}];

            if (act[0] == 's') {
                cout << setw(15) << states_str << " | " << setw(12) << syms_str << " | " << setw(18) << input_rem << " | Shift " << act.substr(1) << endl;
                state_stack.push(stoi(act.substr(1)));
                sym_stack.push(lookahead);
                idx++;
            } 
            else if (act[0] == 'r') {
                int rule_num = stoi(act.substr(1));
                Rule r = rules[rule_num];
                cout << setw(15) << states_str << " | " << setw(12) << syms_str << " | " << setw(18) << input_rem << " | Reduce " << r.lhs << " -> ";
                for(auto s : r.rhs) cout << s; cout << endl;

                for(int i=0; i<r.rhs.size(); ++i) {
                    state_stack.pop();
                    sym_stack.pop();
                }
                state_stack.push(goto_table[{state_stack.top(), r.lhs}]);
                sym_stack.push(r.lhs);
            } 
            else if (act == "acc") {
                cout << setw(15) << states_str << " | " << setw(12) << syms_str << " | " << setw(18) << input_rem << " | Accept" << endl;
                cout << "Result: Accept" << endl;
                return;
            }
        } else {
            cout << setw(15) << states_str << " | " << setw(12) << syms_str << " | " << setw(18) << input_rem << " | Error" << endl;
            cout << "Result: Reject" << endl;
            return;
        }
    }
}

int main() {
    // Initialize Rules
    rules = {
        {1, {"S", {"id", "=", "E"}}}, {2, {"E", {"E", "+", "T"}}},
        {3, {"E", {"T"}}}, {4, {"T", {"T", "*", "F"}}},
        {5, {"T", {"F"}}}, {6, {"F", {"id"}}}, {7, {"F", {"num"}}}
    };

    // Initialize Action Table
    action[{0, "id"}] = "s2";
    action[{1, "$"}] = "acc";
    action[{2, "="}] = "s3";
    action[{3, "id"}] = "s7";    action[{3, "num"}] = "s8";
    action[{4, "+"}] = "s9";    action[{4, "$"}] = "r1";
    action[{5, "+"}] = "r3";    action[{5, "*"}] = "s10";   action[{5, "$"}] = "r3";
    action[{6, "+"}] = "r5";    action[{6, "*"}] = "r5";    action[{6, "$"}] = "r5";
    action[{7, "+"}] = "r6";    action[{7, "*"}] = "r6";    action[{7, "$"}] = "r6";
    action[{8, "+"}] = "r7";    action[{8, "*"}] = "r7";    action[{8, "$"}] = "r7";
    action[{9, "id"}] = "s7";    action[{9, "num"}] = "s8";
    action[{10, "id"}] = "s7";   action[{10, "num"}] = "s8";
    action[{11, "+"}] = "r2";   action[{11, "*"}] = "s10";  action[{11, "$"}] = "r2";
    action[{12, "+"}] = "r4";   action[{12, "*"}] = "r4";   action[{12, "$"}] = "r4";

    // Initialize Goto Table
    goto_table[{0, "S"}] = 1; goto_table[{3, "E"}] = 4;
    goto_table[{3, "T"}] = 5; goto_table[{3, "F"}] = 6;
    goto_table[{9, "T"}] = 11; goto_table[{9, "F"}] = 6;
    goto_table[{10, "F"}] = 12;

    print_table();
    run_lr_parser("id = id + num * id");
    run_lr_parser("id = + id * num");

    return 0;
}