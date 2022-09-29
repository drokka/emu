//#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include <ctime>
#include <fstream>
#include <assert.h>
#include "SymIconApp.h"
#include "ColourIcon.h"
using namespace std;
using namespace emu::utility;

#include <string.h>

#include <jni.h>

#include <sstream>
#include <zconf.h>
#include "GeneratorException.h"

/* native method
 * to return a new VM String. See the corresponding Kotlin source
 * file located at:
 *
 *   app/src/main/java/com/example/kotlin/KotlinJni.kt
 */


static void testColourIcon(){
    int xSz =1000, ySz=1000; //Dimensions
    double bgRGBA[4] = {2.0,0.0,1.1,5.5};
    double minRGBA[4] = {0.0,0.1, 0.3, 0.5};
    double maxRGBA[4] = {1.1, 1.2,1.3,1.4};
    PointList pointList = PointList();
    bool useAlpha = false;
    RgbaList2D colourArray = RgbaList2D ();

    ColourIcon clrI = ColourIcon(xSz,ySz,bgRGBA,minRGBA,maxRGBA,&pointList,colourArray);
  //  cout<<"testColourIcon: " << colourArray.size()<<endl;
   // cout<< "size " << colourArray.size() <<endl;
   // assert(colourArray.capacity() == 1000);
    double *colour = (double*)calloc(4, sizeof(double));
           colour[0] = .1;
    colour[1] =1.2;
    colour[2] =3.3;
    colour[3] =99.9;
    clrI.colourPoint(10,999,colour);
    //cout<<"point 10,999 value " << colourArray.find(IntegerPoint2D(10,999))->second[0] <<endl;

   // assert(colourArray.at(999).size()==1000);
//   free(colour);  the pointer is added to the colour array. Freed on its deletion.
}

int reColourBuffer(stringstream& symIn, int sz, unsigned char **pngBuf, double* bg, double* min, double * max){
    //NOT used JNI.
    SymIconApp appy ;
    symIn >> appy;

    appy.sz = sz;
    appy.colourIcon.xSz = sz;
    appy.colourIcon.ySz = sz;
    appy.setColour(bg,min,max);
 //   unsigned  char *buf = nullptr;
    int nperiod = (appy.type == QuiltIcon::QuiltType::HEX)? 2:1;

        appy.colourIcon.colourIn(sz, false, pngBuf, nperiod);
    if(pngBuf == nullptr){
        appy.error = true;
        return 0;
    }
 //   int bufLen = 0;
 //   appy->createPngBuffer(pngBuf, &bufLen);
  //  delete appy;
  //  free(buf);
    return sz*sz*4;
}

int moreIterSample(long iterations, istringstream &inData, ostringstream &outData,
                   unsigned char **pngBuf, double *bgclr_c, double *minclr_c, double *maxclr_c) {
    SymIconApp* appy = new SymIconApp();
    inData >> *appy;
    appy->setIterations(iterations);
    appy->setInitPoint(appy->lastPoint);
   // if(sz >0){ appy->sz = sz;}
    appy->runGenerator();
    appy->save(outData);
    //double bgc[4] = {0.99,0.99,0.99,0.0};
    //double minc[4] = {0.0,0.0,0.0,0.0};
    //double maxgc[4] = {0.4,0.0,0.0,0.0};

    //free(rgbaByteArray);
    stringstream strlog ; strlog << "colour double arrays " << *bgclr_c << " " << *(bgclr_c+1) << " " << *(bgclr_c+2) << " " << *(bgclr_c+3) << " " << *(bgclr_c+4) << " , "
                                 << *minclr_c << " " << *(minclr_c+1) << " " << *(minclr_c+2) << " " << *(minclr_c+3)<< " " << *(minclr_c+4) << " , "
                                 << *maxclr_c << " " << *(maxclr_c+1) << " " << *(maxclr_c+2) << " " << *(maxclr_c+3)  << " " << *(maxclr_c+4) << endl;

    if(bgclr_c != nullptr) {
    appy->setColour(bgclr_c ,minclr_c,maxclr_c);
    }
   // unsigned  char *buf = nullptr;
    int nperiod = (appy->type == QuiltIcon::QuiltType::HEX)? 2:1;
    int sz = appy->sz;

    int resy = sz*sz*4;

    appy ->colourIcon.colourIn(appy->sz, false, pngBuf,nperiod);
    if(pngBuf == nullptr){
        resy = 0;
    }
 //   int bufLen = 0;
//    appy->createPngBuffer(pngBuf, &bufLen, true);

    delete appy;
  //  free(buf);
    return resy;
}

int runsample(int nparam, char** param, ostringstream &outData, double** lastPoint,unsigned char **pngBuf, int *len, ostringstream &iconDefUsed) {

    long iterations = 10000;
    if(nparam >1){
        try {
            iterations = atol(param[1]);
        }catch (...){//do nothing
        }
    }

    //long res = callSym(iterations);
    //cout << "got max hits:" << res << endl;

   // testColourIcon();

    int sz = 99;
    int degSym = 4;
    QuiltIcon::QuiltType quiltType = QuiltIcon::QuiltType::SQUARE;
    if (nparam >= 3) {
        if ('H' == param[2][0]) { quiltType = QuiltIcon::QuiltType::HEX; }
        else if ('F' == param[2][0]) { quiltType = QuiltIcon::QuiltType::FRACTAL; }
    }
    if(nparam >=5)
    {
        sz = atoi(param[3]); /* WIDTH in pixels is passed in, but assuming height the same. */
        degSym = atoi(param[5]);
    }
    double lambdaVal = 0.6;
    double alphaVal = 0.2;
    double betaVal = 0.3;
    double gammaVal = 0.4;
    double omegaVal = 0.2;
    double maVal = 0.5;


    if (nparam >= 12) {
        try {
            lambdaVal = strtod(param[6], nullptr); // HEIGHT is passed in but skipped/ignored.
            alphaVal = strtod(param[7], nullptr);
            betaVal = strtod(param[8], nullptr);
            gammaVal = strtod(param[9], nullptr);
            omegaVal = strtod(param[10], nullptr);
            maVal = strtod(param[11], nullptr);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }
    iconDefUsed.clear();
    iconDefUsed << " lambdaVal = "+to_string(lambdaVal)
            << " alphaVal = "+to_string(alphaVal)
            << " betaVal = "+to_string(betaVal)
            << " gammaVal = "+to_string(gammaVal)
            << " omegaVal = "+to_string(omegaVal)
            << " maVal = "+to_string(maVal)
            << " degSym = "+to_string(degSym)
            << " quiltType = " << int(quiltType)
            << " width = " << sz
            << " iterations = " << iterations
            << endl;
/*******************************************
    if (nparam == 12) {
        try {
            lambdaVal = strtod(param[5], nullptr); // HEIGHT is passed in but skipped/ignored.
            alphaVal = strtod(param[6], nullptr);
            betaVal = strtod(param[7], nullptr);
            gammaVal = strtod(param[8], nullptr);
            omegaVal = strtod(param[9], nullptr);
            maVal = strtod(param[10], nullptr);
            degSym = atoi(param[11]);
        } catch (...) {
            cout << "Error reading QuiltIcon parameters." << endl;
            //continue using default values
        }
    }
    *************************************************************/
    /**
    cout << "got parameters " << endl;
    cout << "lambdaVal " << lambdaVal << endl;
    cout << "alphaVal " << alphaVal << endl;
    cout << "betaVal " << betaVal << endl;
    cout << "gammaVal " << gammaVal << endl;
    cout << "omegaVal " << omegaVal << endl;
    cout << "maVal " << maVal << endl;
     **************/

    double initX = 0.307;
    double initY = 0.079;
    if(*lastPoint != nullptr && (*lastPoint)[0] != 0.0) initX = (*lastPoint)[0];
    if(*lastPoint != nullptr && (*lastPoint)[1] != 0.0) initY = (*lastPoint)[1];

    std::string fnBase = "img_a_";

    double iconParams[] = {lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal};
    int numIconParams = 6;
    double bgClr[] ={0, 0.2, .15, 1.0};
    double minClr[]= {0.0,.5,.3,1.0};
    double maxClr[] = {.3,.99,.99,1.0};

    if(nparam == 24) { //colours provided
        bgClr[0] = strtod(param[12], nullptr);
        bgClr[1] = strtod(param[13], nullptr);
        bgClr[2] = strtod(param[14], nullptr);
        bgClr[3] = strtod(param[15], nullptr);

        minClr[0] = strtod(param[16], nullptr);
        minClr[1] = strtod(param[17], nullptr);
        minClr[2] = strtod(param[18], nullptr);
        minClr[3] = strtod(param[19], nullptr);
        maxClr[0] = strtod(param[20], nullptr);
        maxClr[1] = strtod(param[21], nullptr);
        maxClr[2] = strtod(param[22], nullptr);
        maxClr[3] = strtod(param[23], nullptr);
    }

    ColourIcon::ColourFn colourFn = emu::utility::simpleColourFn;
 //   stringstream strlog ; strlog << "colour double arrays " << *bgClr << " " << *(bgClr+1) << " " << *(bgClr+2) << " " << *(bgClr+3) << " " << *(bgClr+4) << " , "
   //                              << *minClr << " " << *(minClr+1) << " " << *(minClr+2) << " " << *(minClr+3)<< " " << *(minClr+4) << " , "
     //                            << *maxClr << " " << *(maxClr+1) << " " << *(maxClr+2) << " " << *(maxClr+3)  << " " << *(maxClr+4) << endl;

    SymIconApp app(iterations, initX, initY, quiltType, fnBase, sz, iconParams, numIconParams, degSym, bgClr, minClr, maxClr, colourFn);
    app.runGenerator();
   // cout << "max hits: " << app.maxhits << endl;

    app.save(outData);
//    *lastPoint =(double *) malloc(sizeof(double ) *2);
    (*lastPoint)[0] = app.lastPoint.val[0];
    (*lastPoint)[1] = app.lastPoint.val[1];
     //std::time_t result = std::time(nullptr);
    // const std::string ddate = to_string(result).data();
   // int res = PaintIcon::paintPNG(app.colourIcon, "symi_" +ddate +".png",false);
  //  if(res == 0) {
  //  unsigned  char *buf = nullptr;
    int nperiod = (app.type == QuiltIcon::QuiltType::HEX)? 2:1;
    app.colourIcon.colourIn(sz, false, pngBuf, nperiod);
    if(pngBuf == nullptr){
        app.error = true;
    return 0;
}
 /*
    if(!app.error) {
        PaintIcon paintIcon;
         paintIcon.paintPNGtoBuffer(app.colourIcon, true, len, false, pngBuf);
        if (*pngBuf == nullptr) {
            cout << "save png image failed." << endl;
        }
    }
    */
 /********************************************
    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/

   // free(buf);
    return app.maxhits;

}

    //change the namespace when calling from different app


    /******************
extern "C"
JNIEXPORT jstring JNICALL Java_com_example_symy_MainActivityKt_callRunSampleFromJNI( JNIEnv* env, jclass thiz ) {

    ostringstream output("test");

    int result = runsample(1, (char**)({"whaty";}), output);

    string string1 = output.str().c_str();
******************/
  //  jsize otherLen = 10; //string1.size();
   // jbyteArray jbyteArray1 = env->NewByteArray(otherLen);
   // env->SetByteArrayRegion(jbyteArray1 , 0, otherLen , (jbyte*) &string1 [0]);
   //     return jbyteArray1;

 //   return env->NewStringUTF(string1.c_str());
//}

//Android or Java, as well as argb instead of rgba, also do a ?premultiply?
//The basic alpha blending formula is:
//
// dest.r = ((dest.r * (256 - source.a)) + (source.r * source.a)) >> 8;
// dest.g = ((dest.g * (256 - source.a)) + (source.g * source.a)) >> 8;
// dest.b = ((dest.b * (256 - source.a)) + (source.b * source.a)) >> 8;
//
//where dest is the background pixel and source is the pixel in your bitmap. Pre-multiplying the alpha changes this to:
//
// dest.r = ((dest.r * (256 - source.a)) >> 8) + source.premultiplied_r;
// dest.g = ((dest.g * (256 - source.a)) >> 8) + source.premultiplied_g;
// dest.b = ((dest.b * (256 - source.a)) >> 8) + source.premultiplied_b;
//
//which saves a bunch of multiplies.
// The results are all clamped to 255. I'm not claiming this is the exact formula used, but it is something pretty close to it.
void mungeRgbaToArgbAndroid(unsigned char** dst, int len /* width xheight*/) {
    for (int i = 0; i < len; i++) {

        int premultipliedR = (0xff * 0x88) >> 8;
        for (int i = 0; i < len; i++) {
            *(*dst + i) = (0x88 << 24 | premultipliedR | 0x00 << 8 | 0x00 << 16);
        }
    }
}

jobject bitmapFromJNI(
        JNIEnv *env, int sz, const unsigned char *rgbaBuffer){

        jclass bitmapConfig = env->FindClass("android/graphics/Bitmap$Config");
        jfieldID rgba8888FieldID = env->GetStaticFieldID(bitmapConfig, "ARGB_8888",
                                                         "Landroid/graphics/Bitmap$Config;");
        jobject rgba8888Obj = env->GetStaticObjectField(bitmapConfig, rgba8888FieldID);

        jclass bitmapClass = env->FindClass("android/graphics/Bitmap");
        jmethodID createBitmapMethodID = env->GetStaticMethodID(bitmapClass, "createBitmap",
                                                                "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
         jobject bitmapObj = env->CallStaticObjectMethod(bitmapClass, createBitmapMethodID, sz, sz,
                                                        rgba8888Obj);

        jintArray pixels = env->NewIntArray(sz * sz);

        jint *c_pixels = static_cast<jint *>(malloc(sizeof(jint) * sz * sz));

        for (int i = 0; i < sz * sz; i++) {
            unsigned char red = rgbaBuffer[i * 4 + 0];
            unsigned char green = rgbaBuffer[i * 4 + 1];
            unsigned char blue = rgbaBuffer[i * 4 + 2];
            unsigned char alpha = rgbaBuffer[i * 4 + 3];
            c_pixels[i] = (alpha << 24) | (red << 16) | (green << 8) | (blue);
        }

        env->SetIntArrayRegion(pixels, 0, sz * sz, c_pixels);

        jmethodID setPixelsMid = env->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
        env->CallVoidMethod(bitmapObj, setPixelsMid, pixels, 0, sz, 0, 0, sz, sz);

        //----------- Save outputData ----------------------- calling Java method on MainViewModel instance//
        //  env->CallVoidMethod(mainViewModel, saveOutputDataId, outputData, context, fname, imageFileName);
        // env->DeleteLocalRef(pngJBuf);
        // env->DeleteLocalRef(outDataJ);

        free(c_pixels);
        env->DeleteLocalRef(pixels);
        env->DeleteLocalRef(bitmapClass);
    env->DeleteLocalRef(bitmapConfig);
    env->DeleteLocalRef(rgba8888Obj);

    return bitmapObj;
    }
/****************************************************************
extern "C"
JNIEXPORT jstring JNICALL Java_com_drokka_emu_testloadimage_MainActivityKt_callRunSampleFromJNI( JNIEnv* env, jclass thiz ) {

    ostringstream output("test");
    int result = runsample(1, (char**)({"whaty";}), output);

    string string1 = output.str().c_str();

    return env->NewStringUTF(string1.c_str());
}
 *********************************/
extern "C"
JNIEXPORT jstring JNICALL Java_com_drokka_emu_symicon_SymiNativeWrapperKt_getHelloFromJNI(JNIEnv *env, jclass clazz) {
    return (*env).NewStringUTF("Hello from JNI ! freaka");
}

//-------------------------------------------------------------------------------------------
// MoreIterSample
//--------------------------------------------------------------------------------------------
extern  "C"
JNIEXPORT jobject JNICALL Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_callMoreIterSampleFromJNI(
                            JNIEnv *env,jclass jazz,
                                          jobject mainViewModel ,jobject context,
                                          jlong iterations,  jstring fname, jstring imageFileName,
                                          jdoubleArray bgClr, jdoubleArray minClr, jdoubleArray maxClr){
    jclass outputDataClass = env->FindClass("com/drokka/emu/symicon/generateicon/nativewrap/OutputData");
    jobject outputData = env->AllocObject(outputDataClass);
    jfieldID savedDataField = env->GetFieldID(outputDataClass, "savedData", "Ljava/lang/String;");

 //   jfieldID pngBufferField = env->GetFieldID(outputDataClass, "pngBuffer", "[B");
  //  jfieldID pngBufferLenField = env->GetFieldID(outputDataClass, "pngBufferLen", "I");
    jclass  mvmClass = env->FindClass("com/drokka/emu/symicon/generateicon/ui/main/MainViewModel");
  //  jmethodID saveOutputDataId = env->GetMethodID(mvmClass, "saveOutputData",
    //                                              "(Lcom/drokka/emu/symicon/generateicon/nativewrap/OutputData;Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");

    jmethodID  readDataFileId = env->GetMethodID(mvmClass, "readDataFile",
                                                 "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;");

  //  jfieldID lastPointField = env->GetFieldID(outputDataClass,"lastPoint", "[D");

    double *bgclr_c = env->GetDoubleArrayElements(bgClr, 0);
    double *minclr_c = env->GetDoubleArrayElements(minClr, 0);
    double *maxclr_c = env->GetDoubleArrayElements(maxClr, 0);
 //   stringstream strlog ; strlog << "colour double arrays " << *bgclr_c << " " << *(bgclr_c+1) << " " << *(bgclr_c+2) << " " << *(bgclr_c+3) << " "  << " , "
   //         << *minclr_c << " " << *(minclr_c+1) << " " << *(minclr_c+2) << " " << *(minclr_c+3) << " , "
     //       << *maxclr_c << " " << *(maxclr_c+1) << " " << *(maxclr_c+2) << " " << *(maxclr_c+3)  << " "  << endl;

    auto inData = static_cast<jstring>(env->CallObjectMethod(mainViewModel, readDataFileId,
                                                                context, fname));

    string symInString = env->GetStringUTFChars(inData,nullptr);
 //   int resy =1;
    if(!symInString.empty()) {
        istringstream symStream(symInString);
        //  symStream << symInString;
        ostringstream outData("stuff");
      //  int pngBufLen = moreIterSample(iterations, symStream, outData, &pngBuf, bgclr_c, minclr_c,
        //                               maxclr_c);
     //   mungeRgbaToArgbAndroid(&pngBuf, pngBufLen);

        SymIconApp appy;
        symStream >> appy;
        appy.setIterations(iterations);
        appy.setInitPoint(appy.lastPoint);
        appy.runGenerator();
        appy.save(outData);
        appy.setColour(bgclr_c ,minclr_c,maxclr_c);
        unsigned char* rgbaByteArray = nullptr;
        jobject bitmapObj = nullptr;
        int nperiod = (appy.type == QuiltIcon::QuiltType::HEX)? 2:1;
        appy .colourIcon.colourIn(appy.sz, false,&rgbaByteArray,nperiod);
        if(rgbaByteArray!= nullptr && appy.error == false) {
            jfieldID bitmapField = env->GetFieldID(outputDataClass, "bitmap",
                                                   "Landroid/graphics/Bitmap;");

            int sz = appy.sz;
            bitmapObj = bitmapFromJNI(env, sz,
                                      rgbaByteArray); //env->CallStaticObjectMethod(bitmapClass, createBitmapMethodID, sz, sz, rgba8888Obj);

            env->SetObjectField(outputData, bitmapField, bitmapObj);
        }


       // stringstream bugg;
      /*  RgbaList2DIter iter = appy->colourIcon.colourArray.begin();
        iter+=4455;
        for(int i=1; i<20;i++) {
            bugg <<
        } */
     /*   paintIcon.getCharArray(appy->colourIcon, true,   false); // TRUE for pre
        if (paintIcon.charBuffer == nullptr) {
            cout << "save char buffer failed." << endl;
            throw exception();
        } */


        auto outDataJ = env->NewStringUTF(outData.str().c_str());
        env->SetObjectField(outputData, savedDataField, outDataJ);

     //   jbyteArray pngJBuf = env->NewByteArray(pngBufLen);
     //   if (pngBuf != nullptr) {
    //        env->SetByteArrayRegion(pngJBuf, 0, pngBufLen, reinterpret_cast<const jbyte *>(pngBuf));
     //   }

     //   free(pngBuf); // SetByteArrayRegion is copying... I think
     //   env->SetObjectField(outputData, pngBufferField, pngJBuf);
      //  env->SetIntField(outputData, pngBufferLenField, pngBufLen);

     //   jdoubleArray jdoubleArray1 = env->NewDoubleArray(2);
       // env->SetDoubleArrayRegion(jdoubleArray1, 0, 2,lastPoint);
       // env->SetObjectField(outputData, lastPointField, jdoubleArray1);
       // env->ReleaseIntArrayElements(intArgs, jintArgs, 0 );
       // env->ReleaseDoubleArrayElements(dArgs, jdoubleArgs,0);

        // long time = time_t(0);
        //char * strbuf[30];
        //int fn = snprintf(strbuf,30, "symidata%{d}.sym", time);
        // string fn = "symidataJNI"+ to_string(time) +".sym";
        // auto len = fn.length();
        // jstring dataFileName = env->NewString(reinterpret_cast<const jchar *>(fn.c_str()), len);

        if(rgbaByteArray != nullptr) free(rgbaByteArray);
       env->DeleteLocalRef(inData);
       if(bitmapObj != nullptr) {
           env->DeleteLocalRef(bitmapObj);
       }
       env->DeleteLocalRef(outDataJ);
        env->DeleteLocalRef(mvmClass);
        env->DeleteLocalRef(outputDataClass);

       // resy = 0;
    }
return outputData;
}

/*
 * reColour(stringstream& symIn,
 * unsigned char **pngBuf,
 * string fname,
 * double* bg,
 * double* min,
 * double * max)
 */
extern "C"
JNIEXPORT  jobject JNICALL Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_callReColourBufFromJNI(
        JNIEnv *env, jclass jazz, jstring symIn, jint sz, jdoubleArray bgClr, jdoubleArray minClr, jdoubleArray maxClr) {

    ostringstream output("test");
    jclass outputDataClass = env->FindClass("com/drokka/emu/symicon/generateicon/nativewrap/OutputData");
    jobject outputData = env->AllocObject(outputDataClass);
  //  jfieldID savedDataField = env->GetFieldID(outputDataClass, "savedData", "Ljava/lang/String;");
  //  jfieldID paramsUsedField = env->GetFieldID(outputDataClass, "paramsUsed", "Ljava/lang/String;");

  //  jfieldID pngBufferField = env->GetFieldID(outputDataClass, "pngBuffer", "[B");
    jfieldID pngBufferLenField = env->GetFieldID(outputDataClass, "pngBufferLen", "I");

    jfieldID bitmapField = env->GetFieldID(outputDataClass, "bitmap", "Landroid/graphics/Bitmap;");

    // jsize size = env->GetArrayLength( bgClr );
    double bgClrArray[4] ;
    env->GetDoubleArrayRegion( bgClr, 0, 4, bgClrArray );

 //   jdouble* jdoubleArgs = env->GetDoubleArrayElements(dArgs,0);
    double minClrArray[4] ;
    env->GetDoubleArrayRegion( minClr, 0, 4, minClrArray );
    double maxClrArray[4] ;
    env->GetDoubleArrayRegion( maxClr, 0, 4, maxClrArray );

    int len = 0;
    auto symInString = env->GetStringUTFChars(symIn,0);
    stringstream symStream;
    symStream << symInString;
    int sizeIcon = sz;
 //   len = reColourBuffer( symStream, sz, &pngBuf,  bgClrArray,  minClrArray,  maxClrArray);

    SymIconApp appy ;
    symStream >> appy;

    appy.sz = sz;
    appy.colourIcon.xSz = sz;
    appy.colourIcon.ySz = sz;
    appy.setColour(bgClrArray,minClrArray,maxClrArray);
    unsigned  char *buf = nullptr;

    jobject bitmapObj = nullptr;
    int nperiod = (appy.type == QuiltIcon::QuiltType::HEX)? 2:1;
    appy.colourIcon.colourIn(sz, false, &buf,nperiod);
    if(buf != nullptr) {
        bitmapObj = bitmapFromJNI(env, sz, buf);

        env->SetObjectField(outputData, bitmapField, bitmapObj);
    }
    int bufLen = 0;
/*
    PaintIcon paintIcon;
    paintIcon.getCharArray(appy.colourIcon, true,   false);
    if (paintIcon.charBuffer == nullptr) {
        cout << "save char buffer failed." << endl;
        throw exception();
    }
   unsigned char *rgbaBuf = paintIcon.charBuffer;
   */
  //  mungeRgbaToArgbAndroid(&pngBuf, len);

 /*   jbyteArray pngJBuf = env->NewByteArray(len);
    if (pngBuf != nullptr) {
        env->SetByteArrayRegion(pngJBuf, 0, len, (jbyte *) pngBuf);
    }
*/
  //  env->SetObjectField(outputData, pngBufferField, pngJBuf);
  //  env->SetIntField(outputData, pngBufferLenField,  len);



  //    env->ReleaseDoubleArrayElements(bgClr, bgClrArray,0);
  //  env->ReleaseDoubleArrayElements(minClr, minClrArray,0);
 //   env->ReleaseDoubleArrayElements(maxClr, maxClrArray,0);

    free(buf);
    if(bitmapObj != nullptr) {
        env->DeleteLocalRef(bitmapObj);
    }
    env->DeleteLocalRef(outputDataClass);
    env->ReleaseStringUTFChars(symIn,symInString);

    return outputData;
}

extern "C"
JNIEXPORT  jobject JNICALL Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_callRunSampleFromJNI(
        JNIEnv *env, jclass clazz, jintArray intArgs, jbyte iconImageType, jdoubleArray dArgs) {

    bool generateError = false;
    ostringstream output("test");
    jclass outputDataClass = env->FindClass(
            "com/drokka/emu/symicon/generateicon/nativewrap/OutputData");
    jobject outputData = env->AllocObject(outputDataClass);
    jfieldID savedDataField = env->GetFieldID(outputDataClass, "savedData", "Ljava/lang/String;");
    jfieldID paramsUsedField = env->GetFieldID(outputDataClass, "paramsUsed", "Ljava/lang/String;");

    //   jfieldID pngBufferField = env->GetFieldID(outputDataClass, "pngBuffer", "[B");
    //   jfieldID pngBufferLenField = env->GetFieldID(outputDataClass, "pngBufferLen", "I");

    jsize lenArgs = env->GetArrayLength(intArgs);
    jfieldID lastPointField = env->GetFieldID(outputDataClass, "lastPoint", "[D");
    cout << "length " << lenArgs << endl;

    //int intArg0 = env->GetInt(env->GetObjectArrayElement(intArgs,0));
    jint *jintArgs = env->GetIntArrayElements(intArgs, 0);
    //Size ie width should be second
    int sz = jintArgs[1];
    string argvStr = "whaty ";
    argvStr += to_string(jintArgs[0]);
    argvStr += " ";
    argvStr += (char) iconImageType;
    argvStr += " ";
    argvStr += to_string(jintArgs[1]);
    argvStr += " ";
    argvStr += to_string(jintArgs[2]);

    argvStr += " ";
    argvStr += to_string(jintArgs[3]);

    jdouble *jdoubleArgs = env->GetDoubleArrayElements(dArgs, 0);

    int lenDargs = env->GetArrayLength(dArgs); //colours last 12.... optional
    for (int ii = 0; ii < lenDargs; ii++) {
        argvStr += " ";
        argvStr += to_string(jdoubleArgs[ii]);
    }


    unsigned char *rgbaBuf = nullptr;
    int len = 0;
    int result = 0;

    int nparam = 6 + lenDargs; /* for the char** argument passed in */
    int j = 0;
    char *argy[nparam];

    char *buff = (char *) calloc(2000, sizeof(char));

    buff = strcpy(buff, argvStr.c_str());
    char *p2 = strtok(buff, " ");
    while (p2) {
        argy[j++] = p2;
        p2 = strtok(0, " ");
    }
    ostringstream captureParams("");
    //  argy[nparam -1] = p2; /*ouch got to get the last one. horrible *******/
    // const char** paramChars =    env->GetCharArrayElements(params,NULL);
    //   if (params != 0){
    double *lastPoint = static_cast<double *>(malloc(2 * sizeof(double)));
    lastPoint[0] = 0.0;
    lastPoint[1] = 0.0;
    result = runsample(nparam, argy, output, reinterpret_cast<double **>(&lastPoint), &rgbaBuf,
                       &len, captureParams);

    if (result == 0 || rgbaBuf == nullptr) {
        generateError = true;
        output << "Error " << endl;
    }

    // mungeRgbaToArgbAndroid(&pngBuf, result);

    //   }else {
    //     result = runsample(1, (char **) ({ "whaty"; }), output, &pngBuf, &len);
    //  }
    char strBuf[] = "give me a big enough string for my output line please, thankyou";
   // cout << sprintf(strBuf, "pngBuf start is: %i  %i  %i    and last is  %i", rgbaBuf[0],
     //               rgbaBuf[1], rgbaBuf[2], rgbaBuf[len - 1]) << endl;
    jstring savedData = env->NewStringUTF(output.str().c_str());
    jstring paramsUsed = env->NewStringUTF(captureParams.str().c_str());
    env->SetObjectField(outputData, savedDataField, savedData);
    env->SetObjectField(outputData, paramsUsedField, paramsUsed);

    /*
    jbyteArray pngJBuf = env->NewByteArray(len);
    if (pngBuf != nullptr) {
       env->SetByteArrayRegion(pngJBuf, 0, len, (jbyte *) pngBuf);
    }

    env->SetObjectField(outputData, pngBufferField, pngJBuf);
    env->SetIntField(outputData, pngBufferLenField,  len);
*/
    jobject bitmapObj = nullptr;
    if (!generateError) {
    bitmapObj = bitmapFromJNI(env, sz, rgbaBuf);
}


    jfieldID bitmapField = env->GetFieldID(outputDataClass, "bitmap", "Landroid/graphics/Bitmap;");
    env->SetObjectField(outputData, bitmapField, bitmapObj);

    jdoubleArray jdoubleArray1 = env->NewDoubleArray(2);
    env->SetDoubleArrayRegion(jdoubleArray1, 0, 2,lastPoint);
    env->SetObjectField(outputData, lastPointField, jdoubleArray1);
    env->ReleaseIntArrayElements(intArgs, jintArgs, 0 );
    env->ReleaseDoubleArrayElements(dArgs, jdoubleArgs,0);

   free(buff);
    free(lastPoint);
    if(rgbaBuf != nullptr) {
        free(rgbaBuf); // SetByteArrayRegion is copying... I think
    }
if(bitmapObj != nullptr) {
    env->DeleteLocalRef(bitmapObj);  //???? did setobjectfield copy???
}
   env->DeleteLocalRef(savedData);
    env->DeleteLocalRef(paramsUsed);
    env->DeleteLocalRef(outputDataClass);
    return outputData;

}

extern "C"

JNIEXPORT jstring JNICALL
Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_getHelloFromJNI(JNIEnv *env,
                                                                                        jclass clazz) {
   return (*env).NewStringUTF("Hello from JNI ! freaka");
}
