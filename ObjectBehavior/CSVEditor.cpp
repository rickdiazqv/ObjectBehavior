#include "CSVEditor.h"

CSVEditor::CSVEditor(const char* const fpath) {
	string resource = DxFileRead(fpath);
	Strings lines("\n", resource);

	setRowLength(lines.size());
	int maxColLength = 0;
	for (int i = 0; i < _rowLength; i++) {
		_table.push_back(Strings(",", lines.getString(i)));
	}

	/*for (int i = 0; i < _rowLength; i++) {
		Strings& strs = _table[i];
		for (int j = 0; j < strs.size(); j++) {
			printfDx("%s, ", strs.getString(j).c_str());
		}
		printfDx("\n");
	}*/
}

CSVEditor::~CSVEditor() {

}