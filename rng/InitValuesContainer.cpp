#include "InitValuesContainer.h"

//creating object for init values from cmd
InitValuesContainer::InitValuesContainer(int argc, char* argv[]) {
    vector<string> tokenizedArgument;
    for (size_t i = 1; i < argc; i++)
    {
        tokenizedArgument.resize(0);
        tokenize(argv[i], InitValuesContainer::delimiter, tokenizedArgument);
        if (tokenizedArgument.at(0) == "/h") this->methodCode = "h";
        if (tokenizedArgument.at(0) == "/g") this->methodCode = tokenizedArgument.at(1);
        if (tokenizedArgument.at(0) == "/i") createInitVector(tokenizedArgument.at(1), this->initVector);
        if (tokenizedArgument.at(0) == "/n") this->lenghtOfSequence = stoi(tokenizedArgument.at(1));
        if (tokenizedArgument.at(0) == "/f") this->fileName = tokenizedArgument.at(1);
    }
}

void InitValuesContainer::createInitVector(string const& str, vector<int>& out) {
    vector<string> container;
    tokenize(str, InitValuesContainer::delimiterForVector, container);
    for (size_t i = 0; i < container.size(); i++) out.push_back(stoi(container.at(i)));
}



//InitValuesContainer::delimiter
void InitValuesContainer::tokenize(string const& str, const char delimiter, vector<std::string>& out) {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delimiter, end)) != std::string::npos)
    {
        end = str.find(delimiter, start);
        out.push_back(str.substr(start, end - start));
    }
}

vector<int> InitValuesContainer::getInitVector() {
    return initVector;
}

string InitValuesContainer::getMethodCode()
{
    return methodCode;
}

int InitValuesContainer::getLengthOfSequence()
{
    return lenghtOfSequence;
}

string InitValuesContainer::getFileName()
{
    return fileName;
}
