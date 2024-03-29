/// \file qparms.h
/// \brief Declares the template query parameter-related stuff.
///
/// The classes defined in this file are used by class Query when it
/// parses a template query: they hold information that it finds in the
/// template, so it can assemble a SQL statement later on demand.

/***********************************************************************
 Copyright (c) 1998 by Kevin Atkinson, (c) 1999, 2000 and 2001 by
 MySQL AB, and (c) 2004, 2005 by Educational Technology Resources, Inc.
 Others may also hold copyrights on code in this file.  See the CREDITS
 file in the top directory of the distribution for details.

 This file is part of MySQL++.

 MySQL++ is free software; you can redistribute it and/or modify it
 under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 MySQL++ is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with MySQL++; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
 USA
***********************************************************************/

#ifndef MYSQLPP_QPARMS_H
#define MYSQLPP_QPARMS_H

#include "sql_string.h"

#include <vector>

namespace mysqlpp {

class Query;


/// \brief This class holds the parameter values for filling
/// template queries. 
class SQLQueryParms : public std::vector<SQLString>
{
public:
	/// \brief Abbreviation so some of the declarations below don't
	/// span many lines.
	typedef const SQLString& ss;

	/// \brief Default constructor
	SQLQueryParms() :
	parent_(0)
	{
	}
	
	/// \brief Create object
	///
	/// \param p pointer to the query object these parameters are tied
	/// to
	SQLQueryParms(Query* p) :
	parent_(p)
	{
	}
	
	/// \brief Returns true if we are bound to a query object.
	///
	/// Basically, this tells you which of the two ctors were called.
	bool bound()
	{
		return parent_ != 0;
	}

	/// \brief Clears the list
	void clear()
	{
		erase(begin(), end());
	}

	/// \brief Access element number n
	SQLString& operator [](size_type n)
	{
		if (n >= size())
			insert(end(), (n + 1) - size(), "");
		return std::vector<SQLString>::operator [](n);
	}

	/// \brief Access element number n
	const SQLString& operator [](size_type n) const
	{
		return std::vector<SQLString>::operator [](n);
	}
	
	/// \brief Access the value of the element with a key of str.
	MYSQLPP_EXPORT SQLString& operator [](const char *str);

	/// \brief Access the value of the element with a key of str.
	MYSQLPP_EXPORT const SQLString& operator [](const char *str) const;

	/// \brief Adds an element to the list
	SQLQueryParms& operator <<(const SQLString& str)
	{
		push_back(str);
		return *this;
	}

	/// \brief Adds an element to the list
	SQLQueryParms& operator +=(const SQLString& str)
	{
		push_back(str);
		return *this;
	}

	/// \brief Build a composite of two parameter lists
	///
	/// If this list is (a, b) and \c other is (c, d, e, f, g), then
	/// the returned list will be (a, b, e, f, g).  That is, all of this
	/// list's parameters are in the returned list, plus any from the
	/// other list that are in positions beyond what exist in this list.
	///
	/// If the two lists are the same length or this list is longer than
	/// the \c other list, a copy of this list is returned.
	MYSQLPP_EXPORT SQLQueryParms operator +(
			const SQLQueryParms& other) const;

#if !defined(DOXYGEN_IGNORE)
// Doxygen will not generate documentation for this section.
	void set(ss a)
	{
		clear();
		*this << a;
	}
	void set(ss a, ss b)
	{
		clear();
		*this << a << b;
	}
	void set(ss a, ss b, ss c)
	{
		clear();
		*this << a << b << c;
	}
	void set(ss a, ss b, ss c, ss d)
	{
		clear();
		*this << a << b << c << d;
	}
	void set(ss a, ss b, ss c, ss d, ss e)
	{
		clear();
		*this << a << b << c << d << e;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f)
	{
		clear();
		*this << a << b << c << d << e << f;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g)
	{
		clear();
		*this << a << b << c << d << e << f << g;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g, ss h)
	{
		clear();
		*this << a << b << c << d << e << f << g << h;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g, ss h, ss i)
	{
		clear();
		*this << a << b << c << d << e << f << g << h << i;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g, ss h, ss i, ss j)
	{
		clear();
		*this << a << b << c << d << e << f << g << h << i << j;
	}
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g, ss h, ss i, ss j, ss k)
	{
		clear();
		*this << a << b << c << d << e << f << g << h << i << j << k;
	}
#endif // !defined(DOXYGEN_IGNORE)

	/// \brief Set the template query parameters.
	///
	/// Sets parameter 0 to a, parameter 1 to b, etc. There are
	/// overloaded versions of this function that take anywhere from
	/// one to a dozen parameters.
	void set(ss a, ss b, ss c, ss d, ss e, ss f, ss g,
			ss h, ss i, ss j, ss k, ss l)
	{
		clear();
		*this << a << b << c << d << e << f << g << h << i << j << k << l;
	}

private:
	friend class Query;

	Query* parent_;
};


/// \brief Used within Query to hold elements for parameterized
/// queries.
///
/// Each element has three parts:
///
/// The concept behind the \c before variable needs a little explaining.
/// When a template query is parsed, each parameter is parsed into one
/// of these SQLParseElement objects, but the non-parameter parts of the
/// template also have to be stored somewhere.  MySQL++ chooses to
/// attach the text leading up to a parameter to that parameter.  So,
/// the \c before string is simply the text copied literally into the
/// finished query before we insert a value for the parameter.
///
/// The \c option character is currently one of 'q', 'Q', 'r', 'R' or
/// ' '.  See the "Template Queries" chapter in the user manual for
/// details.
///
/// The position value (\c num) allows a template query to have its
/// parameters in a different order than in the Query method call.
/// An example of how this can be helpful is in the "Template Queries"
/// chapter of the user manual.

struct SQLParseElement
{
	/// \brief Create object
	///
	/// \param b the 'before' value
	/// \param o the 'option' value
	/// \param n the 'num' value
	SQLParseElement(std::string b, char o, char n) :
	before(b),
	option(o),
	num(n)
	{
	}
	
	std::string before;		///< string inserted before the parameter
	char option;			///< the parameter option, or blank if none
	char num;				///< the parameter position to use
};

} // end namespace mysqlpp

#endif // !defined(MYSQLPP_QPARMS_H)

