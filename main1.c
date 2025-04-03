#include "common/mqtt_client.h"

#define CLIENT_ID    "client1"
#define TOPIC        "test/topic"

int main() {
    MQTTClient client;

    // Khởi tạo MQTT client và subscribe vào topic
    if (init_mqtt_client(&client, CLIENT_ID, TOPIC) != 0) {
        printf("Failed to initialize MQTT client.\n");
        return -1;
    }

    // Tạo một message_t để gửi
    message_t message;
    message.user_id = 1;  // Ví dụ user_id
    snprintf((char *)message.data.data1.message, sizeof(message.data.data1.message), "Hello from MQTT Client");

    // Gửi tin nhắn đến broker
    publish_message(client, CLIENT_ID, TOPIC, &message);

    // Ngắt kết nối
    disconnect_from_broker(client);

    return 0;
}