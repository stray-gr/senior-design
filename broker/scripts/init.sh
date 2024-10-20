#!/bin/bash

# Ensure that PID file will be rabbit@hostname.pid
echo 'NODENAME=rabbit@localhost' > /etc/rabbitmq/rabbitmq-env.conf
pid_file="/var/lib/rabbitmq/mnesia/rabbit@localhost.pid" 

# Start broker
{
    rabbitmqctl wait $pid_file --timeout 5;
    /scripts/users.sh >/dev/null 2>&1;
    /scripts/perms.sh >/dev/null 2>&1;
} & rabbitmq-server
