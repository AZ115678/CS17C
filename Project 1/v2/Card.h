#include <string>
using namespace std;
class Card{

    private:
        int value;
        string color, name;
        bool isSpecial = false;

    public:
        Card();
        Card(string, int);
        Card(string, int, bool);
        Card(string, string, int, bool);
        string getName(){return name;}
};