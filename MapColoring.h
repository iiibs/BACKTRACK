#ifdef MACROS
 //colors of the map
 #ifdef REDUCED
  #define CHOICES \
  black,white
 #else
  #define CHOICES \
  blue,yellow,green,red
 #endif

 //states of the USA
 #ifdef REDUCED
  #define DECISIONS \
   A,B,C,D
 #else
  #define DECISIONS \
   AL, /*Alabama*/ \
       /*AK Alaska - not included, because it does not have any neighbor*/ \
   AZ, /*Arizona*/ \
   AR, /*Arkansas*/ \
   CA, /*California*/ \
   CO, /*Colorado*/ \
   CT, /*Connecticut*/ \
   DE, /*Delaware*/ \
   FL, /*Florida*/ \
   GA, /*Georgia*/ \
       /*HI Hawaii - not included, because it does not have any neighbor*/ \
   ID, /*Idaho*/ \
   IL, /*Illinois*/ \
   IN, /*Indiana*/ \
   IA, /*Iowa*/ \
   KS, /*Kansas*/ \
   KY, /*Kentucky*/ \
   LA, /*Louisiana*/ \
   MA, /*Massachusetts*/ \
   ME, /*Maine*/ \
   MD, /*Maryland*/ \
   MI, /*Michigan*/ \
   MN, /*Minnesota*/ \
   MS, /*Mississippi*/ \
   MO, /*Missouri*/ \
   MT, /*Montana*/ \
   ND, /*North Dakota*/ \
   NE, /*Nebraska*/ \
   NV, /*Nevada*/ \
   NH, /*New Hampshire*/ \
   NJ, /*New Jersey*/ \
   NM, /*New Mexico*/ \
   NY, /*New York*/ \
   NC, /*North Carolina*/ \
   OH, /*Ohio*/ \
   OK, /*Oklahoma*/ \
   OR, /*Oregon*/ \
   PA, /*Pennsylvania*/ \
   RI, /*Rhode Island*/ \
   SC, /*South Carolina*/ \
   SD, /*South Dakota*/ \
   TN, /*Tennessee*/ \
   TX, /*Texas*/ \
   UT, /*Utah*/ \
   VT, /*Vermont*/ \
   VA, /*Virginia*/ \
   WA, /*Washington*/ \
       /*Washington DC - not included in this problem*/ \
   WV, /*West Virginia*/ \
   WI, /*Wisconsin*/ \
   WY, /*Wyomin*/ \
       /* WO World Ocean - it can also be colored, but in this case I omitted it*/
 #endif

 //number of choices
 #ifdef REDUCED
  #define NCHOICES 2
 #else
  #define NCHOICES 4
 #endif

 //array of choice strings
 #ifdef REDUCED
  #define ACHOICES "black","white"
 #else
  #define ACHOICES "Blue","Yellow","Green","Red"
 #endif

 //number of decisions
 #ifdef REDUCED
  #define NDECISIONS 4
 #else
  #define NDECISIONS 48
 #endif

 //array of decision strings
 #ifdef REDUCED
  #define ADECISIONS "A","B","C","D"
 #else
  #define ADECISIONS \
  "AL","AZ","AR", \
  "CA","CO","CT", \
  "DE", \
  "FL", \
  "GA", \
  "ID","IL","IN","IA", \
  "KS","KY", \
  "LA", \
  "ME","MD","MA","MI","MN","MS","MO","MT", \
  "NE","NV","NH","NJ","NM","NY","NC","ND", \
  "OH","OK","OR", \
  "PA", \
  "RI", \
  "SC","SD", \
  "TN","TX", \
  "UT", \
  "VT","VA", \
  "WA","WV","WI","WY"
 #endif

#else

 //Neighbor is an array of vectors containing the neighboring information about the states,
 // it will be used to validate the choices for the decisions each.
 const unsigned int maxNeighbors=8;
 Decision Neighbor[nDecisions][maxNeighbors+1];

 //the number of neighbors that currently a state has when creating the connections between the states
 // when all the connections are set, then this number will not change further
 unsigned int NumberNeighbors[nDecisions];

 bool Validator(tCombinationIterator begin_decision,tCombinationIterator end_decision)
 {
  Decision last_state=Decision (end_decision-begin_decision-1);
  Choice last_color=*(end_decision-1);
  bool Valid=true;
  for(unsigned int i=0;i<NumberNeighbors[last_state];i++)
  {
   Decision other_decision=Neighbor[last_state][i];
   if(other_decision<last_state&&*(begin_decision+other_decision)==last_color)
    return false;
  }
  return true;
 }

 bool Validator2(tCombinationIterator begin_decision,tCombinationIterator end_decision,float &n_checks)
 {
  Decision last_state=Decision (end_decision-begin_decision-1);
  Choice last_color=*(end_decision-1);
  bool Valid=true;
  for(unsigned int i=0;i<NumberNeighbors[last_state];i++)
  {
   Decision other_decision=Neighbor[last_state][i];
   n_checks++;
   if(other_decision<last_state&&*(begin_decision+other_decision)==last_color)
    return false;
  }
  return true;
 }

 bool FinalValidator(float &n_checks)
 {
  unsigned long int nErrors=0;
  for(unsigned int i=0;i<NDECISIONS;i++)
  {
   cout << "current decision: " << aDecisions[i] << endl;
   Choice current_choice;
   current_choice=Combination[i];
   cout << "current choice: " << aChoices[current_choice] << endl;
   cout << "number of its neighbors: " << NumberNeighbors[i] << endl;
   for(unsigned int j=0;j<NumberNeighbors[i];j++)
   {
    cout << "its neighbor " << j << ": " << aDecisions[Neighbor[i][j]] << endl;
    Choice neighbor_choice=Combination[Neighbor[i][j]];
    cout << " and the choice of that neighbor: " << aChoices[neighbor_choice] << endl;
    n_checks++;
    if(current_choice==neighbor_choice)
    {
     //it is an error, if the current state and one of its neighboring state has the same color
     nErrors++;
    }
    cout << endl;
   }
  }
  if(nErrors>0)
   return false;
  return true;
 }

inline void Connect(Decision s1,Decision s2)
{

 //check if already connected
 // check each state only for the number of its neighbors
 for(unsigned int iNeighbor=0;iNeighbor<NumberNeighbors[s1];iNeighbor++)
 {
  if(Neighbor[s1][iNeighbor]==s2)
  {
   //if already connected, then return
   return;
  }
 }

 //put s2 as the currently last element of the array of neighbors to s1
 Neighbor[s1][NumberNeighbors[s1]]=s2;
 NumberNeighbors[s1]++;

 //put s2 as the currently last element of the array of neighbors to s1
 Neighbor[s2][NumberNeighbors[s2]]=s1;
 NumberNeighbors[s2]++;

 assert(NumberNeighbors[s1]<=maxNeighbors);
 assert(NumberNeighbors[s2]<=maxNeighbors);

 #ifdef DEBUG2
 cout << "connected states: ";
 cout << aDecisions[static_cast<int>(s1)];
 cout << " <-> ";
 cout << aDecisions[static_cast<int>(s2)];
 cout << endl;
 #endif

}

void BuildMap ()
{

 for(unsigned int iDecision=0;iDecision<nDecisions;iDecision++)
 {
  NumberNeighbors[iDecision]=0; //set count of neighbors to zero
  for(unsigned int jDecision=0;jDecision<nDecisions;jDecision++)
  {
   Neighbor[iDecision][jDecision]=Decision(0);
  }
 }

 #ifdef REDUCED
  Connect(Decision::A,Decision::B);
  Connect(Decision::B,Decision::A); //ez redundans, de ezt ki kell birnia, ki kell szurnie
  Connect(Decision::B,Decision::C);
  Connect(Decision::C,Decision::D);
 #else
  //itt felirtam oda-vissza a szomszedsagot, de a masodik elofordulast a program figyelmen kivul hagyja
  //State Name        Bordering States
  //----------------- ----------------
  //AL Alabama
  Connect(Decision::AL,Decision::FL); //FL Florida
  Connect(Decision::AL,Decision::GA); //GA Georgia
  Connect(Decision::AL,Decision::MS); //MS Mississippi
  Connect(Decision::AL,Decision::TN); //TN Tennessee
  //-----------------
  //AK Alaska
  // none
  //-----------------
  //AZ Arizona
  Connect(Decision::AZ,Decision::CA); //CA California
  // CO Colorado (corner touch)
  Connect(Decision::AZ,Decision::NV); //NV Nevada
  Connect(Decision::AZ,Decision::NM); //NM New Mexico
  Connect(Decision::AZ,Decision::UT); //UT Utah
  //-----------------
  //AR Arkansas
  Connect(Decision::AR,Decision::LA); //LA Louisiana
  Connect(Decision::AR,Decision::MS); //MS Mississippi
  Connect(Decision::AR,Decision::MO); //MO Missouri
  Connect(Decision::AR,Decision::OK); //OK Oklahoma
  Connect(Decision::AR,Decision::TN); //TN Tennessee
  Connect(Decision::AR,Decision::TX); //TX Texas
  //-----------------
  //CA California
  Connect(Decision::CA,Decision::AZ); //AZ Arizona
  Connect(Decision::CA,Decision::NV); //NV Nevada
  Connect(Decision::CA,Decision::OR); //OR Oregon
  //-----------------
  //CO Colorado
  // AZ Arizona (corner touch)
  Connect(Decision::CO,Decision::KS); //KS Kansas
  Connect(Decision::CO,Decision::NE); //NE Nebraska
  Connect(Decision::CO,Decision::NM); //NM New Mexico
  Connect(Decision::CO,Decision::OK); //OK Oklahoma
  Connect(Decision::CO,Decision::UT); //UT Utah
  Connect(Decision::CO,Decision::WY); //WY Wyoming
  //-----------------
  //CT Connecticut
  Connect(Decision::CT,Decision::MA); //MA Massachusetts
  Connect(Decision::CT,Decision::NY); //NY New York
  Connect(Decision::CT,Decision::RI); //RI Rhode Island
  //-----------------
  //DE Delaware
  Connect(Decision::DE,Decision::MD); //MD Maryland
  Connect(Decision::DE,Decision::NJ); //NJ New Jersey
  Connect(Decision::DE,Decision::PA); //PA Pennsylvania
  //-----------------
  //FL Florida
  Connect(Decision::FL,Decision::AL); //AL Alabama
  Connect(Decision::FL,Decision::GA); //GA Georgia
  //-----------------
  //GA Georgia
  Connect(Decision::GA,Decision::AL); //AL Alabama
  Connect(Decision::GA,Decision::FL); //FL Florida
  Connect(Decision::GA,Decision::NC); //NC North Carolina
  Connect(Decision::GA,Decision::SC); //SC South Carolina
  Connect(Decision::GA,Decision::TN); //TN Tennessee
  //-----------------
  //HI Hawaii
  // none
  //-----------------
  //ID Idaho
  Connect(Decision::ID,Decision::MT); //MT Montana
  Connect(Decision::ID,Decision::NV); //NV Nevada
  Connect(Decision::ID,Decision::OR); //OR Oregon
  Connect(Decision::ID,Decision::UT); //UT Utah
  Connect(Decision::ID,Decision::WA); //WA Washington
  Connect(Decision::ID,Decision::WY); //WY Wyoming
  //-----------------
  //IL Illinois
  Connect(Decision::IL,Decision::IN); //IN Indiana
  Connect(Decision::IL,Decision::IA); //IA Iowa
  Connect(Decision::IL,Decision::MI); //MI Michigan
  Connect(Decision::IL,Decision::KY); //KY Kentucky
  Connect(Decision::IL,Decision::MO); //MO Missouri
  Connect(Decision::IL,Decision::WI); //WI Wisconsin
  //-----------------
  //IN Indiana
  Connect(Decision::IN,Decision::IL); //IL Illinois
  Connect(Decision::IN,Decision::KY); //KY Kentucky
  Connect(Decision::IN,Decision::MI); //MI Michigan
  Connect(Decision::IN,Decision::OH); //OH Ohio
  //-----------------
  //IA Iowa
  Connect(Decision::IA,Decision::IL); //IL Illinois
  Connect(Decision::IA,Decision::MN); //MN Minnesota
  Connect(Decision::IA,Decision::MO); //MO Missouri
  Connect(Decision::IA,Decision::NE); //NE Nebraska
  Connect(Decision::IA,Decision::SD); //SD South Dakota
  Connect(Decision::IA,Decision::WI); //WI Wisconsin
  //-----------------
  //KS Kansas
  Connect(Decision::KS,Decision::CO); //CO Colorado
  Connect(Decision::KS,Decision::MO); //MO Missouri
  Connect(Decision::KS,Decision::NE); //NE Nebraska
  Connect(Decision::KS,Decision::OK); //OK Oklahoma
  //-----------------
  //KY Kentucky
  Connect(Decision::KY,Decision::IL); //IL Illinois
  Connect(Decision::KY,Decision::IN); //IN Indiana
  Connect(Decision::KY,Decision::MO); //MO Missouri
  Connect(Decision::KY,Decision::OH); //OH Ohio
  Connect(Decision::KY,Decision::TN); //TN Tennessee
  Connect(Decision::KY,Decision::VA); //VA Virginia
  Connect(Decision::KY,Decision::WV); //WV West Virginia
  //-----------------
  //LA Louisiana
  Connect(Decision::LA,Decision::AR); //AR Arkansas
  Connect(Decision::LA,Decision::MS); //MS Mississippi
  Connect(Decision::LA,Decision::TX); //TX Texas
  //-----------------
  //ME Maine
  Connect(Decision::ME,Decision::NH); //NH New Hampshire
  //-----------------
  //MD Maryland
  Connect(Decision::MD,Decision::DE); //DE Delaware
  Connect(Decision::MD,Decision::PA); //PA Pennsylvania
  Connect(Decision::MD,Decision::VA); //VA Virginia
  Connect(Decision::MD,Decision::WV); //WV West Virginia
  //-----------------
  //MA Massachusetts
  Connect(Decision::MA,Decision::CT); //CT Connecticut
  Connect(Decision::MA,Decision::NH); //NH New Hampshire
  Connect(Decision::MA,Decision::NY); //NY New York
  Connect(Decision::MA,Decision::RI); //RI Rhode Island
  Connect(Decision::MA,Decision::VT); //VT Vermont
  //-----------------
  //MI Michigan
  Connect(Decision::MI,Decision::IL); //IL Illinois
  Connect(Decision::MI,Decision::IN); //IN Indiana
  Connect(Decision::MI,Decision::OH); //OH Ohio
  Connect(Decision::MI,Decision::WI); //WI Wisconsin
  //-----------------
  //MN Minnesota
  Connect(Decision::MN,Decision::IA); //IA Iowa
  Connect(Decision::MN,Decision::ND); //ND North Dakota
  Connect(Decision::MN,Decision::SD); //SD South Dakota
  Connect(Decision::MN,Decision::WI); //WI Wisconsin
  //-----------------
  //MS Mississippi
  Connect(Decision::MS,Decision::AL); //AL Alabama
  Connect(Decision::MS,Decision::AR); //AR Arkansas
  Connect(Decision::MS,Decision::LA); //LA Louisiana
  Connect(Decision::MS,Decision::TN); //TN Tennessee
  //-----------------
  //MO Missouri
  Connect(Decision::MO,Decision::AR); //AR Arkansas
  Connect(Decision::MO,Decision::IL); //IL Illinois
  Connect(Decision::MO,Decision::IA); //IA Iowa
  Connect(Decision::MO,Decision::KS); //KS Kansas
  Connect(Decision::MO,Decision::KY); //KY Kentucky
  Connect(Decision::MO,Decision::NE); //NE Nebraska
  Connect(Decision::MO,Decision::OK); //OK Oklahoma
  Connect(Decision::MO,Decision::TN); //TN Tennessee
  //-----------------
  //MT Montana
  Connect(Decision::MT,Decision::ID); //ID Idaho
  Connect(Decision::MT,Decision::ND); //ND North Dakota
  Connect(Decision::MT,Decision::SD); //SD South Dakota
  Connect(Decision::MT,Decision::WY); //WY Wyoming
  //-----------------
  //NE Nebraska
  Connect(Decision::NE,Decision::CO); //CO Colorado
  Connect(Decision::NE,Decision::IA); //IA Iowa
  Connect(Decision::NE,Decision::KS); //KS Kansas
  Connect(Decision::NE,Decision::MO); //MO Missouri
  Connect(Decision::NE,Decision::SD); //SD South Dakota
  Connect(Decision::NE,Decision::WY); //WY Wyoming
  //-----------------
  //NV Nevada
  Connect(Decision::NV,Decision::AZ); //AZ Arizona
  Connect(Decision::NV,Decision::CA); //CA California
  Connect(Decision::NV,Decision::ID); //ID Idaho
  Connect(Decision::NV,Decision::OR); //OR Oregon
  Connect(Decision::NV,Decision::UT); //UT Utah
  //-----------------
  //NH New Hampshire
  Connect(Decision::NH,Decision::ME); //ME Maine
  Connect(Decision::NH,Decision::MA); //MA Massachusetts
  Connect(Decision::NH,Decision::VT); //VT Vermont
  //-----------------
  //NJ New Jersey
  Connect(Decision::NJ,Decision::DE); //DE Delaware
  Connect(Decision::NJ,Decision::NY); //NY New York
  Connect(Decision::NJ,Decision::PA); //PA Pennsylvania
  //-----------------
  //NM New Mexico	         ,                  ,                 ,                 ,                      
  Connect(Decision::NM,Decision::AZ); //AZ Arizona
  Connect(Decision::NM,Decision::CO); //CO Colorado
  Connect(Decision::NM,Decision::OK); //OK Oklahoma
  Connect(Decision::NM,Decision::TX); //TX Texas
  // UT Utah (corner touch)
  //-----------------
  //NY New York	           ,              ,                   
  Connect(Decision::NY,Decision::CT); //CT Connecticut
  Connect(Decision::NY,Decision::MA); //MA Massachusetts
  Connect(Decision::NY,Decision::NJ); //NJ New Jersey
  Connect(Decision::NY,Decision::PA); //PA Pennsylvania
  Connect(Decision::NY,Decision::VT); //VT Vermont
  //-----------------
  //NC North Carolina
  Connect(Decision::NC,Decision::GA); //GA Georgia
  Connect(Decision::NC,Decision::SC); //SC South Carolina
  Connect(Decision::NC,Decision::TN); //TN Tennessee
  Connect(Decision::NC,Decision::VA); //VA Virginia
  //-----------------
  //ND North Dakota	       ,                ,                  
  Connect(Decision::ND,Decision::MN); //MN Minnesota
  Connect(Decision::ND,Decision::MT); //MT Montana
  Connect(Decision::ND,Decision::SD); //SD South Dakota
  //-----------------
  //OH Ohio
  Connect(Decision::OH,Decision::IN); //IN Indiana
  Connect(Decision::OH,Decision::KY); //KY Kentucky
  Connect(Decision::OH,Decision::MI); //MI Michigan
  Connect(Decision::OH,Decision::PA); //PA Pennsylvania
  Connect(Decision::OH,Decision::WV); //WV West Virginia
  //-----------------
  //OK Oklahoma
  Connect(Decision::OK,Decision::AR); //AR Arkansas
  Connect(Decision::OK,Decision::CO); //CO Colorado
  Connect(Decision::OK,Decision::KS); //KS Kansas
  Connect(Decision::OK,Decision::MO); //MO Missouri
  Connect(Decision::OK,Decision::NM); //NM New Mexico
  Connect(Decision::OK,Decision::TX); //TX Texas
  //-----------------
  //OR Oregon
  Connect(Decision::OR,Decision::CA); //CA California
  Connect(Decision::OR,Decision::ID); //ID Idaho
  Connect(Decision::OR,Decision::NV); //NV Nevada
  Connect(Decision::OR,Decision::WA); //WA Washington
  //-----------------
  //PA Pennsylvania
  Connect(Decision::PA,Decision::DE); //DE Delaware
  Connect(Decision::PA,Decision::MD); //MD Maryland
  Connect(Decision::PA,Decision::NJ); //NJ New Jersey
  Connect(Decision::PA,Decision::NY); //NY New York
  Connect(Decision::PA,Decision::OH); //OH Ohio
  Connect(Decision::PA,Decision::WV); //WV West Virginia
  //-----------------
  //RI Rhode Island
  Connect(Decision::RI,Decision::CT); //CT Connecticut
  Connect(Decision::RI,Decision::MA); //MA Massachusetts
  //-----------------
  //SC South Carolina
  Connect(Decision::SC,Decision::GA); //GA Georgia
  Connect(Decision::SC,Decision::NC); //NC North Carolina
  //-----------------
  //SD South Dakota
  Connect(Decision::SD,Decision::IA); //IA Iowa
  Connect(Decision::SD,Decision::MN); //MN Minnesota
  Connect(Decision::SD,Decision::MT); //MT Montana
  Connect(Decision::SD,Decision::NE); //NE Nebraska
  Connect(Decision::SD,Decision::ND); //ND North Dakota
  Connect(Decision::SD,Decision::WY); //WY Wyoming
  //-----------------
  //TN Tennessee
  Connect(Decision::TN,Decision::AL); //AL Alabama
  Connect(Decision::TN,Decision::AR); //AR Arkansas
  Connect(Decision::TN,Decision::GA); //GA Georgia
  Connect(Decision::TN,Decision::KY); //KY Kentucky
  Connect(Decision::TN,Decision::MS); //MS Mississippi
  Connect(Decision::TN,Decision::MO); //MO Missouri
  Connect(Decision::TN,Decision::NC); //NC North Carolina
  Connect(Decision::TN,Decision::VA); //VA Virginia
  //-----------------
  //TX Texas
  Connect(Decision::TX,Decision::AR); //AR Arkansas
  Connect(Decision::TX,Decision::LA); //LA Louisiana
  Connect(Decision::TX,Decision::NM); //NM New Mexico
  Connect(Decision::TX,Decision::OK); //OK Oklahoma
  //-----------------
  //UT Utah
  Connect(Decision::UT,Decision::AZ); //AZ Arizona
  Connect(Decision::UT,Decision::CO); //CO Colorado
  Connect(Decision::UT,Decision::ID); //ID Idaho
  Connect(Decision::UT,Decision::NV); //NV Nevada
  // NM New Mexico (corner touch)
  Connect(Decision::UT,Decision::WY); //WY Wyoming
  //-----------------
  //VT Vermont
  Connect(Decision::VT,Decision::MA); //MA Massachusetts
  Connect(Decision::VT,Decision::NH); //NH New Hampshire
  Connect(Decision::VT,Decision::NY); //NY New York
  //-----------------
  //VA Virginia
  Connect(Decision::VA,Decision::KY); //KY Kentucky
  Connect(Decision::VA,Decision::MD); //MD Maryland
  Connect(Decision::VA,Decision::NC); //NC North Carolina
  Connect(Decision::VA,Decision::TN); //TN Tennessee
  Connect(Decision::VA,Decision::WV); //WV West Virginia
  //-----------------
  //WA Washington
  Connect(Decision::WA,Decision::ID); //ID Idaho
  Connect(Decision::WA,Decision::OR); //OR Oregon
  //-----------------
  //WV West Virginia
  Connect(Decision::WV,Decision::KY); //KY Kentucky
  Connect(Decision::WV,Decision::MD); //MD Maryland
  Connect(Decision::WV,Decision::OH); //OH Ohio
  Connect(Decision::WV,Decision::PA); //PA Pennsylvania
  Connect(Decision::WV,Decision::VA); //VA Virginia
  //-----------------
  //WI Wisconsin
  Connect(Decision::WI,Decision::IL); //IL Illinois
  Connect(Decision::WI,Decision::IA); //IA Iowa
  Connect(Decision::WI,Decision::MI); //MI Michigan
  Connect(Decision::WI,Decision::MN); //MN Minnesota
  //-----------------
  //WY Wyoming
  Connect(Decision::WY,Decision::CO); //CO Colorado
  Connect(Decision::WY,Decision::ID); //ID Idaho
  Connect(Decision::WY,Decision::MT); //MT Montana
  Connect(Decision::WY,Decision::NE); //NE Nebraska
  Connect(Decision::WY,Decision::SD); //SD South Dakota
  Connect(Decision::WY,Decision::UT); //UT Utah
  //-----------------
 #endif
}

#endif
