# Team GR IoT Data Pipeline Template - Final Report

## Table of Contents
- [Project Description](docs/project_description.md)
- [Test Plan](docs/test_plan.md)
- [User Manual](#user-manual)
- [PPT Presentation](docs/presentations/fall-design-slides.pdf)
- [Initial Self-Assesment]()
- [Final Self-Assesment]()
- [Summary of Expenses](#summary-of-expenses)
- [Appendix](#appendix)

**NOTE:** Any additional documentation can be found in the [docs](docs/) folder. This includes documenation that was required for the fall final report.

### Excluded Documentation
- The *User Interface Specification* was skipped since this project is essentially a comprehensive proof-of-concept and interation with the IoT data pipeline is done headlessly
- Since this is a solo project, the *Summary of Hours and Justification* was skipped

## Summary of Expenses
- The final project budget is approximately $75:
    1. ESP32 Dev Board x3 - $20
    2. HiLetgo DHT22 x4 - $30
    3. Elegoo Electronics Component Kit - $15
    4. Breadboard Kit - $10

## User Manual
- [Design Diagrams](docs/design_diagrams.md)

### FAQ
**What is going to be viewed to the user? Is the API going to have a search feature that then returns what the user wants to see or will they be able to see all the data?**
- First, the user sends a data query in the form of a JSON file which has fields that filter the data (e.g. filter by datetime). From there, the API returns an HDF or CSV file 
where the columns will be the database columns and the rows are the matching data entries. This is all done headlessly, meaning there isn't any direct visualization support. Lastly,
the API user can query sensor data from ANY facility. This means they could see all of the sensor data ever collected if desired.

**Will the central database and API be hosted as a cloud service?**
- This project will locally host the central database and API to save on long term cost. However, some research and discussion will be done regarding cloud deployment as an alternative. 

**Why were RabbitMQ and MQTT were chosen for the message broker?**
- MQTT is an IoT-focused protocol that makes it easy to send messages to a high volume of clients using the PUB/SUB model. With the PUB/SUB model, clients subscribe to a channel/topic 
that is managed by a message broker. From there, publishers can send messages to the message broker over a specific topic. The broker will then forward the published message to
each client subscribed to the topic on behalf of the publisher. This simplifies the development and debugging of the project's network infrastructure, as the responsibility of receiving 
and forwarding messages is now on the message broker rather than the developer. 
- The only reason RabbitMQ was chosen as the message broker was because the *Broadway* framework being used has pre-made middleware for RabbitMQ. Otherwise, the Mosquitto MQTT broker 
would've been used due to its ease of configuration.

**What benefits does this pipeline have over other pre-existing solutions?**
- The idea of this pipeline is to be more developer friendly than other solutions that place restrictions on what can be done. This developer-centric approach would allow developers to 
have an easier time configuring and extending their pipeline without having limitations forced upon them.

## Appendix

### Licensing
- This repo was licensed under the MIT license because it:
    1. Protects any related documenation
    2. Is compatible with the Rust and Python packages being used
    3. Would allow a company to freely use the data pipeline template that this repo will eventually outline
