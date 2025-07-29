#pragma once
#include "const.h"
#include "MysqlDAO.h"
class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
};

