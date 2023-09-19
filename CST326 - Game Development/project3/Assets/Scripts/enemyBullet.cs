using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

[RequireComponent(typeof(Rigidbody2D))] //technique for making sure there isn't a null reference during runtime if you are going to use get component
public class enemyBullet : MonoBehaviour
{
    private Rigidbody2D myRigidbody2D;

    public float speed = 5;
    // Start is called before the first frame update
    void Start()
    {
        myRigidbody2D = GetComponent<Rigidbody2D>();
        Fire();
    }

    // Update is called once per frame
    private void Fire()
    {
        myRigidbody2D.velocity = Vector2.down * speed;
        //Debug.Log("Wwweeeeee");
    }

    private void OnCollisionEnter2D(Collision2D other) //destroys bullet when it comes into contact with something
    {
        if (other.gameObject.CompareTag("Player"))
        {
            Destroy(other.gameObject);
        }
    }
}