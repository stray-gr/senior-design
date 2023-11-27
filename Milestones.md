## Completion of the Input Subsystem
- To reach this milestone, all of the tasks listed for the *Input Subsystem* in the project's [task list](Tasklist.md) must be completed. Additionally, the work for each task must be documented.
  - Of the tasks listed, the acquisition of materials is crucial. Without the hardware needed for this subsystem, very little of its functionality can be
    implemented and tested
- Deliverables will include:
  1. An embedded device with functioning temperature, humidity, and battery level sensors
  2. An embedded device with functioning airflow and battery level sensors
  3. Fixtures to mount each embedded device in the room
  4. Firmware running on each embedded device that can read and transmit data from its sensors when prompted to by the server
  5. A wireless communication infrastructure for the devices and server to communicate on
  6. A sever-side test script that tests collecting data from the sensors and OpenWeather API token

## Completion of the Processing Subsystem
- To reach this milestone, all of the tasks listed for the *Processing Subsystem* in the project's [task list](Tasklist.md) must be completed. Additionally, the work for each task must be documented.
- Deliverables will include:
  1. Two server-side programs (look at the [task list](Tasklist.md) for more info)
  2. An SQL database that stores collected data and indexes the web server's static file directory
  3. A test script that can emulate data input from the embedded devices

## Completion of the Output Subsystem
- To reach this milestone, all of the tasks listed for the *Processing Subsystem* in [task list](Tasklist.md) must be completed. Additionally, the work for each task must be documented.
- Deliverables will include a web server that can serve:
  1. A control panel web page that can view data in near real-time and display and warnings from the embedded devices
  2. A data visualization dashboard that can view processed batches of data
  
## Preparation for the Senior Design Expo
- To reach this milestone, documentation from each of the previous milestones must be compiled in a way that is presentable and engaging
- Deliverables should include:
  - This repo and all pertinent documentation
  - A tutorial on how to set-up and use the data pipeline template outlined by this repo, along with possible alternative solutions.
