using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("MyGame/Player")]
public class Player : MonoBehaviour {

    public float m_life = 3;
    public float m_speed = 1;
    public Transform m_rocket;
    protected Transform m_transform;
    float m_rocketRate = 0;

    //声音
    public AudioClip m_shootClip;

    //声音源
    protected AudioSource m_audio;

    //爆炸特效
    public Transform m_explosionFX;

	// Use this for initialization
	void Start () {

        m_transform = this.transform;

        m_audio = GetComponent<AudioSource>();
	}
	
	// Update is called once per frame
	void Update () {

        //纵向移动距离
        float movev = 0;

        //水平移动距离
        float moveh = 0;

        //按上键
        if (Input.GetKey(KeyCode.UpArrow))
        {
            movev -= m_speed * Time.deltaTime;
        }

        //按下键
        if (Input.GetKey(KeyCode.DownArrow))
        {
            movev += m_speed * Time.deltaTime;
        }

        //按左键
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            moveh += m_speed * Time.deltaTime;
        }

        //按右键
        if (Input.GetKey(KeyCode.RightArrow))
        {
            moveh -= m_speed * Time.deltaTime;
        }

        //移动
        this.m_transform.Translate( new Vector3( moveh, 0, movev));

        m_rocketRate -= Time.deltaTime;

        if (m_rocketRate <= 0)
        {
            m_rocketRate = 0.1f;
            
            //按空格键或鼠标左键发射子弹
            if (Input.GetKey(KeyCode.Space) || Input.GetMouseButton(0))
            {
                Instantiate(m_rocket, m_transform.position, m_transform.rotation);

                //播放射击声音
                m_audio.PlayOneShot(m_shootClip);
            }
        }

	}

    void OnTriggerEnter(Collider other)
    {
        if (other.tag.CompareTo("PlayerRocket") !=0 && other.tag.CompareTo("Bound")!= 0)
        {
            m_life -= 1;

            if (m_life <= 0)
            {
                Instantiate(m_explosionFX, m_transform.position, Quaternion.identity);

                Destroy(this.gameObject);
            }
        }
    }
}
