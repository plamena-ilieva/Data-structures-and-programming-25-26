#include <unordered_set>
#include <unordered_map>


#include <set>

//вар1: 
struct Apple
{
    int weight;
    int reddess;
};
bool operator<(const Apple& lhs, const Apple& rhs)
{
    return true;
}
void f()
{
    std::set<Apple> s;

    s.insert(Apple{ 3,4 });
}

//вар2: 
struct Pear {
    int a;
    int b;
};
struct PearCompare
{
    bool operator()(const Pear& first, const Pear& second) const
    {
        return first.a < second.a;
    }
};

void g()
{
    std::set <Pear, PearCompare> p;
    p.insert(Pear{});
    p.insert(Pear{});
    p.insert(Pear{});
    p.insert(Pear{});
    p.insert(Pear{});
}
struct Hasher
{
    auto operator()(const std::string& obj) const
    {
        return obj.size();
    }
};
#include <set>
int main() {

    {
 
        std::multiset<int>; // map стойност -> бройка

        std::unordered_set<std::string, Hasher> us;

        us.insert("dasdasrwe");
        us.insert("2test");

        us.insert("asdasfsdfsdfsdf");

        us.insert("s");


        //iterate by copy
        for (const std::string& curr : us)
        {
            std::cout << curr << std::endl;
        }
    }

}
