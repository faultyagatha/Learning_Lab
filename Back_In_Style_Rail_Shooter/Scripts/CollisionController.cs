using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement; //ok as long as we use only 1 script that loads the scenes

public class CollisionController : MonoBehaviour {

  [Tooltip("In seconds")] [SerializeField] float levelLoadDelay = 1f;
  [Tooltip("FX prefab on player")] [SerializeField] GameObject deathFX;

  // Use this for initialization
  void Start () {
		
	}

  private void OnTriggerEnter(Collider other) {
    StartDeathSequence();
    deathFX.SetActive(true);
    Invoke("ReloadScene", levelLoadDelay);
  }

  private void StartDeathSequence() {
    SendMessage("OnPlayerDeath");
  }

  // Update is called once per frame
  private void ReloadScene() { //string referenced
    SceneManager.LoadScene(1);
		
	}
}
