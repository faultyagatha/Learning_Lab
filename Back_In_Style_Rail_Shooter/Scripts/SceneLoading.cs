using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneLoading : MonoBehaviour {

  // Use this for initialization
  void Start() {
    Invoke("LoadFirstScene", 4f);
  }

  // Update is called once per frame
  void LoadFirstScene() {
    SceneManager.LoadScene(1);

  }
}
