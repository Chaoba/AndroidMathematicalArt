package cn.chaobao.androidmathematicalart;

import android.content.Context;
import android.graphics.Bitmap;
import android.os.Environment;
import android.util.Log;
import android.util.LruCache;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;

import rx.Observable;
import rx.Subscriber;
import rx.android.schedulers.AndroidSchedulers;
import rx.schedulers.Schedulers;

/**
 * Created by Liyanshun on 2015/7/7.
 */
public class ImageListAdapter extends BaseAdapter {
    private static final String TAG = "AccidentTypeAdapter";
    private int mCount;
    private Context mContext;
    private LruCache<Integer, Bitmap> cache = new LruCache<Integer, Bitmap>(16 * 1024 * 1024) {
        @Override
        protected void entryRemoved(boolean evicted, Integer key, Bitmap oldValue, Bitmap newValue) {
            super.entryRemoved(evicted, key, oldValue, newValue);
            Log.i(TAG, "revmoved:" + key);
            if (evicted && oldValue != null) {
                oldValue.recycle();
            }
        }

        @Override
        protected int sizeOf(Integer key, Bitmap value) {
            int size = value.getByteCount();
            Log.i(TAG, "size:" + size);
            return size;
        }
    };

    public ImageListAdapter(Context c, int count) {
        mCount = count;
        mContext = c;
    }

    @Override
    public int getCount() {
        return mCount;
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        Log.i(TAG, "Getview:" + position);
        final ViewHolder holder = new ViewHolder();
        convertView = View.inflate(mContext, R.layout.list_item, null);
        holder.mImg = (ImageView) convertView.findViewById(R.id.img);
        holder.mTxt = (TextView) convertView.findViewById(R.id.time);
        convertView.setTag(holder);

        Bitmap bm = cache.get(position);
        if (bm != null) {
            Log.i(TAG, "has bitmap");
            holder.mImg.setImageBitmap(bm);
        } else {
            holder.mImg.setImageResource(R.mipmap.ic_launcher);
            Observable observable = Observable.create(new Observable.OnSubscribe<Long>() {
                @Override
                public void call(Subscriber<? super Long> subscriber) {
                    long startTime = System.currentTimeMillis();
                    Bitmap bm = MathematicalArt.jniGetMathematicalArt(Environment.getExternalStorageDirectory()
                            + File.separator + "MathPic.jpg", getCount()-position-1);
                    cache.put(position, bm);
                    subscriber.onNext(startTime);
                    subscriber.onCompleted();
                }
            });
            observable
                    .observeOn(AndroidSchedulers.mainThread())
                    .subscribeOn(Schedulers.io())
                    .subscribe(new Subscriber<Long>() {


                        @Override
                        public void onCompleted() {
                        }

                        @Override
                        public void onError(Throwable e) {
                        }

                        @Override
                        public void onNext(Long startTime) {
                            Log.i(TAG, "onNext");
                            Bitmap bm = cache.get(position);
                            if (bm != null) {
                                holder.mImg.setImageBitmap(bm);
                            }
                            long endTime = System.currentTimeMillis();
                            holder.mTxt.setText((endTime - startTime) + "ms");
                        }
                    });
        }
        return convertView;
    }

    class ViewHolder {
        ImageView mImg;
        TextView mTxt;

    }

}
