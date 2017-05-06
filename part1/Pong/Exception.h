
#pragma once

#include <exception>
#include <string>

enum SYSTEM_ERROR {
	LABEL, TEXTURE, NETWORKING, GAME, WINDOW, RENDERER, 
	AUDIO, FILE_IO
};

enum SYSTEM_PROGRAMMER {
	WILLIAM
};

class Error : public std::exception
{
	SYSTEM_PROGRAMMER exceptionsOwner;
	SYSTEM_ERROR systemErrorLocation;

    std::string errorMessage;

public:
	Error(SYSTEM_ERROR sys, std::string msg, SYSTEM_PROGRAMMER user = WILLIAM);
	virtual ~Error() throw();
	
	const char* title();
	const char* what();
};
