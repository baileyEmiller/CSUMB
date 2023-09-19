using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class playerController : MonoBehaviour
{
    public TextMeshProUGUI finishText;
    public float acceleration = 10f;
    public float maxSpeed = 3f;
    public float jumpForce = 10f;
    public float jumpBoost = 5f;
    public bool isGrounded;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float horizontalAxis = Input.GetAxis("Horizontal");
        Rigidbody rbody = GetComponent<Rigidbody>();
        rbody.velocity += horizontalAxis * Vector3.right * Time.deltaTime * acceleration;

        Collider col = GetComponent<Collider>();
        float halfHeight = .03f;

        if(rbody.velocity.magnitude > maxSpeed && !Input.GetKeyDown(KeyCode.LeftShift))
        {
            rbody.velocity = Vector3.ClampMagnitude(rbody.velocity, maxSpeed);
        }

        isGrounded = Physics.Raycast(transform.position, Vector3.down, halfHeight);
        rbody.velocity = new Vector3(Mathf.Clamp(rbody.velocity.x, -maxSpeed, maxSpeed), rbody.velocity.y, rbody.velocity.z);

        if (isGrounded && Input.GetKeyDown(KeyCode.Space)) 
        {
            rbody.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
        }

        if (Input.GetKeyDown(KeyCode.Space)) 
        {
            rbody.AddForce(Vector3.up * jumpBoost, ForceMode.Force);
        }

        if (Input.GetKeyDown(KeyCode.LeftShift)) 
        {
            if (Input.GetKeyDown(KeyCode.A))
            {
                rbody.AddForce(Vector3.left * 2.5f, ForceMode.Impulse);
            }
            if (Input.GetKeyDown(KeyCode.D))
            {
                rbody.AddForce(Vector3.right * 2.5f, ForceMode.Impulse);
            }
        }
        
        Color lineColor = (isGrounded) ? Color.green : Color.red;
        Debug.DrawLine(transform.position, transform.position + Vector3.down * halfHeight, lineColor, 0f, false);

        float speed = rbody.velocity.magnitude;
        Animator animator = GetComponent<Animator>();
        animator.SetFloat("speed", speed);
        animator.SetBool("jumping", !isGrounded);
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Finish"))
        {
            finishText.text = $"Level Completed!";
        }
        if (other.gameObject.CompareTag("Water"))
        {
            finishText.text = $"You died :(";
        }
    }
}
