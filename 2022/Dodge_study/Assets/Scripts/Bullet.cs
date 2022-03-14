using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public float speed = 8f; // Bullet move speed
    private Rigidbody bulletRigidbody; // Rigidbody Component for move

    void Start()
    {
        // Findout Rigidbody Component in GameObject for assign to bulletRigidbody
        bulletRigidbody = GetComponent<Rigidbody>();

        // Speed of Rigidbody = forward * speed
        bulletRigidbody.velocity = transform.forward * speed;

        // Destroy Bullet in 3 seconds
        Destroy(gameObject, 3f);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        // if Collison`s tag is Player
        if(other.tag =="Player")
        {
            PlayerController playerController = other.GetComponent<PlayerController>();

            if(playerController != null)
                playerController.Die();
        }
    }
}
