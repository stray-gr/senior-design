# Contents
1. [Development Environment Set-up](#development-environment-set-up)
    - [Prerequisites](#set-up-prerequisites)
    - [Installing an Existing Development Environment](#installing-an-existing-development-environment)
    - [Creating a New Development Environment](#creating-a-new-development-environment)
2. [Repo Workflow](#repo-workflow)
    - [Prerequisites](#workflow-prerequisites)
    - [MQTT](#mqtt)
    - [Wokwi Sim](#wokwi-sim)
    - [Web Server](#web-server)
3. [Useful Resources](#useful-resources)
4. [Related Articles](#related-articles)

# Development Environment Set-up
## Set-up Prerequisites
- Must have miniconda installed. For intructions on how to install miniconda, refer to: https://docs.conda.io/projects/miniconda/en/latest/
- Must have VS Code installed with the following extensions:
    1. Better Jinja
    2. Even Better TOML
    3. IntelliCode
    4. Python
    5. Wokwi Simulator (which requires additional set-up)
- For Wokwi Simulator set-up, refer to: https://docs.wokwi.com/vscode/getting-started
- Since development was done on OpenSUSE Tumbleweed for WSL, it is encouraged that you use a unix-like operating system.

## Installing an Existing Development Environment
To install the development environment used by this repo, open the Python folder in a terminal and run the following commands:
1. `conda env create --file environment.yml`
2. `conda activate sd`
3. `micropy`

## Creating a New Development Environment
1. Open a new terminal (CTRL+SHIFT+`)
2. To create a conda environment, which will contain our project's dependencies, run: `conda create -n <your-project-name> python=3.11`. This will create a development environment using conda.
3. Next, activate the newly created conda environment with: `conda activate <your-project-name>`. Then, install the Python packages that your project will use via: `pip install <package name 1, package name 2, ..., package name n>`. 
    - In the context of this repo, run: `pip install aiomqtt blacksheep blacksheep-cli micropy-cli PyJWT pyserial uvicorn[standard] websockets`
4. Using the blacksheep-cli tool, run `blacksheep create`. Then follow the steps below:
    - When prompted for a *Project name*, enter the name of the project's folder. Then hit *ENTER* to proceed
    - When prompted for a *Project template*, select **mvc** and hit *ENTER*
    - When asked if you would like to *Use OpenAPI Documentation? (Y/n)*, enter *n* for no
    - When prompted for *Library to read settings*, select **essentials-configuration** and hit *ENTER*
    - When prompted for the *App settings format*, select **TOML** and hit *ENTER*
5. cd into the project folder created by the blacksheep-cli
6. To install the development dependencies for your project's selected board, first run: `micropy stubs search <board name>`. Then look for the stubs needed for your board in the output. **Note:** The name of your board's subs should be `micropython-<board name>-stubs`  
    - In the context of this project, which uses an ESP32, run: `micropy stubs search esp32`
7. Once you have determined the name of your board's stubs, install them using: `micropy stubs add <stubs name>`. 
    - For example: `micropy stubs add micropython-esp32-stubs`
8. To initialize linting for MicroPython, make sure you are in the project folder created by the blacksheep-cli in step 4. Then run: `micropy init`.
    - When prompted for the *Project Name*, hit *ENTER*. **WARNING:** Do NOT enter a project name here. The micropy cli will default to the project folder's name
    - When asked to *Choose any Templates to Generate*, select *all* options *except* the Pymakr configuration. This can be done by pressing *a*, and then pressing *SPACE* with Pymakr selected. Hit *ENTER* to proceed 
    - When asked *Which stubs would you like to use*, select the stlib stubs and the stubs for your board. Once these two sets of stubs are selected, hit *ENTER*
9. Next, remove *dev-requirements.txt* and *requirements.txt*. These files won't be needed since we will generate an environment.yml from our conda environment.
    - Additionally, *pyproject.toml* could be removed if you don't plan on packaging this project as a wheel
10. Generate an *environment.yml* using: `conda env export > environment.yml`. This can be used by others to install the development environment.
11. Create a *firmware* folder in the root directory of your project. Then download the MicroPython firmware **.bin** and **.elf** files for your project's board into this directory from: https://micropython.org/download/.
12. Rename the *src* folder to *board*. This folder will contain the MicroPython code that will be used by your board.
13. Create an *mqtt* folder in the root directory of your project. This folder will contain any server side mqtt scripts.
14. Create a diagram.json for your project's simulator as shown here: https://docs.wokwi.com/diagram-format. This will define the project's configuration in the simulator.
15. Create a wokwi.toml as shown in this repo. Make sure the firmware and elf variables both point to the **.bin** and **.elf** files you downloaded in step 10.
16. Copy the *upload.py* from this repo's root folder into your project. This python script allows you to upload the MicroPython scripts onto the simulated board via telnet. To do so, update the global constants in upload.py as needed.
17. Copy this repo's *.gitignore*, which will include gitignore patterns for micropy.
18. Lastly, take a look at:
    - The app folder generated by the blacksheep-cli. Feel free to modify and remove the example code as you wish
    - The domain folder generated by the blacksheep-cli. It currently has example code showing how to create common dataclasses that all of your project can use


# Repo Workflow

## Workflow Prerequisites
1. Install the Mosquitto MQTT Broker on a separate device. Otherwise, use `test.mosquitto.org` as an MQTT broker. For instructions on how to install Mosquitto, refer to: https://mosquitto.org/. 
    - **Note:** For some reason, the Wokwi Sim can't use a MQTT broker running on the same device. Using a broker on an external device seemed to remedy this issue
    - **WARNING:** If you are using an MQTT broker located on another device, make sure to:
        1. Create a *mosquitto.conf* file, which has the following lines:
            ``` 
            listener 4000 0.0.0.0 
            allow_anonymous true
            ```
        2. Open port 4000 in your system's firewall
        3. Run the broker with: `mosquitto -c mosquitto.conf`
2. Install this repo's existing development enviroment. For instructions on how to do this, refer to [Installing an Existing Development Environment](#installing-an-existing-development-environment)

## MQTT
- **Note:** Make sure to run each of the following commands from the root folder (Python)
- **WARNING:** Before proceeding, make sure your MQTT broker is running if applicable.
- To run the MQTT test client, use: `python -m mqtt.test_client <uuid>`, where *uuid* is the unique ID for the given test client instance.
- To run the MQTT server (which drives the data collection timing), use: `python -m src.mqtt.server`
- To run the OTA Update utility, use: `python -m src.mqtt.ota_update`

## Wokwi Sim
- **Note:** Make sure to run each of the following commands from the root folder (Python)
- **WARNING:** Before proceeding, make sure your MQTT broker is running if applicable.
- To start the Wokwi Sim:
    1. Use CTRL+SHIFT+P to open the command pallet
    2. Select *Wokwi: Start Simulator*. This will start the simulator
    3. In the simulator's REPL, enter CTRL+E
    4. Use CTRL+SHIFT+` to open a local terminal
    5. To upload the files from the *board* folder to the simulated board, run: `python upload.py`
    6. In the simulator's REPL, enter CTRL+D. This will complete the file upload and reboot the board. Once the board has finished rebooting, it will be running the uploaded code
    7. To try the newly uploaded code, run: `python -m src.mqtt.server`. This will start pinging the board for data. Alternatively, modify some of the code. Then reupload the updated code using: `python -m src.mqtt.ota_update`. This will update the code over-the-air using JWT authentication

## Web Server
- **Note:** Make sure to run each of the following commands from the root folder (Python)
- **WARNING:** Before proceeding, make sure your MQTT broker is running if applicable.
- To demo the web server:
    1. Start two or more MQTT test clients
        - Make sure each client has a different uuid
    2. Start the Wokwi Sim
    3. Run: `python dev.py`
    4. Open the main webpage at: *localhost:8000/*. 
        - Since the MQTT server hasn't pinged the clients for data yet, the web page should have a paragraph saying *Empty!*
        - If the webpage has a paragraph saying *Default*, then refresh the page. If the webpage still has *Default*, then a WebSocket error has likely occurred
    5. Start the MQTT server
        - Now that the server is pinging the clients for data, there should be a row displaying the data returned by each client. If a row is red, then the client's power level is below 20%. Otherwise, the row should be green (meaning the client's power level is above 20%)


# Useful Resources
- [aiomqtt Home Page](https://sbtinstruments.github.io/aiomqtt/)
- [Conda Command Reference](https://docs.conda.io/projects/conda/en/latest/commands/index.html)
- [Blacksheep Home Page](https://www.neoteroi.dev/blacksheep/)
- [Micropy Cli Home Page](https://micropy-cli.readthedocs.io/en/latest/index.html)
- [MicroPython Documentation](https://docs.micropython.org/en/latest/)
- [Mosquitto Home Page](https://mosquitto.org/)
- [Mosquitto Public Test Broker](https://test.mosquitto.org/)
- [PyJWT Usage Examples](https://pyjwt.readthedocs.io/en/latest/usage.html)
- [Wokwi Simulator Documentation](https://docs.wokwi.com/?utm_source=wokwi)
- [Uvicorn Home Page](https://www.uvicorn.org/)


# Related Articles
- Here's part of the reason I switched from Quart to Blacksheep: [Python Async (ASGI) Web Frameworks Benchmark](https://klen.github.io/py-frameworks-bench/)
