/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *   astyle.h
 *
 *   This file is a part of "Artistic Style" - an indentation and
 *   reformatting tool for C, C++, C# and Java source files.
 *   http://astyle.sourceforge.net
 *
 *   The "Artistic Style" project, including all files needed to
 *   compile it, is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later
 *   version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this project; if not, write to the
 *   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *   Boston, MA  02110-1301, USA.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
 
 /*
 	2008-01-26 Patches by Massimo Del Fedele :
 		- modified sources to use Ultimate++ containers instead std:: ones
 		- fixed memory leaks based on bug report 1804791 submitted by Eran Ifrah
 		- modified to work with unicode
 */
#include "ASStringTools.hpp"

///////////////////////////////////////////////////////////////////////////////////////////
// Replaces a chunk in a string with a new string
void ASString_Replace(WString &s, int Pos, int Len, WString const &newString)
{
	if(Pos < 0 || Pos >= s.GetCount())
		return;
	s.Remove(Pos, Len);
	s.Insert(Pos, newString);
	
} // END ASString_Replace()

///////////////////////////////////////////////////////////////////////////////////////////
// Find first character in a string *not* contained in another string
int ASString_Find_First_Not_Of(WString const &s, WString const &Pattern, int pos)
{
	if(pos < 0 || pos >= s.GetCount())
		return -1;
	int len = s.GetCount();
	while(pos < len && Pattern.Find(s[pos]) != -1)
		pos++;
	if(pos < len)
		return pos;
	else
		return -1;
	
} // END ASString_Find_First_Not_Of()

///////////////////////////////////////////////////////////////////////////////////////////
// Find last character in a string *not* contained in another string
int ASString_Find_Last_Not_Of(WString const &s, WString const &Pattern, int pos)
{
	if(pos < 0 || pos >= s.GetCount())
		pos = s.GetCount() -1;
	while(pos > 0 && Pattern.Find(s[pos]) != -1)
		pos--;
	return pos;

} // END ASString_Find_Last_Not_Of()

///////////////////////////////////////////////////////////////////////////////////////////
// Finds a substring starting at the end of a given string
int ASString_ReverseFind(WString const &s, WString const &Pattern)
{
	int pos = -1;
	int k = 0;
	while( (k = s.Find(Pattern, k)) >= 0)
		pos = k++;
	return pos;
	
} // END ASString_ReverseFind()
