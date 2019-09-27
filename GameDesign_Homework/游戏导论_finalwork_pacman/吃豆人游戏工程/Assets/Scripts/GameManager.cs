using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    private static GameManager _instance;
    public static GameManager Instance
    {
        get
        {
            return _instance;
        }
    }
    
    public GameObject pacman;       //吃豆人
    public GameObject blinky;       //怪物1
    public GameObject clyde;        //怪物2
    public GameObject inky;         //怪物3
    public GameObject pinky;        //怪物4
    public GameObject startPanel;               //开始按钮
    public GameObject gamePanel;                //计分板
    public GameObject startCountDownPrefab;     //开始倒计时
    public GameObject gameoverPrefab;           //游戏结束
    public GameObject winPrefab;                //游戏胜利
    public AudioClip startClip;
    public Text remainText;
    public Text nowText;
    public Text scoreText;

    public bool isSuperPacman = false;
    public List<int> usingIndex = new List<int>();
    public List<int> rawIndex = new List<int> { 0, 1, 2, 3 };
    private List<GameObject> pacdotGos = new List<GameObject>();
    private int pacdotNum = 0;
    private int nowEat = 0;
    public int score = 0;

    //Awake()在脚本对象实例化时被调用的
    private void Awake()
    {
        _instance = this;
        Screen.SetResolution(1024, 768, false);
        int tempCount = rawIndex.Count;
        for (int i = 0; i < tempCount; i++)
        {
            int tempIndex = Random.Range(0, rawIndex.Count);
            usingIndex.Add(rawIndex[tempIndex]);
            rawIndex.RemoveAt(tempIndex);
        }
        foreach (Transform t in GameObject.Find("Maze").transform)
        {
            pacdotGos.Add(t.gameObject);
        }
        pacdotNum = GameObject.Find("Maze").transform.childCount;
    }

    //Start()在对象的第一帧时被调用的，而且在Update()之前
    private void Start()
    {
        SetGameState(false);
    }

    private void Update()
    {
        if (nowEat == pacdotNum && pacman.GetComponent<PacmanMove>().enabled != false)
        {
            gamePanel.SetActive(false);
            Instantiate(winPrefab);
            StopAllCoroutines();
            SetGameState(false);
        }
        if (nowEat == pacdotNum)
        {
            if (Input.anyKeyDown)
            {
                SceneManager.LoadScene(0);
            }
        }
        if (gamePanel.activeInHierarchy)
        {
            remainText.text = "Remain:\n\n" + (pacdotNum - nowEat);
            nowText.text = "Eaten:\n\n" + nowEat;
            scoreText.text = "Score:\n\n" + score;
        }
    }


    //按下开始按钮
    public void OnStartButton()
    {
        StartCoroutine(PlayStartCountDown());
        AudioSource.PlayClipAtPoint(startClip, new Vector3(0, 0, -5));
        startPanel.SetActive(false);
    }

    //按下退出按钮
    public void OnExitButton()
    {
        Application.Quit();
    }

    //协程-开始倒计时
    IEnumerator PlayStartCountDown()
    {
        GameObject go = Instantiate(startCountDownPrefab);
        yield return new WaitForSeconds(4f);//暂停协程 4s后执行后续代码(游戏开始倒计时)
        Destroy(go);
        SetGameState(true);//解锁所有角色的运动
        Invoke("CreateSuperPacdot", 10f);//委托 延时调用函数产生特殊豆子
        gamePanel.SetActive(true);
        GetComponent<AudioSource>().Play();
    }

    //吃到所有豆子时
    public void OnEatPacdot(GameObject go)
    {
        nowEat++;
        score += 100;
        pacdotGos.Remove(go);
    }

    //吃到特殊道具(大豆子)时
    public void OnEatSuperPacdot()
    {
        score += 200;
        Invoke("CreateSuperPacdot", 10f);//委托 延时调用函数产生特殊豆子
        isSuperPacman = true;
        FreezeEnemy();
        StartCoroutine(RecoveryEnemy());
    }

    //敌人返回起点
    IEnumerator RecoveryEnemy()
    {
        yield return new WaitForSeconds(3f);
        DisFreezeEnemy();
        isSuperPacman = false;
    }

    //随机出现特殊豆子
    private void CreateSuperPacdot()
    {
        if (pacdotGos.Count < 5)
        {
            return;
        }
        int tempIndex = Random.Range(0, pacdotGos.Count);
        pacdotGos[tempIndex].transform.localScale = new Vector3(3, 3, 3);
        pacdotGos[tempIndex].GetComponent<Pacdot>().isSuperPacdot = true;
    }

    //吃到特殊豆子后冻结敌人
    private void FreezeEnemy()
    {
        //停止敌人运动
        blinky.GetComponent<GhostMove>().enabled = false;
        clyde.GetComponent<GhostMove>().enabled = false;
        inky.GetComponent<GhostMove>().enabled = false;
        pinky.GetComponent<GhostMove>().enabled = false;
        //改变敌人颜色为透明
        blinky.GetComponent<SpriteRenderer>().color = new Color(0.7f, 0.7f, 0.7f, 0.7f);
        clyde.GetComponent<SpriteRenderer>().color = new Color(0.7f, 0.7f, 0.7f, 0.7f);
        inky.GetComponent<SpriteRenderer>().color = new Color(0.7f, 0.7f, 0.7f, 0.7f);
        pinky.GetComponent<SpriteRenderer>().color = new Color(0.7f, 0.7f, 0.7f, 0.7f);
    }

    //时间结束后解冻敌人
    private void DisFreezeEnemy()
    {
        //重新启动敌人运动
        blinky.GetComponent<GhostMove>().enabled = true;
        clyde.GetComponent<GhostMove>().enabled = true;
        inky.GetComponent<GhostMove>().enabled = true;
        pinky.GetComponent<GhostMove>().enabled = true;
        //恢复敌人颜色
        blinky.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
        clyde.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
        inky.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
        pinky.GetComponent<SpriteRenderer>().color = new Color(1f, 1f, 1f, 1f);
    }

    //游戏倒计时结束时解锁或锁定所有角色
    private void SetGameState(bool state)
    {
        pacman.GetComponent<PacmanMove>().enabled = state;
        blinky.GetComponent<GhostMove>().enabled = state;
        clyde.GetComponent<GhostMove>().enabled = state;
        inky.GetComponent<GhostMove>().enabled = state;
        pinky.GetComponent<GhostMove>().enabled = state;
    }
}
