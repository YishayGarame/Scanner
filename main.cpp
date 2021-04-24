#include "scanner.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << "--tokens | --xref  filename" << endl;
		return 1;
	}
	ifstream inputFile(argv[2]);
	if (! inputFile) {
		cout << "Unable to open input file " << argv[2] << endl;
		return 1;
	}

	//
	varToken vt("x");
	vt.printToken();
	vt.add_line(3);
	vt.add_line(4);
	vt.add_line(32);

	SymbolTable s;
	cout << "aa: " << (s.lookupToken("x") == nullptr) << endl;
	s.insertToken("x", make_shared<varToken>(vt));
	cout << "aa: " << (s.lookupToken("x") == nullptr) << endl;
	s.xref();
	//

	SymbolTable symTab;			// create symbol table
	Scanner scanner(inputFile, symTab);	// create scanner
	shared_ptr<Token> tokenp;		// pointer to token object
	if (argv[1] == string("-t") || argv[1] == string("--tokens")) { // output tokens
		cout << "Type\tText\n\n";
		while(tokenp = scanner.nextToken()) {
			tokenp->printToken();
		}
	}

	if (argv[1] == string("-x") || argv[1] == string("--xref")) {	// output cross-reference
		while(tokenp = scanner.nextToken())                     // scan the whole file
			;			
		cout << "Variable\tLines\n\n";
		symTab.xref();
	}
	inputFile.close();
}

