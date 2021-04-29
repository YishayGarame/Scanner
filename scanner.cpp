#include "scanner.h"


shared_ptr<Token> Scanner::nextToken()
{
   int bleckspace= 0 ;

    /*
    comment() /* adapt the following code 
    {
        char c, prev = 0; 
        while (c = input())
        {
            if (c == '/' && prev == '*')
                return;
            prev = c;
        }
    }
    */
     //read the first char of the file
    nextChar();

    while((ch == ' ') || (ch == '\t') || (ch == '\n') || ch == ('/') || (ch == 13))
    {
        // if(ch == ' ')
        // {
        //     cout<<"space:"<<endl;
        // }
        // case ' / ' :
        if(ch == '/')
        {
            nextChar();

            //case /*:
            if(ch == '*')
            {
                char prev = 0;

                while(nextChar())
                {
                    if(ch == '/' && prev == '*' )
                    {
                        break;
                    }
                    prev = ch;
                }
                continue;
            }

            if(ch == '/')
            {
                int currentLine = lineno;
                while(nextChar())
                {
                    if(currentLine != lineno) 
                    {
                        break;
                    }
                    continue;
                }
            }
        }
        if((ch == ' ') || (ch == '\t') || (ch == '\n') || ch == ('/') || (ch == 13))
        {
            bleckspace++;
        }
        if(bleckspace>100000)
        {
            break;
        }
         nextChar();
        // if(ch == 13)
        // {
        //     break;
        // }
        // cout<<"ch : "<<(int)ch<<endl;

    }






    //case:

    /*
    "++"			{ return(INC_OP); }
    "--"			{ return(DEC_OP); }
    "->"			{ return(PTR_OP); }
    "&&"			{ return(AND_OP); }
    "||"			{ return(OR_OP); }
    "<="			{ return(LE_OP); }
    ">="			{ return(GE_OP); }
    "=="			{ return(EQ_OP); }
    "!="			{ return(NE_OP); }
    */

    string myStr =string(1,ch);
    nextChar();
    myStr += ch;
    if(myStr == "++") return make_shared<Token>(INC_OP,myStr);
    if(myStr == "--") return make_shared<Token>(DEC_OP,myStr);
    if(myStr == "->") return make_shared<Token>(PTR_OP,myStr);
    if(myStr == "&&") return make_shared<Token>(AND_OP,myStr);
    if(myStr == "||") return make_shared<Token>(OR_OP,myStr);
    if(myStr == "<=") return make_shared<Token>(LE_OP,myStr);
    if(myStr == ">=") return make_shared<Token>(GE_OP,myStr);
    if(myStr == "==") return make_shared<Token>(EQ_OP,myStr);
    if(myStr == "!=") return make_shared<Token>(NE_OP,myStr);
    inputFile.unget();
    inputFile.unget();
    nextChar();






    switch (ch)
     {
    // each character represents itself
        case ';' : case '{' : case '}' : case ',' : case ':' : \
        case '(' : case ')' : case '[' : case ']' : case '~' : \
        case '*' : case '%' : case '^' : case '?' : case '/': case '=': case '&':
        return shared_ptr<Token>
        (new Token(static_cast<tokenType>(ch),string(1,ch)));
        break;  

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

    // example: .7849673 || 33.545E || 1.556e ...
    if((ch >= '0' && ch <= '9') || ch == '.' || (ch =='-') || (ch == '+'))
    {
        string myNum = string(1,ch);
        //nextChar();
        //cout<<"number is "<<ch<<endl;

        //define number regex
        regex numReg("[+-]?([0-9]*[.])?[0-9]*(E|e)?[0-9]*");
    //([0-9]+(\\.)?[0-9](E|e)?[0-9])"))) 
    // int i =1 ;
        while(nextChar())
        {
            while((ch >= '0' && ch <= '9')||(ch == '.') || (ch == 'e') || (ch == 'E'))
            {
                myNum += ch;
                //cout<<"first if---------"<< myNum <<"a"<<endl;
                nextChar();
               //cout << " the i is fir: "<< i << endl;
              // cout<<"the nuber is : " << myNum <<endl;
            }
            break;
            
            // // check if myvar + the new ch match to the valid regex path 
            // if(regex_match(myNum + ch, numReg))
            // {
            //     cout << " the i is sec: "<< i << endl;
            //     myNum += ch;
            //    // cout<<"good------------"<< myNum <<"a"<<endl;
            // }
            // else
            // {
            //     //cout<<"checking---------"<< myNum <<"a"<<endl;
            //     break;
            // }
            // i++;
        }
        inputFile.unget();
        if(myNum == ".")
        {
           // cout << "-----------------------------"<<endl;
            return shared_ptr<Token>()=make_shared<Token>(static_cast<tokenType>('.'),myNum);
        }

        shared_ptr<Token> token;

        if(regex_match(myNum, numReg))
        {
            token = make_shared<Token>(CONSTANT,myNum);
        }
        else
        {
            //continue fro, here the problem is the two dots
            //cout<< "the error:--->>"<<myNum<<endl;
            token = make_shared<Token>(ERROR,myNum);
        }
        return token;
            
    }


    // //Case Numbers:

    // // example: .7849673 || 33.545E || 1.556e ...
    // if((ch >= '0' && ch <= '9') || ch == '.' || (ch =='-') || (ch == '+'))
    // {
    //     string myNum = string(1,ch);
    //     //nextChar();
    //     //cout<<"number is "<<ch<<endl;

    //     //define number regex
    //     regex numReg("[+-]?([0-9]*[.])?[0-9]*(E|e)?[0-9]*");
    // //([0-9]+(\\.)?[0-9](E|e)?[0-9])"))) 
    // int i =1 ;
    //     while(nextChar())
    //     {
    //         if((ch == '.') || (ch == 'e') || (ch == 'E')|| (ch >= '0' && ch <= '9'))
    //         {
    //             myNum += ch;
    //             //cout<<"first if---------"<< myNum <<"a"<<endl;
    //             nextChar();
    //             cout << " the i is fir: "<< i << endl;
    //         }
            
    //         // check if myvar + the new ch match to the valid regex path 
    //         if(regex_match(myNum + ch, numReg))
    //         {
    //             cout << " the i is sec: "<< i << endl;
    //             myNum += ch;
    //            // cout<<"good------------"<< myNum <<"a"<<endl;
    //         }
    //         else
    //         {
    //             //cout<<"checking---------"<< myNum <<"a"<<endl;
    //             break;
    //         }
    //         i++;
    //     }
    //     inputFile.unget();
    //     // if(myNum == ".")
    //     // {
    //     //     cout << "-----------------------------"<<endl;
    //     //     return shared_ptr<Token>()=make_shared<Token>(static_cast<tokenType>('.'),myNum);
    //     // }

    //     shared_ptr<Token> token;

    //     if(regex_match(myNum, numReg))
    //     {
    //         token = make_shared<Token>(CONSTANT,myNum);
    //     }
    //     else
    //     {
    //         //continue fro, here the problem is the two dots
    //         //cout<< "the error:--->>"<<myNum<<endl;
    //         token = make_shared<Token>(ERROR,myNum);
    //     }
    //     return token;
            
    // }



    //case: 'e' || 'y' .....

    if(ch == '\'')
    {
        regex charReg("\'[^\']\'"); 
        string myChar = string(1,ch);
        

        // while loop until we get ' 
    while(nextChar())
    {
        //cout<<"my char "<<myChar<<endl;
        myChar += ch;
        //cout<<"my char after "<<myChar<<endl;

        
        //we check if we got the second ' and than we'll check mycahr
        if(ch = '\'')
        {
            break;
        }
    }
        //cout<<"my char after after "<<myChar<<endl;

        shared_ptr<Token> token;
        nextChar();
        myChar += ch;
        //if mychar match to the regex will return constant as required 
        if(regex_match(myChar,charReg))
        {
            token = make_shared<Token>(CONSTANT,myChar.substr(1,1));
        }
        else
        {
            token = make_shared<Token>(ERROR,myChar.substr(1,1)) ;
        }
        return token;
    }

    //case: "aaa" || "bbb" .....

    if(ch == '"')
    {
        regex charReg("\"[^\"]*\""); 
        string myChar = string(1,ch);
        

            // while loop until we get ' 
        while(nextChar())
        {
            myChar += ch;

            //we check if we got the second ' and than we'll check mycahr
            if(ch == '"')
            {
                break;
            }

        }
            
            shared_ptr<Token> token;
            int mycharlength = myChar.length();
            //if mychar match to the regex will return constant as required 
            if(regex_match(myChar,charReg))
            {
                token = make_shared<Token>(STRING_LITERAL,myChar.substr(1,mycharlength-2));
            }
            else
            {
                token = make_shared<Token>(ERROR,myChar.substr(1,mycharlength-2)) ;
            }
            return token;
    }

    return nullptr;

}

