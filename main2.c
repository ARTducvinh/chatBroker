#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "common/mqtt_client.h"

#define CLIENT_ID    "client2"
#define PUB_TOPIC    "test/topic2"
#define SUB_TOPIC    "test/topic1"

MQTTClient client;
pthread_mutex_t mqtt_mutex;

void *mqtt_receive_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mqtt_mutex);
        message_t message;
        if (subscribe_message(client, SUB_TOPIC, &message) == 0) {
            printf("[Client2] Received: %s\n", message.data.data1.message);
        }
        pthread_mutex_unlock(&mqtt_mutex);
        sleep(1);
    }
    return NULL;
}

void *mqtt_publish_thread(void *arg) {
    int count = 0;
    while (1) {
        pthread_mutex_lock(&mqtt_mutex);
        message_t message;
        snprintf((char *)message.data.data1.message, sizeof(message.data.data1.message), "Client2 says Hi %d", count++);
        publish_message(client, CLIENT_ID, PUB_TOPIC, &message);
        printf("[Client2] Sent: %s\n", message.data.data1.message);
        pthread_mutex_unlock(&mqtt_mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t recv_thread, pub_thread;

    if (init_mqtt_client(&client, CLIENT_ID, PUB_TOPIC) != 0) {
        printf("Failed to initialize MQTT client.\n");
        return -1;
    }

    pthread_mutex_init(&mqtt_mutex, NULL);
    pthread_create(&recv_thread, NULL, mqtt_receive_thread, NULL);
    pthread_create(&pub_thread, NULL, mqtt_publish_thread, NULL);

    pthread_join(recv_thread, NULL);
    pthread_join(pub_thread, NULL);

    pthread_mutex_destroy(&mqtt_mutex);
    disconnect_from_broker(client);
    return 0;
}
