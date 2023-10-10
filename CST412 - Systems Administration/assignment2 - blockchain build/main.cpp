//a program meant to implement a basic blockchain using SHA256 encryption
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <list>
#include <chrono>
#include "hash-library-master/sha256.h" //https://github.com/stbrumme/hash-library
#include "hash-library-master/sha256.cpp" //there are other encryption algorthims but we are only importing SHA256
using namespace std;


//===============Block class declaration===================================
class Block{
    private:
        string hash; //this blocks hash
        string prevHash; //previous blocks hash
        string data; //data recorded in block
        long timeStamp; //time when block was created
        int pow; //proof of work
        int prefix; //number of leading 0's required by SHA-256 encryption
    public:
        //getters and setters defined in-class
        string getHash(){return hash;}
        void setHash(string newHash){hash = newHash;}
        string getPrevHash(){return prevHash;}
        void setPrevHash(string newPrevHash){prevHash = newPrevHash;}
        string getData(){return data;}
        void setData(string newData){data = newData;}
        long getTimeStamp(){return timeStamp;}
        void setTimeStamp(long newTime){timeStamp = newTime;}
        int getPow(){return pow;}
        void setPow(int newPow){pow = newPow;};
        int getPrefix(){return prefix;}
        void setPrefix(int newPrefix){prefix = newPrefix;}

        //functionality defined below main
        Block(string data, string prevHash, long timeStamp, int prefix); //constructor
        string generateBlockHash(); //compute block hash
        string mineBlock(); //mines block
};
//===========================================================================



//===============BlockChain class declaration=================================
class BlockChain{
    private:
        list<Block> blocks; //list of block objects that make up our block chain
        int chainSize; //how many blocks are in the chain (can't we just get this from the list?)
    public:
        //getters and setters defined here
        list<Block> getBlocks(){return blocks;}
        void setBlock(list<Block> newList){blocks = newList;}
        int getChainSize(){return chainSize;}
        void setChainSize(int newChainSize){chainSize = newChainSize;}

        //functionality defined below main
        BlockChain(); //default constructor
        void addBlock(Block newBlock); //add block to chain
        bool verify(); //verify authenticity of chain
        string toString(); //returns full blockchain in a single string

};
//===========================================================================



//===============TestBlockChain class declaration=============================
class TestBlockChain{
    public:
        //defined below main
        void main();
};
//===========================================================================



//===============other functions declared=====================================
string HexToBin(string hexdec, int size);
//===========================================================================



//================================MAIN=======================================
int main(){
    TestBlockChain test;
    test.main();
    return 0;
}
//===========================================================================



//========================BLOCK METHODS======================================
//constructor
Block::Block(string newData, string newPrevHash, long newTimeStamp, int newPrefix){
    data = newData;
    prevHash = newPrevHash;
    timeStamp = newTimeStamp;
    prefix = newPrefix;
    pow = -1; //it'll get iterated to 0 before we generateBlockHash
    hash = mineBlock();
}

//compute block hash
string Block::generateBlockHash(){
    // stringstream constructed;
    // constructed << data << prevHash << timeStamp << prefix << pow;
    // string concatenatedString = constructed.str();
    SHA256 encrypted;
    return encrypted(data+prevHash+to_string(timeStamp)+to_string(prefix)+to_string(pow));
}

//mine block
string Block::mineBlock(){
    while(true){
        // auto start = chrono::system_clock::now();
        int hexCount = prefix/4;
        if(prefix % 4 != 0){
            hexCount++;
        }
        pow++;
        string currentHash = generateBlockHash();
        string comp = HexToBin(currentHash, hexCount);
        for(int i = 0; i < prefix; i++){   //go through prefix amount of chars of hash, if not 0,
            if(comp[i] != '0'){ //break and go to next itr of while loop
                break;
            }
            if(i == prefix-1){ //if this condition is true, we have right amount of 0's as prefix
                return currentHash;
            }
        }
        // auto end = chrono::system_clock::now();
        // cout << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    }
    cerr << "Something went wrong in mineBlock()\n";
    return "";
}
//===========================================================================================



//====BlockChain METHODS=====================================================================
BlockChain::BlockChain(){
    chainSize = 0;
}

void BlockChain::addBlock(Block newBlock){
    blocks.push_back(newBlock);
    chainSize++;
}

bool BlockChain::verify(){
    string lastHash = "";
    for(list<Block>::iterator i = blocks.begin(); i != blocks.end(); i++){
        string currHash = i->getHash();
        //checking current hash
        SHA256 verifi;
        string constructed;
        constructed = (i->getData() + i->getPrevHash() + to_string(i->getTimeStamp()) + to_string(i->getPrefix()) + to_string(i->getPow()));
        string compareStr = verifi(constructed);
        int temp = currHash.compare(compareStr);
        if(temp != 0){ //if hash does not equal what it should calculate to
            cout << "Validation failed: current hash does not equal the hash when calculated\n";
            return false;
        }

        //checking prevHash
        list<Block>::iterator it = blocks.begin(); //get another iterator to go to the block before current
        temp = lastHash.compare(i->getPrevHash());
        if(temp != 0){ //compare
            cout << "Validation failed: prevHash does not match the previous blocks hash\n";
            return false;
        }
        lastHash = currHash;

        //checking mining process
        int add;
        if(i->getPrefix() % 4 == 0){
            add = 0;
        }else{
            add = 1;
        }
        string bin = HexToBin(currHash, i->getPrefix()+add);
        for(int k = 0; k < i->getPrefix(); k++){
            if(bin[k] != '0'){ //if we don't have right amount of leading 0's
                cout << "Validation failed: incorrect prefix\n";
                return false;
            }
        }
    }
    return true;
}

string BlockChain::toString(){
    string construction;
    int c = 1;
    construction = "chain size: " + to_string(getChainSize());
    for(auto i : blocks){
        construction += ("\nblock " + to_string(c) + ":\n" + "data: " + i.getData() + "\nprefix: " + to_string(i.getPrefix()) + "\nhash: " + i.getHash() + "\nprevHash: " + i.getPrevHash() + "\n");
        c++;
    }
    return construction;
}
//==================================================================================



//===========================testblockChain methods=================================
void TestBlockChain::main(){
    Block myBlock = Block("Genesis block", "", chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(), 4);
    Block myBlock2 = Block("block-1", myBlock.getHash(), chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(), 4);
    Block myBlock3 = Block("block-2", myBlock2.getHash(), chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(), 8);
    Block myBlock4 = Block("block-3", myBlock3.getHash(), chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(), 12);

    BlockChain myBlockChain;
    myBlockChain.addBlock(myBlock);
    myBlockChain.addBlock(myBlock2);
    myBlockChain.addBlock(myBlock3);
    myBlockChain.addBlock(myBlock4);

    //verification & print out
    cout << "\nVerification: " << myBlockChain.verify() << endl << myBlockChain.toString();
}
//==================================================================================



//================================other functions===================================
string HexToBin(string hexdec, int size) //original definition from https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
{
    int i = 0;
    string returnValue = "";
    while (i < size) {
 
        switch (hexdec[i]) {
        case '0':
            returnValue+= "0000";
            break;
        case '1':
            returnValue+= "0001";
            break;
        case '2':
            returnValue+= "0010";
            break;
        case '3':
            returnValue+= "0011";
            break;
        case '4':
            returnValue+= "0100";
            break;
        case '5':
            returnValue+= "0101";
            break;
        case '6':
            returnValue+= "0110";
            break;
        case '7':
            returnValue+= "0111";
            break;
        case '8':
            returnValue+= "1000";
            break;
        case '9':
            returnValue+= "1001";
            break;
        case 'A':
        case 'a':
            returnValue+= "1010";
            break;
        case 'B':
        case 'b':
            returnValue+= "1011";
            break;
        case 'C':
        case 'c':
            returnValue+= "1100";
            break;
        case 'D':
        case 'd':
            returnValue+= "1101";
            break;
        case 'E':
        case 'e':
            returnValue+= "1110";
            break;
        case 'F':
        case 'f':
            returnValue+= "1111";
            break;
        case '.':
            returnValue+= ".";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    return returnValue;
}
//================================================================================