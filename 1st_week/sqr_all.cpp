#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename I> I Sqr(I initial_number);
template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> initial_pair);
template <typename T> vector<T> Sqr(vector<T> initial_vector);
template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> initial_map);

template <typename I> I Sqr(I initial_number) {
    return initial_number * initial_number;
}

template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> initial_pair) {
    return make_pair(Sqr(initial_pair.first), Sqr(initial_pair.second));
}

template <typename T> vector<T> Sqr(vector<T> initial_vector) {
    for (T& element : initial_vector) {
        element = Sqr(element);
    }
    return initial_vector;
}

template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> initial_map) {
    for (auto& element : initial_map) {
        element.second = Sqr(element.second);
    }
    return initial_map;
}

int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    return 0;
}
