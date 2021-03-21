#include "Renderer.h"

Renderer::Renderer() : maxDist{ DBL_MAX }, mt_engine{ 1 }, theta_d{ 0.0, 2.0 }, z_d{ -1.0, 1.0 } {

}

png::image<png::rgb_pixel_16>& Renderer::render(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene) {
	// https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
	double dist = maxDist;
	double ratio{ static_cast<double>(width) / height };
	Vector4D screen = scene.getCamera()->screen;
	image = png::image<png::rgb_pixel_16>{ width, height };

	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		//std::cout << "Progress: " << static_cast<int>(static_cast<double>(py) / image.get_height() * 100) << "%" << std::endl;
		double y{ (screen.w) + ((screen.y - screen.w) / image.get_height() * (static_cast<double>(py) + 0.5)) };  // spots on screen for ray to shoot through
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			double x{ (screen.x) + ((screen.z - screen.x) / image.get_width() * (static_cast<double>(px) + 0.5)) };  // spots on screen for ray to shoot through
			Vector3D pixel{ x + scene.getCamera()->position.x, y + scene.getCamera()->position.y, scene.getCamera()->position.z + 1 };
			Vector3D finalColor{ 0, 0, 0 };

			for (size_t l = 0; l < scene.getLights().size(); l++) {
				Ray ray{ scene.getCamera()->position, Vector3D::normalize(pixel - scene.getCamera()->position) };
				double reflection = 1;
				double lastN = 1;
				std::unique_ptr<Object>* lastObj{ nullptr };
				for (unsigned int i = 0; i < maxReflects; i++) {  // change to "while (true)" in order to reflect until nothing to reflect.
					double dist{ maxDist };
					std::unique_ptr<Object>* obj{ nullptr };
					obj = Object::nearestObject(scene.getObjects(), dist, ray);  // nearest object in ray's path
					if (!obj) {  // if it hits no objects
						break;
					}

					Vector3D intersection{ ray.position + ray.direction * dist };  // point of intersection
					if (i == 0 && l == 0) {
						finalColor = finalColor + (*obj)->getMaterial()->getInherent();
					}

					Vector3D normalVector = (*obj)->getNormal(intersection, ray);
					Vector3D shiftedPoint{ intersection + normalVector * 1e-12 };  // shifted so it doesn't detect the object as between the light source
					Vector3D lightVector = Vector3D::normalize(scene.getLights()[l]->position - intersection);
					Ray lightRay{ shiftedPoint, lightVector };

					double distanceToBetweenObject{ maxDist };
					Object::nearestObject(scene.getObjects(), distanceToBetweenObject, lightRay);
					Vector3D rgb{ 0.0, 0.0, 0.0 };

					if (Vector3D::magnitude(scene.getLights()[l]->position - shiftedPoint) < distanceToBetweenObject) {  // if no object is in the way
						// inherent color without need of light
						//rgb = rgb + (*obj)->getMaterial()->getInherent();

						rgb = BlinnPhong(obj, scene.getCamera(), lightVector, normalVector, intersection, scene.getLights()[l]);
						// ambient
						//rgb = rgb + ((*obj)->getMaterial()->getAmbient(intersection).multiply(scene.getLights()[l]->getMaterial()->getAmbient() * scene.getLights()[l]->getIntensityAt(intersection)));

						// diffuse
						//rgb = rgb + ((*obj)->getMaterial()->getDiffuse(intersection).multiply(scene.getLights()[l]->getMaterial()->getDiffuse() * scene.getLights()[l]->getIntensityAt(intersection))) * (lightVector * normalVector);

						// specular
						//Vector3D cameraVector{ Vector3D::normalize(scene.getCamera()->position - intersection) };
						//Vector3D H{ Vector3D::normalize(lightVector + cameraVector) };
						//rgb = rgb + (*obj)->getMaterial()->getSpecular(intersection).multiply(scene.getLights()[l]->getMaterial()->getSpecular() * scene.getLights()[l]->getIntensityAt(intersection)) * pow((normalVector * H), (*obj)->getMaterial()->getShininess(intersection) / 4);

					} else {

						// inherent color without need of light
						//rgb = rgb + (*obj)->getMaterial()->getInherent();
						
					}
					// reflection / refraction
					if ((*obj)->getMaterial()->getRefraction(intersection) < (*obj)->getMaterial()->getReflection(intersection)) {  // only doing one or the other for now
						// reflections
						finalColor = finalColor + rgb * reflection;
						reflection *= (*obj)->getMaterial()->getReflection(intersection);
						if (reflection == 0) {
							break;
						}
						ray = Ray{ shiftedPoint, Object::reflected(ray.direction, normalVector) };
					} else {
						// refractions
						finalColor = finalColor + rgb * reflection;
						reflection *= (*obj)->getMaterial()->getRefraction(intersection);
						if (reflection == 0) {
							break;
						}

						//snells law
						shiftedPoint = intersection - normalVector * 1e-12;  // go into the object itself
						const double n1n2 = lastN / (*obj)->getMaterial()->getIndex();
						Vector3D angleOfRefraction = ray.direction * (n1n2) + normalVector * ((n1n2) * (-ray.direction * normalVector) - sqrt(1 - pow(n1n2, 2) * (1 - pow(-ray.direction * normalVector, 2))));
						

						ray = Ray{ shiftedPoint, angleOfRefraction };

						if (!lastObj) {
							lastN = (*obj)->getMaterial()->getIndex();
							lastObj = obj;
						} else {
							lastN = 1;
							lastObj = nullptr;
						}

						
					}
				}
			}

			finalColor = Vector3D::clip(finalColor, 0, 1);
			finalColor = finalColor * 65535;
			image[image.get_height() - (py + 1)][px] = png::rgb_pixel_16{ static_cast<png::uint_16>(finalColor.x), static_cast<png::uint_16>(finalColor.y), static_cast<png::uint_16>(finalColor.z) };
		}
	}
	return image;
}

png::image<png::rgb_pixel_16>& Renderer::renderPathTracing(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene, unsigned int samples) {
	
	double ratio{ static_cast<double>(width) / height };
	Vector4D screen{ -1, 1 / ratio, 1, -1 / ratio };
	image = png::image<png::rgb_pixel_16>{ width, height };

	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		double y{ (screen.w) + ((screen.y - screen.w) / image.get_height() * (static_cast<double>(py) + 0.5)) };  // spots on screen for ray to shoot through
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			double x{ (screen.x) + ((screen.z - screen.x) / image.get_width() * (static_cast<double>(px) + 0.5)) };  // spots on screen for ray to shoot through
			Vector3D pixel{ x + scene.getCamera()->position.x, y + scene.getCamera()->position.y, scene.getCamera()->position.z + 1 };
			Vector3D finalColor{ 0, 0, 0 };
			for (unsigned int i = 0; i < samples; i++) {
				Ray ray{ scene.getCamera()->position, Vector3D::normalize(pixel - scene.getCamera()->position) };
				finalColor = finalColor + tracePath(ray, scene, 0, maxReflects);
			}
			finalColor = finalColor / samples;
			finalColor = Vector3D::clip(finalColor, 0, 1);
			finalColor = finalColor * 65535;
			image[image.get_height() - (py + 1)][px] = png::rgb_pixel_16{ static_cast<png::uint_16>(finalColor.x), static_cast<png::uint_16>(finalColor.y), static_cast<png::uint_16>(finalColor.z) };
		}
	}
	return image;
}

Vector3D Renderer::BlinnPhong(std::unique_ptr<Object>* obj, std::unique_ptr<Camera>& cam, const Vector3D& lightVector, const Vector3D& normalVector, const Vector3D& intersection, std::unique_ptr<Light>& light) {
	Vector3D rgb{ 0, 0, 0 };
	// ambient
	rgb = rgb + ((*obj)->getMaterial()->getAmbient(intersection).multiply(light->getMaterial()->getAmbient() * light->getIntensityAt(intersection)));

	// diffuse
	rgb = rgb + ((*obj)->getMaterial()->getDiffuse(intersection).multiply(light->getMaterial()->getDiffuse() * light->getIntensityAt(intersection))) * (lightVector * normalVector);

	// specular
	Vector3D cameraVector{ Vector3D::normalize(light->position - intersection) };
	Vector3D H{ Vector3D::normalize(lightVector + cameraVector) };
	rgb = rgb + (*obj)->getMaterial()->getSpecular(intersection).multiply(light->getMaterial()->getSpecular() * light->getIntensityAt(intersection)) * pow((normalVector * H), (*obj)->getMaterial()->getShininess(intersection) / 4);
	return rgb;
}

Vector3D Renderer::tracePath(Ray& ray, Scene& scene, unsigned int depth, unsigned int maxReflects) {
	if (depth >= maxReflects) {
		return Vector3D{ 0, 0, 0 };
	}

	double dist{ maxDist };
	std::unique_ptr<Object>* obj{ nullptr };
	obj = Object::nearestObject(scene.getObjects(), dist, ray);  // nearest object in ray's path
	if (!obj) {  // if it doesn't hit an object
		return Vector3D{ 0, 0, 0 };
	}

	Vector3D emittance = (*obj)->getMaterial()->getInherent();

	Vector3D intersection{ ray.position + ray.direction * dist };
	Vector3D shiftedPoint{ intersection + (*obj)->getNormal(intersection, ray) * 1e-6 };
	double theta = theta_d(mt_engine) * M_PI;
	double z = z_d(mt_engine);
	double k = sqrt(1 - z * z);
	Vector3D randomDirection{ k*cos(theta), k*sin(theta), z };
	//Vector3D randomDirection{ 0, 1, 0 };
	Ray newRay{ shiftedPoint, randomDirection };

	const double p = 1 / (2 * M_PI);  // new ray probablity

	// BRDF
	double cos_theta = newRay.direction * shiftedPoint;
	Vector3D BRDF = (*obj)->getMaterial()->getAmbient() / M_PI;

	Vector3D incoming = tracePath(newRay, scene, depth + 1, maxReflects);

	return emittance + (BRDF.multiply(incoming) * cos_theta / p);
}