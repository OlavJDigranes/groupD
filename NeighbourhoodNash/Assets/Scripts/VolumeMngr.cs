using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class VolumeMngr : MonoBehaviour
{
    public AudioMixer mixer; 

    public void SetVol(float vol)
    {
        mixer.SetFloat("Volume", vol); 
    }
}

//Probably shortest script in this thing. Yay me. 