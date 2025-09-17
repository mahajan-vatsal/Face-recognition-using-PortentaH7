import tensorflow as tf
import numpy as np
from PIL import Image

# Load the TFLite model and allocate tensors
interpreter = tf.lite.Interpreter(model_path="model.tflite")
interpreter.allocate_tensors()

# Get input and output tensors
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# Prepare the input image
img = Image.open('image.jpg').resize((224, 224))
input_data = np.expand_dims(np.array(img, dtype=np.float32), axis=0)

# Set the tensor to point to the input data to be inferred
interpreter.set_tensor(input_details[0]['index'], input_data)

# Run the model
interpreter.invoke()

# Get the output data
output_data = interpreter.get_tensor(output_details[0]['index'])
print('Output:', output_data)