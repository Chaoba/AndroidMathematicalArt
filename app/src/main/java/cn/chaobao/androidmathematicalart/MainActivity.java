package cn.chaobao.androidmathematicalart;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ImageView v= (ImageView) findViewById(R.id.image);
        ImageView sdv= (ImageView) findViewById(R.id.sd_image);
        Bitmap bm=MathematicalArt.jniGetMathematicalArt(Environment.getExternalStorageDirectory()
                + File.separator + "MathPic.jpg", 0);
        v.setImageBitmap(bm);
//        sdv.setImageURI(Uri.parse(Environment.getExternalStorageDirectory()
//                + File.separator + "MathPic.jpg"));
    }

}
