package cn.chaobao.androidmathematicalart;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {
    ListView mList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mList = (ListView) findViewById(R.id.list);
        ImageListAdapter adapter = new ImageListAdapter(this, 16);
        mList.setAdapter(adapter);

    }

}
