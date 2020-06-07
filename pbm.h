#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "image.h"

using namespace std;

class PBM : public Image {
public:
	PBM();
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

	int getValueAtPosition(int, int);
	int getWidth();
	int getHeight();
	char* getImageName();
	string getMagicNum();

	void setValueAtPosition(int, int, int);

	~PBM();
private:
	char* imageName;
	string magicNum;
	int width;
	int height;
	int range;
	vector<int> value;
};

