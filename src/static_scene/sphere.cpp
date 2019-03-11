#include "sphere.h"

#include <cmath>

#include  "../bsdf.h"
#include "../misc/sphere_drawing.h"

namespace CGL { namespace StaticScene {

bool Sphere::test(const Ray& r, double& t1, double& t2) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection test.
  // Return true if there are intersections and writing the
  // smaller of the two intersection times in t1 and the larger in t2.
  double a = dot(r.d, r.d);
  double b = 2*dot(r.o - o, r.d);
  double c = dot(r.o - o, r.o - o) - r2;
  double delta = b*b - 4*a*c;
  if (delta < 0) return false;
  t1 = (-b - sqrt(delta))/(2*a);
  t2 = (-b + sqrt(delta))/(2*a);
  if (t1 < r.min_t || t2 > r.max_t)
    return false;
  return true;
}

bool Sphere::intersect(const Ray& r) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note that you might want to use the the Sphere::test helper here.
  double t1, t2;
  bool doCross = test(r, t1, t2);
  if (doCross)
    r.max_t = t1;
  return doCross;
}

bool Sphere::intersect(const Ray& r, Intersection *i) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note again that you might want to use the the Sphere::test helper here.
  // When an intersection takes place, the Intersection data should be updated
  // correspondingly.
  double t1, t2;
  bool doCross = test(r, t1, t2);
  if (doCross) {
    r.max_t = t1;
    i->t = t1;
    i->primitive = this;
    Vector3D point = r.o + t1*r.d;
    i->n = (point - o)/(point - o).norm();
    i->bsdf = get_bsdf();
  }
  return doCross;  
}

void Sphere::draw(const Color& c, float alpha) const {
  Misc::draw_sphere_opengl(o, r, c);
}

void Sphere::drawOutline(const Color& c, float alpha) const {
    //Misc::draw_sphere_opengl(o, r, c);
}


} // namespace StaticScene
} // namespace CGL
