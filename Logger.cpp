#include "Logger.h"
#include <iostream>


bool Logger::Initialize(const std::string& theFileName)
{
	std::lock_guard<std::mutex> lock(mMutex);
	mLogFile.open(theFileName, std::ios::app);
	mIsInitialized = true;

	if (!mIsInitialized)
	{
		std::cerr << "Failed to initialize logger with file: " << theFileName << std::endl;
		return false;
	}

	return mIsInitialized;
}

void Logger::LOG(const std::string& theMessage)
{
	std::lock_guard<std::mutex> lock(mMutex);
	if(mIsInitialized && mLogFile.is_open())
	{
		mLogFile << theMessage << std::endl;
		mLogFile.flush(); // Ensure the message is written immediately
	}
	else
	{
		std::cerr << "Logger not initialized. Message: " << theMessage << std::endl;
	}

}

void Logger::CLOSE() 
{
	std::lock_guard<std::mutex> lock(mMutex);
	if (mIsInitialized && mLogFile.is_open())
	{
		mLogFile.close();
		mIsInitialized = false;
	}
}

Logger::~Logger() 
{
	CLOSE();
}


/*
// Example Usage:

#include "Logger.h"

class ExampleClass{
public

	void DoSomething()
	{
		Logger::GetInstance().LOG("Doing something important!");
	}


};

// main entry point:
int main()
{
	Logger::getInstance().Initialize("logFile.txt");

	ExampleClass exampleObject; 
	exampleObject.DoSomething();

	Logger::getInstance().LOG("Main: Application started.");
	Logger::getInstance().CLOSE();
	return 0;
}
*/