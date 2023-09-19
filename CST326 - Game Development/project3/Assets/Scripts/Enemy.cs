using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TMPro;

public class Enemy : MonoBehaviour
{
    public GameObject enemyBullet;
    public delegate void EnemyDestroyed(GameObject other);
    public static event EnemyDestroyed OnEnemyDestroyed;
    public int directionModifier = 1;
    public bool cooldown = false;
    public int sideCount = 0;
    public int downCount = 0;
    public int kills = 0;
    public float speed = 1f;
    public int swipesBeforeMovingDown = 8;
    public Animator animator;
    // Start is called before the first frame update
    private void Start()
    {
        animator = GetComponent<Animator>();
    }
    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("bullet"))
        {
            animator.Play("enemyDieAnimation");
            Debug.Log("Ouch!");
            OnEnemyDestroyed.Invoke(this.gameObject);
            Destroy(this.gameObject, 1f);
            kills++;
        }
    }

    private void Update()
    {
        if(UnityEngine.Random.Range(1, 5000 - (kills * 100)) == 1 && this.gameObject.CompareTag("enemy3"))
        {
            GameObject shot = Instantiate(enemyBullet, this.transform.position, Quaternion.identity);
            Destroy(shot, 3f);
            animator.Play("enemyShootAnimation");

        }
        if(kills > 10)
        {
            speed = 2.5f;
            swipesBeforeMovingDown = 5;
        }

        if(Math.Floor(Time.realtimeSinceStartup) % 2 == 0 && !cooldown)
        {
            cooldown = true;
            directionModifier *= -1;
            sideCount++;
            downCount++;
        }
        if((Math.Floor(Time.realtimeSinceStartup) % 2 == 1 && !this.CompareTag("enemy4")) || Math.Floor(Time.realtimeSinceStartup) % 16 == 15) {
            cooldown = false;
        }
        if(sideCount == swipesBeforeMovingDown)
        {
            sideCount = 0;
            this.transform.position += new Vector3(0, -.5f, 0);
        }
        this.transform.position += new Vector3(.005f * directionModifier * speed, 0, 0);
        
    }
}
