#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
#include "stock.h"
#include "foreign_account.h"

class PersonAccount :virtual public Account, public stock{
private:
    string name;
    vector<ForeignAccount*> foreign_accounts;

public:
    PersonAccount(string name_) :Account(name_),stock(name_){
        name=name_;
    }

    ~PersonAccount() {
        for(int i=0; i<foreign_accounts.size();i++)
            delete foreign_accounts[i];
    }

    ForeignAccount* access_foreign_account(string currency){
        for(int i=0; i<foreign_accounts.size();i++){
            if(foreign_accounts[i]->get_currency()==currency)
                return foreign_accounts[i];
        }

        cout<<name<<"\'s ";
        ForeignAccount* new_account=new ForeignAccount(currency,name);
        foreign_accounts.push_back(new_account);
        return new_account;
    }


    void add_foreign(string);
    void show_all() const;
    float show_foreign_accounts() const;
    void transfer_to_stock(float);
    void transfer_to_basic(float);
};

inline void PersonAccount::transfer_to_stock(float amount){
    if(Account::total_asset()>=amount){
        withdraw(amount);
        deposit(amount);
        cout<<"Transfer "<<amount<<"K from Basic Account to Stock Account.\n";
    }

    else{
        cout<<"Insufficient balance in Basic Account for the operation of transfer.\n";
    }
}


inline void PersonAccount::transfer_to_basic(float amount){
    if(stock::total_asset()>=amount){
        withdraw(amount);
        deposit(amount);
        cout<<"Transfer "<<amount<<"K from Stock Account to Basic Account.\n";
    }

    else{
        cout<<"Insufficient balance in Stock Account the operation of transfer.\n";
    }
}

inline float PersonAccount::show_foreign_accounts() const{
    float total=0;
    for (int i=0; i<foreign_accounts.size();i++) {
        foreign_accounts[i]->show_balance();
        float tmp=foreign_accounts[i]->get_value_twd();
        total+=tmp;
        cout<<"TWD value: "<<tmp<<"\n\n";
    }

    return total;
}

inline void PersonAccount::show_all() const{
    cout<<"Name: "<<name<<"\n";
    Account::show_balance();
    stock::show_balance();
    stock::show();

    float foreign_asset=show_foreign_accounts();
    float basic_asset=Account::total_asset();
    float stock_asset=stock::total_asset();
    cout<<"Total Asset: "<<basic_asset+stock_asset+foreign_asset<<"K\n\n";
}
#endif // PERSON_H_INCLUDED
