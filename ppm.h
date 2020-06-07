#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include "image.h"
#include "pixel.h"

using namespace std;

class PPM : public Image {
public:
	PPM();
	void load(const char*);
	void save();
	void saveAs(const char*);
	
	bool isMonochrome();
	void makeMonochrome();
	bool isAlreadyGrayscaled();
	void grayscale();
	void makeNegative();

	void makeHorizontalCollage(const char*, const char*, const char*);
	void makeVerticalCollage(const char*, const char*, const char*);

	Pixel& getPixelAtPosition(int, int);
	int getWidth();
	int getHeight();
	char* getImageName();
	string getMagicNum();

	void setPixelAtPosition(int, int, Pixel&);

	~PPM();
private:
	char* imageName;
	string magicNum;
	int width;
	int height;
	int range;
	vector<Pixel> pixels;
};

