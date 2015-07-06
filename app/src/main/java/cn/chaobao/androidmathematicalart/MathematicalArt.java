package cn.chaobao.androidmathematicalart;

/**
 * Created by Liyanshun on 2015/7/6.
 */
public class MathematicalArt {
    static
    {
        System.loadLibrary("MathematicalArtLibrary");
    }

    public static  native int jniGetMathematicalArt(String path,int type);
}
