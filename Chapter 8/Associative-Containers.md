# Associative Containers

There are two kinds of associative containers in STL: unordered associative containers and ordered associative containers. 

## Unordered Associative Containers

Unordered associative containers implement unsorted data structures that can be quickly searched. Their underlying data structure are hash tables, which support *O(1)* element access.

### *unordered_set*, *unordered_multiset*

```cpp
#include <unordered_set>
```

Sets are collections of keys, in which *unordered_set* stores unique keys, while keys in *unordered_multiset* can be repeated.

**Adding:**

`us.insert(key);` Insert elements into the container. Time complexity is *O(1)*.

**Inquiry：**

`unordered_set::iterator` Iterator of the container.

`us.find(key);` Find element with specific key, and return its iterator. If no key is found, return the *end()* iterator. Time complexity is *O(1)*.

**Deleting:**

`us.erase(key);` Delete elements from the container with the key. Time complexity is *O(1)*.

`us.erase(it);` Delete elements from the container with the iterator. Time complexity is *O(1)*.

### *unordered_map*, *unordered_multimap*

```cpp
#include <unordered_map>
```

Maps are collections of key-value pairs. Keys are unique in *unordered_map*, while keys in *unordered_multimap* can be repeated.

A *pair* object has two members, *first* and *second*. In map containers, *first* refers to the key, and *second* refers to the value. We can use *make_pair()* to pack key and value into a *pair* object.

**Adding:**

`um.insert(makepair(key, value));` Insert pairs into the container. Time complexity is *O(1)*. We can also use `um.insert({key, value});`.

**Inquiry：**

`unordered_set::iterator` Iterator of the container.

`um.find(key);` Find pair with specific key, and return its iterator. If no key is found, return the *end()* iterator. Time complexity is *O(1)*.

`operator[key]` We can also use operator `[]` to get the value from a key. What needs to be paid attention to is that, if the key doesn't exist, a new pair *{key, value()}* will be inserted into the container, where the default constructor is called for the value.

**Deleting:**

`us.erase(key);` Delete pairs from the container with the key. Time complexity is *O(1)*.

`us.erase(it);` Delete pairs from the container with the iterator. Time complexity is *O(1)*.

*unordered_set* and *unordered_map* is widely used in checking or eliminating duplicates of massive data because of their excellent performance in accessing elements. In the following example, we use an *unordered_map* to count how many times each number is repeated in 100,000 numbers.

```cpp
int main() {
    const int ARR_LEN = 100000;
    int arr[ARR_LEN] = {0};
    for (int i = 0; i < ARR_LEN; ++i) {
        arr[i] = rand() % 10000 + 1;
    }
    unordered_map<int, int> dict;
    for (int k : arr) {
        map[k]++;
    }
	for (auto it = dict.begin(); it != dict.end(); ++it) {
        cout << "key: " << it->first << " count: " << it->second << endl;
    }
}
```

Since keys in an *unordered_map* is unique, we use the map to store unique numbers. If we encounter a new number, ` map[k]++` will insert a new key-value pair and increment the count by 1.

## Ordered Associative Containers

```cpp
#include <set>
#include <map>
```

Associative containers implement sorted data structures. Similar to unordered associative containers, there are also four types of ordered associative containers: *set*, *multiset*, *map* and *multimap*. The difference is that their underlying data structure is a Red-Black Tree, and elements in the container are ordered. Instead of *O(1)* in unordered associative containers, now all the operations have the time complexity of *O(log(n))*.

```cpp
int main() {
    set<int> s;
    for (int i = 0; i < 20; ++i) {
        s.insert(rand()%20 + 1);
    }
    for (int v : s) {
        cout << v << " ";	// 1 2 3 4 7 8 10 11 13 14 16 17 18 20 
    }
    return 0;
}
```

Since Red-Black Tree needs the elements to be comparable to remain sorted, we need to implement the overloaded function for operator `<` if we want to store custom class objects in the containers. What's more, *map* or *multimap* requires the existence of default constructor, because it needs to be called in operator `[]`   to insert a new pair.