#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <MQTTClient.h>
#include "data_format.h"

#define ADDRESS     "tcp://localhost:1883" 
#define QOS         1
#define TIMEOUT     10000L


int message_arrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
static int subscribe_to_topic(MQTTClient client, const char* topic);


static int connect_to_broker(MQTTClient client, MQTTClient_connectOptions* conn_opts) {

    if (MQTTClient_connect(client, conn_opts) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to broker!\n");
        return -1;
    }
    return 0;
}

<<<<<<< HEAD
c
=======
>>>>>>> d047c2e (Cập nhật MQTT client và thêm main2.c)
int init_mqtt_client(MQTTClient *client, const char* client_id, const char* topic) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    if (MQTTClient_create(client, ADDRESS, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL) != MQTTCLIENT_SUCCESS) {
        printf("Failed to create MQTT client!\n");
        return -1;
    }

    MQTTClient_setCallbacks(*client, NULL, NULL, message_arrived, NULL);

    if (connect_to_broker(*client, &conn_opts) != 0) {
        printf("Failed to connect to broker!\n");
        MQTTClient_destroy(client);
        return -1;
    }

    if (subscribe_to_topic(*client, topic) != 0) {
        printf("Failed to subscribe to topic %s\n", topic);
        MQTTClient_disconnect(*client, TIMEOUT);
        MQTTClient_destroy(client);
        return -1;
    }
    return 0;
}

static int subscribe_to_topic(MQTTClient client, const char* topic) {
    int rc = MQTTClient_subscribe(client, topic, QOS);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe to topic %s!\n", topic);
        return -1;
    }
    return 0;
}

void publish_message(MQTTClient client, const char* client_id, const char* topic, message_t* message) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    pubmsg.payload = (void*)message;
    pubmsg.payloadlen = sizeof(message_t);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    int rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Failed to publish message! Error code: %d\n", rc);
        return;
    }

    MQTTClient_waitForCompletion(client, token, TIMEOUT);
}

void disconnect_from_broker(MQTTClient client) {
    if (client != NULL) {
        printf("Disconnecting from broker...\n");
        MQTTClient_disconnect(client, TIMEOUT);
        MQTTClient_destroy(&client);
        printf("Disconnected from broker\n");
    }
}

int message_arrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("📩 Message received on topic: %s\n", topicName);

    if (message->payloadlen != sizeof(message_t)) {
        printf("Invalid message size received!\n");
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 0;
    }

    message_t msg;
    memcpy(&msg, message->payload, sizeof(message_t));

<<<<<<< HEAD
    printf("User ID: %d\n", msg.user_id);
    printf("Message: %s\n", msg.data.data1.message);
=======
    printf("User ID: %s\n", msg.data1.name);
    printf("Message: %s\n", msg.data1.message);
>>>>>>> d047c2e (Cập nhật MQTT client và thêm main2.c)

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);

    return 1;
}
