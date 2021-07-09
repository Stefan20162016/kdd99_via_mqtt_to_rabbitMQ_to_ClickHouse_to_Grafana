
for i in *.cpp ; do g++ -I. -c $i ; done
for i in *.c   ; do gcc -I. -c $i ; done


/usr/bin/c++ -I.   -Wall -std=gnu++0x -g  -rdynamic Config.o Conversation.o ConversationFeatures.o ConversationReconstructor.o FeatureUpdaterCount.o FeatureUpdaterTime.o FiveTuple.o IcmpConversation.o IntervalKeeper.o IpDatagram.o IpFragment.o IpReassembler.o IpReassemblyBuffer.o IpReassemblyBufferHoleList.o Packet.o ReferenceCounter.o Sniffer.o StatsEngine.o StatsPerHost.o StatsPerService.o StatsPerServiceWithSrcPort.o StatsWindow.o StatsWindowCount.o StatsWindowTime.o TcpConnection.o Timestamp.o UdpConversation.o TinyMqtt.o  main.o net.o mqtt.o mqtt_pal.o  -o kdd99extractor  -lpcap -lpthread -lmaxminddb
