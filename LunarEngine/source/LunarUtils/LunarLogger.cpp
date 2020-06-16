#include "../../public/LunarLogger.h"

namespace LunarLogger {
	Logger* Logger::instance = 0;

	Logger::Logger() {

	}

	Logger* Logger::getInstance() {
		if (instance == 0)
			instance = new Logger();

		return instance;
	}

	void Logger::log(std::string message, std::string owner, std::string color) {
		if (color == "white")
			std::cout << WHITE << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "black")
			std::cout << BLACK << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "red")
			std::cout << RED << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "green")
			std::cout << GREEN << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "yellow")
			std::cout << YELLOW << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "blue")
			std::cout << BLUE << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "MAGENTA")
			std::cout << MAGENTA << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
		if(color == "CYAN")
			std::cout << CYAN << "[Lunar " << owner << "]" << RESET << ": " << message << std::endl;
	}
}