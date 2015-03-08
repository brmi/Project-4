//
//  main.cpp
//  Project 4
//
//  Created by desiree on 3/5/15.
//  Copyright (c) 2015 desiree. All rights reserved.
//
//






// We have not yet produced the test driver main routine for you.

#include "provided.h"
#include <iostream>
#include<cassert>
using namespace std;

int main()
{
    //////////////////////////////////////////////////////////////
    //BINARYCONVERTER TESTS
    //To check if encode and decode work comment out the private section of the class declaration
    std::vector<unsigned short> numbers;
    numbers.push_back(43);
    numbers.push_back(99);
    numbers.push_back(234);
    
    std::string str = BinaryConverter::encode(numbers);
    std::vector<unsigned short> numbersTest;
    numbersTest.push_back(21);
    numbersTest.push_back(278);
    numbersTest.push_back(99);
    BinaryConverter::decode(str, numbersTest);
    assert(numbers.size() == numbersTest.size());
    for(int i = 0; i < numbers.size(); i++)
        assert(numbers[i] == numbersTest[i]);
    //16 spaces
    assert(BinaryConverter::decode("                ", numbersTest));
    //17 spaces
    assert(!BinaryConverter::decode("                 ", numbersTest));
    //16 characters, but has a non space/tab
    assert(!BinaryConverter::decode("            3   ", numbersTest));

  cout<<"passed binary converter tests"<<endl;
    vector<unsigned short> number;
    Compressor::compress("AAAAAAAAAB", number);
    string bloopy;
    Compressor::decompress(number, bloopy);
    cout<<bloopy;
    
    
    
}




//#include <iostream>
//#include "HashTable.h"
//#include <string>
//#include <cassert>
//
//int main ()
//{
//
//    //tests for isFull()
//    
////    HashTable<std::string, short> students(3, 5);
////    students.set("Cameron", 25, false);
////    students.set("Lily", 18, false);
////    students.set("Timothy", 43, false);
////    students.set("Sally", 22, false);
////    assert(!students.isFull());
////    students.set("Mikey", 28, false);
////    assert(students.isFull());
////    students.set("Buancho", 36, false);
////    assert(students.isFull()); //betta be full
////    
////    std::cout<<"yey u passed"<<std::endl;
//    
////    Let B be the number of buckets in the hash table, and C be its capacity. If the indicated key is not already in the table: If the table already contains C associations, the set() method returns false without changing anything; otherwise it adds a new association keyàvalue, which will be permanent if the third argument is true, otherwise non-permanent.
//    
//    
////    HashTable<std::string, short> icecream(10,20);
////    icecream.set("Mint and Chip", 2, true);
////    icecream.set("Cookie Dough", 1, false);
////    icecream.set("Strawberry", 3, false);
////    icecream.set("Mint and Chip", 4, false); // this should update value to 4
////    short val;
////    assert(icecream.get("Mint and Chip", val));
////    assert(val==4);
////    assert(icecream.get("Oreo Cookie Surprise", val)==false); //indicated key is not in table-> should return false
////    icecream.set("Dulce de Leche", 4, true);
////    icecream.set("Rocky Road", 6, true);
////    icecream.set("Vanilla Bean 90's Classic", 2, false);
////    
////    std::string discard1;
////    short value= 23;
////    icecream.discard(discard1, value);
////    assert(discard1=="Cookie Dough" && value == 1);
////    icecream.discard(discard1, value);
////    assert(discard1=="Strawberry" && value==3);
////    icecream.discard(discard1, value);
////    assert(discard1=="Vanilla Bean 90's Classic" && value==2);
////    
////    std::cout<<"k u passed second time"<<std::endl;
//    
//    HashTable<std::string, short> students(20, 40);
//    //change bucket to one to make sure that you are properly adding and deleting stuff
//    //    HashTable<std::string, short> students(1, 40);
//    students.set("Madi", 232, false);
//    students.set("Brm", 43, false);
//    students.set("Martin", 99, true);
//    students.set("Dima", 22, false);
//    students.set("Joslyn", 9222, true);
//    students.set("Jose", 10101, false);
//    students.set("Guy", 11, false);
//    students.touch("Madi");
//    
//    std::string brm;
//    short shortie= 83;
//    students.discard(brm, shortie);
//    assert(brm == "Brm" && shortie == 43);
//
//    students.discard(brm, shortie);
//    assert(brm == "Dima" && shortie == 22);
//    students.discard(brm, shortie);
//    assert(brm == "Jose" && shortie == 10101);
//    students.touch("Guy");
//    students.discard(brm, shortie);
//    assert(brm == "Madi" && shortie == 232);
//    students.discard(brm, shortie);
//    assert(brm == "Guy" && shortie == 11);
//    bool d = students.discard(brm, shortie);
//
//    assert(d == false && brm == "Guy" && shortie == 11);
//    assert(!students.isFull());
//    students.set("Brm", 21, false);
//    students.set("Brm", 45, true);
//    students.discard(brm, shortie);
//    assert(brm == "Brm" && shortie == 45);
////
//
//    
//    
//    HashTable<std::string, short> students2(10, 15);
//    students2.set("Madi", 232, false);
//    students2.set("Brm", 43, false);
//    students2.set("Martin", 999, true);
//    students2.get("Martin", shortie);
//    //checks that only the value changes when given a repeat key
//    assert(shortie == 999);
//    students2.set("Dima", 22, false);
//    students2.set("Joslyn", 9222, true);    //5
//    students2.set("Jose", 10101, false);
//    students2.set("Guy", 11, false);
//    students2.set("Philip", 90210, true);
//    students2.set("Don", 555, false);
//    students2.set("Maria", 5, false);   //10
//    students2.set("JOJO", 1, false);
//    students2.set("Kanye", 777, false);
//    students2.set("JLo", 88, true);
//    students2.set("Warhol", 666, true);
//    students2.set("Honay", 22, false);
//    assert(students2.isFull() && !students2.set("TooLate", 0, true));
//    
//    
//    HashTable<std::string, short> students3(1, 5);
//    students3.set("Maria", 5, false);   //10
//    students3.set("JOJO", 1, false);
//    students3.set("Kanye", 777, false);
//    students3.set("JLo", 88, false);
//    students3.set("Warhol", 666, false);
//    
//    assert(!students3.set("Honay", 22, false) && students3.isFull());
//    
//    students3.discard(brm, shortie);
//    assert(brm == "Maria" && shortie == 5);
//    
//    students3.discard(brm, shortie);
//    assert(brm == "JOJO" && shortie == 1);
//    
//    students3.discard(brm, shortie);
//    assert(brm == "Kanye" && shortie == 777);
//    
//    students3.discard(brm, shortie);
//    assert(brm == "JLo" && shortie == 88);
//    
//    students3.discard(brm, shortie);
//    assert(brm == "Warhol" && shortie == 666);
//    
//    students3.discard(brm, shortie);
//    assert(brm == "Warhol" && shortie == 666);
//    
//    students3.set("Honay", 22, false);
//    students3.discard(brm, shortie);
//    assert(brm == "Honay" && shortie == 22);
//    
//    students3.set("Honay", 22, false);
//    students3.set("Honay", 322, true);
//    students3.discard(brm, shortie);
//    assert(brm == "Honay" && shortie == 322);
//    
//    students3.set("Honay", 322, true);
//    students3.set("Honay", 22, false);
//    students3.discard(brm, shortie);
//    assert(brm == "Honay" && shortie == 322);
    
    //    std::cout << "Name:  " << brm << std::endl;
    //    std::cout << "Height: " << shortie << std::endl << std::endl;
    
//    std::cout << "Passed Tests" << std::endl;
    
    
    
    

    
//  
//    HashTable<std::string, short> students(5, 10);
//    students.set("Cameron", 25, false);
//    students.set("Lily", 18, false);
//    students.set("Timothy", 43, false);
//    students.set("Sally", 22, false);
//    students.set("Mikey", 28, false);
//    students.set("Buancho", 36, false);
//    
//    students.touch("Cameron");
//    students.touch("Lily");
//    students.touch("Timothy");
//    students.touch("Sally");
//    students.touch("Mikey");
//    std::string keything="";
//    short value=0;
//    students.discard(keything, value);
//    
//    std::cout<<keything<<std::endl;
//    std::cout<<value<<std::endl;


//}





