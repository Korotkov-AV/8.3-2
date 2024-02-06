// 8.3-2.cpp : 



#include <iostream>
#include <fstream>
#include <list>

enum event {
    warning,
    error,
    fatalError
};

void printConsole(const std::string& message) {
    std::cout << message << std::endl;
}

void printFile(const std::string& message) {
    std::ofstream file("text.txt");
    file << message << std::endl;
    file.close();
}

class Observer {
protected:
    std::string message;
public:
    Observer() {
        std::cout << "hello, im observer" << std::endl;
    };
    virtual void update(const std::string& mes, event e) {};
    virtual void printevent() const {};
    ~Observer() {
        std::cout << "bye, i was observer" << std::endl;
    }

};

class ObsOnWarning : public Observer {
public:
    void update(const std::string& mes, event e) override {
        if (e != event::warning) return;
        message = mes;
        printevent();
    }
    void printevent() const override {
        std::cout << "im processing warning...   ";
        printConsole(message);
    };
};

class ObsOnError : public Observer {
public:
    void update(const std::string& mes, event e) override {
        if (e != event::error) return;
        message = mes;
        printevent();
    }
    void printevent() const override {
        std::cout << "im processing error...   ";
        printFile(message);
    };
};

class ObsOnFatalError : public Observer {
public:
    void update(const std::string& mes, event e) override {
        if (e != event::fatalError) return;
        message = mes;
        printevent();
    }
    void printevent() const override {
        std::cout << "im processing fatal error...   ";
        printConsole(message);
        printFile(message);
    };
};


class subject {
    std::list<Observer*> list_observer_;
public:
    subject() {
        std::cout << "hello, im subject" << std::endl;
    }
    void smtHappend(const std::string& message, event e) {
        std::list<Observer*>::iterator iterator = list_observer_.begin();
        while (iterator != list_observer_.end()) {
            (*iterator)->update(message, e);
            ++iterator;
        }
    };
    void Attach(Observer* observer) {
        list_observer_.push_back(observer);
    }
    void Detach(Observer* observer) {
        list_observer_.remove(observer);
    }
    ~subject() {
        std::cout << "bye, i was subject" << std::endl;
    }
};




int main() {
    subject program;

    ObsOnWarning obs3;
    ObsOnError obs1;
    ObsOnFatalError obs2;

    program.Attach(&obs1);
    program.Attach(&obs2);
    program.Attach(&obs3);


    program.smtHappend("its warning", event::warning);

    program.Detach(&obs2);

    program.smtHappend("its fatal error", event::fatalError);

    std::cout << "this is end of main' part" << std::endl;
}