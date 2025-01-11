#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;
    
    // Read number of test cases
    std::getline(std::cin, line);
    int num_cases = std::stoi(line);
    
    while (num_cases--) {
        // Read N (size of sequence)
        std::getline(std::cin, line);
        int n = std::stoi(line);
        
        // Read sequence line
        std::getline(std::cin, line);
        std::istringstream values(line);
        
        int max_reach = 1;
        for (int i = 0; i < n; i++) {
            if (max_reach <= i) break;
            
            // Read each value from the sequence line
            int height;
            values >> height;
            
            if (i + height > max_reach) {
                max_reach = i + height;
            }
        }
        
        std::cout << std::min(n, max_reach) << '\n';
    }
    
    return 0;
}