# Team GR IoT Data Pipeline Template - Final Report

## Table of Contents
- [Project Description](docs/project-description.md)
- [Test Plan](docs/test-plan.md)
- [User Manual](#user-manual)
- [Final Presentation Slides](docs/presentations/final-presentation.pdf)
- [Initial Capstone Assesment](docs/essays/capstone-assessment-gr.pdf)
- [Final Capstone Assesment](docs/essays/final-capstone-assessment.md)
- [Summary of Expenses](#summary-of-expenses)
- [Appendix](#appendix)

**NOTE:** Any additional documentation can be found in the [docs](docs/) folder. This includes documenation that was required for the fall final report.

### Excluded Documentation
- The *User Interface Specification* was skipped since this project is essentially a comprehensive proof-of-concept and interation with the IoT data pipeline is done headlessly
- Since this is a solo project, the *Summary of Hours and Justification* was skipped
- Due to time constraints, the *Expo Poster* was unfortunately skipped as well

## Summary of Expenses
- The final project budget is approximately $75:
    1. ESP32 Dev Board x3 - $20
    2. HiLetgo DHT22 x4 - $30
    3. Elegoo Electronics Component Kit - $15
    4. Breadboard Kit - $10

## User Manual
This IoT Data Pipeline Template is an example project that demonstrates how such a pipeline could be developed using the microservice architectual pattern. For the demonstation purposes of this project, the showcased data pipeline collects and aggregates temperature and relative humidity data from ESP32s utilizing the DHT22 sensor. Note that this project assumes basic knowledge of the following concepts:
1. **An object-oriented programming language** - the Go and Python code used by this project uses a blend of object-oriented and procedural programming 
2. **A systems level language** - knowing how languages such as C and C++ manually manage memory and spawn threads should help with understanding some of the ideology behing Rust's memory and concurrency safety 
3. **A functional programming language** - knowing how languages such as OCaml and Haskell utilize the *result* and *option/maybe* monads should help with understanding how Rust uses its *result* and *option* type to enforce explicit error checking
4. **Docker and Docker Compose** - Docker is extensively used to run each service in a reproducible environment. Additionally, this project's integration test is orchestrated via Docker Compose
5. **Protobuf** - used by each component to standardize communication format

Before using and expanding the components of this project, make to get a good understanding of how each component interfaces with one another. This can be done by studing this project's [design diagrams](docs/design-diagrams.md). Then, make sure to view the following README's for each component:
- [Microservices](microservice.md)
- [Firmware](firmware/README.md)
- [Postgresql Database](database/README.md)
- [Mosquitto MQTT Broker](broker/README.md)
- [gRPC API Example Client](api/client/README.md)

### FAQ
**What is going to be viewed to the user? Is the API going to have a search feature that then returns what the user wants to see or will they be able to see all the data?**
- Currently, there is a gRPC API that returns all of the collected sensor data stored in the project's database. Since this API is used headlessly, there isn't any direct visualization support for the data aggregated by the API. This is intentional, since this project follows a microservice approach. This means that each component performs a small set of well tasks and has a standardized interface over which any interaction occurs. Therefore, a REST API could make usage of the gRPC API to aggregate and display the data via a rendered template (e.g. a Jinja template) or a server-side rendered JavaScript app (e.g. a Next.js app).

**Will the central database and API be hosted as a cloud service?**
- The original objective of this project was to demonstrate deployment to physically owned hardware and the cloud. That is the main reason why the project took on a microservice approach. Note that such an approach typically doesn't make any assumption on where each service is deployed and tends to offer first-class support for encrypted communication between services as a result.

**Why were Mosquitto and MQTT were chosen for the message broker?**
- MQTT is an IoT-focused protocol that makes it easy to send messages to a high volume of clients using the PUB/SUB model. With the PUB/SUB model, clients subscribe to a channel/topic that is managed by a message broker. From there, publishers can send messages to the message broker over a specific topic. The broker will then forward the published message to each client subscribed to the topic on behalf of the publisher. This simplifies the development and debugging of the project's network infrastructure, as the responsibility of receiving and forwarding messages is now on the message broker rather than the developer. 
- The Mosquitto MQTT broker was chosen because of its ease of configuration and its ability to enfore access control. This is in contrast to more complicated offerings, such as RabbitMQ. During testing, RabbitMQ was found to have insufficient access control over MQTT PUB/SUB channels. This makes sense, since MQTT is typically used by RabbitMQ projects to convert the many-to-many protocol of MQTT to the many-to-one protocol of AMQP. This means that access control is typically enforced on the AMQP queue rather than the MQTT channel.

**What benefits does this pipeline have over other pre-existing solutions?**
- The idea of this pipeline is to be more developer friendly than other solutions that place restrictions on what can be done. This developer-centric approach would allow developers to have an easier time configuring and extending their pipeline without having limitations forced upon them. Developing the pipeline from scratch using microservices should also help cut cloud deployment costs. This is because most pre-built data pipeline services offered in the cloud charge extra due to the convenience they offer.

## Appendix

### Project Conclusion
Since this project hasn't been deployed and testing in a simulated production environment, the result of this project is unfortunately inconclusive. However, the capability that his been demonstrated by this project is promising. All that would need for this project to be conculsive AND successful would be implementing the items listed in the [next steps](#next-steps).

### Next Steps
If more development towards this project were to occur, the following would be explored and expanded upon:
1. **Deployment to physically owned hardware** - this would include details on how to properly configure the firewalls for each machine required to run given a microservice, MQTT broker, Redis Cache, and Postgresql Database 
2. **Deployment to the cloud** - this would include an investigation on different cloud platforms and a guide on how to deploy this project to the cloud platform selected as optimal during the investigation. From personal experience, Google Cloud Platform would've likely been selected. This is due to their rather inclusive free tiers for Google App Engine (a *platform as a service* offering with a Go app template) and Google Compute Enginer (an *infrastructure as a service* offering)
3. **Testing software using automated unit testing and formal methods** - due to time constraints, any unit tests were done manually. With more time, some of these unit tests would've been upgraded to automated unit tests using some form of unit testing framework. Additionally, there are tools such as Dafny and Galois SAW that could be used to formally verify some of the programs written in Go and Rust respectively. At the very least, an investigation would've been done into these formal verification tools with suggestions on how they could be employed

### Quick Note on Licensing
- This repo was licensed under the MIT license because it:
    1. Protects any related documenation
    2. Is compatible with the Go, Rust, and Python packages being used
    3. Would allow anyone to freely adapt and extend the data pipeline components developed by this project
