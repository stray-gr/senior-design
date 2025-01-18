# Setup
1. Open ` ~/.config/pypoetry/config.toml`
2. Add:
    ```toml
    [virtualenvs]
    in-project = true
    ```
3. Get command from `poetry env activate`
4. Run command
5. `python -m grpc_tools.protoc -I./ --python_out=. --pyi_out=. --grpc_python_out=. ./api.proto`