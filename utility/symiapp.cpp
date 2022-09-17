//
// Created by peter on 2/09/2022.
//
#include <iostream>
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <fstream>
#include "runsampleNoJni.cpp"

int doMore(char **pString);

int main(int argc , char** argv){

 // pass through the char* args to runsample call.
 // iterations
 // type
 // size
 // width(size)
 // degree_sym
 // lambdaVal = 0.6;
    //    double alphaVal = 0.2;
    //    double betaVal = 0.3;
    //    double gammaVal = 0.4;
    //    double omegaVal = 0.2;
    //    double maVal = 0.5;                                         12
// bgClr[0] = strtod(pString[12], nullptr);                  double 0.0 - 1.0
//        bgClr[1] = strtod(pString[13], nullptr);
//        bgClr[2] = strtod(pString[14], nullptr);
//        bgClr[3] = strtod(pString[15], nullptr);
//
//        minClr[0] = strtod(pString[16], nullptr);
//        minClr[1] = strtod(pString[17], nullptr);
//        minClr[2] = strtod(pString[18], nullptr);
//        minClr[3] = strtod(pString[19], nullptr);
//        maxClr[0] = strtod(pString[20], nullptr);
//        maxClr[1] = strtod(pString[21], nullptr);
//        maxClr[2] = strtod(pString[22], nullptr);
//        maxClr[3] = strtod(pString[23], nullptr);                24

if(argc == 16){ //iters  filename    size  colours
     doMore(argv);

}else {
    ostringstream outData("");
    ostringstream iconDefUsed("");
    auto *lastPoint = static_cast<double *>(malloc(sizeof(double) * 2));
    lastPoint[0] = .2707;
    lastPoint[1] = .5901;
    unsigned char *pngBuf = nullptr;
    int len = 0;

    int resy = runsample(argc, argv, outData, &lastPoint, &pngBuf, &len, iconDefUsed);


    cout << "argc is " << argc << endl;
    cout << iconDefUsed.str() << endl;
    outData.clear();
    return resy;
}
}

int doMore(char **pString) {
    long iterations = atol(pString[1]);
    int sz = atoi(pString[2]);

    char* inDataFile = pString[3];

    double bgClr[4];
    double minClr[4];
    double maxClr[4];

    bgClr[0] = strtod(pString[4], nullptr);
    bgClr[1] = strtod(pString[5], nullptr);
    bgClr[2] = strtod(pString[6], nullptr);
    bgClr[3] = strtod(pString[7], nullptr);

    minClr[0] = strtod(pString[8], nullptr);
    minClr[1] = strtod(pString[9], nullptr);
    minClr[2] = strtod(pString[10], nullptr);
    minClr[3] = strtod(pString[11], nullptr);
    maxClr[0] = strtod(pString[12], nullptr);
    maxClr[1] = strtod(pString[13], nullptr);
    maxClr[2] = strtod(pString[14], nullptr);
    maxClr[3] = strtod(pString[15], nullptr);

    ifstream inSymi;
    inSymi.open(inDataFile);
    SymIconApp appy;
    inSymi >> appy;
    appy.sz = sz;
    appy.colourIcon.xSz = sz; appy.colourIcon.ySz = sz;

    appy.setColour(bgClr, minClr, maxClr);

    cout<< "after setColour " << appy.colourIcon.bgRGBA[0] <<" " << appy.colourIcon.bgRGBA[1] <<" "
    <<     appy.colourIcon.bgRGBA[2] <<" " << appy.colourIcon.bgRGBA[3] << endl;
    cout<< "after setColour " << appy.colourIcon.minRGBA[0] <<" " << appy.colourIcon.minRGBA[1] <<" "
        <<     appy.colourIcon.minRGBA[2] <<" " << appy.colourIcon.minRGBA[3] << endl;
    cout<< "after setColour " << appy.colourIcon.maxRGBA[0] <<" " << appy.colourIcon.maxRGBA[1] <<" "
        <<     appy.colourIcon.maxRGBA[2] <<" " << appy.colourIcon.maxRGBA[3] << endl;

    appy.setIterations(iterations);
    appy.setInitPoint(appy.lastPoint);
    appy.runGenerator();

    std::time_t result = std::time(nullptr);
    const std::string ddate = to_string(result);

    string fname("symD" +ddate);
    ofstream symFile;
    symFile.open((fname +".symd").c_str(), std::ofstream::out);
    cout <<"writing the SymIconApp to file " + fname <<endl;
    symFile << appy; // use the operator << defn


    unsigned char *byteArray = nullptr;
    appy.colourIcon.colourIn(sz, false, &byteArray);
 //   unsigned char *pngBuf = nullptr;
  //  int len = 0;
   // appy.createByteBuffer(&byteArray,&len);

 //   cout << "got len " << len <<endl;
    // char * fname = "symi_" + ddate + ".png";
    if(!appy.error) {
       // int resy  = stbi_write_png(fname.c_str(), sz, sz, 4, byteArray,sz * 4);
    //    appy.createPNG(&pngBuf, &len, "symi_" + ddate + ".png");  //zipped buffer

       // boost::gil::rgba8_image_t rgba8Image(sz,sz);

        auto myview = boost::gil::interleaved_view(sz, sz, (boost::gil::rgba8_pixel_t const*)(byteArray), 4 * sz);
//        cout <<"doMore write png produced len " << len << endl;

            cout <<"after set pixels" <<endl;

            // write data into image
         //   std::ofstream imageOut((fname + "gil.png").c_str(), std::ios_base::binary);

            std::ofstream imageOut2((fname + "gil2.png").c_str(), std::ios_base::binary);

             write_view( imageOut2, myview, boost::gil::png_tag() );
          //  write_view(imageOut, view(b), boost::gil::png_tag());
            imageOut2.flush();
            imageOut2.close();
            cout << "apparently wrote files" << endl;
            }
    else{
        cout << "error!!!" <<endl;
        return  -1;
    }
  //  free(pngBuf);

    free(byteArray);

    return 0;
}
