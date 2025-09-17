// Define the memory needed by the model
constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

// Instantiate Interpreter
tflite::MicroInterpreter interpreter(model, resolver, tensor_arena,
kTensorArenaSize, error_reporter);

// Allocate memory for the tensors
TfLiteStatus allocate_status = interpreter.AllocateTensors();
if (allocate_status != kTfLiteOk) {
  TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
return;
}