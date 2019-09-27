using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

[AddComponentMenu("MyGame/GameManager")]
public class GameManager : MonoBehaviour {

    public static GameManager Instance;

    //得分
    public int m_score = 0;

    //纪录
    public static int m_hiscore = 0;

    //主角
    protected Player m_player;

    //背景音乐
    public AudioClip m_musicClip;

    //声音源
    protected AudioSource m_Audio;

    void Awake()
    {
        Instance = this;
    }

	// Use this for initialization
	void Start () {

        

        //获取主角
        GameObject obj = GameObject.FindGameObjectWithTag("Player");
        if (obj != null)
        {
            m_player = obj.GetComponent<Player>();
        }

        m_Audio = GetComponent<AudioSource>();

    }
	
	// Update is called once per frame
	void Update () {
		
        //循环播放背景音乐
        if (!m_Audio.isPlaying)
        {
            m_Audio.clip = m_musicClip;
            m_Audio.Play();
        }

        //暂停游戏
        if (Time.timeScale > 0 && Input.GetKeyDown(KeyCode.Escape))
        {
            Time.timeScale = 0;
        }
	}

    void OnGUI()
    {
        //游戏暂停
        if(Time.timeScale == 0)
        {
            //继续游戏按钮
            if(GUI.Button(new Rect(Screen.width * 0.5f - 50, Screen.height * 0.4f, 100, 30), "继续游戏"))
            {
                Time.timeScale = 1;
            }

            //退出游戏按钮
            if(GUI.Button(new Rect(Screen.width * 0.5f - 50, Screen.height * 0.6f, 100, 30), "退出游戏"))
            {
                //退出游戏
                Application.Quit();
            }
        }

        int life = 0;
        if (m_player != null)
        {
            //获得主角的生命值
            life = (int)m_player.m_life;
        }
        else //game over
        {

            //放大字体
            GUI.skin.label.fontSize = 50;

            //显示游戏失败
            GUI.skin.label.alignment = TextAnchor.LowerCenter;
            GUI.Label(new Rect(0, Screen.height * 0.2f, Screen.width, 60), "游戏失败");

            GUI.skin.label.fontSize = 20;

            //显示按钮
            if (GUI.Button(new Rect(Screen.width * 0.5f - 50,Screen.height * 0.5f, 100, 30),"再试一次"))
            {
                //读取当前关卡
                SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            }
        }

        GUI.skin.label.fontSize = 15;

        //显示主角生命
        GUI.Label(new Rect(5, 5, 100, 30), "装甲 " + life);

        //显示最高分
        GUI.skin.label.alignment = TextAnchor.LowerCenter;
        GUI.Label(new Rect(0, 5, Screen.width, 30), "纪录 " + m_hiscore);

        //显示当前得分
        GUI.Label(new Rect(0, 25, Screen.width, 30), "得分 " + m_score);

    }

    //增加分数
    public void AddScore(int point)
    {
        m_score += point;

        //更新高分纪录
        if (m_hiscore < m_score)
            m_hiscore = m_score;
    }
}
