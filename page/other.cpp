#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "other.h"

bool recent_comperator(const page &A,const page &B)
{
	return A.Recent_time>B.Recent_time;
}//porownuje dla funkcji sortujacej po czasie ostatniego wykonania

////////////////////////////////////////////////////////////////////////////////////////////////////
bool frequen_comperator(const page &A,const page &B)
{
	return A.Recent_time>B.Recent_time;
}//porownuje dla funkcji sortujacej po czestotliwosci wykonywania

////////////////////////////////////////////////////////////////////////////////////////////////////
bool number_comperator(const page &A,const page &B)
{
	return A.Number<B.Number;
}//porownuje dla funkcji sortujacej po numerach stron

////////////////////////////////////////////////////////////////////////////////////////////////////
void generator(const int &Quantity,const int &Size,std::vector<int>&Queue,std::vector<page>&List)
{
	std::random_device Generator;
	std::normal_distribution<> Distribution((Size+1)/2,(Size+1)/2);
	//rozklad zapotrzebowania na strony generowany jest z rozkladem normalnym

	for(int i=0;i<Size;i++)
	{
		page Newpage;
		Newpage.Number=i+1;
		List.push_back(Newpage);
	}//tworzy liste stron

	for(int i=0;i<Quantity;i++)
	{
		Queue.push_back((int)Distribution(Generator));
		if(Queue[i]<1){Queue[i]=1;}
		if(Queue[i]>Size){Queue[i]=Size;}
	}//tworzy kolejke zapotrzebowania na strony
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void adding_page(int Counter,int &Iterator,const int &Size,std::vector<int>&Queue,std::vector<page>&List,std::vector<page>&Reference)
{
	std::vector<page>::iterator Indicator=List.begin();
	for(int i=0;i<Size;i++)
	{
		if(List[i].Number==Queue[Iterator])
		{
			Reference.push_back(List[i]);
			//dodaje nowa strone do ramki
			
			Indicator+=i;
			List.erase(Indicator);
			//usowa ta strone z listy

			break;
		}
	}//znajduje strone do dodania do ramki
	
	Reference[size(Reference)-1].Entry_time.push_back(Counter);
	//zapisuje czas rozpoczecia przebywania strony w ramce
				
	//wykonuje strone
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void replace_page(int Counter,int &Iterator,std::vector<int>&Queue,std::vector<page>&List,std::vector<page>&Reference)
{
	int Position=size(Reference)-1;
	//lokalizacja strony do podmiany, na koncu ramki

	Reference[Position].Descent_time.push_back(Counter);
	//zapisuje czas zakonczenia przebywania strony w ramce

	List.push_back(Reference[Position]);
	Reference.pop_back();
	//przenosi strone na liste i usuwa ja z ramki

	adding_page(Counter,Iterator,size(List),Queue,List,Reference);
	//dodaje nowa strone do ramki
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void end_recording(int Counter,const int &Frame,std::vector<page>&List,std::vector<page>&Reference)
{
	for(int i=0;i<Frame;i++)
	{
		Reference[i].Descent_time.push_back(Counter);
		List.push_back(Reference[i]);
	}//zapisuje czasy zakonczenia przebywania stron w ramce
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool is_the_site(int Counter,std::vector<page>&List,std::vector<page>&Reference,int &Iterator,std::vector<int>&Queue)
{
	for(int i=0;i<size(Reference);i++)
	{
		if(Queue[Iterator]==Reference[i].Number)
		{
			Reference[i].Recent_time=Counter;
			//zapisuje czas ponownego z niej skorzystania
			return true;
			//jesli tak to zwraca prawde
		}
	}//sprawdza czy aktualnie potrzebna strona jest w ramce
	return false;
	//jesli nie to zwraca falsz
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool is_the_site_sum(int Counter,std::vector<page>&List,std::vector<page>&Reference,int &Iterator,std::vector<int>&Queue)
{
	for(int i=0;i<size(Reference);i++)
	{
		if(Queue[Iterator]==Reference[i].Number)
		{
			Reference[i].Recent_time+=Counter;
			//zwieksza czestotliwosc korzystania z niej
			return true;
			//jesli tak to zwraca prawde		
		}
	}//sprawdza czy aktualnie potrzebna strona jest w ramce
	return false;
	//jesli nie to zwraca falsz
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void print_data(std::vector<int>&Queue,std::vector<page>&List)
{
	for(int j=0;j<size(Queue);j++){std::cout<<Queue[j]<<"	";}
	std::cout<<std::endl<<std::endl;
	//podaje kolejnosc zapotrzebowania na ramki

	std::sort(List.begin(),List.end(),&number_comperator);
	//sortuje ramki po numerach

	for(int i=0;i<size(List);i++)
	{
		std::cout<<"N:	"<<List[i].Number<<std::endl;
		
		std::cout<<"E:	";
		for(int j=0;j<size(List[i].Entry_time);j++)
		{std::cout<<List[i].Entry_time[j]<<"	";}
		std::cout<<std::endl;
		//podaje czasy wejscia do ramki

		std::cout<<"D:	";
		for(int j=0;j<size(List[i].Descent_time);j++)
		{std::cout<<List[i].Descent_time[j]<<"	";}
		std::cout<<std::endl<<std::endl<<std::endl;
		//podaje czasy wyjscia z ramki
	}
}
