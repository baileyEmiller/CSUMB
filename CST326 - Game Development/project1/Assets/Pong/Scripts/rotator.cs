using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class rotator : MonoBehaviour
{
    //from project 0
    // Update is called once per frame
    void Update()
    {
        transform.Rotate(new Vector3(75, 0, 75) * Time.deltaTime);
    }
}
