using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.TextCore.Text;
using UnityEngine.UI;
using static Enemy;

public class Player : MonoBehaviour
{
    public AudioSource playerShooting;
    public AudioSource playerDying;
    public AudioSource music;
    public GameObject bullet;
    public Transform shottingOffset;
    public bool cooldown = false;
    int timeAtLastShot = 0;
    public string creditSceneName;
    public float upperBound;
    public float lowerBound;
    public ParticleSystem thisParticleSystem;
    public Animator animator;
    public string toBeInvoked = "LoadCredits";
    private void Start()
    {
        music.Play();
        animator = GetComponent<Animator>();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && !cooldown)
        {
            animator.Play("playerShoot");
            GameObject shot = Instantiate(bullet, shottingOffset.position, Quaternion.identity);
            playerShooting.Play();
            Debug.Log("Bang!");
            Destroy(shot, 3f);
            cooldown = true;
            timeAtLastShot = (int)Math.Floor(Time.realtimeSinceStartup);
            thisParticleSystem.Play();
        }

        if (timeAtLastShot + 1 == (int)Math.Floor(Time.realtimeSinceStartup))
        {
            cooldown = false;
        }

        if (Input.GetKey(KeyCode.A) && this.transform.position.x > lowerBound)
        {
            this.transform.position = this.transform.position += new Vector3(-.01f, 0, 0);
        }
        if (Input.GetKey(KeyCode.D) && this.transform.position.x < upperBound)
        {
            this.transform.position = this.transform.position += new Vector3(.01f, 0, 0);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        playerDying.Play();
        animator.GetParameter(0).Equals(true);
        animator.Play("playerDie");
        Destroy(collision.gameObject);
        Destroy(this.gameObject);
        SceneManager.LoadScene(creditSceneName, LoadSceneMode.Single);

    }
}
