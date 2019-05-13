using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour {

  [SerializeField] GameObject deathFX;
  [SerializeField] int scorePerHit = 9;

  ScoreBoard scoreBoard;

  // Use this for initialization
  void Start () {
    AddBoxCollider();
    scoreBoard = FindObjectOfType<ScoreBoard>(); //look at runtime in the 'enemy' and find scoreBoard
	}

  private void AddBoxCollider() {
    Collider enemyCollider = gameObject.AddComponent<BoxCollider>();
    enemyCollider.isTrigger = false;
  }

  void OnParticleCollision(GameObject other) {
    scoreBoard.ScoreHit(scorePerHit);
    Instantiate(deathFX, transform.position, Quaternion.identity);
    Destroy(gameObject);

  }
}
