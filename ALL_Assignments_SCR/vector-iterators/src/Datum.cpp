#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "Datum.h"
using namespace std;
//You may want to write this function, but you do not have to


[[nodiscard]] bool isBadDataEntry(const Datum& datum)
{
  //  return (datum.empty());
}

unsigned int Datum::compute_total() const noexcept
{
    return negative+positive;
}

float Datum::compute_positivity() const noexcept
{  
        float x  = negative+positive;
        return (float) (positive/x);
    //return 0.0;
}
std::ostream& operator<<(std::ostream& out, const Datum& datum)
{
    return out;

}

std::istream& operator>>(std::istream& in, Datum& datum)
{
try{
    string Line;
    getline(in,Line,',');
    datum.week=Line;

//    std::cout<<Line<<std::endl;
    getline(in,Line,',');

//    std::cout<<Line<<std::endl;
    datum.negative=stoul(Line);
// std::cout<<"line 1 " << Line <<endl;
    getline(in,Line,',');
    datum.positive=stoul(Line);
// std::cout<<"line 2 " << Line <<endl;
    getline(in,Line,',');
    datum.total=stoul(Line);
// std::cout<<"line 3 " << Line <<endl;
    getline(in,Line,'%');

    datum.positivity=stof(Line);
// std::cout<<"line 4 " << Line <<endl;
    getline(in,Line);
// std::cout<<"line 124" << Line <<endl;
}
   catch(std::invalid_argument)
    {
        
    }
}

Vector<Datum> readData(std::istream& file)
{
    Datum Box;
    string Holder;

    std::getline(file, Holder);
   // cout << Holder << endl;
    Vector<Datum> store;

    while(!file.eof())
    {  
        
        file>>Box;
        store.push_back(Box);
    
    // this is necessary because the file given has bad data
 

    }
    store.pop_back();    
    return store;
}

Vector<Datum> badDataEntries(const Vector<Datum>& data) noexcept
{
    Vector<Datum> Kinky;
    bool badData = false;
     for(size_t index = 0 ; index < data.size() ; index++)
     {
         float computePos = abs(data[index].compute_positivity()*100)-abs((data[index].positivity));

         if(abs(computePos) > .1 )
         {
         cout << "Compute positiivty  " << abs(data[index].compute_positivity()*100 )<< " data " << abs(data[index].positivity) <<endl;

             badData = true;
         }


         if((data[index].total != data[index].compute_total())||(badData))
         {
            Kinky.push_back(data[index]);
         }
         badData=false;
     }
    
    return Kinky;
}
bool goodData(const Vector<Datum>& data) noexcept
{
    Vector<Datum> cum;
    cum = badDataEntries(data);
    return cum.empty();
}

// You may want to write this function, but you do not have to
[[nodiscard]] bool isBadDataEntry(const Datum& datum);
