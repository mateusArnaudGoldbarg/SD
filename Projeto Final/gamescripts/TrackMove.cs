using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrackMove : MonoBehaviour
{
    private float speed = 1.0f;
    Vector2 Offset;
    ComunicacaoTeste cT;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        cT = FindObjectOfType<ComunicacaoTeste>();
        speed = cT.valor / 50;
        Offset = new Vector2(0, Time.time * speed);

        GetComponent<Renderer>().material.mainTextureOffset = Offset;
    }
}
