## Input
- Generate an OpenWeather API token
- ~~Design a wireless communication architecture the embedded devices and server can use to communicate~~
- Create a development environment that can test the network architecture by:
  1. ~~Emulating data input from the embedded devices~~
  2. ~~Collecting data from the the emulated devices~~
  3. Collecting data from the OpenWeather API and the emulated devices
- Research battery level, airflow, and ~~temperature + humidity~~ sensors 
- Acquire embedded devices that can read analog input and transmit data wirelessly 
- Acquire pre-made sensors, along with the material needed to make any sensors that cannot be bought pre-made 
- Create fixtures that the embedded devices and their associated sensors can reside in
- Program the embedded devices to read and transmit sensor data when prompted to by the server 

## Processing
- Instantiate an SQL database that stores:
  - Raw data that hasn't been processed yet
  - The file paths of all processed data batches. Note that these batches will be stored within the er  batches tatic file or template directory
- Create a server-side data collection/conversion program that:
  1. ~~Prompts the embedded devices for data~~
  2. Collects data from the ~~embedded devices and the~~ OpenWeather API
  3. ~~Displays the collected data, which showcases the network's hardware implementation~~
  4. Converts any analog-to-digital data from the devices into human-readable measurements
  3. Stores the data in the SQL database via an object-relational mapper (ORM) 
      - Note: Data collected by this program during testing will be sent to a TEST table
- Create server-side batch-processing program that: 
  1. Processes batches of data stored in the SQL database in 24-hour increments 
  2. Stores the processed data plots and KPIs in the web server's file system as an html or template file
  3. Adds the file path of the processed batch into the SQL database

## Output
- Create a web server that can serve:
  1. ~~A control panel web page that can display data in near real-time, along with any low power warnings from the embedded devices (all of which are sent from the server via MQTT)~~
  2. A data visualization dashboard that can retrieve html files or templates containing processed data 
- Conduct a short test study to ensure the components are integrated with one another as intended
- Refine the UI using Boostrap CSS

## Preparation for the Senior Design Expo 
- Put together the presentation material outlined in the project's [Milestones](Milestones.md)
  - Note: a majority of the material should've been created during the documentation phases
