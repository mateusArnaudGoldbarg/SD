using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Nathan : MonoBehaviour
{
    ComunicacaoTeste cT;
    string cmd;
    Vector3 position;
    float Natvel = 30f;
    bool flag = false;
    int calls = 0;
    public AudioSource aS;
    // Start is called before the first frame update
    void Start()
    {
        position = transform.position;
        aS = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        
        cT = FindObjectOfType<ComunicacaoTeste>();
        if (cT.valores == "Nathan")
        {
            flag = true;
            
        }
        if (cT.valores == "xau")
        {
            Debug.Log("XAU");
            flag = false;
        }

        if (position.x > 6f && flag == true)
        {
            aS.Play();
        }
        if(flag == true && (position.x > 5.1f))
        { 
            position.x += -Natvel * Time.deltaTime;
            transform.position = position;
            
        }
        else if(position.x >= 4.3f && position.x <= 5.1f){
            position.x = 5f;
            
        }
        if(flag == false)
        {
            position.x += Natvel * Time.deltaTime;
            transform.position = position;
            //position.x = 8.2f;
            position.x = 8.2f;
        }
        
    }
}
