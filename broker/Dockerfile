FROM rabbitmq:4

RUN rabbitmq-plugins enable --offline rabbitmq_mqtt

COPY certs/ca.crt /certs/ca.crt
COPY certs/server.crt /certs/server.crt
COPY certs/server.key /certs/server.key
COPY rabbitmq.conf /etc/rabbitmq/rabbitmq.conf

COPY scripts/ /scripts/
RUN chmod -R +x /scripts/

CMD [ "/scripts/init.sh" ]