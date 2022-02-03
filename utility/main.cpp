//
// Created by peter on 29/04/2020.
//

#include "runsampleNoJni.cpp"

int main(int nparams, char** params){
    ostringstream output("test");
    unsigned char *pngBuf = nullptr;
    int len=0;
  //  char* parmaaa[3] = {"runsample", "100","F"};
    int result = runsample(nparams, params, output, &pngBuf, &len);

    char msg[150]; strchrnul(msg,50);
    sprintf(msg, "pngBuf: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf[0], pngBuf[1]  ,pngBuf[2]  ,
            pngBuf[3] , pngBuf[4],pngBuf[len-1], len);
    cout << msg << endl;

    ofstream stream( "symi.png", ios::out | ios::binary);
    if(!stream){ cout << "failed create bin file stream" << endl;}
    else{
        stream.write((char*)pngBuf, len);
    }

   // free(pngBuf);
    char* parma[3] = {"runsample","100000","H"};

    result += runsample(3,parma , output, &pngBuf, &len);

    char msg2[150]; strchrnul(msg2,50);
    sprintf(msg2, "Hex pngBuf: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf[0], pngBuf[1]  ,pngBuf[2]  ,
            pngBuf[3] , pngBuf[4],pngBuf[len-1], len);
    cout << "HEX ICON DONE!!!!!!!!!!!" << msg2 << endl;


    ofstream stream2( "symi2.png", ios::out | ios::binary);
    if(!stream2){ cout << "failed create bin file stream2" << endl;}
    else{
        stream2.write((char*)pngBuf, len);
    }

//    free(pngBuf);
    char* parmaa[12] = {"runsample", "100000","F", "121", "cannot count",
                        "0.2", "0.13", "0.7","0.39","0.22","0.073","4"};
    unsigned char * pngBuf3 = nullptr;
    int len3 = 0;
    ostringstream output3("test");

    result += runsample(12,parmaa , output3, &pngBuf3, &len3);

    char msg3[150]; strchrnul(msg2,50);
    sprintf(msg3, "Fractal pngBuf3: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf3[0], pngBuf3[1]  ,pngBuf3[2]  ,
            pngBuf3[3] , pngBuf3[4],pngBuf3[len3-1], len3);
    cout << "FRACTAL ICON DONE!!"<< msg3 << endl;

    ofstream stream3( "symiF.png", ios::out | ios::binary);
    if(!stream3){ cout << "failed create bin file stream3" << endl;}
    else{
        stream3.write((char*)pngBuf3, len3);
    }

  //  free(pngBuf3);
    return  result;
}