#include "CommandParser.hpp"

CommandParser::Status CommandParser::parse( std::string command )
{
    if( command == "hello" ) {

    }

    if( command == "help" ) {
        message = "HELP:\n"
        "help - show a list of available commands.\n"
        "stop - stops the daemon.\n";
        return SUCCESS;
    }

    if( command == "stop" ) {
        message = "Preparing to stop papiris.\n";
        return STOP_SIGNAL;
    }

    message = "Unknown command. Type help for a list of available commands.\n";
    return UNKNOWN;
}

std::string CommandParser::getMessage()
{
    return message;
}
