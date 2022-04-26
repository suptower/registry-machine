#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void compile(vector<string> program) {
    int acc = 0, pc = 0;
    vector<int> mem(10,0);
    for (pc = 0; pc <  program.size();) {
        if (program.at(pc).rfind("#",0)==0) {
            //comment detected
            pc++;
            continue;
        }
        else {
            //command detected
            string cmdStr = program.at(pc).substr(0,2);
            string opStr = program.at(pc).substr(3,2);
            int cmd {stoi(cmdStr,0,16)};
            int op {stoi(opStr,0,16)};
            switch(cmd) {
                case 0x1: {
                    //ADD
                    acc += mem.at(op);
                    pc++;
                    break;
                }
                case 0x2: {
                    //SUB
                    acc -= mem.at(op);
                    pc++;
                    break;
                }
                case 0x3: {
                    //MUL
                    acc *= mem.at(op);
                    pc++;
                    break;
                }
                case 0x4: {
                    //DIV
                    acc /= mem.at(op);
                    pc++;
                    break;
                }
                case 0x5: {
                    //LDA
                    acc = mem.at(op);
                    pc++;
                    break;
                }
                case 0x6: {
                    //LDK
                    acc = op;
                    pc++;
                    break;
                }
                case 0x7: {
                    //STA
                    mem.at(op) = acc;
                    pc++;
                    break;
                }
                case 0x8: {
                    //INP
                    cout << "Input integer: ";
                    cin >> mem.at(op);
                    pc++;
                    break;
                }
                case 0x9: {
                    //OUT
                    cout << mem.at(op);
                    pc++;
                    break;
                }  
                case 0xA: {
                    //HLT
                    return;
                    break;
                }
                case 0xB: {
                    //JMP
                    pc = op-1;
                    break;
                }
                case 0xC: {
                    //JEZ
                    if (!acc) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                case 0xD: {
                    //JNE
                    if (acc) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                case 0xE: {
                    //JLZ
                    if (acc < 0) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                case 0xF: {
                    //JLE
                    if (acc <= 0) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                case 0x10: {
                   //JGZ
                    if (acc > 0) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                case 0x11: {
                    //JGE
                    if (acc >= 0) {
                        pc = op-1;
                    }
                    else {
                        pc++;
                    }
                    break;
                }
                default: {
                    //error
                    cerr << "cmd not defined: " << cmd << endl;
                    break;
                    return;
                }
            }
        }
    }
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
int main(int argc, char** argv) {
    string arguments {*++argv};
    cout << arguments << endl;
    ifstream inFile;
    vector<string> inputString;
    if (argc == 2) {
        if (hasEnding(arguments,".txt")) {
            inFile.open(arguments);
            string temp;
            if (!inFile) {
                cerr << "Unable to open file.";
                return 1;
            }
            while (getline(inFile, temp)) {
                inputString.push_back(temp);
            }
            inFile.close();
        } else {
            cerr << "You need to pass a .txt file." << endl;
            return 2;
        }
    } else {
        cerr << "You need to pass exactly 1 text file as argument." << endl;
        return 1;
    }
    compile(inputString);
    return 0;
}