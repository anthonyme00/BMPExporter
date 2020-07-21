#pragma once
#include <cstdint>
#include <ostream>
#include "Image.h"

namespace BMPExporter {
	/// <summary>
	/// Primary class for exporting to BMP File.
	/// Notes: Bitmap uses little endian.
	/// Ref: http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
	/// </summary>
	class Exporter
	{
	private:
		uint32_t fileSize = 0; //for the header, uses 4 bytes. Offset is 2.
		uint32_t width = 0;
		uint32_t height = 0;
		uint16_t planeNumber = 0x0001;
		uint32_t imageSize = 0;
		uint32_t importantColors = 0; //0 = all color is important
		int padAmount = 0;

		char* pixelData;
		
		Image* image;

		void GeneratePixelData();
	public:
		const int bitmapHeaderSize = 0x0E; //14 bytes.
		const uint16_t BMPHeader = 0x424D; //"BM" in ASCII, use at offset 0.
		const uint32_t dataOffset = 0x0036;
		const uint32_t infoHeaderSize = 0x00000028; //40 bytes.
		const uint16_t bitsPerPixel = 0x0018; //24 bits per pixel.
		const uint32_t compression = 0x00000000; //BI_RGB no compression.
		uint32_t pixelPerMeterHorizontal = 1024; //horizontal size
		uint32_t pixelPerMeterVertical = 1024; //vertical size
		const uint32_t usedColors = 0x01000000; //16M colors for 24 bit/pixel

		Exporter(Image* toExport);
		~Exporter();

		void Export(ostream& stream);
	};
}


