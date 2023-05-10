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
            cout << "achei " << sum << '\n';
            i = 0;
        }
    }
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
    int i[5];
    makeLPS(i, vector);
    cout << '\n';
}

//=========================

int main(int argc, char *argv[])
{

    const char *text;
    const char *pattern;
    int lenOfString;
    int *o;
    switch (*(argv[1]))
    {
    case 'A':
        lenOfString = atoi(argv[4]);
        text = (char *)malloc(lenOfString * (sizeof(char *) + 1));
        // generateAleatoryString(text, *(argv[2]), lenOfString);
        pattern = "abcdabca";
        text = "dabcdeabcdabcdabcaa";
        KMP(text, pattern, o);

        break;

    default:
        cout << "Entrada inválida\n";
        break;
    }
}