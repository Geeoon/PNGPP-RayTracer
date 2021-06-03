#include "Renderer.h"

Renderer::Renderer() : maxDist{ DBL_MAX }, mt_engine{ 1 }, theta_d{ 0.0, 2.0 }, z_d{ -1.0, 1.0 }, u_d{ 0.0, 1.0 } {

}

png::image<png::rgb_pixel_16>& Renderer::renderMultithread(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene) {
	auto dist = maxDist;
	auto ratio{ static_cast<double>(width) / height };
	auto screen = scene.getCamera()->screen;
	image = png::image<png::rgb_pixel_16>{ width, height };
	std::vector<int> outputImageRGB;
	outputImageRGB.resize(100);
	concurrency::array_view<int, 2> outputRGB{ static_cast<int>(image.get_height()), static_cast<int>(image.get_width()), outputImageRGB };
	std::array<const double, 3> posArray{ { scene.getCamera()->position.x, scene.getCamera()->position.y, scene.getCamera()->position.z } };
	concurrency::array_view<const double, 1> cameraPos{ 3, posArray };
	Scene* scene2 = &scene;
	concurrency::parallel_for_each(outputRGB.extent,
		[&](concurrency::index<2> idx) restrict(amp) {
		int y = idx[0];
		int x = idx[1];

	});

	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		auto y{ (screen.w) + ((screen.y - screen.w) / image.get_height() * (static_cast<double>(py) + 0.5)) };  // spots on screen for ray to shoot through
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			auto x{ (screen.x) + ((screen.z - screen.x) / image.get_width() * (static_cast<double>(px) + 0.5)) };  // spots on screen for ray to shoot through
			Vector3D pixel{ x + scene.getCamera()->position.x, y + scene.getCamera()->position.y, scene.getCamera()->position.z + 1 };
			Vector3D finalColor{ 0, 0, 0 };
			Ray ray{ scene.getCamera()->position, Vector3D::normalize(pixel - scene.getCamera()->position) };
			finalColor = renderRay(scene, maxReflects, ray);
			finalColor = Vector3D::clip(finalColor, 0, 1);
			finalColor = finalColor * 65535;
			image[image.get_height() - (py + 1)][px] = png::rgb_pixel_16{ static_cast<png::uint_16>(finalColor.x), static_cast<png::uint_16>(finalColor.y), static_cast<png::uint_16>(finalColor.z) };
		}
	}
	return image;
}

png::image<png::rgb_pixel_16>& Renderer::render(unsigned int maxReflects, unsigned int width, unsigned int height, Scene& scene) {
	auto dist = maxDist;
	auto ratio{ static_cast<double>(width) / height };
	auto screen = scene.getCamera()->screen;
	image = png::image<png::rgb_pixel_16>{ width, height };
	for (png::uint_32 py = 0; py < image.get_height(); py++) {
		auto y{ (screen.w) + ((screen.y - screen.w) / image.get_height() * (static_cast<double>(py) + 0.5)) };  // spots on screen for ray to shoot through
		for (png::uint_32 px = 0; px < image.get_width(); px++) {
			auto x{ (screen.x) + ((screen.z - screen.x) / image.get_width() * (static_cast<double>(px) + 0.5)) };  // spots on screen for ray to shoot through
			Vector3D pixel{ x + scene.getCamera()->position.x, y + scene.getCamera()->position.y, scene.getCamera()->position.z + 1 };
			Vector3D finalColor{ 0, 0, 0 };
			Ray ray{ scene.getCamera()->position, Vector3D::normalize(pixel - scene.getCamera()->position) };
			finalColor = renderRay(scene, maxReflects, ray);
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
			Ray ray{ scene.getCamera()->position, Vector3D::normalize(pixel - scene.getCamera()->position) };

			for (unsigned int i = 0; i < samples; i++) {
				finalColor = finalColor + tracePath(ray, scene, 1.0, 0, maxReflects);
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

Vector3D Renderer::tracePath(Ray& ray, Scene& scene, double index, unsigned int depth, unsigned int maxReflects) {
	if (depth >= maxReflects) {
		return Vector3D{ 0, 0, 0 };
	}

	Vector3D output{ 0, 0, 0 };
	double dist{ maxDist };
	std::unique_ptr<Object>* obj{ nullptr };
	obj = Object::nearestObject(scene.getObjects(), dist, ray);  // nearest object in ray's path
	if (!obj) {  // if it hits no objects
		return Vector3D{ 0, 0, 0 };
	}
	Vector3D intersection{ ray.position + ray.direction * dist };  // point of intersection
	Vector3D normal{ (*obj)->getNormal(intersection, ray) };
	Vector3D shiftedPoint{ intersection + normal * 1e-12 };
	Vector3D direction{ 0, 1, 0 };
	
	double reflectance{ (*obj)->getMaterial()->getReflection(intersection) };  // used to determine how much of a reflected image should be on top of the object; basically a glossy finish on top
	double refractance{ (*obj)->getMaterial()->getRefraction(intersection) };
	const double shininess{ (*obj)->getMaterial()->getShininess(intersection) };  // used to determine how much of the light is reflected (0 = random direction, perfectly diffuse; 1 = reflection, perfectly reflective)
	const double indexOfRefraction{ (*obj)->getMaterial()->getIndex(intersection) };

	if (refractance > 0) {
		reflectance = reflectanceFresnel(index, indexOfRefraction, normal, ray.direction);
		refractance = 1 - reflectance;
		if (index != 1.0) {
			Vector3D shiftedPointRef{ intersection + normal * 1e-12 };
			Ray refracted{ shiftedPointRef, refract(index, 1.0, normal, ray.direction) };
			output = output + tracePath(refracted, scene, 1.0, depth, maxReflects);
		} else {
			Vector3D shiftedPointRef{ intersection - normal * 1e-12 };
			Ray refracted{ shiftedPointRef, refract(index, indexOfRefraction, normal, ray.direction) };
			output = output + tracePath(refracted, scene, indexOfRefraction, depth, maxReflects);
		}
	}

	if (reflectance > 0) {
		Vector3D reflectionDirection{ Object::reflected(ray.direction, normal) };
		Ray reflected{ shiftedPoint, reflectionDirection };
		output = output + tracePath(reflected, scene, 1.0, depth + 1, maxReflects) * reflectance;
	}

	direction = randomUnitVector3D();  // computationally expensive but there is no bias.

	Ray outgoingRay{ shiftedPoint, direction };  
	
	// ambient is color and specular is emmitance
	output = output + (*obj)->getMaterial()->getSpecular(intersection) + tracePath(outgoingRay, scene, index, depth + 1, maxReflects).multiply((*obj)->getMaterial()->getAmbient(intersection));
	return output;
}

Vector3D Renderer::refract(double n1, double n2, const Vector3D& normal, const Vector3D& incident) {
	const double n{ n1 / n2 };
	const double cosI{ -(normal * incident) };
	const double sinT2{ n * n * (1.0 - cosI * cosI) };
	if (sinT2 > 1.0) {
		return Vector3D{ 0, 0, 0 };  // reflect
	}
	const double cosT{ sqrt(1.0 - sinT2) };
	return incident * n + normal * (n * cosI - cosT);
}

Vector3D Renderer::renderRay(Scene& scene, double maxReflects, const Ray& r) {
	// https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
	Vector3D finalColor{ 0, 0, 0 };
	Ray ray{ r };
	for (size_t l{ 0 }; l < scene.getLights().size(); l++) {
		ray = r;
		double reflection{ 1.0 };
		double lastN{ 1.0 };
		std::unique_ptr<Object>* lastObj{ nullptr };
		for (unsigned int i{ 0 }; i < maxReflects; i++) {  // change to "while (true)" in order to reflect until nothing to reflect.
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

			Vector3D normalVector{ (*obj)->getNormal(intersection, ray) };
			Vector3D shiftedPoint{ intersection + normalVector * 1e-12 };  // shifted so it doesn't detect the object as between the light source
			Vector3D lightVector{ Vector3D::normalize(scene.getLights()[l]->position - intersection) };
			Ray lightRay{ shiftedPoint, lightVector };

			double distanceToBetweenObject{ maxDist };
			Object::nearestObject(scene.getObjects(), distanceToBetweenObject, lightRay);
			Vector3D rgb{ 0.0, 0.0, 0.0 };

			if (Vector3D::magnitude(scene.getLights()[l]->position - shiftedPoint) < distanceToBetweenObject) {  // if no object is in the way

				rgb = rgb + BlinnPhong(obj, scene.getCamera(), lightVector, normalVector, intersection, scene.getLights()[l]);

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
			} else {  // refractinos
				//snells law
				shiftedPoint = intersection - normalVector * 1e-12;  // go into the object itself
				const double n2{ (*obj)->getMaterial()->getIndex() };
				const double n1n2{ lastN / n2 };

				//Vector3D angleOfRefraction{ ray.direction * (n1n2)+normalVector * ((n1n2) * (-ray.direction * normalVector) - sqrt(1 - pow(n1n2, 2) * (1 - pow(-ray.direction * normalVector, 2)))) };
				Vector3D angleOfRefraction{ refract(lastN, n2, normalVector, ray.direction) };

				if (angleOfRefraction != Vector3D{ 0, 0, 0 }) {
					finalColor = finalColor + rgb * reflection;

					double reflectance{ reflectanceFresnel(lastN, n2, normalVector, ray.direction) };
					reflection *= (*obj)->getMaterial()->getRefraction(intersection) * (1 - reflectance);
					if (reflection == 0) {
						break;
					}

					ray = Ray{ shiftedPoint, angleOfRefraction };

					if (!lastObj) {
						if (reflectance > 0) {
							Ray reflectedRay = Ray{ intersection + normalVector * 1e-12, Object::reflected(ray.direction, normalVector) };
							finalColor = finalColor + renderRay(scene, maxReflects, reflectedRay) * reflectance;
						}
						lastN = n2;
						lastObj = obj;
					} else {
						if (reflectance > 0) {
							Ray reflectedRay = Ray{ intersection - normalVector * 1e-12, Object::reflected(ray.direction, normalVector) };
							finalColor = finalColor + renderRay(scene, maxReflects, reflectedRay) * reflectance;
						}
						lastN = 1;
						lastObj = nullptr;
					}
				} else {
					finalColor = finalColor + rgb * reflection;
					reflection *= (*obj)->getMaterial()->getReflection(intersection);
					if (reflection == 0) {
						break;
					}
					ray = Ray{ shiftedPoint, Object::reflected(ray.direction, normalVector) };
				}
			}
		}
	}
	return finalColor;
}

void Renderer::renderRay(Scene& scene, double maxReflects, const Ray& r, Vector3D* output) {
	*output = renderRay(scene, maxReflects, r);
}

Vector3D Renderer::randomUnitVector3D() {  // computationally expensive
	const double phi{ theta_d(mt_engine) * M_PI };
	const double costheta{ z_d(mt_engine) };
	const double u{ u_d(mt_engine) };
	const double theta{ acos(costheta) };
	const double r{ std::cbrt(u) };
	return Vector3D{ r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta) };
}
double Renderer::reflectanceFresnel(double n1, double n2, const Vector3D& normal, const Vector3D& incident) {
	const double n = n1 / n2;
	const double cosI = -(normal * incident);
	const double sinT2 = n * n * (1.0 - cosI * cosI);
	if (sinT2 > 1.0) {
		return 1.0;
	}
	const double cosT = sqrt(1.0 - sinT2);
	const double r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 * cosT);
	const double rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
	return (r0rth * r0rth + rPar * rPar) / 2.0;
}

double Renderer::calculateSchlick(double n1, double n2, const Vector3D& normal, const Vector3D& incident) {
	double r0{ (n1 - n2) / (n1 + n2) * (n1 - n2) / (n1 + n2) };
	r0 *= r0;
	double cosX = -(normal * incident);
	if (n1 > n2) {
		const double n = n1 / n2;
		const double sinT2 = n * n * (1.0 - (cosX) * (cosX));
		if (sinT2 > 1.0) {
			return 1.0;
		}
		cosX = sqrt(1.0 - sinT2);
	}
	const double x = 1.0 - cosX;
	return r0 + (1.0 - r0) * x * x * x * x * x;
}