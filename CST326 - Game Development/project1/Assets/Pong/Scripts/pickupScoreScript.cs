using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEditor.AssetImporters;
using UnityEngine;

public class pickupScoreScript : GoalTrigger
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("doubleScore"))
        {
            gameManager.SetTwoTimes();
            other.gameObject.SetActive(false);
            Debug.Log("Next score doubled");
        }
    }
}
