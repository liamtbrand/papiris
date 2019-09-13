#ifndef CommandParser_hpp
#define CommandParser_hpp

#include <string>
#include <iostream>

class CommandParser
{
public:
    CommandParser() {}

    enum Status {
        SUCCESS,UNKNOWN,STOP_SIGNAL
    };

    /**
     * @return true if the command was processed successfully, false otherwise.
     */
    CommandParser::Status parse( std::string command );

    /**
     * Fetch the message resulting from the last command parsed.
     */
    std::string getMessage();
private:
    std::string message;
};

#endif /* CommandParser_hpp */
