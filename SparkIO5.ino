#include "SparkComms.h"
#include "SparkIO.h"
#include "RingBuffer.h"
#include "SparkStructures.h"
#include "testdata.h"

byte get_preset[]{0x01, 0xFE, 0x00, 0x00, 0x53, 0xFE, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                  0xF0, 0x01, 0x09, 0x01, 0x02, 0x01,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00 ,0x00, 0x00, 0x00, 0x00,
                  0xF7};
int offset = 16;
int preset_to_get;

unsigned long t;
bool do_it;

byte new_block[BLOCK_SIZE];

void setup() {
  Serial.begin(115200);
  //connect_to_all();
  DEBUG("Starting");

  ble_passthru = true;

  t = millis();
  do_it = false;
  preset_to_get = 0;

  dump_raw_block(blk3_result, sizeof(blk3_result));
  int new_len = expand(new_block, blk3_result, sizeof(blk3_result));
  dump_processed_block(new_block, new_len);
  add_bit_eight(new_block, new_len);
  dump_processed_block(new_block, new_len);

  Serial.println("STALLED");
  while (true);

}


unsigned int cmdsub;
SparkMessage message;
SparkPreset preset;

void loop() {
  int len;
  int trim_len;

  // pre-wait before starting to request presets
  if (millis() - t > 10000 && !do_it) {
    do_it = true;
    t = millis();
  };


  spark_process();
  app_process();

  if (spark_message_in.get_message(&cmdsub, &message, &preset)) {
    t = millis();                              //  add to the delay
    Serial.print("SPK: ");
    Serial.println(cmdsub, HEX);
    if (cmdsub == 0x0301) Serial.println(preset.Name);
  };


  if (app_message_in.get_message(&cmdsub, &message, &preset)) {
    t = millis();                              //  add to the delay
    Serial.print("APP: ");
    Serial.println(cmdsub, HEX);
    if (cmdsub == 0x0101) Serial.println(preset.Name);
  };

  
  if (millis() - t > 10000 && do_it) {
    Serial.println("Sending preset request");
    get_preset[offset + 2] = 0x30; // sequence number
    get_preset[offset + 3] = preset_to_get; //checksum
    get_preset[offset + 8] = preset_to_get;

    pSender_sp->writeValue(get_preset, sizeof(get_preset), false);
    t = millis();
    preset_to_get++;
    if (preset_to_get > 3) preset_to_get = 0;


    //spark_message_out.change_hardware_preset(0, 1);
    //spark_message_out.out_message.dump3();
  };


}
