#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>


inline std::vector<double> split_line(const std::string& line) {
    std::vector<double> res;
    int start_index = 0;
    bool in_number = false; // Flag to track if we are currently reading a number

    for (int i = 0; i < line.length(); i++) {
        if (std::isspace(line[i])) {
            if (in_number) { // If we were reading a number
                res.push_back(std::stod(line.substr(start_index, i - start_index)));
                in_number = false; // We're now outside of a number
            }
        } else {
            if (!in_number) { // If we're not already reading a number
                start_index = i; // Mark the start of a new number
                in_number = true; // We're now reading a number
            }
        }
    }

    // If we ended while still reading a number, process the last number
    if (in_number) {
        res.push_back(std::stod(line.substr(start_index)));
    }

    return res;
}
#endif
