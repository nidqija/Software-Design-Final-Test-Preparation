#include <iostream>
#include <string>

using namespace std;


class IPrinter{
    public:
        virtual void print() = 0;
        virtual ~IPrinter() {}
};


class IScanner{
    public:
        virtual void scan() = 0;
        virtual ~IScanner() {}
};


class IFax{
    public:
        virtual void fax() = 0;
        virtual ~IFax() {}
};



class Machine : public IScanner {


    private:
        string name;
        string title;


    public:

        Machine(string n , string t) : name(n) , title(t){}

        void scan() override {
            cout << "Scanning document..."<< name << " - " << title << endl;
        }
};

class FaxMachine : public IFax {


    private:
        string name;
        string title;

    public:
        FaxMachine(string n, string t) : name(n), title(t) {}

        void fax() override {
            cout << "Faxing document..." << name << " - " << title << endl;
        }
};






int main(){
    
    Machine m("HP", "LaserJet Pro");
    m.scan();

    FaxMachine f("Canon", "MultiFunction Fax");
    f.fax();

    return 0;

    

    


}


/*
// A "Fat" Interface: It tries to do everything for everyone.
class IMachine {
public:
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
    virtual ~IMachine() {}
};

// An advanced All-In-One printer can handle this interface fine.
class AllInOnePrinter : public IMachine {
public:
    void print() override { std::cout << "Printing document..." << std::endl; }
    void scan() override { std::cout << "Scanning document..." << std::endl; }
    void fax() override { std::cout << "Faxing document..." << std::endl; }
};

// A simple Economy Printer CANNOT scan or fax.
class EconomyPrinter : public IMachine {
public:
    void print() override { 
        std::cout << "Economy printing..." << std::endl; 
    }

    // Violation: The client is forced to depend on methods it doesn't use.
    void scan() override {
        // Does nothing or throws an error - this is a "Code Smell"
    }

    void fax() override {
        // Does nothing or throws an error
    }
};
*/

