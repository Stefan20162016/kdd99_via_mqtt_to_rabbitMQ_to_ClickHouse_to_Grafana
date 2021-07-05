
//#include <iostream>

namespace FeatureExtractor {

    class TinyMqtt{
        private:
                std::string connection_dst_host;
                std::string connection_port;
                std::string topicname;
                std::string text2publish;
        public:
            TinyMqtt(std::string x, std::string port, std::string t);
            TinyMqtt(std::string s);
            void operator()();
            void publish(std::string s);

            //void publish_callback(void** unused, struct mqtt_response_publish *published);
            static void* client_refresher(void* client);
            void exit_example(int status, int sockfd, pthread_t *client_daemon);
    };

    
}


