#include "usvn.h"

SysConsole::SysConsole()
{
	CtrlLayoutExit(*this, "System Console");
	list.NoHeader().NoGrid().NoCursor().AddColumn();
	font = Courier(Ctrl::VertLayoutZoom(12));
	list.SetLineCy(font.Info().GetHeight());
}

void SysConsole::AddResult(const String& out)
{
	DUMP(out);
	Vector<String> h = Split(out, '\n');
	for(int i = 0; i < h.GetCount(); i++) {
		String s = "    " + h[i];
		list.Add(AttrText(s).SetFont(font), s);
	}
	list.GoEnd();
}

int SysConsole::System(const char *cmd)
{
	DLOG("=== System =======================================");
	DDUMP(cmd);
	if(!IsOpen())
		Open();
	list.Add(AttrText(cmd).SetFont(font().Bold()).Ink(LtBlue));
	int ii = list.GetCount();
	LocalProcess p;
	if(!p.Start(cmd))
		return -1;
	String out;
	while(p.IsRunning()) {
		DLOG("Get1");
		out.Cat(p.Get());
		int lf = out.ReverseFind('\n');
		if(lf >= 0) {
			AddResult(out.Mid(0, lf + 1));
			out = out.Mid(lf + 1);
		}
		ProcessEvents();
		Sleep(1); // p.Wait would be much better here!
	}
	DLOG("Get2");
	out.Cat(p.Get());
	AddResult(out);
	ProcessEvents();
	int code = p.GetExitCode();
	if(code)
		while(ii < list.GetCount()) {
			list.Set(ii, 0, AttrText(list.Get(ii, 1)).SetFont(font).Ink(LtRed));
			ii++;
		}
	return code;
}
