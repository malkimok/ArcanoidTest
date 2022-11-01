#include <iostream>
#include <string>

#include "inc/Framework.h"
#include "MyFramework.hpp"
#include "Object.hpp"

bool isStringANumber(const string& s);

void handleConsoleInput(int argc, char* argv[], int& wWidth, int& wHeight);

int main(int argc, char* argv[]){
    bool runReturn = 0;
    while(MyFramework::restart){
        MyFramework* framework = new MyFramework();
        int wWidth = framework->getWWidth();
        int wHeight = framework->getWHeight();
        handleConsoleInput(argc, argv, wWidth, wHeight);
        framework->SetWindowParameters(wWidth, wHeight);
        runReturn = run(new MyFramework());
    }
    return runReturn;
}

bool isStringANumber(const string& s){
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void handleConsoleInput(int argc, char* argv[], int& wWidth, int& wHeight){
    if(argc > 1){
        if(strcmp(argv[1], "-window") == 0){
            string WxHInput = argv[2];
            string sWidth = WxHInput.substr(0, WxHInput.find("x"));
            string sHeight = WxHInput.substr(WxHInput.find("x") + 1);
            if(isStringANumber(sWidth)&&isStringANumber(sHeight)){
                wWidth = stoi(sWidth);
                wHeight = stoi(sHeight);
                cout << "WxH will be set as " << wWidth << "x" << wHeight << endl;
            }
            else{
                cout << "Incorrect input. WxH will be set as 800x600" << endl;
            }
        }
    }
    else{
        cout << "WxH will be set as 800x600" << endl;
    }
    cout << "Arrow UP to restart." << endl;
}
