using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletSpawner : MonoBehaviour
{

    // ���� ����
    public GameObject bulletPrefab;    // ź���� �����ϴµ� ����� ���� ������  
    public float spawnRateMin = 0.5f;  // �� ź���� �����ϴµ� �ɸ��� �ð��� �ּڰ�
    public float spawnRateMax = 3f;    // �� ź���� �����ϴµ� �ɸ��� �ð��� �ִ�

    private Transform target;          // ������ ��� ������Ʈ�� Ʈ������ ������Ʈ
    private float spawnRate;           // ���� ź���� ������ ������ ��ٸ� �ð� 
    private float timeAfterSpawn;      // ������ ź�� ���� �������� �帥 �ð��� ǥ���ϴ� Ÿ�̸�

    // Start is called before the first frame update
    void Start()
    {
        // Ÿ�̸� �ּ� �ð� ����
        timeAfterSpawn = 0f;

        // ź�� �����ð��� �ּڰ��� �ִ� �� ������ ������ �ð� �ο�
        spawnRate = Random.Range(spawnRateMin, spawnRateMax);

        // Ÿ���� PlayerController ������Ʈ�� ���� ������Ʈ�� ����
        target = FindObjectOfType<PlayerController>().transform;
    }

    // Update is called once per frame
    void Update()
    {
        UpdateBullet();
    }

    void UpdateBullet()
    {
        // timeAfterSpawn ����
        timeAfterSpawn += Time.deltaTime;

        // �ֱ� ���� ������������ ������ �ð��� �����ֱ⺸�� ũ�ų� ���ٸ�
        if (timeAfterSpawn >= spawnRate)
        {
            // ������ �ð��� ����
            timeAfterSpawn = 0f;


            // bulletPrefab�� �������� transform.position ��ġ��  transform.rotation ȸ������ ����
            GameObject bullet = Instantiate(bulletPrefab, transform.position, transform.rotation);

            // ������ bullet ���� ������Ʈ�� ���� ������ target�� ���ϵ��� ȸ��
            bullet.transform.LookAt(target);

            // ������ ���� ������ spawnRateMin, spawnRateMax ���̿��� ���� ����
            spawnRate = Random.Range(spawnRateMin, spawnRateMax);
        }
    }

}
