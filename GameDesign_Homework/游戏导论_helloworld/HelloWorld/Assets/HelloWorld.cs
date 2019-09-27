using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HelloWorld : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnGUI()
    {
        //改变字符的大小
        GUI.skin.label.fontSize = 100;

        //输出文字
        GUI.Label(new Rect(10, 10, Screen.width, Screen.height), "Hello World");
    }
}
