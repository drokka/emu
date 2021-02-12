//
// Created by peter on 29/04/2020.
//

#include "runsampleNoJni.cpp"

int main(int nparams, char** params){
    ostringstream output("test");
    unsigned char *pngBuf = nullptr;
    int len=0;
    int result = runsample(nparams, params, output, &pngBuf, &len);

    char msg[50]; strchrnul(msg,50);
    sprintf(msg, "pngBuf: %i  %i  %i  %i  %i  last one %i len is %i.", pngBuf[0], pngBuf[1]  ,pngBuf[2]  ,
            pngBuf[3] , pngBuf[4],pngBuf[len-1], len);
    cout << msg << endl;

    ofstream stream( "symi.png", ios::out | ios::binary);
    if(!stream){ cout << "failed create bin file stream" << endl;}
    else{
        stream.write((char*)pngBuf, len);
    }

    free(pngBuf);
    return  result;
}