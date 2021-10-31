#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Stock{
    string ticker;
    int numShares;
    double costBasis; 
};

class Portfolio{
    private:
        double cash; 
        vector<Stock> positions;
    public:
        Portfolio(ifstream &fin);
        void buy(string ticker, int numShares, double price);
        void sell(string ticker, int numShares, double price);
        void addCash(double amount);
        vector<pair<string, double>> performance();
        vector<pair<string, double>> allocation(bool costBasis);
};

#endif
