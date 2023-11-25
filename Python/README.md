# Development Environment Set-up
## Prerequisites
- Must have miniconda installed. For intructions on how to install miniconda, refer to: https://docs.conda.io/projects/miniconda/en/latest/
- Must have VS Code installed with the following extensions:
    1. Python
    2. IntelliCode
    3. Wokwi Simulator (which requires additional set-up)
- For Wokwi Simulator set-up, refer to: https://docs.wokwi.com/vscode/getting-started

## Instructions for Installing an Existing Development Environment
To install the development environment used by this repo, open the Python folder in a terminal and run the following commands:
1. `conda env create --file environment.yml`
2. `conda activate sd`
3. `micropy`

## Instructions for Creating a Development Environment
1. Create and open your project's folder in VS Code 
2. Open a new terminal (CTRL + SHIFT + `)
3. To create a conda environment, which will contain our project's dependencies, run: `conda create -n <your-project-name> python=3.11`. This will create a development environment using conda.
4. To install Python packages that your project will use, run: `pip install <package name>`. 
    - In the context of this repo, run: `pip install aiomqtt blacksheep blacksheep-cli micropy-cli pyserial uvicorn[standard] websockets`
5. To install the development dependencies for your project's selected board, first run: `micropy stubs search <board name>`. Then look for the stubs needed for your board in the output. **Note:** The name of your board's subs should be `micropython-<board name>-stubs`  
    - In the context of this project, which uses an ESP32, run: `micropy stubs search esp32`
6. Once you have determined the name of your board's stubs, install them using: `micropy stubs add <stubs name>`. 
    - For example: `micropy stubs add micropython-esp32-stubs`
7. To initialize linting for MicroPython, run: `micropy init`. 
    - When prompted for the *Project Name*, hit *ENTER*
    - When asked to *Choose any Templates to Generate*, select *all* options *except* the Pymakr configuration. This can be done by pressing *a*, and then pressing *SPACE* with Pymakr selected. Hit *ENTER* to proceed 
    - When asked *Which stubs would you like to use*, select the stlib stubs and the stubs for your board. Then hit *ENTER*
8. Next, remove *dev-requirements.txt* and *requirements.txt*. These files won't be needed since we will generate an environment.yml from our conda environment.
9. Generate an *environment.yml* using: `conda env export > environment.yml`. This can be used by others to install the development environment.
10. Create a firmware folder in the root directory of your project. Then download the MicroPython firmware **.bin** and **.elf** files for your project's board into this directory from: https://micropython.org/download/
11. In the src folder, create the following sub-folders:
    - mqtt (which will contain any server side mqtt scripts)
    - sim (which will contain the code used by the board in the Woki Simulator)
    - web (which will contain the web server code)
12. Create a diagram.json for your project's simulator as shown here: https://docs.wokwi.com/diagram-format. This will define the project's configuration in the simulator.
13. Create a wokwi.toml as shown in this repo. Make sure the firmware and elf variables both point to the **.bin** and **.elf** files you downloaded in step 10.
14. For the final step, copy *upload.py* from this repo's src/sim folder into your project. This python script allows you to upload the scripts that are to be run on the simulated board. To do so, update the global constants in upload.py as needed

# Useful Resources
- [Conda Command Reference](https://docs.conda.io/projects/conda/en/latest/commands/index.html)
- [Micropy Cli Home Page](https://micropy-cli.readthedocs.io/en/latest/index.html)
- [MicroPython Documentation](https://docs.micropython.org/en/latest/)
- [Wokwi Simulator Documentation](https://docs.wokwi.com/?utm_source=wokwi)
- [aiomqtt Home Page](https://sbtinstruments.github.io/aiomqtt/)
- [Blacksheep Home Page](https://www.neoteroi.dev/blacksheep/)
- [Uvicorn Home Page](https://www.uvicorn.org/)

# Interesting Articles
- The reason I switched from Quart to Blacksheep: [Python Async (ASGI) Web Frameworks Benchmark](https://klen.github.io/py-frameworks-bench/)
