#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Filter.h"

FILE* pFile = fopen("Foto.bmp", "rb");
FILE* oFile = fopen("OutFoto.bmp", "wb");

void Filter::BITMAPFILEHEADER::RHeaderFoto(){

	this->bfType = read_16(pFile);
    this->bfSize = read_32(pFile);
    this->bfReserved1 = read_16(pFile);
    this->bfReserved2 = read_16(pFile);
    this->bfOffBits = read_32(pFile);
}

void Filter::BITMAPFILEHEADER::WHeaderFoto(BITMAPFILEHEADER& header){

    write_16(header.bfType, oFile);
    write_32(header.bfSize, oFile);
    write_16(header.bfReserved1, oFile);
    write_16(header.bfReserved2, oFile);
    write_32(header.bfOffBits, oFile);
}

void Filter::BITMAPINFOHEADER::RBmiHeaderFoto(){

    this->biSize = read_32(pFile);
    this->biWidth = read_32(pFile);
    this->biHeight = read_32(pFile);
    this->biPlanes = read_16(pFile);
    this->biBitCount = read_16(pFile);
    this->biCompression = read_32(pFile);
    this->biSizeImage = read_32(pFile);
}

void Filter::BITMAPINFOHEADER::WBmiHeaderFoto(BITMAPINFOHEADER& bmiHeader){

    write_32(bmiHeader.biSize, oFile);
    write_32(bmiHeader.biWidth, oFile);
    write_32(bmiHeader.biHeight, oFile);
    write_16(bmiHeader.biPlanes, oFile);
    write_16(bmiHeader.biBitCount, oFile);
    write_32(bmiHeader.biCompression, oFile);
    write_32(bmiHeader.biSizeImage, oFile);
}

Filter::RGBQUAD* Filter::RGBQUAD::ReadByteColor(BITMAPINFOHEADER& bmiHeader){

    RGBQUAD* pixels = new RGBQUAD[bmiHeader.biHeight * bmiHeader.biWidth];

    for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
        pixels[i].rgbBlue = getc(pFile);
        pixels[i].rgbGreen = getc(pFile);
        pixels[i].rgbRed = getc(pFile);
    }

    return pixels;
}

void Filter::RGBQUAD::Inversion(BITMAPINFOHEADER& bmiHeader, RGBQUAD* &pixels){

    for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
        putc(~pixels[i].rgbBlue, oFile);
        putc(~pixels[i].rgbGreen, oFile);
        putc(~pixels[i].rgbRed, oFile);
    }
}

void Filter::RGBQUAD::BW(BITMAPINFOHEADER& bmiHeader, RGBQUAD*& pixels){

    for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
        int ColorPixel = (pixels[i].rgbBlue + pixels[i].rgbGreen + pixels[i].rgbRed) / 3;
        putc(ColorPixel, oFile);
        putc(ColorPixel, oFile);
        putc(ColorPixel, oFile);
    }
}

unsigned short Filter::read_16(FILE* fp){

    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
}

unsigned int Filter::read_32(FILE* fp){

    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

void Filter::write_16(unsigned short input, FILE* fp){

    putc(input, fp);
    putc(input >> 8, fp);
}

void Filter::write_32(unsigned int input, FILE* fp){

    putc(input, fp);
    putc(input >> 8, fp);
    putc(input >> 16, fp);
    putc(input >> 24, fp);
}

void Filter::PrepareImage(){

    Filter::BITMAPFILEHEADER header;
    Filter::BITMAPINFOHEADER bmiHeader;
    Filter::RGBQUAD pixel;

    header.RHeaderFoto();
    bmiHeader.RBmiHeaderFoto();
    RGBQUAD* pixels = pixel.ReadByteColor(bmiHeader);

    header.WHeaderFoto(header);
    bmiHeader.WBmiHeaderFoto(bmiHeader);
    pixel.BW(bmiHeader, pixels);

    fclose(pFile);
    fclose(oFile);
}