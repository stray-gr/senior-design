#!/bin/bash
rabbitmqadmin declare queue name=data durable=true
rabbitmqadmin declare binding source="amq.topic" destination_type="queue" destination="data" routing_key="#"

rabbitmqadmin declare queue name=lwt durable=true
rabbitmqadmin declare binding source="amq.topic" destination_type="queue" destination="lwt" routing_key="#"