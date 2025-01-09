cc_library(
    name = "callbacks",
    srcs = ["callbacks.cc"],
    hdrs = ["callbacks.h"],
    deps = [ 
        "//msg_def:msg_cc_proto", # Project
    ]
)

cc_binary(
    name = "server.out",
    srcs = ["config.h", "main.cc"],
    deps = [
        "@paho-mqtt-cpp//:paho-mqtt-cpp", # External
        ":callbacks",                     # Module
    ],
    linkopts = ["-pthread"],
)
