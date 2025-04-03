#ifndef MQTT_PROGRAM_H
#define MQTT_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include "data_format.h"

#define ADDRESS     "tcp://localhost:1883" 
#define QOS         1
#define TIMEOUT     10000L 

int init_mqtt_client(MQTTClient *client, const char* client_id, const char* topic);
void publish_message(MQTTClient client, const char* client_id, const char* topic, message_t* message);
void disconnect_from_broker(MQTTClient client);
#endif