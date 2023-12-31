## TODO
- [X] Switch from Quart to Blacksheep and Uvicorn 
- [X] Update the MQTT architecture to use JSON encoded data. Refer to the message struct from the Rust demo 
- [X] Update control panel to use templating
- [X] Get an ESP32 Wokwi Sim demo working with the ability to read and send sensor data via MQTT
- [X] Get an OTA update system working using MQTT. Updated files will be sent via JWT over an update topic
- [X] Create a LWT MQTT topic where clients notify the server when abnormally disconnecting. This allows for the device entry to be cleared
- [ ] Add images to the existing documenation
- [ ] Integrate the OpenWeather API in the control panel
- [ ] Transfer the MicroPython code to hardware when its made available. Then add code for accurate time and power level reporting
- [ ] Update the MQTT architecture to use pre-shared certs for communication over TLS:
    - One personally signed cert for the MQTT clients
    - One personally signed cert for the MQTT server 
- [ ] Ensure that the MQTT clients without the proper cert can't publish or subscribe
- [ ] Updgrade the web sever to use https. This requires a signed cert by a publicly known and verified CA (such as Let's Encrypt)
- [ ] Get a PostgreSQL instance up and running. Ensure it is accessible by localhost ONLY
- [ ] Integrate DB data entry into the MQTT server
- [ ] Create batch processing program that exports plots and KPIs to inline HTML via plotly
- [ ] Finalize control panel and dashboard (could use a dedicated front-end framework if HTMX proves too difficult)
