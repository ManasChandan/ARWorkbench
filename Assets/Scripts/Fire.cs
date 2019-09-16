using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Firebase;
using Firebase.Database;
using Firebase.Unity.Editor;
using UnityEngine.UI;

public class Fire : MonoBehaviour
{   public Text temp = null;
    public Text hum = null;
    public Text wtlevel = null;
    public float text2 ;




    // Start is called before the first frame update
    void Start()
    {
        // Set up the Editor before calling into the realtime database.
        FirebaseApp.DefaultInstance.SetEditorDatabaseUrl("https://lights-7c4ff.firebaseio.com/");

     
        FirebaseDatabase.DefaultInstance
     .GetReference("Temperature")
     .ValueChanged += HandleValueChangedTemp;

        FirebaseDatabase.DefaultInstance
     .GetReference("WaterLevel")
     .ValueChanged += HandleValueChangedwtlevel;

        FirebaseDatabase.DefaultInstance
    .GetReference("Humidity")
    .ValueChanged += HandleValueChangedhum;


    }

    void HandleValueChangedTemp(object sender, ValueChangedEventArgs args)
    {
        if (args.DatabaseError != null)
        {
            Debug.LogError(args.DatabaseError.Message);
            return;
        }
        // Do something with the data in args.Snapshot
        temp.text = args.Snapshot.GetRawJsonValue();
    }
    void HandleValueChangedwtlevel(object sender, ValueChangedEventArgs args)
    {
        if (args.DatabaseError != null)
        {
            Debug.LogError(args.DatabaseError.Message);
            return;
        }
        // Do something with the data in args.Snapshot
        wtlevel.text = args.Snapshot.GetRawJsonValue();
        text2 = (float.Parse(wtlevel.text))*0.0008f;
    }

    void HandleValueChangedhum(object sender, ValueChangedEventArgs args)
    {
        if (args.DatabaseError != null)
        {
            Debug.LogError(args.DatabaseError.Message);
            return;
        }
        // Do something with the data in args.Snapshot
        hum.text = args.Snapshot.GetRawJsonValue();
    }
}


