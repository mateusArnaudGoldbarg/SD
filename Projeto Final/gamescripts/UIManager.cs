using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public Text scoreText;
    public float score = 0;
    bool gameOver = false;
    // Start is called before the first frame update
    void Start()
    {
        score = 0;
        InvokeRepeating("Scoreupdate", 1.0f, 0.5f);
        gameOver = false;
    }

    // Update is called once per frame
    void Update()
    {
        scoreText.text = "SCORE: " + score;

        //Debug.Log(score);

    }
    void Scoreupdate()
    {
        if (gameOver == false)
        {
            score += 1;
        }
    }

    public void Denovo()
    {
        Application.LoadLevel("SampleScene");
    }

    public void gameOverActivated()
    {
        gameOver = true;
    }
}
