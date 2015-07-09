package cn.chaobao.androidmathematicalart;

import android.graphics.Bitmap;

/**
 * Created by Liyanshun on 2015/7/6.
 */
public class MathematicalArt {
    static
    {
        System.loadLibrary("MathematicalArtLibrary");
    }

    public static  native Bitmap jniGetMathematicalArt(String path,int type);
}
