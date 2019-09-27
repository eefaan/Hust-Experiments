using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour {

    public static GameManager Instance = null;

    //游戏得分
    int m_score = 0;

    //游戏最高得分
    static int m_hiscore = 0;

    //弹药数量
    int m_ammo = 100;

    //游戏主角
    Player m_player;

    //UI文字
    Text txt_ammo;
    Text txt_hiscore;
    Text txt_life;
    Text txt_score;

    // Use this for initialization
    void Start () {
        Instance = this;

        //获得主角
        m_player = GameObject.FindGameObjectWithTag("Player").GetComponent<Player>();

        //获得设置的UI文字
        txt_ammo = GameObject.Find("GameManager/Canvas/text_ammo").GetComponent<Text>();
        txt_hiscore = GameObject.Find("GameManager/Canvas/text_hiscores").GetComponent<Text>();
        txt_life = GameObject.Find("GameManager/Canvas/text_life").GetComponent<Text>();
        txt_score = GameObject.Find("GameManager/Canvas/text_scores").GetComponent<Text>();
    }
	
    //更新分数
    public void SetScore(int score)
    {
        m_score += score;

        if (m_score > m_hiscore)
            m_hiscore = m_score;

        txt_score.text = "Score " + m_score;
        txt_hiscore.text = "High Score " + m_hiscore;
    }

    //更新弹药
    public void SetAmmo(int ammo)
    {
        m_ammo -= ammo;

        //如果弹药为负数，重新填弹
        if (m_ammo <= 0)
            m_ammo = 100 - m_ammo;

        txt_ammo.text = m_ammo.ToString() + "/100";
    }

    //更新生命
    public void SetLife(int life)
    {
        txt_life.text = life.ToString();
    }

	void OnGUI()
    {
        if(m_player.m_life<=0)
        {
            //居中显示文字
            GUI.skin.label.alignment = TextAnchor.MiddleCenter;

            //改变文字大小
            GUI.skin.label.fontSize = 40;

            //显示Game Over
            GUI.Label(new Rect(0, 0, Screen.width, Screen.height), "Game Over");

            //显示重新游戏按钮
            GUI.skin.label.fontSize = 30;
            if(GUI.Button(new Rect(Screen.width*0.5f-150,Screen.height*0.75f,300,40),"Try again"))
            {
                SceneManager.LoadScene("demo");
            }
        }
    }
}
