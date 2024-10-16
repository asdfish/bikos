#include <flags.hpp>

CheckboxFlag::CheckboxFlag(const std::string& name, const std::vector<std::string>& items) {
  this->name = name;
  this->items = items;
  
  selections.reserve(items.size());
  for(unsigned int i = 0; i < items.size(); i ++)
    selections.push_back(false);
}

bool CheckboxFlag::check_syntax(Json::Value& json_root) {
  if(!json_root[name].isArray())
    return false;

  for(unsigned int i = 0; i < json_root[name].size(); i ++)
    if(!json_root[name][i].isBool())
      return false;

  return true;
}

void CheckboxFlag::into_json(Json::Value& json_root) {
  Json::Value array;
  for(unsigned int i = 0; i < selections.size(); i ++)
    array[i] = (bool) selections[i];

  json_root[name] = array;
}

DropdownFlag::DropdownFlag(const std::string& name, const std::vector<std::string>& items) {
  this->name = name;
  this->items = items;
}

bool DropdownFlag::check_syntax(Json::Value& json_root) {
  if(!json_root[name].isConvertibleTo(Json::ValueType::uintValue))
    return false;

  if(json_root[name] >= items.size())
    return false;

  return true;
}

void DropdownFlag::into_json(Json::Value& json_root) {
  json_root[name] = selection;
}
