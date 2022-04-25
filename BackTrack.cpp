#include <assert.h>

#include <functional>
using std::unary_function;
using std::binary_function;
#include <string>
typedef std::string string;
#include <list>

#include "BackTrack.h"

//#define DEBUG2 //a leheto legreszletesebb kiiratas

//actual task that we want to solve by backtrack
//#define MAPCOLORING //set different colors for a map, no neighboring coutries should have the same color
#define QUEENSPLACING //place n queens on an n x n chessboard, none of them should attacked another
//#define CUBEREARRANGING //solve a scrambled twisty puzzle (puzzlesolving)

//#define REDUCED //kis szamossagu Choice es Decision, jobban debuggolhato
#undef REDUCED //valodi problema, nem csak REDUCED

/*
There are five steps in using the backtracking algorithm: 
1. Define the types. 
2. Define the operators. 
3. Define a validator function. 
4. Construct a BackTrack object. 
5. Call it. 
*/

/*
1. Define the types 
-------------------
The BackTrack class has three template arguments:
 template<class T, class I, class V>class BackTrack {...};
T is the type of data being stored in the container, and
I is the iterator type for the container.
V is a user-defined boolean function that will return true if the current decision tree is valid.

You will use a T enum of Choice, and a vector (or just an array) of Decisions for the Combination.
*/

//betoltjuk a megfelelo headerbol a MACRO-kat
#define MACROS
#if defined(MAPCOLORING)
 #include "MapColoring.h"
#elif defined(QUEENSPLACING)
 #include "QueensPlacing.h"
#elif defined(CUBEREARRANGING)
 #include "CubeRearranging.h"
#else
#endif

//possible choices, each Decision will choose one of these Choices, so will be the Combination made up

//Choice
enum Choice{CHOICES};

//Decision
enum Decision{DECISIONS};

/*
Add some constants, enums, string arrays and typdefs to make the code more clear,
 also declare the Combination and its iterator:
*/

const unsigned int nChoices=NCHOICES;
string aChoices[nChoices]={ACHOICES};
const unsigned int nDecisions=NDECISIONS;
string aDecisions[nDecisions]={ADECISIONS};

typedef vector<Choice> tCombination;
tCombination Combination;
typedef tCombination::iterator tCombinationIterator;
tCombinationIterator itCombination;

/*
2. Define the Operators
-----------------------
BackTrack uses the following operators on T: &, ==, !=, =, and ++ (prefix).
The compiler predefines these operators for int.
If you are using int for T, your work is done.
However, ++ is not defined for enum Choice. So define it like this:
*/
inline Choice& operator++(Choice &c)
{
 c=Choice(static_cast<int>(c)+1);
 return c;
}

/*
3. Define a Validator Function
------------------------------
Derive your validator function from std::binary_function.
You might need some helper structure for it, like the Neighbor matrix in case of
 the MapColoring problem.
In case of the N-queens problem there is no need for a helper structure.
*/

//betoltjuk a megfelelo headerbol a nem MACRO-kat
#undef MACROS
#if defined(MAPCOLORING)
 #include "MapColoring.h"
#elif defined(QUEENSPLACING)
 #include "QueensPlacing.h"
#elif defined(CUBEREARRANGING)
 #include "CubeRearranging.h"
#else
#endif

struct ValidChoice: public binary_function<tCombinationIterator,tCombinationIterator,bool>
{
 bool operator()(const tCombinationIterator &begin_decision,const tCombinationIterator &end_decision) const
 {
  /*
  The validator function takes iterators pointing to the beginning and end of the
   Combination vector of Decisions.
  This function should return true if the requirements are met.
  Remember that at the time of the call every element except the last
   has already been checked for validity, so you only need to check
   that the back element, *(end-1), is valid.
  The problem statement almost always exactly defines what the validator needs to test.
  */
  return Validator(begin_decision,end_decision);
 }
};

void InitCombination()
{
 for(unsigned int iDecision=0;iDecision<nDecisions;iDecision++)
 {
  Combination.push_back((Choice)0);
 }
}

void printcombination(tCombinationIterator itDecision)
{
 std::cout << std::endl;

 if(itDecision!=Combination.end())
  std::cout << "this is a partial candidate for a solution to the problem:" << std::endl;

 unsigned int i_print=0;
 for(tCombinationIterator it_print=Combination.begin();it_print!=itDecision;it_print++)
 {
  #if defined(MAPCOLORING)
  std::cout << " color of ";
  #endif
  cout << aDecisions[i_print];
  std::cout << " should be " << aChoices[static_cast<unsigned int>(*it_print)] << std::endl;
  i_print++;
 }

 std::cout << std::endl;

}

struct PrintCombination:public unary_function<tCombinationIterator,bool>
{
 bool operator()(const tCombinationIterator end_decision) 
 {
  printcombination(end_decision);
  return true;
 }
};

int main(int argc,char* argv [])
{

 /*
 4. Construct a BackTrack Object
 -------------------------------
 To evaluate the decision tree the algorithm needs to know the valid range for T, the type.
 The BackTrack constructor accepts these values as parameters:
 BackTrack(const T&  first, const T&  last);
 Now you can construct a BackTrack object and initialize the Combination.
 */
 BackTrack<Choice,tCombinationIterator,ValidChoice,PrintCombination>Backtrack(Choice(0),Choice(nChoices-1));

 /*
 Set the initial value of the combination, for example set each decision to the first possible choice.
 Also initialize any helper object that you will use in the Validator function.
 */
 InitCombination();

 #if defined(MAPCOLORING)
  BuildMap();
 #elif defined(QUEENSPLACING)
 #else
 #endif

 /*
 //5. Call the BackTrack Object
 //----------------------------
 BackTrack's operator() takes the begin and end iterators to your container,
  along with a bool parameter that specifies whether this is the first call.
 */

 bool FirstFind=true;

 //valid layout of non-attacking queens on a chess board
 unsigned int i_solution=0;
 while(true)
 {

  //call the backtrack function object
  //This function returns true if a valid solution was found.
  //If one was found, the tree now contains the coloring for each state.
  bool Valid;
  Valid=Backtrack(Combination.begin(),Combination.end(),FirstFind);

  /*
  Many problems, including map coloring, have multiple solutions.
  Once you have found the first solution you can call operator() again to get the next solution.
  This works because the current position in the tree and the solution have the same representation.
  Backtracking from the current solution will result in the next valid solution to be found.
  The variable FirstTime is set to false when operator() is called,
   guaranteeing that subsequent calls find the next solution.
  */

  //valid most a Combination tartalma?
  cout << "one session ended - one Decision is made, so one Choice is selected" << endl << endl;
  if(!Valid)
  {
   //ha nem lett eredmeny
   cout << "and no solution (valid Combination) was found this time"<< endl;
   return 0;
  }
  PrintCombination();
  i_solution++;
  std::cout << i_solution << ". solution ready, hit Enter to continue..." << std::endl;
  char enter=getchar();
 }

 //=================================================================================

 return 0;

}

/*
Implementation Details
----------------------
operator() starts by creating an empty tree.
It generates the first node by calling CreateLeftLeaf.
This private function takes an iterator pointing to the end of the container, and
 appends the first valid value of T, which is stored in the private variable left_child.
operator() now enters a loop that will generate the lower levels of the tree.
The loop first passes the decision tree to the function bool FindValidSibling().
This function finds the first valid sibling of the current leaf.
At the time of call the current leaf has not been checked for validity, so
 the function first checks if this leaf is valid.
It does this by calling the user-defined validator function stored in the private variable IsValid.
If the leaf is valid, FindValidSibling returns true without changing the decision tree.
However, if the leaf is invalid, FindValidSibling will generate the
 next sibling to the leaf by using operator++ to increment the leaf's value.
FindValidSibling successively calls IsValid and then increments the leaf
 until IsValid returns true or all siblings have been generated without success.
If a valid sibling is found, true is returned.
operator() checks the result of FindValidSibling.
If it returned true, the node is valid.
If the tree has been completely generated, the solution is valid and operator() returns true.
Otherwise operator() must generate the next level in the tree and test it.
So it calls CreateLeftLeaf and returns to the top of the loop,
 causing FindValidSibling to be called on the new tree.
However, if the node was invalid, operator() must now backtrack to a valid node.
Function VisitNewNode accomplishes this.
It backs up one level as long as the current leaf is the last valid value of T,
 which is stored in private variable right_child.
Once VisitNewNode finds a leaf unequal to right_child,
it creates a new leaf by incrementing the current leaf's value and returns true.
VisitNewNode returns false if it returns all the way to the root,
 having searched the entire tree.

Efficiency
----------
How a problem is represented greatly influences how long it takes to find a solution.
You must consider two things.
First, the nearer to the root you can prune the tree the greater the reduction in run time.
Second, you should remember that whenever the validator function is called,
 all but the last element have already been validated.
Consider map coloring. You can color the states in any order you want.
Suppose you order the states alphabetically.
The algorithm would first color Alabama, then Arizona.
Because these states are not adjacent, you would never be able to prune the tree at this level,
 since all possible colorings of these two states can lead to valid solutions.
However, if you order the states by adjacency, so that Maine is colored first,
 followed by New Hampshire, you can prune at this level.
Of the 16 nodes at level 2, four will be pruned, which removes over 1029 nodes from consideration.

Conclusion
----------

Using my BackTrack class is straightforward.
The hardest task is writing the validator function, but even this is easy,
 as the problem statement completely defines its functionality.
I can typically whip up a solution in half an hour or less.
After a few attempts I expect other users will be able to do the same.
Choosing the best algorithm for a combinatorial problem is beyond the scope of this paper.
There are many combinatorial problems for which backtracking does not work, or
 does not work quickly enough.
The best survey of these algorithms that I have found is the book
 Heuristics: Intelligent Search Strategies for Computer Problem Solving, by Judea Pearl [2].
While out of print, the book's clear presentation of the topic will
 more than repay the effort it may take to find it.
Even when backtracking is not the best choice, my class can still be useful.
You can use it to unit test your specialized algorithm.
Better yet, use BackTrack as a backup debug-only algorithm to double check
 the results of the specialized algorithm, using #ifdef #endif blocks
 to remove the code from your production builds.
(This technique is discussed in Steve Maguire's Writing Solid Code [3].)
 
References
----------
[1] Bjarne Stroustrup. The C++ Programming Language, 3rd Edition (Addison-Wesley, 1997), p. 514.
[2] Judea Pearl. Heuristics: Intelligent Search Strategies for Computer Problem Solving (Addison-Wesley, 1984).
[3] Steve Maguire. Writing Solid Code (Microsoft Press, 1993), pp. 33-38.
 
Roger Labbe is the C++ Simulation Manager for DCS Corporation in Virginia, where
 he develops and manages avionics simulations as well as flight planning software.
He has previously developed embedded software for flight management computers.

*/
