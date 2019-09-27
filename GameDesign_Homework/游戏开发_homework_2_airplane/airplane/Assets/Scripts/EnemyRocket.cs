using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("MyGame/EnemyRocket")]

public class EnemyRocket : Rocket {

	void OnTriggerEnter(Collider other)
    {
        if (other.tag.CompareTo("Player") != 0)
            return;

        Destroy(this.gameObject);
    }
}
