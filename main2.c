#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
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
=======
#include <unistd.h>
#include <pthread.h>
#include "common/mqtt_client.h"

#define PUB_TOPIC    "test/topic2"
#define SUB_TOPIC    "test/topic1"

char user_id[20]; // Biến toàn cục để lưu user ID

void* mqtt_receive_thread(void* arg);

void run_chat_application(MQTTClient client) {
    pthread_t receive_thread;

    if (pthread_create(&receive_thread, NULL, mqtt_receive_thread, &client) != 0) {
        printf("Failed to create receive thread.\n");
        disconnect_from_broker(client);
        return;
    }

    message_t message;
    char input[50];
    while (1) {
        printf("Enter message to send (or 'exit' to quit): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        snprintf((char *)message.data1.name, sizeof(message.data1.name), "%s", user_id);
        snprintf((char *)message.data1.message, sizeof(message.data1.message), "%s", input);
        publish_message(client, user_id, PUB_TOPIC, (message_t*)&message);
        printf("[You] Sent: %s\n", message.data1.message);
    }

    pthread_cancel(receive_thread);
    pthread_join(receive_thread, NULL);

    disconnect_from_broker(client);
}

void* mqtt_receive_thread(void* arg) {
    while (1) {
        sleep(10);
>>>>>>> d047c2e (Cập nhật MQTT client và thêm main2.c)
    }
    return NULL;
}

int main() {
<<<<<<< HEAD
    pthread_t recv_thread, pub_thread;

    if (init_mqtt_client(&client, CLIENT_ID, PUB_TOPIC) != 0) {
=======
    MQTTClient client;

    printf("Enter your user ID: ");
    if (fgets(user_id, sizeof(user_id), stdin) == NULL) {
        printf("Failed to read user ID.\n");
        return -1;
    }

    user_id[strcspn(user_id, "\n")] = '\0'; 
    if (strlen(user_id) == 0) {
        printf("User ID cannot be empty.\n");
        return -1;
    }

    if (init_mqtt_client(&client, user_id, SUB_TOPIC) != 0) {
>>>>>>> d047c2e (Cập nhật MQTT client và thêm main2.c)
        printf("Failed to initialize MQTT client.\n");
        return -1;
    }

<<<<<<< HEAD
    pthread_mutex_init(&mqtt_mutex, NULL);
    pthread_create(&recv_thread, NULL, mqtt_receive_thread, NULL);
    pthread_create(&pub_thread, NULL, mqtt_publish_thread, NULL);

    pthread_join(recv_thread, NULL);
    pthread_join(pub_thread, NULL);

    pthread_mutex_destroy(&mqtt_mutex);
    disconnect_from_broker(client);
    return 0;
}
=======
    run_chat_application(client);

    return 0;
}
>>>>>>> d047c2e (Cập nhật MQTT client và thêm main2.c)
