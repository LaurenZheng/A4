#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"
#include "material.hpp"

class Mesh;

class Ray {
  public:
  Point3D p;  // the starting point of the ray
  Vector3D dir;   // which direction the ray is pointing at
};

class IntSection {
  public:
  double t;       // the distance between the intersection point and the starting point of the ray, when the ray hit, find the smallest t, which is the closet to the starting point of the ray
  Point3D p;      // the intersection point
  bool ishit;     // a flag, whether the ray hits the object or not
  Vector3D n;     // normal
  Material* m;
  IntSection():
    t(-1.0),
    ishit(false),
    m(NULL){};
};

class Primitive {
public:
  virtual ~Primitive();

  virtual IntSection intsect(Ray ray) = 0;
};



class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();

  virtual IntSection intsect(Ray ray);

private:
  Point3D m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size);
  //  : m_pos(pos), m_size(size)
  //{
  //}
  
  virtual ~NonhierBox();

  virtual IntSection intsect(Ray ray);
  

private:
  Point3D m_pos;
  double m_size;
  Mesh* mesh;
};

class Sphere : public Primitive {
public:
  Sphere();
  virtual ~Sphere();

  virtual IntSection intsect(Ray ray);
private:
  NonhierSphere* s;
};

class Cube : public Primitive {
public:
  Cube();
  virtual ~Cube();

  virtual IntSection intsect(Ray ray);
private:
  NonhierBox* c;
};


#endif
