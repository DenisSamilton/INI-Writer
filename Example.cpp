#include "INIWriter.hpp"

using INIWriter = samilton::INIWriter;

int main() {
	INIWriter config(INIWriter::INIcommentType::unixType);

	config["Graphic"]["resX"] = 1920;
	config["Graphic"]["resY"] = 1080;
	config["Graphic"]["windowMode"] = "borderless";
	config["Launch"]["dev"]("Launch in dev mode") = true;
	config["Physics"]["gravity"] = 1.03;

	config.saveToFile("example.ini");
}