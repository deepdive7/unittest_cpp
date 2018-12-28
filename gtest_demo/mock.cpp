//
// Created by edenzhong on 2018/8/30.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect {
public:
    virtual bool login(string username, string password) { return true;};
    virtual bool logout(string username) { return true; };
    virtual string fetch(string key) { return key; };
};


class MockDB : public DataBaseConnect {
public:
    MOCK_METHOD1(fetch, string(string key));
    MOCK_METHOD1(logout, bool(string username));
    MOCK_METHOD2(login, bool(string username, string password));
};

class MyDatabase {
    DataBaseConnect  & dbConnect;
public:
    MyDatabase(DataBaseConnect & _dbC) : dbConnect(_dbC) {}
    int Init(string uname, string passwd) {
        cout << uname << ": " << passwd << endl;
        if(dbConnect.login(uname, passwd) != true) {
            cout<<"Failed to connect >>>>> "<<endl;
            if(dbConnect.login(uname, passwd) != true) {
                cout<<"Failure 2nd Time.. Returning.."<<endl;
                return -1;
            }
        } else {
            cout<<"Successful Connection >>>>>"<<endl;
            return 1;
        }
        return 0;
    };

    bool Close(string uname){
      return dbConnect.logout(uname);
    };

    string Fetch(string key){
      return dbConnect.fetch(key);
    };
};


TEST(MyDBTest, Login) {
    MockDB mdb;
    MyDatabase db(mdb);
    EXPECT_CALL(mdb, login("mock","db"))
            .Times(AtLeast(1))
            .WillOnce(Return(true));
    int retValue = db.Init("mock", "db");
    EXPECT_EQ(retValue, 1);
}

TEST(MyDBTest, Logout) {
    MockDB mdb;
    MyDatabase db(mdb);
    EXPECT_CALL(mdb, logout("mock"))
            .Times(AtLeast(1))
            .WillOnce(Return(true));
    int retValue = db.Close("mock");
    EXPECT_EQ(retValue, true);
}

TEST(MyDBTest, LoginFailure){
    MockDB mdb;
    MyDatabase md(mdb);

    EXPECT_CALL(mdb, login(_, _))
            .Times(2)
            .WillOnce(Return(false))
            .WillOnce(Return(false));

    int retValue = md.Init("mock", "I'll be back");
    EXPECT_EQ(retValue, -1);
}

TEST(MyDBTest, Fetch){
    MockDB mdb;
    MyDatabase db(mdb);
    EXPECT_CALL(mdb, fetch("mock"))
           .Times(AtLeast(1))
           .WillOnce(Return("mock"));
    string retValue = db.Fetch("mock");
    cout << "Get:" <<  retValue << endl;
    EXPECT_STREQ("mock", retValue.c_str());
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
