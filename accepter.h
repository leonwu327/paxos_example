#include "promise.h"

class Acceptor {

        //上次表决结果
private:
    long   pb;
    long   ab;
    string av;
    string name;

public:
    Acceptor(string name) {
        this->name = name;
        this->pb = 0;
        this->ab = 0;
        this->av = "";
    }

    Promise* onPrepare(long b) {        
        //假设这个过程有20%的几率失败
        if (rand() / double(RAND_MAX) - 0.5 > 0) {
            std::cout << "accepter: " << this->name << " prepare no response" << std::endl;
            return NULL;
        }

        if (b >= this->pb) {
            pb = b;
            Promise *response = new Promise(true, this->ab, this->av);
            std::cout << "accepter: " << this->name << " prepare ok" << std::endl;
            return response;
        } else {
            std::cout << "accepter: " << this->name << " prepare rejected" << std::endl;
            return new Promise(false, 0, "");
        }
    }

    bool onAccept(long b, string v) {
        //假设这个过程有20%的几率失败
        if (rand() / double(RAND_MAX) - 0.5 > 0) {
            std::cout << "accepter: " << this->name << " accept no response" << std::endl;
            return false;
        }

        if (b == this->pb) {
            ab = b;
            av = v;
            std::cout << "accepter: " << this->name << " accept ok < " << b << " : " << v << " >" << std::endl;
            return true;
        } else {
            std::cout << "accepter: " << this->name << " accept rejected" << std::endl;
            return false;
        }
    }
    
    long getPb() {
        return pb;
    }

    long getAb() {
        return ab;
    }

    string getAv() {
        return av;
    }

    string getName() {
        return name;
    }
};

