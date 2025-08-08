const int pinPM25 = 9;
const int pinPM1 = 8;
const unsigned long sampleTime = 2000;  // Reduced to 2 seconds for faster updates

float calc_low_ratio(float lowPulse) {
  return lowPulse / sampleTime * 100.0;  // low ratio in %
}

float calc_c_mgm3(float lowPulse) {
  float r = calc_low_ratio(lowPulse);
  float c_mgm3 = 0.00258425 * pow(r, 2) + 0.0858521 * r - 0.01345549;
  return max(0, c_mgm3);
}

float calc_c_pcs283ml(float lowPulse) {
  float r = calc_low_ratio(lowPulse);
  float c_pcs283ml =  625 * r;
  return min(c_pcs283ml, 12500);
}

void setup() {
  Serial.begin(9600);
  pinMode(pinPM25, INPUT);
  pinMode(pinPM1, INPUT);
  Serial.println("Warming up...");
  delay(20000);  // 1 minute warm-up
}

void loop() {
  static unsigned long t_start = millis();
  static float lowPM = 0;

  unsigned long pulseDuration = pulseIn(pinPM25, LOW, 100000); // 100 ms timeout
  if (pulseDuration > 0) {
    lowPM += pulseDuration / 1000.0; // Accumulate pulse duration
  }

  if ((millis() - t_start) >= sampleTime) {
    float lowRatio = calc_low_ratio(lowPM);

    if (lowRatio < 0.1) {
      Serial.println("No significant dust detected.");
    } else {
      Serial.print("low_%  PM    : ");
      Serial.println(lowRatio);
      Serial.print("c_mgm3 PM    : ");
      Serial.println(calc_c_mgm3(lowPM));
      Serial.print("c_pcs283ml PM: ");
      Serial.println(calc_c_pcs283ml(lowPM));
      Serial.println();
    }

    lowPM = 0;
    t_start = millis();
  }
}



// const int pinPM25 = 7;
// const int pinPM1 = 8;
// const unsigned long sampleTime = 5000;  // mSec   -> 5..30 sec

// float calc_low_ratio(float lowPulse) {
//   return lowPulse / sampleTime * 100.0;  // low ratio in %
// }

// float calc_c_mgm3(float lowPulse) {
//   float r = calc_low_ratio(lowPulse);
//   float c_mgm3 = 0.00258425 * pow(r, 2) + 0.0858521 * r - 0.01345549;
//   return max(0, c_mgm3);
// }

// float calc_c_pcs283ml(float lowPulse) {
//   float r = calc_low_ratio(lowPulse);
//   float c_pcs283ml =  625 * r;
//   return min(c_pcs283ml, 12500);
// }

// void setup() {
//   Serial.begin(9600);
//   pinMode(pinPM25, INPUT);
//   pinMode(pinPM1, INPUT);
//   Serial.println("Warming up...");
//   // delay(60000);  // 1 minute warm-up
// }

// void loop() {
//   static unsigned long t_start = millis();
//   static float lowPM = 0;

//   lowPM += pulseIn(pinPM25, LOW) / 1000.0;   // >2.5µm (PM2.5)
//   //lowPM += pulseIn(pinPM1, LOW) / 1000.0;  // >1µm (PM1)

//   if ((millis() - t_start) >= sampleTime) {
//     Serial.print("low_%  PM    : ");
//     Serial.println(calc_low_ratio(lowPM));
//     Serial.print("c_mgm3 PM    : ");
//     Serial.println(calc_c_mgm3(lowPM));
//     Serial.print("c_pcs283ml PM: ");
//     Serial.println(calc_c_pcs283ml(lowPM));   
//     Serial.println();
//     lowPM = 0;
//     t_start = millis();
//   }
// }
