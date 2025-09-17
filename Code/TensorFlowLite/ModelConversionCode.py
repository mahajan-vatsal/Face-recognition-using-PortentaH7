# Converting a SavedModel to a TensorFlow Lite model.
converter = tf.lite.TFLiteConverter.from_saved_model(model)
tflite_model = converter.convert()

# Converting a tf.Keras model to a TensorFlow Lite model.
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Converting a Keras H5 model to a TensorFlow Lite model.
model = tf.keras.models.load_model('model.h5')
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Converting ConcreteFunctions to a TensorFlow Lite model.
converter = tf.lite.TFLiteConverter.from_concrete_functions([func], model)
tflite_model = converter.convert()

# Converting a Jax model to a TensorFlow Lite model.
converter = tf.lite.TFLiteConverter.experimental_from_jax(
    [func], [[ ('input1', input1), ('input2', input2)]])
tflite_model = converter.convert()
