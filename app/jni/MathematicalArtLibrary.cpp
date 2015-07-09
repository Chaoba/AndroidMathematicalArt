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

typedef struct
    {
    unsigned char alpha, red, green, blue;
    } ARGB;

uint32_t convertArgbToInt(ARGB argb)
    {
    return (argb.alpha<< 24) | (argb.red ) | (argb.green << 8)
	    | (argb.blue << 16);
    }

void convertIntToArgb(uint32_t pixel, ARGB* argb)
    {
    argb->red = ((pixel >> 24) & 0xff);
    argb->green = ((pixel >> 16) & 0xff);
    argb->blue = ((pixel >> 8) & 0xff);
    argb->alpha = (pixel & 0xff);
    }

FILE *fp;
jobject createBitmap(JNIEnv * env,uint32_t* _storedBitmapPixels);

uint32_t pixel_write(int i, int j){
    static unsigned char color[3];
    unsigned char r=RD(i,j);
    unsigned char g=GR(i,j);
    unsigned char b=BL(i,j);
    color[0] = r&255;
    color[1] = g&255;
    color[2] = b&255;
    fwrite(color, 1, 3, fp);
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
  LOGD("jniGetMathematicalArt");
   uint32_t* newBitmapPixels = new uint32_t[DIM * DIM];
    fp = fopen(jstringTostring(env,path),"wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIM, DIM);
    for(int j=0;j<DIM;j++)
        for(int i=0;i<DIM;i++){
          newBitmapPixels[j*DIM+i]= pixel_write(i,j);
          }
    fclose(fp);

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
