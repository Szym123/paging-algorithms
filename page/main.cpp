#include <iostream>
#include <vector>
#include <algorithm>
#include "other.h"

void least_recently_used(const int &Quantity,const int &Frame,std::vector<int>&Queue,std::vector<page>&List)
{
	int Iterator=0,Position;
	bool Flag=false;
	std::vector<page>Reference;//ramka

	while(Iterator<Quantity)
	{
		if(size(Reference)==Frame)
		{
			Flag=is_the_site(Iterator+1,List,Reference,Iterator,Queue);
			//sprawdza czy strona jest w ramce, jesli tak to ja wykonuje

			if(Flag==false)
			{
				std::sort(Reference.begin(),Reference.end(),&recent_comperator);
				//sortuje ramke malejaco po czasie ostatniego uzycia stron
				replace_page(Iterator+1,Iterator,Queue,List,Reference);
				//zastepuje najdawnie uzywana strone
				Reference[size(Reference)-1].Recent_time=Iterator+1;
				//zapisuje czas wejsia nowej strony do ramki	
			}//jesli strona nie jest w ramce
			Flag=false;
			//zeruje flage
		}
		else
		{
			if(size(Reference)>0)
			{
				Flag=is_the_site(Iterator+1,List,Reference,Iterator,Queue);
				//sprawdza czy strona jest w ramce, jesli tak to ja wykonuje
			}//sprawdza czy sa jakiekolwiek strony w ramce

			if(Flag==false)
			{
				std::sort(Reference.begin(),Reference.end(),&recent_comperator);
				//sortuje ramke malejaco po czasie ostatniego uzycia stron
				adding_page(Iterator+1,Iterator,size(List),Queue,List,Reference);
				//dodaje strone
				Reference[size(Reference)-1].Recent_time=Iterator+1;
				//zapisuje czas wejsia nowej strony do ramki
			}//jesli strona nie jest w ramce
			Flag=false;
			//zeruje flage
		}//sprawdza czy ramka jest pelna

		if(Iterator==Quantity-1){end_recording(Iterator+1,Frame,List,Reference);}
		//sprawdza czy lista potrzebnych stron sie niekonczy

		Iterator++;
		//przesuwa wskaznik po kolejce potrzebnych stron
	}//glowna petla algorytmu

	print_data(Queue,List);
	//wyswietlanie wynikow
}

void least_frequently_used(const int &Quantity,const int &Frame,std::vector<int>&Queue,std::vector<page>&List)
{
	int Iterator=0,Position;
	bool Flag=false;
	std::vector<page>Reference;//ramka

	while(Iterator<Quantity)
	{
		if(size(Reference)==Frame)
		{
			Flag=is_the_site_sum(1,List,Reference,Iterator,Queue);

			if(Flag==false)
			{
				std::sort(Reference.begin(),Reference.end(),&frequen_comperator);
				//sortuje ramke poczestotliwosci wykonywania malejaco
				replace_page(Iterator+1,Iterator,Queue,List,Reference);
				//zamienia najrzadziej uzywana strone
				Reference[size(Reference)-1].Recent_time++;
				//zwieksza czestosc urzycia strony
			}
			Flag=false;
			//zeruje flage
		}
		else
		{
			if(size(Reference)>0)
			{
				Flag=is_the_site_sum(1,List,Reference,Iterator,Queue);
				//sprawdza czy strona jest w ramce, jesli tak to ja wykonuje
			}//sprawdza czy sa jakiekolwiek strony w ramce

			if(Flag==false)
			{
				std::sort(Reference.begin(),Reference.end(),&frequen_comperator);
				//sortuje ramke poczestotliwosci wykonywania malejaco
				adding_page(Iterator+1,Iterator,size(List),Queue,List,Reference);
				//dodaje nowa strone
				Reference[size(Reference)-1].Recent_time++;
				//zwieksza czestosc urzycia strony
			}
			Flag=false;
			//zeruje flage
		}//sprawdza czy ramka jest pelna

		if(Iterator==Quantity-1){end_recording(Iterator+1,Frame,List,Reference);}
		//sprawdza czy lista potrzebnych stron sie niekonczy

		Iterator++;
		//przesuwa wskaznik po kolejce potrzebnych stron
	}//glowna petla algorytmu
	
	print_data(Queue,List);
	//wyswietlanie wynikow

}

int main()
{
	std::vector<int> Queue;//kolejka potrzebnych ston
	std::vector<page> List_rec;//lista istniejacych stron dla LRU
	std::vector<page> List_fre;// -||- dla LFU
	
	//int Quantity=50,Size=5,Frame=3;
	//int Quantity=50,Size=10,Frame=3;
	int Quantity=50,Size=15,Frame=3;

	generator(Quantity,Size,Queue,List_rec);

	List_fre=List_rec;

	std::cout<<"LRU"<<std::endl;
	least_recently_used(Quantity,Frame,Queue,List_rec);

	std::cout<<"LFU"<<std::endl;
	least_frequently_used(Quantity,Frame,Queue,List_fre);

	return 0;
}
