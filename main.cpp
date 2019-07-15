// #include <limits>
// #include <cmath>
// #include <iostream>
// #include <fstream>
// #include <vector>

// void render() {
//     const int width    = 1024;
//     const int height   = 768;
//     std::vector<Vec3f> framebuffer(width*height);

//     for (size_t j = 0; j<height; j++) {
//         for (size_t i = 0; i<width; i++) {
//             framebuffer[i+j*width] = Vec3f(j/float(height),i/float(width), 0);
//         }
//     }

//     std::ofstream ofs; // save the framebuffer to file
//     ofs.open("./out.ppm");
//     ofs << "P6\n" << width << " " << height << "\n255\n";
//     for (size_t i = 0; i < height*width; ++i) {
//         for (size_t j = 0; j<3; j++) {
//             ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
//         }
//     }
//     ofs.close();
// }

// int main() {
//     render();
//     return 0;
// }
#include <vector>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>

#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
	const int width  = 800;
	const int height = 800;

void line1(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    for (float t=0.; t<1.; t+=.01) { 
        int x = x0 + (x1-x0)*t; 
        int y = y0 + (y1-y0)*t; 
        image.set(x, y, color); 
    } 
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 

int main(int argc, char** argv) {
    if (2==argc) {
	        model = new Model(argv[1]);
	    } else {
	        model = new Model("obj/african_head.obj");
	    }
	
	    TGAImage image(width, height, TGAImage::RGB);
	    for (int i=0; i<model->nfaces(); i++) {
	        std::vector<int> face = model->face(i);
	        for (int j=0; j<3; j++) {
	            Vec3f v0 = model->vert(face[j]);
	            Vec3f v1 = model->vert(face[(j+1)%3]);
	            int x0 = (v0.x+1.)*width/2.;
	            int y0 = (v0.y+1.)*height/2.;
	            int x1 = (v1.x+1.)*width/2.;
	            int y1 = (v1.y+1.)*height/2.;
	            line(x0, y0, x1, y1, image, white);
	        }
	    }
	
	    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	    image.write_tga_file("output.tga");
	    delete model;
	    return 0;
}


