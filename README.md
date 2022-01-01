# Symbol-table-for-strings
Symbol table for strings **optimized for many key requests without wasting memory**.

### Structure
ST.h is a first-class ADT, which provides the basic functions of data collections.

The internal structure is made with an ordered vector of items containing correlated 
string and id, this allows a search cost (dichotomous) O(logN) for the keys,
and with the addition of a vector (which exploits the relationship between ID and index)
makes direct access O(1) via ID possible.

### Complexity

- STinsert -> O(n)
- STsearch(from key get value) -> O(1)
- STsearchIndex( from value to key) -> O(logN)
