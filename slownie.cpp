#include "slownie.h"


std::string Slownie::zamiana(std::string ccc_input, std::string nazwa)
{
    std::string s1="sto";
    std::string s2="dwieście";
    std::string s3="trzysta";
    std::string s4="czterysta";
    std::string s5="pięćset";
    std::string s6="sześćset";
    std::string s7="siedemset";
    std::string s8="osiemset";
    std::string s9="dziewięćset";

    std::string d1="dziesięć";
    std::string d11="jedenaście";
    std::string d12="dwanaście";
    std::string d13="trzynaście";
    std::string d14="czternaście";
    std::string d15="piętnaście";
    std::string d16="szesnaście";
    std::string d17="siedemnaście";
    std::string d18="osiemnaście";
    std::string d19="dziewiętnaście";
    std::string d2="dwadzieścia";
    std::string d3="trzydzieści";
    std::string d4="czterdzieści";
    std::string d5="pięćdziesiąt";
    std::string d6="sześćdziesiąt";
    std::string d7="siedemdziesiąt";
    std::string d8="osiemdziesiąt";
    std::string d9="dziewięćdziesiąt";

    std::string j0="zero";
    std::string j1="jeden";
    std::string j2="dwa";
    std::string j3="trzy";
    std::string j4="cztery";
    std::string j5="pięć";
    std::string j6="sześć";
    std::string j7="siedem";
    std::string j8="osiem";
    std::string j9="dziewięć";

    size_t input_length=ccc_input.size();
    std::string nazwa1, nazwa24, nazwa51;
    char s, d, j;
    std::string ccc="";
//-----------------------------------------------

    if (nazwa=="tysiac")
    {
        nazwa1="tysiąc";
        nazwa24="tysiące";
        nazwa51="tysięcy";
    }
    else if (nazwa=="zloty")        //    001 milion
    {                               //xx2-xx4 miliony
        nazwa1="złoty,";            //xx5-xx1 milionow
        nazwa24="złote,";           //x12-x14 milionow
        nazwa51="złotych,";
    }
    else if (nazwa=="grosz")
    {
        nazwa1="grosz";
        nazwa24=nazwa1+"e";
        nazwa51=nazwa1+"y";
    }
    else //(nazwa=="milion" || nazwa=="miliard" || nazwa=="bilion" || nazwa=="biliard" || nazwa=="trylion")
    {
        nazwa1=nazwa;
        nazwa24=nazwa1+"y";
        nazwa51=nazwa1+"ów";
    }
//-----------------------------------------------

    if (input_length==3)
    {
        s=ccc_input.at(0);
        d=ccc_input.at(1);
        j=ccc_input.at(2);
    }
    else if (input_length==2 && nazwa!="grosz")
    {
        s='z';
        d=ccc_input.at(0);
        j=ccc_input.at(1);
    }
    else if (input_length==1 && nazwa!="grosz")
    {
        s='z';
        d='z';
        j=ccc_input.at(0);
    }
    else if (input_length==2 && nazwa=="grosz")
    {
        s='0'; //zeby dla jednego grosza dzialala funkcja
        d=ccc_input.at(0);
        j=ccc_input.at(1);
    }

    else if (input_length==1 && nazwa=="grosz")
    {
        s='z';
        d=ccc_input.at(0);
        j='z';
    }
    else
    {
        s='z';
        d='z';
        j='z';
    }
//-----------------------------------------------

    switch (s)
    {
        case '1': ccc=ccc+s1+" "; break;
        case '2': ccc=ccc+s2+" "; break;
        case '3': ccc=ccc+s3+" "; break;
        case '4': ccc=ccc+s4+" "; break;
        case '5': ccc=ccc+s5+" "; break;
        case '6': ccc=ccc+s6+" "; break;
        case '7': ccc=ccc+s7+" "; break;
        case '8': ccc=ccc+s8+" "; break;
        case '9': ccc=ccc+s9+" "; break;
    }

    switch (d)
    {
        case '1':
        {
            switch (j)
            {
                case '0': ccc=ccc+d1+" "+nazwa51+" "; break;
                case '1': ccc=ccc+d11+" "+nazwa51+" "; break;
                case '2': ccc=ccc+d12+" "+nazwa51+" "; break;
                case '3': ccc=ccc+d13+" "+nazwa51+" "; break;
                case '4': ccc=ccc+d14+" "+nazwa51+" "; break;
                case '5': ccc=ccc+d15+" "+nazwa51+" "; break;
                case '6': ccc=ccc+d16+" "+nazwa51+" "; break;
                case '7': ccc=ccc+d17+" "+nazwa51+" "; break;
                case '8': ccc=ccc+d18+" "+nazwa51+" "; break;
                case '9': ccc=ccc+d19+" "+nazwa51+" "; break;
            }
        } break;
        case '2': ccc=ccc+d2+" "; break;
        case '3': ccc=ccc+d3+" "; break;
        case '4': ccc=ccc+d4+" "; break;
        case '5': ccc=ccc+d5+" "; break;
        case '6': ccc=ccc+d6+" "; break;
        case '7': ccc=ccc+d7+" "; break;
        case '8': ccc=ccc+d8+" "; break;
        case '9': ccc=ccc+d9+" "; break;
    }


//--//PRZYPADKI SZCZEGOLNE DLA GROSZY//--------------------------------------------
        if(nazwa=="grosz" && d=='z')
        {
            ccc=ccc+j0+" "; //zero
        }
        if(nazwa=="grosz" && d=='0' && j=='0')
        {
            ccc=ccc+j0+" "; //zero
        }
        if(nazwa=="grosz" && d=='0' && j=='z')
        {
            ccc=ccc+j0+" "; //zero
        }
        if(nazwa=="grosz" && d=='1' && j=='z')
        {
            ccc=ccc+d1+" "+nazwa51+" "; //(.1) dziesiec groszy
        }
//--//PRZYPADKI SZCZEGOLNE DLA GROSZY//--------------------------------------------


    if (d!='1')
    {
        switch (j)
        {
            case 'z':
            {
                if(nazwa=="grosz")
                {
                    ccc=ccc+nazwa51+" "; //(.2 dwadziescia) groszy
                }
                else if(nazwa=="zloty")
                {
                    ccc=ccc+j0+" "+nazwa51+" "; //zero zlotych
                }
            } break;
//=================================================================================
            case '0':
            {
        /*1A*/  if(s=='z' && d=='z' && nazwa=="zloty")
                {
                    ccc=ccc+j0+" "+nazwa51+" "; //zero zlotych
                }
        /*1B*///else if(s=='z' && d=='z' && nazwa!="zloty"); // (0)tysiac
//---------------------------------------------------------------------------------
        /*2A*/  else if(s=='0' && d=='0' && (nazwa=="zloty" || nazwa=="grosz"))
                {
                    ccc=ccc+nazwa51+" "; //(np. tysiac) zlotych
                }
        /*2B*///else if(s=='0' && d=='0' && nazwa!="zloty" && nazwa!="grosz"); // (0)tysiecy... (wczesniej pisal np. miliard milionow tysiecy)
//---------------------------------------------------------------------------------
        /*3A*/  else if((s!='0' || d!='0') && (s!='z' || d!='z')) //((s!='0' && s!='z') || (d!='0' && d!='z'))
                {
                    ccc=ccc+nazwa51+" "; //(dwadziescia) tysiecy / zlotych
                }
            } break;
//=================================================================================
            case '1':
            {
        /*1A*/  if(s=='z' && d=='z' && nazwa=="zloty")
                {
                    ccc=ccc+j1+" "+nazwa1+" "; //jeden zloty
                }
        /*1B*/  else if(s=='z' && d=='z' && nazwa!="zloty")
                {
                    ccc=ccc+nazwa1+" "; // (1)tysiac
                }
//---------------------------------------------------------------------------------
        /*2A*/  else if(s=='0' && d=='0' && (nazwa=="zloty" || nazwa=="grosz"))
                {
                    ccc=ccc+j1+" "+nazwa1+" "; //(np. tysiac) jeden zloty
                }
        /*2B*///else if(s=='0' && d=='0' && nazwa!="zloty" && nazwa!="grosz"); // (1)tysiecy... (wczesniej pisal np. miliard milionow tysiecy)
//---------------------------------------------------------------------------------
        /*3A*/  else if((s!='0' || d!='0') && (s!='z' || d!='z')) //((s!='0' && s!='z') || (d!='0' && d!='z'))
                {
                    ccc=ccc+j1+" "+nazwa51+" "; //(dwadziescia) jeden tysiecy / zlotych
                }
            } break;
//=================================================================================
            case '2': ccc=ccc+j2+" "+nazwa24+" "; break;
            case '3': ccc=ccc+j3+" "+nazwa24+" "; break;
            case '4': ccc=ccc+j4+" "+nazwa24+" "; break;
            case '5': ccc=ccc+j5+" "+nazwa51+" "; break;
            case '6': ccc=ccc+j6+" "+nazwa51+" "; break;
            case '7': ccc=ccc+j7+" "+nazwa51+" "; break;
            case '8': ccc=ccc+j8+" "+nazwa51+" "; break;
            case '9': ccc=ccc+j9+" "+nazwa51+" "; break;
        }
    }
return ccc;
}
//-----------------------------------------------

std::string Slownie::na_slownie(std::string liczebnik)
{
    size_t length_zl=0, length_gr=0;
    size_t liczebnik_length=liczebnik.size();

    size_t found_dot=liczebnik.find(".");
    if (found_dot==std::string::npos) found_dot=liczebnik.find(",");

    std::string slownie="";

    std::string tryliony;
    std::string biliardy;
    std::string biliony;
    std::string miliardy;
    std::string miliony;
    std::string tysiace;
    std::string zlote=""; //jesli dane wejsciowe puste - leci info zero zlotych
    std::string grosze=""; //jesli dane wejsciowe puste - leci info zero groszy

    std::string trylion="trylion";
    std::string biliard="biliard";
    std::string bilion="bilion";
    std::string miliard="miliard";
    std::string milion="milion";
    std::string tysiac="tysiac";
    std::string zloty="zloty";
    std::string grosz="grosz";
//-----------------------------------------------

    if (found_dot!=std::string::npos)
    {
        length_gr=liczebnik_length-(found_dot+1); //+1, bo found liczy od 0 //jak sama kropka, to dlugosc groszy =0
        length_zl=liczebnik_length-(length_gr+1); //+1, czyli grosze i kropka
    }
    else length_zl=liczebnik_length;
//-----------------------------------------------

    if (21>=length_zl && length_zl>18)
    {
        switch (length_zl)
        {
            case 19: tryliony=liczebnik.substr(length_zl-19,1); break;
            case 20: tryliony=liczebnik.substr(length_zl-20,2); break;
            case 21: tryliony=liczebnik.substr(length_zl-21,3); break;
        } slownie=slownie+zamiana(tryliony, trylion);

        biliardy=liczebnik.substr(length_zl-18,3); slownie=slownie+zamiana(biliardy, biliard);
        biliony=liczebnik.substr(length_zl-15,3); slownie=slownie+zamiana(biliony, bilion);
        miliardy=liczebnik.substr(length_zl-12,3); slownie=slownie+zamiana(miliardy, miliard);
        miliony=liczebnik.substr(length_zl-9,3); slownie=slownie+zamiana(miliony, milion);
        tysiace=liczebnik.substr(length_zl-6,3); slownie=slownie+zamiana(tysiace, tysiac);
        zlote=liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (18>=length_zl && length_zl>15)
    {
        switch (length_zl)
        {
            case 16: biliardy=liczebnik.substr(length_zl-16,1); break;
            case 17: biliardy=liczebnik.substr(length_zl-17,2); break;
            case 18: biliardy=liczebnik.substr(length_zl-18,3); break;
        } slownie=slownie+zamiana(biliardy, biliard);

        biliony=liczebnik.substr(length_zl-15,3); slownie=slownie+zamiana(biliony, bilion);
        miliardy=liczebnik.substr(length_zl-12,3); slownie=slownie+zamiana(miliardy, miliard);
        miliony=liczebnik.substr(length_zl-9,3); slownie=slownie+zamiana(miliony, milion);
        tysiace=liczebnik.substr(length_zl-6,3); slownie=slownie+zamiana(tysiace, tysiac);
        zlote=liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (15>=length_zl && length_zl>12)
    {
        switch (length_zl)
        {
            case 13: biliony=liczebnik.substr(length_zl-13,1); break;
            case 14: biliony=liczebnik.substr(length_zl-14,2); break;
            case 15: biliony=liczebnik.substr(length_zl-15,3); break;
        } slownie=slownie+zamiana(biliony, bilion);

        miliardy=liczebnik.substr(length_zl-12,3); slownie=slownie+zamiana(miliardy, miliard);
        miliony=liczebnik.substr(length_zl-9,3); slownie=slownie+zamiana(miliony, milion);
        tysiace=liczebnik.substr(length_zl-6,3); slownie=slownie+zamiana(tysiace, tysiac);
        zlote=liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (12>=length_zl && length_zl>9)
    {
        switch (length_zl)
        {
            case 10: miliardy=liczebnik.substr(length_zl-10,1); break;
            case 11: miliardy=liczebnik.substr(length_zl-11,2); break;
            case 12: miliardy=liczebnik.substr(length_zl-12,3); break;
        } slownie=slownie+zamiana(miliardy, miliard);

        miliony=liczebnik.substr(length_zl-9,3); slownie=slownie+zamiana(miliony, milion);
        tysiace=liczebnik.substr(length_zl-6,3); slownie=slownie+zamiana(tysiace, tysiac);
        zlote=liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (9>=length_zl && length_zl>6)
    {
        switch (length_zl)
        {
            case 7: miliony=liczebnik.substr(length_zl-7,1); break;
            case 8: miliony=liczebnik.substr(length_zl-8,2); break;
            case 9: miliony=liczebnik.substr(length_zl-9,3); break;
        } slownie=slownie+zamiana(miliony, milion);

        tysiace=liczebnik.substr(length_zl-6,3); slownie=slownie+zamiana(tysiace, tysiac);
        zlote=liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (6>=length_zl && length_zl>3)
    {
        switch (length_zl)
        {
            case 4: tysiace=liczebnik.substr(length_zl-4,1); break;
            case 5: tysiace=liczebnik.substr(length_zl-5,2); break;
            case 6: tysiace=liczebnik.substr(length_zl-6,3); break;
        } slownie=slownie+zamiana(tysiace, tysiac);

        zlote=
        liczebnik.substr(length_zl-3,3); slownie=slownie+zamiana(zlote, zloty);
    }

    else if (3>=length_zl && length_zl>=0)
    {
        switch (length_zl)
        {
            case 1: zlote=liczebnik.substr(length_zl-1,1); break;
            case 2: zlote=liczebnik.substr(length_zl-2,2); break;
            case 3: zlote=liczebnik.substr(length_zl-3,3); break;
        } slownie=slownie+zamiana(zlote, zloty);
    }
//-----------------------------------------------

    if (length_gr==1) grosze=liczebnik.substr(found_dot+1,1);
    else if (length_gr>=2) grosze=liczebnik.substr(found_dot+1,2);
    slownie=slownie+zamiana(grosze, grosz);

    return slownie;
}
