FROM eclipse-mosquitto:2.0.18-openssl

COPY certs/          /mosquitto/config/
COPY creds/acl_file  /mosquitto/config/creds/acl_file
COPY creds/plain.txt /mosquitto/config/creds/users.txt
COPY entrypoint.sh   /entrypoint.sh
COPY mosquitto.conf  /mosquitto/config/

EXPOSE 8885

# https://serverfault.com/q/1095845
ENTRYPOINT ["sh", "/entrypoint.sh"]
CMD ["/usr/sbin/mosquitto", "-c", "/mosquitto/config/mosquitto.conf"]