#include <iostream> // wrapped in namesmace called std, std::cint, std::count etc
#include <fstream> // file steam classes std::ifstream for reading, std::ofstream for writing
#include <string>

static void err(const std::string& msg) {
	std:: cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	if (argc != 4)
		err("need params: ./replace <filename> <s1> <s2>");

	const std::string filename = argv[1];
	const std::string s1 = argv[2];
	const std::string s2 = argv[3];

	//if (s1.empty())
	//	err("Error: s1 cannot be empty");

	std::ifstream infile(filename); // open file for reading
	if (!infile)
		err("Error: Could not open file " + filename);

	std::ofstream outfile(filename + ".replace"); // creates/truncates a file for writing
	if (!outfile)
		err("Error: Could not create output file " + filename + ".replace");

	std::string line;
	while (std::getline(infile, line)) { // returns true if read sth
		std::string result;
		size_t pos = 0, found;
		while((found = line.find(s1, pos)) != std::string::npos) {
			result.append(line, pos, found - pos);
			result = s2;
			pos = found + s1.length();
		}
		result.append(line, pos, std::string::npos);
		outfile << result;
		if (!infile.eof())
			outfile << '\n'; // Add newline if not at end of file
	}

	return (0);
}