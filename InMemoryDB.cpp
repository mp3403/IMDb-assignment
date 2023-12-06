#include <string>
#include <map>
#include <exception>
#include <stdexcept>
using namespace std;

class InMemoryDB {
    bool transactionOccuring;
    map<string, int> database;
    map<string, int> tempDB;

    public:
        InMemoryDB() {
            transactionOccuring = false;
        }

        int get(string key) {
            return database[key];
        }

        void put(string key, int val) {
            if (!transactionOccuring)
                throw runtime_error("put() called when transaction not in progress");
            tempDB[key] = val;
        }

        void begin_transaction() {
            tempDB = database;
            transactionOccuring = true;
        }

        void commit() {
            if (!transactionOccuring)
                throw runtime_error("commit() called when transaction not in progress");

            database = tempDB;
            transactionOccuring = false;
        }

        void rollback() {
            if (!transactionOccuring)
                throw runtime_error("rollback() called when transaction not in progress");

            transactionOccuring = false;
        }
};
