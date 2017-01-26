/** This project is used to generate fragment-based index for multiversion data in XML format.
 *  Author: Nimisha Srinivasa
 **/

#include "XMLDataParser.h"
#include <glibmm/convert.h> //For Glib::ConvertError
#include <iostream>
using namespace std;


XMLDataParser::XMLDataParser()
  : xmlpp::SaxParser()
{
  curr_page = NULL;
  cluster_creator = new CreateCluster();
  cluster_creator->choice = RepresentativeChoice::Latest;  //latest by default
}

XMLDataParser::~XMLDataParser()
{
}

void XMLDataParser::on_start_document()
{
  curr_state = State::startState;
}

void XMLDataParser::on_end_document()
{
  curr_state = State::endState;
  cluster_creator->gen_index_for_all_cluster();
  cluster_creator->output_convert_table();
}

void XMLDataParser::on_start_element(const Glib::ustring& name,
                                   const AttributeList& attributes)
{
    if(name.compare("data")==0 && curr_state==State::startState){
      curr_state = State::insideData;
    }
    else if(name.compare("version")==0 && curr_state==State::insideData){
      curr_state = State::insideVersion;
    }
    else if(name.compare("page")==0 && (curr_state==State::insideVersion || curr_state == State::outsideContent)){
      curr_state = State::insidePage;
      curr_page = new Page();
    }
    else if(name.compare("title")==0 && curr_state==State::insidePage){
      curr_state = State::insideTitle;
    }
    else if(name.compare("content")==0 && curr_state==State::insidePage){
      curr_state = State::insideContent;
    }
}

void XMLDataParser::on_end_element(const Glib::ustring& name)
{
  if(name.compare("data")==0 && curr_state==State::insideData){
    curr_state = State::endState;
  }
  else if(name.compare("version")==0 && curr_state==State::insideVersion){
    curr_state = State::insideData;
  }
  else if(name.compare("page")==0 && curr_state==State::insidePage){
    //curr_page->displayPage();
    cluster_creator->deal_with_ver(curr_page);
    delete curr_page;
    curr_state = State::insideVersion;
  }
  else if(name.compare("title")==0 && curr_state==State::insideTitle){
    curr_state = State::insidePage;
  }
  else if(name.compare("content")==0 && curr_state==State::insideContent){
    curr_state = State::insidePage;
  }
}

void XMLDataParser::on_characters(const Glib::ustring& text)
{
  try
  {
    if(curr_state == State::insideTitle){
      curr_page->addTitle(text);
    }
    else if(curr_state == State::insideContent){
      curr_page->addContent(text);
    }
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "XMLDataParser::on_characters(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void XMLDataParser::on_warning(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_warning(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "XMLDataParser::on_warning(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void XMLDataParser::on_error(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_error(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "XMLDataParser::on_error(): Exception caught while converting text for std::cout: " << ex.what() << std::endl;
  }
}

void XMLDataParser::on_fatal_error(const Glib::ustring& text)
{
  try
  {
    std::cout << "on_fatal_error(): " << text << std::endl;
  }
  catch(const Glib::ConvertError& ex)
  {
    std::cerr << "XMLDataParser::on_characters(): Exception caught while converting value for std::cout: " << ex.what() << std::endl;
  }
}
void XMLDataParser::setRepresentativeChoice(RepresentativeChoice c){
  cluster_creator->choice = c;
}