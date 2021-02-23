/*******************************************************
 * Homework 1: Rasterization                           *
 *-----------------------------------------------------*
 * Here you will implement the circle rasterization    *
 * method decribed in the handout.                                           *
 * To compile this in linux:                           *
 *        g++ hw1.cpp                                  *
 * Then, run the program as follows:                   *
 *        ./a.out 200                                  *
 * to generate a 200x200 image containing a circular   *
 * arc.  Note that the coordinate system we're using   *
 * places pixel centers at integer coordinates and     *
 * has the origin at the lower left.                   *
 * Your code will generate a .ppm file containing the  *
 * final image. These images can be viewed using       *
 * "display" in Linux or Irfanview in Mac/Windows.     *
 *******************************************************/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
using namespace std;

// We'll store image info as globals; not great programming practice
// but ok for this short program.
int radius;
bool** image;

void renderPixel(int x, int y) {
    assert(x >= 0 && y >= 0 && x <= radius && y <= radius);

    
    //cout << x << " " << y;
    image[x][y] = 1; // x > 0, y > 0 (actual image) q12
    //image[y][x] = 1; // mirror x>0, >0 through y = x q11

    //image[x][-y] = 1; // x > 0, y < 0 q41
    //image[y][-x] = 1; // mirror x < 0, y > 0 through y = x  q42
    
    //image[-x][-y] = 1; // x < 0, y < 0 q32
    //image[-y][-x] = 1; // mirror x < 0, y < 0 through y = x q31

    //image[-x][y] = 1; // x < 0, y > 0 q21
    //image[-y][x] = 1; // mirror x < 0, y > 0 through y = x q22
    
    
    
    // TODO:  light up the pixel's symmetric counterpart
}

void rasterizeArc(int r) {

    for (int i = 0; i < r+1; i++) {
        for (int j = 0; j < r+1; j++) {
            image[i][j] = 0;
            if(image[i][j] != 0)
                cout << image[i][j] << " ";
        }
        //cout << endl;
    }

    int offset = radius / 2;

    int r1 = 100;
    int r2 = 150;

    //circle r = 100 in x >= 0
    int x1 = 0;
    int y1 = r1;

    int d1 = 1 - r1;
    int deltaE1 = 3;
    int deltaSE1 = -2 * r1 + 5;
    renderPixel(x1 + offset, y1 + offset);
    
    while (y1 > x1) {
        
        if (d1 < 0) {
            d1 += deltaE1;
            deltaE1 += 2;
            deltaSE1 += 2;
        }
        else {
            d1 += deltaSE1;
            deltaE1 += 2;
            deltaSE1 += 4;
            y1--;
        }
        x1++;
        
        renderPixel(x1 + offset, y1 + offset);
        renderPixel(y1 + offset, x1 + offset);

        //renderPixel(x1, -y1);
        //renderPixel(y1, -x1);

        renderPixel(-x1 + offset, y1 + offset);
        renderPixel(-y1 + offset, x1 + offset);

        //renderPixel(-x1, -y1);
        //renderPixel(-y1, -x1);
    }

    //big circle r = 150 in y >= 0

    int x2 = 0;
    int y2 = r2;

    int d2 = 1 - r2;
    int deltaE2 = 3;
    int deltaSE2 = -2 * r2 + 5;
    renderPixel(y2 + offset, x2 + offset);

    while (y2 > x2) {

        if (d2 < 0) {
            d2 += deltaE2;
            deltaE2 += 2;
            deltaSE2 += 2;
        }
        else {
            d2 += deltaSE2;
            deltaE2 += 2;
            deltaSE2 += 4;
            y2--;
        }
        x2++;

        renderPixel(x2 + offset, y2 + offset);
        renderPixel(y2 + offset, x2 + offset);

        renderPixel(x2 + offset, -y2 + offset);
        renderPixel(y2 + offset, -x2 + offset);

    }


    // TODO:  rasterize the arc using renderPixel to light up pixels

}

// You shouldn't need to change anything below this point.

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " circleSize\n";
        return 0;
    }

#ifdef _WIN32
    sscanf_s(argv[1], "%d", &radius);
#else
    sscanf(argv[1], "%d", &radius);
#endif
    if (radius <= 0) {
        cout << "Image must be of positive size.\n";
        return 0;
    }

    // reserve image as 2d array
    image = new bool* [radius + 1];
    for (int i = 0; i <= radius; i++) image[i] = new bool[radius + 1];

    rasterizeArc(radius);

    char filename[50];
#ifdef _WIN32
    sprintf_s(filename, 50, "circle%d.ppm", radius);
#else
    sprintf(filename, "circle%d.ppm", radius);
#endif

    ofstream outfile(filename);
    outfile << "P3\n# " << filename << "\n";
    outfile << radius + 1 << ' ' << radius + 1 << ' ' << 1 << endl;

    for (int i = 0; i <= radius; i++)
        for (int j = 0; j <= radius; j++)
            outfile << image[radius - i][j] << " 0 0\n";

    // delete image data
    for (int i = 0; i <= radius; i++) delete[] image[i];
    delete[] image;

    return 0;
}
