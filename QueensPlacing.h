#ifdef MACROS

 //columns of the chessboard
 #ifdef REDUCED
  #define CHOICES \
   a,b,c,d
 #else
  #define CHOICES \
   a,b,c,d,e,f,g,h
 #endif

 //rows of the chessboard
 #ifdef REDUCED
  #define DECISIONS \
   row0,row1,row2,row3
  #else
  #define DECISIONS \
   row0,row1,row2,row3,row4,row5,row6,row7
  #endif

 //number of choices
 #ifdef REDUCED
  #define NCHOICES 4
 #else
  #define NCHOICES 8
 #endif

 //array of choice strings
 #ifdef REDUCED
  #define ACHOICES "a","b","c","d"
 #else
  #define ACHOICES "a","b","c","d","e","f","g","h"
 #endif

 //number of decisions
 #ifdef REDUCED
  #define NDECISIONS 4
 #else
  #define NDECISIONS 8
 #endif

 //array of decision strings
 #ifdef REDUCED
  #define ADECISIONS "row0","row1","row2","row3"
 #else
  #define ADECISIONS "row0","row1","row2","row3","row4","row5","row6","row7"
 #endif

#else

 bool Validator(tCombinationIterator begin_decision,tCombinationIterator end_decision,float &n_checks)
 {
  Decision last_decision=Decision(end_decision-begin_decision-1);
  #ifdef DEBUG2
   cout << "last queen row: " << aDecisions[static_cast<unsigned int>(last_decision)]<< endl;
  #endif
  Choice last_choice=*(end_decision-1);
  #ifdef DEBUG2
   cout << "last queen column: " << aChoices[static_cast<unsigned int>(last_choice)] << endl;
  #endif
  //comparison needs to be performed only with the queens in the previous rows
  // because there are no more queens placed yet
  for(unsigned int other_decision=0;other_decision<static_cast<unsigned int>(last_decision);other_decision++)
  {
   #ifdef DEBUG2
   cout << "other queen row: " << other_decision << endl;
   #endif
   //validity needs to be checked only for those neighbors, which are following begin_decision
   // where validity check means that two the new queens do not attack the already placed one
   // because validity was already checked for those queens, which are preceeding the begin_decision
   Choice other_choice;
   other_choice=Combination[static_cast<int>(other_decision)];
   #ifdef DEBUG2
   std::cout << " and this: " << aChoices[static_cast<unsigned int>(other_choice)] << std::endl;
   #endif
   n_checks++;
   if(other_choice==last_choice)
   {
    //if they occupy the same column, then they are attacking each other, and that would violate the restriction
    // they cannot occupy the same row, due to the nature of the process, because we are trying to place
    // only one queen in a row, and the decision is only where to place the queens in its own row
    #ifdef DEBUG2
    cout << "is a fail: same column" << endl;
    #endif
    return false;
   }
   int OtherqueenRow=other_decision;
   int LastqueenRow=last_decision;
   unsigned int QueensRowdistance;
   QueensRowdistance=abs(OtherqueenRow-LastqueenRow);
   int OtherqueenColumn=other_choice;
   int LastqueenColumn=last_choice;
   unsigned int QueensColumndistance;
   QueensColumndistance=abs(OtherqueenColumn-LastqueenColumn);
   nChecks++;
   if(QueensRowdistance==QueensColumndistance)
   {
    //is is also a fail if the distance between their rows and columns is the same
    // because it would means that they are on the same diagonal
    #ifdef DEBUG2
    cout << "fail: same diagonal" << endl;
    #endif
    return false;
   }
   #ifdef DEBUG2
   cout << "placement is good, we can continue with the next 'other queen'" << std::endl;
   #endif
  }
  #ifdef DEBUG2
  cout << "no error in the placement so far, we can continue with placing a new queen on the board" << endl;
  #endif
  return true;
 }

 bool FinalValidator(float &n_checks)
 {
  unsigned long int nErrors=0;
  for(int i=0;i<NDECISIONS;i++)
  {
   cout << "current decision: " << aDecisions[i] << endl;
   Choice current_choice;
   current_choice=Combination[i];
   cout << "current choice: " << aChoices[current_choice] << endl;
   for(int j=0;j<NCHOICES;j++)
   {
    cout << "its concurrent decision " << j << ": " << aDecisions[j] << endl;
    Choice concurrent_choice=Combination[j];
    cout << " and the choice of that concurrent decision: " << aChoices[concurrent_choice] << endl;
    //if the two queens are not the same, then we check the requirements
    if(i!=j)
    {
     n_checks++;
     //it is an error, if
     if((current_choice==concurrent_choice)||(abs(i-j)==abs(current_choice-concurrent_choice)))
     {
      // they are in the same colum or they are on the same diagonal
      nErrors++;
     }
    }
    cout << endl;
   }
  }
  if(nErrors>0)
   return false;
  return true;
 }

#endif
