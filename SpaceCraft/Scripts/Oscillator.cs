using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[DisallowMultipleComponent] // make sure we have only one script attached
public class Oscillator : MonoBehaviour {



  [SerializeField] Vector3 movementVector = new Vector3(10f, 10f, 10f); //store a movement vector
  [SerializeField] float period = 2f;

  [Range(0, 1)] [SerializeField] float movementFactor; //store a movement factor

  Vector3 startingPosition; //store a starting position for absolute movement

  // Use this for initialization
  void Start () {
    startingPosition = transform.position; //get a starting position from the game object

  }
	
	// Update is called once per frame
	void Update () {
    //set movement factor
    if (period <= Mathf.Epsilon) { return; }
    float cycles = Time.time / period; //grows continuosly starting from 0
    const float tau = 2 * Mathf.PI;
    float rawSin = Mathf.Sin(cycles * tau);
    movementFactor = rawSin / 2f + 0.5f;

    Vector3 offset = movementVector * movementFactor;
    transform.position = startingPosition + offset;
	}
}
