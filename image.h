#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#ifndef IMAGE_H
#define IMAGE_H

class Image {
public:

	virtual void load(const char*) = 0;
	virtual void save() = 0;
	virtual void saveAs(const char*) = 0;

	virtual bool isMonochrome() = 0;
	virtual void makeMonochrome() = 0;
	virtual void makeNegative() = 0;
	virtual bool isAlreadyGrayscaled() = 0;
	virtual void grayscale() = 0;

	virtual void makeHorizontalCollage(const char*, const char*, const char*) = 0;
	virtual void makeVerticalCollage(const char*, const char*, const char*) = 0;

	virtual char* getImageName() = 0;
	virtual string getMagicNum() = 0;

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

};


#endif // !IMAGE_H

