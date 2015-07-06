#include <cn_chaobao_androidmathematicalart_MathematicalArt.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#define DIM 1024
#define DM1 (DIM-1)
#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root


unsigned char RD(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
}
unsigned char GR(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
}
unsigned char BL(int i,int j){
    float s=3./(j+99);
    return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
}

void pixel_write(int,int);
FILE *fp;

void pixel_write(int i, int j){
    static unsigned char color[3];
    color[0] = RD(i,j)&255;
    color[1] = GR(i,j)&255;
    color[2] = BL(i,j)&255;
    fwrite(color, 1, 3, fp);
}
char* jstringTostring(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
    rtn = (char*)malloc(alen + 1);

    memcpy(rtn, ba, alen);
    rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}
JNIEXPORT jobject JNICALL Java_cn_chaobao_androidmathematicalart_MathematicalArt_jniGetMathematicalArt
  (JNIEnv * env, jclass cla, jstring path,jint type){
    fp = fopen(jstringTostring(env,path),"wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    for(int j=0;j<DIM;j++)
        for(int i=0;i<DIM;i++)
            pixel_write(i,j);
    fclose(fp);
  }


