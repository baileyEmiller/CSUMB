using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneSwitcher : MonoBehaviour
{
    public string gameSceneName;
    public string creditSceneName;

    private void Start()
    {
        GameObject.DontDestroyOnLoad(gameObject);
    }
    public void LoadGameScene()
    {
        SceneManager.LoadScene(gameSceneName, LoadSceneMode.Single);
    }

    public void LoadGameCredits()
    {
        SceneManager.LoadScene(creditSceneName, LoadSceneMode.Single);
    }
}
