#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

int countLen(const char *text)
{
    int sum = 0;
    for (const char *i = text; *(i) != '\0'; ++i)
    {
        ++sum;
    }
    return sum;
}

void printV(int *v, int len)
{
    for (int *i = v; i != (v + len); ++i)
    {
        cout << *(i) << ' ';
    }
    cout << '\n';
}

//=========================================================

void makeLPS(int oc[], const char *pattern)
{
    int sum = 0;
    oc[0] = sum;
    int len = 0;
    int posiLooking = 0;
    int i = 0;
    i++;
    while (pattern[i] != '\0')
    {
        if (pattern[len] == pattern[i])
        {
            len++;
            oc[i] = len;
            i++;
        }
        else if (pattern[len] != pattern[i] && len == 0)
        {
            oc[i] = len;
            i++;
        }
        else if (pattern[len] != pattern[i] && len != 0)
        {
            len = oc[len - 1];
        }
    }
}

void KMP(const char *text, const char *pattern, int *o)
{
    int lenPattern = countLen(pattern);
    int *oc = (int *)malloc(lenPattern * sizeof(int));
    makeLPS(oc, pattern);
    int i = 0;
    int j = 0;
    int sum = 0;
    int *oPosi = o;
    while (text[j] != '\0')
    {
        if (text[j] != pattern[i] && i == 0)
        {
            ++j;
        }
        else if (text[j] != pattern[i] && i > 0)
        {
            i = oc[i - 1];
        }
        else if (text[j] == pattern[i])
        {
            ++i;
            ++j;
        }
        if (i == lenPattern)
        {
            ++sum;
            cout << "achei " << (j - i) << '\n';
            *(oPosi) = j - i;
            i = 0;
            ++oPosi;
        }
    }
    *(oPosi) = -1;
}

//===========================================================

void brute(const char *text, const char *pattern, int *o)
{
    int textp2;
    int pat2;
    int *oPosi = o;
    for (int i = 0; text[i] != '\0'; ++i)
    {
        textp2 = i;
        pat2 = 0;
        while ((text[textp2] != '\0' && pattern[pat2] != '\0') && (text[textp2] == pattern[pat2]))
        {
            ++pat2;
            ++textp2;
        }
        if (pattern[pat2] == '\0')
        {
            cout << "bruta achohu " << i << '\n';
            *(oPosi) = i;
            ++oPosi;
        }
    }
    *(oPosi) = -1;
}

//===========================================================

class RandomNumber
{
private:
    int end;

public:
    static mt19937 generator;
    RandomNumber(int endNumber) : end(endNumber){};
    uniform_int_distribution<> distr{0, end};
    int returnNumber()
    {
        return distr(generator);
    };
};

random_device disp_alea;
mt19937 RandomNumber::generator{disp_alea()};

//=====================

void generateAleatoryString(char *vector, char limitLetter, int lenOfString)
{
    int limit = limitLetter - 'a';
    RandomNumber teste{limit};
    for (char *i = vector; i != (vector + lenOfString); ++i)
    {
        *(i) = 'a' + teste.returnNumber();
    }
    *(vector + lenOfString) = '\0';
    cout << '\n';
}

//=========================

int main(int argc, char *argv[])
{

    char *text;
    char *pattern;
    int lenOfString;
    int lenOfPattern;
    int *o_ofKmp;
    int *o_ofBrute;
    switch (*(argv[1]))
    {
    case 'A':
        lenOfString = atoi(argv[4]);
        lenOfPattern = atoi(argv[3]);
        /* text = (char *)malloc(lenOfString * (sizeof(char *) + 1));
        pattern = (char *)malloc(lenOfPattern * (sizeof(char *) + 1)); */
        o_ofBrute = (int *)malloc(lenOfPattern * (19));
        o_ofKmp = (int *)malloc(lenOfPattern * (19));

        // generateAleatoryString(text, *(argv[2]), lenOfString);
        pattern = "abcdabca";
        text = "dabcdeabcdabcdabcaa";
        KMP(text, pattern, o_ofKmp);
        brute(text, pattern, o_ofBrute);
        cout << "Vetor do kmp\n ";
        printV(o_ofKmp, 19);
        cout << "Vetor do bruta\n ";
        printV(o_ofBrute, 19);

        break;

    default:
        cout << "Entrada inválida\n";
        break;
    }
}

/* g++ -Wall -Wextra -std=c++17 -pedantic -o programa main.cpp */

/*

    afekfkfkklk
            abcf

         abcf

*/