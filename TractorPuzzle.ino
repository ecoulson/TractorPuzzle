#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

// Wire Pin Outputs
const int GreenWireOutput = 2;
const int RedWireOutput = 3;
const int BlueWireOutput = 4;
const int YellowWireOutput = 5;
const int WhiteWireOutput = 6;

// Wire Input Pins
const int GreenWireInput = A7;
const int RedWireInput = A6;
const int BlueWireInput = A5;
const int YellowWireInput = A1;
const int WhiteWireInput = A0;

// Expected Values
const long GreenWireExpectedPulseLength = 797;
const long RedWireExpectedPulseLength = 1026;
const long BlueWireExpectedPulseLength = 640;
const long YellowWireExpectedPulseLength = 1511;
const long WhiteWireExpectedPulseLength = 1742;

//Speaker Pin
const int SpeakerPin = 11;

// Margin of error for pulse readings
const int MarginOfError = 50;

const char* filename = "test.wav";
File audioTrack;
TMRpcm tmrpcm;

// solved state
bool isSolved = false;


void setup() {
  tmrpcm.speakerPin = SpeakerPin;
  // Beign serial
  Serial.begin(9600);

  if (!SD.begin(53)) {
    Serial.println("SD card failed");
    return;
  }

  // Set pin modes of inputs
  pinMode(GreenWireInput, INPUT);
  pinMode(RedWireInput, INPUT);
  pinMode(RedWireInput, INPUT);
  pinMode(YellowWireInput, INPUT);
  pinMode(WhiteWireInput, INPUT);

  // Write wire values
  analogWrite(GreenWireOutput, 100);
  analogWrite(RedWireOutput, 130);
  analogWrite(BlueWireOutput, 160);
  analogWrite(YellowWireOutput, 190);
  analogWrite(WhiteWireOutput, 220);  
}

void loop() {
  // Get pulse data
  long greenPulse = pulseIn(GreenWireInput, HIGH);
  long redPulse = pulseIn(RedWireInput, HIGH);
  long bluePulse = pulseIn(BlueWireInput, HIGH);
  long yellowPulse = pulseIn(YellowWireInput, HIGH);
  long whitePulse = pulseIn(WhiteWireInput, HIGH);

  // Check if puzzle is solved
  if (IsCorrectPulseLength(greenPulse, GreenWireExpectedPulseLength) && 
       IsCorrectPulseLength(redPulse, RedWireExpectedPulseLength) &&
       IsCorrectPulseLength(bluePulse, BlueWireExpectedPulseLength) &&
       IsCorrectPulseLength(yellowPulse, YellowWireExpectedPulseLength) &&
       IsCorrectPulseLength(whitePulse, WhiteWireExpectedPulseLength) && 
     !isSolved) {
    PlayAudioClue();
    delay(5000);
    PlayAudioClue();
    isSolved = true;
   }
}

// Checks for the correct pulse length on a passed input pin
bool IsCorrectPulseLength(long pulseLength, long expectedPulseLength) {
  return pulseLength <= expectedPulseLength + MarginOfError &&
    pulseLength >= expectedPulseLength - MarginOfError;
}


// Plays the audio clue to unlock the number lock
void PlayAudioClue() {
  delay(500);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(4000);
  
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(3000);

  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(3000);

  delay(2000);
  tmrpcm.play("tractor2.wav");
  delay(3000);
}

  




