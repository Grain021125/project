#pragma once
#include "const.h"

struct SectionInfo
{
	SectionInfo() {}
	~SectionInfo()
	{
		_section_datas.clear();
	}

	std::map<std::string, std::string> _section_datas;
	
	SectionInfo(const SectionInfo& src) {
		_section_datas = src._section_datas;
	}

	SectionInfo& operator=(const SectionInfo& src) {
		if (&src == this) {
			return *this;
		}

		this->_section_datas = src._section_datas;
		return *this;
	}

	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}

		return _section_datas[key];
	}
};

class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}

	static ConfigMgr& GetInstance() {
		static ConfigMgr instance;
		return instance;
	}

	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}

		return _config_map[section];
	}

private:
	ConfigMgr();
	ConfigMgr(const ConfigMgr&) = delete;
	ConfigMgr& operator=(const ConfigMgr& src) = delete;

	std::map<std::string, SectionInfo> _config_map;
};

