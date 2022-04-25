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

 bool Validator(tCombinationIterator begin_decision,tCombinationIterator end_decision)
 {
  Decision last_decision=Decision(end_decision-begin_decision-1);
  #ifdef DEBUG2
   cout << "last queen row: " << aDecisions[static_cast<unsigned int>(last_decision)]<< endl;
  #endif
  Choice last_choice=*(end_decision-1);
  #ifdef DEBUG2
   cout << "last queen column: " << aChoices[static_cast<unsigned int>(last_choice)] << endl;
  #endif
  //csak az elozo row-k beli queen -ekkel kell osszehasonlitanom, mert a tobbi meg nincs elhelyezve
  for(unsigned int other_decision=0;other_decision<static_cast<unsigned int>(last_decision);other_decision++)
  {
   #ifdef DEBUG2
   cout << "other queen row: " << other_decision << endl;
   #endif
   //csak a begin_decision utani szomszedokra kell vizsgalnom a validitast (hogy nem uti oket az uj queen), mert
   // a begin_decision elotti queen-ekre mar megvolt az ellenorzes mire ideert az algoritmus
   Choice other_choice;
   other_choice=Combination[static_cast<int>(other_decision)];
   #ifdef DEBUG2
   std::cout << " es ez: " << aChoices[static_cast<unsigned int>(other_choice)] << std::endl;
   #endif
   if(other_choice==last_choice)
   {
    //ha azonos oszlopot foglalnak el, akkor utesben allnanak, tehat ez nem jo
    // az azonos sorban leves eleve kizart, mert olyan a modszer, hogy soronkent dontunk egyet
    #ifdef DEBUG2
    cout << "hiba: azonos oszlop" << endl;
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
   if(QueensRowdistance==QueensColumndistance)
   {
    //az sem jo, ha ugy allnak, hogy amennyi a soraik kozotti tavolsag, ugyanannyi az oszlopaik kozotti tavolsag,
    // mert ez azt jelentene, hogy atloban vannak
    #ifdef DEBUG2
    cout << "hiba: azonos atlo" << endl;
    #endif
    return false;
   }
   #ifdef DEBUG2
   cout << "okes az elhelyezes, mehetunk uj other queen-re" << std::endl;
   #endif
  }
  #ifdef DEBUG2
  cout << "eddig nincs hiba az elhelyezesben, feltehetunk egy uj queen-t" << endl;
  #endif
  return true;
 }

#endif
