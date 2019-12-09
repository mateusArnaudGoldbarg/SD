using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarSpawner : MonoBehaviour
{
    UIManager sc;
    public GameObject[] cars;
    int carno; 
    public float maxpos = 1.9f;
    public float minpos = -1.9f;
    private float delayTimer = 3f;
    float timer;

    // Start is called before the first frame update
    void Start()
    {
        sc = FindObjectOfType<UIManager>();

        if (sc != null)
        {
            //Debug.Log(sc.score.ToString());
        }
        timer = delayTimer - sc.score/100;
    }

    // Update is called once per frame
    void Update()
    {
        

        timer -= Time.deltaTime;
        if (timer <= 0)
        {
            carno = Random.Range(0,3);
            Vector3 carPos = new Vector3(Random.Range(minpos, maxpos), transform.position.y, transform.position.z);
            Instantiate(cars[carno], carPos, transform.rotation);
            timer = delayTimer - sc.score / 100;
        }
        
    }
}
