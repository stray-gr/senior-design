# Team GR Final Capstone Assessment

### Did you apply and build upon the skills identified in your initial assessment from last Fall? 

Out the the concepts identififed in my initial assesment, the following were applied:
1. **Data Structures** - using concepts taught in this class helped me optimize how batches of messages are stored and processed using Redis queues. Furthermore, the batch-router microservice used to use C++ and in-memory storage before the switch to Go and Redis. During this intermiediate stage, I applied my knowledge of datastructures and concluded that a doubly-linked list was the most efficient way to queue batches and schedule jobs that process said batches. This is because messages and jobs would be appended to the list's tail and removed from the head in O(1) time. Additionally, there was no need for constant time access or for iterating over the queues.

2. **Database Design and Development** - using concepts taught in this class allowed me to quickly create a database using SQL that made efficient use of foreign keys and table normalization to minimize the dimensionality of each table. This reduction in dimensionality then makes it easier to process the data in a useful way, especially if this data were to be used in training a predicative classifier.

3. **DC Circuit Design** - using concepts that I learned during my internships at AFRL allowed me to easily reason about the implemenation of this project's IoT devices.  

### What did you do and how did you do it? 

As development of this project continued, I made sure to periodically re-evaluate the design decisions being made by this project. I also kept a watchful eye on alternative solutions. Lastly, I made sure to consult my project advisor for decisions I was on the fence about. Doing all of these significantly benefitted me. For example, this approach led me to adopting Go for the microservice implemenations. This is because the gRPC benchmarks for Go and C++ showed me that Go isn't too far behind in terms of performance and memory overhead. Additionally, Go makes dependency management and program compilation much simpler than C++.    

### What did you learn and what competencies did you build? 

During the development of this project, I've become more proficient with the following concepts:
1. Development using Go and Rust
2. Usage Docker and Docker Compose, especially with using the Alpine Linux Docker Image (which is very minimal)
3. API design (gRPC APIs in particular). I now know that it is possible to stream data directly from a database, to an API backend, to the client. This method uses much less memory overhead than having the API download all of the data before sending said data in one shot. 

### What were your successes, what were you obstacles?

My successes with this project include developing an integrated system of microservices that is capable of batching, storing, and retrieving atmospheric data collect from a simulated IoT device. During the development of this integrated system, I did run into difficulty trying to balance program simplicity with performance and memory overhead. This is especially true when each microservice was orginally implemented using C++. I found out the hard way that multi-threaded C++ can be a bit difficult to manage. Especially when you need to implement pooled resouce via a sempahore that needs to be manually implemented. Building each microservice and its dependencies also proved to be time-consuming in C++. 

Another success with this project was developing firmware in Rust for the ESP32 that is capable of reporting the temperature and relative humidity of a given room using a DHT22 sensor. However, this firmware was originally written using the ESP-IDF framework in C. This is because some major obstacles were initially encountered when developing the firmware using Rust. Mainly, the ESP32 Rust framework didn't support MQTT v5 at the time. This obstacle was overcome by using Redis keys to emulate the behavior of delayed device failure (LWT) messages. This work around now allows any version of MQTT to be used with the project. If a LWT message for a given device is received and is followed by a connection message from the same device within the delay interval, then the LWT message isn't sent as intended.

**NOTE:** Since this is a solo project, "*What was your individual contribution to this project?*" in Part A and all questions in Part B were skipped