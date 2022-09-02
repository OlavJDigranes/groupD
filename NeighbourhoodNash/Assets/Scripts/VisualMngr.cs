using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro; 

public class VisualMngr : MonoBehaviour
{
    Resolution[] reses;

    public TMP_Dropdown resDrop; 

    void Start()
    {
        //This makes me annoyed at having to ever use SFML. This is better
        List<string> options = new List<string>(); 

        reses = Screen.resolutions;

        resDrop.ClearOptions();

        int currentRes = 0;
        for (int i = 0; i < reses.Length; i++) {
            string option = reses[i].width + "X" + reses[i].height;
            options.Add(option);

            if (reses[i].width == Screen.currentResolution.width && reses[i].height == Screen.currentResolution.height)
            {
                currentRes = i; 
            }
        }

        resDrop.AddOptions(options);
        resDrop.value = currentRes;
        resDrop.RefreshShownValue(); 
    }

    public void SetQual(int index)
    {
        QualitySettings.SetQualityLevel(index, true); 
    }

    public void SetFS(bool isFS)
    {
        Screen.fullScreen = isFS; 
    }

    public void SetRes(int resIndex)
    {
        Resolution res = reses[resIndex]; 
        Screen.SetResolution(res.width, res.height, Screen.fullScreen); 
    }
}
