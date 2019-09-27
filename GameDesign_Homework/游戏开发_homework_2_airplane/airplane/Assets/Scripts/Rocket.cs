using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("MyGame/Rocket")]

public class Rocket : MonoBehaviour {

    //子弹飞行速度
    public float m_speed = 10;

    //生存时间
    public float m_liveTime = 1;

    //威力
    public float m_power = 1.0f;

    protected Transform m_trasform;

    // Use this for initialization
    void Start() {
        m_trasform = this.transform;
    }

    // Update is called once per frame
    void Update() {

        m_liveTime -= Time.deltaTime;
        if (m_liveTime <= 0)
            Destroy(this.gameObject);

        m_trasform.Translate(new Vector3(0, 0, -m_speed * Time.deltaTime));

    }

    void OnTriggerEnter(Collider other)
    {
        if (other.tag.CompareTo("Enemy") != 0)
            return;

        Destroy(this.gameObject);
    }
}