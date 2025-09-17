cc_binary(
    name = "my_project",
    srcs = ["src/main.cpp"],
    deps = ["@tensorflow_lite//tensorflow/lite:micro"],
)
