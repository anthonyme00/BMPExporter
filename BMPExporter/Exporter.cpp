#include "Exporter.h"

namespace BMPExporter {
	Exporter::Exporter(Image* image) {
		this->image = image;
		width = image->GetResolution()->x;
		height = image->GetResolution()->y;
		padAmount = (4 - (width * 3) % 4) % 4;
		imageSize = width * height * 3 + padAmount * height;
		fileSize = imageSize + bitmapHeaderSize + infoHeaderSize;
		pixelData = new char[imageSize];

		GeneratePixelData();
	}

	/// <summary>
	/// Make sure to set the binary flag
	/// </summary>
	/// <param name="stream"></param>
	void Exporter::Export(ostream& stream) {
		//create header
		stream	<< (char)(BMPHeader >> 8) << (char)(BMPHeader) //header
				<< (char)fileSize << (char)(fileSize >> 8) << (char)(fileSize >> 16) << (char)(fileSize >> 24) //file size
				<< (char)0 << (char)0 << (char)0 << (char)0 //reserved
				<< (char)dataOffset << (char)(dataOffset >> 8) << (char)(dataOffset >> 16) << (char)(dataOffset >> 24); //data offset
		//create info header
		stream	<< (char)infoHeaderSize << (char)(infoHeaderSize >> 8) << (char)(infoHeaderSize >> 16) << (char)(infoHeaderSize >> 24)
				<< (char)width << (char)(width >> 8) << (char)(width >> 16) << (char)(width >> 24)
				<< (char)height << (char)(height >> 8) << (char)(height >> 16) << (char)(height >> 24)
				<< (char)planeNumber << (char)(planeNumber >> 8) //not sure what this is. Must be set to 1
				<< (char)bitsPerPixel << (char)(bitsPerPixel >> 8)
				<< (char)compression << (char)(compression >> 8) << (char)(compression >> 16) << (char)(compression >> 24)
				<< (char)imageSize << (char)(imageSize >> 8) << (char)(imageSize >> 16) << (char)(imageSize >> 24)
				<< (char)pixelPerMeterHorizontal << (char)(pixelPerMeterHorizontal >> 8) << (char)(pixelPerMeterHorizontal >> 16) << (char)(pixelPerMeterHorizontal >> 24)
				<< (char)pixelPerMeterVertical << (char)(pixelPerMeterVertical >> 8) << (char)(pixelPerMeterVertical >> 16) << (char)(pixelPerMeterVertical >> 24)
				<< (char)usedColors << (char)(usedColors >> 8) << (char)(usedColors >> 16) << (char)(usedColors >> 24)
				<< (char)importantColors << (char)(importantColors >> 8) << (char)(importantColors >> 16) << (char)(importantColors >> 24);
				
		for (unsigned int i = 0; i < imageSize; i++) {
			stream << (char)pixelData[i];
		}
	}

	void Exporter::GeneratePixelData() {
		int offset = 0;
		
		//data is kept left to right, bottom to top
		for (unsigned int y = height - 1; y >= 0 && y < height; y--) {
			for (unsigned int x = 0; x < width; x++) {
				//data is kept in BGR order (little endian)
				Color* col = image->GetPixel(x, y);
				
				pixelData[offset] = (char)col->b;
				pixelData[offset+1] = (char)col->g;
				pixelData[offset+2] = (char)col->r;
				
				offset += 3;
			}
			for (int j = 0; j < padAmount; j++) {
				pixelData[offset++] << (char)0;
			}
		}
	}

	Exporter::~Exporter() {
		delete[] pixelData; //clear out pixeldata
	}
}
