/*
* Original author details:
* ------------------------
* Roger Labbe
* https://www.linkedin.com/in/roger-labbe-1b530944
* https://github.com/rlabbe
* .
* rlabbejr@gmail.com
* linkedin.com/in/roger-labbe-1b530944
* Principal Engineer, Research and Development/Special Projects
* Company Name: Sportvision
* Dates Employed: Feb 2012 – Present [2021]
* Employment Duration: 9 yrs 11 mos
* Location: Fremont, CA
*
* Original article:
* -----------------
* link to Wikipedia, where the actual link was found:
*  https://en.wikipedia.org/wiki/Backtracking
* actual link to Dr. Dobbs Journal archive
*  https://www.drdobbs.com/cpp/solving-combinatorial-problems-with-stl/184401194
* 
* Minor changes, comments, renames, debugging
* -------------------------------------------
* Sandor Barabas
* https://github.com/iiibs
*/

//Listing 1: An STL-style backtracking functor

#ifndef BackTrack_h
#define BackTrack_h

#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <vector>
using std::vector;
#include <map>
using std::map;

template
<
 class T,
 class I,
 class V,
 class P
>
class BackTrack
{
 public:

 // precondition: first <= last
 BackTrack(const T&  first, const T&  last);

 // Finds the next solution to the problem. Repeated calls 
 // will find all solutions to a problem if multiple solutions 
 // exist.
 // Returns true if a solution was found.
 //
 // Set first to true to get the first solution.
 //
 bool operator() (const I& begin, I end, bool& first);

 private:
 // Finds the next valid sibling of the leaf (end-1). 
 // Returns true is if a valid sibling was found.
 bool FindValidSibling (const I& begin, const I& end);

 // Backtracks through the decision tree until it finds a node
 // that hasn't been visited. Returns true if an unvisited 
 // node was found.
 bool VisitNewNode (const I& begin, I& end);

 void CreateLeftLeaf (I& end);

 T left_child;
 T right_child;

 V IsValid;
 #ifdef DEBUG2
 P Print;
 #endif

};

template <class T, class I, class V,class P>
BackTrack<T,I,V,P>::BackTrack(const T& first, const T& last) 
   : left_child (first), right_child (last)
{
}

template <class T, class I, class V,class P>
bool BackTrack<T,I,V,P>::VisitNewNode(const I& begin, I& end)
{
   // ALGORITHM:
   //
   // If the current node is the rightmost child we must 
   // backtrack one level because there are no more children at 
   // this level. So we back up until we find a non-rightmost 
   // child, then generate the child to the right. If we back 
   // up to the top without finding an unvisted child, then all 
   // nodes have been generated.

   // Back up as long as the node is the rightmost child of 
   // its parent.
   while (end-begin > 0 && *(end-1) == right_child)
      --end;

   if(end==begin)
    return false;
   
   I back = end-1;
   if (end-begin > 0 && *back != right_child) {
      ++(*back);
      return true;
   } else
      return false;
}

template <class T, class I, class V,class P> 
bool BackTrack<T,I,V,P>::FindValidSibling
(const I& begin, const I& end)
{
   // Note that on entry to this routine the leaf has not yet 
   // been used or tested for validity, so the leaf is 
   // considered a "sibling" of itself.

   I back = end-1;
   while (true) {
      if (IsValid (begin, end))
         return true;
      else if (*back != right_child)
         ++(*back);
      else
         return false;
   }
}

template <class T, class I, class V,class P>
inline void BackTrack<T,I,V,P>::CreateLeftLeaf (I& end)
{
   *(end++) = left_child;
}

template <class T, class I, class V,class P>
bool BackTrack<T,I,V,P>::operator()
(const I& begin, I end, bool& first)
{
 //const int size = end - begin;
 const __int64 size=end-begin;
 #ifdef DEBUG2
 cout << "size: " << size << endl;
 #endif

 // If first time, need to create a root.
 // Otherwise need to visit new node since vector
 // contains the last solution.
 if(first)
 {
  #ifdef DEBUG2
  cout << "this is the first time that BackTrack operator is called " << endl;
  #endif
  first=false;
  end=begin;
  CreateLeftLeaf(end);
 }
 else if(!VisitNewNode(begin,end))
  return false;

 while(true)
 {
  if(FindValidSibling(begin,end))
  {
   if(end-begin<size)
   {
    CreateLeftLeaf(end);
   }
   else
   {
    #ifdef DEBUG2
    Print(end);
    #endif
    return true;
   }
  }
  else if(!VisitNewNode(begin,end))
   return false; // the tree has been exhausted, 
                 // so no solution exists.
 }
}

#endif
