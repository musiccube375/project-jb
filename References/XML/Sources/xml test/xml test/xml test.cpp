// xml test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include "tinyxml.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// Make xml: <?xml ..><Hello>World</Hello>
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	TiXmlElement * element = new TiXmlElement( "Hello" );
	element->SetAttribute("X", "3");
	//TiXmlText * text = new TiXmlText( "World" );
	//element->LinkEndChild( text );
	doc.LinkEndChild( decl );
	doc.FirstChildElement("First");
	doc.LinkEndChild( element );
	doc.SaveFile( "madeByHand.xml" );

	getch();
	return 0;
}

