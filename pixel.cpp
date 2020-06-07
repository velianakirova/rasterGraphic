#pragma once
#include "pixel.h"

Pixel::Pixel() : r(0), g(0), b(0) {};

Pixel& Pixel::operator=(const Pixel& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	return*this;
}