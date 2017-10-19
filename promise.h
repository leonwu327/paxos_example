#include <string>
#include <stdlib.h>/*用到了srand函数，所以要有这个头文件*/
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

class Promise {
private:
    bool ack;
    long ab;
    string av;

public:
    Promise(bool ack, long ab, string av) {
        this->ack = ack;
        this->ab = ab;
        this->av = av;
    }

    bool isAck() {
        return ack;
    }

    long getAb() {
        return ab;
    }

    string getAv() {
        return av;
    }
};

