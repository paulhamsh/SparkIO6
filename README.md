# SparkIO5
## Updated Spark BLE classes for ESP32

## Revised SparkIO for GO and MINI compatibility

## Key changes

The Spark GO and MINI proved less reliable in BLE communications with the ESP32 especially when retrieving a preset.   
This caused issues for SparkMINI and SparkBox.   

The previous library used a streaming approach, removing and decoding the Spark format as the data was streamed.   
This caused issues when data was incomplete.   

The new library will read and process packets.   


## Packet determination
The Spark amps cuts packets up into chunks with specific maximum lengths. For Spark 40 this is 106 bytes, and for the GO and MINI, this is 90 bytes cut further into 4 chunks of 20 and a chunk of 10.    
This means a full packet will comprise multipes of these chunk sizes, with a possible final smaller chunk.   
The packet will always end in a byte of 0xf7 (see the specification here https://github.com/paulhamsh/Spark/blob/main/Spark%20Protocol%20Description%20v3.2.pdf).   

A packet with this shorter final chunk is easy to detect because it will have a length which is not 10, 20 or 106.   
But if the final chunk is exactly one of these sizes (for example, the GO hardware preset change message) then it cannot be idenfitied as different from an intermediate chunk in the message that just happens to end in 0xf7. 

The approach taken here is to incorporate timeouts.   
If a message times out (takes more than a determined time to reach a shorter final chunk), then it is checked to see if the last byte was 0xf7.   
If so, then it is assumed to be a full message.   
If not, the message is assumed to be missing a final chunk (or more) and is dropped.

There is a risk that the final chunk received meets the above criteria when it is, in fact, just the last chunk before some that are missing. This seems low risk, and the next stage of decoding will have to check for this.   
There seems no fully robust manner to find the final chunk.   

Pseudo-code for this is shown below - for the BLE callback and a function to check whether a packet has been received.   

```
#define BUF_SIZE 5000
bool got_packet = false;

byte buffer[BUF_SIZE];
int buffer_index = 0;

notify_callback(chunk_data, chunk_length) {
  last_callback_time = mills();
  // copy bytes to the buffer and update buffer_index
  for (int i = 0; i < packet_length; i++)
    buffer[buffer_index++] = packet_data[i];
  final_byte = buffer[buffer_index - 1]; // get the last byte from this chunk 
  if (chunk_length != 10 && chunk_length != 20 && chunk_length != 106 && final_byte == 0xf7)
    got_packet = true;
}
```

```
#define CALLBACK_TIMEOUT 200

bool check_received() {
  if (got_packet) return true;  // we got a packet
  if (millis() - last_callback_time > CALLBACK_TIMEOUT) {
    final_byte = buffer[buffer_index-1];
    if (final_byte == 0xf7) return true;  // timeout with a final byte of 0f7 so very likely a packet
    // otherwise clear buffer, definitely failed to get a packet within time
    buffer_index = 0;
    return false;
  }
}
```

## Interesting things for GO and MINI

The long request for a preset for the Spark 40 is as below

```
0x01, 0xFE, 0x00, 0x00 ,0x53, 0xFE, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xF0, 0x01, 0x09, 0x01, 0x02, 0x01,
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00,
0xF7
```

This has a block header, then a chunk header, then the data, then many 0x00s, then a trailing 0xf7.

Interestingly, for the GO and MINI, the block header is not required, so this works.   
```
0xF0, 0x01, 0x09, 0x01, 0x02, 0x01,
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00,
0xF7
```

Even more interestingly, all the 0x00s are not required either, so this much more compact form works.   
```
0xF0, 0x01, 0x09, 0x01, 0x02, 0x01,
0x00, 0x00, 0x01,
0xF7
```
