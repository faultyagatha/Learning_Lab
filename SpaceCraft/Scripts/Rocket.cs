using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

//debuging keys: L - jump to the next level; C - toggle collision on and off

public class Rocket : MonoBehaviour {

  [SerializeField] float rcsThrust = 250f; //make the value available in the inspector without making it public for all
  [SerializeField] float mainThrust = 300f;
  [SerializeField] float levelLoadDelay = 2f;


  [SerializeField] AudioClip mainEngine;
  [SerializeField] AudioClip dyingState;
  [SerializeField] AudioClip successState;

  [SerializeField] ParticleSystem mainEngineParticles; //todo: in the future, instansiate particles in code instead of copying them
  [SerializeField] ParticleSystem successParticles;
  [SerializeField] ParticleSystem deathParticles;

  Rigidbody rigidBody;
  AudioSource audioSource;

  enum State { Alive, Dying, Transcending }
  State state = State.Alive; //default state
  bool collisionsAreEnabled = true; //debug collisions

	//initialization
  void Start () {
    rigidBody = GetComponent<Rigidbody>(); //get component of type 'Rigidbody'
    audioSource = GetComponent<AudioSource>(); //get component of type 'AudioSource'

  }
	
  void Update () {
    if (state == State.Alive) {
      RespondToRotateInput();
      RespondToThrustInput();
    }
    if (Debug.isDebugBuild) { //only if in debug mode (can be toggled in Build)
      SwithToDebugMode();
    }
  }

  private void RespondToRotateInput() {
    rigidBody.freezeRotation = true; //take manual control over rotation
    float rotationThisFrame = rcsThrust * Time.deltaTime;  //diverse command over rotation 

    if (Input.GetKey(KeyCode.A)) {
      transform.Rotate(Vector3.forward * rotationThisFrame); //go clockwise around z
      Debug.Log("Rotating Left");
    } else if (Input.GetKey(KeyCode.D)) {
      transform.Rotate(-Vector3.forward * rotationThisFrame); //go anti-clockwise around z
      Debug.Log("Rotating Right");
    }
    rigidBody.freezeRotation = false; //resume physics control over rotation
  }

  private void RespondToThrustInput() {
    if (Input.GetKey(KeyCode.Space)) {
      ApplyThrust();
    } else {
      audioSource.Stop();
      mainEngineParticles.Stop();
    }
  }

  private void SwithToDebugMode() {
    if (Input.GetKeyDown(KeyCode.L)) {
      LoadNextLevel();
    } else if (Input.GetKeyDown(KeyCode.C)) {
      collisionsAreEnabled = !collisionsAreEnabled; //toggle collision for debugging
    }
  }

  private void OnCollisionEnter(Collision collision) {
    if (state != State.Alive || !collisionsAreEnabled) { return; } //if we're not alive stop the execution; just another identation without else statement
    switch (collision.gameObject.tag) {
      case "Friendly":
        //do nothing
        break;
      case "Finish":
        StartSuccessSequence();
        break;
      default:
        StartDeathSequence();
        break;
    }
  }

  private void StartSuccessSequence() {
    state = State.Transcending;
    audioSource.Stop();
    audioSource.PlayOneShot(successState);
    successParticles.Play();
    Invoke("LoadNextLevel", levelLoadDelay); 
  }

  private void StartDeathSequence() {
    print("dead");
    state = State.Dying;
    audioSource.Stop();
    audioSource.PlayOneShot(dyingState);
    deathParticles.Play();
    Invoke("LoadFirstLevel", levelLoadDelay); 
  }

  private void LoadNextLevel() {
    int currentSceneIndex = SceneManager.GetActiveScene().buildIndex;
    int nextSceneIndex = currentSceneIndex + 1; 
    SceneManager.LoadScene(nextSceneIndex);
    print(currentSceneIndex);
    //we can't store the level index on the rocket because the rocket gets reset every time we change the level
    //we use conditionals instead
    if (currentSceneIndex % SceneManager.sceneCountInBuildSettings == 0 ) {
      nextSceneIndex = 0;
    }
  }

  private void LoadFirstLevel() {
    SceneManager.LoadScene(0); // todo: allow for more than 2 levels
  }

  private void ApplyThrust() {
    rigidBody.AddRelativeForce(Vector3.up * mainThrust * Time.deltaTime); //make thrust framerate independent
    if (!audioSource.isPlaying) { //TODO: put the audio in the separate method
      audioSource.PlayOneShot(mainEngine);
    }
    mainEngineParticles.Play();
    }
  }
