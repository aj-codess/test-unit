#include <iostream>
#include <chrono>
#include <mutex>
#include <atomic>
#include <thread>

class SnowflakeIDGenerator {
private:
    static constexpr uint64_t epoch = 1640995200000; // Custom epoch (2022-01-01)
    static constexpr uint64_t machineIDBits = 10;
    static constexpr uint64_t sequenceBits = 12;
    
    static constexpr uint64_t maxMachineID = (1 << machineIDBits) - 1;
    static constexpr uint64_t maxSequence = (1 << sequenceBits) - 1;
    
    uint64_t machineID;
    std::atomic<uint64_t> lastTimestamp;
    std::atomic<uint64_t> sequence;
    std::mutex mtx;

    uint64_t currentTimestamp() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch()).count();
    }

public:
    explicit SnowflakeIDGenerator(uint64_t machineID) : machineID(machineID), lastTimestamp(0), sequence(0) {
        if (machineID > maxMachineID) {
            throw std::invalid_argument("Machine ID exceeds max limit.");
        }
    }

    uint64_t generateID() {
        std::lock_guard<std::mutex> lock(mtx);
        uint64_t timestamp = currentTimestamp();

        if (timestamp == lastTimestamp) {
            sequence = (sequence + 1) & maxSequence;
            if (sequence == 0) {
                // Wait for next millisecond
                while (timestamp <= lastTimestamp) {
                    timestamp = currentTimestamp();
                }
            }
        } else {
            sequence = 0;
        }

        lastTimestamp = timestamp;

        return ((timestamp - epoch) << (machineIDBits + sequenceBits)) |
               (machineID << sequenceBits) |
               sequence;
    }
};

// Test
int main() {
    SnowflakeIDGenerator generator(1); // Machine ID 1
    for (int i = 0; i < 5; ++i) {
        std::cout << generator.generateID() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Simulating requests
    }
    return 0;
}
