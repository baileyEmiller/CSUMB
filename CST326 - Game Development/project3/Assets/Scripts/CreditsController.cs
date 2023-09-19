using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CreditsController : MonoBehaviour
{
    public float timeBeforeMainMenuLoad;
    public TextMeshProUGUI scrollingText;
    public string menuSceneName;
    public float scrollSpeed;
    public AudioSource endMusic;

    private void Start()
    {
        endMusic.Play();
    }
    // Update is called once per frame
    void Update()
    {
        scrollingText.transform.position += new Vector3(0, scrollSpeed, 0);
        if(Time.timeSinceLevelLoad >= timeBeforeMainMenuLoad)
        {
            SceneManager.LoadScene(menuSceneName, LoadSceneMode.Single);
        }
    }
}
