using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotator : MonoBehaviour
{
    // ȸ�� �ӵ� ����
    public float rotationSpeed = 60f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // transform �� rotate�� y���� Time.deltaTime��ŭ�� ȸ��
        transform.Rotate(0f, rotationSpeed * Time.deltaTime , 0f);
    }
}
