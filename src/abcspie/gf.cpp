#include <iostream>
#include <string>

using namespace std;

const unsigned int gf = 95;

int main(int argc, char const *argv[])
{
    bool found;
    cout << "{";
    for (size_t i = 0; i < gf; i++)
    {
        found = false;
        for (size_t j = 0; j < gf; j++)
        {
            if (((i * j) % gf) == 1)
            {
                found = true;
                cout << " " << j << ",";
            }
        }
        if (!found)
        {
            cout << " " << i << ",";
        }
    }

    cout << "}" << endl;

    for (size_t i = 0; i < gf; i++)
    {
        char c = i + 32;
        cout << c;
    }
    cout << endl;

    return 0;
}
