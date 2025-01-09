# Set-up From Scratch
1. conan new bazel_exe
2. Replace conanfile.py with conanfile.txt
3. Update conanfile.txt requires with project deps
    - Search for packages [here](https://conan.io/center)
4. conan install . --build=missing
5. copy .vscode, then update the `C_Cpp.default.compilerPath` variable with your C++ compiler's path
6. Copy MODULE.bazel and update `use_repo` as described here: https://docs.conan.io/2/reference/tools/google/bazeldeps.html#
7. Refer to this example for how to set up the project directory structure: https://bazel.build/start/cpp
8. bazel --bazelrc=./conan/conan_bzl.rc build --config=conan-config //folder:cc_binary_name

# TODO
1. Add symlink from broker ca cert to here (make sure to update configs)
2. Bazel build :all
3. Add [postgres](https://conan.io/center/recipes/libpqxx?version=7.10.0) integration. Make sure to stream inserts
    - Schema for testing (uses cat protobuf toy example)
    - Schema for sensor data
    - Schema for API users
    - How to specify schema via exec: https://stackoverflow.com/a/34098414
4. Add [D++](https://conan.io/center/recipes/dpp?version=10.0.35) integration
    - This replaces email and mailing list with a Discord server managed by a wider variety of community members