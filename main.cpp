#include "InMemoryDB.cpp"
#include <iostream>
using namespace std;

InMemoryDB inmemoryDB;

int main() {
    // should return null, because A doesn’t exist in the DB yet
    inmemoryDB.get("A");

    // should throw an error because a transaction is not in progress
    try {
        inmemoryDB.put("A", 5);
    } catch (runtime_error e) {
        cout << e.what() << endl;
    }

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // set’s value of A to 5, but its not committed yet
    inmemoryDB.put("A", 5);

    // should return null, because updates to A are not committed yet
    inmemoryDB.get("A");

    // update A’s value to 6 within the transaction
    inmemoryDB.put("A", 6);

    // commits the open transaction
    inmemoryDB.commit();

    // should return 6, that was the last value of A to be committed
    inmemoryDB.get("A");

    // throws an error, because there is no open transaction
    try {
        inmemoryDB.commit();
    } catch (runtime_error e) {
        cout << e.what() << endl;
    }

    // throws an error because there is no ongoing transaction
    try {
        inmemoryDB.rollback();
    } catch (runtime_error e) {
        cout << e.what() << endl;
    }

    // should return null because B does not exist in the database
    inmemoryDB.get("B");

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // Set key B’s value to 10 within the transaction
    inmemoryDB.put("B", 10);

    // Rollback the transaction - revert any changes made to B
    inmemoryDB.rollback();

    // Should return null because changes to B were rolled back
    inmemoryDB.get("B");

    return 0;
}
