using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotator : MonoBehaviour
{
    // 회전 속도 지정
    public float rotationSpeed = 60f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // transform 의 rotate의 y값을 Time.deltaTime만큼을 회전
        transform.Rotate(0f, rotationSpeed * Time.deltaTime , 0f);
    }
}
