#include "Image.h"

#include <iostream>

namespace BMPExporter {
	Image::Image(unsigned int sizeX, unsigned int sizeY) {
		m_resolution = Resolution(sizeX, sizeY);
		m_colorArr = new Color[sizeX * sizeY];
	}

	Resolution* Image::GetResolution() {
		return &m_resolution;
	}

	void Image::SetPixel(unsigned int xPosition, unsigned int yPosition, Color color) {
		if (xPosition >= m_resolution.x || yPosition >= m_resolution.y || xPosition < 0 || yPosition < 0) {
			throw "Position is not valid!";
			return;
		}
		else {
			m_colorArr[(yPosition * m_resolution.x + xPosition)] = color;
		}
	}

	/// <summary>
	/// Set a pixel on the image
	/// </summary>
	/// <param name="xPosition">horizontal pixel (left to right)</param>
	/// <param name="yPosition">vertical pixel (top to bottom)(</param>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="a"></param>
	void Image::SetPixel(unsigned int xPosition, unsigned int yPosition, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		this->SetPixel(xPosition, yPosition, (Color(r, g, b, a)));
	}

	Color* Image::GetPixel(unsigned int xPosition, unsigned int yPosition) {		
		try {
			if (xPosition >= m_resolution.x || yPosition >= m_resolution.y || xPosition < 0 || yPosition < 0) {
				throw "Position is not valid!";
			}
			else {
				return &m_colorArr[yPosition * m_resolution.x + xPosition];
			}
		}
		catch(exception e){
			return &Color(0, 0, 0);
		}		
	}


	Image::~Image() {
		delete[] this->m_colorArr;
	}
}
