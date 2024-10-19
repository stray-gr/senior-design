#!/bin/bash

# Ensure that PID file will be rabbit@hostname.pid
echo 'NODENAME=rabbit@test-broker' > /etc/rabbitmq/rabbitmq-env.conf
pid_file="/var/lib/rabbitmq/mnesia/rabbit@test-broker.pid" 

# Start broker
{
    rabbitmqctl wait $pid_file --timeout 5;
    /users.sh >/dev/null 2>&1;
    /perms.sh >/dev/null 2>&1;
    /queues.sh >/dev/null 2>&1;
} & rabbitmq-server
