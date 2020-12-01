// huffcode.hpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017
//
// Modified 11/29/2020
// Ben Talotta
// For CS 411 Fall 2020 HW 6

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <memory>
class Node {
    
public:
    char letter;
    int freq;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node() {
        letter = NULL;
        freq = 0;
        left = right = NULL;
    }
    Node(char letVal, int freqVal) {
        letter = letVal;
        freq = freqVal;
        left = right = NULL;
    }
    Node(std::shared_ptr<Node> leftNode, std::shared_ptr<Node> rightNode, int newFreq) {
        freq = newFreq;
        left = leftNode;
        right = rightNode;
    }
};
class compareNodes {
public:
    bool operator()(Node &firstNode, Node &secondNode) {
        return firstNode.freq > secondNode.freq;
    }
};
// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    
    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

    
// ***** HuffCode: data members *****
private:
    void code(std::shared_ptr<Node>& curTreePos, std::string curCodeWord);
    std::shared_ptr<Node> root;
    std::unordered_map<char, std::string> codewords;
};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

