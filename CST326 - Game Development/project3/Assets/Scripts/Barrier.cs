using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Barrier : MonoBehaviour
{
    public int hitsTaken = 0;
    public int canTake = 4;

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Debug.Log("Barrier is taking damage!");
        if(hitsTaken+1 == canTake)
        {
            Destroy(this.gameObject);
        }
        else
        {
            hitsTaken++;
        }
        Destroy(collision.gameObject);
    }
}
