//
// Created by peter on 29/04/2020.
//

#include "runsampleNoJni.cpp"

int main(int nparams, char** params){
    ostringstream output("test");
    unsigned char *pngBuf = nullptr;
    int len=0;
  //  char* parmaaa[3] = {"runsample", "100","F"};
    ostringstream paramValsApplied("Icon definition and parameters captured: ");

    cout<<"runsample call 1"<<endl;
    double lastPoint[2];
    int result = runsample(nparams, params, output, reinterpret_cast<double **>(&lastPoint), &pngBuf, &len, paramValsApplied);

    char msg[150]; strchrnul(msg,50);
    sprintf(msg, "pngBuf: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf[0], pngBuf[1]  ,pngBuf[2]  ,
            pngBuf[3] , pngBuf[4],pngBuf[len-1], len);
    cout << msg << endl;
    cout << paramValsApplied.str() << endl;

    ofstream stream( "symi1.png", ios::out | ios::binary);
    if(!stream){ cout << "failed create bin file stream" << endl;}
    else{
        stream.write((char*)pngBuf, len);
    }

   // free(pngBuf);
    char* parma[3] = {"runsample","1000000","H"};

    ostringstream paramValsApplied1("");
    unsigned char* pngBuf2 = nullptr;
    ostringstream outputH;
    cout<<"runsampe call 2, HEX icon" <<endl;
            result += runsample(3,parma , outputH,reinterpret_cast<double **>(&lastPoint), &pngBuf2, &len, paramValsApplied1);

    std::time_t resultH = std::time(nullptr);
    const std::string ddateH = to_string(resultH).data();
    ofstream stream2( "symiHEX"+ddateH+".png", ios::out | ios::binary);
    if(!stream2){ cout << "failed create bin file stream" << endl;}
    else{
        stream2.write((char*)pngBuf2, len);
    }

    cout << "HEX ICON DONE!!!!!!!!!!!"  << endl;
    cout << paramValsApplied1.str() << endl;
    stringstream hexSymApp; hexSymApp << outputH.str();
 //   cout <<"hexSymApp is: " <<endl;
  //  cout << outputH.str() <<endl;
    unsigned char *pngRecolrBuf = nullptr;
    double bg[4]  = {0.99,0.0,0.0,0.0};
    double minC[4] = {0.0,0.9,0.0,0.0};
    double maxC[4] = {0.0,0.01,0.99,0.9};
    int reClrResult = -1;
    cout<<"recolour on hex"<<endl;
    reClrResult = reColourBuffer(hexSymApp, 201, &pngRecolrBuf, bg, minC, maxC);
    if(reClrResult < 1){
        cout<< "recolourFAILED!!!!!!!!!!!!!!!!!!" <<endl;
    }else{
         std::time_t result = std::time(nullptr);
         const std::string ddate = to_string(result).data();

          ofstream stream( "symiRecolour" + ddate +".png", ios::out | ios::binary);
        if(!stream){ cout << "failed create bin file stream for recolour!!!!" << endl;}
        else{
            stream.write((char*)pngRecolrBuf, reClrResult);
            cout<<"recolour of hex icon written to symiRecolour.png" <<endl;
        }
    }

    ofstream stream3( "symi2.png", ios::out | ios::binary);
    if(!stream3){ cout << "failed create bin file stream2" << endl;}
    else{
        stream3.write((char*)pngBuf, len);
    }

//    free(pngBuf);
    char* parmaa[12] = {"runsample", "100000","F", "121", "cannot count",
                        "0.2", "0.13", "0.7","0.39","0.22","0.073","4"};
    unsigned char * pngBuf3 = nullptr;
    int len3 = 0;
    ostringstream output3("test");
    ostringstream paramValsApplied2("");

    result += runsample(12,parmaa , output3, reinterpret_cast<double **>(&lastPoint),&pngBuf3, &len3, paramValsApplied2);

     cout << "FRACTAL ICON DONE!!" << endl;
    cout << paramValsApplied2.str() << endl;

    ofstream stream4( "symiF.png", ios::out | ios::binary);
    if(!stream4){ cout << "failed create bin file stream3" << endl;}
    else{
        stream4.write((char*)pngBuf3, len3);
    }

  //  free(pngBuf3);
    return  result;
}
