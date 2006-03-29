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

/********************************************************************************************

	menucmds.cpp - This module provides a set of menu command functions which are called from
	OIL Menu Module when an appropriate menu item is selected. 

********************************************************************************************/


#include "camtypes.h" 
//#include <afxext.h>

#include "menucmds.h"
#include "camelot.h"
//#include "mainfrm.h"
#include "camdoc.h"
//#include "camvw.h"
#include "ensure.h"
#include "printing.h"
#include "helpuser.h"
#include "menuops.h"
#include "docview.h"
#include "bars.h"
#include "camview.h"
//#ifdef WEBSTER
//#include "ollie.h"
//#include "resource.h"
//#include "simon.h"
//#include "registry.h"
#include "product.h"
//#include "resimmap.h"
#include "app.h"
#include "fileutil.h"
#include "sgliboil.h"
//#endif //webster
#include "group.h"			// for management of blend stuff
#include "rechblnd.h"		// so that can reset blend pointers
//#include "urls.h"

DECLARE_SOURCE("$Revision: 662 $");  
#define THIRTY_TWO 32

/********************************************************************************************

>	void ExitAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Exit application menu function.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()
	SeeAlso:	State()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/

void ExitAction() 
{               
	AfxGetApp().OnAppExit();
}
 
 
/********************************************************************************************

>	void FileNewAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs New File menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/

void FileNewAction() 
{               
	//First tell the document system that the next template to use is the
	//default animation template
	CCamDoc::SetNextTemplateToUse(DocOps::GetDefaultDrawingTemplate());

	// OnFileOpen needs an event, but doesn't use it
	wxCommandEvent event;
	AfxGetApp().GetDocumentManager()->OnFileNew( event );

	CCamDoc::EnableRemoveUntouchedDocs();		// Next idle event will try ro get rid of 
												// the auto-created startup document
}

/********************************************************************************************

>	void FileNewAnimationAction(); 	

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/10/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Opens the animation template
	Errors:		-
	SeeAlso:	MenuCmds

********************************************************************************************/

void FileNewAnimationAction() 
{               
	//First tell the document system that the next template to use is the
	//default animation template
	CCamDoc::SetNextTemplateToUse(DocOps::GetDefaultAnimationTemplate());

PORTNOTETRACE("other", "FileNewAnimationAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	AfxGetApp().OnFileNew();
#endif

	CCamDoc::EnableRemoveUntouchedDocs();		// Next idle event will try ro get rid of 
												// the auto-created startup document
}

/********************************************************************************************

>	void FileNewTemplateAction(INT32 iNumberOfTemplate) 

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	21/10/97
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	Opens the specified template
	Errors:		-
	SeeAlso:	MenuCmds

********************************************************************************************/

void FileNewTemplateAction(INT32 iNumberOfTemplate) 
{               
PORTNOTETRACE("other", "FileNewTemplateAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	//First we must find the name of the template to use

	//So search through the templates directory
	String_256 strSearchFilename(_R(IDS_NEWTEMPLATES_DEFAULTTEMPLATEEXTENSION));

	//First find the default template path
	Application* pApplication=GetApplication();

	PathName pathTemplates=pApplication->GetTemplatesPath();
	
	pathTemplates.SetFileNameAndType(strSearchFilename);

	//And search the path for xar files that are
	//NOT the default animation or drawing templates
	String_256 strTemplates=pathTemplates.GetPath(FALSE);

	String_256 strPathOfFile;

	if (FileUtil::StartFindingFiles(&strTemplates))
	{
		String_256 strNameOfFile;
		PathName pathOfFile=pathTemplates;

		String_256 strPathOfDrawingTemplate=DocOps::GetDefaultDrawingTemplate().GetPath(FALSE);
		String_256 strPathOfAnimationTemplate=DocOps::GetDefaultAnimationTemplate().GetPath(FALSE);
		
		for (INT32 i=0; i<iNumberOfTemplate; i++)
		{
			do
			{
				if (!FileUtil::FindNextFile(&strNameOfFile))
				{
					//We failed to find a template. So remove this
					//item from the menu.
					strNameOfFile="";
				}

				pathOfFile.SetFileNameAndType(strNameOfFile);
				strPathOfFile=pathOfFile.GetPath(FALSE);
			}
			while (strPathOfFile.CompareTo(strPathOfDrawingTemplate, FALSE)==0 ||
				strPathOfFile.CompareTo(strPathOfAnimationTemplate, FALSE)==0);
		}

		FileUtil::StopFindingFiles();
	}

	pathTemplates.SetFileNameAndType(strPathOfFile);

	CCamDoc::SetNextTemplateToUse(pathTemplates);

	AfxGetApp().OnFileNew();

	CCamDoc::EnableRemoveUntouchedDocs();		// Next idle event will try ro get rid of 
												// the auto-created startup document
#endif
}


 
/********************************************************************************************

>	void FileOpenAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs File Open menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/

void FileOpenAction() 
{
	// OnFileOpen needs an event, but doesn't use it
	wxCommandEvent		event;
	AfxGetApp().GetDocumentManager()->OnFileOpen( event );
	CCamDoc::EnableRemoveUntouchedDocs();		// Next idle event will try ro get rid of 
												// the auto-created startup document
}
 
/********************************************************************************************

>	void FileCloseAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs File Close menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The MDIGetActive() function is a member func-
	tion of the CMDIFrameWnd class and is used to get the currently active child window. 
	From the Child window the GetActiveDocument() function will obtain the currently active
	document. The OnFileClose() function is then applied to the currently active document 
	which is incidently cast to a Camelot Document before this call made.
********************************************************************************************/

void FileCloseAction() 
{               
 	// CGS:  we need to clear out all intermediate blend steps ....
	// NOTE:  this clears out all 'built-up' intermediate data
	// it clears out the becomea stuff

	NodeGroup::KillAllBlendBecomeAConsLists ();

	// CGS:  these pointers MUST be reset! ....
		
	BlendRecordHandler::SetLastInsertedNodeBlender (NULL);
	BlendRecordHandler::SetLastInsertedNodeBlend (NULL);
	BlendRecordHandler::SetLastInsertedNodeBlendPath (NULL);
	
	// OnFileClose needs an event, but doesn't use it
	wxCommandEvent		event;
	AfxGetApp().GetDocumentManager()->OnFileClose( event );
}
 
/********************************************************************************************

>	void FileSaveAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs File Save menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The MDIGetActive() function is a member func-
	tion of the CMDIFrameWnd class and is used to get the currently active child window. 
	From the Child window the GetActiveDocument() function will obtain the currently active
	document. The OnFileSave() function is then applied to the currently active document 
	which is incidently cast to a Camelot Document before this call made.
********************************************************************************************/

void FileSaveAction() 
{               
#if 0
 	((CCamDoc *)											
 		(((CMDIFrameWnd *)                                      
 			((AfxGetApp())->m_pMainWnd))->MDIGetActive()   	//Get Active Child Window
 					)->GetActiveDocument()                  	//Get Active Document
 						)->OnFileSave();                   			//Save Active Document
#endif
	wxCommandEvent		event;
	AfxGetApp().GetDocumentManager()->OnFileSave( event );
}
 
/********************************************************************************************

>	void FileSaveAsAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs File SaveAs menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The MDIGetActive() function is a member func-
	tion of the CMDIFrameWnd class and is used to get the currently active child window. 
	From the Child window the GetActiveDocument() function will obtain the currently active
	document. The OnFileSaveAs() function is then applied to the currently active document 
	which is incidently cast to a Camelot Document before this call made.
********************************************************************************************/

void FileSaveAsAction() 
{               
PORTNOTETRACE("other", "FileSaveAsAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CCamDoc *)											
 		(((CMDIFrameWnd *)                                      
 			((AfxGetApp())->m_pMainWnd))->MDIGetActive()   	//Get Active Child Window
 					)->GetActiveDocument()                  	//Get Active Document
 						)->OnFileSaveAs();                   		//SaveAs Active Document
#endif
}


/********************************************************************************************

>	void FileSaveAllAction()

	Author:		Rik_Heywood (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/7/95
	Purpose:	Performs the File Save All Action in a Kernel / oil compliant way

********************************************************************************************/

void FileSaveAllAction()
{
	// We do not want to call our version of this function as for some reason
	// it also shuts down the dialog manager...
PORTNOTETRACE("other", "FileSaveAllAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	((CCamApp*)AfxGetApp())->RealSaveAll();
#endif
}


/********************************************************************************************

>	void PrintSetupAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Printer Setup menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
void PrintSetupAction() 
{               
PORTNOTETRACE("other", "PrintSetupAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	((CCamApp*) AfxGetApp())->OnFilePrintSetup();
#endif
}
#endif //webster
/********************************************************************************************

>	void PrintAction()

	Author:		Andy_Pennell (Xara Group Ltd) <camelotdev@xara.com>
	Created:	16/7/93
	Inputs:		None
	Outputs:	void for handled or not
	Returns:	None
	Purpose:	Stop MFC menu items from doing things that don't work (e.g. Print). For
				now calls the Print operation (which ENSURE's).
	Errors:		None

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The MDIGetActive() function is a member func-
	tion of the CMDIFrameWnd class and is used to get the currently active child window. 
	From the Child window the GetActiveView() function will obtain the currently active
	view. The OnFilePrint() function is then applied to the currently active view 
	which is incidently cast to a Camelot View before this call made.
********************************************************************************************/
//	WEBSTER-ranbirr-12/11/96
#ifndef WEBSTER
void PrintAction() 
{               
#if !defined(STANDALONE) && !defined(EXCLUDE_FROM_XARALX)
/*
 	((CCamView *)											
 		(((CMDIFrameWnd *)                                      
 			((AfxGetApp())->m_pMainWnd))->MDIGetActive()   	//Get Active Child Window
 					)->GetActiveView()                  		//Get Active Document
 						)->OnFilePrint();                   		//Print Active Document
*/

	CWinApp* pApp = AfxGetApp();
	if (pApp != NULL)
	{
		CMDIFrameWnd* pWin = (CMDIFrameWnd*) (pApp->m_pMainWnd);
		if (pWin != NULL)
		{
			CMDIChildWnd* pChildWin = pWin->MDIGetActive();
			if (pChildWin != NULL)
			{
				CCamView* pCCamView = (CCamView*) (pChildWin->GetActiveView());
				if (pCCamView != NULL)
					pCCamView->OnFilePrint();
			}
		}
	}

#endif
}
#endif //webster
/********************************************************************************************

>	void PrintPreviewAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs File Print Preview menu function on the File menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The MDIGetActive() function is a member func-
	tion of the CMDIFrameWnd class and is used to get the currently active child window. 
	From the Child window the GetActiveView() function will obtain the currently active
	view. The OnFilePrintPreview() function is then applied to the currently active view 
	which is incidently cast to a Camelot View before this call made.
********************************************************************************************/

void PrintPreviewAction() 
{               
PORTNOTETRACE("other", "PrintPreviewAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CCamView *)											
 		(((CMDIFrameWnd *)                                      
 			((AfxGetApp())->m_pMainWnd))->MDIGetActive()   	//Get Active Child Window
 					)->GetActiveView()                  		//Get Active Document
 						)->OnFilePrintPreview();                   	//Print Preview Doc
#endif
}
 
/********************************************************************************************

>	void WindowNewAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs New Window menu function on the Window menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The OnWindowNew() function is then applied to 
	the mainframe window of the currently active application.
********************************************************************************************/

void WindowNewAction() 
{               
PORTNOTETRACE("other", "WindowNewAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnWindowNew();
#endif
}

/********************************************************************************************

>	void WindowArrangeAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Window menu function Arrange.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void WindowArrangeAction() 
{               
PORTNOTETRACE("other", "WindowArrangeAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnMDIWindowCmd(_R(ID_WINDOW_ARRANGE));
#endif
}

/********************************************************************************************

>	void WindowCascadeAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Window menu function Cascade.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void WindowCascadeAction() 
{               
PORTNOTETRACE("other", "WindowCascadeAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnMDIWindowCmd(_R(ID_WINDOW_CASCADE));
#endif
}

/********************************************************************************************

>	void WindowTileHorzAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Window menu function Tile Horizontal.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void WindowTileHorzAction() 
{               
PORTNOTETRACE("other", "WindowTileHorzAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnMDIWindowCmd(_R(ID_WINDOW_TILE_HORZ));
#endif
}

/********************************************************************************************

>	void WindowTileVertAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Window menu function Tile Verticle.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void WindowTileVertAction() 
{               
PORTNOTETRACE("other", "WindowTileVertAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
 	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnMDIWindowCmd(_R(ID_WINDOW_TILE_VERT));
#endif
}

/********************************************************************************************

>	OpState WindowCmdState()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the window menu options.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState WindowCmdState()
{
PORTNOTETRACE("other", "WindowCmdState does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
    // Get Active Child Window                                                 
    if (((CMDIFrameWnd *) (AfxGetApp())->m_pMainWnd)->MDIGetActive() != NULL)                                               
#endif
		return OpState( FALSE, FALSE );					// not ticked, not greyed
#if !defined(EXCLUDE_FROM_XARALX)
	else
	 	return OpState( FALSE, TRUE );					// not ticked, greyed
#endif
} 

/********************************************************************************************

>	void HelpIndexAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Help Index menu function on the Help menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/

void HelpIndexAction() 
{
PORTNOTETRACE("other", "HelpIndexAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
#if (_MFC_VER >= 0x250)
	GetMainFrame()->OnHelpIndex();
#else
	((CCamApp*) AfxGetApp())->OnHelpIndex();
#endif
#endif
}


 
/********************************************************************************************

>	void HelpUsingAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	8/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs Help Using menu function on the Help menu.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object.This
	is used cast to a Camelot Application object so that camelot the camelot menu functions 
	can be used.
********************************************************************************************/

void HelpUsingAction() 
{               
PORTNOTETRACE("other", "HelpUsingAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
#if (_MFC_VER >= 0x250)
	GetMainFrame()->OnHelpUsing();
#else
	((CCamApp*) AfxGetApp())->OnHelpUsing();
#endif
#endif
}



void HelpToolsAction() 
{               
	HelpUsingTools();
}



void HelpGalleriesAction()
{
	HelpUsingGalleries();
}



void HelpDemosAction()
{
	HelpOnlineDemos();
}



void HelpTechSupportAction()
{
	HelpTechnicalSupport();
}


#ifdef STANDALONE
/********************************************************************************************

>	void HelpSpecAction(); 	

	Author:		Will_Cowling (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/5/95
	Purpose:	Performs Help Spec menu function on the Help menu.
	SeeAlso:	MenuCmds

********************************************************************************************/

void HelpSpecAction() 
{
	ShowHelpSpec();
}
#endif

 
 
/********************************************************************************************

>	void ViewToolBarAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to update ToolBar.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The OnBarCheck() function is then applied to 
	the mainframe window of the currently active application.
********************************************************************************************/

void ViewToolBarAction() 
{
PORTNOTETRACE("other", "ViewToolBarAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	((CMainFrame*)((AfxGetApp())->m_pMainWnd))->OnBarCheck(_R(ID_VIEW_TOOLBAR));
#endif
}

/********************************************************************************************

>	void ViewStatusBarAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to update StatusBar.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/
/*
Technical Notes:
	The AfxGetApp() function is used to obtain the currently active application object. The 
	m_pMainWnd object is a member variable of a CWinApp class which contains the main frame
	window of the current application object. The OnBarCheck() function is then applied to 
	the mainframe window of the currently active application.
********************************************************************************************/

void ViewStatusBarAction() 
{
PORTNOTETRACE("other", "ViewStatusBarAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	GetMainFrame()->ShowStatusBar(!GetMainFrame()->IsStatusBarVisible());
#endif
}

/********************************************************************************************

>	void ViewRulersAction(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to update Rulers.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void ViewRulersAction() 
{
PORTNOTETRACE("other", "ViewRulersAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	// Get the currently selected view pointer. (can be NULL if no documents!)
	DocView *pView = DocView::GetSelected();
	
	if (pView)
	{
		BOOL NewState = ! pView->AreRulersVisible();
		pView->ShowViewRulers(NewState);
		ScreenCamView::SetDefaultRulersState(NewState);
	}
#endif	
}
/********************************************************************************************

>	OpState ViewToolBarState()

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the ToolBar menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewToolBarState()
{
PORTNOTETRACE("other", "ViewToolBarState does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	CWnd* pBar = ((CMainFrame*)((AfxGetApp())->m_pMainWnd)
									)->GetDescendantWindow(_R(AFX_IDW_TOOLBAR));
	
	if ((pBar != NULL) && ((pBar->GetStyle() & WS_VISIBLE) != 0))
#endif
		 return OpState( TRUE, FALSE );					// not ticked, not greyed
#if !defined(EXCLUDE_FROM_XARALX)
	else
	 	return OpState( FALSE, FALSE );					// ticked, not greyed
#endif
} 

/********************************************************************************************

>	OpState ViewStatusBarState(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the ToolBar menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewStatusBarState()
{
PORTNOTETRACE("other", "ViewStatusBarState does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	if(GetMainFrame()->IsStatusBarVisible())
#endif
		return OpState( TRUE, FALSE );				// not ticked, not greyed
#if !defined(EXCLUDE_FROM_XARALX)
	else  
		return OpState( FALSE, FALSE );					// ticked, not greyed
#endif
}

/********************************************************************************************

>	OpState ViewColourBarState(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/94
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the ColourBar menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewColourBarState()
{
PORTNOTETRACE("other", "ViewColourBarState does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	if(GetMainFrame()->IsColourBarVisible())
#endif
		return OpState( TRUE, FALSE );				// not ticked, not greyed
#if !defined(EXCLUDE_FROM_XARALX)
	else
	 	return OpState( FALSE, FALSE );					// ticked, not greyed
#endif	
}

/********************************************************************************************

>	OpState ViewRulersState(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/94
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the Rulers menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewRulersState()
{
	// Get the currently selected view pointer. (can be NULL if no documents!)
	DocView *pView = DocView::GetSelected();
	if (pView == NULL)
		return OpState( FALSE, TRUE );				// not ticked, greyed;

	if(pView->AreRulersVisible())
		 return OpState( TRUE, FALSE );				// ticked, not greyed
	else
	 	return OpState( FALSE, FALSE );				// not ticked, not greyed
	
}

/********************************************************************************************

>	OpState ViewFullScreenState(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/94
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the FullScreen menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewFullScreenState()
{			
PORTNOTETRACE("other", "ViewFullScreenState does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	if(GetMainFrame()->IsFullScreenMode())
#endif
		return OpState( TRUE, FALSE );				// not ticked, not greyed
#if !defined(EXCLUDE_FROM_XARALX)
	else
	 	return OpState( FALSE, FALSE );					// ticked, not greyed
#endif	
}

/********************************************************************************************

>	OpState ViewScrollBarsState(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	7/10/94
	Outputs:	None
	Returns:	None
	Purpose:	Updates the state of the ScrollBars menu option.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

OpState ViewScrollBarsState()
{			
	// Get the currently selected view pointer. (can be NULL if no documents!)
	DocView *pView = DocView::GetSelected();
	if (pView == NULL)
		return OpState( FALSE, TRUE );				// not ticked, greyed;

	if(pView->AreScrollersVisible())
		 return OpState( TRUE, FALSE );				// ticked, not greyed
	else
	 	return OpState( FALSE, FALSE );				// not ticked, not greyed
	
	/* OLD Global version
	if(GetMainFrame()->AreScrollBarsVisible())
		 return OpState( TRUE, FALSE );				// not ticked, not greyed
	else  
	 	return OpState( FALSE, FALSE );					// ticked, not greyed
	*/
}

/********************************************************************************************

>	void ViewColourBarAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to update Colour Bar.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void ViewColourBarAction() 
{
PORTNOTETRACE("other", "ViewColourBarAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	GetMainFrame()->ShowColourBar(!GetMainFrame()->IsColourBarVisible());
#endif	
}

/********************************************************************************************

>	void ViewScrollBarsAction(); 	

	Author:		Mario_Shamtani (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/7/93
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to update Scroll Bars.
	Errors:		None
	SeeAlso:	MenuCmds
	SeeAlso:	SetupDefaultMenu()
	SeeAlso:	SetupSharedMenu()

********************************************************************************************/

void ViewScrollBarsAction() 
{
PORTNOTETRACE("other", "ViewScrollBarsAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	// Get the currently selected view pointer. (can be NULL if no documents!)
	DocView *pView = DocView::GetSelected();
	if (pView)
	{
		BOOL NewState = ! pView->AreScrollersVisible();
		pView->ShowViewScrollers(NewState);
		ScreenCamView::SetDefaultScrollersState(NewState);
	}

	// OLD Global version			
	//  GetMainFrame()->ShowScrollBars(!GetMainFrame()->AreScrollBarsVisible());
#endif
}


/********************************************************************************************

>	void ViewFullScreenAction(); 	

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/10/94
	Inputs:		None
	Outputs:	None
	Returns:	None
	Purpose:	Performs View menu function to Toggle Full Screen mode.
				Full Screen Mode is a bit misleading.. this function actually toggles mode
				by writing/loading either clean.con or normal.con files - all bars except the infobar
				are destroyed and recreated in there new state after the load.The Infobar is a 
				special case this is just moved after the load.  
	Errors:		None
	SeeAlso:	MenuCmds

********************************************************************************************/

void ViewFullScreenAction() 
{
PORTNOTETRACE("other", "ViewFullScreenAction does nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	BOOL NoError = TRUE;
	// lock the window to avoid untidy layout recalcs
	::LockWindowUpdate(GetMainFrame()->GetSafeHwnd());
	
	// tell the mainframe we are changing modes - this prevents
	// some unnecessary work
	GetMainFrame()->SetChangingMode(TRUE);

	// save current bars setup in clean/normal ini file
	if(GetMainFrame()->IsFullScreenMode())
		NoError = DialogBarOp::WriteNamedBars("clean");
	else
		NoError = DialogBarOp::WriteNamedBars("normal");

	if(!NoError)
		InformError();
	// kill all bars ( except infobar at the mo..)
	BROADCAST_TO_CLASS(DialogMsg(NULL, DIM_BAR_DEATH, NULL ),DialogBarOp);
	
	// hide the info bar
	InformationBarOp::SetVisibility(FALSE,TRUE);
	
	// load clean/normal bars ini file
	if(GetMainFrame()->IsFullScreenMode())
		DialogBarOp::LoadNamedBars("normal");
	else
		DialogBarOp::LoadNamedBars("clean");
	
	// force the info bar to the correct visible state
	InformationBarOp::SetVisibility(InformationBarOp::IsVisible(),TRUE);
	
	// All clear to Mainframe
	GetMainFrame()->SetChangingMode(FALSE);
	
	// Make sure everything is positioned correctly
	GetMainFrame()->RecalcLayout();
	GetMainFrame()->RelocateToolbar ();
	
	// and unlock and show the window
	::LockWindowUpdate(NULL);

	// Update all button controls that invoke this Op
	OpDescriptor* pOpDesc = OpDescriptor::FindOpDescriptor(OPTOKEN_VIEWFULLSCREEN);
	if (pOpDesc!=NULL)
	{
		// Found the opdescriptor. Now find all the gadgets associated with it
		List Gadgets;
		if (pOpDesc->BuildGadgetList(&Gadgets))
		{
			// Found some. Set the controls accordingly
			GadgetListItem* pGadgetItem = (GadgetListItem*) Gadgets.GetHead();

			while (pGadgetItem != NULL)
			{
				// Set the gadget
				pGadgetItem->pDialogBarOp->SetBoolGadgetSelected(pGadgetItem->gidGadgetID,
																	GetMainFrame()->IsFullScreenMode());
				// Find the next gadget
				pGadgetItem = (GadgetListItem*) Gadgets.GetNext(pGadgetItem);
			}
	
			// Clean out the list
			Gadgets.DeleteAll();
		}
	}
#endif
}


/*********************************************************************************************************************
/// Website related help items
***********************************************************************************************************************/


//	WEBSTER-ranbirr-12/11/96
//#ifdef WEBSTER


/*********************************************************************************************************************
	void HelpXaraForumAction() 

	Author:		Alex
	Created:	19/02/2004
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to XaraX's Forum Page (e.g. Talkgraphics)
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

***********************************************************************************************************************/

void HelpXaraForumAction()
{
PORTNOTETRACE("other","HelpXaraPurchasePage - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Opens the default Browser on XaraX's Forum Page
	String_256 lpURL(_R(IDS_URL_FORUM));
	HINSTANCE hChild = ShellExecute(HWND_DESKTOP, "open", (TCHAR*)lpURL, NULL, NULL, SW_SHOW);

	// If the function (ShellExecute()) fails, then an error value that is less than or equal to 32 is returned. 
	if ((INT32)hChild <= THIRTY_TWO )
	{
		switch ( (INT32)hChild )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
		}
	}	
#endif
}


/*********************************************************************************************************************
	void HelpWebsterHomePage() 

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to Webster's Home Page.
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

***********************************************************************************************************************/

void HelpWebsterHomePage()
{
PORTNOTETRACE("other","HelpXaraPurchasePage - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Opens the default Browser on Webster's Home Page
	String_256 lpURL(_R(IDS_URL_PRODUCT));
	HINSTANCE hChild = ShellExecute(HWND_DESKTOP, "open", (TCHAR*)lpURL, NULL, NULL ,SW_SHOW);

	// If the function (ShellExecute()) fails, then an error value that is less than or equal to 32 is returned. 
	if ( (INT32)hChild <= THIRTY_TWO )
	{
		switch ( (INT32)hChild )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
		}
	}
#endif
}
/*********************************************************************************************************************
	void HelpXaraHomePage()

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to Xara's HomePage Page.
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

***********************************************************************************************************************/
void HelpXaraHomePage()
{
PORTNOTETRACE("other","HelpXaraPurchasePage - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Opens the default Browser on Xara's Home Page
	String_256 lpURL(_R(IDS_URL_XARASITE));
	HINSTANCE hChild = ShellExecute(HWND_DESKTOP, "open", (TCHAR*)lpURL, NULL, NULL ,SW_SHOW);

	// If the function (ShellExecute()) fails, then an error value that is less than or equal to 32 is returned. 
	if ( (INT32)hChild <= THIRTY_TWO )
	{
		switch ( (INT32)hChild )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
		}
	}
#endif
}

//#endif //webster

/*********************************************************************************************************************
	BOOL IsCDROMOn() 

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/97
	Inputs:		-
	Outputs:	-
	Returns		True if this is a CD version of Webster, FALSE if it is a download version.
	Purpose:	To discover whether the installed version of Webster is a CD or DownLoad version.
	Errors		-
	See Also	-

***********************************************************************************************************************/
BOOL IsCDROMOn() 
{
PORTNOTETRACE("other","IsCDROMOn - do nothing");
#if !defined(EXCLUDE_FROM_XARALX)
	BOOL bSetting;
	HKEY arhKeys[3];
	DWORD dwBoolSize = sizeof(BOOL);
	DWORD dwDisposition;

	BOOL bResult = 	((RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS, &arhKeys[0]) == ERROR_SUCCESS) &&

	(RegCreateKeyEx(arhKeys[0], PRODUCT_MANUFACTURER,  0, NULL, REG_OPTION_NON_VOLATILE,  KEY_ALL_ACCESS, NULL, &arhKeys[1], &dwDisposition) == ERROR_SUCCESS) &&

	(RegCreateKeyEx(arhKeys[1], PRODUCT_WEBLINKNAME,  0, NULL, REG_OPTION_NON_VOLATILE,  KEY_ALL_ACCESS, NULL, &arhKeys[2], &dwDisposition) == ERROR_SUCCESS) &&

	(RegQueryValueEx(arhKeys[2],	"Search CDROM",	NULL, NULL,  (LPBYTE) &bSetting,	&dwBoolSize) == ERROR_SUCCESS));

//	ERROR2IF(!bResult, "Registry read error");

	// If We failed to read from the registry, Untick the Menu item.
	if(!bResult)
		bSetting = bResult;

	for (INT32 i = 2; i >= 0; i--) 
	      RegCloseKey(arhKeys[i]);

	return bSetting;
#else
	return FALSE;
#endif
}

/*********************************************************************************************************************
	void WebsterDemos()

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	20/01/97
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to Webster's Movies Demos Page.
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

************************************************************************************************************************/
void WebsterDemos()
{
	// Opens the default Browser on Xara's Home Page
	const String_256 cmd = TEXT(PRODUCT_WEBLINKEXENAME " movies/index.htm");
	InvokeWeblink(cmd);
}

/*********************************************************************************************************************
	void WebsterHelpPages()

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	17/02/97
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to Webster's Help Pages
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

************************************************************************************************************************/
void WebsterHelpPages()
{
PORTNOTETRACE("other","HelpXaraPurchasePage - do nothing");
#ifndef EXCLUDE_FROM_XARALX
// Old weblink way of opening browser onto hints and tips page - doesn't seem to work
//	// Opens the default Browser on Xara's Home Page
//	const String_256 cmd = TEXT(PRODUCT_WEBLINKEXENAME " hints/index.htm");
//	InvokeWeblink(cmd);

	// Opens the default Browser on Xara Xone we pages
	String_256 lpURL(_R(IDS_URL_TUTORIALS));
	HINSTANCE hChild = ShellExecute(HWND_DESKTOP, "open", (TCHAR*)lpURL, NULL, NULL ,SW_SHOW);

	// If the function (ShellExecute()) fails, then an error value that is less than or equal to 32 is returned. 
	if ( (INT32)hChild <= THIRTY_TWO )
	{
		switch ( (INT32)hChild )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
		}
	}
#endif
}

/*********************************************************************************************************************
	void HelpXaraPurchasePage()

	Author:		Priestley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	28/09/2000
	Inputs:		-
	Outputs:	-
	Returns		-
	Purpose:	Provides access from a help menu to Xara's Purchase Page.
	Errors		If the browser could not be opened, an Error message box is diplayed.
	See Also	-

***********************************************************************************************************************/
void HelpXaraPurchasePage()
{
PORTNOTETRACE("other","HelpXaraPurchasePage - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	// Opens the default Browser on Xara's Purchase Page
	String_256 lpURL(_R(IDS_URL_PURCHASE));
	HINSTANCE hChild = ShellExecute(HWND_DESKTOP, "open", (TCHAR*)lpURL, NULL, NULL ,SW_SHOW);

	// If the function (ShellExecute()) fails, then an error value that is less than or equal to 32 is returned. 
	if ( (INT32)hChild <= THIRTY_TWO )
	{
		switch ( (INT32)hChild )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK)/*,_R(IDS_HELP)*/);
			}
			break;
		}
	}
#endif
}


/*********************************************************************************************************************

>	BOOL InvokeWeblink(const String_256& command)

	Author:		Neville_Humphrys (Xara Group Ltd) <camelotdev@xara.com> from Ranbir code
	Created:	16/09/97
	Inputs:		-
	Returns		True if worked ok, False otherwise
	Purpose:	Allows a command to be sent to Weblink. This enables the default browser to be fired up
				to display the specified URL or file. If there is a browser open then this will be used
				instead rather than firing up a new instance.
	Errors		If the command had a problem, an Error message box is diplayed.
	See Also	-

************************************************************************************************************************/

BOOL InvokeWeblink(const String_256& command)
{
PORTNOTETRACE("other","InvokeWeblink - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	//TCHAR* pCmd = (TCHAR*)command;
	UINT32 Error = WinExec(command, SW_SHOW);

	// If the function (WebExec()) fails, then an error value that is less than or equal to 32 is returned. 
	if ( Error <= THIRTY_TWO )
	{
		switch ( Error )
		{
			case	ERROR_FILE_NOT_FOUND:
			case	ERROR_PATH_NOT_FOUND: 
			case	SE_ERR_ACCESSDENIED:
			case	SE_ERR_ASSOCINCOMPLETE:
			{
				InformError(_R(IDS_NO_WEB_UTILITY),_R(IDS_OK));
			}
			break;
			default:
			{
				InformError(_R(IDS_NO_WEB_PAGE),_R(IDS_OK));
			}
			break;
		}
		
		return FALSE;
	}
#endif
	
	return TRUE;
}


/*********************************************************************************************************************
	void SetWebsterReg(BOOL pcData) 

	Author:		Ranbir_Rana (Xara Group Ltd) <camelotdev@xara.com>
	Created:	27/01/97
	Inputs:		pcdata - To set the state of the Flag
	Outputs:	-
	Returns		-
	Purpose:	To set the registry flag for Webster.
				i.e. Is the Help to be obtained from the CD or from the Net.
	Errors		
	See Also	-

***********************************************************************************************************************/
//#ifdef WEBSTERCD
void SetWebsterReg(BOOL pcData) 
{
PORTNOTETRACE("other","SetWebsterReg - do nothing");
#ifndef EXCLUDE_FROM_XARALX
	HKEY arhKeys[3];
	DWORD dwBoolSize = sizeof(BOOL);
	DWORD dwDisposition;

		BOOL bResult = ((RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, KEY_ALL_ACCESS, &arhKeys[0]) == ERROR_SUCCESS) &&

		(RegCreateKeyEx(arhKeys[0], PRODUCT_MANUFACTURER,  0, NULL, REG_OPTION_NON_VOLATILE,  KEY_ALL_ACCESS, NULL, &arhKeys[1], &dwDisposition) == ERROR_SUCCESS) &&

		(RegCreateKeyEx(arhKeys[1], PRODUCT_WEBLINKNAME,  0, NULL, REG_OPTION_NON_VOLATILE,  KEY_ALL_ACCESS, NULL, &arhKeys[2], &dwDisposition) == ERROR_SUCCESS) &&

		(RegSetValueEx (arhKeys[2],	"Search CDROM",	NULL, REG_DWORD,  (LPBYTE) &pcData,	dwBoolSize) == ERROR_SUCCESS));

	for (INT32 i = 2; i >= 0; i--) 
	      RegCloseKey(arhKeys[i]);
#endif
}
//#endif
