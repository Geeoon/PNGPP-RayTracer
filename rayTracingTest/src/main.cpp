#include <png++/png.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "vector/Vector4D.h"
#include "vector/Vector3D.h"
#include "objects/Plane.h"
#include "objects/Object.h"
#include "objects/Sphere.h"
#include "Light.h"

#define M_PI 3.14159265358979323846264338327950288

int main() {
	const double maxDist = DBL_MAX;
	const unsigned int maxReflects = 5;
	unsigned int width{ 1920 };
	unsigned int height{ 1080 };
	double ratio{ static_cast<double>(width) / height };
	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 0, 0, 4 }, Vector3D{ 0.1, 0.0, 0.0 }, Vector3D{ 0.7, 0.0, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ 5, 0, 4 }, Vector3D{ 0.1, 0.0, 0.1 }, Vector3D{ 0.7, 0.0, 0.7 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Sphere>(2, Vector3D{ -5, 0, 4 }, Vector3D{ 0.0, 0.1, 0.0 }, Vector3D{ 0.0, 0.6, 0.0 }, Vector3D{ 0.1, 0.1, 0.1 }, 100.0, 0.5));
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, -2, 0 }, Vector3D{ 0.4, 0.4, 0.4 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0.1, 0.1, 0.1 }, 0, 0));  // floor
	objects.push_back(std::make_unique<Plane>(Vector3D{ 0, 101, 0 }, Vector3D{ 0.85, 0.91, 1 }, Vector3D{ 0, 0, 0 }, Vector3D{ 0, 0, 0 }, 0, 0));  // sky
	
	std::vector<std::unique_ptr<Light>> lights;
	lights.push_back(std::make_unique<Light>(Vector3D{ 100, 100, -80 }, Vector3D{ .85, .91, 1 }, Vector3D{ .85, .91, 1 }, Vector3D{ .85, .91, 1 }));
	//lights.push_back(std::make_unique<Light>(Vector3D{ 20, 5, -20 }, Vector3D{ .5, .5, .5 }, Vector3D{ .5, .5, .5 }, Vector3D{ .5, .5, .5 }));

	Vector3D cameraPosition{ 0, 1, -5 };
	Vector3D cameraAngle{ 0, 0, 0 };  //in radians

	Vector4D screen{ -1, 1 / ratio, 1, -1 / ratio };  // left, top, right, bottom

	png::image<png::rgb_pixel_16> image{ width, height };

	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			image[py][px] = png::rgb_pixel_16{ 0, 0, 0 };  // set all pixles to black by default
		}
	}

	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		//std::cout << "Progress: " << static_cast<int>(static_cast<double>(py) / image.get_height() * 100) << "%" << std::endl;
		double y{ (screen.w) + ((screen.y - screen.w) / image.get_height() * (static_cast<double>(py) + 0.5)) };  // spots on screen for ray to shoot through
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			double x{ (screen.x) + ((screen.z - screen.x) / image.get_width() * (static_cast<double>(px) + 0.5)) };  // spots on screen for ray to shoot through
			Vector3D pixel{ x + cameraPosition.x, y + cameraPosition.y, cameraPosition.z + 1 };
			Vector3D finalColor{ 0, 0, 0 };
			for (size_t l = 0; l < lights.size(); l++) {
			Ray ray{ cameraPosition, Vector3D::normalize(pixel - cameraPosition) };

			double reflection = 1;
				for (auto i = 0; i < maxReflects; i++) {
					double dist{ maxDist };
					std::unique_ptr<Object>* obj{ nullptr };
					obj = Object::nearestObject(objects, dist, ray);
					if (obj) {  // if it hits an object
						Vector3D intersection{ ray.position + ray.direction * dist };  // point of intersection


						// checking lighting
						Vector3D normalVector = (*obj)->getNormal(intersection, ray);
						Vector3D shiftedPoint{ intersection + normalVector * 1e-5 };  // shifted so it doesn't detect itself as between the light source
						Vector3D lightVector = Vector3D::normalize(lights[l]->position - shiftedPoint);
						Ray lightRay{ shiftedPoint, lightVector };

						double distanceToBetweenObject{ maxDist };
						Object::nearestObject(objects, distanceToBetweenObject, lightRay);

						if (Vector3D::magnitude(lights[l]->position - shiftedPoint) < distanceToBetweenObject) {  // if no objet is in the way
							Vector3D rgb{ 0.0, 0.0, 0.0 };

							// ambient
							rgb = rgb + ((*obj)->getAmbient().multiply(lights[l]-> ambient));

							// diffuse
							rgb = rgb + ((*obj)->getDiffuse().multiply(lights[l]->diffuse)) * (lightVector * normalVector);

							//specular
							Vector3D cameraVector{ Vector3D::normalize(cameraPosition - intersection) };
							Vector3D H{ Vector3D::normalize(lightVector + cameraVector) };
							rgb = rgb + (*obj)->getSpecular().multiply(lights[l]->specular) * pow((normalVector * H), (*obj)->getShininess() / 4);


							//reflection
							finalColor = finalColor + rgb * reflection;
							reflection *= (*obj)->getReflection();

							ray = Ray{ shiftedPoint, Object::reflected(ray.direction, normalVector) };
						}
					} else {
						break;
					}
				}
			}
			finalColor = Vector3D::clip(finalColor, 0, 1);
			finalColor = finalColor * 65535;
			image[image.get_height() - (py + 1)][px] = png::rgb_pixel_16{ static_cast<png::uint_16>(finalColor.x), static_cast<png::uint_16>(finalColor.y), static_cast<png::uint_16>(finalColor.z) };
		}
	}
	
	

	image.write("output.png");
	
	return 0;
}