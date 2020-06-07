#pragma once
#include "imageFactory.h"

bool isEqualto1(const char* strOne, const char* strTwo) {
	int lenOne = strlen(strOne);
	int lenTwo = strlen(strTwo);
	if (lenOne != lenTwo) return false;
	for (int i = 0; i < lenOne; i++) {
		if (strOne[i] != strTwo[i]) return false;
	}
	return true;
}


Image* ImageFactory::make(const char* extension) {
	Image* newImage = nullptr;
	if (isEqualto1(extension, "pbm")) {
		newImage = new PBM();
	}
	else if (isEqualto1(extension, "pgm")) {
		newImage = new PGM();
	}
	else if (isEqualto1(extension, "ppm")) {
		newImage = new PPM();
	}
	else {
		//throw UnknownImageType(extension);
		cout << "\nUnknown image type.\n";
	}

	return newImage;
}