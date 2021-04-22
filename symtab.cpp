#include <iostream>
#include "symtab.h"
#include <fstream>


    //read the reserved file and add into map
	void SymbolTable::initReserved()
    {
        std::ifstream myfile("reserved.txt");
        string type;
        int typeNumber;

        //while file has type and number
        while (myfile >> type >> typeNumber)
        {
            shared_ptr<Token> token = make_shared<Token>(static_cast<tokenType>(typeNumber),type);
            this->symMap.insert( std::pair<string,shared_ptr<Token>>(type,token) );     
        }
    {


    
	shared_ptr<Token> SymbolTable::lookupToken(string text)
    {

    }

    //insert into symMap Text and Shared_ptr Token
	void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
    {
        this->symMap.insert( std::pair<string,shared_ptr<Token>>(text,tokenp) );
    }
	void SymbolTable::xref()
    {
        // for(int i = 0 ,i <this->symMap.size() , i++ )
        // {
        //     cout<<this->symMap.at(i).first <<'\t'<<this->symMap.at(i).second <<" "<< endl;
        // }
         for (auto& x: this->symMap)
          {
             cout << x.first <<'\t'<< x.second <<" "<< endl;
          }
    }