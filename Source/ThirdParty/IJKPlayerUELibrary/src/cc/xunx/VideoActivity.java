package cc.xunx;

import android.app.Activity;
import android.content.res.Configuration;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;


import com.dou361.ijkplayer.bean.VideoijkBean;
import com.dou361.ijkplayer.widget.PlayStateParams;
import com.dou361.ijkplayer.widget.PlayerView;


import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;


public class VideoActivity extends Activity {

    private String json;
    private View rootView;
    private PlayerView player;
    private String Title = "";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        Bundle extras = getIntent().getExtras();
        json = extras.getSerializable("Json").toString();

        ArrayList<VideoijkBean> list = new ArrayList<VideoijkBean>();
        try {
            JSONObject jsonObject = new JSONObject(json);
            Title = jsonObject.getString("Title");
            JSONArray jsonArray = jsonObject.getJSONArray("array");
            for (int i=0;i<jsonArray.length();i++){
                JSONObject _object =jsonArray.getJSONObject(i);
                String name =  _object.getString("name");
                String url =  _object.getString("url");
                VideoijkBean vb = new VideoijkBean();
                vb.setUrl(url);
                vb.setStream(name);
                list.add(vb);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }



        rootView = getLayoutInflater().from(this).inflate(R.layout.simple_player_view_player, null);
        setContentView(rootView);
        player = new PlayerView(this)
                .setTitle(Title)
                .setScaleType(PlayStateParams.fitparent)
                .hideMenu(true)
                .forbidTouch(false)
                .setPlaySource(list)
                .startPlay();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (player != null) {
            player.onDestroy();
        }
    }
    @Override
    protected void onPause() {
        super.onPause();
        if (player != null) {
            player.onPause();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (player != null) {
            player.onResume();
        }
    }


    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        if (player != null) {
            player.onConfigurationChanged(newConfig);
        }
    }

    @Override
    public void onBackPressed() {
        if (player != null && player.onBackPressed()) {
            return;
        }
        super.onBackPressed();
    }
}
