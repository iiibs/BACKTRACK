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
*/

//Listing 1: An STL-style backtracking functor

#ifndef BackTrack_h
#define BackTrack_h

#ifdef _DEBUG
#define DEBUG2
#endif

#include <iostream>
using std::cout;
using std::endl;
#include <typeinfo>
#include <vector>
using std::vector;
#include <map>
using std::map;

//#define NEW
#ifdef NEW

template
<
 //type parameters for declaration
 typename itD, // type of decision (container)
 typename C, // type of choice (data being stored in the container)
 typename I, // iterator type for the container
 typename ND, //user-defined boolean function to return the next decision, if any
 typename IR, // user-definded boolean function that will return true if the current decision is related to another decision
 //typename V, // user-defined boolean function that will return true if the current decision's choice is valid
 typename P // user-defined procedure to display the current decisions
>
class BackTrack
{
 public:

 //constructor of the BackTrack class
 BackTrack
 (
  //const unsigned int, //number of decisions to be made
  //const I &, //iterator to the actual decision
  const itD //iterator to the first decision
  //const itD, //iterator to the last decision
  //const C, //iterator to the first choice
  //const C //iterator to the last choice
 );

 //Finds the next solution to the problem.
 //Repeated calls will find all solutions to a problem if multiple solutions exist.
 //Returns true if a solution was found.
 // overload function call operator: operator()
 // When a user-defined class overloads the function call operator, operator(), it becomes a FunctionObject type.
 // An object of such a type can be used in a function call expression.
 // FunctionObject call will have three parameters
 // - the decision from where it should start
 // - the decision up to where it ran
 // - bool that shows if it was the first time it was called or not
 bool operator()(itD &,bool &);

 private:

 //methods
 // Finds the next valid choice to the current choice (next valid sibling of the leaf at end-1) 
 // Returns true is if a valid choice (sibling) was found.
 bool NextValidChoice(itD &);

 // Backtracks through the decision tree until it finds a node that has not been visited.
 // Returns true if an unvisited node was found.
 bool VisitNewNode(I &);

 // Takes an iterator pointing to the end of the container, and
 // appends the first valid value of T, which is stored in the private variable FirstChoice.
 void CreateFirstChoice(I &);

 // Returns true if the decision given as parameter is valid
 bool IsValid(itD);

 //members
 //unsigned int nDecisions;
 //typedef map<unsigned int,D> mD;
 //mD mDecisions;
 //vector<vector<bool>> Adjacency;
 unsigned int iDecision; //hanyadik szempontnal tartunk
 itD FirstDecision; //az elso szempontra mutato iterator
 itD LastDecision; //az utolso szempontra mutato iterator
 C FirstChoice; //the first choice (leftmost child) of the level
 C LastChoice; //the last choice (rightmost child) of the level
 //user defined functions
 ND NextDecision; //user-defined bool function that returns the next decision (if exists) based on its parameter, which is a pointer to the actual decision
 IR IsRelated; //user-defined bool function
 //  V IsValid; //user-defined validator function
 P Print; //user-defined print function
};

//constructor of BackTrack
template<class itD,class C,class I,class IR,class ND,class P>
BackTrack<itD,C,I,IR,ND,P>::BackTrack
(
 //const unsigned int n_decisions,
 //const I &act_decision,
 const itD it_first_decision
 //const itD it_last_decision,
 //const C first_choice,
 //const C last_choice
)
 :
 //nDecisions(n_decisions),
 FirstDecision(it_first_decision)
 //LastDecision(*it_last_decision),
 //FirstChoice(first_choice),
 //LastChoice(last_choice)
{
 /*
 #ifdef DEBUG_LEVEL_2
 std::cout << "constructor of BackTrack" << std::endl;
 std::cout << "the type of data being stored in your decision vector: '" << typeid(T).name() << "'" << std::endl;
 std::cout << "iterator type for your decision vector: '" << typeid(I).name() << "'" << std::endl;
 std::cout << "the valid range for the type '" << typeid(T).name() << "' is from 'FirstChoice' to 'LastChoice'" << std::endl;
 #endif
 #ifdef DEBUG_LEVEL_2
 std::cout << "the value of 'FirstChoice' casted to 'unsigned int' is: " << static_cast<unsigned int>(FirstChoice) << std::endl;
 std::cout << "the value of 'LastChoice' casted to 'unsigned int' is: " << static_cast<unsigned int>(LastChoice) << std::endl;
 #endif
 */
 iDecision=0;
}

//BackTrack's FunctionObject: operator() takes the end() iterator of your container,
// along with a bool parameter that specifies whether this is the first call. 
template <class itD,class C,class I,class IR,class ND,class P> 
bool BackTrack<itD,C,I,IR,ND,P>::operator()(itD &it_act_decision,bool &first_time)
{
 if(first_time)
 {
  first_time=false;
  //a fa jelenlegi szintjere egy ballevelet hozunk letre, mert minden szint egy ballevellel kezdodik
  // az act_decision ez utan a hivas utan az uj end() -re mutat
  CreateFirstChoice(it_act_decision);
 }
 else
 {
  // Is there a new node that can be visited?
  if(!VisitNewNode(it_act_decision))
   // No more nodes can be visited, so return false.
   return false;
 }

 //operator() now enters a loop that will generate the lower levels of the tree. 
 while (true)
 {

  #ifdef DEBUG_LEVEL_2
  Print(it_act_decision);
  #endif

  //The loop first passes the decision tree to the function bool NextValidChoice()
  // operator() checks the result of NextValidChoice. 
  if(NextValidChoice(it_act_decision))
  {

   /*
   //If it returned true, the node is valid. 
   if(iDecision<nDecisions)
   {
    //If the tree has not been completely generated, then operator() must generate the next level
    // in the tree and test it. 
    //So it calls CreateFirstChoice (CreateLeftLeaf) and returns to the top of the loop,
    // causing NextValidChoice (FindValidSibling) to be called on the new tree.
    CreateFirstChoice(i_decision);
   }
   else
    //If the tree has been completely generated, the solution is valid and operator() returns true. 
    return true;
   */

   // checks if another decision is needed
   if(NextDecision(it_act_decision))
   {
    #ifdef DEBUG_LEVEL_2
    cout << "yes, another decision was needed, it is returned in it_decision" << endl;
    #endif
   }
   else
   {
    #ifdef DEBUG_LEVEL_2
    cout << "no more decision is needed, a valid solution is ready" << endl;
    #endif
    return true;
   }

  }
  else
  {
   //However, if the node was invalid, operator() must now backtrack to a valid node.
   // Function VisitNewNode accomplishes this.
   // It backs up one level as long as the current leaf is the last valid value of T,
   // which is stored in private variable right_child. 
   //Once VisitNewNode finds a leaf unequal to right_child, it
   // creates a new leaf by incrementing the current leaf's value and returns true. 
   if(!VisitNewNode(it_act_decision))
   {
    //VisitNewNode returns false if it returns all the way to the root, having searched the entire tree.
    // the tree has been exhausted, so no solution exists.
    return false;
   }
  }
 }
}

template<class D,class C,class I,class IR,class ND,class P>
bool BackTrack<D,C,I,IR,ND,P>::VisitNewNode(I &act_decision)
{
 // ALGORITHM:
 //
 // If the current node is the rightmost child we must 
 // backtrack one level because there are no more children at 
 // this level. So we back up until we find a non-rightmost 
 // child, then generate the child to the right. If we back 
 // up to the top without finding an unvisited child, then all 
 // nodes have been generated.

 // Backtrack on the decisions as far as the node is the last choice (rightmost child) of its parent.
 #ifdef DEBUG_LEVEL_2
 std::cout << "level of actual decision: " << iDecision << std::endl;
 std::cout << "choice of actual decision: " << static_cast<unsigned int>(*(act_decision-1)) << std::endl;
 #endif
 while(iDecision>0&&*(act_decision-1)==LastChoice)
 {
  --act_decision;
  iDecision--;
 }

 //if there is no more decision to track back to, then return with false
 if(iDecision==0)
  return false;

 //track back
 I back_decision=act_decision-1;
 if(iDecision>0&&*back_decision!=LastChoice)
 {
  ++(*back_decision);
  return true;
 }
 else
  return false;
}

template<class itD,class C,class I,class IR,class ND,class P>
bool BackTrack<itD,C,I,IR,ND,P>::IsValid(itD it_decision)
{
 //for(itD it_other_decision=FirstDecision;it_other_decision<LastDecision;it_other_decision++)
 itD it_other_decision=FirstDecision;
 do
 {
  //is other decision related to actual decision?
  if(IsRelated(it_other_decision,it_decision))
  {
   cout << "yes, the two decisions are related" << endl;
   /*
   if(IsPreceding(i_decision,act_decision))
   {
    if(IsInvalid(i_decision,act_decision))
    {
     return false;
    }
   }
   */
  }
  else
  {
   cout << "no, the two decisions are not related" << endl;
  }
 }
 while(NextDecision(it_other_decision));
 return true;
}

template<class itD,class C,class I,class IR,class ND,class P> 
bool BackTrack<itD,C,I,IR,ND,P>::NextValidChoice(itD &it_decision)
{
 // Note that on entry to this routine the leaf has not yet 
 // been used or tested for validity, so the leaf is 
 // considered a "sibling" of itself.

 itD back_decision=it_decision-1;
 //Continue while the tree has not been completely generated
 while(true)
 {
  //At the time of call the current leaf has not been checked for validity, so
  // the function first checks if this leaf is valid.
  //It does this by calling the user-defined validator function
  // stored in the private variable IsValid.
  //No, this has changed.
  // IsValid is now a private function, which is using three user-defined functions: IsRelated(), IsPreceding(), IsInvalid()
  if(IsValid(it_decision))
  {
   // If the leaf is valid, NextValidSibling returns true without changing the decision tree.
   return true;
  }
  else
  {
   //The leaf is invalid
   //Check if all choices (siblings) have been generated without success
   if(*back_decision!=LastChoice)
   {
    //Not all choices (siblings) have been generated.
    //NextValidChoice will generate the
    // next choice (sibling) to the current choice (leaf) by using operator++ to increment the choice (leaf) value
    // this will use the host's operator++ if it is defined, otherwise it will use the standard ++
    ++(*back_decision);

    #ifdef DEBUG_LEVEL_2
    Print(it_decision);
    #endif
   }
   else
   {
    return false;
   }
  }
 }
}

//This private function takes an iterator pointing to the end of the container, and
// appends the first valid value of T, which is stored in the private variable left_child.
template<class D,class C,class I,class V,class ND,class P>
inline void BackTrack<D,C,I,V,ND,P>::CreateFirstChoice(I &it_act_decision)
{
 *(it_act_decision++)=FirstChoice; //az uj szint az elso lehetseges valasztast kapja
 iDecision++;
}

#endif

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
