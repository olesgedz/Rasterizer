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

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "tgaimage.h"

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

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
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(52, 41, red);
	image.flip_vertically();
    line(0,0, 50,50, image, red);
	image.write_tga_file("output.tga");
	return 0;
}


