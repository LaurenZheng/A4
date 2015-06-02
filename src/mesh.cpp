#include "mesh.hpp"
#include <iostream>
#include <limits.h>

Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
    double minX = INT_MAX;
    double minY = INT_MAX;
    double minZ = INT_MAX;
    double maxX = INT_MIN;
    double maxY = INT_MIN;
    double maxZ = INT_MIN	;
    for (unsigned int i = 0 ; i < m_verts.size() ; ++i) {
	Point3D v = m_verts[i];
	if (v[0] < minX) { 
	    minX = v[0]; 
	}
	if (v[0] > maxX) { 
	    maxX = v[0]; 
	}
	if (v[1] < minY) { 
	    minY = v[1]; 
	}
	if (v[1] > maxY) { 
	    maxY = v[1]; 
        }
	if (v[2] < minZ) { 
	    minZ = v[2]; 
        }
	if (v[2] > maxZ) { 
	    maxZ = v[2]; 
        }	
    }
    Point3D maxP(maxX, maxY, maxZ);
    Point3D minP(minX, minY, minZ);
    Point3D center((maxX+minX)/2, (maxY+minY)/2 , (maxZ+minZ)/2);
    Vector3D radius = maxP - minP;
    bsphere = new NonhierSphere(center, radius.length()/2 );

    //show the bounding sphere
    //GeometryNode* gsphere = new GeometryNode("bsphere", bsphere);
    //PhongMaterial* pm = new PhongMaterial({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25);
    //gsphere->set_material(pm);

    //s->add_child(gsphere);

}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";
  
  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin()) std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}


IntSection intpoly(Ray ray, std::vector<Point3D> poly) {

    IntSection i;

    Ray r = ray;
    //r.dir.normalize();

    //from course notes p122
    Point3D v0 = poly[0];
    Point3D v1 = poly[1];
    Point3D v2 = poly[2];

    Vector3D n = (v2 - v1).cross(v0 - v1);
    n.normalize();

    double dm = n.dot(r.dir);
    if (dm <= 0) {
      return i;
    }

    double nm = n.dot(v0 - ray.p);
    double t = nm/dm;
    if (t < 0 ) { 
      return i;
    }

    i.p = ray.p + t * r.dir;

    //Vector3D u = v2 - v1;
    //Vector3D v = v0 - v1;

    //Vector3D w = i.p - v1;

    //double uv = u.dot(v);
    //double wv = w.dot(v);
    //double wu = w.dot(u);
    //double vv = v.dot(v);
    //double uu = u.dot(u);

    //double si = (uv * wv - vv * wu)/(uv * uv - uu * vv);
    //double ti = (uv * wu - uu * wv)/(uv * uv - uu * vv);

    bool ishit = false;

    //if ( si >= 0 && ti >= 0 && (si + ti <= 1) ) { 
	//ishit = true;
    //}else {
	//ishit = false;
    //}

    for (unsigned int j = 0; j < poly.size(); j++) {
      double d = (((poly[(j+1)%poly.size()]) - poly[j]).cross(i.p - poly[j])).dot(n);
      if (d > 0) {
        ishit = true;
      }else {
        ishit = false;
        break;
      }
    }

    if (ishit){
      i.ishit =  ishit;
      i.n = -1.0 * n;
      i.t = t;
    }
    return i;

}

IntSection Mesh::intsect (Ray ray) {

    IntSection bsi = bsphere->intsect(ray);

    IntSection i;

    if ( !bsi.ishit ){
      return i;
    }else {

    //polygon from all the faces
    for (std::vector<Face>::const_iterator it = m_faces.begin(), end = m_faces.end(); it != end; it++) {
      std::vector<Point3D> poly;

      Face face = *it;
      for (unsigned int j = 0; j < face.size(); j++) {
        poly.insert(poly.begin(),m_verts[face[j]]);
      }
      IntSection polyi = intpoly(ray, poly);

      if (polyi.ishit) {
        //pick the polygon hit if it's closer
        if (!i.ishit || polyi.t < i.t ) {
          i = polyi;
        }
      }

    }   


    return i;
    }   
}
