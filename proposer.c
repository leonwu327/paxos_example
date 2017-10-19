#include "accepter.h"
#include <queue>

string PROPOSALS[3] = {"Proposal_1", "Proposal_2", "Proposal_3"};

#define ARRAY_LENGTH(array) (sizeof(array)/sizeof(array[0]))

static void proposerVote(vector<Acceptor *> &acceptors) {
    int quorum = acceptors.size() / 2 + 1;
    int maxb = 0;
    int last_prepare_b = 0;
    int b = last_prepare_b + 1;
    int count_pre_ok = 0;
    int count_accept_ok = 0;
    int i = 0;
    queue<int> queue;
    string v;
    
    while (true) {
        v = PROPOSALS[rand() % ARRAY_LENGTH(PROPOSALS)];

        //得到b的序号
        if ((!queue.empty()) && rand() / double(RAND_MAX) - 0.5 > 0) {
            //乱序的序号到达
            b = queue.front();
            queue.pop();
        } else {
            b = last_prepare_b + 1;
            last_prepare_b ++;
            if (rand() / double(RAND_MAX) - 0.7 > 0) {
                //模拟乱序, 部分没有到达, 下一次随机到达
                queue.push(b);
                continue;
            }
        }
        std::cout << std::endl;
        std::cout << "**************************************************************" << std::endl;
        std::cout << "Accepter  pb  ab    av" << std::endl;
        for (i = 0; i < acceptors.size(); i ++) {
            std::cout << acceptors[i]->getName() << "         "
                      << acceptors[i]->getPb() << "   "
                      << acceptors[i]->getAb() << "   "
                      << acceptors[i]->getAv() << " "
                      << std::endl;
        }
        
        std::cout << std::endl;
        std::cout << "vote    : start < vote_number : " << b << " >" << std::endl;
        
        count_pre_ok = 0;
        for (i = 0; i < acceptors.size(); i ++) {
            Promise *promise = acceptors[i]->onPrepare(b);
            if (promise && promise->isAck()) {
                count_pre_ok ++;
                if (promise->getAb() > maxb && promise->getAv() != "") {
                    maxb = promise->getAb();
                    //使用maxvalue的v
                    v = promise->getAv();
                    std::cout << "vote    : v change < maxb : " << maxb << " v : " << v << " >" << std::endl;
                    
                }
            }
        }
        
        if (count_pre_ok < quorum) {
            std::cout<<"prepare : end <" << b << "> : vote < not accepted >" << std::endl;
            continue;
        }
        
        count_accept_ok = 0;
        for (i = 0; i < acceptors.size(); i ++) {
            if (acceptors[i]->onAccept(b, v)) {
                count_accept_ok ++;
            }
        }
        
        if (count_accept_ok < quorum) {
            std::cout<<"accept  : end <" << b << ":" << v << "> : vote < not accepted >"<<std::endl;
            continue;
        }
        
        break;
    }
    std::cout<<"proposal: <" << b << ":" << v << "> : vote < success >"<<std::endl;
}

int main() {
    srand((unsigned)time(NULL));  
    vector<Acceptor *> acceptors;
    acceptors.push_back(new Acceptor("A"));
    acceptors.push_back(new Acceptor("B"));
    acceptors.push_back(new Acceptor("C"));
    acceptors.push_back(new Acceptor("D"));
    acceptors.push_back(new Acceptor("E"));
    proposerVote(acceptors);
    return 0;
}


