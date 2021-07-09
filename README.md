# The kdd99_via_mqtt_to_rabbitMQ_to_ClickHouse_to_Grafana Project:

## main purpose is to use kdd99 features in Grafana-Dashboards
## the features themselves and the Destination IPs on the worldmap plugin of Grafana
## TODO: use stored features in ClickHouse to convert to parquet for VAE or GAN anomaly detection

![Worldmap](worldmap/worldmap.png)

- TL;DR: kdd99 via mqtt to rabbitMQ to ClickHouse to Grafana Dashboard :)

![workflow](arrowsapp2.png)


- go to src -> run ./COMPILE.sh
- install/setup ClickHouse
- install/setup RabbitMQ
- install Grafana and install ClickHouse plugin, see grafana_dashboard.json for queries
- (maybe change RabbitMQ/MQTT broker connection string and topic in TinyMqtt.cpp)
- run ./kdd99extractor 

see [Documentation](Documentation.pdf) for Details, like ClickHouse table creation

![Grafana Dashbaord 1hour](grafana_last_hour.png)
![Grafana Dashbaord 1hour](grafana_3hours.png)
![WorldmapDASH](worldmap/worldmap_dashboard.png)

- for worldmap install (apt install libmaxminddb-dev)
