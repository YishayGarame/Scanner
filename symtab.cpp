#include <iostream>
#include "symtab.h"
#include <fstream>
#include <typeinfo>


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
    }


	shared_ptr<Token> SymbolTable::lookupToken(string text)
    {
        return symMap[text];
    }

    //insert into symMap Text and Shared_ptr Token
	void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
    {
        symMap[text] =tokenp;
    }
	void SymbolTable::xref()
    {

         for (auto& x: this->symMap)
          {
            if(x.second->getType() == IDENTIFIER)
            {
                shared_ptr<set<int>> lines = x.second->getLines();
                cout << x.first <<'\t';
            // using begin() to print set
                for (auto it = lines->begin(); it != lines->end(); ++it)
                {
                    cout << *it << " ";
                }
                cout << endl;
            }
            
                
          }
    }