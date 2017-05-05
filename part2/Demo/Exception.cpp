
#include "Exception.h"

Error::Error(ErrorType sys, std::string msg, ErrorAuthor user)
{
    errorType = sys;
    errorAuthor = user;
    errorMessage = msg;
}

Error::~Error() throw()
{
}

const char * Error::what()
{
    static std::string message = "Error thrown by ";

    switch (errorAuthor)
    {
    case ErrorAuthor::William: message += " William Taylor\n\nMessage ->";
        break;
    }

    message.append(errorMessage.c_str());
    return(message.c_str());
}

const char * Error::title()
{
    static std::string title = "Error !!!";

    switch (errorType)
    {
    case ErrorType::Networking: title = "Networking error";
        break;
    case ErrorType::Renderer: title = "Renderer error";
        break;
    case ErrorType::Texture: title = "Texture error";
        break;
    case ErrorType::FileIO: title = "File_IO error";
        break;
    case ErrorType::Window: title = "Window error";
        break;
    case ErrorType::Audio: title = "Audio error";
        break;
    case ErrorType::Label: title = "Label error";
        break;
    case ErrorType::Game: title = "Game error";
        break;
    }

    return(title.c_str());
}
