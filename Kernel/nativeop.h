// $Id$
/* @@tag:xara-cn@@ DO NOT MODIFY THIS LINE
================================XARAHEADERSTART===========================
 
               Xara LX, a vector drawing and manipulation program.
                    Copyright (C) 1993-2006 Xara Group Ltd.
       Copyright on certain contributions may be held in joint with their
              respective authors. See AUTHORS file for details.

LICENSE TO USE AND MODIFY SOFTWARE
----------------------------------

This file is part of Xara LX.

Xara LX is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as published
by the Free Software Foundation.

Xara LX and its component source files are distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with Xara LX (see the file GPL in the root directory of the
distribution); if not, write to the Free Software Foundation, Inc., 51
Franklin St, Fifth Floor, Boston, MA  02110-1301 USA


ADDITIONAL RIGHTS
-----------------

Conditional upon your continuing compliance with the GNU General Public
License described above, Xara Group Ltd grants to you certain additional
rights. 

The additional rights are to use, modify, and distribute the software
together with the wxWidgets library, the wxXtra library, and the "CDraw"
library and any other such library that any version of Xara LX relased
by Xara Group Ltd requires in order to compile and execute, including
the static linking of that library to XaraLX. In the case of the
"CDraw" library, you may satisfy obligation under the GNU General Public
License to provide source code by providing a binary copy of the library
concerned and a copy of the license accompanying it.

Nothing in this section restricts any of the rights you have under
the GNU General Public License.


SCOPE OF LICENSE
----------------

This license applies to this program (XaraLX) and its constituent source
files only, and does not necessarily apply to other Xara products which may
in part share the same code base, and are subject to their own licensing
terms.

This license does not apply to files in the wxXtra directory, which
are built into a separate library, and are subject to the wxWindows
license contained within that directory in the file "WXXTRA-LICENSE".

This license does not apply to the binary libraries (if any) within
the "libs" directory, which are subject to a separate license contained
within that directory in the file "LIBS-LICENSE".


ARRANGEMENTS FOR CONTRIBUTION OF MODIFICATIONS
----------------------------------------------

Subject to the terms of the GNU Public License (see above), you are
free to do whatever you like with your modifications. However, you may
(at your option) wish contribute them to Xara's source tree. You can
find details of how to do this at:
  http://www.xaraxtreme.org/developers/

Prior to contributing your modifications, you will need to complete our
contributor agreement. This can be found at:
  http://www.xaraxtreme.org/developers/contribute/

Please note that Xara will not accept modifications which modify any of
the text between the start and end of this header (marked
XARAHEADERSTART and XARAHEADEREND).


MARKS
-----

Xara, Xara LX, Xara X, Xara X/Xtreme, Xara Xtreme, the Xtreme and Xara
designs are registered or unregistered trademarks, design-marks, and/or
service marks of Xara Group Ltd. All rights in these marks are reserved.


      Xara Group Ltd, Gaddesden Place, Hemel Hempstead, HP2 6EX, UK.
                        http://www.xara.com/

=================================XARAHEADEREND============================
 */
// Operation to load and save in the Native EPS format.
// These ops are initiated from the File Save / Load menu options eventually

#ifndef INC_NATIVEOP
#define INC_NATIVEOP


#include "selop.h"
#include "pathname.h"

#define	OPTOKEN_NATIVELOAD		wxT("NativeLoad")
#define	OPTOKEN_NATIVESAVE		wxT("NativeSave")
#define	OPTOKEN_SAVEASNATIVEV1	wxT("SaveAsNativeV1")
#define OPTOKEN_SAVEASDEFAULT	wxT("SaveAsDefault")

// Forward references.
class CCLexFile;


// These are the parameters that the native file Operations take.  They are passed by
// pointer to the Operations as the first parameter of the OpParam.
struct NativeFileOpParams
{
	CCLexFile* pFile;
	BOOL	   fStatus;
	UINT32	   nPrefFilter;
};


// This global function is a useful shorthand for the rigmarole you have to go through
// to invoke Operations.  It returns TRUE if the given Operation on the given file is
// successful.
BOOL InvokeNativeFileOp(const TCHAR* pOpName, CCLexFile* pFile, UINT32 nPrefFilter);



/********************************************************************************************

>	class OpMenuLoad : public SelOperation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	Imports the specified file as NativeEPS.

********************************************************************************************/

class OpMenuLoad : public SelOperation
{
	CC_DECLARE_DYNCREATE(OpMenuLoad)

public:
	virtual void DoWithParam(OpDescriptor*, OpParam* pOpParam);

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

	// Karim 21/01/2000 - see UndoableOperation base implementation.
	virtual BOOL MayChangeNodeBounds() const { return FALSE; }

protected:
	BOOL LoadFile(CCLexFile* pFileToLoad, UINT32 nPrefFilter);
};



/********************************************************************************************

>	class OpMenuSave : public Operation

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/12/94
	Purpose:	Saves the document to the file specified in the params to the disk using the
				NativeEPS format.

********************************************************************************************/

class OpMenuSave : public Operation
{
	CC_DECLARE_DYNCREATE(OpMenuSave)

public:
	virtual void DoWithParam ( OpDescriptor*, OpParam* pOpParam );
	virtual void Do ( OpDescriptor* pOpDesc );

	static BOOL Init ();
	static OpState GetState (String_256*, OpDescriptor*);

protected:
	virtual BOOL FindFilterAndSave ( CCLexFile* pFile, UINT32 nPrefFilter );
	virtual Filter* FindFilter ( UINT32 nPrefFilter );
	virtual BOOL Save ( Filter *pFilter, CCLexFile* pFile );
	virtual BOOL SaveSpecificFile ( Filter*, CCLexFile* pFile );

	virtual UINT32 GetSearchFilterId ();
	virtual BOOL EnsureFileTypeCorrectId (Filter *pFilter, PathName& Path);
	virtual BOOL FixFileType ();
};

/********************************************************************************************

>	class OpSaveAsNativeV1 : public OpMenuSave

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com>
	Created:	1/8/96
	Purpose:	Saves the document to the file specified in the params to the disk using the
				Version 1 Native format i.e. Native EPS.

********************************************************************************************/

class OpSaveAsNativeV1 : public OpMenuSave
{
	CC_DECLARE_DYNCREATE(OpSaveAsNativeV1)

public:
	// Use the base class versions of Do and DoWithParam

	static BOOL Init();
	static OpState GetState(String_256*, OpDescriptor*);

protected:
	virtual UINT32 GetSearchFilterId();

	virtual BOOL FixFileType();
};



#endif  // INC_NATIVEOP

