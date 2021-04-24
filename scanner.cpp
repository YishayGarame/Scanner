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

    switch (ch) {
// each character represents itself
case ';' : case '{' : case '}' : case ',' : case ':' : \
case '(' : case ')' : case '[' : case ']' : case '~' : \
case '*' : case '%' : case '^' : case '?' : case '/':
return shared_ptr<Token>
(new Token(static_cast<tokenType>(ch),string(1,ch)));
break;

        

    return shared_ptr<Token>();
}
}

