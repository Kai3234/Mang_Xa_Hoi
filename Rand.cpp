#include <bits/stdc++.h>
using namespace std;

class FRIEND 
{
protected:
    vector<string> friendname; 

public:
    bool isFriend(const string& name) const 
    {
        return find(friendname.begin(), friendname.end(), name) != friendname.end();
    }

    const vector<string>& getFriends() const {
        return friendname;
    }
};

class USER : public FRIEND {
public:
    string name;
    string password;

    USER(const string& username, const string& pass)
        : name(username), password(pass) {}
// những tài khoản được tạo ra sẽ đi cùng với 1 file tên+_friends.txt để lưu danh sách bạn bè 
    void fileFriend() {
        ifstream infile("Friends/" + name + "_friends.txt"); // Personal friend file
        string friendName;
        while (infile >> friendName) {
            if (!isFriend(friendName)) {
                friendname.push_back(friendName);
            }
        }
        infile.close();
    }

    void makeFriend(const string& friendName) {
        if (isFriend(friendName)) {
            cout << friendName << " Đã là bạn của bạn .\n";
            return;
        }

        friendname.push_back(friendName);

        ofstream outfile("Friends/" + name + "_friends.txt", ios::app);
        outfile << friendName << endl;
        outfile.close();
        cout << "Da ket ban voi: " << friendName << "\n";
    }
};

void showFriend(const USER& user) {
    cout << "Danh sach ban cua " << user.name << ":\n";
    const vector<string>& friends = user.getFriends();
    for (const string& fname : friends) {
        cout << "- " << fname << endl;
    }
}

void mutualFriend(const USER& loginUser, const vector<USER>& users) {
    vector<string> mutualFriends;
    const vector<string>& loginUserFriends = loginUser.getFriends();

    for (const string& friendName : loginUserFriends) {
        for (const USER& user : users) {
            if (user.isFriend(friendName) && user.name != loginUser.name) {
                if (find(mutualFriends.begin(), mutualFriends.end(), friendName) == mutualFriends.end()) {
                    mutualFriends.push_back(friendName);
                }
            }
        }
    }

    cout << "Ban chung:\n";
    for (const string& mf : mutualFriends) {
        cout << "- " << mf << endl;
    }
}

void registerUser(vector<USER>& users) {
    cout << "Nhap ten dang nhap moi: ";
    string username;
    cin >> username;

    cout << "Nhap mat khau: ";
    string password;
    cin >> password;

    for (const auto& user : users) {
        if (user.name == username) {
            cout << "Ten dang nhap da ton tai. Vui long chon ten khac.\n";
            return;
        }
    }

    users.push_back(USER(username, password));
    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    cout << "Dang ky thanh cong!\n";
}

USER* loginUser(vector<USER>& users) {
    cout << "Nhap ten dang nhap: ";
    string username;
    cin >> username;
    cout << "Nhap mat khau: ";
    string password;
    cin >> password;

    for (auto& user : users) {
        if (user.name == username && user.password == password) {
            user.fileFriend(); 
            cout << "Dang nhap thanh cong!\n";
            return &user;
        }
    }

    cout << "Ten dang nhap hoac mat khau khong dung.\n";
    return nullptr;
}

void loadUsers(vector<USER>& users) {
    ifstream infile("users.txt");
    string username, password;
    while (infile >> username >> password) {
        users.push_back(USER(username, password));
    }
    infile.close();
}

int main() {
    vector<USER> users;
    loadUsers(users);

    USER* loggedInUser = nullptr;

    while (true) {
        cout << "\n----- Menu -----\n"
             << "1. Dang ky\n"
             << "2. Dang nhap\n"
             << "3. Hien danh sach ban be\n"
             << "4. Hien ban be chung\n"
             << "5. Ket ban\n"
             << "6. Thoat\n"
             << "Lua chon cua ban la: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                loggedInUser = loginUser(users);
                break;
            case 3:
                if (loggedInUser) showFriend(*loggedInUser);
                else cout << "Ban can dang nhap truoc!\n";
                break;
            case 4:
                if (loggedInUser) mutualFriend(*loggedInUser, users);
                else cout << "Ban can dang nhap truoc!\n";
                break;
            case 5:
                if (loggedInUser) {
                    string newFriendName;
                    cout << "Nhap ten nguoi ma ban muon ket ban: ";
                    cin >> newFriendName;
                    loggedInUser->makeFriend(newFriendName);
                } else {
                    cout << "Ban can dang nhap truoc!\n";
                }
                break;
            case 6:
                return 0;
            default:
                cout << "Lua chon khong hop le. Hay thu lai.\n";
                break;
        }
    }
}