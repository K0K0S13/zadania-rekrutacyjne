// Z podanego zbioru danych wyselekcjonuj 5 o największej wartości na jednostkę, znając kategorię obiektu
// Dane znajdują się w folderze "dane" w pliku "zbiór_wejściowy.json" oraz "kategorie.json"
// Wynik przedstaw w czytelnej formie na standardowym wyjściu
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cmath>
using namespace std;

class Kategoria
{
    public:
    string typ;
    string czystosc;
    int wartosc_za_uncje;


    //Kategoria (string t, int w, string cz) :typ(t), czystosc(cz), wartosc_za_uncje(w) {}
    Kategoria() {}


    void display()
    {
        cout<<endl<<"Typ: "<<typ<<endl<<"Wartość za uncję: "<<wartosc_za_uncje<<endl<<"Czystość: "<<czystosc<<endl;
    }
};


class Ore
{
    public:
    string typ; 
    long double masa_ounce;
    string czystosc;
    string barwa;
    string pochodzenie;
    string wlasciciel;
    long double value=0;
   

   Ore() {}

   void display()
   {
    cout<<"Object's value: "<<value<<endl;

    cout<<endl<<"Typ: "<<typ<<endl<<"Masa: "<<masa_ounce<<" ounces"<<endl<<"Czystość: "<<czystosc<<endl;
    cout<<"Barwa: "<<barwa<<endl<<"Pochodzenie: "<<pochodzenie<<endl<<"Właściciel: "<<wlasciciel<<endl<<endl;
   }
};

int main()
{
locale::global(locale("pl_PL.UTF-8"));

 ifstream file("../dane/kategorie.json");
    if (!file) cerr << "Could not open the file!" << endl;


getline(file, string());


Kategoria category[19];
int i=0;
string line;
long double pom, value_pom;
int startpos, endpos;
while(!file.eof()) //getting categories into a class object
{
    file>>line;
    if(line=="]")  break; //breaking after the file ends (last line is ] )


    getline(file, string()); //skipping the {

    //getting the value of "Typ"
    getline(file, line); 
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    category[i].typ=line;


    //getting the value of "Wartość za uncję"
    getline(file, line); 
    startpos = line.find(" ", line.find(":"))+1;
    endpos = line.find(",", startpos);
    line = line.substr(startpos, endpos-startpos);
    pom=0;
    value_pom=0;
    while(pom<line.size())//value_per_ounce to int
    {
        value_pom*=10;
        value_pom+=line[pom]-48;
        pom++;
    }
    category[i].wartosc_za_uncje=value_pom;
    


    //getting the value of "Czystość"
    getline(file, line); 
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    category[i].czystosc=line;


   i++;

    getline(file, string()); //skipping the }

}
file.close();
//for(int o=0; o<19; o++) category[o].display();

ifstream file2("../dane/zbiór_wejściowy.json");
    if (!file2) cerr << "Could not open the file!" << endl;


Ore ore[47];
int j=0;
int g;
int pom_fraction;
double sum_fraction;


getline(file2, string()); //skipping the [
while(!file2.eof()) //getting ores into a class object
{
    file2>>line;
    if(line=="]")  break; //breaking after the file ends (last line is ] )


    getline(file2, string()); //skipping the {

    //getting the value of "Typ"
    getline(file2, line); 
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    ore[j].typ=line;


    //getting the value of "masa" and converting it to ounces
    getline(file2, line); 
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);

    if(line.find('g')!=string::npos) 
    {
        g=1;
        line = line.substr(0, line.length()-1);//cutting off the g
    }
    else 
    {
        g=0;
        line = line.substr(0, line.length()-2);//cutting off the ct
    } 

    
    pom=0;
    value_pom=0;
    //mass to double
    
    while(line[pom]!=',' && pom<line.size()) //whole part of the number
    {
        value_pom*=10;
        value_pom+=line[pom]-48;
        pom++;
    }
    if(pom<line.size()) pom++;
    pom_fraction = 0;
    sum_fraction = 0;
    while(pom<line.size()) //fraction part of the number
    {
        sum_fraction*=10;
        sum_fraction+=line[pom]-48;
        pom++;
        pom_fraction++;
    }
    sum_fraction*=pow(0.1, pom_fraction);
    value_pom+=sum_fraction;

   

  
    if(g==1) value_pom = value_pom *0.0352739619; //grams to ounces
    else value_pom = value_pom *0.00705479239;   //carats to ounces


    ore[j].masa_ounce=value_pom;
    

    getline(file2, line); //getting the value of "Czystość"
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    ore[j].czystosc=line;

    getline(file2, line); //getting the value of "Barwa"
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    ore[j].barwa=line;

    getline(file2, line); //getting the value of "Pochodzenie"
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    ore[j].pochodzenie=line;

    getline(file2, line); //getting the value of "Właściciel"
    startpos = line.find("\"", line.find(":"))+1;
    endpos = line.find("\"", startpos);
    line = line.substr(startpos, endpos-startpos);
    ore[j].wlasciciel=line;



    getline(file2, string()); //skipping the }





for(int r=0; r<19; r++) //calculating the value of each object
{
    if(ore[j].typ==category[r].typ){
        if(ore[j].czystosc==category[r].czystosc) ore[j].value = ore[j].masa_ounce * category[r].wartosc_za_uncje;
    }
}




     j++;
}
file2.close();
//for(int o=0; o<47; o++) ore[o].display();
    


int sorted_top5[46]; //indexes of ore objects
for(int l=0; l<47; l++) sorted_top5[l]=l;
for(int ll=0; ll<5; ll++) //5 times to get the top 5 sorted
for(int l=0; l<46-ll; l++)
{
    if(ore[sorted_top5[l]].value > ore[sorted_top5[l+1]].value ) swap(sorted_top5[l], sorted_top5[l+1]);
}

for(int l=46; l>41; l--) {
    cout<<"Top "<<47-l<<": "<<endl;
    ore[sorted_top5[l]].display();
    }
}

//I could value gold, silver and platinum, which don't have a purity exactly matching a category, by
//using the category of a lower purity (for example: gold 750 purity would be treated as 
//gold 585 purity), but it wasn't specified in the problem's description so I don't want to give a
//wrong answer.