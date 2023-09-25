## Input
- Determine which room will be studied
- Generate an OpenWeather API token
- Select an embedded device that can read analog input and transmit data wirelessly
- Research battery level, airflow, temperature, and humidity sensors
- Obtain pre-made sensors, along with the material needed to make any sensors that cannot be
  bought pre-made
- Program the embedded devices to read and transmit sensor data when prompted to by the server
- Design and implement a wireless communication architecture the embedded devices and server can 
  use to communicate
- Create a server-side test program that:
  1. Prompts the embedded devices for data
  2. Receives data from the embedded devices and the OpenWeather API
  3. Prints the collected data, which shows that the wireless communication is properly configured
- Create fixtures that the embedded devices and their associated sensors can reside in

## Processing
- Build an SQL database that store all of the collected data
- Implement a simple file server that can serve static files (such as plots and JSON files)
  - Note: The SQL database could be used to track which files are and aren't available
- Create a server-side program that can:
  1. Prompt the embedded devices for data
  2. Collect data from the embedded devices and the OpenWeather API
  3. Convert analog-to-digital data from the devices into human-readable measurements
  4. Store the data in the SQL database via an object-relational mapper (ORM)
  5. Send the data to a control panel web app via a WebSocket
- Create another server-side program that:
  1. Processes batches of data stored in the SQL database in 24-hour increments
  2. Stores data plots and key metrics in the file server 

## Output
- Create a control panel web app that can display data in real time, along with any low power 
  warnings from the embedded devices (all of which are sent from the server via WebSocket)
- Create a simple data visualization dashboard that can display data plots and key metrics stored 
  in the file server
