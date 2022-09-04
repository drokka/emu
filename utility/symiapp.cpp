//
// Created by peter on 2/09/2022.
//

#include "runsampleNoJni.cpp"
#include "..././../../stb/stb_image_write.h"

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
    return doMore(argv);
}
 ostringstream outData("");
 ostringstream iconDefUsed("");
 auto  *lastPoint = static_cast<double *>(malloc(sizeof(double) * 2));
 lastPoint[0] = .2707; lastPoint[1] = .5901;
    unsigned char *pngBuf = nullptr;
    int len =0;

    int resy =  runsample(argc, argv, outData, &lastPoint, &pngBuf, &len, iconDefUsed) ;




        cout << "argc is " << argc << endl;
       cout <<  iconDefUsed.str() <<endl;
    outData.clear();
    return resy;
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

    appy.setColour(bgClr, minClr, maxClr);

    appy.setIterations(iterations);
    appy.setInitPoint(appy.lastPoint);
    appy.runGenerator();

    std::time_t result = std::time(nullptr);
    const std::string ddate = to_string(result).data();

    string fname("symD" +ddate+".symd");
    ofstream symFile;
    symFile.open(fname.c_str(), std::ofstream::out);
    cout <<"writing the SymIconApp to file " + fname <<endl;
    symFile << appy; // use the operator << defn


    unsigned char *byteArray = nullptr;
    appy.colourIcon.colourIn(sz, false, &byteArray);
    unsigned char *pngBuf = nullptr;
    int len = 0;
    appy.createByteBuffer(&pngBuf,&len);

    cout << "got len " << len <<endl;
    // char * fname = "symi_" + ddate + ".png";
    if(!appy.error) {
      //  int resy  = stbi_write_png(fname.c_str(), sz, sz, 4, byteArray,sz * 4);
        appy.createPNG(&pngBuf, &len, "symi_" + ddate + ".png");
        cout <<"doMore write png produced len " << len << endl;
    }
    else{
        cout << "error!!!" <<endl;
        return  -1;
    }
    free(pngBuf);

    free(byteArray);

    return 0;
}
