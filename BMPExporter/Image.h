#pragma once

#include <cstdlib>
#include <cstdint>

using namespace std;

namespace BMPExporter {
	struct Resolution {
		unsigned int x = 0;
		unsigned int y = 0;

		Resolution(unsigned int x = 0, unsigned int y = 0) {
			this->x = x;
			this->y = y;
		}
	};

	struct Color {
		uint8_t r, g, b, a = 255;

		Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	class Image
	{
	public:
		Image(unsigned int sizeX, unsigned int sizeY);
		~Image();

		Resolution* GetResolution();
		void SetPixel(unsigned int xPosition, unsigned int yPosition, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetPixel(unsigned int xPosition, unsigned int yPosition, Color color);
		Color* GetPixel(unsigned int xPosition, unsigned int yPosition);

	private:
		Resolution m_resolution;
		Color* m_colorArr;
	};
}
