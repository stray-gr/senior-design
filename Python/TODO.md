## TODO
- [X] Switch from Quart to Blacksheep and Uvicorn 
- [X] Update the MQTT architecture to use JSON encoded data. Refer to the message struct from the Rust demo 
- [X] Update control panel to use templating
- [ ] Get an ESP32 Wokwi Sim demo working with the ability to read and send sensor data via MQTT
- [ ] Get an OTA update system working using an update MQTT topic. Updated files will be gzipped and sent via JWT

- [ ] Transfer the MicroPython code to hardware when its made available.
- [ ] Create a domain name for the server (web server and MQTT broker). This will help when getting the server's cert signed by a valid CA
- [ ] Update the MQTT architecture to use pre-shared certs for communication over TLS and HTTPS:
    - One personally signed cert for the MQTT clients
    - One personally signed cert for the MQTT server 
    - One signed cert by a publicly known and verified CA (such as Let's Encrypt) for the web server to use
- [ ] Ensure that the MQTT clients without the proper cert can't publish or subscribe
- [ ] Get a PostgreSQL instance up and running. Ensure it is accessible by localhost ONLY (no domain name needed)
- [ ] Integrate DB data entry into the MQTT server
- [ ] Create batch processing program that exports plots and KPIs to inline HTML via plotly
- [ ] Finalize control panel and dashboard (could use a dedicated front-end framework if HTMX proves too difficult)