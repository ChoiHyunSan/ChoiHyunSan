using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletSpawner : MonoBehaviour
{

    // 변수 선언
    public GameObject bulletPrefab;    // 탄알을 생성하는데 사용할 원본 프리팹  
    public float spawnRateMin = 0.5f;  // 새 탄알을 생성하는데 걸리는 시간의 최솟값
    public float spawnRateMax = 3f;    // 새 탄알을 생성하는데 걸리는 시간의 최댓값

    private Transform target;          // 조준할 대상 오브젝트의 트랜스폼 컴포넌트
    private float spawnRate;           // 다음 탄알을 생성할 때까지 기다릴 시간 
    private float timeAfterSpawn;      // 마지막 탄알 생성 시점부터 흐른 시간을 표시하는 타이머

    // Start is called before the first frame update
    void Start()
    {
        // 타이머 최소 시간 설정
        timeAfterSpawn = 0f;

        // 탄알 생성시간을 최솟값과 최댓 값 사이의 임의의 시간 부여
        spawnRate = Random.Range(spawnRateMin, spawnRateMax);

        // 타겟을 PlayerController 컴포넌트를 가진 오브젝트로 지정
        target = FindObjectOfType<PlayerController>().transform;
    }

    // Update is called once per frame
    void Update()
    {
        UpdateBullet();
    }

    void UpdateBullet()
    {
        // timeAfterSpawn 갱신
        timeAfterSpawn += Time.deltaTime;

        // 최근 생성 시점에서부터 누적된 시간이 생성주기보다 크거나 같다면
        if (timeAfterSpawn >= spawnRate)
        {
            // 누적된 시간을 리셋
            timeAfterSpawn = 0f;


            // bulletPrefab의 복제본을 transform.position 위치와  transform.rotation 회전으로 생성
            GameObject bullet = Instantiate(bulletPrefab, transform.position, transform.rotation);

            // 생성된 bullet 게임 오브젝트의 정면 방향이 target을 향하도록 회전
            bullet.transform.LookAt(target);

            // 다음번 생성 간격을 spawnRateMin, spawnRateMax 사이에서 랜덤 지정
            spawnRate = Random.Range(spawnRateMin, spawnRateMax);
        }
    }

}
