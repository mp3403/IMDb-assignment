#include "InMemoryDB.cpp"
#include <iostream>
using namespace std;

InMemoryDB inmemoryDB;

int main() {
    // should return null, because A doesn’t exist in the DB yet
    cout << "Value for A at beginning of program: ";
    cout << inmemoryDB.get("A") << endl;

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
    cout << "Value for A after put call but before commit: ";
    cout << inmemoryDB.get("A") << endl;

    // update A’s value to 6 within the transaction
    inmemoryDB.put("A", 6);

    // commits the open transaction
    inmemoryDB.commit();

    // should return 6, that was the last value of A to be committed
    cout << "Value for A after commit: ";
    cout << inmemoryDB.get("A") << endl;

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
    cout << "Value for B before rollback: ";
    cout << inmemoryDB.get("B") << endl;

    // starts a new transaction
    inmemoryDB.begin_transaction();

    // Set key B’s value to 10 within the transaction
    inmemoryDB.put("B", 10);

    // Rollback the transaction - revert any changes made to B
    inmemoryDB.rollback();

    // Should return null because changes to B were rolled back
    cout << "Value for B after rollback: ";
    cout << inmemoryDB.get("B") << endl;

    return 0;
}
