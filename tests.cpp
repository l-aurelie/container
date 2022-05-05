#include <iostream>
#include <string>

#include "reverse_iterator.hpp"

#include <vector>
#include "vector.hpp"
#include "vector_iterator.hpp"
#include "vector_iterator.hpp"
#include "vector_const_iterator.hpp"

#include <map>
#include "map.hpp"
#include "map_iterator.hpp"
#include "map_iterator.hpp"
#include "map_const_iterator.hpp"

#include <stack>
#include "stack.hpp"

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define NC "\e[0m"

//===================================== VECTOR ===========================================

template<typename T>
void printVector(const ft::vector<T>& vector)
{
    std::cout << "      ";
    for(std::size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " | ";
    std::cout << "(_size:" << vector.size() << ", capacity:"<< vector.capacity() << ")" <<std::endl;
}

template<typename T>
void printStdVector(const std::vector<T>& vector)
{
    std::cout << "      "; 
    for(std::size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " | ";
    std::cout << "     : vs classic std::vector";
    std::cout << std::endl;
}

int test_vector()
{
    std::cout << std::endl;
    std::cout <<  GRN "=========================/ VECTOR /=========================" NC << std::endl;
    std::vector<int>expl;
    expl.push_back(1);
    expl.push_back(2);
    expl.push_back(3);
    expl.push_back(4);
    expl.push_back(5);

    std::cout <<  GRN ".../ Constructor /..." NC << std::endl;
    std::cout << "- Create vec" << std::endl;
    ft::vector<std::string> vec;
    vec.push_back("coucou");
    vec.push_back("this");
    vec.push_back("is vector");
    std::cout << "- Push back \"coucou\" \"this\" \"is vector\"" << std::endl;
    printVector(vec);
    
    std::cout << "- Create vec2(3,10)" << std::endl;
    ft::vector<std::string> vec2(3, "hello");
    printVector(vec2);

    std::cout << "- Create vec3(vec.begin(), vec.end())" << std::endl;
    ft::vector<std::string> vec3(vec.begin(), vec.end());
    printVector(vec3);
    
    std::cout <<  GRN "- Swap vec1, vec2, " NC;
    std::cout << "then print vec, print vec2" << std::endl;
    vec.swap(vec2);
    printVector(vec);
    printVector(vec2);

    std::cout <<  GRN ".../ Copy, assignation /..." NC << std::endl;
    std::cout << "- Create vecc copy of vec" << std::endl;
    ft::vector<std::string> vecc(vec);
    printVector(vecc);

    std::cout << "- Create vecc1 = vecc" << std::endl;
    ft::vector<std::string> vecc1 = vecc;
    printVector(vecc1);
    //TODO: get allocator

    std::cout <<  GRN ".../ /..." NC << std::endl;
    {
        std::vector<int> max;
        ft::vector<int> max1;
        std::cout <<  GRN "- Max size : " NC << "With ft >> " << max1.max_size() << " (VS with std >> " << max.max_size() << ")" << std::endl;
    }
    vec.pop_back();
    std::cout << GRN "- One pop_back" NC << std::endl;
    printVector(vec);
    vec.clear();
    std::cout << GRN "- Clear vec" NC << std::endl;
    printVector(vec);
    std::cout <<  GRN "- Empty vec : " NC << vec.empty() << std::endl;
    vec.push_back("coucou");
    vec.push_back("coucou");
    std::cout << GRN "- Push back" NC; 
    std::cout << "\"coucou\" \"coucou\"" << std::endl;
    printVector(vec);

    std::cout << std::endl;

    ft::vector<int> vec1;
    std::cout << "- Create vec1" << std::endl;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    std::cout << "- Push back \" 1\" \"2\" \"3\" \"4\" \"5\"" << std::endl;
    std::cout <<  GRN "- Print using iterators : " NC;
    for(ft::vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++)
    {
        std::cout << *it << " | ";
    }
    std::cout << std::endl;
    std::cout << GRN "- Elemets acces: " NC << std::endl;
    std::cout << "      - vec1[4]: " << vec1[4] << std::endl;
    std::cout << "      - vec1.at(4): " << vec1.at(4) << std::endl;
    std::cout << "      - vec1.front: " << vec1.front() << std::endl;
    std::cout << "      - vec1.back: " << vec1.back() << std::endl;

    vec1.insert(++vec1.begin(), 4, 3);
    expl.insert(++expl.begin(), 4, 3);
    std::cout << GRN "- Insert" NC;
    std::cout << "(++begin, 4, 3)" << std::endl;
    printVector(vec1);
    printStdVector(expl);
    
    vec1.insert(++vec1.begin(), 10);
    expl.insert(++expl.begin(), 10);
    std::cout << "- Insert(++begin, 10)" << std::endl;
    printVector(vec1);
    printStdVector(expl);

    std::vector<int> test;
    test.assign(3, 100);
    test.push_back(200);
    vec1.insert(++vec1.begin(), test.begin(), test.end());
    expl.insert(++expl.begin(), test.begin(), test.end());
    std::cout << "- Insert(++begin, vec range containing 100 | 100 | 100 | 200 )" << std::endl;
    printVector(vec1);
    printStdVector(expl);
    
    vec1.erase(++vec1.begin());
    expl.erase(++expl.begin());
    std::cout << GRN "- erase" NC;
    std::cout << "(++begin)" << std::endl;
    printVector(vec1);
    printStdVector(expl);
    
    vec1.erase(++vec1.begin(), --vec1.end());
    expl.erase(++expl.begin(), --expl.end());
    std::cout << "- erase(++begin, --end)" << std::endl;
    printVector(vec1);
    printStdVector(expl);
    
    std::cout << std::endl;
    vec1.pop_back();
    std::cout << "- One pop_back " << std::endl;
    printVector(vec1);
    vec1.assign(7, 4);
    std::cout << GRN "- Assign 7, 4 " NC << std::endl;
    printVector(vec1);
    
    vec1.assign(expl.begin(), expl.end());
    std::cout << "- Assign expl range " << std::endl;
    printVector(vec1);

    vec1.resize(12);
    std::cout << GRN "- Resize 12 " NC << std::endl;
    printVector(vec1);
    vec1.resize(2);
    std::cout << "- Resize 2 " << std::endl;
    printVector(vec1);
    std::cout << std::endl;

    std::cout << GRN "- Get allocator " NC << std::endl;
    std::allocator<std::string> allo(vec.get_allocator());

    std::cout << std::endl;
    std::cout << GRN "=========================/ ITERATOR (vector) /======================" NC << std::endl;
    {    
        std::cout << std::endl;

        ft::vector<int> vec2;
        std::cout << "- Create vec2" << std::endl;
        vec2.push_back(10);
        vec2.push_back(9);
        vec2.push_back(8);
        vec2.push_back(7);
        vec2.push_back(6);
        vec2.push_back(5);
        vec2.push_back(4);
        vec2.push_back(3);
        vec2.push_back(2);
        vec2.push_back(1);

        std::cout << "- Create const vec3 cpy of vec2" << std::endl;
        const ft::vector<int> vec3(vec2);
        ft::vector<int>::iterator it = vec2.begin();
        std::cout << std::endl;
        std::cout << "- testing const iterator from normal iterator : ";
        ft::vector<int>::const_iterator it_c = vec2.begin();
        for(;it_c != vec2.end(); it_c++)
        {std::cout <<  *it_c;}
        std::cout << std::endl;

        std::cout << "- Decomment to test constness" << std::endl;
    // *it_c = 2; // decomment to test constness of iterators
        std::cout << "- Create it, iterator from vec2 containing 10 9 8 7 6 5 4 3 2 1" << std::endl;
        it += 2;
        std::cout << "- it += 2 : " << *it << std::endl;
        std::cout << "- begin + 2 : " << *(vec2.begin() + 2) << std::endl;
        std::cout << "- it != begin = " << (int)(it != vec2.begin()) << std::endl;
        std::cout << "- it == begin + 2 = " << (int)(it == vec2.begin() + 2) << std::endl;
        std::cout << "- it < begin = " << (int)(it < vec2.begin()) << std::endl;
        std::cout << "- it >= begin = " << (int)(it >= vec2.begin()) << std::endl;
        std::cout << "- it - begin = " << (int)(it - vec2.begin()) << std::endl;
        std::cout << "- it go back to the begening with operator -- : ";
        for(; it != vec2.begin(); it --)
            std::cout << " " <<*it;
        std::cout<< " " << *it;
        std::cout << std::endl;
        std::cout << "- 2 + it = " << *(2 + it) << std::endl;

        std::cout << std::endl;
        std::cout <<  GRN "===========================/ REVERSE ITERATORS /=============================" NC<< std::endl;
        ft::vector<int>::reverse_iterator rit = vec2.rbegin();
        std::cout << std::endl;
        std::cout << "- testing rev const iterator from normal iterator : ";
        ft::vector<int>::const_reverse_iterator rit_c = vec2.rbegin();
        for(;rit_c != vec2.rend(); rit_c++)
            {std::cout <<  *rit_c;}
        std::cout << std::endl;

        std::cout << " - Decomment to test constness" << std::endl;
        // *rit_c = 2; // decomment to taste constness of iterators
        std::cout << "- Create rit, rev iterator from vec2 containing 10 9 8 7 6 5 4 3 2 1" << std::endl;
        std::cout << "rit = " << *rit << std::endl;

        rit += 2;
        std::cout << "- rit += 2 : " << *rit << std::endl;
        std::cout << "- rbegin + 2 : " << *(vec2.rbegin() + 2) << std::endl;
        std::cout << "- rit != rbegin = " << (int)(rit != vec2.rbegin()) << std::endl;
        std::cout << "- rit == rbegin + 2 = " << (int)(rit == vec2.rbegin() + 2) << std::endl;
        std::cout << "- rit < rbegin = " << (int)(rit < vec2.rbegin()) << std::endl;
        std::cout << "- rit >= rbegin = " << (int)(rit >= vec2.rbegin()) << std::endl;
        std::cout << "- rit - rbegin = " << (int)(rit - vec2.rbegin()) << std::endl;
        
        rit = vec2.rend() - 1;
        std::cout << "from rend - 1, go back to rbegin with operator -- : ";
        for(; rit != vec2.rbegin(); rit--)
            std::cout << " " <<*rit;
        std::cout<< " " << *rit;
        std::cout << std::endl;
        std::cout << "- 2 + rit = " << *(2 + rit) << std::endl;
    }
    return (0);
}

//===================================== STACK ===========================================

template<typename T >
void printStack(const ft::stack<T>& stack)
{
    std::cout << "      ";
    std::cout << "stack_top : " << stack.top() << " | stack_size : " << stack.size() << std::endl;
}

int test_stack()
{
    std::cout << RED "=========================/  TEST STACK /======================" NC << std::endl;
    std::cout << RED "- Construct" NC <<  " stk1" << std::endl;
    ft::stack< int > stk1;
    std::cout << RED "- Empty " NC <<  "stack1 = " << stk1.empty() << std::endl;
    std::cout << RED "- Push " NC <<  "stack1 1 2 3 4"<< std::endl;
    stk1.push(1);
    stk1.push(2);
    stk1.push(3);
    stk1.push(4);
    std::cout << RED "- Top " NC<< std::endl;
    printStack(stk1);
    std::cout << RED "- Pop " NC<< std::endl;
    stk1.pop();
    printStack(stk1);
    std::cout << RED "- Assignation" NC << " stk2 = stk1" << std::endl;
    ft::stack< int > stk2;
    stk2 = stk1;
    std::cout <<  RED ".../ Comparaison /..." NC << std::endl;
    std::cout << "stk1 == stk2 = " <<  (stk1 == stk2) << std::endl;
    std::cout << "stk1 > stk2 = " <<  (stk1 > stk2) << std::endl;
    std::cout << "stk1 >= stk2 = " <<  (stk1 >= stk2) << std::endl;
    std::cout << "stk1 < stk2 = " <<  (stk1 < stk2) << std::endl;
    std::cout << "stk1 <= stk2 = " <<  (stk1 <= stk2) << std::endl;
    std::cout << "stk1 != stk2 = " <<  (stk1 != stk2) << std::endl;
    return(0);
}


//===================================== MAP ===========================================

template<class K, class V>
void printMap(const ft::map<K, V>& map_obj)
{
    std::cout << "      ";
    for(typename ft::map<K, V>::const_iterator it = map_obj.begin(); it != map_obj.end(); it++)// TODO : pk const 
        std::cout << it->first << ":" << it->second << " | ";
    std::cout << "(_size:" << map_obj.size() << ")" << std::endl;
}

template<class K, class V>
void printStdMap(const std::map<K, V>& map_obj)
{
    std::cout << "      ";
    for(typename std::map<K, V>::const_iterator it = map_obj.begin(); it != map_obj.end(); it++)
        std::cout << it->first << ":" << it->second << " | ";
    std::cout << "     : vs classic std::vector";
    std::cout << std::endl;
}

int test_map()
{
    std::cout << CYN "=========================/  TEST MAP /======================" NC << std::endl;
    std::cout << std::endl;

    std::cout << CYN ".../  Constructor assignation /..." NC << std::endl;
    std::cout << "- Create map1 insert <a:1> <b:2> <c:3> <d:4> " << std::endl;
    ft::map<std::string, int, std::less<std::string> > map1;
    map1.insert(ft::make_pair< std::string, int >("a", 1));
	map1.insert(ft::make_pair< std::string, int >("b", 2));
	map1.insert(ft::make_pair< std::string, int >("c", 3));
	map1.insert(ft::make_pair< std::string, int >("d", 4));
    printMap(map1);
    std::cout << "- Create map2(map1.begin() map1.end()) " << std::endl;
    ft::map<std::string, int, std::less<std::string> > map2(map1.begin(), map1.end());
    printMap(map2);
    std::cout << "- Create map3 copie map2 " << std::endl;
    ft::map<std::string, int, std::less<std::string> > map3(map2);
    printMap(map3);
    std::cout << "- Erase \"a\" sur map2, map3 = map2 " << std::endl;
    map2.erase("a");
    map3 = map2;
    printMap(map3);

    std::cout << CYN ".../ Element access /..." NC << std::endl;
    std::cout << CYN "- Operator At " NC << "a = " << map1.at("a") << std::endl;
    //std::cout <<  "- At x = " << map1.at("x") << std::endl;//Decomment to test out of range
    std::cout << CYN "- Operator [] " NC << "c = " << map1["c"] << std::endl;
    std::cout << "- Operator [] x = " << map1["x"] << std::endl;
    printMap(map1);
    std::cout << CYN ".../ /..." NC << std::endl;
    std::cout << CYN "- Clear map1 " NC << std::endl;
    map1.clear();
    printMap(map1);
    
    std::map<std::string, int > st_map;
    std::cout << CYN "- Max_size = " NC << map1.max_size() << " (VS std max_size = " << st_map.max_size() << ")" << std::endl;

    std::cout << CYN "- Insert" NC << " map1 insert <e:5> <f:6> <g:7> <h:8> " << std::endl;
    map1.insert(map1.begin(), ft::make_pair< std::string, int >("e", 5));
	map1.insert(ft::make_pair< std::string, int >("f", 6));
	map1.insert(ft::make_pair< std::string, int >("g", 7));
	map1.insert(ft::make_pair< std::string, int >("h", 8));
    printMap(map1);
    std::cout << "- Insert map1(map2.begin(), map2.end()) " << std::endl;
    map1.insert(map2.begin(), map2.end());
    printMap(map1);
    std::cout << CYN "- Erase" NC << " --map1.end() " << std::endl;
    map1.erase(--map1.end());
    printMap(map1);
    std::cout << "- Erase(map3.begin, --map3.end()) " << std::endl;
    map3.erase(map3.begin(), --map3.end());
    printMap(map3);
    std::cout << CYN "- Swap" NC << " and print map2 et map3" << std::endl;
    std::cout << "before = " << std::endl;
    printMap(map2);
    printMap(map3);
    map2.swap(map3);
    std::cout << "After = " << std::endl;
    printMap(map2);
    printMap(map3);
    std::cout << CYN "- Count" NC << " map2.count(d) = " << map2.count("d") << std::endl;
    std::cout << "- Count map2.count(x) = " << map2.count("x") << std::endl;
    std::cout << CYN "- Find" NC << " map2.count(d) = ";
    {
        ft::map<std::string, int>::iterator found(map2.find("d")); 
        if(found != map2.end())
            std::cout << found->first << ":" << found->second << std::endl;
        else
            std::cout << "this->end" << std::endl;
    }
    std::cout << "- Find map2.count(x) = ";
    {
        ft::map<std::string, int>::iterator found(map2.find("x")); 
        if(found != map2.end())
            std::cout << found->first << ":" << found->second << std::endl;
        else
            std::cout << "this->end" << std::endl;
    }
    std::cout << CYN "- Lower bound" NC << " map1.lower_bound(d) = " << map1.lower_bound("d")->first << std::endl;
    std::cout << CYN "- Upper bound" NC << " map1.upper_bound(d) = " << map1.upper_bound("d")->first << std::endl;
    std::cout << CYN "- Equal range" NC << " Equal_range(d) = " << map1.equal_range("d").first->first << ":"<< map1.equal_range("d").second->first << std::endl;
    
    std::cout << CYN ".../Comparaison/..." NC<< std::endl;
    ft::map<int, int> map4;
    map4.insert(ft::make_pair<int, int>(1, 1));
    ft::map<int, int> map5;
    map5.insert(ft::make_pair<int, int>(2, 2));
    std::cout << "map4:" ;
    printMap(map4);
    std::cout << "map5:" ;
    printMap(map5);
    map5.insert(ft::make_pair<int, int>(2, 2));
    std::cout << "map4 > map5 = " <<  (map4 > map5) << std::endl;
    std::cout << "map4 < map5 = " <<  (map4 < map5) << std::endl;
    std::cout << "map4 != map5 = " <<  (map4 != map5) << std::endl;
    std::cout << "map4 == map5 = " <<  (map4 == map5) << std::endl;
    
    std::cout << std::endl;
    std::cout << CYN ".../Iterator/..." NC << std::endl;
    printMap(map1);
    std::cout << "map1.begin = " << map1.begin()->first << std::endl;
    std::cout << "--map1.end = " << (--map1.end())->first << std::endl;
    std::cout << "map1.rbegin = " << map1.rbegin()->first << std::endl;
    std::cout << "--map1.rend = " << (--map1.rend())->first << std::endl;
    return(0);
}


int main (int argc, char **argv)
{
    std::cout << argc << std::endl;
    if(argc < 2)
        std::cout << "USAGE : Enter in lower case names of containers you to test";
    for(int i = 0; i < argc; i++)
    {
        std::string arg(argv[i]);
        if(!arg.compare("vector"))
            test_vector();
        if(!arg.compare("stack"))
            test_stack();
        if(!arg.compare("map"))
            test_map();
    }
    return 0;
} 