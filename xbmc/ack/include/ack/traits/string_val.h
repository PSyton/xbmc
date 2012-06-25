#pragma once

#define STRING_VALUE_DECL(name, val) class String_Value_##name {public: operator QString() const {return val;} };

#define STRING_VALUE(name) String_Value_##name 
