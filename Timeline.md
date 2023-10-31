## Input
| Task | Projected Due Date |
| ---- | ------------------ |
| Generate an OpenWeather API token | Nov. 6 |
| Design a wireless communication architecture the embedded devices and server can use to communicate | Nov. 6 |
| Create a series of script that test the network architecture as described in Tasklist.md | Nov. 13 |
| Research battery level, airflow, temperature, and humidity sensors | Nov 20. |
| Acquire embedded devices that can read analog input and transmit data wirelessly | Nov. 27 |
| Acquire pre-made sensors, along with the material needed to make any sensors that cannot be bought pre-made | Nov. 27 |
| Create fixtures that the embedded devices and their associated sensors can reside in | Dec. 4 |
| Program the embedded devices to read and transmit sensor data when prompted to by the server | Jan. 8 |

### Completion of the Input Subsystem (Jan. 12)
- Once the test script has been used and any remaining bugs have been found, the remaining time will be used to revise the documentation

## Processing
| Task | Projected Due Date |
| ---- | ------------------ |
| Create a server-side program as described in Tasklist.md | Jan. 15 |
| Build an SQL database that stores all of the collected data | Jan. 22 |
| Create a server-side data collection/conversion program as described in Tasklist.md | Jan. 29 |
| Create server-side batch-processing program as described in Tasklist.md | Feb. 5 |
| Implement a simple file server API that indexes the web server's static file directory | Feb. 12 |

### Completion of the Processing Subsystem (Feb. 16)
- Documentation for the processing subsystem will be revised once the processing subsystem can do the following:
  1. Store near real-time data in a log file (which simulates the control panel)
  2. Process and store batches of data
  3. Serve the processed data (JSON, plots, etc.)

## Output
| Task | Projected Due Date |
| ---- | ------------------ |
| Create a control panel web app as described in Tasklist.md | Feb. 23 |
| Add websocket communication between the data collection/conversion program and the control panel | Mar. 1 |
| Create a data visualization dashboard that can retrieve processed data via the file server API   | Mar. 8 |
| Conduct a short test study to ensure the components are integrated with one another as intended  | Mar. 11 |

### Completion of the Output Subsystem (Mar. 15)
- Provided no bugs were found during the short test study, the remaining time will be used to revise the documentation

## Investigation
| Task | Projected Due Date |
| ---- | ------------------ |
| Using the created data acquisition system, collect data in the room to be studied for 1 week | Mar. 16 - Mar. 23 |
| Aggregate any standards regarding ventilation, temperature, and humidity requirements for the type of residential room being studied | Mar. 23 |
| Once the data has been collected, quantify what the issues are using the aggregated standards | Mar. 23 |
| Perform a root cause analysis to determine why these issues are occurring | Mar. 24 |
| Research and recommend possible countermeasures as described in Tasklist.md | Mar. 29 |
  
## Preparation for the Senior Design Expo 
1. The presentation material (outlined in Milestones.md) will be finished **at most two days before the expo**. 
   - Note: a majority of the material should've been created during the documentation phases
2. The remaining time will be used to rehearse the presentation
