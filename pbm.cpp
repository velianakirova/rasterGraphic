#pragma once
#include "pbm.h"

PBM::PBM() {
	width = 0;
	height = 0;
	range = 0;
	magicNum = "P1";
	imageName = nullptr;
}

int PBM::getValueAtPosition(int row, int column) {
	return value[(column * width) + row];
}

int PBM::getWidth() {
	return width;
}

int PBM::getHeight() {
	return height;
}

char* PBM::getImageName() {
	return imageName;
}

string PBM::getMagicNum() {
	return magicNum;
}

void PBM::setValueAtPosition(int row, int column, int value) {
	this->value[(column * width) + row] = value;
}


void PBM::makeHorizontalCollage(const char* imageOne, const char* imageTwo, const char* collageName) {
	imageName = new char[strlen(collageName) + 1];
	for (int i = 0; i < strlen(collageName) + 1; i++) {
		imageName[i] = collageName[i];
	}

	ifstream loadImageOne(imageOne, ios::in);
	if (loadImageOne.fail()) { cout << "Error"; return; }
	ifstream loadImageTwo(imageTwo, ios::in);
	if (loadImageTwo.fail()) { cout << "Error"; return; }

	string _magicNumOne, _magicNumTwo;
	int _widthOne, _heightOne, _rangeOne, _widthTwo, _heightTwo, _rangeTwo;

	loadImageOne >> _magicNumOne;
	loadImageOne >> _widthOne >> _heightOne;
	loadImageOne >> _rangeOne;

	loadImageTwo >> _magicNumTwo;
	loadImageTwo >> _widthTwo >> _heightTwo;
	loadImageTwo >> _rangeTwo;

	magicNum = _magicNumOne;
	width = _widthOne + _widthTwo;
	if (_heightOne > _heightTwo) height = _heightOne;
	else height = _heightTwo;
	range = _rangeOne;

	value.clear();

	int num;
	for (int i = 0; i < width * height; i++) {
		for (int j = 0; j < _widthOne; j++) {
			if (_heightOne >= i) {
				loadImageOne >> num;
				value.push_back(num);
			}
			else value.push_back(0);

		}
		for (int j = _widthOne; j < width; j++) {
			loadImageTwo >> num;
			value.push_back(num);
		}

	}

	loadImageOne.close();
	loadImageTwo.close();
}

void PBM::makeVerticalCollage(const char* imageOne, const char* imageTwo, const char* collageName) {
	imageName = new char[strlen(collageName) + 1];
	for (int i = 0; i < strlen(collageName) + 1; i++) {
		imageName[i] = collageName[i];
	}

	ifstream loadImageOne(imageOne, ios::in);
	if (loadImageOne.fail()) { cout << "Error"; return; }
	ifstream loadImageTwo(imageTwo, ios::in);
	if (loadImageTwo.fail()) { cout << "Error"; return; }

	string _magicNumOne, _magicNumTwo;
	int _widthOne, _heightOne, _rangeOne, _widthTwo, _heightTwo, _rangeTwo;

	loadImageOne >> _magicNumOne;
	loadImageOne >> _widthOne >> _heightOne;
	loadImageOne >> _rangeOne;

	loadImageTwo >> _magicNumTwo;
	loadImageTwo >> _widthTwo >> _heightTwo;
	loadImageTwo >> _rangeTwo;

	magicNum = _magicNumOne;
	height = _heightOne + _heightTwo;
	if (_widthOne > _widthTwo) width = _widthOne;
	else width = _widthTwo;
	range = _rangeOne;

	value.clear();

	int num;
	for (int j = 0; j < _widthOne * _heightOne; j++) {
		loadImageOne >> num;
		value.push_back(num);
	}
	for (int j = _widthOne * _heightOne; j < width * height; j++) {
		loadImageTwo >> num;
		value.push_back(num);
	}



	loadImageOne.close();
	loadImageTwo.close();
}


void PBM::load(const char* path) {
	imageName = new char[strlen(path) + 1];
	for (int i = 0; i < strlen(path) + 1; i++) {
		imageName[i] = path[i];
	}

	ifstream load(path, ios::in);
	if (load.fail()) { cout << "Error"; return; }

	string _magicNum;
	int _width, _height, _range;

	load >> _magicNum;
	load >> _width >> _height;
	load >> _range;

	magicNum = _magicNum;
	width = _width;
	height = _height;
	range = _range;

	value.clear();

	int num;
	for (int i = 0; i < width * height; i++) {
		load >> num;
		value.push_back(num);
	}
	load.close();
}


void PBM::save() {
	ofstream save(imageName, ios::out);
	save << magicNum << endl;
	save << width << " " << height << endl;
	save << range << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int value = getValueAtPosition(j, i);
			save << value << " ";
		}
		save << endl;
	}
}

void PBM::saveAs(const char* path) {
	ofstream save(path, ios::out);
	save << magicNum << endl;
	save << width << " " << height << endl;
	save << range << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int value = getValueAtPosition(j, i);
			save << value << " ";
		}
		save << endl;
	}
}


void PBM::makeNegative() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setValueAtPosition(j, i, 1 - getValueAtPosition(j, i));
		}
	}
}

bool PBM::isMonochrome() {
	return true;
}

void PBM::makeMonochrome() { 
	return;
}

bool PBM::isAlreadyGrayscaled() { 
	return true;
}

void PBM::grayscale() { 
	return;
}

PBM::~PBM() {
	delete[] imageName;
}