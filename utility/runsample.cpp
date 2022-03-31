//#include <iostream>
#include <map>
#include "QuiltIcon.h"

#include "Generator.h"
#include <ctime>
#include <fstream>
#include <assert.h>
#include "SymIconApp.h"
#include "ColourIcon.h"
#include "image/PaintIcon.h"
using namespace std;
using namespace emu::utility;

#include <string.h>

#include <jni.h>
#include <sstream>
#include <zconf.h>

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
int reColour(stringstream& symIn, unsigned char **pngBuf, string fname, double* bg, double* min, double * max){
    SymIconApp* appy = new SymIconApp();
    symIn >> *appy;

    appy->setColour(bg,min,max);
    appy ->colourIcon.colourIn();
    int bufLen = 0;
    appy->createPNG(pngBuf, &bufLen, fname);
    return bufLen;
}
int reColourBuffer(stringstream& symIn, int sz, unsigned char **pngBuf, double* bg, double* min, double * max){
    SymIconApp* appy = new SymIconApp();
    symIn >> *appy;

    appy->sz = sz;
    appy->colourIcon.xSz = sz;
    appy->colourIcon.ySz = sz;
    appy->setColour(bg,min,max);
    appy ->colourIcon.colourIn(sz);
    int bufLen = 0;
    appy->createPngBuffer(pngBuf, &bufLen);
    return bufLen;
}

int runsample(int nparam, char** param, ostringstream &outData, unsigned char **pngBuf, int *len, ostringstream &iconDefUsed) {

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
    std::string fnBase = "img_a_";

    double iconParams[] = {lambdaVal, alphaVal, betaVal, gammaVal, omegaVal, maVal};
    int numIconParams = 6;
    double bgClr[] ={0, 0.2, .15, .5};
    double minClr[]= {0.0,.5,.3,.5};
    double maxClr[] = {.3,.99,.99,1};

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

    SymIconApp app(iterations, initX, initY, quiltType, fnBase, sz, iconParams, numIconParams, degSym, bgClr, minClr, maxClr, colourFn);
    app.runGenerator();
   // cout << "max hits: " << app.maxhits << endl;

    app.save(outData);
     //std::time_t result = std::time(nullptr);
    // const std::string ddate = to_string(result).data();
   // int res = PaintIcon::paintPNG(app.colourIcon, "symi_" +ddate +".png",false);
  //  if(res == 0) {

    if(!app.error) {
        PaintIcon paintIcon;
        *pngBuf = paintIcon.paintPNGtoBuffer(app.colourIcon, false, len);
        if (*pngBuf == nullptr) {
            cout << "save png image failed." << endl;
        }
    }
 /********************************************
    res = PaintIcon::paintHDR(app.colourIcon, "symi_" +ddate +".hdr",false);
    if(res == 0) {
        cout <<"save hdr image failed." << endl;
    }
   ***************************************************************/
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
    return (*env).NewStringUTF("Hello from JNI ! freaka");}

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
    jfieldID savedDataField = env->GetFieldID(outputDataClass, "savedData", "Ljava/lang/String;");
    jfieldID paramsUsedField = env->GetFieldID(outputDataClass, "paramsUsed", "Ljava/lang/String;");

    jfieldID pngBufferField = env->GetFieldID(outputDataClass, "pngBuffer", "[B");
    jfieldID pngBufferLenField = env->GetFieldID(outputDataClass, "pngBufferLen", "I");

   // jsize size = env->GetArrayLength( bgClr );
    double bgClrArray[4] ;
    env->GetDoubleArrayRegion( bgClr, 0, 4, bgClrArray );

 //   jdouble* jdoubleArgs = env->GetDoubleArrayElements(dArgs,0);
    double minClrArray[4] ;
    env->GetDoubleArrayRegion( minClr, 0, 4, minClrArray );
    double maxClrArray[4] ;
    env->GetDoubleArrayRegion( maxClr, 0, 4, maxClrArray );


    unsigned char *pngBuf = nullptr;
    int len = 0;
    string symInString = env->GetStringUTFChars(symIn,NULL);
    stringstream symStream;
    symStream << symInString;
    int sizeIcon = sz;
    len = reColourBuffer( symStream, sz, &pngBuf,  bgClrArray,  minClrArray,  maxClrArray);

    jbyteArray pngJBuf = env->NewByteArray(len);
    if (pngBuf != nullptr) {
        env->SetByteArrayRegion(pngJBuf, 0, len, (jbyte *) pngBuf);
    }

    free(pngBuf); // SetByteArrayRegion is copying... I think
    env->SetObjectField(outputData, pngBufferField, pngJBuf);
    env->SetIntField(outputData, pngBufferLenField,  len);

  //  env->ReleaseDoubleArrayElements(bgClr, bgClrArray,0);
  //  env->ReleaseDoubleArrayElements(minClr, minClrArray,0);
 //   env->ReleaseDoubleArrayElements(maxClr, maxClrArray,0);

    return outputData;
}

extern "C"
JNIEXPORT  jobject JNICALL Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_callRunSampleFromJNI(
        JNIEnv *env, jclass clazz, jintArray intArgs, jbyte iconImageType, jdoubleArray dArgs) {

    ostringstream output("test");
    jclass outputDataClass = env->FindClass("com/drokka/emu/symicon/generateicon/nativewrap/OutputData");
    jobject outputData = env->AllocObject(outputDataClass);
    jfieldID savedDataField = env->GetFieldID(outputDataClass, "savedData", "Ljava/lang/String;");
    jfieldID paramsUsedField = env->GetFieldID(outputDataClass, "paramsUsed", "Ljava/lang/String;");

    jfieldID pngBufferField = env->GetFieldID(outputDataClass, "pngBuffer", "[B");
    jfieldID pngBufferLenField = env->GetFieldID(outputDataClass, "pngBufferLen", "I");

    jsize lenArgs = env->GetArrayLength(intArgs);
    cout<< "length "<< lenArgs <<endl;

    //int intArg0 = env->GetInt(env->GetObjectArrayElement(intArgs,0));
    jint* jintArgs = env->GetIntArrayElements(intArgs, 0);
    string argvStr = "whaty ";
    argvStr += to_string(jintArgs[0]);
    argvStr += " ";
    argvStr += (char)iconImageType;
    argvStr += " ";
    argvStr += to_string(jintArgs[1]);
    argvStr += " ";
    argvStr += to_string( jintArgs[2]);

    argvStr += " ";
    argvStr += to_string( jintArgs[3]);

    jdouble* jdoubleArgs = env->GetDoubleArrayElements(dArgs,0);

    int lenDargs = env->GetArrayLength(dArgs); //colours last 12.... optional
    for(int ii = 0; ii< lenDargs; ii++){
        argvStr += " ";
        argvStr += to_string(jdoubleArgs[ii]);
    }


    unsigned char *pngBuf = nullptr;
    int len = 0;
    int result = 0;

    int nparam = 6 + lenDargs; /* for the char** argument passed in */
    int j = 0;
    char *argy[nparam];

    char * buff = (char*)calloc(200 ,  sizeof(char) );

    buff = strcpy(buff, argvStr.c_str() );
    char *p2 = strtok(buff, " ");
    while (p2 )
    {
        argy[j++] = p2;
        p2 = strtok(0, " ");
    }
    ostringstream captureParams("");
  //  argy[nparam -1] = p2; /*ouch got to get the last one. horrible *******/
   // const char** paramChars =    env->GetCharArrayElements(params,NULL);
 //   if (params != 0){
        result = runsample(nparam, argy , output, &pngBuf, &len, captureParams);

 //   }else {
   //     result = runsample(1, (char **) ({ "whaty"; }), output, &pngBuf, &len);
  //  }
    char strBuf[] = "give me a big enough string for my output line please, thankyou";
cout << sprintf(strBuf,"pngBuf start is: %i  %i  %i    and last is  %i", pngBuf[0],pngBuf[1], pngBuf[2], pngBuf[len-1])  << endl;
    if(result ==0){
        return nullptr;
    }
    env->SetObjectField ( outputData,savedDataField,env->NewStringUTF(output.str().c_str()));
    env->SetObjectField ( outputData,paramsUsedField,env->NewStringUTF(captureParams.str().c_str()));

    jbyteArray pngJBuf = env->NewByteArray(len);
    if (pngBuf != nullptr) {
       env->SetByteArrayRegion(pngJBuf, 0, len, (jbyte *) pngBuf);
    }

    free(pngBuf); // SetByteArrayRegion is copying... I think
    env->SetObjectField(outputData, pngBufferField, pngJBuf);
    env->SetIntField(outputData, pngBufferLenField,  len);

    env->ReleaseIntArrayElements(intArgs, jintArgs, 0 );
    env->ReleaseDoubleArrayElements(dArgs, jdoubleArgs,0);
   free(buff);

    return outputData;

}

extern "C"

JNIEXPORT jstring JNICALL
Java_com_drokka_emu_symicon_generateicon_nativewrap_SymiNativeWrapperKt_getHelloFromJNI(JNIEnv *env,
                                                                                        jclass clazz) {
   return (*env).NewStringUTF("Hello from JNI ! freaka");
}
