#!/bin/bash
rabbitmqadmin declare permission vhost="/" user=dev1 configure="^mqtt-sub.*$" write="^mqtt-sub.*$" read=".*"
rabbitmqadmin declare permission vhost="/" user=dev2 configure="^mqtt-sub.*$" write=".*" read="^mqtt-sub.*$"