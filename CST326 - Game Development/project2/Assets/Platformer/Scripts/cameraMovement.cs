using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using static UnityEngine.Input;
using UnityEngine.Rendering;
using TMPro;
using UnityEngine.SocialPlatforms.Impl;

public class cameraMovement : MonoBehaviour
{
    public TextMeshProUGUI coinText;
    public int coins = 0;
    public int score = 0;
    public TextMeshProUGUI scoreText;
    public GameObject PlayerCam;

    private Vector3 pos;
    // Start is called before the first frame update
    void Start()
    {
        pos = new Vector3(17, 7.5f, -10);
        PlayerCam.transform.position = pos;
    }

    // Update is called once per frame
    void Update()
    {
        //PlayerCam.transform.position = pos;
        if (Input.GetKey(KeyCode.E)) {
            pos = new Vector3(pos.x + .05f, pos.y, pos.z);
            PlayerCam.transform.position = pos;
        }
        if(Input.GetKey(KeyCode.Q))
        {
            pos = new Vector3(pos.x - .05f, pos.y, pos.z);
            PlayerCam.transform.position = pos;
        }

        RaycastHit detected;
        var rayToCast = Camera.main.ScreenPointToRay(Input.mousePosition);
        if (Input.GetMouseButtonDown(0) && Physics.Raycast(rayToCast, out detected))
        {
            if(detected.transform.name == "Question(Clone)")
            {
                coins++;
                coinText.text = $"Coins: {coins}";
            }
            if(detected.transform.name == "Brick(Clone)" || detected.transform.name == "Question(Clone)")
            {
                Destroy(detected.transform.gameObject);
                score = score + 100;
                scoreText.text = $"Mario\n{score}";
            }
        }
    }

    //void OnMove(InputValue movementValue)
    //{
    //    Vector3 movementVector = movementValue.Get<Vector3>();
    //    pos = new Vector3(movementVector.x, pos.y, pos.z);
    //}
}
