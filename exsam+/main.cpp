#include <iostream> 
#include <string>    
#include <windows.h>  
using namespace std;

class Participant {
public:
    virtual string getName() = 0;
    virtual int getMaxRun() = 0;
    virtual int getMaxJump() = 0;
    virtual bool run(int distance) = 0;
    virtual bool jump(int height) = 0;
    virtual ~Participant() {}
};

class Human : public Participant {
private:
    string name;     
    int age;         
    string gender;   
    int maxRun;     
    int maxJump;    

public:
    Human(int age, string gender, int maxRun, int maxJump)
        : name("Марк"), age(age), gender(gender),
        maxRun(maxRun), maxJump(maxJump) {
    }

    string getName() override { return name; }
    int getMaxRun() override { return maxRun; }
    int getMaxJump() override { return maxJump; }

 
    bool run(int distance) override {
        cout << "Человек: " << name
            << " | " << age << " лет | пол: " << gender
            << " | бежит " << distance << " м\n";

 
        return distance <= maxRun;
    }

    bool jump(int height) override {
        cout << "Человек: " << name
            << " | " << age << " лет | пол: " << gender
            << " | прыгает " << height << " м\n";

        return height <= maxJump;
    }
};

class Cat : public Participant {
private:
    string name;  
    string color;   
    int maxRun;
    int maxJump;

public:
    Cat(string name, string color, int maxRun, int maxJump)
        : name(name), color(color),
        maxRun(maxRun), maxJump(maxJump) {
    }

    string getName() override { return name; }
    int getMaxRun() override { return maxRun; }
    int getMaxJump() override { return maxJump; }

    bool run(int distance) override {
        cout << "Кот: " << name
            << " | цвет: " << color
            << " | бежит " << distance << " м\n";

        return distance <= maxRun;
    }

    bool jump(int height) override {
        cout << "Кот: " << name
            << " | цвет: " << color
            << " | прыгает " << height << " м\n";

        return height <= maxJump;
    }
};


class Robot : public Participant {
private:
    string name;    
    string version;  
    int maxRun;
    int maxJump;

public:
    Robot(string name, string version, int maxRun, int maxJump)
        : name(name), version(version),
        maxRun(maxRun), maxJump(maxJump) {
    }

    string getName() override { return name; }
    int getMaxRun() override { return maxRun; }
    int getMaxJump() override { return maxJump; }

    bool run(int distance) override {
        cout << "Робот: " << name
            << " | версия " << version
            << " | бежит " << distance << " м\n";

        return distance <= maxRun;
    }

    bool jump(int height) override {
        cout << "Робот: " << name
            << " | версия " << version
            << " | прыгает " << height << " м\n";

        return height <= maxJump;
    }
};

class Obstacle {
public:
    virtual string getName() = 0;
    virtual bool overcome(Participant* participant) = 0;
    virtual ~Obstacle() {}
};


class Treadmill : public Obstacle {
private:
    int length; 

public:

    Treadmill(int length) : length(length) {}

    
    string getName() override { return "Беговая дорожка"; }


    bool overcome(Participant* participant) override {
        cout << "Препятствие: " << getName()
            << " (" << length << " м)\n";

     
        if (participant->run(length)) {
            cout << "Успех!\n\n";
            return true;   
        }
        else {
            cout << "Не смог пробежать\n\n";
            return false; 
        }
    }
};


class Wall : public Obstacle {
private:
    int height; 

public:
    Wall(int height) : height(height) {}
    string getName() override { return "Стена"; }

    bool overcome(Participant* participant) override {
        cout << "Препятствие: " << getName()
            << " (" << height << " м)\n";

    
        if (participant->jump(height)) {
            cout << "Успех!\n\n";
            return true;  
        }
        else {
            cout << "Не смог перепрыгнуть\n\n";
            return false;  
        }
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Participant* participants[] = {
        new Human(20, "мужской", 500, 2),
        new Cat("Барсик", "рыжий", 300, 4),
        new Robot("R2D2", "2.1", 1000, 1)
    };

    Obstacle* obstacles[] = {
        new Treadmill(200),
        new Wall(2),
        new Treadmill(600),
        new Wall(3)
    };

    for (int i = 0; i < 3; i++) {
        cout << "\n============================\n";
        cout << "Старт участника: "
            << participants[i]->getName() << endl;
        cout << "============================\n";

        for (int j = 0; j < 4; j++) {
            if (!obstacles[j]->overcome(participants[i])) {
                cout << "Участник выбыл из соревнования\n";
                break;
            }
        }
    }

    for (int i = 0; i < 3; i++)
        delete participants[i];

    for (int i = 0; i < 4; i++)
        delete obstacles[i];

    return 0;
}
