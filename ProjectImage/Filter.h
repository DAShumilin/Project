#pragma once

class Filter {

public:

    class BITMAPFILEHEADER {

        friend class Filter;

    private:

        unsigned int bfType;
        unsigned long bfSize;
        unsigned int bfReserved1;
        unsigned int bfReserved2;
        unsigned long bfOffBits;

        void RHeaderFoto();
        void WHeaderFoto(BITMAPFILEHEADER& header);
    };

    class BITMAPINFOHEADER {

        friend class Filter;
        friend class RGBQUAD;

    private:

        unsigned int biSize;
        int biWidth;
        int biHeight;
        unsigned short biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;

        void RBmiHeaderFoto();
        void WBmiHeaderFoto(BITMAPINFOHEADER& bmiHeader);
    };

    class RGBQUAD {

        friend class Filter;

    private:

        int rgbBlue;
        int rgbGreen;
        int rgbRed;
        int rgbReserved;

        RGBQUAD* ReadByteColor(BITMAPINFOHEADER& BmiHeader);
        void Inversion(BITMAPINFOHEADER& BmiHeader, RGBQUAD*& pixels);
        void BW(BITMAPINFOHEADER& BmiHeader, RGBQUAD*& pixels);
    };

    static unsigned short read_16(FILE* fp);
    static unsigned int read_32(FILE* fp);

    static void write_16(unsigned short input, FILE* fp);
    static void write_32(unsigned int input, FILE* fp);

    void PrepareImage();
};