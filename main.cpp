#include <iostream>
#include <string>

#include <millisecond_id.h>

using namespace std;

class id_caller{
	public:
	std::string give();
	std::string today(std::string time);

	private:
	id maker;	
};


std::string id_caller::give(){

	return maker.gen_id();

};


std::string id_caller::today(std::string time){

	return maker.get_timestamp(time);

};


int main(){

id_caller id_giver;

std::string yello=id_giver.give();

cout<<yello<<endl;

cout<<"length is - "<<yello.length()<<endl;

cout<<"time is being translated to - "<<id_giver.today(yello)<<endl;

return 0;
}
