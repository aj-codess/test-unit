#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <mutex>

using namespace std;

class id{
	public:
	std::string gen_id();
	std::string get_timestamp(std::string junk);

	private:
	std::mutex mtx;
	std::string get_milli();
	std::string get_time_stamp(std::string string_time_junk);
};



std::string id::gen_id(){
	mtx.lock();

	std::string get_id=this->get_milli();

	mtx.unlock();

	return get_id;
};



std::string id::get_milli(){

	std::string holder;

	auto current_time=std::chrono::system_clock::now();

	auto get_duration=current_time.time_since_epoch();

	auto get_in_milli=std::chrono::duration_cast<std::chrono::milliseconds>(get_duration).count();

	holder=std::to_string(get_in_milli);

	return holder;
};



std::string id::get_timestamp(std::string junk){


	mtx.lock();

	std::string current=this->get_time_stamp(junk);

	mtx.unlock();


	return  current;

};




std::string id::get_time_stamp(std::string string_time_junk){

    time_t time_value=std::stoll(string_time_junk);

    decltype(time_value) div=(time_value/1000);

    char* junk_time=std::ctime(&div);

    return std::string(junk_time);
};
