#ifndef _OTHER_H
#define _OTHER_H

#include <vector>

struct page
{
	int Number=0;
	int Recent_time=0;//czas ostatniego urzycia
	std::vector<int> Entry_time;//czas wejscia do ramki
	std::vector<int> Descent_time;//czas wyjscia z ramki
};

////////////////////////////////////////////////////////////////////////////////////////////////////

bool recent_comperator(const page &A,const page &B);
bool frequen_comperator(const page &A,const page &B);
bool number_comperator(const page &A,const page &B);

////////////////////////////////////////////////////////////////////////////////////////////////////
void generator(const int &Quantity,const int &Size,std::vector<int>&Queue,std::vector<page>&List);
void adding_page(int Counter,int &Iterator,const int &Size,std::vector<int>&Queue,std::vector<page>&List,std::vector<page>&Reference);
void replace_page(int Counter,int &Iterator,std::vector<int>&Queue,std::vector<page>&List,std::vector<page>&Reference);
void end_recording(int Counter,const int &Frame,std::vector<page>&List,std::vector<page>&Reference);
bool is_the_site(int Counter,std::vector<page>&List,std::vector<page>&Reference,int &Iterator,std::vector<int>&Queue);
bool is_the_site_sum(int Counter,std::vector<page>&List,std::vector<page>&Reference,int &Iterator,std::vector<int>&Queue);
void print_data(std::vector<int>&Queue,std::vector<page>&List);

#endif
