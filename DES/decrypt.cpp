/*
To run program provide the text file containing cipher text as
an 1st command-line argument.Plaintext will be save decrypted_text file.
*/
#include<iostream>
#include<mypro.h>
#include<fstream>
using namespace std;
//-----------------------Conversion codes-------------

string string_to_hex(const string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

//----------------------------------------------------
int main(int argc,char* argv[]){
	int mssgcount,j=0;
	string mssg="",key,m=argv[1],word;
	
	fstream ReadFile;
    ReadFile.open(m.c_str());
    while (ReadFile>>word) {
           mssg=mssg+word;
     }
	
    mssgcount=mssg.length()/16;
	
	cout<<"Enter the key(64 bit) hexamdecimal:";
	cin>>key;
	
	string plaintext="";
	for(int i=0;i<mssgcount;i++){
	    plaintext=plaintext+hex_to_string(des(mssg.substr(j,j+16),key));
		j+=16;
	}
	
	ofstream plainfile("decrypt_text.txt");
    plainfile << plaintext;
    plainfile.close();
	
	return 0;
}