/*
 * File: WelcomeToCpp.cpp
 * --------------------------
 * Name: [Jianqiu Wang]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the first assignment of CS106B.
 * [TODO: rewrite the documentation]
 *
 * The repeating call sequence is
 *    triggerStackOverflow(137), which calls
 *    [137, 164, 685, 203, 327, 549], which calls
 *    triggerStackOverflow(137) again.
 */

// Please feel free to add any other #includes you need!
#include "WelcomeToCpp.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "random.h"
#include "tokenscanner.h"


using namespace std;


void flipHeads() {
    /* Write a program that simulates fipping a coin repeatedly
            and continues until three consecutive heads are tossed.
    */
    int count_total = 0;
    int count_head = 0;
    bool last_flip = false;
    while (count_head < 3) {
        if (randomBool()) {
            count_head++;
            last_flip = true;
            cout << "Flip: heads\n";
        } else {
            last_flip = false;
            count_head = 0;
            cout << "Flip: tails\n";
        }
        count_total++;
    }
    cout << "It took "<< count_total << " flips to get 3 consecutive heads.";
}


int nChooseK(int n, int k) {
    /* recursive implementa- tion of a function n choose k that computes n
    choose k using no loops, no multiplication, and no calls to a function that
    computes factorials. */
    if ((n == 0) || (k == 0) || (n == k)) {
        return 1;
    } else {
        return nChooseK(n-1,k-1) + nChooseK(n-1,k);
    }
}


int stringToInt(string str) {
    /* converts a string into its representation as a number */
    if (str[0] == '-') {
        return -stringToInt(str.substr(1));
    }
    if (str.length() == 1) {
        return str[0] - '0';
    } else {
        char ch = str[str.length()-1];
        int val = ch - '0';
        string substring = str.substr(0,str.length()-1);
        return 10*stringToInt(substring) + val;
    }
}


string intToString(int n) {
    /* converts an integer into its representation as a string of decimal digits */
    if (n < 0) {
        return string("-") + intToString(-n);
    } else if (n < 10) {
        char ch = char(n + '0');
        string str(1, ch);
        return str;
    } else {
        return intToString(n/10) + intToString(n%10);
    }
}


DocumentInfo statisticsFor(istream& source) {
    /* it takes as input a stream containing the contents of a file,
     * then returns a DocumentInfo object containing the number of
     * sentences, words, and syllables contained in that file.
     */

    // Use TokenScanner class to read file
    TokenScanner scanner(source);
    scanner.addWordCharacters("'");
    scanner.addWordCharacters("_");
    scanner.ignoreWhitespace(); // ignore white spaces

    // Count words, sentences and syllables
    int count_words = 0, count_sentences = 0, count_syllables = 0;
    string vowels = "aeiouyAEIOUY";
    while (scanner.hasMoreTokens()) {
          string token = scanner.nextToken();
          int count_syllables_inword = 0;
          // indicate whethe char before is a vowel
          bool found0 = false;

          // Loop over every token
          for (int j=0; j < token.length(); j++) {
              // Modify all character to lower
              char i = token[j];
              i = char(tolower(i));
              // count vowels including 'y'
              if ( i=='a' || i=='e' || i=='i' || i=='o' || i=='u' || i=='y') {
                  count_syllables_inword++;
                  if ((j!=0) & (found0)) {
                      // consectuive vowels are only counted once
                      count_syllables_inword--;
                  }
              }
              // Word end with e and second last is not vowels will not be counted
              if (j == token.length()-1) {
                  if ((!found0) & (token[j]=='e')) {
                      count_syllables_inword--;
                  }
              }

              if ( i=='a' || i=='e' || i=='i' || i=='o' || i=='u' || i=='y') {
                  found0 = true;
              } else {
                  found0 = false;
              }
           }

          if (isalpha(token[0])) {
              count_words++;
              count_syllables_inword = max(1,count_syllables_inword);
          }
          if ((token==".") || (token=="!") || ( token=="?")) {
              count_sentences++;
          }
          count_syllables += count_syllables_inword;
    }

    DocumentInfo docInfo = {count_sentences, count_words, count_syllables};
    return docInfo;
}

