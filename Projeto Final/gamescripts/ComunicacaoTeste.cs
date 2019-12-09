using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using UnityEngine.UI;

public class ComunicacaoTeste : MonoBehaviour
{
    public GameObject nat;
    private float carSpeed = 14f;
    private float natSpeed = 5f;
    private float minpos = -1.9f;
    private float maxpos = 1.9f;
    public string valores;
    public UIManager ui;
    public int valor;
    Vector3 position;
    public Text speedText;
    SerialPort myport = new SerialPort("COM3", 9600);
    
    // Start is called before the first frame update
    void Start()
    {
        //ui = GetComponent<UIManager>();
        position = transform.position;

        myport.Open();
        myport.ReadTimeout = 5;
    }

    // Update is called once per frame
    void Update()
    {
        string data_rx = myport.ReadTo("\n");
        //Debug.Log(data_rx);
        valores = data_rx;
        if (data_rx == "E")
        {
            Debug.Log("Esquerda");
            position.x += -carSpeed * Time.deltaTime;
            transform.position = position;
            //transform.position = Vector2.Lerp(transform.position,newPosition, -carSpeed * Time.deltaTime);
            
        }

        else if (data_rx == "D")
        {
            Debug.Log("Direita");
            position.x += carSpeed * Time.deltaTime;
            transform.position = position;
            //transform.position = Vector2.Lerp(transform.position,newPosition, carSpeed * Time.deltaTime);

        }

        else if(data_rx != "E" && data_rx != "D" && data_rx != "Nathan" && data_rx != "xau")
        {
            char character = data_rx[0];
            valor = character + 50;
            speedText.text = "SPEED: " + valor + "Km/h";
        }



        position.x = Mathf.Clamp(position.x, -1.9f, 1.9f);
        
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        
        Debug.Log("Bateu");
        if (col.gameObject.tag == "ENEMY")
        {
            Destroy(gameObject);
            ui.gameOverActivated();
            myport.Close();
        }
        
    }
}
