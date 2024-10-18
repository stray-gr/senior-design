#!/bin/sh

# Create queues and users
# rabbitmqctl add_user "dev1" "PASSword"
# rabbitmqctl add_user "dev2" "passWORD"

# Ensure the nodename doesn't change, e.g. if docker restarts.
# Important because rabbitmq stores data per node name (or 'IP')
# echo 'NODENAME=rabbit@test-broker' > /etc/rabbitmq/rabbitmq-env.conf

# Create Rabbitmq user
(rabbitmqctl wait --timeout 60 /var/lib/rabbitmq/mnesia/rabbitmq ; \
rabbitmqctl add_user "dev1" "PASSword" 2>/dev/null ; \
rabbitmqctl set_user_tags "dev1" administrator ; \
rabbitmqctl set_permissions -p / "dev1"  ".*" ".*" ".*" ; \
echo "*** Log in the WebUI at port 15672 (example: http:/localhost:15672) ***") &&

# $@ is used to pass arguments to the rabbitmq-server command.
# For example if you use it like this: docker run -d rabbitmq arg1 arg2,
# it will be as you run in the container rabbitmq-server arg1 arg2
rabbitmq-server $@
