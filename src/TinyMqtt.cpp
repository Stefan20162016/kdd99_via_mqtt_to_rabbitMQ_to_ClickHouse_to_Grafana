
#include <iostream>
#include <thread>
#include "TinyMqtt.h"
// mqtt
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <mqtt.h>
#include "posix_sockets.h"
//mqtt end

namespace FeatureExtractor {
    
    TinyMqtt::TinyMqtt(std::string x, std::string port, std::string t):
        connection_dst_host{x}, connection_port{port}, topicname{t}
    {}

    /*
        NEW SECTION
    */
    TinyMqtt::TinyMqtt(std::string s): text2publish(s), connection_dst_host("localhost"), connection_port("1883"), topicname("kdd99features")
    {}
    void TinyMqtt::operator()(){
        //try{
                std::cout << "in tinyMQTT: " << std::this_thread::get_id() << ":" << text2publish << ";"<<connection_dst_host<<connection_port<<topicname  << std::endl;  
                //{std::lock_guard<std::mutex> lock(coutmtx);
                // std::cout << worker_id << ": EMPTY constructor string." << std::endl;}
                //std::this_thread::sleep_for(std::chrono::milliseconds(4)); 
                this->publish(text2publish);
        //    }
        //catch(...){
        //}
    }
    
    /*
        END NEW SECTION
    */

    //void TinyMqtt::publish_callback(void** unused, struct mqtt_response_publish *published){}

    void* TinyMqtt::client_refresher(void* client){ 
        while(1) {
            mqtt_sync((struct mqtt_client*) client);
            usleep(50000U);
        }
        return NULL;

    }
    void TinyMqtt::exit_example(int status, int sockfd, pthread_t *client_daemon){
        if (sockfd != -1) close(sockfd);
        if (client_daemon != NULL) pthread_cancel(*client_daemon);
        
        //exit(status);
        if (status != 0){
            std::cout << "mqttpublish exit-status: " << status << std::endl;
        }
    }

    void TinyMqtt::publish(std::string publish_this_string){
        
        //std::cout << "in publish() with: " << publish_this_string << std::endl;

        const char* addr = connection_dst_host.c_str();
        const char* port = connection_port.c_str();
        const char* topic = topicname.c_str();

        int sockfd = open_nb_socket(addr, port);

    if (sockfd == -1) {
        perror("Failed to open socket: ");
        exit_example(EXIT_FAILURE, sockfd, NULL);
    }

    /* setup a client */

    struct mqtt_client client;

    uint8_t sendbuf[8*2048]; /* sendbuf should be large enough to hold multiple whole mqtt messages */
    uint8_t recvbuf[8*1024]; /* recvbuf should be large enough any whole mqtt message expected to be received */
    //mqtt_init(&client, sockfd, sendbuf, sizeof(sendbuf), recvbuf, sizeof(recvbuf), publish_callback);
    mqtt_init(&client, sockfd, sendbuf, sizeof(sendbuf), recvbuf, sizeof(recvbuf), NULL);
    /* Create an anonymous session */
    const char* client_id = NULL; //"668"; 
    /* Ensure we have a clean session */
    uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
    /* Send connection request to the broker. */
    mqtt_connect(&client, client_id, NULL, NULL, 0, NULL, NULL, connect_flags, 400);

    /* check that we don't have any errors */

    if (client.error != MQTT_OK) {
        fprintf(stderr, "error: %s\n", mqtt_error_str(client.error));  
        exit_example(EXIT_FAILURE, sockfd, NULL);     
    }

    /* start a thread to refresh the client (handle egress and ingree client traffic) */
    pthread_t client_daemon;

    //if(pthread_create(&client_daemon, NULL, client_refresher, &client)) {
    ////if(pthread_create(&client_daemon, NULL, NULL, &client)) {
    //    fprintf(stderr, "Failed to start client daemon.\n");
    //    exit_example(EXIT_FAILURE, sockfd, &client_daemon);
    //}

   
    
    /* get the current time */
    time_t timer;
    time(&timer);
    struct tm* tm_info = localtime(&timer);
    char timebuf[26];
    strftime(timebuf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    /* print a message */
    char application_message[256];
    snprintf(application_message, sizeof(application_message), "time: %s", timebuf);
    
    std::string mqttmessage = publish_this_string;

    //printf(" published : \"%s\"", application_message);
    /* publish the time */
    
    //mqtt_publish(&client, topic, application_message, strlen(application_message) + 1, MQTT_PUBLISH_QOS_0);
    mqtt_publish(&client, topic, mqttmessage.c_str(), strlen(mqttmessage.c_str()) + 0, MQTT_PUBLISH_QOS_0);
    //char * application_message2 = "{\"time\": \"2021-07-02 19:37:16\", \"srcIP\": \"162.125.19.130\"}";
    //mqtt_publish(&client, topic, application_message2, strlen(application_message2) + 0, MQTT_PUBLISH_QOS_0);

    //mqtt_sync((struct mqtt_client*) &client);
    __mqtt_send((struct mqtt_client*) &client);
    //usleep(100000U);

    /* check for errors */
    if (client.error != MQTT_OK) {
        fprintf(stderr, "MQTT-error: %s\n", mqtt_error_str(client.error));
    }
    

    usleep( 300000U);

    /* exit */ 
    //printf("\n disconnecting from %s\n", addr);
    exit_example(EXIT_SUCCESS, sockfd, &client_daemon);
    //exit_example(EXIT_SUCCESS, sockfd, NULL);

    
  //  std::terminate();

    }



    
}
