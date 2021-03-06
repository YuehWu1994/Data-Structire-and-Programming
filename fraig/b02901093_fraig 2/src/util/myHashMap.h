/****************************************************************************
  FileName     [ myHashMap.h ]
  PackageName  [ util ]
  Synopsis     [ Define HashMap and Cache ADT ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2009-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef MY_HASH_MAP_H
#define MY_HASH_MAP_H

#include <vector>

using namespace std;

// TODO: (Optionally) Implement your own HashMap and Cache classes.

//-----------------------
// Define HashMap classes
//-----------------------
// To use HashMap ADT, you should define your own HashKey class.
// It should at least overload the "()" and "==" operators.
//
class HashKey
{
public:
   HashKey() {}
   HashKey(size_t i0, size_t i1): in0(i0), in1(i1){}
   ~HashKey() {}
 
   //int operator() () const{};
 
   bool operator == (const HashKey& k) const {
      if((in0 == k.in0 && in1 == k.in1) || (in0 == k.in1 && in1 == k.in0)) return true;
      else return false;
   }
   // testing 
   size_t getG0()const { return in0; }

private:
      size_t in0, in1;
};

class HashData
{
public:
   HashData() {}
   HashData(size_t g): g0(g) {}
   ~HashData() {}
 
   size_t operator() () const;
   size_t getG0()const { return g0; }
 
private:
      size_t g0;   
};

template <class HashKey, class HashData>
class HashMap
{
typedef pair<HashKey, HashData> HashNode;

public:
   HashMap(size_t b=0, size_t i = 0) : _numBuckets(0), _buckets(0), _idx(i) { if (b != 0) init(b); }
   ~HashMap() { reset(); }

   class iterator
   {
      friend class HashMap<HashKey, HashData>;

   public:
      

   private:
   };

   void init(size_t b) {
      reset(); _numBuckets = b; _buckets = new vector<HashNode>[b]; }
   void reset() {
      _numBuckets = 0;
      if (_buckets) { delete [] _buckets; _buckets = 0; }
   }
   void clear() {
      for (size_t i = 0; i < _numBuckets; ++i) _buckets[i].clear();
   }
   size_t numBuckets() const { return _numBuckets; }

   vector<HashNode>& operator [] (size_t i) { return _buckets[i]; }
   const vector<HashNode>& operator [](size_t i) const { return _buckets[i]; }


   // return true if no valid data
   bool empty() const {
      for(int i = 1; i <= _numBuckets; i++){
         if(_buckets[i-1].empty() == false) return false;
      }
      return true;
   }
   // number of valid data
   size_t size() const {
      size_t s = 0;
      for(int i = 1; i <= _numBuckets; i++){
         if(_buckets[i-1].empty() == false)   s = s + _buckets[i-1].size();
      }
      return s;
   }

   // check if k is in the hash...
   // if yes, return true;
   // else return false;
   size_t check(const HashKey& k) const {
      if(empty()) return 0;
      for(size_t i = 0; i < _idx; i++){
         if(_buckets[i][0].first == k) return _buckets[i][0].second.getG0();
      }    
      return 0;
   }

   // return true if inserted d successfully (i.e. k is not in the hash)
   // return false is k is already in the hash ==> will not insert
   bool insert(HashKey& k, const HashData& d) {
      // make_pair
      HashNode p(k, d);
      _buckets[_idx].push_back(p);
      //cout << _idx << ' ' << _buckets[0][0].first.getG0();
      _idx ++;
      return true;
   }


private:
   size_t                   _numBuckets;
   vector<HashNode>*        _buckets;
   size_t                   _idx;                                             // to the current capacity
   /*
   size_t bucketNum(const HashKey& k) const {
      return k();}
   */
};

//---------------------
// Define Cache classes
//---------------------
// To use Cache ADT, you should define your own HashKey class.
// It should at least overload the "()" and "==" operators.
//
// class CacheKey
// {
// public:
//    CacheKey() {}
//    
//    size_t operator() () const { return 0; }
//   
//    bool operator == (const CacheKey&) const { return true; }
//       
// private:
// }; 
// 
/*
template <class CacheKey, class CacheData>
class Cache
{
typedef pair<CacheKey, CacheData> CacheNode;

public:
   Cache() : _size(0), _cache(0) {}
   Cache(size_t s) : _size(0), _cache(0) { init(s); }
   ~Cache() { reset(); }

   // NO NEED to implement Cache::iterator class

   // TODO: implement these functions
   //
   // Initialize _cache with size s
   void init(size_t s) { reset(); _size = s; _cache = new CacheNode[s]; }
   void reset() {  _size = 0; if (_cache) { delete [] _cache; _cache = 0; } }

   size_t size() const { return _size; }

   CacheNode& operator [] (size_t i) { return _cache[i]; }
   const CacheNode& operator [](size_t i) const { return _cache[i]; }

   // return false if cache miss
   bool read(const CacheKey& k, CacheData& d) const {
      size_t i = k() % _size;
      if (k == _cache[i].first) {
         d = _cache[i].second;
         return true;
      }
      return false;
   }
   // If k is already in the Cache, overwrite the CacheData
   void write(const CacheKey& k, const CacheData& d) {
      size_t i = k() % _size;
      _cache[i].first = k;
      _cache[i].second = d;
   }

private:
   // Do not add any extra data member
   size_t         _size;
   CacheNode*     _cache;
};

*/
#endif // MY_HASH_H
