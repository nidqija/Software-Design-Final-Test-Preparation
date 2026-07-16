#include <iostream>


using namespace std;


class IPaymentProcessor {
public:
    virtual void Charge(double amount) = 0;
    virtual ~IPaymentProcessor() {}
};

class IComplianceAuditor {
public:
    virtual void Verify(double amount) = 0;
    virtual ~IComplianceAuditor() {}
};

class USPaymentProcessor : public IPaymentProcessor {
public:
    void Charge(double amount) override {
        cout << "Charging $" << amount << " using US Payment Processor." << endl;
    }
};

class EUPaymentProcessor : public IPaymentProcessor {
public:
    void Charge(double amount) override {
        cout << "Charging €" << amount << " using EU Payment Processor." << endl;
    }
};

class USComplianceAuditor : public IComplianceAuditor {
public:
    void Verify(double amount) override {
        cout << "Verifying US compliance for $" << amount << "." << endl;
    }
};

class EUComplianceAuditor : public IComplianceAuditor {
public:
    void Verify(double amount) override {
        cout << "Verifying EU compliance for €" << amount << "." << endl;
    }
};




class TransactionManager {

    public:
       virtual IPaymentProcessor* createPayment() = 0;
       virtual IComplianceAuditor* createComplianceAuditor() = 0;
       virtual ~TransactionManager() = default;
        
       
};


class USATransactionManager : public TransactionManager {
    public:
        IPaymentProcessor* createPayment() override {
            return new USPaymentProcessor();
        }

        IComplianceAuditor* createComplianceAuditor() override {
            return new USComplianceAuditor();
        }
};


class EUTransactionManager : public TransactionManager {
    public:
        IPaymentProcessor* createPayment() override {
            return new EUPaymentProcessor();
        }

        IComplianceAuditor* createComplianceAuditor() override {
            return new EUComplianceAuditor();
        }
};


void proceedCheckout(TransactionManager* manager , double amount){


    IPaymentProcessor* paymentProcessor = manager->createPayment();
    IComplianceAuditor* complianceAuditor = manager->createComplianceAuditor();

    complianceAuditor->Verify(amount);
    paymentProcessor->Charge(amount);

    delete paymentProcessor;
    delete complianceAuditor;
};











int main(){


    
    TransactionManager* usManager = new USATransactionManager();
    proceedCheckout(usManager, 100.0);
    delete usManager;

    cout << endl;

    TransactionManager* euManager = new EUTransactionManager();
    proceedCheckout(euManager, 85.0);
    delete euManager;

}