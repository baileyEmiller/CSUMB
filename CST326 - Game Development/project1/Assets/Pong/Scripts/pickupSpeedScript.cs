using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEditor.AssetImporters;
using UnityEngine;

public class pickupSpeedScript : GameManager
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("speedPickup"))
        {
            other.gameObject.SetActive(false);
            ballBody.velocity = ballBody.velocity * 0.5f;
            Debug.Log("Speed halfed");
        }
    }
}