

/*#include <iostream>
#include <string>
#include <vector>

class WorkerManager {
private:
    std::string name;
    double hourlyRate;
    int hoursWorked;

public:
    WorkerManager(std::string n, double rate, int hours) 
        : name(n), hourlyRate(rate), hoursWorked(hours) {}

    // Responsibility 1: Business Logic / Data
    std::string getName() { return name; }

    // Responsibility 2: Payroll Calculation
    double calculatePay() {
        return hourlyRate * hoursWorked;
    }

    // Responsibility 3: Report Generation (Presentation)
    void printPerformanceReport() {
        std::cout << "Performance Report for: " << name << std::endl;
        std::cout << "Efficiency Rating: High" << std::endl;
    }

    // Responsibility 4: Persistence (Saving to a file/DB)
    void saveToDatabase() {
        std::cout << "Saving " << name << " records to database..." << std::endl;
        // Database logic here
    }
};*/



#include <iostream>
#include <string>

using namespace std;


class Worker {

    private:
        string name;
        double hourlyRate;
        int hoursWorked;


    public:
        Worker(string n , double h , int w) : name(n) , hourlyRate(h) , hoursWorked(w){}


        string getName() { 
            return name; 
        }





};


class Pay{
    

    private:
        double hourlyRate;
        int hoursWorked;
        Worker work;


    public:

        Pay(double h , int w , Worker worker ) : hourlyRate(h) , hoursWorked(w) , work(worker){}

        double calculatePay() {
            return hourlyRate * hoursWorked;
        }

};


class Report{

    private:
       Worker work;
       Pay pay;

    public:
      
        Report(Worker worker, Pay payment) : work(worker), pay(payment) {}

        void printPerformanceReport() {
            cout << "Performance Report for: " << work.getName() << endl;
            cout << "Efficiency Rating: High" << endl;
        }

};



class Database{


    private:
       Worker work;
       Pay pay;



    public:
      
        Database(Worker worker, Pay payment) : work(worker), pay(payment) {}

        void saveToDatabase() {
            cout << "Saving " << work.getName() << " records to database..." << endl;
            // Database logic here
        }
};






int main(){
    Worker worker1("John Doe", 20.0, 40);
    Pay pay1(20.0, 40, worker1);
    Report report1(worker1, pay1);
    Database db1(worker1, pay1);

    cout << "Worker: " << worker1.getName() << endl;
    cout << "Total Pay: $" << pay1.calculatePay() << endl;
    report1.printPerformanceReport();
    db1.saveToDatabase();


    return 0;

}


