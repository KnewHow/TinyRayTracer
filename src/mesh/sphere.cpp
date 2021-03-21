#include "sphere.h"

#include <cmath>

Sphere::Sphere(const vec3f& c, float r)
    :center(c), radius(r){}

Sphere::Sphere(const vec3f& c, float r, const Material& m)
    :center(c), radius(r), material(m) {}

Sphere::~Sphere(){}

std::optional<IntersectResult> Sphere::rayIntersect(const vec3f& orig, const vec3f& d) const {
    vec3f L = center - orig;
    float tca = L * d;
    float d2 = L * L - tca * tca;
    if(d2 > radius * radius) return std::nullopt;
    float thc = sqrtf(radius * radius - d2);
    float t = tca - thc;
    float t1 = tca + thc;
    if(t < 0) t = t1;
    if(t < 0)  return std::nullopt;
    vec3f hitPoint = orig + t * d;
    vec3f normal = (hitPoint - center).normalize();
    return IntersectResult{t, hitPoint, material, normal};
}