using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("MyGame/Enemy")]
public class Enemy : MonoBehaviour {

    //生命
    public float m_life = 10;

    //速度
    public float m_speed = 1;

    //旋转速度
    protected float m_rotSpeed = 30;

    //变向间隔时间
    protected float m_timer = 1.5f;

    //声音源
    protected AudioSource m_audio;

    //爆炸特效
    public Transform m_explosionFX;

    //分数
    public int m_point = 10;

    protected Transform m_transform;
	
    // Use this for initialization
	void Start () {

        m_transform = this.transform;

        
    }
	
	// Update is called once per frame
	void Update () {

        UpdateMove();
	}

    protected virtual void UpdateMove()
    {
        m_timer -= Time.deltaTime;
        if(m_timer <= 0)
        {
            m_timer = 3;

            //改变旋转方向
            m_rotSpeed = -m_rotSpeed;
        }

        //旋转方向
        m_transform.Rotate(Vector3.up, m_rotSpeed * Time.deltaTime, Space.World);

        //前进
        m_transform.Translate(new Vector3(0, 0, -m_speed * Time.deltaTime));
    }

    void OnTriggerEnter (Collider other)
    {
        if (other.tag.CompareTo("PlayerRocket") == 0)
        {
            Rocket rocket = other.GetComponent<Rocket>();
            if(rocket != null)
            {
                m_life -= rocket.m_power;

                if(m_life <= 0)
                {
                    GameManager.Instance.AddScore(m_point);

                    Instantiate(m_explosionFX, m_transform.position, Quaternion.identity);
                    Destroy(this.gameObject);
                }
            }
        }

        else if (other.tag.CompareTo("Player") == 0)
        {
            m_life = 0;
            Instantiate(m_explosionFX, m_transform.position, Quaternion.identity);
            Destroy(this.gameObject);
        }

        if (other.tag.CompareTo("Bound") == 0)
        {
            m_life = 0;
            Destroy(this.gameObject);
        }
    }
}
