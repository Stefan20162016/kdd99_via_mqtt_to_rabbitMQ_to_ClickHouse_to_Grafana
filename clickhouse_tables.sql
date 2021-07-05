CREATE TABLE incomingKDD99
(
`time`  DateTime,
`srcIP` String,
`srcPort` UInt16,
`dstIP` String,
`dstPort` UInt16,
`protocol` String,
`srcbytes` UInt64,
`dstbytes` UInt64,
`count` UInt64,
`service` String
)
ENGINE = RabbitMQ SETTINGS rabbitmq_host_port = 'localhost:5672', rabbitmq_exchange_name = 'toClickHouse', rabbitmq_exchange_type = 'direct', rabbitmq_routing_key_list = 'rabbitkdd99', rabbitmq_format = 'JSONEachRow', rabbitmq_num_consumers = 1, date_time_input_format = 'best_effort';


CREATE TABLE kdd99
(
`time`  DateTime,
`srcIP` String,
`srcPort` UInt16,
`dstIP` String,
`dstPort` UInt16,
`protocol` String,
`srcbytes` UInt64,
`dstbytes` UInt64,
`count` UInt64,
`service` String
)
ENGINE = MergeTree
ORDER BY time;

CREATE MATERIALIZED VIEW kdd99_material TO kdd99
    AS SELECT * FROM incomingKDD99;
    ;
    
    
