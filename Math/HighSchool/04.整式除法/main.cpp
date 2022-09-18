#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <algorithm>
#include <memory>
#include <string>
#include <assert.h>

struct Item {
    int coefficient{};
    int exponent{};

    Item operator*(const Item& rhs) const {
        return Item{ coefficient * rhs.coefficient, exponent + rhs.exponent };
    }

    Item& operator*=(const Item& rhs) {
        coefficient *= rhs.coefficient;
        exponent += rhs.exponent;
        return *this;
    }

    Item operator/(const Item& rhs) const {
        return Item{ coefficient / rhs.coefficient, exponent - rhs.exponent };
    }
    
    Item& operator/=(const Item& rhs) {
        coefficient /= rhs.coefficient;
        exponent -= rhs.exponent;
        return *this;
    }

    std::string toString() const {
        return std::to_string(coefficient) + " " + std::to_string(exponent);
    }
};

using ItemPtr = std::shared_ptr<Item>;

struct Polynomial {
    std::list<ItemPtr> items{};

    bool empty() const {
        return items.empty() || (items.size() == 1 && items.front()->coefficient == 0);
    }

    void append(Item item, bool force = false) {
        if (item.coefficient == 0 && !force) {
            return;
        }

        if (items.empty()) {
            items.push_back(std::make_shared<Item>(item));
            return;
        } else if (items.size() == 1 && items.front()->coefficient == 0) {
            items.front()->coefficient = item.coefficient;
            items.front()->exponent = item.exponent;
            return;
        }

        auto iter = items.begin();
        while (iter != items.end()) {
            if ((*iter)->exponent == item.exponent) {
                (*iter)->coefficient += item.coefficient;
                if ((*iter)->coefficient == 0) {
                    items.erase(iter);
                }
                return;
            } else if ((*iter)->exponent < item.exponent) {
                items.insert(iter, std::make_shared<Item>(item));
                return;
            } else {
                iter++;
            }
        }
        items.push_back(std::make_shared<Item>(item));
    }

    // 以指数递降排列
    void sort() {
        items.sort([](const ItemPtr& a, const ItemPtr& b) {
            return a->exponent > b->exponent;
        });
    }

    // 无元素时以{0, 0}表示
    void justify() {
        if (items.empty()) {
            items.push_back(std::make_shared<Item>(Item{ 0, 0 }));
        }
    }

    // 化简，合并同类项、消除零系数项
    void simplify() {
        do {
            if (items.empty()) {
                break;
            }
            sort();
            auto iter = items.begin();
            while (iter != items.end() && (*iter)->coefficient == 0) {
                iter = items.erase(iter);
            }
            if (iter == items.end()) {
                break;
            }
            auto prev = *iter++;
            while (iter != items.end()) {
                if ((*iter)->coefficient == 0) {
                    iter = items.erase(iter);
                } else if (prev->exponent == (*iter)->exponent) {
                    prev->coefficient += (*iter)->coefficient;
                    iter = items.erase(iter);
                } else {
                    prev = *iter++;
                }
            }

            iter = items.begin();
            while (iter != items.end()) {
                if ((*iter)->coefficient == 0) {
                    iter = items.erase(iter);
                } else {
                    iter++;
                }
            }

        } while (0);

        justify();
    }

    // 化繁，使得从最高次幂到最低次幂，每项都有元素（以系数为0的元素填充）
    void complicate() {
        simplify();
        auto front = items.front();
        auto back = items.back();
        for (int i = 0; i < front->exponent; i++) {
            if (i != back->coefficient) {
                append(Item{ 0, i }, true);
            }
        }
    }

    Polynomial operator+(const Polynomial& rhs) const {
        Polynomial c;
        for (const auto& item : items) {
            c.append(*item);
        }
        for (const auto& item : rhs.items) {
            c.append(*item);
        }
        c.simplify();
        return c;
    }
    
    Polynomial operator-(const Polynomial& rhs) const {
        Polynomial c;
        for (const auto& item : items) {
            c.append(*item);
        }
        for (const auto& item : rhs.items) {
            c.append(Item{ -item->coefficient, item->exponent });
        }
        c.simplify();
        return c;
    }

    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial c;
        for (const auto& i : items) {
            for (const auto& j : rhs.items) {
                c.append(*i * *j);
            }
        }
        c.simplify();
        return c;
    }

    Polynomial operator*(const Item& rhs) const {
        Polynomial c;
        for (const auto& i : items) {
            c.append(*i * rhs);
        }
        c.simplify();
        return c;
    }

    Polynomial operator/(const Polynomial& rhs) const {
        Polynomial dividend = *this, divisor = rhs, res;
        dividend.complicate();
        divisor.complicate();
        res.justify();
        if (divisor.empty() || divisor.items.front()->exponent > dividend.items.front()->exponent) {
            return res;
        }

        while (!dividend.empty() && dividend.items.front()->exponent >= divisor.items.front()->exponent) {
            Item t = dividend.items.front()->operator/(*(divisor.items.front()));
            res.append(t);
            auto sub = (divisor * t);
            dividend = dividend - sub;
        }

        return res;
    }

    std::string toString() {
        justify();
        auto iter = items.begin();
        std::string res = (*iter)->toString();
        while (++iter != items.end()) {
            res += " " + (*iter)->toString();
        }
        return res;
    }
};

Polynomial readPolynomial()
{
    Polynomial p;
    int n;
    scanf("%d", &n);
    Item item;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &item.coefficient, &item.exponent);
        p.append(item);
    }
    return p;
}

void test_pta_710()
{
    // 4 3 4 - 5 2  6 1 - 2 0
    // 3 5 20 - 7 4  3 1

    /*
    15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
    5 20 -4 4 -5 2 9 1 -2 0

    */

    Polynomial a;
    a.append(Item({ 3,4 }));
    a.append(Item({ -5,2 }));
    a.append(Item({ 6,1 }));
    a.append(Item({ -2,0 }));
    Polynomial b;
    b.append(Item({ 5,20 }));
    b.append(Item({ -7,4 }));
    b.append(Item({ 3,1 }));

    auto prd = a * b;
    auto sum = a + b;
    assert(prd.toString() == "15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1");;
    assert(sum.toString() == "5 20 -4 4 -5 2 9 1 -2 0");
}

void test_整式除法()
{
    // (x^3 - 2x^2 - 4) / (x - 3) = (x^2 + x + 3) 余 5
    {
        Polynomial a; // x^3 - 2x^2 - 4
        a.append(Item({ 1,3 }));
        a.append(Item({ -2,2 }));
        a.append(Item({ -4,0 }));
        Polynomial b; // x - 3
        b.append(Item({ 1,1 }));
        b.append(Item({ -3,0 }));


        auto res = a / b; // should be x^2 + x + 3
        assert(res.toString() == "1 2 1 1 3 0");

    }

    // (x^4 - 2x^3 + 2x^2 - x - 6) / (x + 1) = (x^3 - 3x^2 + 5x - 6)
    {
        Polynomial a;
        a.append(Item({ 1,4 }));
        a.append(Item({ -2,3 }));
        a.append(Item({ 2,2 }));
        a.append(Item({ -1,1 }));
        a.append(Item({ -6,0 }));
        Polynomial b;
        b.append(Item({ 1,1 }));
        b.append(Item({ 1,0 }));


        auto res = a / b;
        assert(res.toString() == "1 3 -3 2 5 1 -6 0");
    }
}


int main()
{    
    test_pta_710();
    test_整式除法();

}