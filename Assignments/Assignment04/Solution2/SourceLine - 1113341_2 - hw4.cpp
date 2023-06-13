// SourceLine class member-function definitions.

#include <iostream>
using std::cout;
using std::endl;

#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine()
	: sourceLine()
{
}

SourceLine& SourceLine::operator=( const char * const ptr )
{
	sourceLine = ptr;
	return *this;
}

void SourceLine::delComments()
{
	size_t length = sourceLine.size();
	for (size_t i = 0; i < length; i++) {
		if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
		{
			sourceLine.erase(i, length); /*set soureceLine.myData.mySize as i(start of comment)*/
			break; /*a sourceLine only has one comment*/
		}
		/*length = sourceLine.size();*/
	}
	//cout << sourceLine << endl;
}

void SourceLine::delStrConst()
{
	//size_t length = sourceLine.size();
	size_t strStart{}, strEnd{};
	for (size_t i = 0; i < sourceLine.size(); i++) {
		if (sourceLine.begin()[i] == '"') {
			strStart = i;
			for (size_t j = i; j < sourceLine.size(); j++) {
				if (sourceLine.begin()[j + 1] == '"' && sourceLine.begin()[j] != '\\') {
					strEnd = j + 1;
				}
			}
			/*if cannot find strEnd, means the rest of sourceLine should be erased*/
			if (strEnd - strStart < 0) {
				sourceLine.erase(strStart, sourceLine.size()); 
				break;
			}

			sourceLine.erase(strStart, strEnd - strStart + 1);
			//i = strEnd;
		}
	}
	//cout << "a" << sourceLine << endl;
}

void SourceLine::delCharConst()
{
	//size_t length = sourceLine.size();
	size_t charStart{}, charEnd{};
	//cout << "indelChar\n";
	//cout << endl << "cSize: " << sourceLine.size() << endl;
	for (size_t i = 0; i < sourceLine.size(); i++) {
		if (sourceLine.begin()[i] == '\'' && sourceLine.begin()[i + 1] == '\\') {
			sourceLine.erase(i, 4);
		}
		else if (sourceLine.begin()[i] == '\'' && sourceLine.begin()[i + 1] != '\\')
			sourceLine.erase(i, 3);
	}
	/*cout << "b" << sourceLine << endl;*/
}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{
	string token;
	size_t length = sourceLine.size();
	size_t idStart{}, idEnd{};
	//cout << sourceLine << endl << endl;
	for (size_t i = 0; i < length; i++) 
	{
		if (isalpha(sourceLine[i]))
		{
			idStart = i;
			for (size_t j = i + 1; j <= length; j++) /*j <= length because idStart may be the last character*/
			{
				if (!isalnum(sourceLine[j]) && sourceLine[j] != '_')
				{
					idEnd = j;
					break;
				}
				/*else 
					idEnd = length - 1;*/ /*cannot find idEnd in sourceLine, means delete all character after idStart*/
			}
			//cout << "idS " << idStart << ": " << sourceLine[idStart] << 
			//	"idE " << idEnd << ": " << sourceLine[idEnd] << endl;
			/*if (idEnd - idStart <= 0) break;*/
			/*99~100 & 104: idEnd must be length in the end, so don't need these 3 lines*/
			token = sourceLine.substr(idStart, idEnd - idStart);
			//cout << "token: " << token << endl;
			identifiers.push_back(token);
			//cout << identifiers[0];
			i = idEnd;
		}
	}
}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
	return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
	return !( lhs == rhs );
}