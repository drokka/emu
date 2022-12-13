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
    double *lastPoint = nullptr;  //runsample allocs 2*double
    int result = runsample(nparams, params, output, reinterpret_cast<double **>(&lastPoint), &pngBuf, &len, paramValsApplied, "default", 0.57);

  //  char msg[150]; strchr(msg,0);
 //   sprintf(msg, "pngBuf: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf[0], pngBuf[1]  ,pngBuf[2]  ,
  //          pngBuf[3] , pngBuf[4],pngBuf[len-1], len);
  //  cout << msg << endl;
    cout << paramValsApplied.str() << endl;

  //  PaintIcon::savePNG("symi1.png", 999,999, pngBuf);
  //  ofstream stream( "symi1.png", ios::out | ios::binary);
 //   if(!stream){ cout << "failed create bin file stream" << endl;}
  //  else{
  //      stream.write((char*)pngBuf, len);
  //  }

  //  free(pngBuf);
    char* parma[3] = {"runsample","1000000","H"};

    ostringstream paramValsApplied1("");
    unsigned char* pngBuf2 = nullptr;
    ostringstream outputH;
    cout<<"runsampe call 2, HEX icon" <<endl;
            result += runsample(3,parma , outputH,reinterpret_cast<double **>(&lastPoint), &pngBuf2, &len, paramValsApplied1, "default", 0.57);

    std::time_t resultH = std::time(nullptr);
    const std::string ddateH = to_string(resultH).data();
 //   PaintIcon::savePNG("symiHEX"+ddateH+".png", 999,999, pngBuf2);
/*
    ofstream stream2( "symiHEX"+ddateH+".png", ios::out | ios::binary);
    if(!stream2){ cout << "failed create bin file stream" << endl;}
    else{
        stream2.write((char*)pngBuf2, len);
    }*/

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
         cout<<"Before savePNG pngRecolrBuf row 200" << *(pngRecolrBuf + 40000) << " "
<< *(pngRecolrBuf + 40000 +1) << " " << *(pngRecolrBuf + 40000 +2 ) << " "  << *(pngRecolrBuf + 40000 +3)
<< " " << *(pngRecolrBuf + 40000 +4) << " " <<         endl;

//PaintIcon::savePNG("symiRecolour" + ddate +".png", 201,201, pngRecolrBuf);

 //       PaintIcon::savePNG("symiRecolour" + ddate +".png", 201,201, pngRecolrBuf);

         /* ofstream stream( "symiRecolour" + ddate +".png", ios::out | ios::binary);
        if(!stream){ cout << "failed create bin file stream for recolour!!!!" << endl;}
        else{
            stream.write((char*)pngRecolrBuf, reClrResult);
            cout<<"recolour of hex icon written to symiRecolour.png" <<endl;
        }
          */
    }

    /*
    PaintIcon::savePNG("symi2.png", 999,999, pngBuf2);

    ofstream stream3( "symi2.png", ios::out | ios::binary);
    if(!stream3){ cout << "failed create bin file stream2" << endl;}
    else{
        stream3.write((char*)pngBuf, len);
    }
     */

//    free(pngBuf);
    char* parmaa[12] = {"runsample", "100000","F", "121", "dummyincannotcount", "7",
                        "0.5", "0.0", "0.1","0.5","0.5","0.1"};
    unsigned char * pngBuf3 = nullptr;
    int len3 = 0;
    ostringstream output3("test");
    ostringstream paramValsApplied2("");

    double *lasty = nullptr;
    cout<< "before runsample for FRACTAL call" <<endl;
    result += runsample(12,parmaa , output3, reinterpret_cast<double **>(&lasty),&pngBuf3, &len3, paramValsApplied2, "default", 0.57);

     cout << "FRACTAL ICON DONE!!" << endl;
    cout << paramValsApplied2.str() << endl;

 //   PaintIcon::savePNG("symiF.png",121,121,pngBuf3);
 /*   ofstream stream4( "symiF.png", ios::out | ios::binary);
    if(!stream4){ cout << "failed create bin file stream3" << endl;}
    else{
        stream4.write((char*)pngBuf3, len3);
    }
*/
   // free(pngBuf3);
    return  result;
}
