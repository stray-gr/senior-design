## Input
- Determine which room will be studied 
- Generate an OpenWeather API token
- Design a wireless communication architecture the embedded devices and server can use to communicate
- Create a script that tests the network architecture by:
  1. Emulating data input from the embedded devices 
  2. Collecting data from the OpenWeather API and the emulated devices
  3. Printing the collected data, which showcases the network's software implementation
- Research battery level, airflow, temperature, and humidity sensors 
- Acquire embedded devices that can read analog input and transmit data wirelessly 
- Acquire pre-made sensors, along with the material needed to make any sensors that cannot be bought pre-made 
- Create fixtures that the embedded devices and their associated sensors can reside in
- Program the embedded devices to read and transmit sensor data when prompted to by the server 

## Processing
- Create a server-side program that can prompt the embedded devices for data 
- Create a server-side test script that:
  1. Prompts the embedded devices for data
  2. Receives data from the embedded devices and the OpenWeather API
  3. Prints the collected data, which showcases the network's hardware implementation
- Build an SQL database that stores all of the collected data 
- Create a server-side data collection/conversion program that:
  1. Collects data from the embedded devices and the OpenWeather API
  2. Converts analog-to-digital data from the devices into human-readable measurements
  3. Stores the data in the SQL database via an object-relational mapper (ORM) 
      - Note: Data collected by this program during testing will be sent to a TEST table
  4. Sends the data to a control panel web app via a WebSocket 
      - Note: This action can be emulated with a log file until the control panel is implemented
- Create server-side batch-processing program that: 
  1. Processes batches of data stored in the SQL database in 24-hour increments 
  2. Stores data plots and key metrics in the file server 
- Implement a simple file server API that indexes the web server's static file directory
  - Note: The SQL database could be used to track which files are and aren't available

## Output
- Create a control panel web app that can display data in near real-time, along with any low power 
  warnings from the embedded devices (all of which are sent from the server via WebSocket)
- Add websocket communication between the data collection/conversion program and the control panel
- Create a data visualization dashboard that can retrieve processed data via the file server API 
- Conduct a short test study to ensure the components are integrated with one another as intended

## Investigation
- Using the created data acquisition system, collect data in the room to be studied for 1 week
- Aggregate any standards regarding ventilation, temperature, and humidity requirements for the type of 
  residential room being studied
- Once the data has been collected, quantify what the issues are using the aggregated standards
- Perform a root cause analysis to determine why these issues are occurring
- Research and recommend possible countermeasures. Make sure to include the feasibility of each 
  countermeasure. Feasibility can include the countermeasure's cost and installation procedure
  
## Preparation for the Senior Design Expo 
- Put together the presentation material outlined in Milestones.md 
  - Note: a majority of the material should've been created during the documentation phases
- Rehearse the presentation
