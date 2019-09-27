using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

[AddComponentMenu("MyGame/TitleScreen")]
public class TitleScreen : MonoBehaviour {

    public Texture2D BgImg;
    public Texture2D MarsImg;
    void OnGUI()
    {
        /***
        string aa = "";
        
        //构造空的GUIStyle
        GUIStyle p_bg = new GUIStyle();
        GUIStyle p_mars = new GUIStyle();
        //设置正常显示时是背景图片
        p_bg.normal.background = BgImg;
        p_mars.normal.background = MarsImg;
        GUI.Label(new Rect(0, 0, 750, 300), aa, p_bg);
        GUI.Label(new Rect(200, 0, 300, 300), aa, p_mars);
        ***/
        //文字大小
        GUI.skin.label.fontSize = 48;

        //UI中心对齐
        GUI.skin.label.alignment = TextAnchor.LowerCenter;

        //显示标题
        GUI.Label(new Rect(0, 30, Screen.width, 100), "太空大战");

        //开始游戏按钮
        if (GUI.Button(new Rect(Screen.width * 0.5f - 100, Screen.height *0.7f, 200, 30), "开始游戏"))
        {
            //开始读取下一关
            //Application.LoadLevel("level1");
            SceneManager.LoadScene("level1");
        }
    }

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
