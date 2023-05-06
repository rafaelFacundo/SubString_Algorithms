#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

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

void generateAleatoryString(char *vector, char limitLetter, int lenOfString)
{
    int limit = limitLetter - 'a';
    RandomNumber teste{limit};
    for (char *i = vector; i != (vector + lenOfString); ++i)
    {
        *(i) = 'a' + teste.returnNumber();
    }
    for (int i = 0; i < lenOfString; ++i)
    {
        cout << vector[i];
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{

    char *text;
    char *pattern;
    int lenOfString;
    switch (*(argv[1]))
    {
    case 'A':
        lenOfString = atoi(argv[4]);
        text = (char *)malloc(lenOfString * (sizeof(char *) + 1));
        generateAleatoryString(text, *(argv[2]), lenOfString);
        break;

    default:
        cout << "Entrada inválida\n";
        break;
    }
}