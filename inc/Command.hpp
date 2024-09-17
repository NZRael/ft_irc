#pragma once

#include <string>
#include <vector>

class Command {
public:
    Command();
    Command(const std::string& raw_message);
    ~Command();
    
    void parse(const std::string& raw_message);
    
    std::string getPrefix() const;
    std::string getName() const;
    std::vector<std::string> getParams() const;
    std::string getTrailing() const;

private:
    std::string prefix;
    std::string name;
    std::vector<std::string> params;
    std::string trailing;

    void parsePrefix(std::string& message);
    void parseName(std::string& message);
    void parseParams(std::string& message);
};
