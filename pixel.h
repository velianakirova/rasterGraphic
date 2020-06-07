#pragma once
#include <iostream>
using namespace std;

class Pixel {
public:
	Pixel();
	Pixel& operator=(const Pixel&);
	int r;
	int g;
	int b;
};

