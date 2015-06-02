#include "primitive.hpp"
#include "mesh.hpp"
#include <cmath>
#include <math.h>
#include <vector>

Primitive::~Primitive()
{
}

Sphere::Sphere()
{
	s = new NonhierSphere(Point3D(0.0, 0.0, 0.0), 1.0);
}

Sphere::~Sphere()
{
	delete s;
}

IntSection Sphere::intsect(Ray ray){
	return s->intsect(ray);
}

Cube::Cube()
{
	c = new NonhierBox(Point3D(0.0, 0.0, 0.0), 1.0);
}

Cube::~Cube()
{
	delete c;
}

IntSection Cube::intsect(Ray ray){


    //Ray r = ray;
    //r.dir.normalize();

	return c->intsect(ray);
}

NonhierSphere::~NonhierSphere()
{
}

IntSection NonhierSphere::intsect(Ray ray) { 

    Ray r = ray;
    //r.dir.normalize();

    IntSection i;

    double t;
    double t1;
    double t2;

    double x0 = ray.p[0];
    double y0 = ray.p[1];
    double z0 = ray.p[2];

    double xd = ray.dir[0];
    double yd = ray.dir[1];
    double zd = ray.dir[2];

    double xc = m_pos[0];
    double yc = m_pos[1];
    double zc = m_pos[2];

    //double a = pow(xd,2) + pow(yd,2) + pow(zd,2); 
    //double b = 2 * (xd * (x0 - xc) + yd * (y0 - yc) + zd * (z0 - zc));
    //double c = pow((x0 - xc),2) + pow((y0 - yd),2) + pow((z0 - zd),2) - pow((m_radius),2);

    //double d = pow(b,2) - 4 * a * c;

    double a = ray.dir.dot(ray.dir);
    Vector3D dist = m_pos - ray.p; 
    double b = r.dir.dot( dist);
    double d = b*b - a *( dist.dot( dist) - m_radius * m_radius);

    bool ishit;

    if ( d < 0 ){

      ishit = false;

      return i;

    }else {

      ishit = true;
    }

    t1 = (b + sqrt(d))/a;
    t2 = (b - sqrt(d))/a;
//std::cerr << "t1:" << t1 << std::endl;
//std::cerr << "t2:" << t2 << std::endl;


    //t1 = (-b + sqrt(pow(b,2) - 4 * a * c))/2 * a;
    //t2 = (-b - sqrt(pow(b,2) - 4 * a * c))/2 * a;

    if (t1 > 0){
      t = t1;
    }

    if ( (t2 > 0) && (t2 < t) ){
      t = t2;
    }

    if (t < 0) { return i; }


    //if ( t1 < t2 ) {
    //  t = t1;
    //}else{
    //  t = t2;
    //}
//std::cerr << "t:" << t << std::endl;


    i.t = t;
    i.p = ray.p + t * r.dir;
    i.ishit = ishit;

    Vector3D n = i.p - m_pos;
    n.normalize();
    i.n = n;

    return i;
    
}

NonhierBox::NonhierBox(const Point3D& pos, double size)
    : m_pos(pos), m_size(size) {

    double xc = m_pos[0];
    double yc = m_pos[1];
    double zc = m_pos[2];

    std::vector<Point3D> v;

    v.push_back(Point3D(xc,yc,zc));
    v.push_back(Point3D(xc,yc,zc + m_size));
    v.push_back(Point3D(xc + m_size,yc,zc + m_size));
    v.push_back(Point3D(xc + m_size,yc,zc));

    v.push_back(Point3D(xc,yc + m_size,zc));
    v.push_back(Point3D(xc,yc + m_size,zc + m_size));
    v.push_back(Point3D(xc + m_size,yc + m_size,zc + m_size));
    v.push_back(Point3D(xc + m_size,yc + m_size ,zc));

    std::vector<std::vector<int> > faces;

    int face[6][4] = {
				{3,2,1,0},
				{3,2,6,7},
				{2,1,5,6},
				{1,0,4,5},
				{0,3,7,4},
				{4,7,6,5}
    };

    for(int i = 0; i < 6; i++) {

	std::vector<int> poly;
	for(int j = 0; j < 4; j++) {
	    poly.insert(poly.begin(),face[i][j]);
	}
	faces.push_back(poly);
    }

    mesh = new Mesh(v, faces);

}


NonhierBox::~NonhierBox()
{
	delete mesh;
}

IntSection NonhierBox::intsect(Ray ray){
    return mesh->intsect(ray);
}
