#include "Portfolio.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

Portfolio::Portfolio(ifstream &fin){
    //spec:
    // first line is cash
    // next lines are stocks "<ticker> <numShares> <costBasis>"
    fin >> cash; 
    string ticker; int numShares; double costBasis;
    while(fin >> ticker >> numShares >> costBasis){
        positions.emplace_back(ticker, numShares, costBasis);
    }
}

void Portfolio::addCash(double amount){
    cash += amount;
}

void Portfolio::buy(string ticker, int numShares, double price = 0.0){
    if(numShares * price > cash){
        throw "Insufficient cash";
    }
    for(auto &position : positions){
        if(position.ticker == ticker){
            position.costBasis = 
                ( (position.numShares * position.costBasis) 
                + (numShares * price) ) / (double) (position.numShares + numShares);
            position.numShares += numShares;
            cash -= numShares * price;
            return;
        }
    }
    positions.emplace_back(ticker, numShares, price);
}

void Portfolio::sell(string ticker, int numShares, double price = 0.0){
    for(auto &position : positions){
        if(position.ticker == ticker){
            if(numShares > position.numShares){
                throw "Insufficient shares to sell";
            }
            position.numShares -= numShares;
            cash += numShares * price;
            return;
        }  
    }
    throw "Error: Ticker not found.";
}

vector<pair<string, double>> Portfolio::performance(){
    vector<pair<string, double>> performance;
    //need price data
    return performance;
}

vector<pair<string, double>> Portfolio::allocation(bool costBasis = true){
    //if cost basis is true, want allocation based on cost basis
    //otherwise, based on current price
    vector<pair<string, double>> allocation;
    if(costBasis){
        double value = 0; 
        value += cash; 
        for(auto &position : positions){
            value += position.numShares * position.costBasis;
        }
        allocation.emplace_back("CASH", cash / value);       
        for(auto &position : positions){
            allocation.emplace_back(position.ticker, 
                (position.numShares * position.costBasis) / value);
        }
    }else{
        
    }
    return allocation;
}