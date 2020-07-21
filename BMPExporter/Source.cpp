#include "Image.h"
#include "Exporter.h"
#include <iostream>
#include <fstream>

using namespace BMPExporter;
using namespace std;

int main() {
	Image img = Image(1024, 1024);
	
	for (unsigned int x = 0; x < 1024; x++) {
		for (unsigned int y = 0; y < 1024; y++) {
			img.SetPixel(x, y, x/4, 15, y/4);
		}
	}
	
	ofstream file;
	file.open("abc.bmp", ios::out|ios::binary);

	Exporter exporter = Exporter(&img);

	exporter.Export(file);

	file.close();
}