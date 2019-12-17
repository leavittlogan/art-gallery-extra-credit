#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "polygon.h"
#include "artgallery.h"

const char * inFileName = "polygons.txt";
const char * outFileName = "output.txt";
const char delim = '|';

int main() {
    std::ifstream inFile(inFileName);

    std::string points;
    double x, y;
    Polygon p;
    std::vector<ArtGallery> galleries;
    while (!inFile.eof()) {
        std::getline(inFile, points, delim);
        std::istringstream ss(points);

        while (ss >> x >> y) {
            p.push(x, y);
        }

        galleries.push_back(ArtGallery(p));
        p.clear();
    }

    inFile.close();


    std::ofstream outFile(outFileName);
    int i = 1;
    for (auto it = galleries.begin(); it != galleries.end(); ++it) {

        // output to terminal
        const std::vector<Point> guards = (*it).getGuards();
        std::cout << "\tPolygon " << i << std::endl
            << guards.size() << " guard(s) needed, placed at:" << std::endl;
        for (auto it2 = guards.begin(); it2 != guards.end(); ++it2) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;

        // output to file
        outFile << "\tPolygon " << i++ << std::endl
            << *it << std::endl << std::endl;
    }
    outFile.close();

    return 0;
}
