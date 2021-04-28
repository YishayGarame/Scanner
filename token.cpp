#include "token.h"
#include "tokenstrings.h"

    //return the token type
    tokenType Token::getType()
    {
        return this->type;
    }

    //return the token text
    string Token::getText()
    {
        return this->text;
    }

    //print the token type and text
    void Token::printToken()
    {
        if(this->type < 258)
        {
        cout <<(char)this->type<<"\t"<<this->text<< endl;
        }
        else
        {
        cout << tokenStrings[this->getType()-258]<<'\t'<<this->text<< endl;
        }
    }

    //add a line the tokens lines
    void varToken::add_line(int l)
     {
         this->lines->insert(l);
     }
    
    //return shared_ptr lines
    shared_ptr<set<int>> varToken::getLines()
     {
         return this->lines;
     }

