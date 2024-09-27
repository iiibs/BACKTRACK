#ifdef MACROS

//possible twists
 #ifdef REDUCED
  #define CHOICES \
  L1,L2,L3,R1,R2,R3
 #else
  #define CHOICES \
  U1,U2,U3,R1,R2,R3,F1,F2,F3
 #endif

 //serial number of the twist
 #ifdef REDUCED
  #define DECISIONS \
   D1,D2,D3,D4
 #else
  #define DECISIONS \
   D01,D02,D03,D04,D05,D06,D07,D08,D09,D10,D11,D12,D13,D14,D15,D16,D17,D18,D19,D20
 #endif

 //number of choices
 #ifdef REDUCED
  #define NCHOICES 6
 #else
  #define NCHOICES 9
 #endif

 //array of choice strings
 #ifdef REDUCED
  #define ACHOICES "L1","L2","L3","R1","R2","R3"
 #else
  #define ACHOICES "U1","U2","U3","R1","R2","R3","F1","F2","F3"
 #endif

 //number of decisions
 #ifdef REDUCED
  #define NDECISIONS 4
 #else
  #define NDECISIONS 48
 #endif

 //array of decision strings
 #ifdef REDUCED
  #define ADECISIONS "D1","D2","D3","D4"
 #else
  #define ADECISIONS \
  "D01","D02","D03","D04","D05","D06","D07","D08","D09","D10", \
  "D11","D12","D13","D14","D15","D16","D17","D18","D19","D20"
 #endif

#else

 struct Piece
 {
  string Name;
  string Base;
 };

 Piece Pieces[]={{"wR","a1"},{"wN","b1"},{"bP","c1"},{"wP","a2"},{"bN","b2"},{"bR","c2"}};

 string Rows[]={{"1"},{"2"}};
 string Cols[]={{"a"},{"b"},"c"};

 const unsigned int nRows=2;
 const unsigned int nCols=3;
 Piece Board[nRows][nCols];

 void SetBoard()
 {
  bool AllPiecesAtBase=true;

  /*
  //after no twist -> solution: no problem
  Board[1][0].Name="wP"; Board[1][1].Name="bN"; Board[1][2].Name="bR";
  Board[0][0].Name="wR"; Board[0][1].Name="wN"; Board[0][2].Name="bP";
  */

  //after R1 -> solution: R3
  Board[1][0].Name="wP"; Board[1][1].Name="wN"; Board[1][2].Name="bN";
  Board[0][0].Name="wR"; Board[0][1].Name="bP"; Board[0][2].Name="bR";

  for(unsigned i=0;i<nRows;i++)
  {
   for(unsigned j=0;j<nCols;j++)
   {
    cout << i << " " << j << " ";
    cout << Board[nRows-i-1][j].Name << " ";
    for(unsigned int k=0;k<nRows*nCols;k++)
    {
     if(Board[nRows-i-1][j].Name==Pieces[k].Name)
     {
      if(Pieces[k].Base!=Cols[j]+Rows[nRows-(i+1)])
      {
       AllPiecesAtBase=false;
      }
      Board[nRows-i-1][j].Base=Pieces[k].Base;
     }
    }
   }
   cout << endl;
  }
  if(AllPiecesAtBase)
  {
   cout << "no problem" << endl;
   exit(1);
  }
 }

 void PrintBoard()
 {
  for(unsigned i=0;i<nRows;i++)
  {
   for(unsigned j=0;j<nCols;j++)
   {
    cout << Board[nRows-i-1][j].Name << " ";
   }
   cout << endl;
  }
 }

 void Twist(unsigned int iDecision)
 {
  string Twist;
  Twist=aChoices[Combination[iDecision]];
  cout << "Twist: " << Twist << endl;
  if(Twist=="L1")
  {
   return;
  }
  if(Twist=="L2")
  {
   return;
  }
  if(Twist=="L3")
  {
   return;
  }
  if(Twist=="R1")
  {
   return;
  }
  if(Twist=="R2")
  {
   return;
  }
  if(Twist=="R3")
  {
   return;
  }
 }

 bool Validator(tCombinationIterator begin_decision,tCombinationIterator end_decision,float &n_checks)
 {
  return true;
 }

 bool FinalValidator(float &n_checks)
 {
  bool retval=true;

  //set board to starting status
  SetBoard();

  //perform all the twists that are decided so far
  for(unsigned int iDecision=0;iDecision<NDECISIONS;iDecision++)
  {
   Twist(iDecision);
  }

  //check the Board: is each square of the Board holding a Piece, whose Base location is just that square?
  for(unsigned i=0;i<nRows;i++)
  {
   for(unsigned j=0;j<nCols;j++)
   {
    #ifdef DEBUG3
    cout << Cols[j] << Rows[nRows-(i+1)] << endl;
    cout << Board[nRows-(i+1)][j].Name << endl;
    cout << Board[nRows-(i+1)][j].Base << endl;
    #endif
    n_checks++;
    if(Board[nRows-(i+1)][j].Base!=Cols[j]+Rows[nRows-(i+1)])
     //at least one Piece is not standing on its Base
     return false;
   }
   cout << endl;
  }
  //each Piece checked, all of them stand on their Base
  return true;
 }

 #endif
