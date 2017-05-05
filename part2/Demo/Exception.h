
#include <exception>
#include <string>

enum class ErrorType
{
    Label,
    Texture,
    Networking,
    Game,
    Window,
    Renderer,
    Audio,
    FileIO,
    System
};

enum class ErrorAuthor
{
    William
};

class Error : public std::exception
{
    ErrorAuthor errorAuthor;
    ErrorType errorType;

    std::string errorMessage;
public:
    Error(ErrorType sys, std::string msg, ErrorAuthor user = ErrorAuthor::William);
    virtual ~Error() throw();

    const char * title();
    const char * what();

};
