using System.Collections;
using System.Collections.Generic;
using System.IO;
using TMPro;
using UnityEngine;

public class ScoreManager : MonoBehaviour
{
    public TextMeshProUGUI scoreText;
    public TextMeshProUGUI centerText;
    public TextMeshProUGUI highScoreText;
    public int score = 0;
    public int highScore = 0;
    public string filename;
    public AudioSource enemyDie;
    // Start is called before the first frame update
    void Start()
    {
        string line = "";
        Enemy.OnEnemyDestroyed += aboutToBeDestroyed;
        string fileToParse = $"{Application.dataPath}{"/Resources/"}{filename}.txt";
        using(StreamReader sr = new StreamReader(fileToParse))
        {
            line = sr.ReadLine();
        }
        highScore = int.Parse(line);
        highScoreText.text = "High Score: " + line;
    }

    private void aboutToBeDestroyed(GameObject other)
    {
        Debug.Log("recieved the event for counting score");
            enemyDie.enabled = true;
            enemyDie.Play();
        if (other.gameObject.CompareTag("enemy1"))
        {
            score += 30;
        }
        if (other.CompareTag("enemy2"))
        {
            score += 20;
        }
        if (other.CompareTag("enemy3"))
        {
            score += 10;
        }
        if (other.CompareTag("enemy4"))
        {
            int temp = Random.Range(10, 40);
            temp *= 10;
            score += temp;
        }

        if (score < 10)
        {
            scoreText.text = "Score: 000" + score.ToString();
        }
        else if(score < 100)
        {
            scoreText.text = "Score: 00" + score.ToString();
        }
        else if(score < 1000)
        {
            scoreText.text = "Score: 0" + score.ToString();
        }
        else
        {
            scoreText.text = "Score: " + score.ToString();
        }

        if (other.gameObject.CompareTag("Player")){
            centerText.text = "You Died Bozo";
        }
        if(score > highScore)
        {
            highScore = score;
            if(score < 10)
            {
                File.WriteAllText($"{Application.dataPath}{"/Resources/"}{filename}.txt", "000" + highScore.ToString());
            }else if(score < 100)
            {
                File.WriteAllText($"{Application.dataPath}{"/Resources/"}{filename}.txt", "00" + highScore.ToString());
            }else if(score < 1000)
            {
                File.WriteAllText($"{Application.dataPath}{"/Resources/"}{filename}.txt", "0" + highScore.ToString());
            }
            else
            {
                File.WriteAllText($"{Application.dataPath}{"/Resources/"}{filename}.txt", highScore.ToString());
            }
        }
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            centerText.text = "";
        }


    }
}
