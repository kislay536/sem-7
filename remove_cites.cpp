#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input.md> <output.md>\n";
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: Could not open input file.\n";
        return 1;
    }

    std::ostringstream buffer;
    buffer << infile.rdbuf();
    std::string content = buffer.str();

    // Regex patterns
    std::regex cite_start(R"(\[cite_start\])");
    std::regex cite_pattern(R"(\[cite:.*?\])");

    // Remove them
    content = std::regex_replace(content, cite_start, "");
    content = std::regex_replace(content, cite_pattern, "");

    std::ofstream outfile(argv[2]);
    if (!outfile) {
        std::cerr << "Error: Could not open output file.\n";
        return 1;
    }

    outfile << content;

    std::cout << "Processing complete. Cleaned file written to " << argv[2] << "\n";
    return 0;
}
