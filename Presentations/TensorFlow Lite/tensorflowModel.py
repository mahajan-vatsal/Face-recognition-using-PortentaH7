import tensorflow as tf
import numpy as np
input_shape = (2,) # Define the input shape
model = tf.keras.Sequential([ # Create a Seq.model
    tf.keras.layers.Input(shape=input_shape),
    tf.keras.layers.Dense(1)  # Single neuron for o/p
])
# Compile the model
model.compile(optimizer='sgd', loss='mse')
# Generate some training data
X_train = np.array([[1, 2], [3, 4], [5, 6]])
y_train = np.array([[3], [7], [11]])
# Train the model
model.fit(X_train, y_train, epochs=100, verbose=0)
# Save the model using recommended method for TF 2.x
tf.keras.models.save_model(model, 'addition_model.h5')
print("Model saved as 'addition_model.h5'")
