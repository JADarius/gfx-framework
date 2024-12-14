#include "Hitbox.h"

Hitbox::Hitbox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) : 
	xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax) {}

Hitbox::~Hitbox() {}

float Hitbox::getXMin() {
	return xMin;
}

float Hitbox::getXMax() {
	return xMax;
}

float Hitbox::getYMin() {
	return yMin;
}

float Hitbox::getYMax() {
	return yMax;
}

float Hitbox::getZMin() {
	return zMin;
}

float Hitbox::getZMax() {
	return zMax;
}
