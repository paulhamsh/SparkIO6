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


unsigned int cmd_sub;
SparkMessage message;
SparkPreset pre;
int p = 0;
float v=60.0;


void loop() {
  int len;
  int trim_len;
  bool got;

  Serial.println("Try for serial number");
    // Get serial number
  spark_msg_out.get_serial();
  spark_send();
  got = wait_for_spark(0x0323);
  if (got) DEBUG("Got serial number");
  else DEBUG("Failed to get serial number");

  delay(1000);
/*
  // pre-wait before starting to request presets
  if (millis() - t > 10000 && !do_it) {
    do_it = true;
    t = millis();
  };


  if (update_spark_state()) {
    t = millis();
    //Serial.println(cmdsub, HEX);
  };
*/

/*
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
*/

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

//    t = millis();
    
//  };


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
