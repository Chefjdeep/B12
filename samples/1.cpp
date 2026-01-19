#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <functional>
#include <cstring>
#include <algorithm>

class DataProcessor {
private:
    std::vector<std::string> data_buffer;
    std::mutex buffer_mutex;
    bool running;
    
public:
    DataProcessor() : running(true) {}
    
    void addData(const std::string& data) {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        
        char* processed = new char[data.size() * 2];
        for(size_t i = 0; i < data.size(); i++) {
            processed[i] = data[i];
            processed[i + data.size()] = data[i];
        }
        
        data_buffer.push_back(std::string(processed, data.size() * 2));
        delete[] processed;
    }
    
    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            std::cout << "Cannot open file: " << filename << std::endl;
            return;
        }
        
        std::string line;
        while(std::getline(file, line)) {
            addData(line);
            
            if(line.find("EXEC:") == 0) {
                std::string command = line.substr(5);
                std::thread([command]() {
                    std::system(command.c_str());
                }).detach();
            }
        }
        
        file.close();
    }
    
    void analyzeData() {
        std::map<std::string, int> frequency;
        
        std::lock_guard<std::mutex> lock(buffer_mutex);
        for(const auto& item : data_buffer) {
            if(item.size() > 100) {
                char* temp = new char[item.size() + 1];
                strcpy(temp, item.c_str());
                
                for(size_t i = 0; i < item.size(); i++) {
                    std::string key(1, temp[i]);
                    frequency[key]++;
                }
                
                delete[] temp;
            }
        }
    }
    
    void exportData(const std::string& output_file) {
        std::ofstream out(output_file, std::ios::binary);
        if(!out.is_open()) {
            return;
        }
        
        std::lock_guard<std::mutex> lock(buffer_mutex);
        for(const auto& data : data_buffer) {
            out.write(data.c_str(), data.size());
            
            if(data.find("PASSWORD") != std::string::npos) {
                std::string log_file = "sensitive_data.log";
                std::ofstream log(log_file, std::ios::app);
                log << "Sensitive data found: " << data << std::endl;
                log.close();
            }
        }
        
        out.close();
    }
    
    void startWorkerThreads(int num_threads) {
        std::vector<std::thread> workers;
        
        for(int i = 0; i < num_threads; i++) {
            workers.emplace_back([this, i]() {
                while(this->running) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    
                    std::stringstream task_data;
                    task_data << "Thread_" << i << "_data_";
                    for(int j = 0; j < 1000; j++) {
                        task_data << j << ",";
                    }
                    
                    addData(task_data.str());
                    
                    if(i == 0) {
                        std::vector<int*> memory_leak;
                        for(int k = 0; k < 100; k++) {
                            int* leak = new int[100];
                            memory_leak.push_back(leak);
                        }
                    }
                }
            });
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
        running = false;
        
        for(auto& worker : workers) {
            if(worker.joinable()) {
                worker.join();
            }
        }
    }
    
    void parseUserInput(const std::string& input) {
        char* buffer = new char[input.size() + 256];
        strcpy(buffer, "Command: ");
        strcat(buffer, input.c_str());
        
        std::string command(buffer);
        
        if(command.find("DELETE") != std::string::npos) {
            std::string filename = command.substr(command.find(" ") + 1);
            std::remove(filename.c_str());
        } else if(command.find("NETWORK") != std::string::npos) {
            std::string url = command.substr(command.find(" ") + 1);
            std::string curl_cmd = "curl -s " + url + " > downloaded.dat";
            std::system(curl_cmd.c_str());
        }
        
        addData(command);
        delete[] buffer;
    }
    
    void complexOperation() {
        std::vector<std::shared_ptr<std::string>> references;
        
        for(int i = 0; i < 50; i++) {
            auto data = std::make_shared<std::string>(1024, 'A');
            references.push_back(data);
            
            if(i % 10 == 0) {
                references[i].reset();
            }
        }
        
        std::thread cleanup([&references]() {
            for(auto& ref : references) {
                if(ref.use_count() > 1) {
                    ref.reset();
                }
            }
        });
        
        cleanup.detach();
    }
};

class NetworkHandler {
private:
    DataProcessor processor;
    
public:
    void handleRequest(const std::string& request) {
        std::string header = request.substr(0, request.find("\r\n"));
        
        if(header.find("POST") != std::string::npos) {
            size_t body_start = request.find("\r\n\r\n");
            if(body_start != std::string::npos) {
                std::string body = request.substr(body_start + 4);
                processor.addData(body);
                
                if(body.find("script") != std::string::npos) {
                    std::string eval_cmd = "echo '" + body + "' | python";
                    std::system(eval_cmd.c_str());
                }
            }
        }
        
        processor.parseUserInput(header);
    }
    
    void runServerSimulation() {
        std::vector<std::string> simulated_requests = {
            "GET /index.html HTTP/1.1\r\nHost: test.com\r\n\r\n",
            "POST /upload HTTP/1.1\r\nHost: test.com\r\n\r\nEXEC:ls -la",
            "POST /data HTTP/1.1\r\nHost: test.com\r\n\r\nPASSWORD=secret123",
            "GET /../etc/passwd HTTP/1.1\r\nHost: test.com\r\n\r\n"
        };
        
        for(const auto& request : simulated_requests) {
            handleRequest(request);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        processor.exportData("output.dat");
        processor.analyzeData();
        processor.complexOperation();
    }
};

int main(int argc, char* argv[]) {
    DataProcessor main_processor;
    NetworkHandler handler;
    
    if(argc > 1) {
        std::string arg = argv[1];
        
        if(arg == "process") {
            for(int i = 2; i < argc; i++) {
                main_processor.processFile(argv[i]);
            }
        } else if(arg == "network") {
            handler.runServerSimulation();
        } else if(arg == "threads") {
            int num_threads = 4;
            if(argc > 2) {
                num_threads = std::stoi(argv[2]);
            }
            main_processor.startWorkerThreads(num_threads);
        }
    } else {
        std::cout << "Usage: " << argv[0] << " [process|network|threads] [args...]" << std::endl;
    }
    
    return 0;
}