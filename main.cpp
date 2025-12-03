// main.cpp - Linux-compatible version for Ubuntu
// Compile: g++ -std=c++17 -O2 -o tradable main.cpp
// Run: ./tradable
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>   // usleep
#include <iomanip>    // setw, setprecision

using namespace std;

// Small stock record used by this demo program
struct Stock {
    string symbol;
    string name;
    double price;
    double pe_ratio;   // price-earnings ratio
    double ev_to_ebit; // example metric
};

// helper: split string into tokens (words)
vector<string> separate_words(const string &text) {
    vector<string> words;
    istringstream iss(text);
    string w;
    while (iss >> w) words.push_back(w);
    return words;
}

// Load stocks from CSV file named "data.csv" in current folder
// CSV format: symbol,name,price,pe_ratio,ev_to_ebit
vector<Stock> loadStocks(const string &csvFile = "data.csv") {
    vector<Stock> stocks;
    ifstream in(csvFile);
    if (!in.is_open()) {
        // file missing: return empty vector (program still works)
        return stocks;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        // simple parsing
        istringstream ss(line);
        string symbol, name, priceS, peS, evS;

        if (!getline(ss, symbol, ',')) continue;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, priceS, ',')) continue;
        if (!getline(ss, peS, ',')) continue;
        if (!getline(ss, evS, ',')) {
            // last column might not have comma; try read remainder
            // (not strictly needed)
        }

        try {
            Stock s;
            s.symbol = symbol;
            s.name = name;
            s.price = stod(priceS);
            s.pe_ratio = stod(peS);
            s.ev_to_ebit = stod(evS);
            stocks.push_back(s);
        } catch (...) {
            // skip bad line
            continue;
        }
    }
    return stocks;
}

// Simple login (demo). In production, replace with secure auth.
bool login() {
    string user, pass;
    cout << "=== Tradable — Login ===\n";
    cout << "Username: ";
    getline(cin, user);
    cout << "Password: ";
    getline(cin, pass);
    // demo credentials: admin / 1234
    if (user == "admin" && pass == "1234") {
        cout << "Login successful.\n";
        usleep(500 * 1000);
        return true;
    }
    cout << "Login failed.\n";
    usleep(700 * 1000);
    return false;
}

// Show main menu
void functionsMenu() {
    cout << "\n=== Main Menu ===\n";
    cout << "1) Search stocks\n";
    cout << "2) P/E analysis (show average P/E)\n";
    cout << "3) EV/EBIT analysis (show low/high)\n";
    cout << "4) Recommend (simple rule)\n";
    cout << "5) User Activity (demo)\n";
    cout << "0) Exit\n";
    cout << "Choose option: ";
}

// Search stocks by symbol or name (case-insensitive)
void searchStocks(const vector<Stock> &stocks) {
    cout << "\nEnter search term (symbol or name): ";
    string term; getline(cin, term);
    string low = term;
    transform(low.begin(), low.end(), low.begin(), ::tolower);

    vector<Stock> found;
    for (auto &s : stocks) {
        string sym = s.symbol;
        string nm = s.name;
        transform(sym.begin(), sym.end(), sym.begin(), ::tolower);
        transform(nm.begin(), nm.end(), nm.begin(), ::tolower);
        if (sym.find(low) != string::npos || nm.find(low) != string::npos) {
            found.push_back(s);
        }
    }

    if (found.empty()) {
        cout << "No stocks matched your search.\n";
        return;
    }

    cout << "\nMatches:\n";
    cout << left << setw(10) << "Symbol" << setw(30) << "Name" 
         << setw(10) << "Price" << setw(8) << "P/E" << setw(10) << "EV/EBIT\n";
    cout << string(70, '-') << "\n";
    cout << fixed << setprecision(2);
    for (auto &f : found) {
        cout << left << setw(10) << f.symbol
             << setw(30) << f.name
             << setw(10) << f.price
             << setw(8) << f.pe_ratio
             << setw(10) << f.ev_to_ebit << "\n";
    }
}

// Compute and show average P/E for loaded stocks
void PEanalysis(const vector<Stock> &stocks) {
    if (stocks.empty()) {
        cout << "No stock data loaded.\n";
        return;
    }
    double sum = 0; int n = 0;
    for (auto &s : stocks) {
        if (s.pe_ratio > 0) { sum += s.pe_ratio; ++n; }
    }
    if (n==0) {
        cout << "No P/E data available.\n";
        return;
    }
    cout << "Average P/E (across " << n << " stocks): " << fixed << setprecision(2) << (sum / n) << "\n";
}

// Simple EV/EBIT analysis: show top 5 lowest EV/EBIT
void Evebanalysis(const vector<Stock> &stocks) {
    if (stocks.empty()) {
        cout << "No stock data loaded.\n";
        return;
    }
    vector<Stock> copy = stocks;
    sort(copy.begin(), copy.end(), [](const Stock &a, const Stock &b){
        return a.ev_to_ebit < b.ev_to_ebit;
    });
    int limit = min((int)copy.size(), 5);
    cout << "Top " << limit << " stocks with lowest EV/EBIT (possible value buys):\n";
    for (int i=0;i<limit;i++){
        auto &s = copy[i];
        cout << i+1 << ") " << s.symbol << " | " << s.name << " | EV/EBIT: " 
             << fixed << setprecision(2) << s.ev_to_ebit << " | Price: " << s.price << "\n";
    }
}

// Recommend simple rules: low P/E and low EV/EBIT
void Recommend(const vector<Stock> &stocks) {
    cout << "\nRecommendations (simple rule: P/E < 15 and EV/EBIT < 8):\n";
    for (auto &s : stocks) {
        if (s.pe_ratio > 0 && s.pe_ratio < 15 && s.ev_to_ebit > 0 && s.ev_to_ebit < 8) {
            cout << "- " << s.symbol << " (" << s.name << ")  P/E: " << s.pe_ratio 
                 << "  EV/EBIT: " << s.ev_to_ebit << "\n";
        }
    }
}

// Dummy user activity function (demo)
void userActivity() {
    cout << "\nUser activity (demo): you logged in and browsed.\n";
    // In real app, log timestamp, actions, etc.
}

int main() {
    // Load stocks from data.csv (if present)
    vector<Stock> stocks = loadStocks("data.csv");

    // Welcome
    cout << "Welcome to Tradable (Linux demo)\n";
    // Login loop
    bool ok = false;
    for (int tries=0; tries<3 && !ok; ++tries) {
        ok = login();
        if (!ok && tries < 2) cout << "Try again...\n";
    }
    if (!ok) {
        cout << "Too many failed attempts. Exiting.\n";
        return 0;
    }

    // Main menu loop
    while (true) {
        system("clear");
        functionsMenu();
        string choice;
        getline(cin, choice);
        if (choice.empty()) continue;

        if (choice == "0") {
            cout << "Goodbye!\n";
            break;
        } else if (choice == "1") {
            searchStocks(stocks);
        } else if (choice == "2") {
            PEanalysis(stocks);
        } else if (choice == "3") {
            Evebanalysis(stocks);
        } else if (choice == "4") {
            Recommend(stocks);
        } else if (choice == "5") {
            userActivity();
        } else {
            cout << "Unknown option.\n";
        }

        cout << "\nPress Enter to return to menu...";
        string tmp; getline(cin, tmp);
    }

    return 0;
}
