#include <bits/stdc++.h>

using namespace std;

class personCompare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
};

int main() {
    //edge and vertex
    int noTransaction, noFriends;
    cin >> noTransaction >> noFriends;

    //x gives y some amount
    string x, y;
    int amount;

    //net amount each person will have at end
    map<string, int> net;

    while (noTransaction--) {
        cin >> x >> y >> amount;
        if (net.count(x) == 0) {
            net[x] = 0;
        }
        if (net.count(y) == 0) {
            net[y] = 0;
        }
        net[x] -= amount;
        net[y] += amount;
    }

    //to store multiple net balances
    multiset<pair<string, int>,personCompare> m;

    //initializing a list and sorting it
    for (auto p: net) {
        string person = p.first;
        int amount = p.second;

        if (net[person] != 0) {
            m.insert(make_pair(person, amount));
        }
    }

    /*
     * Greedy Approach -
     * Take out two net balances,
     * one from left and right.
     *
     * Left one will be debited and right one
     * will be credited until set is empty.
     *
     * Person with low net balance will
     * try to settle person with the high net balance.
     *
     * */

    int cnt = 0;
    while (!m.empty()) {
        auto left = m.begin();
        auto right = prev(m.end());

        string debit_person = left->first;
        int debit = left->second;

        string credit_person = right->first;
        int credit = right->second;

        //erasing them from multiset
        m.erase(left);
        m.erase(right);

        //settlement
        int settlementAmount = min(abs(debit), credit);
        cnt++;

        debit += settlementAmount;
        credit -= settlementAmount;

        cout<<debit_person<<" will pay "<<settlementAmount<<" to "<<credit_person<<endl;

        if (debit != 0){
            m.insert(make_pair(debit_person,debit));
        }
        if (credit != 0){
            m.insert(make_pair(credit_person,credit));
        }

    }

    cout <<"Total number of Transaction(s) required : "<<cnt << endl;

    return 0;
}

//Sample Test Case :
//3 3
//Rahul Ajay 100
//Ajay Neha 50
//Neha Rahul 40
