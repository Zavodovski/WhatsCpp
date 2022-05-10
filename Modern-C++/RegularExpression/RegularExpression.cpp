#include<iostream>
#include<string>
#include<regex>
using namespace std;

/*
 *  Regular Expression: a regular expression is a specific pattern that provides concise and flexible means
        to "match" strings of text, such as particular characters, words, or patterns of characters. -- wikipedia
 */




int main()
{
    
    //regular expression basic grammar

    // string str;
    // while(true)
    // {
    //     cin >> str;

        

        //regex e("abc");

        //regex e("abc", regex_constants::icase); //ignore the letter case
        //regex e("abc.", regex_constants::icase);  // .  Any character except newline
        //regex e("abc?", regex_constants::icase);  // ?   0 or 1 preceding character
        //regex e("abc*", regex_constants::icase);  // *   0 or more preceding character
        //regex e("abc+", regex_constants::icase);  // ?   1 or more preceding character
        //regex e("ab[cd]*", regex_constants::icase);  // [...]   Any character inside the square brackets
        //regex e("ab[^cd]*", regex_constants::icase);  // [...]   Any character not inside the square brackets
        //regex e("ab[cd]{3}", regex_constants::icase);  // [...]   Any character inside the square brackets exact 3 appearances
        //regex e("ab[cd]{3,}", regex_constants::icase);  // [...]   Any character inside the square brackets exact 3 or more appearances
        //regex e("ab[cd]{3,5}", regex_constants::icase);  // [...]   Any character inside the square brackets exact 3, 4, 5 appearances
        //regex e("abc|de[fg]");  // | Or
        //regex e("abc|de[\\}fg]");  // \ escape operator
        //regex e("(abc)de+\\1");  // \1 First group
        //regex e("(ab)c(de+)\\2\\1");  // \2 Second group \1 First group
        //regex e("[[:w:]]+@[[:w:]]+\\.com");  // [[:w:]] 
        
        //bool match = regex_match(str, e);

        //regex e("^abc.", regex_constants::icase);  //abc appears at the beginning
        //regex e("abc.$", regex_constants::icase);  //abc appears at the end
        //regex e("^abc.+");

        //regex e("^abc.+", regex_constants::grep);  // in grep grammar, + is a regular character, does not have the meaning of one or more preceding character

        //bool match = regex_search(str, e);

        /*
         *  std::match_results<> store the detailed matches
         *  
         *  smatch     Detailed match in string
         * 
         *  smatch m
         *  m[0].str()  The entire match(same with m.str(), m.str(0))
         *  m[1].str()  The substring that matches the first group (same with m.str(1))
         *  m[2].str()  The substring that matches the second group
         *  m.prefix()  Everything before the first matched character
         *  m.suffix()  Everything after the last matched character
         */
/*
        smatch m; //typedef std::match_results<string>
        regex e("([[:w:]]+)@([[:w:]]+)\\.com");

        bool match = regex_search(str, m, e);

        cout << "m.size() " << m.size() << endl;

        for(int n = 0; n < m.size(); n ++)
        {
            cout << "m[" << n << "]: str()=" << m[n].str() << endl; 
            cout << "m[" << n << "]: str()=" << m.str(n) << endl;
            cout << "m[" << n << "]: str()=" << *(m.begin() + n) << endl;
        }

        cout << "m.prefix().str():" << m.prefix().str() << endl;
        cout << "m.suffix.str():" << m.suffix().str() << endl;

        cout << (match ? "Matched" : "Not matched") << endl << endl;
    }
*/

    //regex_iterator
    /*
    string str = "boq@gmail.com;  boqian@hotmail.com;;  bo_qian2000@163.com";

    regex e("([[:w:]]+)@([[:w:]]+)\\.com");

    sregex_iterator pos(str.cbegin(), str.cend(), e);
    sregex_iterator end;  //default constructor of a iterator defines past-the-end iterator so it's the end

    for(; pos != end; pos ++)
    {
        cout << "Matched: " << pos->str(0) << endl;
        cout << "user name: " << pos->str(1) << endl;
        cout << "Domain: " << pos->str(2) << endl;
        cout << endl;
    }

    cout << "===================\n\n";
    */

    string str = "boq@gmail.com;  boqian@hotmail.com;;  bo_qian2000@163.com";

    regex e("([[:w:]]+)@([[:w:]]+)\\.com");
    //regex e("([[:w:]]+)@([[:w:]]+)\\.com", regex_constants::grep|regex_constants::icase);


    //sregex_token_iterator pos(str.cbegin(), str.cend(), e);     //extract the entire matched string
    //sregex_token_iterator pos(str.cbegin(), str.cend(), e, 0);  //default 0 so it's the same as the last line
    //sregex_token_iterator pos(str.cbegin(), str.cend(), e, 1);  //extract the first group
    //sregex_token_iterator pos(str.cbegin(), str.cend(), e, 2);  //extract the second group
    sregex_token_iterator pos(str.cbegin(), str.cend(), e, -1); //extract the part of string that is not matched by the regular expression
    sregex_token_iterator end;  //default constructor of a iterator defines past-the-end iterator so it's the end

    for(; pos != end; pos ++)
    {
        cout << "Matched: " << pos->str() << endl;

        cout << endl;
    }

    //cout << regex_replace(str, e, "$1 is on $2 ");  //replace the matched string with a certain format, $1 is substituted with the first submatch and $2 is substituted with the second submatch
    //cout << regex_replace(str, e, "$1 is on $2 ", regex_constants::format_no_copy);  //all the things that are not matched by the regular expression will not be copied to the new string
    cout << regex_replace(str, e, "$1 is on $2 ", regex_constants::format_no_copy|regex_constants::format_first_only);  //only the first match is considered a match and everything else is not considered a match
    cin >> str;

}


/*
 *  Regular Expression Grammars:
 *    1. ECMAScript
 *    2. basic
 *    3. extended
 *    4. awk
 *    5. grep
 *    6. egrep
 */  