#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>	
#include <mutex>
#include <afx.h>

class Logger {
public:
	static Logger& GetInstance()
	{
		static Logger instance;
		return instance;
	}

	bool Initialize(const std::string& theFileName);
	void LOG(const std::string& theMessage);
	void CLOSE();

	//Utility function Convert from CString to std::string 
	static std::string CStringToStdString(const CString& cstr, bool isForUnicodeBuilds = false)
	{
		#ifdef UNICODE
				//Unicode build 
				return std::string(CT2A(cstr.GetString())); 

		#else 
				//ANSI build 
				return std::string(cstr.GetString());
		#endif
	}

	//Delete copy constructor and assignment operator to prevent copies
	Logger(const Logger&) = delete; //Copy Constructor
	Logger& operator=(const Logger&) = delete;	//Assignment operator


private:
	Logger() = default; //Private constructor for singleton
	~Logger(); // { CLOSE(); } //Destructor


	std::ofstream mLogFile;
	std::mutex mMutex;
	bool mIsInitialized = false;
};



#endif // LOGGER_H