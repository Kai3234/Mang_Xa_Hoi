#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cstdlib> //rng
#include <ctime>  
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;



void show_ad() 
{
    string ads[] = 
    {
        "\n-----   [AD]: Dep Min Khong Ti Vet Cung Crystal Glow! :[AD]   -----",
        "\n-----   [AD]: Moi Luc Moi Noi, RelaxPlus Mang Lai Giay Phut! :[AD]   -----",
        "\n-----   [AD]: Huong Vi Thanh Loc Tu SlimTea - Co The Thon Gon Tu Ben Trong! :[AD]   -----",
        "\n-----   [AD]: Kham Pha Am Thanh Dinh Cao Cung SoundMax Pro! :[AD]   -----",
        "\n-----   [AD]: Duolingo - Cach Hoc Ngoai Ngu Tot Nhat The Gioi! :[AD]   -----"
    };

    int ad_index = rand() % 5;  
    cout << ads[ad_index] << endl;
}


class COMMENT
{
protected:
    string user;
    string content;
public:
    COMMENT(string name, string cont)
    {
        user = name;
        content = cont;
    }
    string get_comment_user()
    {
        return user;
    }
    string get_comment_content()
    {
        return content;
    }
};


class POST
{
protected:
    string idpost;
    string user;
    string content;
    
public:
    vector<COMMENT> comments;

    POST(int order, string name, string cont)
    {
        idpost = to_string(order);
        user = name;
        content = cont;
    }

    string get_content()
    {
        return content;
    }

    void showComment()
    {
        cout<<"     +) Binh luan:"<<endl;
        for(int i = 0; i < comments.size(); i++)
        {
            cout<<"     ["<<comments[i].get_comment_user()<<"]: ";
            cout<<comments[i].get_comment_content()<<endl;
        }
        cout<<endl;
    }

    void filecomment()
    {
        fstream fcomment;
        fcomment.open("Posts/Comments/" + user + idpost + ".txt", ios::in | ios::out);
        if(!fcomment)
        {
            fcomment.open("Posts/Comments/" + user + idpost + ".txt", ios::in | ios::out | ios::trunc);
        }
        else
        {
            fcomment.seekg(0, ios::beg);
            string name;
            string cont;
            while (getline(fcomment, name) && getline(fcomment, cont))
            {   
                COMMENT c(name, cont);
                comments.push_back(c);
            }
        }
        fcomment.close();
    }
};


class FRIEND 
{
protected:
    vector<string> friendlist; 

public:
    bool isFriend(string& name)  
    {
        return find(friendlist.begin(), friendlist.end(), name) != friendlist.end();
    }

    vector<string>& getFriends() 
    {
        return friendlist;
    }
};

class USER: public FRIEND
{
protected:
    string name;
    string pass;
public:
    vector<POST> posts;

    USER(string username, string passcode)
    {
        name = username;
        pass = passcode;
    }

    string get_name()
    {
        return name;
    }
    
    string get_pass()
    {
        return pass;
    }

    void filePost()
    {
        fstream fpost;
        
        fpost.open("Posts/" + name + ".txt", ios::in | ios::out);
        if(!fpost)
        {
            fpost.open("Posts/" + name + ".txt", ios::in | ios::out | ios::trunc);
        }
        else
        {
            string cont;
            while (getline(fpost, cont))
            {   
                POST p(posts.size(), name, cont);
                posts.push_back(p);
            }
        }
        fpost.close();
        for (int i = 0; i < posts.size(); i++)
        {
            posts[i].filecomment();
        }
        
    }

    void addPost()
    {
        cout<<"--   Bai viet "<<posts.size() + 1<<"   --\n";
        cout<<"-- Nhap noi dung bai viet: ";
        string cont;
        cin.ignore(1); getline(cin, cont);

        POST curPost(posts.size(), name, cont);
        posts.push_back(curPost);

        fstream fpost;
        fpost.open("Posts/" + name + ".txt", ios::in | ios::out | ios::app);
        if(!fpost)
        {
            fpost.open("Posts/" + name + ".txt", ios::in | ios::out | ios::trunc);
        }    
        fpost<<cont<<"\n";
        fpost.close();
    }

    void addComment(USER *loginUser, int postOrder)
    {
        cout<<"-- Nhap noi dung binh luan: ";
        string cont;
        cin.ignore(1); getline(cin, cont);

        COMMENT newCom(loginUser->get_name(), cont);
        posts[postOrder].comments.push_back(newCom);

        fstream fcomment;
        string idpo = to_string(postOrder);
        fcomment.open("Posts/Comments/" + name + idpo + ".txt", ios::in | ios::out | ios::app);
        if(!fcomment)
        {
            fcomment.open("Posts/Comments/" + name + idpo + ".txt", ios::in | ios::out | ios::trunc);
        }
        fcomment<<loginUser->get_name()<<"\n";
        fcomment<<cont<<"\n";
        fcomment.close();  
    }

    void showPost(USER *loginUser)
    {
        int postOrder = 0;
        int m = 0;
        if (posts.size() > 0)
        {
            while(m != 4)
            { 
                int random_number = rand() % 2 + 1;
                if (random_number == 1) 
                {
                    show_ad();
                }

                cout<<"\n--   Bai viet "<<postOrder + 1<<"   --"<<endl;
                cout<<"["<<get_name()<<"]"<<endl;                        
                cout<<posts[postOrder].get_content()<<endl;
                posts[postOrder].showComment();

                cout<<"--   Lua chon   --"<<endl;
                cout<<"1. Binh luan"<<endl<<"2. Truoc"<<endl<<"3. Sau"<<endl<<"4. Thoat"<<endl;
                cout<<"--   Nhap so de lua chon: "; 
                cin>>m;

                switch (m)
                {
                case 1:
                {
                    addComment(loginUser, postOrder);
                    break;
                }
                
                case 2:
                {
                    if(postOrder > 0)
                    {
                        postOrder--;
                    }
                    break;
                } 

                case 3:
                {
                    if(postOrder < posts.size() - 1)                    
                    {
                        postOrder++;
                    }
                    break;
                } 

                case 4:
                    cout<<"--   Dang tro ve   --\n";
                    break;
                }
            }
        }
        else
        {
            cout<<"\n--   ["<<name<<"] khong co bai viet nao!   --"<<endl;
        }   
    } 

    string getChatFileName(USER& chatUser) 
    {
        string filename = this->name + "_" + chatUser.name + ".txt";
        if (this->name > chatUser.name) {
            filename = chatUser.name + "_" + this->name + ".txt";
        }
        return "Messages/" + filename;
    }

    void typeMessage(USER& chatUser) 
    {
        string filename = getChatFileName(chatUser);
        ofstream outfile(filename, ios::app);
        if (!outfile) 
        {
            cerr << "Khong the mo file: " << filename << endl;
            return;
        }

        string message;
        cout << "[" << this->name << "]: ";
        cin.ignore(1);
        getline(cin, message);

        outfile << "[" << this->name << "]: " << message << endl;
        outfile.close();
    }

    void showMessage(USER& chatUser) 
    {
        string filename = getChatFileName(chatUser);
        ifstream infile(filename);

        cout << "\n---   Cuoc tro chuyen cung [" << chatUser.name << "]  --\n";

        string line;
        while (getline(infile, line)) 
        {
            cout << line << endl;
        }
        infile.close();
    }

    void fileFriend() 
    {
        ifstream infile("Friends/" + name + "_friends.txt"); 
        string friendName;
        while (infile >> friendName) 
        {
            if (!isFriend(friendName)) 
            {
                friendlist.push_back(friendName);
            }
        }
        infile.close();
    }

    void makeFriend(string friendName, USER* friendUser) 
    {
        if (isFriend(friendName)) 
        {
            cout << "--   Cac ban da la ban be voi nhau    --\n";
            return;
        }

        friendlist.push_back(friendName);
        friendUser->friendlist.push_back(name);

        ofstream outfile1("Friends/" + name + "_friends.txt", ios::app);
        outfile1 << friendName << endl;
        outfile1.close();

        ofstream outfile2("Friends/" + friendName + "_friends.txt", ios::app);
        outfile2 << name << endl;
        outfile2.close();

        cout << "\n--   Thanh cong ket ban voi [" << friendName << "]   --\n";
    }
};

//đăng nhập, đăng ký
bool read_User(vector<USER>& users) 
{
    ifstream file("User.txt"); 
    if (!file) 
    {  
        cerr << "Error: Could not open credentials file." << endl;
        return false;
    }
    string line, name, pass;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        iss >> name >> pass;  
        users.push_back({name, pass});  
    }
    file.close(); 
    return true;
}

bool verify_login(string input_name, string input_pass, vector<USER> users) 
{
    for (auto &user : users) 
    {
        if (user.get_name() == input_name && user.get_pass() == input_pass) {
            return true;  
        }
    }
    return false;  
}

void sign_up(vector<USER> &users) 
{
    string new_name, new_pass;
    cout << "--   Dang ky   --" << std::endl;
    cout << "--   Nhap ten dang ky: ";
    cin >> new_name;

    for (auto &user : users) 
    {
        if (user.get_name() == new_name) 
        {
            cout<<"--   Ten nguoi dung da ton tai   --"<<endl;
            return;  
        }
    }
    cout << "--   Nhap mat khau: ";
    cin >> new_pass;

    USER p(new_name, new_pass);
    users.push_back(p);
    
    ofstream file("User.txt", ios::app);
    if (file) 
    {
        file << new_name << " " << new_pass << "\n";
        cout << "--   Dang ky thanh cong!" << endl;
        cout<<"--   Nhan bat ki phim gi de tiep tuc   --";
        getch();
        system("cls");
    } 
    else 
    {
        cerr << "--   Khong the mo User.txt de luu tai khoan   --" << endl;
    }
    file.close();
}


//tìm kiếm
string toLower(const string& str) 
{
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string trim(const string& str) 
{
    size_t first = str.find_first_not_of(" \t\n");
    size_t last = str.find_last_not_of(" \t\n");
    if (first == string::npos || last == string::npos) 
    {
        return "";
    }
    return str.substr(first, last - first + 1);
}


USER* searchUsers(vector<USER>& users, string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_name() == username)
        {
            return &users[i];
        }
    }
    return nullptr;
}

void optionUser(USER* loginUser, USER* selectedUser)
{
    int action;
    while (action != 4)
    {
        cout << "\n--   User: [" << selectedUser->get_name() << "]   --\n";
        cout << "1. Xem bai viet\n";
        cout << "2. Tin nhan\n";
        cout << "3. Ket ban\n";
        cout << "4. Thoat\n";
        cout << "--   Nhap so de lua chon: ";
        cin >> action;
        switch (action)
        {
        case 1:
            selectedUser->showPost(loginUser);
            break;
        case 2:
        {
            int choicemes = 0;
            while (choicemes != 2)
            {
                loginUser->showMessage(*selectedUser);
                cout<<"\n--   Lua chon:    --";
                cout<<"\n1. Nhan tin";
                cout<<"\n2. Tro ve";
                cout<<"\n--   Nhap so de lua chon: ";                      
                cin>>choicemes;
                switch (choicemes)
                {
                case 1:
                    loginUser->typeMessage(*selectedUser);
                    break;

                case 2:
                    cout << "\n--   Dang ket thuc   --\n";
                    break;
            
                default:
                    cout << "\n--   Lua chon khong hop le!   --\n";
                    break;
                }
                
            }          
            break;
        }
        case 3:
            loginUser->makeFriend(selectedUser->get_name(), selectedUser);
            break;
        case 4:
            cout << "\n--   Dang ket thuc   --\n";
            break;
        
        default:
            cout << "\n--   Lua chon khong hop le!   --\n";
            break;
        }

    }

}

void chooseUser(USER* loginUser, vector<string> listUser, vector<USER>& users)
{
    for (size_t i = 0; i < listUser.size(); ++i) 
    {
        cout << i + 1 << ". [" << listUser[i] << "]\n";
    }
    cout<<endl<<listUser.size() + 1<<". Thoat";
    
    int selectedIndex;
    while (selectedIndex != listUser.size() + 1)
    {
        cout << "\n--   Nhap STT de lua chon nguoi dung: ";
        cin >> selectedIndex;
        if (selectedIndex >= 1 && selectedIndex <= listUser.size()) 
        {     
            USER* selectedUser = searchUsers(users, listUser[selectedIndex - 1]);      
            optionUser(loginUser, selectedUser);
            return;
        }
        else if(selectedIndex == listUser.size() + 1)
        {
            cout<<"\n--   Dang tro ve   --\n";
        }
        else 
        {
            cout << "\n--   Lua chon khong hop le!   --\n";
        }
    }   
}

void searchforUsername(string& word, vector<USER>& users, USER* loginUser) 
{
    string lowerWord = toLower(trim(word));

    if (lowerWord.empty()) 
    {
        cout << "--   Tu tim kiem duoc nhap khong hop le   --\n";
        return;
    }

    vector<string> matchingUsers;
    for (auto& user : users) 
    {
        string lowerUsername = toLower(user.get_name());
        if (lowerUsername.find(lowerWord) != string::npos && lowerUsername != toLower(loginUser->get_name())) 
        {
            matchingUsers.push_back(user.get_name());
        }
    }

    if (matchingUsers.empty()) 
    {
        cout << "--   Khong co ket qua tim kiem thich hop   --\n";
        return;
    }
    else 
    {
        cout << "--   Ket qua tim kiem nguoi dung   --\n";
        
        chooseUser(loginUser, matchingUsers, users);
        
    }
}

void everyonePost(USER* loginUser, vector<USER>& users)
{
    int choice3 = 0;
    while (choice3 != 4)
    {
        int iuser = rand() % users.size();
        if(users[iuser].posts.size() == 0 || users[iuser].get_name() == loginUser->get_name())
        {
            continue;
        }
            
        int random_number = rand() % 2 + 1; 
        if (random_number == 1) 
        {
            show_ad();
        }
        
        int ipost = rand() % users[iuser].posts.size();
        cout<<"\n--   Bai viet "<<ipost + 1<<"   --"<<endl;
        cout<<"["<<users[iuser].get_name()<<"]"<<endl;                        
        cout<<users[iuser].posts[ipost].get_content()<<endl;
        users[iuser].posts[ipost].showComment();

        cout<<"--   Lua chon   --"<<endl;
        cout<<"1. Xem nguoi dang"<<endl;
        cout<<"2. Binh luan"<<endl;
        cout<<"3. Tiep"<<endl;
        cout<<"4. Thoat"<<endl;
        cout<<"--   Nhap so de lua chon: "; 
        cin>>choice3;
        switch (choice3)
        {

        case 1:
        {
            optionUser(loginUser, &users[iuser]);
            break;
        }
        
        case 2:
        {
            users[iuser].addComment(loginUser, ipost);
            break;
        } 
        case 3:
        {
            break;
        } 
        case 4:
            cout<<"--   Dang tro ve   --\n";
            break;
        }
    }
}

//Friend
void showFriend(USER* loginUser, vector<USER>& users) 
{
    vector<string> friends = loginUser->getFriends();
    if(friends.size() == 0)
    {
        cout<<"\n--   Ban chua ket ban voi ai   --\n";
        return;
    }

    cout << "\n--   Danh sach ban be cua [" << loginUser->get_name() << "]   --\n";
    chooseUser(loginUser, friends, users);
}

void showMutualFriend(USER* loginUser, vector<USER>& users) 
{
    vector<string> mutualFriends;
    vector<string>& loginUserFriends = loginUser->getFriends();

    for (string& friendName : loginUserFriends) 
    {
        for (USER& user : users) 
        {
            if (user.isFriend(friendName) && user.get_name() != loginUser->get_name()) 
            {
                if(find(loginUserFriends.begin(), loginUserFriends.end(), user.get_name()) == loginUserFriends.end() && find(mutualFriends.begin(), mutualFriends.end(), user.get_name()) == mutualFriends.end())
                {
                    mutualFriends.push_back(user.get_name());
                }       
            }
        }
    }

    if(mutualFriends.size() == 0)
    {
        cout<<"\n--   Ban khong co ban chung voi nguoi dung nao   --\n";
        return;
    }

    cout << "\n--   Nhung nguoi ban co the biet   --\n";
    chooseUser(loginUser, mutualFriends, users);
}



int main()
{
    srand(time(0));
    vector<USER> users;
    read_User(users);
    for(int i = 0; i < users.size(); i++)
    {
        users[i].fileFriend();
        users[i].filePost();
    }
    
    int n = 0;
    while (1)
    {
        cout<<"\n----------<   Chao mung den ung dung   >----------"<<endl;
        cout<<"1. Dang nhap"<<endl;
        cout<<"2. Dang ky"<<endl;;
        cout<<"3. Thoat"<<endl;
        cout<<"--   Nhap so de lua chon (1, 2, 3): ";
        cin>>n; cout<<endl;
        switch (n)
        {
            case 1:
            {
                string input_name, input_pass;
                cout << "--   Dang nhap   --" << endl;
                cout << "--   Nhap ten dang nhap: ";
                cin >> input_name;
                cout << "--   Nhap mat khau: ";
                cin >> input_pass;

                if (verify_login(input_name, input_pass, users)) 
                {
                    cout << "\n--   Dang nhap thanh cong!   --" << endl;
                    cout<<"--   Nhan bat ki phim gi de tiep tuc   --\n";
                    getch();
                    system("cls");
                } 
                else 
                {
                    cout << "--   Ten nguoi dung hoac mat khau sai!   --" << endl;
                    break;
                }

                USER *loginUser = searchUsers(users, input_name);   
                int choice = 0;
                while (choice != 8)
                {
                    cout<<"\n----------   Menu User: ["<<loginUser->get_name()<<"]:   ----------"<<endl; 
                    cout<<"1. Dang bai"<<endl;
                    cout<<"2. Bai viet cua minh"<<endl;
                    cout<<"3. Xem bai viet cua moi nguoi"<<endl;
                    cout<<"4. Ban be"<<endl;
                    cout<<"5. Goi y ban be"<<endl;
                    cout<<"6. Tim kiem nguoi dung"<<endl;
                    cout<<"7. Nguoi la nhan tin voi ban"<<endl;
                    cout<<"8. Dang xuat"<<endl;
                    cout<<"--   Nhap lua chon cua ban: ";
                    cin>>choice;
                    switch (choice)
                    {
                    case 1: //Đăng bài
                    {
                        cout<<endl;
                        loginUser->addPost();
                        break;
                    }

                    case 2: //Bài viết của mình
                    {
                        loginUser->showPost(loginUser);
                        break;
                    }

                    case 3: //Mọi người
                    {
                        everyonePost(loginUser, users);
                        break;
                    }  

                    case 4: //Bạn bè
                    {
                        showFriend(loginUser, users);
                        break;
                    }
                        
                    case 5:  //gợi ý bạn bè
                    {
                        showMutualFriend(loginUser, users);     
                        break;
                    }

                    case 6: //tìm kiếm
                    {
                        cout<<"\n--   Tim kiem nguoi dung   --"<<endl;
                        cout<<"--   Nhap tu tim kiem: ";
                        if (cin.peek() == '\n') 
                            cin.ignore();
                        string word;
                        getline(cin, word);
                        cout<<endl;

                        searchforUsername(word, users, loginUser);
                        break;
                    }

                    case 7: //Tin nhắn từ người lạ
                    {

                    }

                    case 8: // đăng xuất
                    {
                        cout<<"\n--   Tam biet ["<<loginUser->get_name()<<"]!   --\n";
                        cout<<"--   Nhan bat ki phim gi de tiep tuc   --\n";
                        getch();
                        system("cls");
                        break;
                    }
                    default:
                        cout<<"--   Lua chon khong hop le!   --";
                        break;
                    }
                }
                break;
            }

            case 2:
            {
                sign_up(users);
                break;
            }

            case 3:
            {
                cout<<"--   Thank you and goodbye!   --\n\n";
                return 0;
            }
                
            default: 
                cout<<"--   Lua chon khong hop le!   --\n";
                break;
    }
    }
}
