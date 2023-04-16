
#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <chrono>
#include "library.h"
#include "helpers.h"

using std::chrono::nanoseconds; 
using namespace std;


constexpr int maxlen = 10000;
constexpr int sizes = 0;

int main()
{
    fstream bst_insert_random("bst_insert_random.txt", ios::out);
    fstream avl_insert_random("avl_insert_random.txt", ios::out);

    fstream bst_insert_ordered("bst_insert_ordered.txt", ios::out);
    fstream avl_insert_ordered("avl_insert_ordered.txt", ios::out);

    fstream bst_insert_low("bst_insert_low.txt", ios::out);
    fstream avl_insert_low("avl_insert_low.txt", ios::out);

    fstream avl_search_randomf("avl_search_random.txt", ios::out);
    fstream bst_search_randomf("bst_search_random.txt", ios::out);

    fstream avl_search_orderedf("avl_search_ordered.txt", ios::out);
    fstream bst_search_orderedf("bst_search_ordered.txt", ios::out);

    std::random_device rd;
    std:mt19937 gen(time(NULL));
    std::uniform_int_distribution<int> dist(-2 * maxlen, maxlen*2);

    
    int* random_data = new int[maxlen];
    int* ordered_data = new int[maxlen];
    int* low_entropy_data = new int[maxlen];

    BST bst;
    AVL avl;

    //random data
    for(int i=0; i<maxlen; ++i)
        random_data[i] = dist(gen);

    //ordered data
    copy(random_data, ordered_data, maxlen);
    std::sort(ordered_data, ordered_data+maxlen);

    //low entttropy data
    copy(ordered_data, low_entropy_data, maxlen);
    make_low_entropy(low_entropy_data, maxlen, gen);

    //for random data
    for(int i=1; i<maxlen; ++i)
    {
        nanoseconds bst_random(0);
        nanoseconds avl_random(0);

        nanoseconds bst_search_random_Ex(0);
        nanoseconds bst_search_random_Dx(0);

        nanoseconds avl_search_random_Ex(0);
        nanoseconds avl_search_random_Dx(0);

        


        bst_random = calculate_time(bst, random_data[i]);
        avl_random = calculate_time(avl, random_data[i]);

        bst_search_random_Ex = timeit_search(bst, random_data[i]);
        bst_search_random_Dx = timeit_search(bst, random_data[i+1]);

        avl_search_random_Ex = timeit_search(avl, random_data[i]);
        avl_search_random_Dx = timeit_search(avl, random_data[i+1]);

        cout << i  << "   " << bst_random.count()  << "  " << avl_random.count() << endl;
        bst_insert_random << i  << "   " << bst_random.count() << endl;
        avl_insert_random << i  << "   " << avl_random.count() << endl;

        bst_search_randomf << i << "   " << bst_search_random_Ex.count() << "  " << bst_search_random_Dx.count() << endl; 
        avl_search_randomf << i << "   " << avl_search_random_Ex.count() << "  " << avl_search_random_Dx.count() << endl; 
    }

    //for ordered data
    for(int i=0; i<maxlen; ++i)
    {
        nanoseconds bst_ordered(0);
        nanoseconds avl_ordered(0);

        nanoseconds bst_search_random_Ex(0);
        nanoseconds bst_search_random_Dx(0);

        nanoseconds avl_search_random_Ex(0);
        nanoseconds avl_search_random_Dx(0);

        bst_ordered = calculate_time(bst, ordered_data[i]);
        avl_ordered = calculate_time(avl, ordered_data[i]);

        bst_search_random_Ex = timeit_search(bst, ordered_data[i]);
        bst_search_random_Dx = timeit_search(bst, ordered_data[i+1]);

        avl_search_random_Ex = timeit_search(avl, ordered_data[i]);
        avl_search_random_Dx = timeit_search(avl, ordered_data[i+1]);

        bst_insert_ordered << i << "  " << bst_ordered.count() << endl;
        avl_insert_ordered << i << "  " << avl_ordered.count() << endl;
        

        bst_search_orderedf << i << "   " << bst_search_random_Ex.count() << "  " << bst_search_random_Dx.count() << endl; 
        avl_search_orderedf << i << "   " << avl_search_random_Ex.count() << "  " << avl_search_random_Dx.count()<< endl; 
    }


    //for low entropy data
    for(int i=0; i<maxlen; ++i)
    {
        nanoseconds bst_low_entropy(0);
        nanoseconds avl_low_entropy(0);

        bst_low_entropy = calculate_time(bst, low_entropy_data[i]);
        avl_low_entropy = calculate_time(avl, low_entropy_data[i]);

        bst_insert_low << i << "  " << bst_low_entropy.count() << endl;
        avl_insert_low << i << "  " << avl_low_entropy.count() << endl;
    }
    return 0;
}