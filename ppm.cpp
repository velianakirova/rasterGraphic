#pragma once
#include "ppm.h"

PPM::PPM() {
	width = 0; 
	height = 0;
	range = 0; 
	magicNum = "P3"; 
	imageName = nullptr; 
}

Pixel& PPM::getPixelAtPosition(int row, int column) {
	return pixels[(column * width) + row];
}

int PPM::getWidth() {
	return width;
}

int PPM::getHeight() {
	return height;
}

char* PPM::getImageName() {
	return imageName;
}

string PPM::getMagicNum() {
	return magicNum;
}

void PPM::setPixelAtPosition(int row, int column, Pixel& pixel) {
	pixels[(column * width) + row] = pixel;
}

void PPM::makeHorizontalCollage(const char* imageOne, const char* imageTwo, const char* collageName) {
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

	pixels.clear();
	Pixel temp;
	int R, G, B;


	for (int i = 0; i < width * height; i++) {
		for (int j = 0; j < _widthOne; j++) {

			loadImageOne >> R >> G >> B;
			temp.r = R;
			temp.g = G;
			temp.b = B;
			pixels.push_back(temp);

		}
		for (int j = _widthOne; j < width; j++) {
			loadImageTwo >> R >> G >> B;
			temp.r = R;
			temp.g = G;
			temp.b = B;
			pixels.push_back(temp);
		}

	}

	loadImageOne.close();
	loadImageTwo.close();
}

void PPM::makeVerticalCollage(const char* imageOne, const char* imageTwo, const char* collageName) {
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

	pixels.clear();
	Pixel temp;
	Pixel black;
	int R, G, B;
	for (int i = 0; i < _widthOne * _heightOne; i++) {
		loadImageOne >> R >> G >> B;
		temp.r = R;
		temp.g = G;
		temp.b = B;
		pixels.push_back(temp);

	}
	for (int i = _widthOne * _heightOne; i < width * height; i++) {
		loadImageTwo >> R >> G >> B;
		temp.r = R;
		temp.g = G;
		temp.b = B;
		pixels.push_back(temp);
	}



	loadImageOne.close();
	loadImageTwo.close();
}


void PPM::load(const char* path) {
	imageName = new char[strlen(path) + 1];
	for (int i = 0; i < strlen(path) + 1; i++) {
		imageName[i] = path[i];
	}
	ifstream load(path, ios::in);
	if (load.fail()) { cout << "Error"; return; }
	string _magicNum;
	int _width, _height, _range;

	load >> _magicNum;
	load >> _width >> _height >> _range;

	magicNum = _magicNum;
	width = _width;
	height = _height;
	range = _range;

	pixels.clear();

	Pixel temp;
	int R, G, B;
	for (int i = 0; i < width * height; i++) {
		load >> R >> G >> B;
		temp.r = R;
		temp.g = G;
		temp.b = B;

		pixels.push_back(temp);
	}
	load.close();
}

void PPM::save() {
	ofstream save(imageName, ios::out);
	save << magicNum << endl;
	save << width << " " << height << endl;
	save << range << endl;

	for (int i = 0; i < width * height; i++) {
		save << pixels[i].r << " " << pixels[i].g << " " << pixels[i].b << endl;
	}

}

void PPM::saveAs(const char* path) {
	ofstream save(path, ios::out);
	save << magicNum << endl;
	save << width << " " << height << endl;
	save << range << endl;

	for (int i = 0; i < width * height; i++) {
		save << pixels[i].r << " " << pixels[i].g << " " << pixels[i].b << endl;
	}
}

bool PPM::isAlreadyGrayscaled() {
	for (int i = 0; i < width * height; i++) {
		if (pixels[i].r != pixels[i].b && pixels[i].b != pixels[i].g && pixels[i].r != pixels[i].g) {
			cout << "Not yet\n";
			return false;
		}
	}
	return true;
}

void PPM::grayscale() {
	for (int i = 0; i < width * height; i++) {
		if (pixels[i].r > pixels[i].g && pixels[i].r > pixels[i].b) {
			pixels[i].g = pixels[i].r;
			pixels[i].b = pixels[i].r;
		}
		else if (pixels[i].g > pixels[i].r && pixels[i].g > pixels[i].b) {
			pixels[i].r = pixels[i].g;
			pixels[i].b = pixels[i].g;
		}
		else if (pixels[i].b > pixels[i].r && pixels[i].b > pixels[i].g) {
			pixels[i].g = pixels[i].b;
			pixels[i].r = pixels[i].b;
		}


	}
}

bool PPM::isMonochrome() {
	for (int i = 0; i < width * height; i++) {
		if ((pixels[i].r != 0 && pixels[i].g != 0 && pixels[i].b != 0) || (pixels[i].r != 255 && pixels[i].g != 255 && pixels[i].b != 255)) {
			cout << "false";
			return false;
		}
	}
	cout << "true";
	return true;
}

void PPM::makeMonochrome() {
	for (int i = 0; i < width * height; i++) {
		if (pixels[i].r != 255 || pixels[i].g != 255 || pixels[i].b != 255) {
			pixels[i].r = 0;
			pixels[i].g = 0;
			pixels[i].b = 0;
		}
	}
}

void PPM::makeNegative() {
	for (int i = 0; i < width * height; i++) {
		pixels[i].r = 255 - pixels[i].r;
		pixels[i].g = 255 - pixels[i].g;
		pixels[i].b = 255 - pixels[i].b;
	}
}

PPM::~PPM() {
	delete[] imageName;
}