/*
 * Copyright 1999-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: XMLDOMComment.h 191054 2005-06-17 02:56:35Z jberry $
 */

#ifndef ___xmldomcomment_h___
#define ___xmldomcomment_h___

#include <xercesc/dom/DOMComment.hpp>
#include "IXMLDOMCharacterDataImpl.h"

XERCES_CPP_NAMESPACE_USE

class ATL_NO_VTABLE CXMLDOMComment :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IXMLDOMCharacterDataImpl<IXMLDOMComment, &IID_IXMLDOMComment>
{
public:
	CXMLDOMComment()
	{}

	void	FinalRelease()
	{
		ReleaseOwnerDoc();
	}

	virtual DOMCharacterData* get_DOMCharacterData()  { return comment;}
	virtual DOMNodeType get_DOMNodeType() const			{ return NODE_COMMENT; }
	
DECLARE_NOT_AGGREGATABLE(CXMLDOMComment)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLDOMComment)
	COM_INTERFACE_ENTRY(IXMLDOMComment)
	COM_INTERFACE_ENTRY(IXMLDOMCharacterData)
	COM_INTERFACE_ENTRY(IXMLDOMNode)
	COM_INTERFACE_ENTRY(IIBMXMLDOMNodeIdentity)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DOMComment* comment;
};

typedef CComObject<CXMLDOMComment> CXMLDOMCommentObj;

#endif // ___xmldomcomment_h___