#include <vector>
#include <string>
#include <iostream>
//https://stackoverflow.com/questions/6482338/how-to-create-a-list-of-tuples-c
#include <tuple>
#include <algorithm>

int main(){

    std::vector<std::string> lk_sigmaringen {
        //Liste aller Gemeinden
        "Bad Saulgau",
        "Beuron",
        "Bingen",
        "Gammertingen",
        "Göggingen",
        "Herbertingen",
        "Herdwangen-Schönach",
        "Hettingen",
        "Illmensee",
        "Inzigkofen",
        "Krauchenwies",
        "Laiz",
        "Leibertingen",
        "Mengen",
        "Hohentengen",
        "Meßkirch",
        "Neufra",
        "Ostrach",
        "Pfullendorf",
        "Sauldorf",
        "Scheer",
        "Schwenningen",
        "Sigmaringen",
        "Sigmaringendorf",
        "Stetten a.k.M",
        "Veringenstadt",
        "Wald"
    };

    
    std::vector<std::vector<int>> graph_lk_sigmaringen_taxi{ 
        //Kanten aller "Städte" zueinander
        
        //Saulgau
        {0,5},{0,14},{0,17},
        //Beuron
        {1,12},{1,21},{1,24},{1,22},
        //Bingen
        {2,25},{2,7},{2,22},{2,23},{2,20},
        //Gammertingen
        {3,16},{3,7},
        //Göggingen
        {4,10},{4,15},{4,9},{4,11},
        //Herbertingen
        {5,13},{5,14},
        //Herdwangen-S
        {6,26},{6,18},
        //Hettingen
        {7,25},{7,3},{7,16},
        //Illmensee
        {8,18},{8,17},
        //Inzigkofen
        {9,11},{9,22},{9,15},
        //Krauchenwies
        {10,11},{10,22},{10,26},{10,13},{10,18},{10,17},
        //Laiz
        {11,22},
        //Leibertingen
        {12,22},{12,15},{12,19},
        //Mengen
        {13,20},{13,14},{13,17},
        //Hohentengen
        {14,17},
        //Meßkirch
        {15,19},{15,26},
        //Neufra
        {15,25},
        //Ostrach
        {17,18},
        //Pfullendorf
        {18,26},
        //Sauldorf
        
        //Scheer
        {20,23},
        //Schenningen
        {21,24},
        //Sigmaringen
        {22,25},{22,23}
        //Sigmaringendorf

        //Stetten a.k.M
        
        //Veringenstadt

        //Wald
    };


    std::cout << graph_lk_sigmaringen[1] << std::endl;

    //std::cout << graph_lk_sigmaringen[0][0] << std::endl;

    /*

    Alphabetical sort of vector

    std::sort(lk_sigmaringen.begin(),lk_sigmaringen.end());

    for (int i = 0; i < lk_sigmaringen.size(); i++){
        std::cout << '"' << lk_sigmaringen[i] << '"' << ',' << std::endl;
    }
    */

    

    


}
