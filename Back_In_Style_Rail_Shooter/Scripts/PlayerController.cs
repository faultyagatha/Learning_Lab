using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityStandardAssets.CrossPlatformInput;

public class PlayerController : MonoBehaviour {

  [Header("General")]
  [Tooltip("in ms^-1")] [SerializeField] float xSpeed = 15f;
  [Tooltip("in ms^-1")] [SerializeField] float ySpeed = 10f;
  [Tooltip("in ms^-1")] [SerializeField] float xRange = 5f;
  [Tooltip("in ms^-1")] [SerializeField] float yRange = 3f;

  [Header("Screen-position parameters")]
  [SerializeField] float posPitchFactor = -5f;
  [SerializeField] float posYawhFactor = 5f;

  [Header("Control-throw parameters")]
  [SerializeField] float controlPitchFactor = -20f;
  [SerializeField] float controlRollFactor = -10f;

  float xThrow, yThrow;
  bool isControlEnabled = true;


  // Use this for initialization
  void Start () {
  }

  // Update is called once per frame
  void Update () {
    if (isControlEnabled) {
      ProcessTranslation();
      ProcessRotation();
    }
  }

  void OnPlayerDeath() { //called by string reference
    print("controls flozen");
    isControlEnabled = false;

  }

  private void ProcessTranslation() {
    xThrow = CrossPlatformInputManager.GetAxis("Horizontal"); //goes between 0 and 1; the transition depends on the values of gravity and sensitivity in the inspector
    yThrow = CrossPlatformInputManager.GetAxis("Vertical");

    float xOffsetThisFrame = xThrow * xSpeed * Time.deltaTime;
    float yOffsetThisFrame = yThrow * ySpeed * Time.deltaTime;

    float clampedXpos = Mathf.Clamp(transform.localPosition.x + xOffsetThisFrame, -xRange, xRange); //make the transition smooth
    float clampedYpos = Mathf.Clamp(transform.localPosition.y + yOffsetThisFrame, -yRange, yRange); //make the transition smooth

    transform.localPosition = new Vector3(clampedXpos, clampedYpos, transform.localPosition.z);
  }

  private void ProcessRotation() { //order matters, use Quaternion for rotations; // example: Quaternion.Euler(0f, 30f, 0f); is a rotation 30 degrees around the y-axis; 
    float pitchDueToPosition = transform.localPosition.y * posPitchFactor; //coupled to the pos on screen
    float pitchDueToControlThrow = yThrow * controlPitchFactor; //coupled to the control throw 

    float yaw = transform.localPosition.x * posYawhFactor;
    float roll = xThrow * controlRollFactor;
    float pitch = pitchDueToPosition + pitchDueToControlThrow; 

    transform.localRotation = Quaternion.Euler(pitch, yaw, roll); //local - because our player is childed to the camera; 

  }
}
