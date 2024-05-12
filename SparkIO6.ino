#define CLASSIC
//#define PSRAM

#include "SparkIO.h"
#include "Spark.h"

void setup() {
  Serial.begin(115200);

  spark_state_tracker_start();
  DEBUG("Starting");
}


void loop() {
  if (update_spark_state() {
    Serial.print("Got message ");
    Serial.println(cmdsub, HEX);
  }
}
