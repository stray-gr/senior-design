# Poetry Setup
1. Open ` ~/.config/pypoetry/config.toml`
2. Add:
    ```toml
    [virtualenvs]
    in-project = true
    ```

# Project Setup
1. `poetry new project_name`
2. `cd` into the newly create project and `poetry add grpcio grpcio-tools`
3. Get command from `poetry env activate`
4. Run command
5. `cd` to repo root, then run:
    ```bash
    python -m grpc_tools.protoc -I./ --python_out=./api/{module}/{module} --pyi_out=./api/{module}/{module} --grpc_python_out=./api/{module}/{module} ./service.proto
    ```
