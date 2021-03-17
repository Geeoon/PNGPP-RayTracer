#include "Light.h"

Light::Light(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp) : position{ pos }, ambient{ am }, diffuse{ di }, specular{ sp }, intensity{ 1.0 } {

}

Light::Light(Vector3D pos, Vector3D am, Vector3D di, Vector3D sp, double in) : position{ pos }, ambient{ am }, diffuse{ di }, specular{ sp }, intensity{ in } {

}

double Light::getIntensityAt(Vector3D point) {
	return intensity;
}