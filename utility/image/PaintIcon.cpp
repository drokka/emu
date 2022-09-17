//
// Created by peter on 27/01/2021.
//
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "../../../stb/stb_image_write.h"

#include <ctime>
#include <string>
#include "PaintIcon.h"
#include <iostream>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <fstream>

/*
void PaintIcon::getCharArray(ColourIcon &colourIcon, bool  withAlpha, bool switchRGBAtoARGB) {

    int width = colourIcon.xSz;
    int height = colourIcon.ySz;
    int xPos = 0;
    int yPos = 0;
    int pixelSize = withAlpha ? 4 : 3;
    int premultipliedR = (0xff * 0x88) >> 8;
    //Make rgba buffer
    charBuffer = (unsigned char *) (calloc(width * height * pixelSize, sizeof(unsigned char)));
    if (charBuffer != nullptr) {

        //set to background colour
        cout << "bgRGBA " << colourIcon.bgRGBA[0] << " " << colourIcon.bgRGBA[1] << " "
             << colourIcon.bgRGBA[2] << " "
             << colourIcon.bgRGBA[3] << endl;
        cout << "pixelSize " << pixelSize << endl;

        if(!switchRGBAtoARGB){
        for (int k = 0; k < width * height; k++) {
            charBuffer[k * pixelSize + 0] = (unsigned int) (colourIcon.bgRGBA[0] * 255); //Red
            charBuffer[k * pixelSize + 1] = (unsigned int) (colourIcon.bgRGBA[1] * 255);  //Green
            charBuffer[k * pixelSize + 2] = (unsigned int) (colourIcon.bgRGBA[2] * 255); //Blue
            charBuffer[k * pixelSize + 3] = (unsigned int) (colourIcon.bgRGBA[3] * 255); //Alpha
        }} else{

            double bm_premultiplied_R = min((colourIcon.bgRGBA[3] / 255.0) * colourIcon.bgRGBA[0], 255.0);  //alpha / 255 x red
            double  bm_premultiplied_G = min((colourIcon.bgRGBA[3] / 255.0) * colourIcon.bgRGBA[1], 255.0);
            double bm_premultiplied_B = min((colourIcon.bgRGBA[3] / 255.0) * colourIcon.bgRGBA[2], 255.0);


            for (int k = 0; k < width * height; k++) {

                charBuffer[k * pixelSize + 0] = (unsigned int) (colourIcon.bgRGBA[3] * 255);  //alpha
             charBuffer[k * pixelSize + 1] = (unsigned int)((colourIcon.bgRGBA[0] * (256 - colourIcon.bgRGBA[3])) + bm_premultiplied_R);
                charBuffer[k * pixelSize + 2] = (unsigned int)((colourIcon.bgRGBA[1] * (256 - colourIcon.bgRGBA[3])) + bm_premultiplied_G);
                charBuffer[k * pixelSize + 3]  = (unsigned int)((colourIcon.bgRGBA[2] * (256 - colourIcon.bgRGBA[3])) + bm_premultiplied_B);

                //dest.r = ((dest.r * (256 - source.a)) + (source.r * source.a)) >> 8;
// dest.g = ((dest.g * (256 - source.a)) + (source.g * source.a)) >> 8;
// dest.b = ((dest.b * (256 - source.a)) + (source.b * source.a)) >> 8;

              /*  charBuffer[k * pixelSize + 1] = (unsigned int) (colourIcon.bgRGBA[0] * 255); //alpha first for android?
                charBuffer[k * pixelSize + 2] = (unsigned int) (colourIcon.bgRGBA[1] * 255);
                charBuffer[k * pixelSize + 3] = (unsigned int) (colourIcon.bgRGBA[2] * 255);
                charBuffer[k * pixelSize + 0] = (unsigned int) (colourIcon.bgRGBA[3] * 255);

            }
        }
        */
            /*
            for(int p=0;p<pixelSize;p++) {
                unsigned int val = (unsigned int)( colourIcon.bgRGBA[p] *255);
                charBuffer[k * pixelSize + p] = val; /* convert from 0.0 to 1.0 to 0 to 255 */

            //   } **/
            // for Android
            //*(*dst + i) = (0x88 << 24 | premultipliedR | 0x00 << 8 | 0x00 << 16);
            // charBuffer[k * pixelSize + 3] = (unsigned int) (255 - colourIcon.bgRGBA[3]*255);

            /**** debug ****************
              std::time_t result = std::time(nullptr);
            const std::string ddate = to_string(result).data();

            stbi_write_png(("bgOnly" +ddate +".png").c_str(), colourIcon.xSz, colourIcon.ySz, pixelSize, buf, colourIcon.xSz*pixelSize);
    ******************************************************************************************/

      /*      RgbaList2DIter iter = colourIcon.colourArray.begin();
            int posy = 0;
            // int  count = 0;
            while (iter != colourIcon.colourArray.end() /*&& count < width*height*pixelSize ) {
                //  count++;
                xPos = iter->first.val[0];
                yPos = iter->first.val[1];

                if (xPos > width - 1 || (yPos > height - 1)) {
                    iter++;
                    continue;
                }
                // cout << xPos <<" " << yPos << " ";

                posy = (yPos * width + xPos) * pixelSize;
                auto red = (iter->second[0] * 255.0);
                auto green = (iter->second[1] * 255);
                auto blue = (iter->second[2] * 255);
                auto alpha = (iter->second[3] * 255);
                if(!switchRGBAtoARGB) {
                    charBuffer[posy + 0] = (unsigned int)red;
                    charBuffer[posy + 1] = (unsigned int)green;
                    charBuffer[posy + 2] = (unsigned int)blue;
                    charBuffer[posy + 3] = (unsigned int)alpha;
                }else{
                    double bm_premultiplied_R = min((alpha / 255.0) * red, 255.0);  //alpha / 255 x red
                    double  bm_premultiplied_G = min((alpha/ 255.0) * green, 255.0);
                    double bm_premultiplied_B = min((alpha / 255.0) * blue, 255.0);

                    charBuffer[posy + 0] = (unsigned int) (alpha );  //alpha
                    charBuffer[posy + 1] = (unsigned int)((red * (256 - alpha)) + bm_premultiplied_R);
                    charBuffer[posy + 2] = (unsigned int)((green * (256 - alpha)) + bm_premultiplied_G);
                    charBuffer[posy + 3]  = (unsigned int)((blue* (256 - alpha)) + bm_premultiplied_B);
                    /*
                    charBuffer[posy + 1] = (unsigned int)red;
                    charBuffer[posy + 2] = (unsigned int)green;
                    charBuffer[posy + 3] = (unsigned int)blue;
                    charBuffer[posy + 0] = (unsigned int)alpha;

                }*/
                /*
                for(int n=0;n<pixelSize;n++) {
                    try {

                        double fVal = iter->second[n];
                 //   cout << fVal << " ";
                    unsigned int val = (unsigned int)( fVal * 255);
                     posy = (yPos * width + xPos) * pixelSize +n;

                 //       cout << "posy "<< posy << "val " <<  val << "   " ;

                        charBuffer[posy] = static_cast<unsigned char>(val);
                    }catch (runtime_error &xx){
                        //just skip?
                        cout<< " error charBuffer " << xx.what() << endl;
                    }


                } */
                //  cout <<endl;
   //             iter++;
     //       }
     //   }
//}

/*
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
    int bufMax = width*height*pixelSz;
    floatBuffer = (float*)(calloc(bufMax, sizeof(float)));

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
        int bufPos = 0;
       // int count = 0;
       // while(iter != colourIcon.colourArray.end()/* && (count < bufMax)){
         //   count++;
                xPos = iter->first.val[0];
                yPos = iter->first.val[1];

              //    cout << xPos <<" " << yPos << " ";
                double *rgba = iter->second;
                for (int n = 0; n < pixelSz; n++) {
                    float fVal = iter->second[n];
                    // cout << fVal << " ";
                    bufPos = (yPos * width + xPos) * pixelSz + n;

                    floatBuffer[bufPos] = fVal;
                  //   cout << fVal << "   " ;
                }
               //  cout <<endl;
                iter++;
            }
        }
    }


/*****
int len;
unsigned char *png = stbi_write_png_to_mem((const unsigned char *) data, stride_bytes, x, y, comp, &len);
************/

/*
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

void PaintIcon::paintPNGtoBuffer(ColourIcon &colourIcon, bool withAlpha, int *len, bool switchRGBAtoARGB , unsigned char **pngBuffer){
    if(charBuffer == nullptr) {
        getCharArray(colourIcon, withAlpha, switchRGBAtoARGB);
    }
    cout<< "PaintIcon paintPNGBuffer got char array" <<endl;
    if(charBuffer != nullptr) {
        cout <<"charBuffer not null" <<endl;
        int pixelSize = withAlpha ? 4 : 3;
        *pngBuffer = stbi_write_png_to_mem((const unsigned char *) charBuffer, colourIcon.xSz * pixelSize,
                                                   colourIcon.xSz, colourIcon.ySz, pixelSize, len);
        cout <<"pngBuffer len is "<< *len <<endl;
    }
    return;
}
*/
PaintIcon::~PaintIcon() {
   // free(charBuffer);
 //   free(floatBuffer);
   // free(pngBuffer); //OK handed off
}
/*********
 *  Save png to file.
 * @param fname
 * @param width
 * @param height
 * @param rgbaBuf unsigned char pixel data. Assumes red green blue alpha so buffer should be 4*width*height length
 */
void PaintIcon::savePNG(const string& fname, int width, int height, unsigned char *rgbaBuf) {
    auto myview = boost::gil::interleaved_view(width, height, (boost::gil::rgba8_pixel_t const*)(rgbaBuf), 4 * width);
    std::ofstream imageOut2((fname).c_str(), std::ios_base::binary);

    write_view( imageOut2, myview, boost::gil::png_tag() );
    //  write_view(imageOut, view(b), boost::gil::png_tag());
    imageOut2.flush();
    imageOut2.close();

}



