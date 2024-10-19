FROM rabbitmq:4-management

RUN rabbitmq-plugins enable --offline rabbitmq_mqtt

ADD scripts/users.sh /users.sh
ADD scripts/perms.sh /perms.sh
ADD scripts/queues.sh /queues.sh
ADD scripts/init.sh /init.sh

RUN chmod +x /users.sh
RUN chmod +x /perms.sh
RUN chmod +x /queues.sh
RUN chmod +x /init.sh

CMD [ "/init.sh" ]