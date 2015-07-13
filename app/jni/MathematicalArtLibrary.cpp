#include <cn_chaobao_androidmathematicalart_MathematicalArt.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <android/log.h>
#include <stdio.h>
#include <android/bitmap.h>
#define DIM 1024
#define DM1 (DIM-1)
#define _sq(x) ((x)*(x)) // square
#define _cb(x) abs((x)*(x)*(x)) // absolute value of cube
#define _cr(x) (unsigned char)(pow((x),1.0/3.0)) // cube root
#define  LOG_TAG    "jniArtLibrary"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
class JniBitmap
    {
public:
    uint32_t* _storedBitmapPixels;
    AndroidBitmapInfo _bitmapInfo;
    JniBitmap()
	{
	_storedBitmapPixels = NULL;
	}
    };
typedef struct
    {
    unsigned char alpha, red, green, blue;
    } ARGB;

uint32_t convertArgbToInt(ARGB argb)
    {
    return (argb.alpha<< 24) | (argb.red ) | (argb.green << 8)
	    | (argb.blue << 16);
    }
unsigned char RD(int i,int j,int type);
unsigned char GR(int i,int j,int type);
unsigned char BL(int i,int j,int type);
//FILE *fp;
jobject createBitmap(JNIEnv * env,uint32_t* _storedBitmapPixels);

unsigned char RD(int i,int j,int type){
    switch(type){
    case 0:
        {
            float s=3./(j+99);
            return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
        }
    case 1:
        {
            float s=3./(j+99);
            float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
            return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
        }
    case 2:
        #define P 6.03
        {
            float s=3./(j+250),y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
        }
    case 3:
        {
            return _sq(sqrt(i*1.0)+sqrt(j*1.0));
        }
    case 4:
        {
             return j^j-i^i;
        }
    case 5:
        {
             return _sq((1024-i)*(1024-j)/1024)/1024*2;
        }
    case 6:
        {
            return (char)(_sq(cos(atan2(j-512.0,i-512.0)/2))*255);
        }
    case 7:
        return sqrt(_sq(512.0-i)+_sq(512.0-j));
    }
}
unsigned char GR(int i,int j,int type){
    switch(type){
    case 0:
        {
            float s=3./(j+99);
            return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
        }
    case 1:
        {
            float s=3./(j+99);
            float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
            return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
        }
    case 2:
        {
            float s=3./(j+250);
            float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;
            return (int(5*((i+DIM)*s+y))%2+int(5*((DIM*2-i)*s+y))%2)*127;
        }
    case 3:
        {
            return _sq(sqrt(512-i*1.0)+sqrt(512-j*1.0));
        }
    case 4:
        {
             return (i-DIM)^2+(j-DIM)^2;
        }
    case 5:
        {
             return _sq((512-i)*(521-j)/512)/512*2;
        }
    case 6:
        {
            return (char)(_sq(cos(atan2(j-512.0,i-512.0)/2.0-2*acos(-1.0)/3))*255);
        }
    case 7:
        {
           return sqrt(_sq(1024.0-i)+_sq(1024.0-j));
        }
    }
}
unsigned char BL(int i,int j,int type){
    switch(type){
    case 0:
        {
            float s=3./(j+99);
            return (int((i+DIM)*s+j*s)%2+int((DIM*2-i)*s+j*s)%2)*127;
        }
    case 1:
        {
            float s=3./(j+99);
            float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM)*35)*s;
            return (int((i+DIM)*s+y)%2+int((DIM*2-i)*s+y)%2)*127;
        }
    case 2:
        {
            float s=3./(j+250);
            float y=(j+sin((i*i+_sq(j-700)*5)/100./DIM+P)*15)*s;
            return (int(29*((i+DIM)*s+y))%2+int(29*((DIM*2-i)*s+y))%2)*127;
        }
    case 3:
        {
           return _sq(sqrt(1024.0-i)+sqrt(1024.0-j));
        }
    case 4:
        {
            return i^i-j^j;
        }
    case 5:
        {
            return _sq(i*j/1024)/1024;
        }
    case 6:
        {
           return (char)(_sq(cos(atan2(j-512.0,i-512.0)/2.0+2*acos(-1.0)/3))*255);
        }
    case 7:
        {
            return sqrt(_sq(i*1.0)+_sq(j*1.0));
        }
    }
}

uint32_t pixel_write(int i, int j,int type){
//    static unsigned char color[3];
    unsigned char r=RD(i,j,type);
    unsigned char g=GR(i,j,type);
    unsigned char b=BL(i,j,type);
//    color[0] = r&255;
//    color[1] = g&255;
//    color[2] = b&255;
//    fwrite(color, 1, 3, fp);
    ARGB rgb={0xff,r,g,b};
    return convertArgbToInt(rgb);
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
    uint32_t* newBitmapPixels = new uint32_t[DIM * DIM];
//    fp = fopen(jstringTostring(env,path),"wb");
//    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    for(int j=0;j<DIM;j++)
        for(int i=0;i<DIM;i++){
          newBitmapPixels[j*DIM+i]= pixel_write(i,j,type);
          }
//    fclose(fp);

    return createBitmap(env,newBitmapPixels);
  }

jobject createBitmap(JNIEnv * env,uint32_t* _storedBitmapPixels){
    LOGD("createBitmap");
    //
    //creating a new bitmap to put the pixels into it - using Bitmap Bitmap.createBitmap (int width, int height, Bitmap.Config config) :
    //
    jclass bitmapCls = env->FindClass("android/graphics/Bitmap");
    jmethodID createBitmapFunction = env->GetStaticMethodID(bitmapCls,
	    "createBitmap",
	    "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jstring configName = env->NewStringUTF("ARGB_8888");
    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    jmethodID valueOfBitmapConfigFunction = env->GetStaticMethodID(
	    bitmapConfigClass, "valueOf",
	    "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
    jobject bitmapConfig = env->CallStaticObjectMethod(bitmapConfigClass,
	    valueOfBitmapConfigFunction, configName);
    jobject newBitmap = env->CallStaticObjectMethod(bitmapCls,
	    createBitmapFunction, DIM, DIM, bitmapConfig);
    //
    // putting the pixels into the new bitmap:
    //
    int ret;
    void* bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &bitmapPixels)) < 0)
	{
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
	}
    uint32_t* newBitmapPixels = (uint32_t*) bitmapPixels;
    int pixelsCount = DIM*DIM;
    memcpy(newBitmapPixels, _storedBitmapPixels,sizeof(uint32_t) * pixelsCount);
    AndroidBitmap_unlockPixels(env, newBitmap);
    LOGD("returning the new bitmap");
    return newBitmap;
}
