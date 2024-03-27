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

int blk_size;
byte new_block[2000];
byte new_block2[2000];

void setup() {
  Serial.begin(115200);

//  byte tb[]{0xF0, 0x01, 0x05, 0x00, 0x03, 0x10, 0x00, 0x00, 0x00, 0xF7, 0xF0, 0x01, 0x06, 0x16, 0x03, 0x01, 0x20, 0x0F, 0x00, 0x19, 0x01, 0x00, 0x59, 0x24, 0x00, 0x44, 0x37, 0x32, 0x43, 0x31, 0x35, 0x31, 0x00, 0x38, 0x2D, 0x45, 0x42, 0x30, 0x44, 0x2D, 0x00, 0x34, 0x43, 0x31, 0x46, 0x2D, 0x39, 0x34, 0xF7, 0xF0, 0x01, 0x06, 0x30, 0x03, 0x01, 0x00, 0x0F, 0x01, 0x19, 0x34, 0x32, 0x2D, 0x44, 0x00, 0x45, 0x45, 0x37, 0x39, 0x36, 0x34, 0x35, 0x10, 0x39, 0x42, 0x34, 0x33, 0x25, 0x50, 0x48, 0x08, 0x20, 0x41, 0x43, 0x23, 0x30, 0x2E, 0x37, 0xF7, 0xF0, 0x01, 0x06, 0x57, 0x03, 0x01, 0x08, 0x0F, 0x02, 0x19, 0x27, 0x31, 0x2D, 0x43, 0x10, 0x6C, 0x65, 0x61, 0x6E, 0x28, 0x69, 0x63, 0x40, 0x6F, 0x6E, 0x2E, 0x70, 0x6E, 0x67, 0x4A, 0x32, 0x42, 0x70, 0x00, 0x00, 0x17, 0x2E, 0x62, 0xF7, 0xF0, 0x01, 0x06, 0x7B, 0x03, 0x01, 0x00, 0x0F, 0x03, 0x19, 0x69, 0x61, 0x73, 0x2E, 0x00, 0x6E, 0x6F, 0x69, 0x73, 0x65, 0x67, 0x61, 0x6C, 0x74, 0x65, 0x43, 0x13, 0x00, 0x11, 0x4A, 0x6E, 0x3E, 0x2C, 0x02, 0x11, 0x01, 0x11, 0x4A, 0xF7, 0xF0, 0x01, 0x06, 0x49, 0x03, 0x01, 0x30, 0x0F, 0x04, 0x19, 0x3E, 0x59, 0x02, 0x0F, 0x16, 0x02, 0x11, 0x4A, 0x3F, 0x00, 0x00, 0x00, 0x01, 0x2A, 0x43, 0x6F, 0x6D, 0x70, 0x72, 0x65, 0x30, 0x73, 0x73, 0x6F, 0x72, 0x43, 0x12, 0x00, 0xF7, 0xF0, 0x01, 0x06, 0x24, 0x03, 0x01, 0x18, 0x0F, 0x05, 0x19, 0x11, 0x4A, 0x3F, 0x07, 0x1A, 0x4C, 0x67, 0x01, 0x11, 0x4A, 0x3F, 0x7F, 0x05, 0x47, 0x4B, 0x27, 0x42, 0x6F, 0x6F, 0x73, 0x58, 0x74, 0x65, 0x72, 0x43, 0x11, 0x00, 0x11, 0xF7, 0xF0, 0x01, 0x06, 0x7B, 0x03, 0x01, 0x08, 0x0F, 0x06, 0x19, 0x4A, 0x3F, 0x0F, 0x1F, 0x02, 0x78, 0x28, 0x41, 0x43, 0x20, 0x42, 0x6F, 0x58, 0x6F, 0x73, 0x74, 0x43, 0x15, 0x00, 0x11, 0x45, 0x4A, 0x3E, 0x0C, 0x55, 0x54, 0x01, 0x11, 0xF7, 0xF0, 0x01, 0x06, 0x3D, 0x03, 0x01, 0x28, 0x0F, 0x07, 0x19, 0x4A, 0x3E, 0x70, 0x4E, 0x0C, 0x62, 0x02, 0x11, 0x4A, 0x3F, 0x01, 0x0E, 0x2D, 0x4F, 0x03, 0x11, 0x4A, 0x3E, 0x2C, 0x7C, 0x6D, 0x65, 0x04, 0x11, 0x4A, 0x3D, 0x71, 0x06, 0xF7, 0xF0, 0x01, 0x06, 0x3C, 0x03, 0x01, 0x10, 0x0F, 0x08, 0x19, 0x4C, 0x2C, 0x43, 0x68, 0x00, 0x6F, 0x72, 0x75, 0x73, 0x41, 0x6E, 0x61, 0x58, 0x6C, 0x6F, 0x67, 0x42, 0x14, 0x00, 0x11, 0x55, 0x4A, 0x3E, 0x41, 0x15, 0x32, 0x01, 0x11, 0xF7, 0xF0, 0x01, 0x06, 0x38, 0x03, 0x01, 0x08, 0x0F, 0x09, 0x19, 0x4A, 0x3F, 0x11, 0x5B, 0x0C, 0x1E, 0x02, 0x11, 0x4A, 0x3E, 0x5D, 0x49, 0x2D, 0x44, 0x03, 0x11, 0x4A, 0x3E, 0x00, 0x00, 0x02, 0x00, 0x29, 0x44, 0x65, 0x6C, 0x61, 0x79, 0xF7, 0xF0, 0x01, 0x06, 0x0B, 0x03, 0x01, 0x00, 0x0F, 0x0A, 0x19, 0x4D, 0x6F, 0x6E, 0x6F, 0x1B, 0x42, 0x15, 0x00, 0x11, 0x4A, 0x3E, 0x1F, 0x1B, 0x31, 0x20, 0x01, 0x11, 0x4A, 0x3E, 0x6E, 0x5B, 0x24, 0x61, 0x02, 0x11, 0x4A, 0x3E, 0x7B, 0xF7, 0xF0, 0x01, 0x06, 0x04, 0x03, 0x01, 0x40, 0x0F, 0x0B, 0x19, 0x24, 0x57, 0x03, 0x11, 0x51, 0x4A, 0x3F, 0x1B, 0x55, 0x6A, 0x04, 0x11, 0x25, 0x4A, 0x3F, 0x00, 0x00, 0x00, 0x2B, 0x62, 0x00, 0x69, 0x61, 0x73, 0x2E, 0x72, 0x65, 0x76, 0xF7, 0xF0, 0x01, 0x06, 0x39, 0x03, 0x01, 0x40, 0x0F, 0x0C, 0x19, 0x65, 0x72, 0x62, 0x42, 0x0D, 0x18, 0x00, 0x11, 0x4A, 0x3F, 0x30, 0x55, 0x2C, 0x4B, 0x01, 0x11, 0x4A, 0x3E, 0x49, 0x24, 0x2D, 0x12, 0x02, 0x11, 0x4A, 0x3E, 0x6C, 0x1A, 0xF7, 0xF0, 0x01, 0x06, 0x0D, 0x03, 0x01, 0x60, 0x0F, 0x0D, 0x19, 0x48, 0x03, 0x11, 0x4A, 0x6C, 0x3F, 0x31, 0x16, 0x20, 0x04, 0x11, 0x4A, 0x6E, 0x3E, 0x79, 0x79, 0x7A, 0x05, 0x11, 0x4A, 0x66, 0x3E, 0x6E, 0x4A, 0x38, 0x06, 0x11, 0x4A, 0xF7, 0xF0, 0x01, 0x06, 0x66, 0x03, 0x01, 0x70, 0x0F, 0x0E, 0x0C, 0x3E, 0x19, 0x19, 0x1A, 0x06, 0x07, 0x11, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x01, 0x64, 0xF7};
//  byte t2[1000];
//    int trim_len = remove_headers(tb, tb, sizeof(tb));
//    dump_raw_block(tb, trim_len);
//    fix_bit_eight(tb, trim_len);
//    dump_raw_block(tb, trim_len);
//    int len = compact(tb, tb, trim_len);
//    dump_raw_block(tb, len);


  spark_state_tracker_start();
  DEBUG("Starting");

  t = millis();
  do_it = false;
  preset_to_get = 0;

  int new_len;


/*  
  spark_msg_out.get_preset_details(1);
  spark_msg_out.copy_message_to_array(new_block, &blk_size);
  new_len = expand(new_block2, new_block, blk_size);
  add_bit_eight(new_block2, new_len);
  new_len = add_headers(new_block, new_block2, new_len);
  dump_processed_block(new_block, new_len);
*/


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

void dump_preset(SparkPreset *p){
  Serial.print(p->curr_preset); Serial.print(" ");
  Serial.println(p->preset_num); 
  Serial.println(p->UUID); 
  Serial.println(p->Name); 
  Serial.println(p->Version); 
  Serial.println(p->Description); 
  Serial.println(p->Icon); 
  Serial.println(p->BPM); 
  Serial.println(p->chksum); 
  for (int i=0; i<7; i++) {
    Serial.print(p->effects[i].EffectName); Serial.print(" : ");
    Serial.print(p->effects[i].NumParameters);
    for (int j=0; j<p->effects[i].NumParameters; j++) {
      Serial.print(p->effects[i].Parameters[j]); Serial.print(" ");
    }
    Serial.println();
      
  }
  Serial.println();
}

unsigned int cmd_sub;
SparkMessage message;
SparkPreset pre;
int p = 0;
float v=60.0;


void loop() {
  int len;
  int trim_len;


  // pre-wait before starting to request presets
  if (millis() - t > 10000 && !do_it) {
    do_it = true;
    t = millis();
  };


  if (update_spark_state()) {
    t = millis();
    //Serial.println(cmdsub, HEX);
  };


if (millis() - t > 10000 && do_it) {
    //Serial.println("Sending preset and update ui");
    //spark_message_out.create_preset(&my_preset);
    //spark_send();
    //spark_message_out.change_hardware_preset(0, p);
    //spark_send();
    //app_message_out.change_hardware_preset(0, p);
    //app_send();
    //delay(200);
    //app_message_out.save_hardware_preset(0x00, p++); //0x03);
    //app_send();

    //p++;
    //if (p > 3) p = 0;
    
    //update_ui_hardware();
    Serial.print("Send tap tempo");
    Serial.println(v);
    spark_msg_out.send_tap_tempo(v);
    spark_send();
    v += 10.0;
    if (v > 200.0) v = 60.0;


/*
  bool got;

  app_message_out.save_hardware_preset(0x00, 0x03);
  app_send();

  Serial.println("Updating UI");
  got = wait_for_app(0x0201);
  if (got) {
    strcpy(presets[5].Name, "SyncPreset");
    strcpy(presets[5].UUID, "F00DF00D-FEED-0123-4567-987654321000");  
    presets[5].curr_preset = 0x00;
    presets[5].preset_num = 0x03;
    //dump_preset(&presets[5]);
    app_message_out.create_preset(&presets[5]);
    //app_message_out.create_preset(&my_preset);
    //dump_preset(my_preset);

    app_send();
    delay(100);
    app_message_out.change_hardware_preset(0x00, 0x00);
    app_send();
    app_message_out.change_hardware_preset(0x00, 0x03);     
    app_send();
  }
*/

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
