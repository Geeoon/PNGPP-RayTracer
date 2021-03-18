#include "Camera.h"

Camera::Camera(Vector3D pos, Vector3D ori, double r) : position{ pos }, orientation{ ori }, ratio{ r }, screen{ -1, 1 / r, 1, -1 / r } {

}