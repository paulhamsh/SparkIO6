# SparkIO6 - updated Spark BLE classes for ESP32

## Revised SparkIO for GO, MINI and LIVE compatibility

Includes new LIVE-only messages and updated Protocol description document.   

## Key changes

The Spark GO and MINI proved less reliable in BLE communications with the ESP32 especially when retrieving a preset.   
This caused issues for SparkMINI and SparkBox.   

The previous library used a streaming approach, removing and decoding the Spark format as the data was streamed.   
This caused issues when data was incomplete.   

The new library will read and process packets.   


