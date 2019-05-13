using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundController : MonoBehaviour {

  private void Awake() {
    int numMusicPlayers = FindObjectsOfType<AudioSource>().Length;
    if (numMusicPlayers > 1) {
      Destroy(gameObject); //we could also use 'this' instead of gameObject instance
    } else {
      DontDestroyOnLoad(gameObject);
    }

   }
}
