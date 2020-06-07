#pragma once
#include "image.h"
#include "pbm.h"
#include "pgm.h"
#include "ppm.h"

class ImageFactory {
public:
	static Image* make(const char*);
};


/*
class UnknownImageType : public exception {
public:
	UnknownImageType(const char*&);
	const char* what() const noexcept;
private:
	char* message;
};

UnknownImageType::UnknownImageType(const char*& type) {
	char temp[50] = "Unknown cage type. ";
	message = new char[strlen(temp) + 1];
	for (int i = 0; i < strlen(temp) + 1; i++) {
		message[i] = temp[i];
	}
}

const char* UnknownImageType::what() const noexcept {
	return message;
}*/

