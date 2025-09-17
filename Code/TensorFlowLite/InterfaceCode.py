		import tensorflow as tf
		# Load TFLite model and allocate tensors.
		interpreter = tf.lite.Interpreter(model_path=
		"model.tflite")
		# Get input and output tensors.
		interpreter.allocate_tensors()
		# Set the value of the input tensor.
		input_details = interpreter.get_input_details()
		output_details = interpreter.get_output_details()
		interpreter.set_tensor(input_details[0]['index'], 
		input_data)
		# Run the inference model.
		interpreter.invoke()
		# Get the value of the output tensor.
		output_data = interpreter.get_tensor(output_details[0]
		['index'])