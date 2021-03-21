#include "Camera.h"

Camera::Camera(Vector3D pos, Vector3D ori, double r) : position{ pos }, orientation{ ori }, ratio{ r }, screen{ -1, 1 / r, 1, -1 / r }, zoom{ 1.0 } {

}

Camera::Camera(Vector3D pos, Vector3D ori, double r, double z) : position{ pos }, orientation{ ori }, ratio{ r }, screen{ -1 / z, 1 / r / z, 1 / z, -1 / r / z }, zoom{ z } {

}