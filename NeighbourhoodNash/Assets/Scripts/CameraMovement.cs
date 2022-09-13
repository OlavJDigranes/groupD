using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    public Transform p1;
    public Vector3 offset;

    // Start is called before the first frame update
    void Start()
    {
        p1 = GameObject.Find("PlayerTest").transform; 
    }

    // Update is called once per frame
    void Update()
    {
        //https://answers.unity.com/questions/878913/how-to-get-camera-to-follow-player-2d.html
        Camera.main.transform.position = new Vector3 (p1.position.x + offset.x, p1.position.y + offset.y, offset.z); // Camera follows the player with specified offset position
    }
}
