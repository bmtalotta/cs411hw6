// huffcode.cpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017
//
// Modified 11/29/2020
// Ben Talotta
// For CS 411 Fall 2020 HW 6
#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include<queue>
using std::priority_queue;
#include<vector>
using std::vector;

void HuffCode::setWeights(const unordered_map<char, int>& theweights)
{
    if (theweights.size() == 0) {
        return;
    }
    priority_queue<Node,vector<Node>,compareNodes> pq;
    for (auto i: theweights) {
        Node tmp;
        tmp.freq = i.second;
        tmp.letter = i.first;
        pq.push(tmp);
    }
    while (pq.size() > 1) {
        auto left = std::make_shared<Node>(pq.top());
        pq.pop();
        auto right = std::make_shared<Node>(pq.top());
        pq.pop();
        auto *nextNode = new Node(left, right, left->freq + right->freq);
        pq.push(*nextNode);
    }
    
    root = std::make_shared<Node>(pq.top());
    if (theweights.size() == 1) {
        root->left = std::make_shared<Node>(pq.top());
    }
    code(root, "");
}
void HuffCode::code(std::shared_ptr<Node> &curTreePos, string curCodeWord) {

    if ((curTreePos->left)&&(curTreePos->right)) {
        curCodeWord += '0'; //went left tree
        code(curTreePos->left, curCodeWord);
        curCodeWord.pop_back();
        curCodeWord += '1'; //went right tree
        code(curTreePos->right, curCodeWord);
        curCodeWord.pop_back();
    }
    else {
        codewords.insert({ curTreePos->letter, curCodeWord });
    }

};

string HuffCode::encode(const string& text) const
{
    string encodedAnswer = "";
    
    for (auto i : text) {
        for (auto j : codewords) {
            if (i == j.first) {
                encodedAnswer += j.second;
            }
        }
    }
    return encodedAnswer;
}


string HuffCode::decode(const string& codestr) const
{
    string decodedAnswer = "";
    auto tracker = root;
    for (auto i : codestr) {
        if (tracker->left) {
            if (i == 1) {
                tracker = tracker->right;
            }
            else {
                tracker = tracker->left;
            }
        }
        else {
            decodedAnswer += tracker->letter;
            tracker = root;
        }

    }
    return decodedAnswer;
}
