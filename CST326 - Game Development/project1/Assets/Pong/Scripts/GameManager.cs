
using UnityEngine;
using TMPro;
using Unity.VisualScripting;

public class GameManager : MonoBehaviour
{
    public Transform ball;
    public float startSpeed = 3f;
    public GoalTrigger leftGoalTrigger;
    public GoalTrigger rightGoalTrigger;
    public Rigidbody ballBody;
    public TextMeshProUGUI score;

    private int twoTimes = 0;
    private int leftPlayerScore = 0;
    private int rightPlayerScore = 0;
    private Vector3 ballStartPos;

    private const int scoreToWin = 11;

    // Start is called before the first frame update
    void Start()
    {
        ballStartPos = ball.position;
        ballBody = ball.GetComponent<Rigidbody>();
        ballBody.velocity = new Vector3(1f, 0f, 0f) * startSpeed;
        IncrementScore();
    }

    // If the ball entered the goal area, increment the score, check for win, and reset the ball
    public void OnGoalTrigger(GoalTrigger trigger)
    {
        //Debug.Log(twoTimes);
        if (trigger == leftGoalTrigger)
        {
            rightPlayerScore = rightPlayerScore + twoTimes + 1;
            twoTimes = 0;
            Debug.Log($"Right player scored: {rightPlayerScore}");
            IncrementScore();
            if (rightPlayerScore == scoreToWin)
            {
                Debug.Log("Right player wins!");
            }
            else
            {
                ResetBall(-1f);
            }
        }
        else if (trigger == rightGoalTrigger)
        {
            leftPlayerScore = leftPlayerScore + twoTimes + 1;
            twoTimes = 0;
            Debug.Log($"Left player scored: {leftPlayerScore}");
            IncrementScore();
            if (leftPlayerScore == scoreToWin)
            {
                Debug.Log("Left player wins!");
            }
            else
            {
                ResetBall(1f);
            }
        }
    }

    void ResetBall(float directionSign)
    {
        ball.position = ballStartPos;

        // Start the ball within 20 degrees off-center toward direction indicated by directionSign
        directionSign = Mathf.Sign(directionSign);
        Vector3 newDirection = new Vector3(directionSign, 0f, 0f) * startSpeed;
        newDirection = Quaternion.Euler(0f, Random.Range(-20f, 20f), 0f) * newDirection;

        var rbody = ball.GetComponent<Rigidbody>();
        rbody.velocity = newDirection;
        rbody.angularVelocity = new Vector3();

        // We are warping the ball to a new location, start the trail over
        ball.GetComponent<TrailRenderer>().Clear();
    }

    public void SetTwoTimes()
    {
        twoTimes = 1;
    }

    public void IncrementScore()
    {
        int temp;
        if(leftPlayerScore > rightPlayerScore)
        {
            temp = leftPlayerScore - rightPlayerScore;
        }
        else
        {
            temp = rightPlayerScore - leftPlayerScore;
        }

        score.text = leftPlayerScore.ToString() + "                         " + rightPlayerScore.ToString();
        if (temp < 2)
        {
            score.color = new Color(0, 255, 0, 255);
        }
        else if (temp < 5)
        {
            score.color = new Color(255, 255, 0, 255);
        }
        else if(temp < 8)
        {
            score.color = new Color(255, 50, 0, 255);
        }
        else
        {
            score.color = new Color(255, 0, 0, 255);
        }
    }
}
