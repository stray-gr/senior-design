#!/bin/sh

# Ensure that PID file will be rabbit@hostname.pid
echo 'NODENAME=rabbit@test-broker' > /etc/rabbitmq/rabbitmq-env.conf

{
    rabbitmqctl wait "/var/lib/rabbitmq/mnesia/rabbit@test-broker.pid" --timeout 5;
    /users.sh;
    /perms.sh;
    /queues.sh;
} & rabbitmq-server
