#ifndef DOUBLE_HASHING_HPP
#define DOUBLE_HASHING_HPP
#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"

typedef long long ll;

bool isPrime(ll num);
ll nextPrime(ll num);

class Doublehashing
{

    ll auxHash(string key)
    {
        ll i, sum;
        for (i = 0, sum = 0; i < key.length(); i++)
            sum += key[i];
        return sum % N;
    }

    ll hash1(string key) // djb2 hash function
    {
        char *str = (char *)key.c_str();
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
        {
            hash = ((hash << 5) + hash) + c;
        }

        return hash % N;
    }

    ll hash2(string key) // polynomial rolling hash function
    {
        ll hashVal = 0;

        for (ll i = 0; i < key.length(); i++)
            hashVal = 37 * hashVal + key[i];

        hashVal %= N;

        if (hashVal < 0)
            hashVal += N;

        return hashVal;
    }

public:
    ll N, size, collisions, probes;
    vector<Node> hashTable;
    ll hashFunction;

    Doublehashing(ll N, ll hashFunction)
    {
        this->N = nextPrime(N);
        hashTable.resize(this->N);
        size = collisions = probes = 0;
        this->hashFunction = hashFunction;
    }

    ll doubleHash(string key, ll i)
    {
        return ((hashFunction == 1 ? hash1(key) : hash2(key)) + i * auxHash(key)) % N;
    }

    void insert(string key, ll value)
    {
        if ((size / N > 0.5) || (size > 100 && probes / (0.1 * N) > 2))
            reHash(1);

        ll i = 0, h, prev, offset = 0;

        h = doubleHash(key, i);
            prev = h;
        while (hashTable[h].key != "")
        {
            h = (offset + doubleHash(key, ++i)) % N;
            if (h == prev)
            {
                offset++;
                i = 0;
            }
            // probes++;
            collisions++;
        }

        hashTable[h] = Node(key, value);
        size++;
    }

    void reHash(ll n)
    {
        ll oldN = N, oldCollisions = collisions;
        if (n == 1)
            N = nextPrime(2 * N);
        else if(n==2)
            N = nextPrime(N / 2);
        vector<Node> temp = hashTable;
        hashTable.clear();
        hashTable.resize(N);
        size = 0;

        for (ll i = 0; i < oldN; i++)
        {
            if (temp[i].key != "")
                insert(temp[i].key, temp[i].value);
        }
    }

    ll find(string key)
    {
        ll i = 0, h, prev, offset = 0;
        h = doubleHash(key, i);

        prev = h;
        while (hashTable[h].key != "" && i < N)
        {
                // probes++;
            if (hashTable[h].key == key)
            {
                probes++;
                return hashTable[h].value;
            }
            h = (offset + doubleHash(key, ++i)) % N;

            if (h == prev)
            {
                offset++;
                i = 0;
            }
            else
                probes++;
        }

        return -1;
    }

    void remove(string key)
    {
        if (size / N < 0.1)
            reHash(2);

        ll i = 0, h, prev, offset = 0;
        h = doubleHash(key, i);

            prev = h;
        while (hashTable[h].key != "" && i < N)
        {

            if (hashTable[h].key == key)
            {
                hashTable[h] = Node("", -1);
                size--;
                return;
            }

            h = (offset + doubleHash(key, ++i)) % N;

            if (h == prev)
            {
                offset++;
                i = 0;
            }
            else
                probes++;
        }
    }
};

#endif