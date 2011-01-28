#ifndef _CtrlMoverTest_CtrlMoverTest_h
#define _CtrlMoverTest_CtrlMoverTest_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <CtrlMoverTest/CtrlMoverTest.lay>
#include <CtrlCore/lay.h>

#include <CtrlMover/CtrlMover.h>

class CtrlMoverTest : public WithCtrlMoverTestLayout<TopWindow> {
public:
	typedef CtrlMoverTest CLASSNAME;
	CtrlMoverTest();

	void VisitCB();
	void ClearCB();
	void EnableCB();
	void DisableCB();

	void ToInfo(const String& s);
	void OnSelect(Ctrl& c, Point p, dword keyflags);
	void OnMissed(Point p, dword keyflags);
	
	CtrlMover hk;
	FrameTop<WithControlLay<ParentCtrl> > ft;
};

#endif

