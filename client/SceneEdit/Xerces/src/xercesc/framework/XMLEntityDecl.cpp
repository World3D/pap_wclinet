/*
 * Copyright 1999-2004 The Apache Software Foundation.
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

/**
 * $Id: XMLEntityDecl.cpp 191705 2005-06-21 19:01:19Z cargilld $
 */


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/framework/XMLEntityDecl.hpp>
#include <../../../SceneEdit/Xerces/src/xercesc/util/XMLUniDefs.hpp>
#include <../../../SceneEdit/Xerces/src/xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  XMLEntityDecl: Constructors and Destructor
// ---------------------------------------------------------------------------
XMLEntityDecl::XMLEntityDecl(MemoryManager* const manager) :

    fId(0)
    , fValueLen(0)
    , fValue(0)
    , fName(0)
    , fNotationName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
}

XMLEntityDecl::XMLEntityDecl(const XMLCh* const entName,
                             MemoryManager* const manager) :

    fId(0)
    , fValueLen(0)
    , fValue(0)
    , fName(0)
    , fNotationName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
    fName = XMLString::replicate(entName, fMemoryManager);
}

typedef JanitorMemFunCall<XMLEntityDecl>  CleanupType;

XMLEntityDecl::XMLEntityDecl(const  XMLCh* const   entName
                            , const XMLCh* const   value
                            , MemoryManager* const manager) :
    fId(0)
    , fValueLen(XMLString::stringLen(value))
    , fValue(0)
    , fName(0)
    , fNotationName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
    CleanupType cleanup(this, &XMLEntityDecl::cleanUp);

    try
    {
        fValue = XMLString::replicate(value, fMemoryManager);
        fName = XMLString::replicate(entName, fMemoryManager);
    }
    catch(const OutOfMemoryException&)
    {
        cleanup.release();

        throw;
    }

    cleanup.release();
}

XMLEntityDecl::XMLEntityDecl(const  XMLCh* const   entName
                            , const XMLCh          value
                            , MemoryManager* const manager) :
    fId(0)
    , fValueLen(1)
    , fValue(0)
    , fName(0)
    , fNotationName(0)
    , fPublicId(0)
    , fSystemId(0)
    , fBaseURI(0)
    , fMemoryManager(manager)
{
    CleanupType cleanup(this, &XMLEntityDecl::cleanUp);

    try
    {
        XMLCh dummy[2] = { chNull, chNull };
        dummy[0] = value;
        fValue = XMLString::replicate(dummy, fMemoryManager);
        fName = XMLString::replicate(entName, fMemoryManager);
    }
    catch(const OutOfMemoryException&)
    {
        cleanup.release();

        throw;
    }

    cleanup.release();
}

XMLEntityDecl::~XMLEntityDecl()
{
    cleanUp();
}


// ---------------------------------------------------------------------------
//  XMLEntityDecl: Setter methods
// ---------------------------------------------------------------------------
void XMLEntityDecl::setName(const XMLCh* const entName)
{
    // Clean up the current name stuff
    if (fName)
       fMemoryManager->deallocate(fName);

    fName = XMLString::replicate(entName, fMemoryManager);
}


// ---------------------------------------------------------------------------
//  XMLEntityDecl: Private helper methods
// ---------------------------------------------------------------------------
void XMLEntityDecl::cleanUp()
{
    fMemoryManager->deallocate(fName);
    fMemoryManager->deallocate(fNotationName);
    fMemoryManager->deallocate(fValue);
    fMemoryManager->deallocate(fPublicId);
    fMemoryManager->deallocate(fSystemId);
    fMemoryManager->deallocate(fBaseURI);
}

/***
 * Support for Serialization/De-serialization
 ***/

IMPL_XSERIALIZABLE_NOCREATE(XMLEntityDecl)

void XMLEntityDecl::serialize(XSerializeEngine& serEng)
{

    if (serEng.isStoring())
    {
        serEng<<fId;
        serEng<<fValueLen;
        serEng.writeString(fValue);
        serEng.writeString(fName);
        serEng.writeString(fNotationName);
        serEng.writeString(fPublicId);
        serEng.writeString(fSystemId);
        serEng.writeString(fBaseURI);
    }
    else
    {
        serEng>>fId;
        serEng>>fValueLen;
        serEng.readString(fValue);
        serEng.readString(fName);
        serEng.readString(fNotationName);
        serEng.readString(fPublicId);
        serEng.readString(fSystemId);
        serEng.readString(fBaseURI);
    }
}

XERCES_CPP_NAMESPACE_END

