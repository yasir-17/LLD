# include <iostream>
# include <string>
# include <vector>
# include <unordered_map>

using namespace std;

enum LockerSize {
    SMALL,
    MEDIUM,
    LARGE
};

class Coordinates {
    private:
        int x;
        int y;
    public:
        Coordinates(int x, int y): x(x), y(y) {}

        int getXCoordinate() const { return x; }
        int getYCoordinate() const { return y; }

        int getNearestdistance(Coordinates coord) {
            return (x-coord.getXCoordinate())^2 + (y-coord.getYCoordinate())^2;
        }

};

class Locker {
    private:
        int id;
        Coordinates cd;
        LockerSize size;
        bool isAvailable;
        int expiryDate;
    public:
        Locker (int id, Coordinates cd, LockerSize size, bool isAvailable, int expiry) : id(id), cd(cd), size(size), isAvailable(isAvailable), expiryDate(expiry) {}

        int getId() const { return id; }
        bool isAvailable() const { return isAvailable; }
        int getSize() const { return size; }
        Coordinates getCoordinates() const { return cd; }
        
};

class Users {
    private:
        int id;
        Coordinates cd;

    public:
        Users (int id, Coordinates cd) : id(id), cd(cd) {}

};

class AmazonLocker {
    private:
        vector<Locker> lockers;
        unordered_map<int, string> lockerCodes;
    public:
        AmazonLocker();

        void addLocker (Locker locker) {
            lockers.push_back(locker);
        }

        Locker* findNearestLocker (Coordinates& userLoc, LockerSize size) {
            Locker* nearest = nullptr;
            int minDist = 1e6;
            for (auto& locker : lockers) {
                if (locker.isAvailable() && locker.getSize() == size) {
                    int dist = userLoc.getNearestdistance(locker.getCoordinates());
                    if (dist < minDist) {
                        minDist = dist;
                        nearest = &locker;
                    }
                }
            }
            return nearest;
        }

        string generateCode() {
            string code;
            for (int i = 0; i < 6; ++i) {
                code += to_string(rand() % 10);
            }
            return code;
        }

        void assignLocker (Users& user, LockerSize size) {
            Locker* nearest = findNearestLocker(user.getCoordinates(), size);
            if (locker) {
                locker->setAvailability(false);
                string code = generateCode();
                lockerCodes[locker->getId()] = code;
                cout << "Locker assigned. Code: " << code << endl;
            } else {
                cout << "No suitable locker available." << endl;
            }
        }

};