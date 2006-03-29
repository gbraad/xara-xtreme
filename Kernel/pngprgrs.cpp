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

// PNG progress bar code
// Jonathan Payne 8/2000

#include "camtypes.h"
#include "png.h"
#include "pngprgrs.h"
#include "progress.h"		// For hourglass stuff

// An implement to match the Declare in the .h file.
CC_IMPLEMENT_MEMDUMP(PNGProgressBar, CC_CLASS_MEMDUMP)

/********************************************************************************************

>	PNGProgressBar::PNGProgressBar(String_64 *ProgressString, bool new_interlaced, UINT32 new_height)

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/2000
	Inputs:		ProgressString
	Outputs:	Progress bar on screen
	Returns:	void
	Purpose:	Constructor.  Sets show_progress_bar.  If ProgressString != NULL, starts
				prorgress bar.
	Scope:		Public

********************************************************************************************/

PNGProgressBar::PNGProgressBar(String_64 *ProgressString, bool new_interlaced, UINT32 new_height)
{
	interlaced = new_interlaced;
	height = new_height;

	if (ProgressString != NULL)
	{
		show_progress_bar = true;
		if (interlaced)
		// An interlaced image
		{
			// PNG interlaced files always have 7 passes so use 7 as
			// final value for status bar
			BeginSlowJob(8, FALSE, ProgressString);

			// Next update the status bar at pass 0
			next_update = 0;
		}
		else
		// A non-interlaced image
		{
			BeginSlowJob(height, FALSE, ProgressString);
			
			// Update the status bar on row 0
			next_update = 0;
		}
	}
	else
	{
		show_progress_bar = false;
	}
}

/********************************************************************************************

>	PNGProgressBar::~PNGProgressBar()

	Author:		Jonathan_Payne (Xara Group Ltd) <camelotdev@xara.com>
	Created:	30/8/2000
	Outputs:	Removes progress bar from screen
	Returns:	void
	Purpose:	Constructor.  Sets show_progress_bar.  If ProgressString != NULL, starts
				prorgress bar.
	Scope:		Public

********************************************************************************************/

PNGProgressBar::~PNGProgressBar()
{
	// If started, then stop then progress bar
	if (show_progress_bar)
		EndSlowJob();
}

void PNGProgressBar::UpdateCallback(png_structp png_ptr, png_uint_32 row_number, INT32 pass)
{
	if (show_progress_bar)
	{
		if (interlaced)
		// Interlaced image
		{
			if (pass + 1 >= next_update)
				ContinueSlowJob(pass + 1);
		}
		else
		// Non-interlaced image
		{
			if ((INT32)row_number >= next_update)
				ContinueSlowJob(row_number);
		}
	}
}
