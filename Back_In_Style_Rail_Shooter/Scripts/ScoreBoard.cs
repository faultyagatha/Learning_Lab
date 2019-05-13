using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreBoard : MonoBehaviour {

  int score = 0;
  Text scoreText;

	// Use this for initialization
	void Start () {
    scoreText = GetComponent<Text>(); //get a reference to the component of type Text
    scoreText.text = score.ToString(); //Text is a string, so we need to convert our score to string to be visible
	}

  public void ScoreHit(int scoreIncrease) { //'public' is visible to other classes
    score = score + scoreIncrease;
    scoreText.text = score.ToString(); //update the score on the screen
  }
}
