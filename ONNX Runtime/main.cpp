#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>
#include <cmath> 
#include <array>
#include <random>
#include <iomanip>
#include <string>
#include <fstream>

void LoadTestData(const std::string& file_path, std::vector<float>& X_data, std::vector<float>& Y_data) {

	X_data.clear();
    Y_data.clear();
    std::ifstream file(file_path);
    if (!file.is_open()) {
		throw std::runtime_error("File not found");
	}
    int lines_count = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++lines_count;
    }

    X_data.resize(lines_count);
    Y_data.resize(lines_count);

    file.clear();
    file.seekg(0, std::ios::beg);

    for(int i = 0; i < lines_count; i++) {
        file >> X_data[i] >> Y_data[i];
		std::cout << "X: " << X_data[i] << ", Y: " << Y_data[i] << "\n";
	}
}

int main() {
    try {
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);

        Ort::Session session(env, L"model.onnx", session_options);

        Ort::AllocatorWithDefaultOptions allocator;

        Ort::AllocatedStringPtr input_name_ptr = session.GetInputNameAllocated(0, allocator);
        Ort::AllocatedStringPtr output_name_ptr = session.GetOutputNameAllocated(0, allocator);

        const char* input_name = input_name_ptr.get();
        const char* output_name = output_name_ptr.get();

        std::vector<float> X_data;
        std::vector<float> Y_data;
		LoadTestData("data.txt", X_data, Y_data);

        std::vector<float> input_data = X_data;
        
        std::array<int64_t, 3> input_shape{ 1, 100, 1};

        auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
        Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_data.data(), input_data.size(), input_shape.data(), input_shape.size());

        auto output_tensors = session.Run(Ort::RunOptions{ nullptr },
            &input_name, &input_tensor, 1,
            &output_name, 1);

        float* output_data = output_tensors.front().GetTensorMutableData<float>();

        for (int i = 0; i < Y_data.size(); ++i) {
            if (output_data[i] > 0.5f)
                std::cout << "Transition at time step: " << i << "\n";
        }
    }
    catch (const Ort::Exception& e) {
        std::cerr << "ONNX Runtime ошибка: " << e.what() << "\n";
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 3;
    }
    return 0;
}
