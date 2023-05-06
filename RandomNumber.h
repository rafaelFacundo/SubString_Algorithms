#pragma once
#include <random>
using namespace std;

class RandomNumber
{
    static random_device disp_alea;
    static mt19937 generator;
};