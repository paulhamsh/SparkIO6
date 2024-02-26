#include "SparkIO.h"
#include "Spark.h"
#include "testdata.h"

byte get_preset[]{0x01, 0xFE, 0x00, 0x00, 0x53, 0xFE, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                  0xF0, 0x01, 0x09, 0x01, 0x02, 0x01,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00 ,0x00, 0x00, 0x00, 0x00,
                  0xF7};

byte gp_result[] {0x02, 0x01, 0x00, 0x26, 0x00, 0x09, 
                    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

int offset = 16;
int preset_to_get;

unsigned long t;
bool do_it;

byte new_block[2000];
byte new_block2[2000];

void setup() {
  Serial.begin(115200);
  //connect_to_all();
  spark_state_tracker_start();
  DEBUG("Starting");

  ble_passthru = true;

  t = millis();
  do_it = false;
  preset_to_get = 0;

  int new_len;

/*
  //dump_raw_block(blk_result, sizeof(blk_result));
  new_len = expand(new_block, blk_result, sizeof(blk_result));
  //dump_processed_block(new_block, new_len);
  add_bit_eight(new_block, new_len);
  //dump_processed_block(new_block, new_len);
  new_len = add_headers(new_block2, new_block, new_len);
  dump_processed_block(new_block2, new_len);
  Serial.println(memcmp(new_block2, blk, sizeof(blk)));

  Serial.println("==========");

  //dump_raw_block(blk2_result, sizeof(blk2_result));
  new_len = expand(new_block, blk2_result, sizeof(blk2_result));
  //dump_processed_block(new_block, new_len);
  add_bit_eight(new_block, new_len);
  //dump_processed_block(new_block, new_len);
  new_len = add_headers(new_block2, new_block, new_len);
  dump_processed_block(new_block2, new_len);
  Serial.println(memcmp(new_block2, blk2, sizeof(blk2)));

  Serial.println("==========");

  //dump_raw_block(blk3_result, sizeof(blk3_result));
  new_len = expand(new_block, blk3_result, sizeof(blk3_result));
  //dump_processed_block(new_block, new_len);
  add_bit_eight(new_block, new_len);
  //dump_processed_block(new_block, new_len);
  new_len = add_headers(new_block2, new_block, new_len);
  dump_processed_block(new_block2, new_len);
  Serial.println(memcmp(new_block2, blk3, sizeof(blk3)));
  Serial.println("==========");

  //dump_raw_block(block_from_spark, len);   
  new_len = remove_headers(get_preset, get_preset, sizeof(get_preset));
  dump_processed_block(get_preset, new_len);
  fix_bit_eight(get_preset, new_len);
  dump_processed_block(get_preset, new_len);
  new_len = compact(get_preset, get_preset, new_len);
  dump_processed_block(get_preset, new_len);

  Serial.println("^^^^^^^^^");
  new_len = expand(new_block, get_preset, sizeof(get_preset));
  dump_processed_block(new_block, new_len);

  add_bit_eight(new_block, new_len);
  dump_processed_block(new_block, new_len);
  new_len = add_headers(new_block2, new_block, new_len);
  dump_processed_block(new_block2, new_len);

  Serial.println("**************");
  //spark_message_out.change_hardware_preset(0, 3);
  spark_message_out.create_preset(&my_preset);
  spark_send();

  Serial.println("STALLED");
  while (true);
*/
}


unsigned int cmd_sub;
SparkMessage message;
SparkPreset pre;

void loop() {
  int len;
  int trim_len;

  // pre-wait before starting to request presets
  if (millis() - t > 10000 && !do_it) {
    do_it = true;
    t = millis();
  };



  if (update_spark_state()) {
    //Serial.println(cmdsub, HEX);
  };

if (millis() - t > 10000 && do_it) {
    Serial.println("Sending preset and update ui");
    spark_message_out.create_preset(&my_preset);
    spark_send();
    spark_message_out.change_hardware_preset(0, 1);
    spark_send();

    update_ui();

    t = millis();
    
  };


/*
  spark_process();
  app_process();

  if (spark_message_in.get_message(&cmd_sub, &message, &pre)) {
    t = millis();                              //  add to the delay
    Serial.print("SPK: ");
    Serial.println(cmd_sub, HEX);
    if (cmd_sub == 0x0301) Serial.println(preset.Name);
  };


  if (app_message_in.get_message(&cmd_sub, &message, &pre)) {
    t = millis();                              //  add to the delay
    Serial.print("APP: ");
    Serial.println(cmd_sub, HEX);
    if (cmd_sub == 0x0101) Serial.println(preset.Name);
  };

  
  if (millis() - t > 2000 && do_it) {
    
    //Serial.println("Sending preset request");
    //get_preset[offset + 2] = 0x30; // sequence number
    //get_preset[offset + 3] = preset_to_get; //checksum
    //get_preset[offset + 8] = preset_to_get;

    //pSender_sp->writeValue(get_preset, sizeof(get_preset), false);
    //t = millis();
    //preset_to_get++;
    //if (preset_to_get > 3) preset_to_get = 0;

    
    Serial.println("Sending preset");
    //spark_message_out.get_serial();
    spark_message_out.create_preset(&my_preset);
    spark_send();

    spark_message_out.change_hardware_preset(0, 1);
    spark_send();
    //spark_message_out.change_hardware_preset(0, 1);
    //spark_send();
    //spark_message_out.out_message.dump3();
    t = millis();
    
  };
  */

}
