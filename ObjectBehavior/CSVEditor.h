#pragma once
#include "define.h"
#include "Strings.h"

class CSVEditor {
private:
	vector<Strings> _table;
	int _rowLength = 0;

public:
	CSVEditor(const char* const fpath);
	~CSVEditor();

public:
	inline int rowLength() { return _rowLength; }
	inline int colLength(int rowIndex) { 
		return _table[rowIndex].size(); 
	}
	inline string getString(int rowIndex, int colIndex) { 
		return getValue(rowIndex, colIndex); 
	}
	inline int getInt(int rowIndex, int colIndex) { 
		return atoi(getValue(rowIndex, colIndex).c_str()); 
	}

private:
	inline string& getValue(int rowIndex, int colIndex) { 
		return _table[rowIndex].getString(colIndex); 
	}

private:
	inline void setRowLength(int rowLength) { _rowLength = rowLength; }
};

