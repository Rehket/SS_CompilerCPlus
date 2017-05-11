//
// Created by adama on 5/9/2017.
//

#ifndef SS_COMPILERC_LEXICALANALYZER_H
#define SS_COMPILERC_LEXICALANALYZER_H

#include <stdlib.h>
#include <string>
#include <array>

using namespace std;

typedef enum {nulSymbol = 0, identSymbol, numberSymbol, plusSymbol, minusSymbol, multiplySymbol,
    slashSymbol, oddSymbol, equalSymbol, notEqualSymbol, lessthanSymbol, lessthanEqualSymbol,
    greaterthanSymbol, greaterthanEqualSymbol, leftParentheseSymbol, rightParentheseSymbol, commaSymbol, semicolunSymbol,
    peroidSymbol, becomesSymbol, beginSymbol, endSymbol, ifSymbol, thenSymbol, whileSymbol, doSymbol, callSymbol,
    constantSymbol, variableSymbol, procedureSymbol, writeSymbol,
    readSymbol, elseSymbol} tokenSymbols;

typedef enum {noComment = 0, lineComment, blockComment} commentTypes;

// The language alphabet.
const string ALPHABET ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");


const array<string, 14> RESERVED = {"const", "var", "procedure", "call", "begin", "end", "if",
                                    "then", "else", "while", "do", "read", "write", "odd"};

const array<string, 16> SYMBOLS = {"+", "-", "*", "/", "(", ")", "=", "," , ".", "<", ">",
                                   ";", ":=", "<=" , ">=", "<>"};

class Lexer{

private:


public:
    Lexer();
    ~Lexer();


    //Remove Comments from the Files.
    string clearComments(string s, int length);

};



#endif //SS_COMPILERC_LEXICALANALYZER_H



