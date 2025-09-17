import numpy as np # convert_tflite_to_header.py
with open("addition_model.tflite", "rb") as f:
    tflite_model = f.read()
tflite_model_as_c_array = np.array(list(tflite_model), dtype=np.uint8)
with open("addition_model.h", "w") as f:
    f.write("#ifndef ADDITION_MODEL_H\n")
    f.write("#define ADDITION_MODEL_H\n\n")
    f.write("unsigned char addition_model_tflite[] = {")
    for i, byte in enumerate(tflite_model_as_c_array):
        if i % 12 == 0:
            f.write("\n")
        f.write(f"0x{byte:02x}, ")
    f.write("\n};\n\n")
    f.write("unsigned int addition_model_tflite_len = {};\n".format(len(tflite_model_as_c_array)))
    f.write("#endif // ADDITION_MODEL_H\n")
