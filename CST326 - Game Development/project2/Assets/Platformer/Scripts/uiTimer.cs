using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class uiTimer : MonoBehaviour
{
    public TextMeshProUGUI timerText;
    public TextMeshProUGUI finishText;

    // Update is called once per frame
    void Update()
    {
        int wholeSecond = (int)Mathf.Floor(Time.realtimeSinceStartup);
        timerText.text = $"Time\n {(100 - wholeSecond).ToString()}";
        if (100 - wholeSecond == 0)
        {
            finishText.text = $"Level Incomplete";
        }
    }
}
