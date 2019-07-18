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
const TGAColor red = TGAColor(255, 0, 0, 255);
Model *model = NULL;
const int width = 800;
const int height = 800;

void line1(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    for (float t = 0.; t < 1.; t += .01)
    {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        image.set(x, y, color);
    }
}

void line(Vec2i t0, Vec2i t1, TGAImage &image, TGAColor color)
{
    bool steep = false;
    if (std::abs(t0.x - t1.x) < std::abs(t0.y - t1.y))
    {
        std::swap(t0.x, t0.y);
        std::swap(t1.x, t1.y);
        steep = true;
    }
    if (t0.x > t1.x)
    {
        std::swap(t0.x, t1.x);
        std::swap(t0.y, t1.y);
    }
    int dx = t1.x - t0.x;
    int dy = t1.y - t0.y;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = t0.y;
    for (int x = t0.x; x <= t1.x; x++)
    {
        if (steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx)
        {
            y += (t1.y > t0.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) { 
    if (t0.y==t1.y && t0.y==t2.y) return; // I dont care about degenerate triangles 
    // sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!) 
    if (t0.y>t1.y) std::swap(t0, t1); 
    if (t0.y>t2.y) std::swap(t0, t2); 
    if (t1.y>t2.y) std::swap(t1, t2); 
    int total_height = t2.y-t0.y; 
    for (int i=0; i<total_height; i++) { 
        bool second_half = i>t1.y-t0.y || t1.y==t0.y; 
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y; 
        float alpha = (float)i/total_height; 
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here 
        Vec2i A =               t0 + (t2-t0)*alpha; 
        Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta; 
        if (A.x>B.x) std::swap(A, B); 
        for (int j=A.x; j<=B.x; j++) { 
            image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y 
        } 
    } 
}

int main(int argc, char **argv)
{
    if (2 == argc)
    {
        model = new Model(argv[1]);
    }
    else
    {
        model = new Model("obj/african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
    // for (int i=0; i<model->nfaces(); i++) {
    //     std::vector<int> face = model->face(i);
    //     for (int j=0; j<3; j++) {
    //         Vec3f v0 = model->vert(face[j]);
    //         Vec3f v1 = model->vert(face[(j+1)%3]);
    //         int x0 = (v0.x+1.)*width/2.;
    //         int y0 = (v0.y+1.)*height/2.;
    //         int x1 = (v1.x+1.)*width/2.;
    //         int y1 = (v1.y+1.)*height/2.;
    //         line(x0, y0, x1, y1, image, white);
    //     }
    // }

    Vec2i t0[3] = {Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80)};
    triangle(t0[0], t0[1], t0[2], image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}
