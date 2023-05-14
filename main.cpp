#include <iostream>
#include <stdlib.h>
#include <random>
#include <chrono>
#include "./instancias_Reais_Trabalho_2.hpp"
using namespace std;
using namespace chrono;

void printV(int *v)
{
    for (int *i = v; *(i) != -1; ++i)
    {
        cout << *(i) << ' ';
    }
    cout << '\n';
}

void printS(char *string)
{
    for (char *i = string; *(i) != '\0'; ++i)
    {
        cout << *(i);
    }
    cout << '\n';
}

struct ExecutionError
{
    const char *message;
};

int countLen(const char *text)
{
    int sum = 0;
    for (const char *i = text; *(i) != '\0'; ++i)
    {
        ++sum;
    }
    return sum;
}

bool verifyTheResults(int *kmpOvec, int *bruteOvec)
{
    while ((*(kmpOvec) == *(bruteOvec)) && (*(kmpOvec) != -1 && *(bruteOvec) != -1))
    {
        ++kmpOvec;
        ++bruteOvec;
    }
    if (*(kmpOvec) != -1 || *(bruteOvec) != -1)
        return false;
    else
        return true;
}

//=========================================================

void makeLPS(int oc[], const char *pattern)
{
    int sum = 0;
    oc[0] = sum;
    int len = 0;
    int i = 1;
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

    try
    {
        int lenPattern = countLen(pattern);
        int *oc = new int[lenPattern];
        makeLPS(oc, pattern);
        int i = 0;
        int j = 0;
        int *oPosi = o;
        while (*(text + j) != '\0')
        {
            if (text[j] != pattern[i] && i > 0)
            {
                i = oc[i - 1];
            }
            else if (text[j] != pattern[i] && i == 0)
            {
                ++j;
            }
            else if (text[j] == pattern[i])
            {
                ++i;
                ++j;
            }
            if (i == lenPattern)
            {
                *(oPosi) = j - i;
                i = oc[i - 1];
                ++oPosi;
            }
        }
        *(oPosi) = -1;
    }
    catch (const bad_alloc &e)
    {
        throw ExecutionError{e.what()};
    }
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
}

void printResults(duration<double> kmpTime, duration<double> bruteTime)
{
    cout << "== RESULTADO DOS TEMPOS GASTOS PELOS ALGORITMOS: \n";
    cout << "== KMP  --------- : " << kmpTime.count() << " seg.\n";
    cout << "== FORÇA BRUTA -- : " << bruteTime.count() << " seg.\n";
}

//=========================

int main(int, char *argv[])
{

    char *text;
    char *pattern;
    int numberOfinstances;
    int lenOfString;
    int lenOfPattern;
    int *o_ofKmp;
    int *o_ofBrute;
    char letter;
    int x;
    int y;

    duration<double> kmpTime;
    duration<double> bruteTime;

    try
    {
        switch (*(argv[1]))
        {
        case 'A':
            numberOfinstances = atoi(argv[5]);
            lenOfString = atoi(argv[4]);
            lenOfPattern = atoi(argv[3]);
            letter = *(argv[2]);
            text = new char[lenOfString];
            pattern = new char[lenOfPattern];
            o_ofBrute = new int[lenOfString];
            o_ofKmp = new int[lenOfString];

            while (numberOfinstances > 0)
            {
                generateAleatoryString(text, letter, lenOfString);
                generateAleatoryString(pattern, letter, lenOfPattern);
                auto startKMP = steady_clock::now();
                KMP(text, pattern, o_ofKmp);
                auto endKMP = steady_clock::now();
                kmpTime += endKMP - startKMP;
                auto startBrute = steady_clock::now();
                brute(text, pattern, o_ofBrute);
                auto endBrute = steady_clock::now();
                bruteTime += endBrute - startBrute;
                cout << "O vetor de ocorrencia: \n";
                cout << "Força bruta: \n";
                printV(o_ofBrute);
                cout << "KMP: \n";
                printV(o_ofKmp);

                if (!verifyTheResults(o_ofBrute, o_ofKmp))
                {
                    throw ExecutionError{"Os algoritmos não funcionaram.\n"};
                    break;
                }
                --numberOfinstances;
            }
            printResults(kmpTime, bruteTime);
            break;

        case 'R':
            o_ofBrute = (int *)malloc(35129 * sizeof(int));
            o_ofKmp = (int *)malloc(35129 * sizeof(int));
            x = atoi(argv[2]);
            y = atoi(argv[3]);
            if (x > y || x > 35129 || y > 35129)
                throw ExecutionError{"Os valores de x e y fornecidos estão incorretos.\n"};
            while (x <= y)
            {
                auto startKMP = steady_clock::now();
                KMP(Texto_Livros, Padroes_Palavras[x], o_ofKmp);
                auto endKMP = steady_clock::now();
                kmpTime += endKMP - startKMP;
                auto startBrute = steady_clock::now();
                brute(Texto_Livros, Padroes_Palavras[x], o_ofBrute);
                auto endBrute = steady_clock::now();
                bruteTime += endBrute - startBrute;
                if (!verifyTheResults(o_ofBrute, o_ofKmp))
                {
                    throw ExecutionError{"Os algoritmos não funcionaram.\n"};
                    break;
                }
            }
            printResults(kmpTime, bruteTime);
            break;

        default:
            throw ExecutionError{"Entrada inválida.\n"};
            break;
        }
    }
    catch (ExecutionError &e)
    {
        cout << e.message << '\n';
    }
    catch (...)
    {
        cout << "Algum erro inesperado aconteceu, tente novamente.\n";
    }

    /* delete text;
    delete pattern;
    delete o_ofBrute;
    delete o_ofKmp; */
}

/* g++ -Wall -Wextra -std=c++17 -pedantic -o programa main.cpp */

/*

    afekfkfkklk
            abcf

         abcf

*/