#include "chaining.hpp"
#include "customProbing.hpp"
#include "doubleHashing.hpp"
#include <ctime>
#include <set>
#include <vector>
#include <iomanip>

#define numberOfStringsToGenerate 10000
#define searchRandomly 1000

bool isPrime(ll num)
{
    if (num <= 1)
        return false;
    if (num <= 3)
        return true;
    if (num % 2 == 0 || num % 3 == 0)
        return false;

    for (long long i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;

    return true;
}

long long nextPrime(ll num)
{
    while (true)
    {
        if (isPrime(num))
            return num;
        num++;
    }
}

string generateRandomString(int length)
{
    const string charset = "abcdefghijklmnopqrstuvwxyz";
    string randomString;
    for (int i = 0; i < length; ++i)
    {
        randomString += charset[rand() % charset.size()];
    }
    return randomString;
}

int main(int argc, char const *argv[])
{
    set<string> generatedStrings;

    srand(time(0));

    for (int i = 0; i < numberOfStringsToGenerate; ++i)
    {
        int length = rand() % 6 + 5;
        string randomString;

        do
        {
            randomString = generateRandomString(length);
        } while (!generatedStrings.insert(randomString).second);
    }

    vector<string> generatedStringsVector(generatedStrings.begin(), generatedStrings.end());

    long long size[3] = {5000, 10000, 20000};
    double report[3][3][2][2];
    freopen("hashing_report.txt", "w", stdout);
    ll n = 0;
    for (auto i : size)
    {
        for (ll j = 1; j <= 2; j++)
        {
            chaining obj(i, j);
            for (auto k : generatedStringsVector)
            {
                obj.insert(k, obj.size + 1);
            }

            for (ll m = 0; m < searchRandomly; m++)
            {
                ll index = rand() % numberOfStringsToGenerate;
                obj.find(generatedStringsVector[index]);
            }

            report[n][0][j - 1][0] = obj.collisions;
            report[n][0][j - 1][1] = (double)obj.probes / searchRandomly;
        }
        for (ll j = 1; j <= 2; j++)
        {
            customProbing obj(i, j);
            for (auto k : generatedStringsVector)
            {
                obj.insert(k, obj.size + 1);
            }

            for (ll m = 0; m < searchRandomly; m++)
            {
                ll index = rand() % numberOfStringsToGenerate;
                obj.find(generatedStringsVector[index]);
            }

            report[n][1][j - 1][0] = obj.collisions;
            report[n][1][j - 1][1] = (double)obj.probes / searchRandomly;
        }
        for (ll j = 1; j <= 2; j++)
        {
            Doublehashing obj(i, j);
            for (auto k : generatedStringsVector)
            {
                obj.insert(k, obj.size + 1);
            }

            for (ll m = 0; m < searchRandomly; m++)
            {
                ll index = rand() % numberOfStringsToGenerate;
                obj.find(generatedStringsVector[index]);
            }

            report[n][2][j - 1][0] = obj.collisions;
            report[n][2][j - 1][1] = (double)obj.probes / searchRandomly;
        }
        n++;
    }
    std::cout << " " << setw(68) << setfill('_') << "" << endl;
    std::cout << setfill(' ');
    std::cout << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    std::cout << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    std::cout << "|" << setw(69) << setfill('_') << "|" << endl;
    std::cout << setfill(' ');
    ll i = 0;
    for (auto n : size)
    {
        std::cout << "| N = " << setw(7) << left << n;
        for (ll j = 0; j < 3; j++)
        {
            if (j == 0)
                std::cout << "| Separate Chaining | ";
            else if (j == 1)
                std::cout << "|" << setw(34) << right << "| Double Hashing    | ";
            else
                std::cout << "|" << setw(34) << right << "| Custom Probing    | ";

            for (long long k = 0; k < 2; k++)
            {
                for (long long m = 0; m < 2; m++)
                {
                    if (m == 0)
                        std::cout << defaultfloat << setw(5) << setprecision(5) << right << report[i][j][k][m] << "  ";
                    if (m == 1)
                        std::cout << fixed << setw(2) << setprecision(3) << " " << report[i][j][k][m] << "  ";
                }

                std::cout << "| ";
            }

            std::cout << endl;
        }

        std::cout << "|" << setw(69) << setfill('_') << "|" << endl;
        std::cout << setfill(' ');
        i++;
    }

    return 0;
}

// chaining obj(10,1,1);
// obj.insert("apple",1);
// obj.insert("hello",2);
// obj.insert("abc",3);
// obj.insert("cde",4);
// obj.insert("efg",5);
// obj.insert("ghi",6);
// obj.insert("ieij",7);
// obj.insert("yfsty",8);
// obj.insert("idiudh",9);
// obj.insert("deiuygsw",10);
// obj.insert("srdrea",11);
// obj.insert("gsuutsfu",12);

// obj.print();

// cout<<"adding more key and values: "<<endl;
// obj.insert("giyguy",13);
// obj.insert("bsuyiw",14);
// obj.insert("sdvu",15);
// obj.insert("susy",16);

// obj.print();

// cout<<"after removing"<<endl;
// obj.remove("ghi");
// obj.remove("hello");
// obj.remove("efg");
// obj.print();