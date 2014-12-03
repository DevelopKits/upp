#include "CodeEditor.h"

NAMESPACE_UPP

void CodeEditor::InitFindReplace()
{
	findreplace.find.AddButton().SetMonoImage(CtrlImg::smallright()).Tip("Wildcard")
		<<= THISBACK(FindWildcard);
	findreplace.replace.AddButton().SetMonoImage(CtrlImg::smallright()).Tip("Wildcard")
		<<= THISBACK(ReplaceWildcard);
	PutI(findreplace.find);
	PutI(findreplace.replace);
	findreplace.amend <<= THISBACK(Replace);
	findreplace.amend_all <<= THISBACK1(ReplaceAll, false);
	findreplace.amend_rest <<= THISBACK1(ReplaceAll, true);
	findreplace.prev <<= THISBACK(DoFindBack);
	findreplace.replacing = false;
	found = notfoundfw = notfoundbk = foundsel = false;
	persistent_find_replace = false;
	findreplace.find <<= findreplace.wholeword <<= findreplace.wildcards
	                 <<= findreplace.incremental <<= findreplace.regexp
	                 <<= findreplace.ignorecase <<= THISBACK(IncrementalFind);
	ff_start_pos = -1;
}

FindReplaceDlg::FindReplaceDlg()
{
	find.NoUpDownKeys();
	samecase <<= true;
	close.Cancel();
	prev.SetImage(CtrlImg::SmallUp());
	amend.SetImage(CodeEditorImg::Replace());
	amend_all.SetImage(CodeEditorImg::ReplaceAll());
	amend_rest.SetImage(CodeEditorImg::ReplaceRest());
	incremental <<= true;
	mode <<= THISBACK(Sync);
	mode.Hide();
	Sync();
}

void FindReplaceDlg::Sync()
{
	samecase.Enable(ignorecase);
	bool b = !regexp;
	wildcards.Enable(b);
	prev.Enable(b);
	ignorecase.Enable(b);
	wholeword.Enable(b);
	incremental_from_cursor.Enable(IsIncremental());
	b = !mode.IsVisible() || ~mode == 0;
	replace.Enable(b);
	replace_txt.Enable(b);
}

dword CodeEditor::find_next_key = K_F3;
dword CodeEditor::find_prev_key = K_SHIFT_F3;
dword CodeEditor::replace_key = K_CTRL_R;

bool FindReplaceDlg::Key(dword key, int cnt) {
	if(key == K_CTRL_I) {
		if(find.HasFocus()) {
			find <<= itext;
			return true;
		}
		if(replace.HasFocus()) {
			replace <<= itext;
			return true;
		}
	}
	if(key == K_ENTER) {
		next.WhenAction();
		return true;
	}
	if(findarg(key, K_TAB, K_SHIFT_TAB) >= 0 && replace.IsShown()) {
		if(find.HasFocus())
			replace.SetFocus();
		else
			find.SetFocus();
		return true;
	}
	if(key == K_ESCAPE) {
		close.WhenAction();
		return true;
	}
	return TopWindow::Key(key, cnt);
}

void FindReplaceDlg::Setup(bool doreplace)
{
	CtrlLayout(*this);
	close.SetImage(CodeEditorImg::Cancel());
	close.Tip("Close (Esc)");
	close.Normal();
	close.SetLabel("");
	next.SetImage(CtrlImg::SmallDown());
	next.Tip("Find next (" + GetKeyDesc(CodeEditor::find_next_key) + ")");
	next.Normal();
	next.SetLabel("");
	prev.Tip("Find prev (" + GetKeyDesc(CodeEditor::find_prev_key) + ")");
	amend.Tip("Replace (" + GetKeyDesc(CodeEditor::replace_key) + ")");
	amend.Disable();
	info.SetLabel("&Find");
	replacing = doreplace;
	replace.Show(replacing);
	amend.Show(replacing);
	amend_all.Show(replacing);
	amend_rest.Show(replacing);
	Height(doreplace ? GetLayoutSize().cy : replace.GetRect().top);
	SetFrame(TopSeparatorFrame());
	Sync();
}

void CodeEditor::SetFound(int fi, int type, const WString& text)
{
	Found& f = foundwild.At(fi);
	f.type = type;
	f.text = text;
}

int CodeEditor::Match(const wchar *f, const wchar *s, int line, bool we, bool ignorecase, int fi)
{
	const wchar *b = s;
	int n = 0;
	WString ln;
	while(*f) {
		if(*f == WILDANY) {
			f++;
			WString wild;
			for(;;) {
				int nn = Match(f, s, line, we, ignorecase, fi + 1);
				if(nn >= 0) {
					SetFound(fi, WILDANY, wild);
					return int(s - b) + n + nn;
				}
				wild.Cat(*s ? *s : '\n');
				if(!*s++) return -1;
			}
			return -1;
		}
		else
		if(*f == WILDONE) {
			if(!*s) return -1;
			SetFound(fi++, WILDONE, WString(*s, 1));
			s++;
		}
		else
		if(*f == WILDSPACE) {
			const wchar *wb = s;
			if(*s != ' ' && *s != '\t') return -1;
			s++;
			while(*s == ' ' || *s == '\t')
				s++;
			SetFound(fi++, WILDSPACE, WString(wb, s));
		}
		else
		if(*f == WILDNUMBER) {
			const wchar *wb = s;
			if(*s < '0' || *s > '9') return -1;
			s++;
			while(*s >= '0' && *s <= '9')
				s++;
			SetFound(fi++, WILDNUMBER, WString(wb, s));
		}
		else
		if(*f == WILDID) {
			const wchar *wb = s;
			if(!iscib(*s)) return -1;
			s++;
			while(iscidl(*s)) s++;
			SetFound(fi++, WILDID, WString(wb, s));
		}
		else
		if(*f == '\n') {
			if(*s != '\0' || ++line >= GetLineCount()) return -1;
			n += int(s - b) + 1;
			ln = GetWLine(line);
			s = b = ln;
		}
		else {
			if(ignorecase ? ToUpper(*s) != ToUpper(*f) : *s != *f) return -1;
			s++;
		}
		f++;
	}
	return we && iscidl(*s) ? -1 : int(s - b) + n;
}

bool CodeEditor::Find(bool back, bool block)
{
	foundsel = true;
	if(notfoundfw) MoveTextBegin();
	if(notfoundbk) MoveTextEnd();
	foundsel = false;
	int cursor, pos;
	if(found)
		GetSelection(pos, cursor);
	else
		GetSelection(cursor, pos);
	pos = cursor;
	bool b = FindFrom(pos, back, block);
	findreplace.amend.Enable(b);
	return b;
}

bool CodeEditor::RegExpFind(int pos, bool block)
{
	RegExp regex((String)~findreplace.find);
	
	int line = GetLinePos(pos);
	int linecount = GetLineCount();
	String ln = ToUtf8(GetWLine(line).Mid(pos));
	for(;;) {
		if(regex.Match(ln)) {
			for(int i = 0; i < regex.GetCount(); i++)
				SetFound(i, WILDANY, regex.GetString(i).ToWString());
			int off = regex.GetOffset();
			int len = utf8len(~ln + off, regex.GetLength());
			pos = GetPos(line, utf8len(~ln, off) + pos);
			foundtext = GetW(pos, len);
			if(!block) {
				foundsel = true;
				SetSelection(pos, pos + len);
				foundsel = false;
				CenterCursor();
			}
			foundpos = pos;
			foundsize = len;
			found = true;
			return true;
		}
		if(++line >= linecount)
			return false;
		ln = GetUtf8Line(line);
		pos = 0;
	}
}

bool CodeEditor::FindFrom(int pos, bool back, bool block)
{
	notfoundbk = notfoundfw = false;
	if(findreplace.regexp) {
		if(RegExpFind(pos, block))
			return true;
		if(back)
			notfoundbk = true;
		else
			notfoundfw = true;
		return false;
	}
	WString text = ~findreplace.find;
	WString ft;
	const wchar *s = text;
	while(*s) {
		int c = *s++;
		if(c == '\\') {
			c = *s++;
			if(c == '\0') break;
			if(c == 'n')
				ft.Cat('\n');
			else
			if(c == 't')
				ft.Cat('\t');
			else
			if(c >= ' ')
				ft.Cat(c);
		}
		else
		if(c >= ' ') {
			if(findreplace.wildcards)
				ft.Cat(c == '*' ? WILDANY :
					   c == '?' ? WILDONE :
					   c == '%' ? WILDSPACE :
					   c == '#' ? WILDNUMBER :
					   c == '$' ? WILDID :
								  c
				);
			else
				ft.Cat(c);
		}
	}
	bool wb = findreplace.wholeword ? iscidl(*ft) : false;
	bool we = findreplace.wholeword ? iscidl(*ft.Last()) : false;
	if(ft.IsEmpty()) return false;
	foundwild.Clear();
	int line = GetLinePos(pos);
	int linecount = GetLineCount();
	WString ln = GetWLine(line);
	const wchar *l = ln;
	s = l + pos;
	bool ignorecase = findreplace.ignorecase;
	for(;;) {
		for(;;) {
			if(!wb || (s == l || !iscidl(s[-1]))) {
				int n = Match(ft, s, line, we, ignorecase);
				if(n >= 0) {
					int pos = GetPos(line, int(s - l));
					foundtext = GetW(pos, n);
					if(!back || pos + n < cursor) {
						if(!block) {
							foundsel = true;
							SetSelection(pos, pos + n);
							foundsel = false;
							CenterCursor();
						}
						foundpos = pos;
						foundsize = n;
						found = true;
						return true;
					}
				}
			}
			if(back) {
				if(s-- == l) break;
			}
			else
				if(!*s++) break;
		}
		if(back) {
			if(--line < 0) break;
			ln = GetWLine(line);
			l = ln;
			s = ln.End();
		}
		else {
			if(++line >= linecount) break;
			ln = GetWLine(line);
			l = s = ln;
		}
	}
	if(back)
		notfoundbk = true;
	else
		notfoundfw = true;
	return false;
}

void CodeEditor::FindReplaceAddHistory()
{
	if(!IsNull(findreplace.find))
		findreplace.find.AddHistory();
	if(!IsNull(findreplace.replace))
		findreplace.replace.AddHistory();
}

void CodeEditor::NoFindError()
{
	findreplace.find.Error(false);
	findreplace.info.SetLabel("&Find");
}

void CodeEditor::NotFound()
{
	findreplace.find.Error();
	findreplace.info.SetLabel("Not &found");
	if(!findreplace.IsIncremental())
		SetFocus();
	findreplace.amend.Disable();
}

bool CodeEditor::Find(bool back, bool blockreplace, bool replace)
{
	NoFindError();
	if(Find(back, blockreplace)) {
		if(!blockreplace) {
			if(!findreplace.IsOpen())
				OpenNormalFindReplace(replace);
			if(!findreplace.IsIncremental())
				SetFocus();
		}
		return true;
	}
	else {
		NotFound();
		return false;
	}
}

WString CodeEditor::GetWild(int type, int& i)
{
	for(;;) {
		if(i >= foundwild.GetCount()) break;
		Found& f = foundwild[i++];
		if(f.type == type) return f.text;
	}
	for(int j = 0; j < foundwild.GetCount(); j++) {
		Found& f = foundwild[j++];
		if(f.type == type) return f.text;
	}
	return WString();
}

WString CodeEditor::GetReplaceText()
{
	WString rs = ~findreplace.replace;
	bool wildcards = findreplace.wildcards;
	bool samecase = findreplace.ignorecase && findreplace.samecase;

	int anyi = 0, onei = 0, spacei = 0, numberi = 0, idi = 0;
	WString rt;
	const wchar *s = rs;
	while(*s) {
		int c = *s++;
		if(c == '\\') {
			c = *s++;
			if(c == '\0') break;
			if(c == 'n')
				rt.Cat('\n');
			else
			if(c == 't')
				rt.Cat('\t');
			else
			if(c >= ' ')
				rt.Cat(c);
		}
		else
		if(c >= ' ') {
			if(wildcards) {
				WString w;
				if(c == '*')
					w = GetWild(WILDANY, anyi);
				else
				if(c == '?')
					w = GetWild(WILDONE, onei);
				else
				if(c == '%')
					w = GetWild(WILDSPACE, spacei);
				else
				if(c == '#')
					w = GetWild(WILDNUMBER, numberi);
				else
				if(c == '$')
					w = GetWild(WILDID, idi);
				else
				if(c == '@') {
					c = *s++;
					if(c == '\0') break;
					if(c == '@') {
						rt << AsString(replacei).ToWString();
						continue;
					}
					if(c == '#') {
						rt << AsString(replacei + 1).ToWString();
						continue;
					}
					if(c >= '1' && c <= '9') {
						c -= '1';
						w = c < foundwild.GetCount() ? foundwild[c].text : WString();
					}
					else {
						rt.Cat('@');
						if(c >= ' ' && c < 255) rt.Cat(c);
						continue;
					}
				}
				else {
					rt.Cat(c);
					continue;
				}
				if(*s == '+') {
					w = ToUpper(w);
					s++;
				}
				else
				if(*s == '-') {
					w = ToLower(w);
					s++;
				}
				else
				if(*s == '!') {
					w = InitCaps(w);
					s++;
				}
				rt.Cat(w);
			}
			else
				rt.Cat(c);
		}
	}
	if(samecase) {
		if(foundtext.GetCount() && rt.GetCount()) {
			if(IsUpper(foundtext[0]))
				rt.Set(0, ToUpper(rt[0]));
			if(IsLower(foundtext[0]))
				rt.Set(0, ToLower(rt[0]));
		}
		if(foundtext.GetCount() > 1) {
			if(IsUpper(foundtext[1]))
				for(int i = 1; i < rt.GetCount(); i++)
					rt.Set(i, ToUpper(rt[i]));
			if(IsLower(foundtext[1]))
				for(int i = 1; i < rt.GetCount(); i++)
					rt.Set(i, ToLower(rt[i]));
		}
	}
	replacei++;
	return rt;
}

void CodeEditor::Replace()
{
	if(!findreplace.replacing)
		return;
	NextUndo();
	FindReplaceAddHistory();
	if(!found) return;
	if(RemoveSelection()) {
		Paste(GetReplaceText());
		Find(false, false, true);
	}
}

int CodeEditor::BlockReplace()
{
	NextUndo();
	Refresh(); // Setting full-refresh here avoids Pre/Post Remove/Insert costs
	int l, h;
	if(!GetSelection(l, h)) return 0;
	PlaceCaret(l);
	int count = 0;
	foundpos = l;
	Index<int> ln;
	while(FindFrom(foundpos, false, true) && foundpos + foundsize <= h) {
		CachePos(foundpos);
		if(~findreplace.mode == 0) {
			Remove(foundpos, foundsize);
			WString rt = GetReplaceText();
			Insert(foundpos, rt);
			foundpos += rt.GetCount();
			h = h - foundsize + rt.GetCount();
			count++;
		}
		else {
			ln.FindAdd(GetLine(foundpos));
			foundpos += foundsize;
		}
	}
	if(~findreplace.mode != 0) {
		ClearSelection();
		int ll = GetLine(l);
		int lh = GetLine(h);
		if(GetPos(lh) == h)
			lh--;
		bool mm = ~findreplace.mode == 1;
		for(int i = lh; i >= ll; i--) {
			if((ln.Find(i) >= 0) != mm) {
				int pos = GetPos(i);
				int l = GetLineLength(i);
				CachePos(pos);
				Remove(pos, min(l + 1, GetLength() - pos));
				count++;
			}
		}
		SetSelection(GetPos(ll), lh - count + 1 < GetLineCount() ? GetPos(lh - count + 1)
		                                                         : GetLength());
	}
	else
		SetSelection(l, h);
	return count;
}

void CodeEditor::OpenNormalFindReplace0(bool replace)
{
	findreplace.incremental.Enable(GetLength() < 2000000);
	findreplace.Setup(replace);
	findreplace.itext = GetI();
	findreplace.prev.Show();
	findreplace.next <<= THISBACK(DoFind);
	findreplace.close <<= THISBACK(EscapeFindReplace);
	if(!findreplace.IsOpen())
		InsertFrame(FindFrame(sb), findreplace);
	WhenOpenFindReplace();
	findreplace.find.SetFocus();
}

void CodeEditor::OpenNormalFindReplace(bool replace)
{
	OpenNormalFindReplace0(replace);
	if(!findreplace.incremental_from_cursor)
		IncrementalFind();
}

void CodeEditor::FindReplace(bool pick_selection, bool pick_text, bool replace)
{
	if(findreplace.IsOpen())
		CloseFindReplace();

	ff_start_pos = GetCursor();

	replacei = 0;
	WString find_text;
	int find_pos = -1;
	
	findreplace.Setup(replace);
	
	if(pick_text || pick_selection)
	{
		WString s = GetSelection().ToWString();
		if(IsSelection()) {
			if(s.Find('\n') < 0)
				find_text = s;
		}
		else
		if(pick_text) {
			int l, h;
			l = h = GetCursor();
			while(l > 0 && CharFilterCIdent(GetChar(l - 1)))
				l--;
			while(h < GetLength() && CharFilterCIdent(GetChar(h)))
				h++;
			find_text = Get(l, h - l).ToWString();
			find_pos = h;
		}
		if(find_text.GetCount())
			findreplace.find <<= find_text;
	}
	if(IsSelection() && replace) {
		findreplace.itext = GetI();
		SetLayout_BlockReplaceLayout(findreplace);
		findreplace.SetRect(WithBlockReplaceLayout<EmptyClass>::GetLayoutSize());
		findreplace.Title(t_("Replace in selection"));
		findreplace.amend.Hide();
		findreplace.amend_all.Hide();
		findreplace.amend_rest.Hide();
		findreplace.prev.Hide();
		findreplace.next.Ok() <<= findreplace.Breaker(IDOK);
		findreplace.close.Cancel() <<= findreplace.Breaker(IDCANCEL);
		findreplace.close.SetImage(Null);
		findreplace.close.Tip("");
		findreplace.next.SetImage(Null);
		findreplace.next.Tip("");
		findreplace.mode.Show();
		findreplace.mode <<= 0;
		findreplace.Sync();
		if(findreplace.Execute() == IDOK)
			BlockReplace();
		findreplace.mode.Hide();
	}
	else {
		if(find_pos >= 0)
			SetCursor(find_pos);
		OpenNormalFindReplace(replace);
		findreplace.find.SetFocus();
	}
}

void CodeEditor::ReplaceAll(bool rest)
{
	int l, h;
	GetSelection(l, h);
	int c = min(l, h);
	findreplace.mode <<= 0;
	SetSelection(rest * c, GetLength());
	BlockReplace();
	SetCursor(c);
}

void CodeEditor::InsertWildcard(const char *s)
{
	iwc = s;
}

void FindWildcardMenu(Callback1<const char *> cb, Point p, bool tablf, Ctrl *owner, bool regexp)
{
	MenuBar menu;
	if(regexp) {
		menu.Add(t_("One or more spaces"), callback1(cb, " +"));
		menu.Add(t_("One or more any characters"), callback1(cb, ".+"));
		menu.Add(t_("Word"), callback1(cb, "\\w+"));
		menu.Add(t_("Number"), callback1(cb, "\\d+"));
		menu.Add(t_("Any character"), callback1(cb, "."));
		if(tablf) {
			menu.Separator();
			menu.Add(t_("Tab"), callback1(cb, "\\t"));
		}
	}
	else {
		menu.Add(t_("One or more spaces"), callback1(cb, "%"));
		menu.Add(t_("One or more any characters"), callback1(cb, "*"));
		menu.Add(t_("C++ identifier"), callback1(cb, "$"));
		menu.Add(t_("Number"), callback1(cb, "#"));
		menu.Add(t_("Any character"), callback1(cb, "?"));
		if(tablf) {
			menu.Separator();
			menu.Add(t_("Tab"), callback1(cb, "\\t"));
			menu.Add(t_("Line feed"), callback1(cb, "\\n"));
		}
	}
	menu.Execute(owner, p);
}

void CodeEditor::FindWildcard()
{
	int l, h;
	findreplace.find.GetSelection(l, h);
	iwc.Clear();
	FindWildcardMenu(THISBACK(InsertWildcard), findreplace.find.GetPushScreenRect().TopRight(), true,
	                 &findreplace, findreplace.regexp);
	if(iwc.GetCount()) {
		if(!findreplace.regexp)
			findreplace.wildcards = true;
		findreplace.find.SetFocus();
		findreplace.find.SetSelection(l, h);
		findreplace.find.RemoveSelection();
		findreplace.find.Insert(iwc);
	}
}

void CodeEditor::ReplaceWildcard()
{
	MenuBar menu;
	String ptxt;
	if(findreplace.regexp) {
		ptxt = t_("Matched subpattern %d");
	}
	else {
		menu.Add(t_("Matched spaces"), THISBACK1(InsertWildcard, "%"));
		menu.Add(t_("Matched one or more any characters"), THISBACK1(InsertWildcard, "*"));
		menu.Add(t_("Matched C++ identifier"), THISBACK1(InsertWildcard, "$"));
		menu.Add(t_("Matched number"), THISBACK1(InsertWildcard, "#"));
		menu.Add(t_("Matched any character"), THISBACK1(InsertWildcard, "?"));
	}
	menu.Add(t_("0-based replace index"), THISBACK1(InsertWildcard, "0"));
	menu.Add(t_("1-based replace index"), THISBACK1(InsertWildcard, "1"));
	menu.Separator();
	for(int i = 1; i <= 9; i++)
		menu.Add(Format(ptxt, i), THISBACK1(InsertWildcard, "@"+AsString(i)));
	menu.Separator();
	menu.Add(t_("To upper"), THISBACK1(InsertWildcard, "+"));
	menu.Add(t_("To lower"), THISBACK1(InsertWildcard, "-"));
	menu.Add(t_("InitCaps"), THISBACK1(InsertWildcard, "!"));
	menu.Separator();
	menu.Add(t_("Tab"), THISBACK1(InsertWildcard, "\\t"));
	menu.Add(t_("Line feed"), THISBACK1(InsertWildcard, "\\n"));
	int l, h;
	findreplace.replace.GetSelection(l, h);
	iwc.Clear();
	menu.Execute(&findreplace, findreplace.replace.GetPushScreenRect().TopRight());
	if(iwc.GetCount()) {
		if(!findreplace.regexp)
			findreplace.wildcards = true;
		findreplace.replace.SetFocus();
		findreplace.replace.SetSelection(l, h);
		findreplace.replace.RemoveSelection();
		findreplace.replace.Insert(iwc);
	}
}

void CodeEditor::CloseFindReplace()
{
	if(findreplace.IsOpen()) {
		FindReplaceAddHistory();
		RemoveFrame(findreplace);
	}
}

void CodeEditor::EscapeFindReplace()
{
	CloseFindReplace();
	if(ff_start_pos >= 0 && ff_start_pos < GetLength() && findreplace.IsIncremental() && do_ff_restore_pos) {
		SetCursor(ff_start_pos);
		ff_start_pos = -1;
	}
}

void CodeEditor::IncrementalFind()
{
	NoFindError();
	findreplace.Sync();
	if(!findreplace.IsIncremental() || findreplace.GetTopCtrl() == &findreplace) // || we are block replace
		return;
	bool b = FindFrom(ff_start_pos >= 0 && ff_start_pos < GetLength()
	             && findreplace.incremental_from_cursor ? ff_start_pos : 0, false, false);
	findreplace.amend.Enable(b);
	if(!b)
		NotFound();
}

void CodeEditor::DoFind()
{
	Find(false, false);
}

void CodeEditor::DoFindBack()
{
	Find(true, false);
}

void CodeEditor::SerializeFind(Stream& s)
{
	int version = 2;
	s / version;
	s % findreplace.find;
	findreplace.find.SerializeList(s);
	s % findreplace.wholeword % findreplace.ignorecase % findreplace.wildcards;
	if(version >= 0)
		s % findreplace.samecase;
	s % findreplace.replace;
	if(version >= 1)
		s % findreplace.incremental;
	if(version >= 2)
		s % findreplace.regexp;
	findreplace.replace.SerializeList(s);
}

CodeEditor::FindReplaceData CodeEditor::GetFindReplaceData() const
{
	FindReplaceData r;
	r.find = ~findreplace.find;
	r.replace = ~findreplace.replace;
	r.wholeword = ~findreplace.wholeword;
	r.ignorecase = ~findreplace.ignorecase;
	r.wildcards = ~findreplace.wildcards;
	r.samecase = ~findreplace.samecase;
	r.regexp = ~findreplace.regexp;
	return r;
}

void CodeEditor::SetFindReplaceData(const FindReplaceData& r)
{
	findreplace.find <<= r.find;
	findreplace.replace <<= r.replace;
	findreplace.wholeword <<= r.wholeword;
	findreplace.ignorecase <<= r.ignorecase;
	findreplace.wildcards <<= r.wildcards;
	findreplace.samecase <<= r.samecase;
	findreplace.regexp <<= r.regexp;
	findreplace.mode <<= 0;
}

void CodeEditor::FindPrevNext(bool prev)
{
	if(!findreplace.IsOpen())
		OpenNormalFindReplace0(false);
	if(Find(prev, false))
		NoFindError();
	else
		NotFound();
}

void CodeEditor::FindNext()
{
	FindPrevNext(false);
}

void CodeEditor::FindPrev()
{
	FindPrevNext(true);
}

END_UPP_NAMESPACE
