//
// Created by peter on 27/01/2021.
//
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <ctime>
#include "PaintIcon.h"


void PaintIcon::getCharArray(ColourIcon &colourIcon, bool  withAlpha) {

    int width = colourIcon.xSz;
    int height = colourIcon.ySz;
    int xPos = 0;
    int yPos = 0;
    int pixelSize = withAlpha? 4:3;
    //Make rgba buffer
   charBuffer = (unsigned char*)(calloc(width*height*pixelSize, sizeof(unsigned char)));
    if(charBuffer != nullptr){

        //set to background colour
        cout << "bgRGBA "<< colourIcon.bgRGBA[0] << " " << colourIcon.bgRGBA[1] << " " << colourIcon.bgRGBA[2] << " "
        << colourIcon.bgRGBA[3] <<endl;
        cout << "pixelSize " << pixelSize << endl;
        for(int k=0;k<width*height;k++){
            for(int p=0;p<pixelSize;p++) {
                unsigned int val = (unsigned int)( colourIcon.bgRGBA[p] *255);
                charBuffer[k * pixelSize + p] = val; /* convert from 0.0 to 1.0 to 0 to 255 */

            }
        }
        /**** debug ****************
          std::time_t result = std::time(nullptr);
        const std::string ddate = to_string(result).data();

        stbi_write_png(("bgOnly" +ddate +".png").c_str(), colourIcon.xSz, colourIcon.ySz, pixelSize, buf, colourIcon.xSz*pixelSize);
******************************************************************************************/

        RgbaList2DIter iter = colourIcon.colourArray.begin();
        while(iter != colourIcon.colourArray.end()){
            xPos = iter->first.val[0];
            yPos = iter->first.val[1];

            if(xPos > width-1 || (yPos > height-1)) continue;
          //  cout << xPos <<" " << yPos << " ";
            double *rgba = iter->second;
            for(int n=0;n<pixelSize;n++) {
                double fVal = iter->second[n];
               // cout << fVal << " ";
                unsigned int val = (unsigned int)( fVal * 255);
                int pos = (yPos * width + xPos) * pixelSize +n;

                try {
                    charBuffer[pos] = static_cast<unsigned char>(val);
                }catch (runtime_error xx){
                    //just skip?
                    cout<< " error charBuffer hasnt got " << pos <<" " << xx.what() << endl;
                }

               // cout << val << "   " ;
            }
           // cout <<endl;
            iter++;
        }
    }
}

int PaintIcon::paintPNG(ColourIcon &colourIcon, string fileName, bool withAlpha){
    getCharArray(colourIcon, withAlpha);
    int result = 0;
    if(charBuffer != nullptr) {
        int pixelSize = withAlpha ? 4 : 3;
        result = stbi_write_png(fileName.c_str(), colourIcon.xSz, colourIcon.ySz, pixelSize, charBuffer,
                                colourIcon.xSz * pixelSize);
    }
        if (result == 0) { cout << "ERROR stbi_wtite_bmp failed." << endl; }

    return result;
}

 void PaintIcon::getFloatArray(ColourIcon &colourIcon, bool useAlpha= false) {

    int width = colourIcon.xSz;
    int height = colourIcon.ySz;
    int xPos = 0;
    int yPos = 0;
    int pixelSz = useAlpha? 4:3;

    //Make rgba buffer
    floatBuffer = (float*)(calloc(width*height*pixelSz, sizeof(float)));
    if(floatBuffer != nullptr){
        //set to background colour
        cout << "bgRGBA "<< colourIcon.bgRGBA[0] << " " << colourIcon.bgRGBA[1] << " " << colourIcon.bgRGBA[2] << " "
             << colourIcon.bgRGBA[3] <<endl;
        for(int k=0;k<width*height;k++) {
            for (int p = 0; p < pixelSz; p++) {
                floatBuffer[k * pixelSz + p] = colourIcon.bgRGBA[p];
            }
        }
            std::time_t result = std::time(nullptr);
            const std::string ddate = to_string(result).data();
        int resy = stbi_write_hdr(("bgOnly" +ddate +".hdr").c_str(), colourIcon.xSz, colourIcon.ySz, pixelSz, floatBuffer);
        if(resy == 0){cout << "couldn't write bg image" << endl;}
        RgbaList2DIter iter = colourIcon.colourArray.begin();
        while(iter != colourIcon.colourArray.end()){
            xPos = iter->first.val[0];
            yPos = iter->first.val[1];

            //  cout << xPos <<" " << yPos << " ";
            double *rgba = iter->second;
            for(int n=0;n<pixelSz;n++) {
                float fVal = iter->second[n];
                // cout << fVal << " ";
                floatBuffer[(yPos*width + xPos)*pixelSz +n] = fVal;
                // cout << val << "   " ;
            }
            // cout <<endl;
            iter++;
        }
    }
}
/*****
int len;
unsigned char *png = stbi_write_png_to_mem((const unsigned char *) data, stride_bytes, x, y, comp, &len);
************/

int PaintIcon::paintHDR(ColourIcon &colourIcon, string fileName, bool withAlpha=false){
    getFloatArray(colourIcon, withAlpha);
    int result = 0;
    if(floatBuffer != nullptr) {
        int pixelSize = withAlpha ? 4 : 3;
        result = stbi_write_hdr(fileName.c_str(), colourIcon.xSz, colourIcon.ySz, pixelSize, floatBuffer);
    }
    if(result == 0){  cout << "ERROR stbi_wtite_bmp failed." << endl;}
    return result;
}

unsigned char *PaintIcon::paintPNGtoBuffer(ColourIcon &colourIcon, bool withAlpha, int *len) {
    if(charBuffer == nullptr) {
        getCharArray(colourIcon, withAlpha);
    }
    cout<< "PaintIcon paintPNGBuffer got char array" <<endl;
    if(charBuffer != nullptr) {
        cout <<"charBuffer not null" <<endl;
        int pixelSize = withAlpha ? 4 : 3;
        pngBuffer = stbi_write_png_to_mem((const unsigned char *) charBuffer, colourIcon.xSz * pixelSize,
                                                   colourIcon.xSz, colourIcon.ySz, pixelSize, len);
        cout <<"pngBuffer len is "<< *len <<endl;
    }
    return pngBuffer;
}

PaintIcon::~PaintIcon() {
    free(charBuffer);
    free(floatBuffer);
   // free(pngBuffer); //OK handed off
}



