#include "scanner.h"


shared_ptr<Token> Scanner::nextToken()
{
    //read the first char of the file
    nextChar();






 // Case: ' ' (Space)
    if(ch == ' ' || ch == '\n') //rrl
    {
        while(nextChar())
        {
            if(ch != ' ' || ch != '\n')
            {
                inputFile.unget();
                break;
            }
        }
    }


    // Case: // || /**/
    if(ch == '/')
    {
        int currentLine = lineno;
        nextChar();
        if(ch == '/')  //  "//"
        {
            while(nextChar())
            {
                if(currentLine != lineno) 
                {
                    inputFile.unget();
                    break;
                }
            }
        }

        //case /**/
        if(ch == '*')
        {
            while(nextChar())
            {
                if(ch == '*' )
                {
                    nextChar(); // in case * is  solid
                    if(ch == '/') // */
                    {
                     break;
                    }
                }
            }
        }
  
    }






    switch (ch)
     {
// each character represents itself
        case ';' : case '{' : case '}' : case ',' : case ':' : \
        case '(' : case ')' : case '[' : case ']' : case '~' : \
        case '*' : case '%' : case '^' : case '?' : case '/':
        return shared_ptr<Token>
        (new Token(static_cast<tokenType>(ch),string(1,ch)));
        break;  

    return shared_ptr<Token>();
    }




//Case Words:

// example: abc_ABC_Zz

if( (ch >= 'a' && ch <='z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
{
    string myVar = string(1,ch);

    // define regex path
    regex validRegVar("^[a-zA-Z_$][a-zA-Z_$0-9]*$");

    while(nextChar())
    {
        // check if myvar + the new ch match to the valid regex path 
        if(regex_match(myVar + ch, validRegVar))
        {
            myVar += ch;
        }
        else
        {
            shared_ptr<Token> token;

            //check if symtab has the new var
            token = symTab.lookupToken(myVar);
            
            if(token == nullptr)
            {
                token = make_shared<varToken>(myVar);
                symTab.insertToken(myVar, token);
            }
            //in case that we got regulat Token the addline function will do nothing
            token->add_line(lineno);
            inputFile.unget();
            return token;
        }
    }

}


//Case Numbers:




}

