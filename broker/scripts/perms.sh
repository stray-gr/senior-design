#!/bin/bash
rabbitmqctl set_permissions -p / dev1 "^mqtt-sub.*$" "^mqtt-sub.*$" ".*"
rabbitmqctl set_permissions -p / dev2 "^mqtt-sub.*$" ".*" "^mqtt-sub.*$" 
