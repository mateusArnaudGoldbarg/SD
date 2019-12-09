using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCar : MonoBehaviour
{
    ComunicacaoTeste cT;

    private float carspeed;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        cT = FindObjectOfType<ComunicacaoTeste>();

        if (cT != null)
        {
            Debug.Log(cT.valor.ToString());
        }
        carspeed = 10f * (cT.valor + 1)/ 177 + 1;
        transform.Translate(new Vector3(0, -1, 0) * carspeed *Time.deltaTime );
    }
}
