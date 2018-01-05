/*	  _____
	 /	   |			INI Writer
	| .ini |_  _ 		version 1.0.0
	|	  _\ \/ /_		https://github.com/Oradle/INI-Writer
	|___ |_  ()  _|		
	       /_/\_\
		   
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2018 Oradle

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#ifndef _INI_WRITER_
#define _INI_WRITER_

#include <fstream> // ofstream
#include <map> // map
#include <ostream> // ostream, ios, endl
#include <string> // string, to_string
#include <type_traits> // enable_if, is_same, is_arithmetic, is_integral


namespace samilton {
	// force declaration
	class INIstring;
	class INIsectionMap;

	class INIWriter {
	public:
		/*!
		@brief  enum class that contain boolean types which uses for
		changing how bool variables will be looks in file
		*/
		enum class INIbooleanType {
			INI_true_false,
			INI_True_False,
			INI_TRUE_FALSE,
			INI_yes_no,
			INI_Yes_No,
			INI_YES_NO,
			INI_on_off,
			INI_On_Off,
			INI_ON_OFF,
			INI_1_0
		};

		/*!
		@brief  default constructor that set boolean type to "true/false"
		*/
		INIWriter() {
			_boolType = new INIbooleanType;
			*_boolType = INIbooleanType::INI_true_false;
		}

		/*!
		@brief  constructor that set boolean type by param
		@param[in] boolType  boolean type that should be set
		*/
		INIWriter(const INIbooleanType &boolType) {
			_boolType = new INIbooleanType;
			*_boolType = boolType;
		}

		/*!
		@brief  clear all data and set boolean type to default "true/false"
		*/
		void clear();

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		void saveToFile(T fileName, const int &iosMode = std::ios::trunc) const;

		/*!
		@brief  set boolean type by param
		@param[in] type  boolean type that should be set
		*/
		void setBooleanType(const INIbooleanType &type) {
			*_boolType = type;
		}

		friend std::ostream &operator<<(std::ostream& ofstr, const INIWriter& ini);

		friend std::ostream &operator>>(const INIWriter& ini, std::ostream& ofstr) {
			return ofstr << ini;
		}

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		INIsectionMap &operator[](T section) {
			if (_INImap[section] == nullptr)
				_INImap[section] = new INIsectionMap(_boolType);
			return *_INImap[section];
		}

		template<class T, 
		class = typename std::enable_if<std::is_integral<T>::value>::type>
		INIsectionMap &operator[](const T &section) {
			if (_INImap[std::to_string(section)] == nullptr)
				_INImap[std::to_string(section)] = new INIsectionMap(_boolType);
			return *_INImap[std::to_string(section)];
		}

		~INIWriter() {
			clear();
			delete _boolType;
		}

	private:
		std::map<std::string, INIsectionMap*> _INImap;
		INIbooleanType *_boolType;
	};

	class INIstring {
	public:

		INIstring(INIWriter::INIbooleanType *type) {
			_boolType = type;
		}

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		INIstring operator=(T val) {
			_str = val;
			return *this;
		}

		template<class T, 
		class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
		INIstring operator=(const T &val) {
			_str = std::to_string(val);
			return *this;
		}

		INIstring operator=(const bool val) {
			if (val)
				switch (*_boolType)
				{
				case INIWriter::INIbooleanType::INI_true_false:
					_str = "true";
					break;
				case INIWriter::INIbooleanType::INI_True_False:
					_str = "True";
					break;
				case INIWriter::INIbooleanType::INI_TRUE_FALSE:
					_str = "TRUE";
					break;
				case INIWriter::INIbooleanType::INI_yes_no:
					_str = "yes";
					break;
				case INIWriter::INIbooleanType::INI_Yes_No:
					_str = "Yes";
					break;
				case INIWriter::INIbooleanType::INI_YES_NO:
					_str = "YES";
					break;
				case INIWriter::INIbooleanType::INI_on_off:
					_str = "on";
					break;
				case INIWriter::INIbooleanType::INI_On_Off:
					_str = "On";
					break;
				case INIWriter::INIbooleanType::INI_ON_OFF:
					_str = "ON";
					break;
				case INIWriter::INIbooleanType::INI_1_0:
					_str = "1";
					break;
				}
			else
				switch (*_boolType)
				{
				case INIWriter::INIbooleanType::INI_true_false:
					_str = "false";
					break;
				case INIWriter::INIbooleanType::INI_True_False:
					_str = "False";
					break;
				case INIWriter::INIbooleanType::INI_TRUE_FALSE:
					_str = "FALSE";
					break;
				case INIWriter::INIbooleanType::INI_yes_no:
					_str = "no";
					break;
				case INIWriter::INIbooleanType::INI_Yes_No:
					_str = "No";
					break;
				case INIWriter::INIbooleanType::INI_YES_NO:
					_str = "NO";
					break;
				case INIWriter::INIbooleanType::INI_on_off:
					_str = "off";
					break;
				case INIWriter::INIbooleanType::INI_On_Off:
					_str = "Off";
					break;
				case INIWriter::INIbooleanType::INI_ON_OFF:
					_str = "OFF";
					break;
				case INIWriter::INIbooleanType::INI_1_0:
					_str = "0";
					break;
				}

			return *this;
		}

	private:
		std::string _str;
		INIWriter::INIbooleanType *_boolType;

		friend std::ostream &operator<<(std::ostream& ofstr, const INIWriter& ini);

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		friend void INIWriter::saveToFile(T fileName, const int &iosMode) const;
	};

	class INIsectionMap {
	public:

		INIsectionMap(INIWriter::INIbooleanType *type) {
			_boolType = type;
		}

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		INIstring &operator[](T name) {
			if (_sectionMap[name] == nullptr)
				_sectionMap[name] = new INIstring(_boolType);
			return *_sectionMap[name];
		}

		template<class T, 
		class = typename std::enable_if<std::is_integral<T>::value>::type>
		INIstring &operator[](const T &name) {
			if (_sectionMap[std::to_string(name)] == nullptr)
				_sectionMap[std::to_string(name)] = new INIstring(_boolType);
			return *_sectionMap[std::to_string(name)];
		}

		~INIsectionMap() {
			for (auto &i : _sectionMap)
				delete i.second;
		}

	private:
		friend std::ostream &operator<<(std::ostream& ofstr, const INIWriter& ini);

		template<class T, 
		class = typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const char*>::value>::type>
		friend void INIWriter::saveToFile(T fileName, const int &iosMode) const;

		INIWriter::INIbooleanType *_boolType;
		std::map<std::string, INIstring*> _sectionMap;
	};


	template<class T, class>
	void INIWriter::saveToFile(T fileName, const int &iosMode) const {
		std::ofstream file(fileName, iosMode);

		for (auto &i : _INImap) {
			file << '[' << i.first << ']' << std::endl;

			for (auto &j : i.second->_sectionMap) {
				file << j.first << " = " << j.second->_str << std::endl;
			}

			file << std::endl;
		}

		file.close();
	}

	inline std::ostream &operator<<(std::ostream& ofstr, const INIWriter& ini) {
		for (auto &i : ini._INImap) {
			ofstr << '[' << i.first << ']' << std::endl;

			for (auto &j : i.second->_sectionMap) {
				ofstr << j.first << " = " << j.second->_str << std::endl;
			}

			ofstr << std::endl;
		}

		return ofstr;
	}

	inline void INIWriter::clear() {
		for (auto &i : _INImap)
			delete i.second;
		*_boolType = INIbooleanType::INI_true_false;

		_INImap.clear();
	}
}
#endif // _INI_WRITER_