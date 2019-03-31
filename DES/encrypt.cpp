/*
To run program provide the text file containing plain text as
an 1st command-line argument.Ciphertext will be save cipher_text file and key 
will be saved in key.txt file.
*/
#include<iostream>
#include<fstream>
#include<mypro.h>
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

int main(int argc,char* argv[]){
	int mssgcount,j=0;
	string mssg="",key,word,m=argv[1];
	
	fstream ReadFile;
    ReadFile.open(m.c_str());
    while (ReadFile>>word) {
           mssg=mssg+" "+word;
     }
	
	mssg=string_to_hex(mssg);
    mssgcount=mssg.length()/16;
	double rembits=mssg.length()%16;
	
	cout<<"Enter the key(64 bit) hexamdecimal:";
	cin>>key;
	
	ofstream keyfile("key.txt");
    keyfile<<key;
    keyfile.close();
	
	string cipher="";
	for(int i=0;i<mssgcount;i++){
	    cipher=cipher+des(mssg.substr(j,j+16),key);
		j+=16;
	}
	
	if(rembits!=0){
	  string fill16="";
	  int k=mssgcount*16;
		for(int i=0;i<rembits;i++){
		     fill16=fill16+"1";
		}
	  mssg=mssg+fill16;	
	  cipher=cipher+des(mssg.substr(k,16),key);	
	}
	
	ofstream cipherfile("cipher_text.txt");
    cipherfile << cipher;
    cipherfile.close();
	
	return 0;
}
