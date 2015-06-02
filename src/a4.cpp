#include "a4.hpp"
#include "image.hpp"
#include "algebra.hpp"
#include "primitive.hpp"
#include "material.hpp"
#include <ctime>

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights
               )
{
  // Fill in raytracing code here.

  std::cerr << "Stub: a4_render(" << root << ",\n     "
            << filename << ", " << width << ", " << height << ",\n     "
            << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
            << ambient << ",\n     {";


  for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
    if (I != lights.begin()) std::cerr << ", ";
    std::cerr << **I;
  }
  std::cerr << "});" << std::endl;
  
  // ray tracing setup

  fov = fov * M_PI/360.0;

  Vector3D u = view.cross(up);
  Vector3D newview = view;
  Vector3D newup = up;

  u.normalize();
  newview.normalize();
  newup.normalize();

  // For now, just make a sample image.

  Image img(width, height, 3);

  // ray tracing starts now
std::cerr << "----------Ray tracing starts now" << std::endl;
std::cerr << "----------Image is 512x512" << std::endl;
    clock_t startTime = clock();
    int e = 0;
    for ( int y = 0; y < height; y++ ) {
	for ( int x = 0; x < width; x++ ) {
            e++;
	    Ray ray;

	    ray.p = eye;
	    ray.dir = newview + (x / (double(width)) * 2 - 1 )* tan(fov) * (double(width)/double(height)) * u
			      + (y / (double(height)) * 2 - 1 ) * tan(fov) * (-(newup)) ;

            ray.dir.normalize();

	    IntSection i;

	    i = root->intsect(ray);

	    if ( !i.ishit ) {
		img(x, y, 0) = 0.4;
		img(x, y, 1) = 0.4;
		img(x, y, 2) = 0.8;

	    }else {

		Vector3D c;
		Material* m = i.m;
		PhongMaterial* pm = dynamic_cast<PhongMaterial*>(m);


		for (std::list<Light*>::const_iterator lit = lights.begin(), end = lights.end(); lit != end; ++lit) {
		    Light* l = *lit;

		    Vector3D ld = l->position - i.p;
		    ld.normalize();

		    Ray lray;
		    lray.dir = i.p - l->position;
		    lray.dir.normalize();
		    lray.p = l->position;

		    bool shadow = false;

		    const double t = (i.p - l->position).length();

		    IntSection lighti = root->intsect(lray);

		    if(lighti.ishit) {
			if( (lighti.p - l->position).length() < t - 0.001) { 

			    shadow = true;
			}

		    }

		    if(shadow) {
			continue;
		    }

		    //l dot n

		    double lamb = i.n.dot(ld);

		    c[0] += lamb * pm->diffuse().R() * l->colour.R();
		    c[1] += lamb * pm->diffuse().G() * l->colour.G();
		    c[2] += lamb * pm->diffuse().B() * l->colour.B();

		    double reflect = 2.0 * (ld.dot(i.n));
		    Vector3D phongDir = ld - reflect * i.n;
		    double phonCoeff = std::max(phongDir.dot(ray.dir), 0.0);

		    phonCoeff = pow(phonCoeff, pm->shininess());

		    c[0] += phonCoeff * pm->specular().R() * l->colour.R();
		    c[1] += phonCoeff * pm->specular().G() * l->colour.G();
		    c[2] += phonCoeff * pm->specular().B() * l->colour.B();

		
		}

		c[0] += pm->diffuse().R() * ambient.R();
		c[1] += pm->diffuse().G() * ambient.G();
		c[2] += pm->diffuse().B() * ambient.B();

		img(x, y, 0) = c[0];
		img(x, y, 1) = c[1];
		img(x, y, 2) = c[2];


	    }




	}
    if(e == 512*51*1){
	std::cerr << "----------10%" << std::endl;
    }else if(e == 512*51*2){
	std::cerr << "----------20%" << std::endl;
    }else if(e == 512*51*3){
	std::cerr << "----------30%" << std::endl;
    }else if(e == 512*51*4){
	std::cerr << "----------40%" << std::endl;
    }else if(e == 0.5*512*512){
	std::cerr << "----------50%" << std::endl;
    }else if(e == 512*51*6){
	std::cerr << "----------60%" << std::endl;
    }else if(e == 512*51*7){
	std::cerr << "----------70%" << std::endl;
    }else if(e == 512*51*8){
	std::cerr << "----------80%" << std::endl;
    }else if(e == 512*51*9){
	std::cerr << "----------90%" << std::endl;
    }else if(e == 512*512){
	std::cerr << "----------100%" << std::endl;
    }
    }
std::cerr << "----------Ray tracing complete" << std::endl;

    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
std::cerr << "----------" << "Total time: " << timeInSeconds << std::endl;
  // ray tracing ends now


  //for (int y = 0; y < height; y++) {
  //  for (int x = 0; x < height; x++) {
      // Red: increasing from top to bottom
  //    img(x, y, 0) = (double)y / height;
      // Green: increasing from left to right
  //    img(x, y, 1) = (double)x / width;
      // Blue: in lower-left and upper-right corners
  //    img(x, y, 2) = ((y < height/2 && x < height/2)
  //                    || (y >= height/2 && x >= height/2)) ? 1.0 : 0.0;
  //  }
  //}
  img.savePng(filename);
  
}
